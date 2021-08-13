//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2001-2003 The Quantum World Corporation. All rights reserved.
//

// Version History:
// 2003.07.01    PAW    Creation


#include "StdAfx.h"
#include "device.h"
#include "math.h"

// Length of buffer 10K
#define BuffLength 10240

CDevice::CDevice(void)
: bufferInPointer(0)
, bufferOutPointer(0)
, bytesInBuffer(0)
, pBuffer(NULL)
, bitCounter(0)
, normalConjugate(0)
, needNewNormalCalc(true)
, mutexLock(NULL)
, quantFactor(1)
, mMTimerResolution(0)
, assembleWord8(0)
, assembleCount(0)
, generalStatus(PCQNG_E_DEVICE_NOT_OPEN)
, SkipBitCorrector(false)
, SkipByteCorrector(false)
{
	// initialize critical section objects
	InitializeCriticalSection(&syncCritical);
	InitializeCriticalSection(&syncCritReset);

	// manual-reset, non-signaled event to release a thread waiting for new data
	eventNewBytesAvailable = CreateEvent(NULL, TRUE, FALSE, NULL);
	// Auto-reset, non-signaled event for Multimedia pulsing
	eventMMPulse = CreateEvent(NULL, FALSE, FALSE, NULL);

	// Create a buffer (10240+12 bytes for rollover)
	pBuffer = new char[BuffLength+12];

	// Init Bit corrector
	int RegLengths[7];
	RegLengths[0] = 31;
	RegLengths[1] = 37;
	RegLengths[2] = 41;
	RegLengths[3] = 43;
	RegLengths[4] = 47;
	RegLengths[5] = 53;
	RegLengths[6] = 59;
	BitCorrector.SetRegisters(RegLengths, 7);

	// Init Word corrector
	RegLengths[0] = 11;
	RegLengths[1] = 13;
	RegLengths[2] = 17;
	RegLengths[3] = 19;
	RegLengths[4] = 23;
	RegLengths[5] = 29;
	WordCorrector.SetRegisters(RegLengths, 6);

	// Init DMMI Corrector
	RegLengths[0] = 5;
	RegLengths[1] = 7;
	RegLengths[2] = 9;
	DMMICorrector.SetRegisters(RegLengths, 3);

	// calc the halfOfLSB
	__int64 BitHalfOfLSB;
	BitHalfOfLSB = 0x3ce0000000000000;
	memcpy(&halfOfLSB, &BitHalfOfLSB, 8);
}

CDevice::~CDevice(void)
{
	// make sure device is closed
	Close();

	// release buffer from mem
	if (pBuffer != NULL)
	{
		delete pBuffer;
		pBuffer = NULL;
	}

	// release event resources
	CloseHandle(eventMMPulse);
	CloseHandle(eventNewBytesAvailable);

	// free critical section object
	DeleteCriticalSection(&syncCritical);
	DeleteCriticalSection(&syncCritReset);
}

// Opens the PCQNG
HRESULT CDevice::Open(void)
{
	// Fear the worst
	HRESULT RetVal = PCQNG_E_DEVICE_UNAVAILABLE;
	generalStatus = PCQNG_E_DEVICE_UNAVAILABLE;

	// Check sys req's
	RetVal = CheckSystem();
	if (RetVal!=PCQNG_S_OK)
		return RetVal;

	// Lock instance
	RetVal = LockInstance();
	if (RetVal!=PCQNG_S_OK)
		return RetVal;

	// Get/Set quantization
	RetVal = GetQuantization(&quantFactor, &cpuFreq);
	if (RetVal!=PCQNG_S_OK)
	{
		Close();
		return RetVal;
	}

	// Set Mode to 1000 bits/sec
	modeCounter = -123;
	modeExtended = 1;

	// Start the actual device functionality (MMTimer/Thread)
	RetVal = StartDevice();
	if (RetVal!=PCQNG_S_OK)
	{
		Close();
		return RetVal;
	}

	// Fast Seed 5x, then call mode, mode will seed 1x if rate<8000
	SetMode(8);
	SelfSeed(640);
	RetVal = SetMode(1);
	if (RetVal!=PCQNG_S_OK)
	{
		Close();
		return RetVal;
	}

	// Check for diagnostics mode in registry
	HKEY RegKey;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\QWC\\PCQNG", NULL, KEY_READ, &RegKey);
	DWORD Type = REG_DWORD;
	DWORD Length = 4;
	DWORD RxMode = 0;
	RegQueryValueEx(RegKey, "RxMode", NULL, &Type, (LPBYTE)&RxMode, &Length);
	RegCloseKey(RegKey);
	if (RxMode!=0)	
		SetRxMode(RxMode); // Indeed special diagnostics mode

	generalStatus = RetVal;
	return RetVal;
}

