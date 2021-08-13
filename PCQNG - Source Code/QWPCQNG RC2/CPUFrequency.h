//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2001-2003 The Quantum World Corporation. All rights reserved.
//

// Version History:
// 2003.07.01    PAW    Creation

#pragma once

class CCPUFrequency
{
public:
	CCPUFrequency(void);
	~CCPUFrequency(void);

	// Measures CPU frequency with error indicated.
	void Measure(double& Frequency, double& Error);

protected:
	// Syncpoint to measure CPU frequency
	struct SyncPoint
	{
		unsigned __int64 TS1;	// TS at beginning of bracket
		unsigned __int64 TS2;	// TS at end of bracket
		LARGE_INTEGER HPC;		// High performance count in bracket
	};

	// Univarsal SyncPoints
	SyncPoint SP1;
	SyncPoint SP2;

	// Starts a CPU frequency measurement
	void Start();

	// Attempts to get a good measurement point syncronizing TS and HPC
	void GetSyncPoint(SyncPoint& SyncPoint);
	// Calcs frequency of the system and returns error
	void CalcSystemFreq(double& TSFrequency, double& TSClockError, SyncPoint SyncPoint1, SyncPoint SyncPoint2);

	// Returns the current TSC
	inline unsigned __int64 RDTSC();
};
