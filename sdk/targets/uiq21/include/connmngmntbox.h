/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 27 11:57:44 2002
 */
/* Compiler settings for G:\symbian_connect\mRouterClients\ConnMngmnt\ConnMngmntBox\ConnMngmntBox.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


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

#ifndef __ConnMngmntBox_h__
#define __ConnMngmntBox_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IConnMngmnt_FWD_DEFINED__
#define __IConnMngmnt_FWD_DEFINED__
typedef interface IConnMngmnt IConnMngmnt;
#endif 	/* __IConnMngmnt_FWD_DEFINED__ */


#ifndef __ConnMngmnt_FWD_DEFINED__
#define __ConnMngmnt_FWD_DEFINED__

#ifdef __cplusplus
typedef class ConnMngmnt ConnMngmnt;
#else
typedef struct ConnMngmnt ConnMngmnt;
#endif /* __cplusplus */

#endif 	/* __ConnMngmnt_FWD_DEFINED__ */


#ifndef __IConnMngmntClientSink_FWD_DEFINED__
#define __IConnMngmntClientSink_FWD_DEFINED__
typedef interface IConnMngmntClientSink IConnMngmntClientSink;
#endif 	/* __IConnMngmntClientSink_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IConnMngmnt_INTERFACE_DEFINED__
#define __IConnMngmnt_INTERFACE_DEFINED__