// Closes PCQNG
HRESULT CDevice::Close(void)
{
	// Stop device
	StopDevice();

	// Close device "singleton" lock
	if (mutexLock!=NULL)
	{
		CloseHandle(mutexLock);
		mutexLock=NULL;
	}

	generalStatus = PCQNG_E_DEVICE_NOT_OPEN;
	return PCQNG_S_OK;
}

// Starts the MMtimer and thread for actual device functionality
#pragma warning (disable : 4311)
HRESULT CDevice::StartDevice(void)
{
	// Start device (MMTimer)
	TIMECAPS tc;
	UINT     wTimerRes;
	if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
		return PCQNG_E_GENERAL_FAILURE;

	// Set minimum resolution possible
	wTimerRes = min(max(tc.wPeriodMin, 1), tc.wPeriodMax);
	timeBeginPeriod(wTimerRes);

	// Remember resolution, place in registry
	mMTimerResolution = wTimerRes;
	DWORD RegRes = (DWORD)wTimerRes;
	HKEY RegKey;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\QWC\\PCQNG", NULL, KEY_ALL_ACCESS, &RegKey);
	RegSetValueEx(RegKey, "MMTimerResolution", NULL, REG_DWORD, (BYTE*)&RegRes, 4);
	RegCloseKey(RegKey);

	// Restart MMtimer
	timerID = timeSetEvent(
		mMTimerResolution,				// Best resolution
		0,								// Resolution (global variable)
		(LPTIMECALLBACK)OnMMPulse,
		(DWORD)this,					// User data
		TIME_PERIODIC /*|				// Periodic timer event
		TIME_KILL_SYNCHRONOUS*/);		// Synchronizes kill

	if (timerID==NULL)
		return PCQNG_E_GENERAL_FAILURE;

	return PCQNG_S_OK;
}
#pragma warning (default : 4311)

// Stops actual device functionality MMTimer/Thread
HRESULT CDevice::StopDevice(void)
{
	// stop MMtimer
	timeKillEvent(timerID);

	return PCQNG_S_OK;
}

// Attempts to lock pcqng device to prevent multiple instances
HRESULT CDevice::LockInstance(void)
{
	DWORD WinVer = GetVersion();

	// Check if already running
	char* LockName = "Global\\QWPCQNG_GLOBAL_LOCK";
	// Win 9x/NT4 cannnot have backslash
	if ((WinVer&0xff)==4)
		memcpy(LockName, "QWPCQNG_GLOBAL_LOCK", 20);
	// Try to create mutex with global name	
	mutexLock = CreateMutex(NULL, TRUE, LockName);
	if ((mutexLock==NULL) || (GetLastError()==ERROR_ALREADY_EXISTS))
		return PCQNG_E_DEVICE_UNAVAILABLE;

	return PCQNG_S_OK;
}

// Unlock instance of PCQNG device, no longer running - open for other apps
HRESULT CDevice::UnlockInstance(void)
{
	if (CloseHandle(mutexLock)==S_OK)
		return PCQNG_S_OK;
	else
		return PCQNG_E_GENERAL_FAILURE;
}

