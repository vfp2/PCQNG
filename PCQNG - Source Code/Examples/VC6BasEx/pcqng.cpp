// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "pcqng.h"

/////////////////////////////////////////////////////////////////////////////
// CPCQNG

IMPLEMENT_DYNCREATE(CPCQNG, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CPCQNG properties

/////////////////////////////////////////////////////////////////////////////
// CPCQNG operations

void CPCQNG::Open()
{
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CPCQNG::Close()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

float CPCQNG::GetMode()
{
	float result;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

void CPCQNG::SetMode(float Mode)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Mode);
}

void CPCQNG::Clear()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CPCQNG::Reset()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CPCQNG::GetRandInt32()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

double CPCQNG::GetRandUniform()
{
	double result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

double CPCQNG::GetRandNormal()
{
	double result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

VARIANT CPCQNG::GetRandBytes(long Length)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Length);
	return result;
}