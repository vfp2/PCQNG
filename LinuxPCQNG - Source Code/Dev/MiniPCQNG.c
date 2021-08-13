/////////////////////////////////////////////////////////////////////////////
//
// MiniPCQNG.c - Mini PCQNG implementation for Linux
//
// Copyright © 2001-2003 The Quantum World Corporation. All rights reserved
//
// Confidential
//

// Version History
// PAW		2003-03-10		Creation

// Win32 if run on Windows, else Lin32 for Linux
#define Win32
// #define Lin32

unsigned long MakeWord(void)
{
// Define vars ///////////////////////////////////////////////////////////////
	// To return 32 bit random result
	unsigned long RetVal = 0;

	// To store timestamp counter word, low word only 
	unsigned long TSCWord = 0;

	// Used for intermediate result
	double CalcDouble = 0.;

#ifdef Win32
	// 64 bit word used for processing
	__int64 CalcWord64 = 0;
#endif
#ifdef Lin32
	// Linux, I think that "long long" = 64 bit, also try "u64"
	long long CalcWord64 = 0;
#endif
//////////////////////////////////////////////////////////////////////////////

// Each interrupt produces a 32 bit word
// XOR 4 32-bit results from interrupts to get result near Entropy=1
for (int i=0; i<4; i++)
{

// Wait for interrupt ////////////////////////////////////////////////////////
#ifdef Win32
	// This Sleep is intended to simulate an interrupt ~64Hz Windows
	// Wait on interrupt in Linux code in Lin32 #ifdef following
	Sleep(15);
#endif
#ifdef Lin32
	// Wait for interrupt here 
#endif
//////////////////////////////////////////////////////////////////////////////


// Read TSC //////////////////////////////////////////////////////////////////
#ifdef Win32
	// Windows inline asm for TSC 32 LSBits (eax) -> TSCWord
	__asm
	{
		rdtsc
		mov dword ptr [TSCWord], eax
	}
#endif
#ifdef Lin32
	// Inline asm for Linux TSC here, only need 32 LSBits (eax)
#endif
//////////////////////////////////////////////////////////////////////////////


// Special randomizing processing ////////////////////////////////////////////
	CalcWord64 = TSCWord;

	// CalcWord64 = Mod(CalcWord64^2, 3719549303) * Mod(CalcWord64^2, 4959399113)
	CalcWord64 *= CalcWord64;
	CalcWord64 = (CalcWord64 % 3719549303) * (CalcWord64 % 4959399113);

	// CalcDouble = 2^32 * (Mod(CalcWord64, 12884901893) / 12884901893)
	CalcDouble = ((double)(CalcWord64 % 12884901893))/12884901893.;
	CalcDouble *= 4294967296.;

	// RetVal = Retval XOR Floor(CalcDouble)
	RetVal ^= (unsigned long)CalcDouble;

//////////////////////////////////////////////////////////////////////////////

}

	return RetVal;
}