// Measures and/or reads quantization from registry
HRESULT CDevice::GetQuantization(ULONG* pQuantFactor, unsigned __int64* pCPUFreq)
{
	// Get previous CPU measurement from registry
	HKEY RegKey;
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\QWC\\PCQNG", NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &RegKey, NULL)!=ERROR_SUCCESS)
        RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\QWC\\PCQNG", NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &RegKey, NULL);
	DWORD Length = 8;
	double RegCPUFreq = 0;
	ULONG RegQuantFactor = 0;
	DWORD Type = REG_QWORD;
	RegQueryValueEx(RegKey, "CPUFrequency", NULL, &Type, (LPBYTE)&RegCPUFreq, &Length);
	Type = REG_DWORD;
	RegQueryValueEx(RegKey, "QuantizationFactor", NULL, &Type, (LPBYTE)&RegQuantFactor, &Length);
	RegCloseKey(RegKey);

	// Check/Measure CPU speed with registry version
	double CPUFreq, CPUClockErr;

	do
	{
		CPUFrequency.Measure(CPUFreq, CPUClockErr);

	} while ((CPUClockErr>10e-6) && ((fabs(CPUFreq-RegCPUFreq)/RegCPUFreq)>.01));	

	// If good measurement, store in Registry
	if (CPUClockErr<10e-6)
	{
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\QWC\\PCQNG", NULL, KEY_ALL_ACCESS, &RegKey)!=ERROR_SUCCESS)
            RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\QWC\\PCQNG", NULL, KEY_ALL_ACCESS, &RegKey);
		RegCPUFreq = CPUFreq;
		RegQuantFactor = (ULONG)((CPUFreq/33333333)+.5);
		RegSetValueEx(RegKey, "CPUFrequency", NULL, REG_QWORD, (BYTE*)&RegCPUFreq, 8);
		if (RegSetValueEx(RegKey, "QuantizationFactor", NULL, REG_DWORD, (BYTE*)&RegQuantFactor, 4)!=ERROR_SUCCESS)
		{
			RegCloseKey(RegKey);
			return PCQNG_E_GENERAL_FAILURE;
		}
		RegCloseKey(RegKey);
	}

	memcpy(pQuantFactor, &RegQuantFactor, 4);
	unsigned __int64 CPUFreqInt = (unsigned __int64)RegCPUFreq;
	memcpy(pCPUFreq, &CPUFreqInt, 8); 

	return PCQNG_S_OK;
}

// Checks system requirements (RDTSC and Win9x+/NT4+)
HRESULT CDevice::CheckSystem(void)
{
	// Check RDTSC (Pentium class processor)
	try
	{
		__asm { rdtsc }
	}
	catch (...)
	{
		return PCQNG_E_INVALID_SYSTEM;
	}
		
	// Check Windows version (MMTimer capable)
	DWORD WinVer = GetVersion();
	if ((WinVer&0xff)<4)  // Invalid Windows
		return PCQNG_E_INVALID_SYSTEM;

	// System OK
	return PCQNG_S_OK;
}

// Returns the next 32-bit number from the buffer
HRESULT CDevice::GetInt32(long* pInt32)
{
	// Infinite, should have a time-out!!! ???
	while ((bytesInBuffer<4) && (generalStatus==PCQNG_S_OK))
		WaitForSingleObject(eventNewBytesAvailable, INFINITE);

	// copy 4 bytes over
	*pInt32 = *((long*)&pBuffer[bufferOutPointer]);

	// update OutPointer
	bufferOutPointer += 4;
	bufferOutPointer %= BuffLength;

	EnterCriticalSection(&syncCritical);
		// update buffer status
		bytesInBuffer -= 4;
	LeaveCriticalSection(&syncCritical);

	return generalStatus;
}

// Returns a uniform number of (0, 1]
HRESULT CDevice::GetUniform(double* pUniform)
{
	// infinite, should have a time-out!!!
	while ((bytesInBuffer<6) && (generalStatus==PCQNG_S_OK))
		WaitForSingleObject(eventNewBytesAvailable, INFINITE);

	// copy 6 bytes into mantissa
	__int64 UInt64;
	UInt64 = *((__int64*)&pBuffer[bufferOutPointer]);
	UInt64 &= 0x0000ffffffffffff;
	*pUniform = (double)UInt64;
	*pUniform /= 281474976710656.;

	// update OutPointer
	bufferOutPointer += 6;
	bufferOutPointer %= BuffLength;

	EnterCriticalSection(&syncCritical);
		// update buffer status
		bytesInBuffer -= 6;
	LeaveCriticalSection(&syncCritical);

	return generalStatus;
}

