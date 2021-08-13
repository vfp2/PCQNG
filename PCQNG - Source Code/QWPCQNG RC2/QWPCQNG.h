

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue Feb 17 13:49:17 2004
 */
/* Compiler settings for .\QWPCQNG.idl:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __QWPCQNG_h__
#define __QWPCQNG_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPCQNG_FWD_DEFINED__
#define __IPCQNG_FWD_DEFINED__
typedef interface IPCQNG IPCQNG;
#endif 	/* __IPCQNG_FWD_DEFINED__ */


#ifndef ___IPCQNGEvents_FWD_DEFINED__
#define ___IPCQNGEvents_FWD_DEFINED__
typedef interface _IPCQNGEvents _IPCQNGEvents;
#endif 	/* ___IPCQNGEvents_FWD_DEFINED__ */


#ifndef __PCQNG_FWD_DEFINED__
#define __PCQNG_FWD_DEFINED__

#ifdef __cplusplus
typedef class PCQNG PCQNG;
#else
typedef struct PCQNG PCQNG;
#endif /* __cplusplus */

#endif 	/* __PCQNG_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IPCQNG_INTERFACE_DEFINED__
#define __IPCQNG_INTERFACE_DEFINED__

/* interface IPCQNG */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPCQNG;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C59FF083-E24E-4ACE-A04A-CA51BE626DFE")
    IPCQNG : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMode( 
            /* [retval][out] */ FLOAT *Mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMode( 
            /* [in] */ FLOAT Mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RandInt32( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RandUniform( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RandNormal( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RandBytes( 
            /* [in] */ LONG Length,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPCQNGVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPCQNG * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPCQNG * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPCQNG * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPCQNG * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPCQNG * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPCQNG * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPCQNG * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IPCQNG * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IPCQNG * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMode )( 
            IPCQNG * This,
            /* [retval][out] */ FLOAT *Mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMode )( 
            IPCQNG * This,
            /* [in] */ FLOAT Mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IPCQNG * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IPCQNG * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RandInt32 )( 
            IPCQNG * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RandUniform )( 
            IPCQNG * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RandNormal )( 
            IPCQNG * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RandBytes )( 
            IPCQNG * This,
            /* [in] */ LONG Length,
            /* [retval][out] */ VARIANT *pVal);
        
        END_INTERFACE
    } IPCQNGVtbl;

    interface IPCQNG
    {
        CONST_VTBL struct IPCQNGVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPCQNG_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPCQNG_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPCQNG_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPCQNG_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPCQNG_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPCQNG_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPCQNG_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPCQNG_Open(This)	\
    (This)->lpVtbl -> Open(This)

#define IPCQNG_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IPCQNG_GetMode(This,Mode)	\
    (This)->lpVtbl -> GetMode(This,Mode)

#define IPCQNG_SetMode(This,Mode)	\
    (This)->lpVtbl -> SetMode(This,Mode)

#define IPCQNG_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IPCQNG_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IPCQNG_get_RandInt32(This,pVal)	\
    (This)->lpVtbl -> get_RandInt32(This,pVal)

#define IPCQNG_get_RandUniform(This,pVal)	\
    (This)->lpVtbl -> get_RandUniform(This,pVal)

#define IPCQNG_get_RandNormal(This,pVal)	\
    (This)->lpVtbl -> get_RandNormal(This,pVal)

#define IPCQNG_get_RandBytes(This,Length,pVal)	\
    (This)->lpVtbl -> get_RandBytes(This,Length,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPCQNG_Open_Proxy( 
    IPCQNG * This);


void __RPC_STUB IPCQNG_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPCQNG_Close_Proxy( 
    IPCQNG * This);


void __RPC_STUB IPCQNG_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPCQNG_GetMode_Proxy( 
    IPCQNG * This,
    /* [retval][out] */ FLOAT *Mode);


void __RPC_STUB IPCQNG_GetMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPCQNG_SetMode_Proxy( 
    IPCQNG * This,
    /* [in] */ FLOAT Mode);


void __RPC_STUB IPCQNG_SetMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPCQNG_Clear_Proxy( 
    IPCQNG * This);


void __RPC_STUB IPCQNG_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPCQNG_Reset_Proxy( 
    IPCQNG * This);


void __RPC_STUB IPCQNG_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPCQNG_get_RandInt32_Proxy( 
    IPCQNG * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IPCQNG_get_RandInt32_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPCQNG_get_RandUniform_Proxy( 
    IPCQNG * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IPCQNG_get_RandUniform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPCQNG_get_RandNormal_Proxy( 
    IPCQNG * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IPCQNG_get_RandNormal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPCQNG_get_RandBytes_Proxy( 
    IPCQNG * This,
    /* [in] */ LONG Length,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IPCQNG_get_RandBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPCQNG_INTERFACE_DEFINED__ */



#ifndef __QWPCQNGLib_LIBRARY_DEFINED__
#define __QWPCQNGLib_LIBRARY_DEFINED__

/* library QWPCQNGLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_QWPCQNGLib;

#ifndef ___IPCQNGEvents_DISPINTERFACE_DEFINED__
#define ___IPCQNGEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IPCQNGEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IPCQNGEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("695C3DAA-4ADE-4AA7-90AA-53521E6DF42E")
    _IPCQNGEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IPCQNGEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IPCQNGEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IPCQNGEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IPCQNGEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IPCQNGEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IPCQNGEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IPCQNGEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IPCQNGEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IPCQNGEventsVtbl;

    interface _IPCQNGEvents
    {
        CONST_VTBL struct _IPCQNGEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IPCQNGEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IPCQNGEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IPCQNGEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IPCQNGEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IPCQNGEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IPCQNGEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IPCQNGEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IPCQNGEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PCQNG;

#ifdef __cplusplus

class DECLSPEC_UUID("59DA5E62-69A4-4505-A9D0-CAEE53C49E07")
PCQNG;
#endif
#endif /* __QWPCQNGLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


