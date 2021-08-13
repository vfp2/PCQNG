//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2001-2003 The Quantum World Corporation. All rights reserved.
//

// Version History:
// 2003.07.01    PAW    Creation

#pragma once

#include "Mmsystem.h"

#include "cpufrequency.h"
#include "TabCorrector.h"

class CDevice
{
public:
	CDevice(void);
	virtual ~CDevice(void);

	// Opens the PCQNG
	virtual HRESULT Open(void);
	// Closes PCQNG
	virtual HRESULT Close(void);

	// Returns the next 32-bit number from the buffer
	virtual HRESULT GetInt32(long* pInt32);
	// Returns a uniform number of (0, 1]
	virtual HRESULT GetUniform(double* pUniform);
	// Returns a normal number from the buffer (generated in pairs)
	virtual HRESULT GetNormal(double* pNormal);
	// Returns a block of bytes from the hardware
	virtual HRESULT GetBytes(void* pOutBuffer, unsigned long Length);

	// Clears all buffers - provides "fresh" data
	virtual HRESULT ClearAll(void);
	// Clears buffers, including the correctors - then reseeds correctors
	virtual HRESULT Reset(void);

	// Sets the mode to new requested value
	virtual HRESULT SetMode(float ModeRequest);
	// Returns the current mode value
	virtual HRESULT GetMode(float* pMode);

protected:
	// Failure status of device
	HRESULT generalStatus;

	// Mutex handle to determine if control already running (using mutex)
	HANDLE mutexLock;
	// Attempts to lock pcqng device to prevent multiple instances
	HRESULT LockInstance(void);
	// Unlock instance of PCQNG device, no longer running - open for other apps
	HRESULT UnlockInstance(void);

	// Checks system requirements
	HRESULT CheckSystem(void);

	// Used to measure CPU frequency and thus quantization
	CCPUFrequency CPUFrequency;
	// CPU frequency
	unsigned __int64 cpuFreq;
	// Quantization factor for this machine
	ULONG quantFactor;
	// Measures and/or reads quantization from registry
	HRESULT GetQuantization(ULONG* pQuantFactor, unsigned __int64* pCPUFreq);

	// Auto-reset, non-signaled event for Multimedia pulsing
	HANDLE eventMMPulse;
	// Handle to auto-reset event to show that bytes available
	HANDLE eventNewBytesAvailable;
	// Stores timer resolution
	UINT mMTimerResolution;
	// Stores timer ID
	MMRESULT timerID;

	// Starts the MMtimer and thread for actual device functionality
	HRESULT StartDevice(void);
	// Stops actual device functionality MMTimer/Thread
	HRESULT StopDevice(void);

	// Used in assembling byte words
	BYTE assembleWord8;
	// Counts number of bits already assembled
	int assembleCount;

	// Pointer of reading data into the buffer from the device
	int bufferInPointer;
	// Pointer for reading data out of raw data buffer
	int bufferOutPointer;
	// Buffer, feed from device - out to client
	char* pBuffer;
	// Bytes available for client
	int bytesInBuffer;

	// Seeds PCQNG correctors with amount of bytes indicated, then resets buffers
	HRESULT SelfSeed(int Bytes);

	// Second normal number produced by GetNormal property
	double normalConjugate;
	// Indicates if two new normal numbers need to be calculated, or if the normalConjugate should be read
	bool needNewNormalCalc;	
	// Half of LSB (49th bit) in 48 bit encoded uniform number for normal calc
	double halfOfLSB;

	// Returns the current TSC
	inline unsigned __int64 RDTSC();

	// Bit Corrector
	CTabCorrector<BYTE> BitCorrector;
	// Byte Word Corrector
	CTabCorrector<BYTE> WordCorrector;
	// DMMI Corrector
	CTabCorrector<BYTE> DMMICorrector;

	// Skip bit corrector?
	bool SkipBitCorrector;
	// Skip byte corrector?
	bool SkipByteCorrector;

	// Ongoing bit counter (raw bits)
	int bitCounter;
	// This many bits til one taken for buffer
	int modeCounter;
	// Modes requiring multiples of 8 bits per sample
	int modeExtended;

	// Sets diagnostics mode if exists
	HRESULT SetRxMode(DWORD RxMode);

private:
	// Critical section syncronization object
	CRITICAL_SECTION syncCritical;
	// Syncronizes ClearAll method
	CRITICAL_SECTION syncCritReset;

	// Called on a MMPulse
	static void CALLBACK OnMMPulse(UINT wTimerID, UINT msg, DWORD pObject, DWORD dw1, DWORD dw2);
};