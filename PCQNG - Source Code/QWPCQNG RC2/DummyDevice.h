//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2001-2003 The Quantum World Corporation. All rights reserved.
//

// Version History:
// 2003.07.01    PAW    Creation

#pragma once
#include "device.h"

// Length of buffer 10K
#define BuffLength 10240

class CDummyDevice :
	public CDevice
{
public:
	CDummyDevice(void);
	virtual ~CDummyDevice(void);

	// Null Function
	virtual HRESULT Open(void);
	// Null function
	virtual HRESULT Close(void);
	// Null function
	virtual HRESULT ClearAll(void);
	// Null function
	virtual HRESULT Reset(void);

	// Returns "123456789"
	virtual HRESULT GetInt32(long* pInt32);
	// Returns "0.123456789"
	virtual HRESULT GetUniform(double* pUniform);
	// Returns "1.23456789"
	virtual HRESULT GetNormal(double* pNormal);
	// Returns "01234567890123..." (hex)
	virtual HRESULT GetBytes(void* pOutBuffer, unsigned long Length);

	// Sets dummy mode
	virtual HRESULT SetMode(float ModeRequest);
	// Returns dummy mode value
	virtual HRESULT GetMode(float* pMode);

protected:
	// Buffer for block operations.
	char* pBuffer;
	// Mode
	float Mode;
};