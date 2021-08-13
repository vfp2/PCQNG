//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2001-2003 The Quantum World Corporation. All rights reserved.
//

// Version History:
// 2003.07.01    PAW    Creation

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0400	// Change this to the appropriate value to target Windows 2000 or later.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0400	// Change this to the appropriate value to target IE 5.0 or later.
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off ATL's hiding of some common and often safely ignored warning messages
#define _ATL_ALL_WARNINGS


#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>


// Custom PCQNG HRESULT messages

//
// MessageId: PCQNG_S_OK
//
// MessageText:
//
//  PCQNG reports success.
//
#define PCQNG_S_OK						_HRESULT_TYPEDEF_(0x00044500L)

//
// MessageId: PCQNG_E_GENERAL_FAILURE
//
// MessageText:
//
//  PCQNG general error.
//
#define PCQNG_E_GENERAL_FAILURE			_HRESULT_TYPEDEF_(0x80044501L)

//
// MessageId: PCQNG_E_IO_ARRAY_OVERSIZED
//
// MessageText:
//
//  PCQNG read array size exceeds 8192 bytes.
//
#define PCQNG_E_IO_ARRAY_OVERSIZED		_HRESULT_TYPEDEF_(0x80044504L)

//
// MessageId: PCQNG_E_DEVICE_UNAVAILABLE
//
// MessageText:
//
//  PCQNG unavailable or already in use.
//
#define PCQNG_E_DEVICE_UNAVAILABLE		_HRESULT_TYPEDEF_(0x8004450AL)

//
// MessageId: PCQNG_E_DEVICE_NOT_OPEN
//
// MessageText:
//
//  PCQNG device has not been opened yet.
//
#define PCQNG_E_DEVICE_NOT_OPEN			_HRESULT_TYPEDEF_(0x8004450BL)

//
// MessageId: PCQNG_E_INVALID_SYSTEM
//
// MessageText:
//
//  PCQNG incompatible with system.
//
#define PCQNG_E_INVALID_SYSTEM			_HRESULT_TYPEDEF_(0x8004450DL)

//
// MessageId: PCQNG_E_INVALID_MODE
//
// MessageText:
//
//  PCQNG incompatible mode.
//
#define PCQNG_E_INVALID_MODE			_HRESULT_TYPEDEF_(0x80044511L)


using namespace ATL;