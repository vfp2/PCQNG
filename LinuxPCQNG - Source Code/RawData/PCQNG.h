/////////////////////////////////////////////////////////////////////////////
//
// PCQNG.h - Header for CPCQNG class (Visual C++ 6.0)
//
//      Copyright © 2001 The Quantum World Corporation. All rights reserved
//

#include <windows.h>
#include <winioctl.h>
#include "PCQNG_IOCTL.h"

#if !defined(PCQNG_H)
#define PCQNG_H

class CPCQNG  
{
public:
	// Open/Close driver
	HANDLE Open();
	bool Close();

	// Read from driver
	bool Read( void* RandWord );

	// Set/Read driver modes
	bool SetMode( unsigned long ModeWord );
	bool GetMode( unsigned long* CurrentMode );
	
	// Clear all driver internal buffers
	bool StartBurst();


protected:
	HANDLE m_hPCQNG;	// Open handle to PCQNG driver
	DWORD m_WordLength;	// Length of read buffer in bytes (mode dependant)
};

#endif