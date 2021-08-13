/////////////////////////////////////////////////////////////////////////////
//
// PCQNG.cpp - Implementation of the CPCQNG class (Visual C++ 6.0)
//
//      Copyright © 2001 The Quantum World Corporation. All rights reserved
//

#include "stdafx.h"
#include "PCQNG.h"

// Suppress "forcing value to bool 'true' or 'false'" warning
#pragma warning(disable:4800)

/////////////////////////////////////////////////////////////////////////////
//
// bool Read( void* RandWord ) - Reads a random word from the PCQNG driver
//
// Params: void* RandWord - A pointer to a buffer that receives the genreated
//                          random word. In integer mode this must be a
//                          pointer to an unsigned long, in floating point
//                          mode a pointer to a double, and in DMMI mode
//                          this must be a pointer to an unsigned char. 
// 
// Return: bool - true if successful, false otherwise
//
bool CPCQNG::Read( void* RandWord )
{
	bool bRet;			// Returns true if successful read, otherwise false.
	DWORD cbRet;

	bRet = DeviceIoControl(
			m_hPCQNG,			// handle to driver			
			(DWORD)IOCTL_READ,	// IoControlCode for Read
			NULL,				// no in-buffer
			0,					// no size of in-buffer
			RandWord,			// Outbuffer
			m_WordLength,		// size of out-buffer (set at mode change)
			&cbRet,				// bytes returned
			NULL				// not overlapped
	);
		
	return bRet;
}


/////////////////////////////////////////////////////////////////////////////
//
// HANDLE Open() - Opens a handle to the PCQNG driver
//
// Params: none
//
// Return: HANDLE - to the driver if successful,
//         otherwise INVALID_HANDLE_VALUE if unsuccessful
//
HANDLE CPCQNG::Open()
{
	m_hPCQNG = CreateFile(
			"\\\\.\\pcqng.qng",
			0,					// device query access
			0,					// no sharing
			NULL,				// handle can NOT be inherited
			0,
			FILE_FLAG_DELETE_ON_CLOSE,	// get driver out of memory on close
			NULL				// MUST be NULL
	);

	// By default the driver runs in integer mode 32 bits = 4 bytes
	m_WordLength = 4;

	return m_hPCQNG;	// Failed if returned value = INVALID_HANDLE_VALUE
}


/////////////////////////////////////////////////////////////////////////////
//
// bool Close() - Closes the PCQNG driver
//
// Params: none
//
// Return: bool - true if successful, otherwise false
//
bool CPCQNG::Close()
{
	// true if successful, otherwise false
	return (bool)CloseHandle( m_hPCQNG );
}


/////////////////////////////////////////////////////////////////////////////
//
// bool SetMode( unsigned long ModeWord ) - change PCQNG device mode
//
// Params: unsigned long ModeWord - PCQNG mode (see docs for mode info)
//
// Return: bool - true if successful with valid mode change, otherwise false
//
bool CPCQNG::SetMode( unsigned long ModeWord )
{
	bool bRet;			// Returns true if successful set, otherwise false.
	DWORD cbRet;

	bRet = DeviceIoControl(
			m_hPCQNG,				// handle to driver			
			(DWORD)IOCTL_SET_MODE,	// IoControlCode for Setting the Mode
			&ModeWord,				// in-buffer
			4,						// DWORD size
			NULL,					// no out-buffer
			0,						// no size of out-buffer
			&cbRet,					// bytes returned
			NULL					// not overlapped
	);
		
	if ( bRet )		// if successful
	{
		switch ( ModeWord&0xf000 )	// check which output mode
		{
			case 0x1000:		// integer, 32bis, 4 bytes
				m_WordLength = 4;
				break;

			case 0xD000:		// DMMI, 1bit in lsb of a byte
				m_WordLength = 1;
				break;

			case 0xF000:		// uniform (double), 8 bytes
				m_WordLength = 8;
				break;
		}
	}

	return bRet;
}


/////////////////////////////////////////////////////////////////////////////
//
// bool GetMode( unsigned long* CurrentMode ) - get PCQNG device mode
//
// Params: unsigned long* CurrentMode - buffer to be filled with PCQNG mode
//
// Return: bool - true if successful with valid mode change, otherwise false
//
bool CPCQNG::GetMode( unsigned long* CurrentMode )
{
	bool bRet;			// Returns true if successful mode read, otherwise false.
	DWORD cbRet;

	bRet = DeviceIoControl(
			m_hPCQNG,			// handle to driver
			(DWORD)IOCTL_GET_MODE,	// IoControlCode for Read Mode
			NULL,				// no in-buffer
			0,					// no size of in-buffer
			CurrentMode,		// Outbuffer
			4,					// size of out-buffer
			&cbRet,				// bytes returned
			NULL				// not overlapped
	);

	return bRet;
}


/////////////////////////////////////////////////////////////////////////////
//
// bool StartBurst() - reset driver buffers (used to produce "fresh" data)
//
// Params: none
//
// Return: bool - true if successful reset.
//
bool CPCQNG::StartBurst()
{
	bool bRet;			// Returns true if successful burst
	DWORD cbRet;

	bRet = DeviceIoControl(
			m_hPCQNG,			// handle to driver
			(DWORD)IOCTL_START_BURST,	// IoControlCode for Burst
			NULL,				// no in-buffer
			0,					// no size of in-buffer
			NULL,				// no out-buffer
			0,					// no size of out-buffer
			&cbRet,				// bytes returned
			NULL				// not overlapped
	);

	return bRet;
}
