//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2001-2003 The Quantum World Corporation. All rights reserved.
//

// Version History:
// 2003.07.01    PAW    Creation

// PCQNG.h : Declaration of the CPCQNG
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "QWPCQNG.h"
#include "Device.h"
#include "DummyDevice.h"
#include "_IPCQNGEvents_CP.h"
#include "CDlgThanks.h"
#include "Security.h"

// CPCQNG
class ATL_NO_VTABLE CPCQNG : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IPCQNG, &IID_IPCQNG, &LIBID_QWPCQNGLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistStreamInitImpl<CPCQNG>,
	public IOleControlImpl<CPCQNG>,
	public IOleObjectImpl<CPCQNG>,
	public IOleInPlaceActiveObjectImpl<CPCQNG>,
	public IViewObjectExImpl<CPCQNG>,
	public IOleInPlaceObjectWindowlessImpl<CPCQNG>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPCQNG>,
	public CProxy_IPCQNGEvents<CPCQNG>, 
	public IObjectWithSiteImpl<CPCQNG>,
	public IServiceProviderImpl<CPCQNG>,
	public IPersistStorageImpl<CPCQNG>,
	public ISpecifyPropertyPagesImpl<CPCQNG>,
	public IQuickActivateImpl<CPCQNG>,
	public IProvideClassInfo2Impl<&CLSID_PCQNG, &__uuidof(_IPCQNGEvents), &LIBID_QWPCQNGLib>,
	public IPropertyNotifySinkCP<CPCQNG>,
	public CComCoClass<CPCQNG, &CLSID_PCQNG>,
	public CComControl<CPCQNG>
{
public:

	CPCQNG()
	{
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE | 
	OLEMISC_INVISIBLEATRUNTIME |
	OLEMISC_CANTLINKINSIDE | 
	OLEMISC_INSIDEOUT | 
	OLEMISC_ACTIVATEWHENVISIBLE | 
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_PCQNG)

BEGIN_COM_MAP(CPCQNG)
	COM_INTERFACE_ENTRY(IPCQNG)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IServiceProvider)
END_COM_MAP()

BEGIN_PROP_MAP(CPCQNG)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CPCQNG)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(__uuidof(_IPCQNGEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CPCQNG)
	CHAIN_MSG_MAP(CComControl<CPCQNG>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IPCQNG,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(0)

// IPCQNG
public:
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		// draws an icon at design time
		static HICON hIcon = NULL;
		RECT& rc = *(RECT*)di.prcBounds;
		if( NULL == hIcon ) hIcon = LoadIcon(_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(IDI_PCQNG));
		DrawIcon(di.hdcDraw,rc.left,rc.top,hIcon);

		return S_OK;
	}

	STDMETHOD(_InternalQueryService)(REFGUID guidService, REFIID riid, void** ppvObject)
	{
		return E_NOTIMPL;
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		// force size of design time icon
		m_bAutoSize = TRUE;		// no resize
		SIZEL size = {32,32};	// pixel size
		AtlPixelToHiMetric(&size, &m_sizeExtent);
		m_sizeNatural = m_sizeExtent;

		// pDevice = NULL, for clean destruction
		pDevice = NULL;

		return S_OK;
	}
	
	void FinalRelease() 
	{
		if (pDevice!=NULL)
		{
			pDevice->Close();
			delete pDevice;
			pDevice = NULL;
		}
	}

	

protected:
	// PCQNG device
	CDevice* pDevice;

	// Generates custom error message
	inline HRESULT RetResult(HRESULT DevResult);

	// Provides licensing
	CCDlgThanks DlgThanks;
	CSecurity Security;

public:
	STDMETHOD(Open)(void);
	STDMETHOD(Close)(void);
	STDMETHOD(GetMode)(FLOAT* Mode);
	STDMETHOD(SetMode)(FLOAT Mode);
	STDMETHOD(Clear)(void);
	STDMETHOD(Reset)(void);
	STDMETHOD(get_RandInt32)(LONG* pVal);
	STDMETHOD(get_RandUniform)(DOUBLE* pVal);
	STDMETHOD(get_RandNormal)(DOUBLE* pVal);
	STDMETHOD(get_RandBytes)(LONG Length, VARIANT* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(PCQNG), CPCQNG)
