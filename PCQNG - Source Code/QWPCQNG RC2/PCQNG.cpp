//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2001-2003 The Quantum World Corporation. All rights reserved.
//

// Version History:
// 2003.07.01    PAW    Creation

// PCQNG.cpp : Implementation of CPCQNG
#include "stdafx.h"
#include "PCQNG.h"

// CPCQNG

STDMETHODIMP CPCQNG::Open(void)
{
	if (pDevice==NULL)
	{
		BOOL bIsRunMode = TRUE;
		GetAmbientUserMode(bIsRunMode);

		if (bIsRunMode)
		{
			if (Security.CheckLicense())
            {
				DlgThanks.DoModal();
                if (DlgThanks.isCancelled == true)
                    return RetResult(PCQNG_E_DEVICE_NOT_OPEN);
                if (Security.CheckLicense())
                {
                    if (Security.CheckDate())
        			    pDevice = new CDevice; // Run mode, real device
                    else
                        pDevice = new CDummyDevice;
                }
                else
           			pDevice = new CDevice; // Run mode, real device
            }
            else
    			pDevice = new CDevice; // Run mode, real device
		}
		else
			pDevice = new CDummyDevice;	// Design mode, get dummy device
	}

	return RetResult(pDevice->Open());
}

STDMETHODIMP CPCQNG::Close(void)
{
	if (pDevice!=NULL)
	{
		pDevice->Close();
		delete pDevice;
		pDevice = NULL;
	}

	return S_OK;
}

STDMETHODIMP CPCQNG::GetMode(FLOAT* Mode)
{
	if (pDevice!=NULL)
		return RetResult(pDevice->GetMode(Mode));
	else
		return RetResult(PCQNG_E_DEVICE_NOT_OPEN);
}

STDMETHODIMP CPCQNG::SetMode(FLOAT Mode)
{
	if (pDevice!=NULL)
		return RetResult(pDevice->SetMode(Mode));
	else
		return RetResult(PCQNG_E_DEVICE_NOT_OPEN);
}

STDMETHODIMP CPCQNG::Clear(void)
{
	if (pDevice!=NULL)
		return RetResult(pDevice->ClearAll());
	else
		return RetResult(PCQNG_E_DEVICE_NOT_OPEN);
}

STDMETHODIMP CPCQNG::Reset(void)
{
	if (pDevice!=NULL)
		return RetResult(pDevice->Reset());
	else
		return RetResult(PCQNG_E_DEVICE_NOT_OPEN);
}

STDMETHODIMP CPCQNG::get_RandInt32(LONG* pVal)
{
	if (pDevice!=NULL)
		return RetResult(pDevice->GetInt32(pVal));
	else
		return RetResult(PCQNG_E_DEVICE_NOT_OPEN);
}

STDMETHODIMP CPCQNG::get_RandUniform(DOUBLE* pVal)
{
	if (pDevice!=NULL)
		return RetResult(pDevice->GetUniform(pVal));
	else
		return RetResult(PCQNG_E_DEVICE_NOT_OPEN);
}

STDMETHODIMP CPCQNG::get_RandNormal(DOUBLE* pVal)
{
	if (pDevice!=NULL)
		return RetResult(pDevice->GetNormal(pVal));
	else
		return RetResult(PCQNG_E_DEVICE_NOT_OPEN);
}

STDMETHODIMP CPCQNG::get_RandBytes(LONG Length, VARIANT* pVal)
{
	if (pDevice!=NULL)
	{
		// Check if valid Length <= 8192
		if (Length>8192)
			return RetResult(PCQNG_E_IO_ARRAY_OVERSIZED);

		// Initialize variant as an array of unisigned char/byte
		VariantInit(pVal);
		pVal->vt = VT_ARRAY | VT_UI1;

		// Create the SAFEARRAY with Length elements and zero indexed
		SAFEARRAY* pSafeArray;
		SAFEARRAYBOUND SABounds = {Length, 0};
		pSafeArray = SafeArrayCreate(VT_I1, 1, &SABounds);

		// Fill safe array with data
		unsigned char* charArray;
		SafeArrayAccessData(pSafeArray, reinterpret_cast<void**>(&charArray));
			HRESULT DevResult = pDevice->GetBytes(charArray, Length);
		SafeArrayUnaccessData(pSafeArray);

		// Return array to user
		pVal->parray = pSafeArray;

		return RetResult(DevResult);
	}
	else
		return RetResult(PCQNG_E_DEVICE_NOT_OPEN);
}

// Generates custom error message
HRESULT CPCQNG::RetResult(HRESULT DevResult)
{
	switch (DevResult)
	{
	case PCQNG_S_OK:
		return S_OK;
		break;

	case PCQNG_E_IO_ARRAY_OVERSIZED:
		return Error(_T("PCQNG read array size exceeds 8192 bytes."), IID_IPCQNG, PCQNG_E_IO_ARRAY_OVERSIZED);
		break;

	case PCQNG_E_DEVICE_UNAVAILABLE:
		return Error(_T("PCQNG unavailable or already in use."), IID_IPCQNG, PCQNG_E_DEVICE_UNAVAILABLE);
		break;

	case PCQNG_E_DEVICE_NOT_OPEN:
		return Error(_T("PCQNG device has not been opened yet."), IID_IPCQNG, PCQNG_E_DEVICE_NOT_OPEN);
		break;

	case PCQNG_E_INVALID_SYSTEM:
		return Error(_T("PCQNG incompatible with system."), IID_IPCQNG, PCQNG_E_INVALID_SYSTEM);
		break;

	case PCQNG_E_INVALID_MODE:
		return Error(_T("PCQNG incompatible mode."), IID_IPCQNG, PCQNG_E_INVALID_MODE);

	default:
		return Error(_T("PCQNG general error."), IID_IPCQNG, PCQNG_E_GENERAL_FAILURE);
	}
}