// Returns a normal number from the buffer (generated in pairs)
HRESULT CDevice::GetNormal(double* pNormal)
{
	if (needNewNormalCalc)
	{
		// infinite, should have a time-out!!!
		while ((bytesInBuffer<12) && (generalStatus==PCQNG_S_OK))
			WaitForSingleObject(eventNewBytesAvailable, INFINITE);

		// uniform numbers to go into equation
		double Uniform1;
		double Uniform2;

		// make Uniform1
		__int64 UInt64;
		UInt64 = *((__int64*)&pBuffer[bufferOutPointer]);
		UInt64 &= 0x0000ffffffffffff;
		Uniform1 = (double)UInt64;
		Uniform1 /= 281474976710656.;
		Uniform1 += halfOfLSB;

		// make Uniform2
		UInt64 = *((__int64*)&pBuffer[bufferOutPointer+6]);
		UInt64 &= 0x0000ffffffffffff;
		Uniform2 = (double)UInt64;
		Uniform2 /= 281474976710656.;
		Uniform2 += halfOfLSB;

		// n1 = cos(2PI * u2) * sqrt(-2 * ln(u1)) 
		// n1 = sin(2PI * u2) * sqrt(-2 * ln(u1))
		double LogPart = sqrt(-2. * log(Uniform1));
		*pNormal = cos(6.28318530717958647692528676656 * Uniform2) * LogPart;
		normalConjugate = sin(6.28318530717958647692528676656 * Uniform2) * LogPart;

		// update OutPointer
		bufferOutPointer += 12;
		bufferOutPointer %= BuffLength;

		EnterCriticalSection(&syncCritical);
			// update buffer status
			bytesInBuffer -= 12;
		LeaveCriticalSection(&syncCritical);

		needNewNormalCalc = false;
	}
	else
	{
		*pNormal = normalConjugate;

		needNewNormalCalc = true;
	}

	return generalStatus;
}

// Returns array of bytes from buffer
HRESULT CDevice::GetBytes(void* pOutBuffer, unsigned long Length)
{
	// wait for bytes needed
	while ((bytesInBuffer<(int)Length) && (generalStatus==PCQNG_S_OK))
		WaitForSingleObject(eventNewBytesAvailable, INFINITE);

	// check to see if buffer wrap around will occur
	// remember we have copied the first 12 "wrap-around" bytes to the end of the buffer
	if ((bufferOutPointer+Length) < BuffLength)
	{
		// copy without wrap-around
		memcpy(pOutBuffer, &pBuffer[bufferOutPointer], Length);
	}
	else
	{
		// copy with wrap around
		memcpy(pOutBuffer, &pBuffer[bufferOutPointer], BuffLength-bufferOutPointer);
		memcpy(&((PBYTE)pOutBuffer)[BuffLength-bufferOutPointer], &pBuffer[0], Length - (BuffLength-bufferOutPointer));
	}

	// update OutPointer
	bufferOutPointer += Length;
	bufferOutPointer %= BuffLength;

	EnterCriticalSection(&syncCritical);
		// update buffer status
		bytesInBuffer -= Length;
	LeaveCriticalSection(&syncCritical);

	return generalStatus;
}

// Clears all buffers - provides "fresh" data
HRESULT CDevice::ClearAll(void)
{
	// make sure ClearAll is sync'd
	EnterCriticalSection(&syncCritReset);

	// clear buffer
	bufferInPointer = 0;
	bufferOutPointer = 0;
	bytesInBuffer = 0;
	needNewNormalCalc = true;

	// Start bit counter over
	bitCounter = 0;

	// make sure ClearAll is sync'd
	LeaveCriticalSection(&syncCritReset);

	return generalStatus;
}

