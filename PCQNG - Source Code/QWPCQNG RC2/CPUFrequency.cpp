//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2001-2003 The Quantum World Corporation. All rights reserved.
//

// Version History:
// 2003.07.01    PAW    Creation

#include "StdAfx.h"
#include "cpufrequency.h"

CCPUFrequency::CCPUFrequency(void)
{
	Start();
}

CCPUFrequency::~CCPUFrequency(void)
{
}

// Get Start Point
void CCPUFrequency::Start()
{
	GetSyncPoint(SP1);
}

// Measures CPU frequency with error indicated.
void CCPUFrequency::Measure(double& Frequency, double& Error)
{
measurestart:
	GetSyncPoint(SP2);
		
	if (SP2.HPC.QuadPart<SP1.HPC.QuadPart)
	{
		Start();	// Caught HPC rollover, start over
		goto measurestart;
	}

	// Calculate frequency and error
	CalcSystemFreq(Frequency, Error, SP1, SP2);
}

// Attempts to get a good measurement point syncronizing TS and HPC
void CCPUFrequency::GetSyncPoint(SyncPoint& SyncPoint)
{
	unsigned __int64 TSCDiff;
	unsigned __int64 TS1, TS2;
	LARGE_INTEGER HPC;

	TSCDiff = 0xffffffffffffffff;

	// Get best of at least 3+1 measurements
	for (int i=0; i<3; i++)
	{
		TS1 = RDTSC();
			QueryPerformanceCounter(&HPC);
		TS2 = RDTSC();

		// If the bracket is smaller this time;
		if (TSCDiff>(TS2-TS1))
		{
			// This should be as small as possible
			TSCDiff = TS2 - TS1;

			// This is the best measurement yet
			SyncPoint.TS1 = TS1;
			SyncPoint.TS2 = TS2;
			SyncPoint.HPC = HPC;

			// Get 3 more measurements to compare
			i=0;
		}
	}
}

void CCPUFrequency::CalcSystemFreq(double& TSFrequency, double& TSClockError,
								 SyncPoint SyncPoint1, SyncPoint SyncPoint2)
{
	// Calc TS interval using the mid of each TS bracket count
	unsigned __int64 TSBracket1 = SyncPoint1.TS2-SyncPoint1.TS1;
	unsigned __int64 TSBracket2 = SyncPoint2.TS2-SyncPoint2.TS1;
	unsigned __int64 TSInterval = SyncPoint2.TS1-SyncPoint1.TS1;
	TSInterval += (TSBracket2)/2 - (TSBracket1)/2;

	// Calc performance counter interval
	LARGE_INTEGER HPCInterval;
	HPCInterval.QuadPart = SyncPoint2.HPC.QuadPart - SyncPoint1.HPC.QuadPart;

	// Calc TS frequency
	LARGE_INTEGER HPF;
	QueryPerformanceFrequency(&HPF);
	TSFrequency = (double)TSInterval/(double)HPCInterval.QuadPart;
	TSFrequency *= (double)HPF.QuadPart;

	// Calc TS error per tick
	// Need HPC granularity in TS ticks
	double HPCError = TSFrequency /((double)HPF.QuadPart*(double)TSInterval);
	double BracketError = (double)(TSBracket1+TSBracket2)/(double)TSInterval;
	// Greatest error can be HPC granularity plus brackets in ticks
	TSClockError = BracketError + HPCError;
}

// Returns the current TSC
unsigned __int64 CCPUFrequency::RDTSC()
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