/* interface IConnMngmnt */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IConnMngmnt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC000180-CEE5-11D2-A953-00105A46D6E4")
    IConnMngmnt : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisplayConnectionsScreen( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisplayDeviceDisconnectedScreen( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisplayChangeDeviceScreenModal( 
            /* [out] */ BSTR __RPC_FAR *bstrConnectedID,
            /* [in] */ BSTR bstrCurrentID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSelection( 
            /* [out] */ BSTR __RPC_FAR *bstrConnectedID,
            /* [out] */ BSTR __RPC_FAR *bstrUID,
            /* [out] */ VARIANT_BOOL __RPC_FAR *bOnline,
            /* [out] */ VARIANT_BOOL __RPC_FAR *bKnown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSelection( 
            /* [in] */ BSTR bstrConnectedID,
            /* [in] */ BSTR bstrUID,
            /* [in] */ VARIANT_BOOL bOnline,
            /* [in] */ VARIANT_BOOL bKnown) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDefaultDevice( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Advise( 
            ULONG __RPC_FAR *ulClientID,
            IDispatch __RPC_FAR *pCallback) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnAdvise( 
            ULONG ulClientID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HideDeviceDisconnectedScreen( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConnMngmntVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IConnMngmnt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IConnMngmnt __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IConnMngmnt __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IConnMngmnt __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IConnMngmnt __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IConnMngmnt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IConnMngmnt __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisplayConnectionsScreen )( 
            IConnMngmnt __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisplayDeviceDisconnectedScreen )( 
            IConnMngmnt __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisplayChangeDeviceScreenModal )( 
            IConnMngmnt __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *bstrConnectedID,
            /* [in] */ BSTR bstrCurrentID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSelection )( 
            IConnMngmnt __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *bstrConnectedID,
            /* [out] */ BSTR __RPC_FAR *bstrUID,
            /* [out] */ VARIANT_BOOL __RPC_FAR *bOnline,
            /* [out] */ VARIANT_BOOL __RPC_FAR *bKnown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSelection )( 
            IConnMngmnt __RPC_FAR * This,
            /* [in] */ BSTR bstrConnectedID,
            /* [in] */ BSTR bstrUID,
            /* [in] */ VARIANT_BOOL bOnline,
            /* [in] */ VARIANT_BOOL bKnown);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDefaultDevice )( 
            IConnMngmnt __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Advise )( 
            IConnMngmnt __RPC_FAR * This,
            ULONG __RPC_FAR *ulClientID,
            IDispatch __RPC_FAR *pCallback);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnAdvise )( 
            IConnMngmnt __RPC_FAR * This,
            ULONG ulClientID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HideDeviceDisconnectedScreen )( 
            IConnMngmnt __RPC_FAR * This);
        
        END_INTERFACE
    } IConnMngmntVtbl;

    interface IConnMngmnt
    {
        CONST_VTBL struct IConnMngmntVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConnMngmnt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConnMngmnt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConnMngmnt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConnMngmnt_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IConnMngmnt_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IConnMngmnt_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IConnMngmnt_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IConnMngmnt_DisplayConnectionsScreen(This)	\
    (This)->lpVtbl -> DisplayConnectionsScreen(This)

#define IConnMngmnt_DisplayDeviceDisconnectedScreen(This)	\
    (This)->lpVtbl -> DisplayDeviceDisconnectedScreen(This)

#define IConnMngmnt_DisplayChangeDeviceScreenModal(This,bstrConnectedID,bstrCurrentID)	\
    (This)->lpVtbl -> DisplayChangeDeviceScreenModal(This,bstrConnectedID,bstrCurrentID)

#define IConnMngmnt_GetSelection(This,bstrConnectedID,bstrUID,bOnline,bKnown)	\
    (This)->lpVtbl -> GetSelection(This,bstrConnectedID,bstrUID,bOnline,bKnown)

#define IConnMngmnt_SetSelection(This,bstrConnectedID,bstrUID,bOnline,bKnown)	\
    (This)->lpVtbl -> SetSelection(This,bstrConnectedID,bstrUID,bOnline,bKnown)

#define IConnMngmnt_SetDefaultDevice(This)	\
    (This)->lpVtbl -> SetDefaultDevice(This)

#define IConnMngmnt_Advise(This,ulClientID,pCallback)	\
    (This)->lpVtbl -> Advise(This,ulClientID,pCallback)

#define IConnMngmnt_UnAdvise(This,ulClientID)	\
    (This)->lpVtbl -> UnAdvise(This,ulClientID)

#define IConnMngmnt_HideDeviceDisconnectedScreen(This)	\
    (This)->lpVtbl -> HideDeviceDisconnectedScreen(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConnMngmnt_DisplayConnectionsScreen_Proxy( 
    IConnMngmnt __RPC_FAR * This);


void __RPC_STUB IConnMngmnt_DisplayConnectionsScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConnMngmnt_DisplayDeviceDisconnectedScreen_Proxy( 
    IConnMngmnt __RPC_FAR * This);


void __RPC_STUB IConnMngmnt_DisplayDeviceDisconnectedScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConnMngmnt_DisplayChangeDeviceScreenModal_Proxy( 
    IConnMngmnt __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *bstrConnectedID,
    /* [in] */ BSTR bstrCurrentID);


void __RPC_STUB IConnMngmnt_DisplayChangeDeviceScreenModal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConnMngmnt_GetSelection_Proxy( 
    IConnMngmnt __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *bstrConnectedID,
    /* [out] */ BSTR __RPC_FAR *bstrUID,
    /* [out] */ VARIANT_BOOL __RPC_FAR *bOnline,
    /* [out] */ VARIANT_BOOL __RPC_FAR *bKnown);


void __RPC_STUB IConnMngmnt_GetSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConnMngmnt_SetSelection_Proxy( 
    IConnMngmnt __RPC_FAR * This,
    /* [in] */ BSTR bstrConnectedID,
    /* [in] */ BSTR bstrUID,
    /* [in] */ VARIANT_BOOL bOnline,
    /* [in] */ VARIANT_BOOL bKnown);


void __RPC_STUB IConnMngmnt_SetSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConnMngmnt_SetDefaultDevice_Proxy( 
    IConnMngmnt __RPC_FAR * This);


void __RPC_STUB IConnMngmnt_SetDefaultDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConnMngmnt_Advise_Proxy( 
    IConnMngmnt __RPC_FAR * This,
    ULONG __RPC_FAR *ulClientID,
    IDispatch __RPC_FAR *pCallback);


void __RPC_STUB IConnMngmnt_Advise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConnMngmnt_UnAdvise_Proxy( 
    IConnMngmnt __RPC_FAR * This,
    ULONG ulClientID);


void __RPC_STUB IConnMngmnt_UnAdvise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConnMngmnt_HideDeviceDisconnectedScreen_Proxy( 
    IConnMngmnt __RPC_FAR * This);


void __RPC_STUB IConnMngmnt_HideDeviceDisconnectedScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConnMngmnt_INTERFACE_DEFINED__ */



#ifndef __CONNMNGMNTBOXLib_LIBRARY_DEFINED__
#define __CONNMNGMNTBOXLib_LIBRARY_DEFINED__

/* library CONNMNGMNTBOXLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CONNMNGMNTBOXLib;

EXTERN_C const CLSID CLSID_ConnMngmnt;

#ifdef __cplusplus

class DECLSPEC_UUID("EC100180-CEE5-11D2-A953-00105A46D6E4")
ConnMngmnt;
#endif

#ifndef __IConnMngmntClientSink_INTERFACE_DEFINED__
#define __IConnMngmntClientSink_INTERFACE_DEFINED__

/* interface IConnMngmntClientSink */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IConnMngmntClientSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC000182-CEE5-11D2-A953-00105A46D6E4")
    IConnMngmntClientSink : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnDismissChangeDeviceDialog( 
            /* [in] */ VARIANT_BOOL bResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConnMngmntClientSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IConnMngmntClientSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IConnMngmntClientSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IConnMngmntClientSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IConnMngmntClientSink __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IConnMngmntClientSink __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IConnMngmntClientSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IConnMngmntClientSink __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDismissChangeDeviceDialog )( 
            IConnMngmntClientSink __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bResult);
        
        END_INTERFACE
    } IConnMngmntClientSinkVtbl;

    interface IConnMngmntClientSink
    {
        CONST_VTBL struct IConnMngmntClientSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConnMngmntClientSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConnMngmntClientSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConnMngmntClientSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConnMngmntClientSink_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IConnMngmntClientSink_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IConnMngmntClientSink_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IConnMngmntClientSink_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IConnMngmntClientSink_OnDismissChangeDeviceDialog(This,bResult)	\
    (This)->lpVtbl -> OnDismissChangeDeviceDialog(This,bResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConnMngmntClientSink_OnDismissChangeDeviceDialog_Proxy( 
    IConnMngmntClientSink __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bResult);


void __RPC_STUB IConnMngmntClientSink_OnDismissChangeDeviceDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConnMngmntClientSink_INTERFACE_DEFINED__ */

#endif /* __CONNMNGMNTBOXLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