// Clears buffers, including the correctors - then reseeds correctors
HRESULT CDevice::Reset(void)
{
	// make sure ClearAll is sync'd
	EnterCriticalSection(&syncCritReset);

	BitCorrector.Reset();
	WordCorrector.Reset();

	// clear buffer
	bufferInPointer = 0;
	bufferOutPointer = 0;
	bytesInBuffer = 0;
	needNewNormalCalc = true;

	// Start bit counter over
	bitCounter = 0;

	// make sure ClearAll is sync'd
	LeaveCriticalSection(&syncCritReset);

	// Fast Seed 5x, then call mode, mode will seed 1x if rate<8000
	SetMode(8);
	SelfSeed(640);
	SetMode(1);	// Set to default mode

	return generalStatus;
}

#pragma warning (disable : 4244)
// Sets the mode to new requested value
HRESULT CDevice::SetMode(float ModeRequest)
{
	// CurrentMode?
	float CurrentMode;
	GetMode(&CurrentMode);

	// Raw
	if (ModeRequest==0.)
	{
		modeCounter = 0;
		modeExtended = 0;
	}

	// DMMI
	else if (ModeRequest==-1.)
	{
		modeCounter = 0;
		modeExtended = -1;
		SelfSeed(210);
	}

	else
	{
		// All other modes
		float Finder = .125;
		for (int i=0; i<=10; i++)
		{
			if (i>=10)
				return PCQNG_E_INVALID_MODE;

			if (ModeRequest!=Finder)
				Finder *= 2;
			else
			{
				if (ModeRequest<CurrentMode)
				{	
					// Quickseed on 1000 bits
					modeExtended = 1;
					modeCounter = 8;
					SelfSeed(128);
				}

				if (ModeRequest<=8)
				{
					// Count up this many raw bits until output one bit for use
					modeCounter = (int)(8./ModeRequest);
					// In extended mode run through this many times.
					modeExtended = 1;

					break;
				}
				else
				{
					modeCounter = 1;
					modeExtended = (int)(ModeRequest/8.);

					break;
				}
			}
		}
	}

	ClearAll();

	return PCQNG_S_OK;
}
#pragma warning (default : 4244)

// Sets special diagnostics modes
HRESULT CDevice::SetRxMode(DWORD RxMode)
{
	switch (RxMode&0xff)
	{
	// TSC data mode
	case 0x11:
		modeExtended = -586;
		modeCounter = 1;
		break;

	// Counter data output - resets to 0 on Reset()
	case 0x12:
		modeExtended = -123;
		modeCounter = 1;
		break;

	// Both correctors OK
	case 0x20:
		SkipBitCorrector = false;
		SkipByteCorrector = false;
		break;

	// Bit corrector only
	case 0x21:
		SkipBitCorrector = false;
		SkipByteCorrector = true;
		break;

	// Word corrector only
	case 0x22:
		SkipBitCorrector = true;
		SkipByteCorrector = false;
		break;
	}

	// Find super multiplication, if exists in top 16 bits
	RxMode >>= 19;	// already devide by 8, after 16 bits
	int Factor = 1;
	while (RxMode>0)
	{
		Factor *= 2;
		RxMode >>= 1;
	}
	Factor /= 2;
	if (Factor>1)
	{
		modeExtended = Factor;
		modeCounter = 1;
	}

	ClearAll();
	
	return PCQNG_S_OK;
}

// Returns the current mode value
HRESULT CDevice::GetMode(float* pMode)
{
	float Mode;

	// > 8x
	if (modeExtended>1)
		Mode = (float)(modeExtended*8);

	// Normal
	if (modeExtended==1)
		Mode = 8/((float)modeCounter);

	// DMMI
	if (modeExtended==-1)
		Mode = -1;

	// Raw
	if ((modeExtended==0) && (modeCounter==0))
		Mode = 0;

	memcpy(pMode, &Mode, 4);

	return PCQNG_S_OK;
}

