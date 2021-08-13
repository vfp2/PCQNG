//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2001-2003 The Quantum World Corporation. All rights reserved.
//

// Version History:
// 2003.07.01    PAW    Creation

#include "StdAfx.h"
#include "dummydevice.h"

CDummyDevice::CDummyDevice(void)
: pBuffer(NULL)
, Mode(1.)
{
	// Create a buffer (BuffLength+12 bytes for rollover)
	pBuffer = new char[BuffLength+12];

	// Fill buffer with "0123456789012345..." hex
	int PNTER = 0;
	while (PNTER<BuffLength)
	{
		for (BYTE i=0; i<5; i++)
		{
			pBuffer[PNTER] = ((i*2)<<4) || ((i*2+1));
		}
		PNTER += 10;
	}
}

CDummyDevice::~CDummyDevice(void)
{
	// Release buffer from mem
	if (pBuffer != NULL)
	{
		delete pBuffer;
		pBuffer = NULL;
	}
}

// Null Function
HRESULT CDummyDevice::Open(void)
{
	return PCQNG_S_OK;
}

// Null function
HRESULT CDummyDevice::Close(void)
{
	return PCQNG_S_OK;
}

// Null function
HRESULT CDummyDevice::ClearAll(void)
{
	return PCQNG_S_OK;
}

// Null function
HRESULT CDummyDevice::Reset(void)
{
	return PCQNG_S_OK;
}

// Returns "01234567890123..." (hex)
HRESULT CDummyDevice::GetBytes(void* pOutBuffer, unsigned long Length)
{
	memcpy(pOutBuffer, pBuffer, Length);
	return PCQNG_S_OK;
}

// Returns "123456789"
HRESULT CDummyDevice::GetInt32(long* pInt32)
{
	*pInt32 = 123456789;
	return PCQNG_S_OK;
}

// Returns "0.123456789"
HRESULT CDummyDevice::GetUniform(double* pUniform)
{
	*pUniform = 0.123456789;
	return PCQNG_S_OK;
}

// Returns "1.23456789"
HRESULT CDummyDevice::GetNormal(double* pNormal)
{
	*pNormal = 1.23456789;
	return PCQNG_S_OK;
}

// Sets dummy mode
HRESULT CDummyDevice::SetMode(float ModeRequest)
{
	Mode = ModeRequest;
	return PCQNG_S_OK;
}

// Gets dummy mode
HRESULT CDummyDevice::GetMode(float* pMode)
{
	memcpy(pMode, &Mode, 4);
	return PCQNG_S_OK;
}