// OnMMPulse sampling
#pragma warning (disable : 4311; disable: 4312)
void CDevice::OnMMPulse(UINT wTimerID, UINT msg, DWORD pObject, DWORD dw1, DWORD dw2)
{
	// Get a word instantly
	unsigned __int64 RawWord;
	__asm
	{
		rdtsc
		mov dword ptr [RawWord], eax
		mov dword ptr [RawWord]+4, edx
	}

	// Resolve object instance
	CDevice* pDevice;
	pDevice =  (CDevice*) pObject;

	// ClearAll sync'd
	EnterCriticalSection(&pDevice->syncCritReset);

	// Regular mode?
	if (pDevice->modeExtended>=1)
	{
		// Divide out quantization, with rounding
		RawWord = RawWord/pDevice->quantFactor + ((((RawWord%pDevice->quantFactor)<<1)>=(pDevice->quantFactor))? 1 : 0);

		// Feed in lsb 8 bits into bit corrector
		for (int x=0; x<pDevice->modeExtended; x++)
		{
			BYTE CorrectedBit = 0;
			for (int i=7; i>=0; i--)
			{
				if (pDevice->SkipBitCorrector==false)
					CorrectedBit ^= (pDevice->BitCorrector.Run((BYTE)(RawWord>>i)&0x1));
				else
					CorrectedBit ^= (BYTE)(RawWord>>i)&0x1;

				pDevice->bitCounter++;
				if (!(pDevice->bitCounter%pDevice->modeCounter))
				{
					// Assemble 8-bit word
					pDevice->assembleWord8 <<= 1;
					pDevice->assembleWord8 |= (CorrectedBit&0x1);
					pDevice->assembleCount++;

					CorrectedBit = 0;
				}
			}
			// Place assembled word into buffer
			if (pDevice->assembleCount>=8)
			{
				// Buffer sync'd
				EnterCriticalSection(&pDevice->syncCritical);

				if (pDevice->bytesInBuffer<BuffLength)
				{
					if (pDevice->SkipByteCorrector==false)
						pDevice->pBuffer[pDevice->bufferInPointer] = pDevice->WordCorrector.Run(pDevice->assembleWord8);
					else
						pDevice->pBuffer[pDevice->bufferInPointer] = pDevice->assembleWord8;

					if (pDevice->bufferInPointer<12)
						pDevice->pBuffer[pDevice->bufferInPointer+BuffLength] = pDevice->pBuffer[pDevice->bufferInPointer];

					pDevice->bytesInBuffer++;
					pDevice->bufferInPointer++;
					pDevice->bufferInPointer %= BuffLength;
				}
				pDevice->assembleCount = 0;

				// Buffer sync'd
				LeaveCriticalSection(&pDevice->syncCritical);
			}

		PulseEvent(pDevice->eventNewBytesAvailable);
		}
	}
	// Raw bits
	else if ((pDevice->modeExtended==0) && (pDevice->modeCounter==0))
	{
		// Divide out quantization, with rounding
		RawWord = RawWord/pDevice->quantFactor + ((((RawWord%pDevice->quantFactor)<<1)>=(pDevice->quantFactor))? 1 : 0);

		// 8 bits to put onto buffer
		pDevice->assembleCount = 8;
		pDevice->assembleWord8 = (BYTE)RawWord&0xff;

		// Place assembled word into buffer
		if (pDevice->assembleCount>=8)
		{
			// Buffer sync'd
			EnterCriticalSection(&pDevice->syncCritical);

			if (pDevice->bytesInBuffer<BuffLength)
			{
				pDevice->pBuffer[pDevice->bufferInPointer] = pDevice->assembleWord8;
				if (pDevice->bufferInPointer<12)
					pDevice->pBuffer[pDevice->bufferInPointer+BuffLength] = pDevice->pBuffer[pDevice->bufferInPointer];

				pDevice->bytesInBuffer++;
				pDevice->bufferInPointer++;
				pDevice->bufferInPointer %= BuffLength;
			}

			pDevice->assembleCount=0;

			// Buffer sync'd
			LeaveCriticalSection(&pDevice->syncCritical);
		}
	}
	// DMMI
	else if (pDevice->modeExtended==-1)
	{
		// Divide out quantization, with rounding
		RawWord = RawWord/pDevice->quantFactor + ((((RawWord%pDevice->quantFactor)<<1)>=(pDevice->quantFactor))? 1 : 0);

		//BYTE CorrectedBit = pDevice->TableDMMI[RawWord&0xff];
		// Assemble 8-bit word
		BYTE CorrectedBit = 0;
		for (int y=0; y<8; y++)
		{
			CorrectedBit ^= pDevice->DMMICorrector.Run((BYTE)RawWord&0x1);
			RawWord >>= 1;
		}
		pDevice->assembleWord8 <<= 1;
		pDevice->assembleWord8 |= CorrectedBit;
		pDevice->assembleCount++;

		// Place assembled word into buffer
		if (pDevice->assembleCount>=8)
		{
			// Buffer sync'd
			EnterCriticalSection(&pDevice->syncCritical);

			if (pDevice->bytesInBuffer<BuffLength)
			{
				pDevice->pBuffer[pDevice->bufferInPointer] = pDevice->assembleWord8;
				if (pDevice->bufferInPointer<12)
					pDevice->pBuffer[pDevice->bufferInPointer+BuffLength] = pDevice->pBuffer[pDevice->bufferInPointer];

				pDevice->bytesInBuffer++;
				pDevice->bufferInPointer++;
				pDevice->bufferInPointer %= BuffLength;
			}

			pDevice->assembleCount=0;

			// Buffer sync'd
			LeaveCriticalSection(&pDevice->syncCritical);
		}
	}
	// Raw TSC
	else if (pDevice->modeExtended==-586)
	{
		// Place raw TSC into buffer
		DWORD LoWord = (DWORD)RawWord;

		// Buffer sync'd
		EnterCriticalSection(&pDevice->syncCritical);

		if (pDevice->bytesInBuffer<(BuffLength-3))
		{
			memcpy(&pDevice->pBuffer[pDevice->bufferInPointer], &LoWord, 4);
			if (pDevice->bufferInPointer<12)
				memcpy(&pDevice->pBuffer[pDevice->bufferInPointer+BuffLength], &LoWord, 4);

			pDevice->bytesInBuffer += 4;
			pDevice->bufferInPointer +=4;
			pDevice->bufferInPointer %= BuffLength;
		}

		// Buffer sync'd
		LeaveCriticalSection(&pDevice->syncCritical);
	}
	// Counter
	else if (pDevice->modeExtended==-123)
	{
		// Place counter into buffer
		pDevice->bitCounter++;

		// Buffer sync'd
		EnterCriticalSection(&pDevice->syncCritical);

		if (pDevice->bytesInBuffer<(BuffLength-3))
		{
			memcpy(&pDevice->pBuffer[pDevice->bufferInPointer], &(pDevice->bitCounter), 4);
			if (pDevice->bufferInPointer<12)
				memcpy(&pDevice->pBuffer[pDevice->bufferInPointer+BuffLength], &(pDevice->bitCounter), 4);

			pDevice->bytesInBuffer += 4;
			pDevice->bufferInPointer +=4;
			pDevice->bufferInPointer %= BuffLength;
		}

		// Buffer sync'd
		LeaveCriticalSection(&pDevice->syncCritical);
	}

	// Fire new Bytes available event, pulse all waiting threads
	PulseEvent(pDevice->eventNewBytesAvailable);

	// Make sure ClearAll is sync'd
	LeaveCriticalSection(&pDevice->syncCritReset);
}
#pragma warning (default : 4311; default: 4312)

// Seeds PCQNG correctors with amount of bytes indicated, then resets buffers
HRESULT CDevice::SelfSeed(int Bytes)
{
	while (bytesInBuffer<Bytes)
		Sleep(1);	// Sleep will prevent lock-up

	ClearAll();	// Start fresh

	return PCQNG_S_OK;
}

// Returns the current TSC
unsigned __int64 CDevice::RDTSC()
{
	unsigned __int64 RetVal;

	__asm
	{
		rdtsc
		mov dword ptr [RetVal], eax
		mov dword ptr [RetVal]+4, edx
	}
	return RetVal;
}
