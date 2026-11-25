/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jun 13 22:41:16 2003
 */
/* Compiler settings for G:\Symbian_Connect\mRouterClients\rtsock\RtSock.idl:
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

#ifndef __RtSock_h__
#define __RtSock_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ImConnectionStatusCallback_FWD_DEFINED__
#define __ImConnectionStatusCallback_FWD_DEFINED__
typedef interface ImConnectionStatusCallback ImConnectionStatusCallback;
#endif 	/* __ImConnectionStatusCallback_FWD_DEFINED__ */


#ifndef __ImRouterSocket_FWD_DEFINED__
#define __ImRouterSocket_FWD_DEFINED__
typedef interface ImRouterSocket ImRouterSocket;
#endif 	/* __ImRouterSocket_FWD_DEFINED__ */


#ifndef __ImRouterSimpleTransport_FWD_DEFINED__
#define __ImRouterSimpleTransport_FWD_DEFINED__
typedef interface ImRouterSimpleTransport ImRouterSimpleTransport;
#endif 	/* __ImRouterSimpleTransport_FWD_DEFINED__ */


#ifndef __RouterSimpleTransport_FWD_DEFINED__
#define __RouterSimpleTransport_FWD_DEFINED__

#ifdef __cplusplus
typedef class RouterSimpleTransport RouterSimpleTransport;
#else
typedef struct RouterSimpleTransport RouterSimpleTransport;
#endif /* __cplusplus */

#endif 	/* __RouterSimpleTransport_FWD_DEFINED__ */


#ifndef __RouterSocket_FWD_DEFINED__
#define __RouterSocket_FWD_DEFINED__

#ifdef __cplusplus
typedef class RouterSocket RouterSocket;
#else
typedef struct RouterSocket RouterSocket;
#endif /* __cplusplus */

#endif 	/* __RouterSocket_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_RtSock_0000 */
/* [local] */ 

typedef 
enum tagIM_CONNECTIONSTATUS
    {	IM_CONNECTIONSTATUS_CONNECTING	= 0,
	IM_CONNECTIONSTATUS_CONNECTED	= IM_CONNECTIONSTATUS_CONNECTING + 1,
	IM_CONNECTIONSTATUS_DISCONNECTING	= IM_CONNECTIONSTATUS_CONNECTED + 1,
	IM_CONNECTIONSTATUS_DISCONNECTED	= IM_CONNECTIONSTATUS_DISCONNECTING + 1,
	IM_CONNECTIONSTATUS_UNKNOWN	= IM_CONNECTIONSTATUS_DISCONNECTED + 1
    }	IM_CONNECTIONSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_RtSock_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_RtSock_0000_v0_0_s_ifspec;

#ifndef __ImConnectionStatusCallback_INTERFACE_DEFINED__
#define __ImConnectionStatusCallback_INTERFACE_DEFINED__

/* interface ImConnectionStatusCallback */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ImConnectionStatusCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC000150-CEE5-11D2-A953-00105A46D6E4")
    ImConnectionStatusCallback : public ISequentialStream
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnStatusChange( 
            IM_CONNECTIONSTATUS __MIDL_0015) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ImConnectionStatusCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ImConnectionStatusCallback __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ImConnectionStatusCallback __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ImConnectionStatusCallback __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            ImConnectionStatusCallback __RPC_FAR * This,
            /* [length_is][size_is][out] */ void __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            ImConnectionStatusCallback __RPC_FAR * This,
            /* [size_is][in] */ const void __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnStatusChange )( 
            ImConnectionStatusCallback __RPC_FAR * This,
            IM_CONNECTIONSTATUS __MIDL_0015);
        
        END_INTERFACE
    } ImConnectionStatusCallbackVtbl;

    interface ImConnectionStatusCallback
    {
        CONST_VTBL struct ImConnectionStatusCallbackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ImConnectionStatusCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ImConnectionStatusCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ImConnectionStatusCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ImConnectionStatusCallback_Read(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> Read(This,pv,cb,pcbRead)

#define ImConnectionStatusCallback_Write(This,pv,cb,pcbWritten)	\
    (This)->lpVtbl -> Write(This,pv,cb,pcbWritten)


#define ImConnectionStatusCallback_OnStatusChange(This,__MIDL_0015)	\
    (This)->lpVtbl -> OnStatusChange(This,__MIDL_0015)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ImConnectionStatusCallback_OnStatusChange_Proxy( 
    ImConnectionStatusCallback __RPC_FAR * This,
    IM_CONNECTIONSTATUS __MIDL_0015);


void __RPC_STUB ImConnectionStatusCallback_OnStatusChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ImConnectionStatusCallback_INTERFACE_DEFINED__ */


#ifndef __ImRouterSocket_INTERFACE_DEFINED__
#define __ImRouterSocket_INTERFACE_DEFINED__

/* interface ImRouterSocket */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ImRouterSocket;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC000151-CEE5-11D2-A953-00105A46D6E4")
    ImRouterSocket : public ISequentialStream
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Cancel( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCallback( 
            /* [in] */ IBindStatusCallback __RPC_FAR *pBSC) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ImRouterSocketVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ImRouterSocket __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ImRouterSocket __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ImRouterSocket __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            ImRouterSocket __RPC_FAR * This,
            /* [length_is][size_is][out] */ void __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            ImRouterSocket __RPC_FAR * This,
            /* [size_is][in] */ const void __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Cancel )( 
            ImRouterSocket __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCallback )( 
            ImRouterSocket __RPC_FAR * This,
            /* [in] */ IBindStatusCallback __RPC_FAR *pBSC);
        
        END_INTERFACE
    } ImRouterSocketVtbl;

    interface ImRouterSocket
    {
        CONST_VTBL struct ImRouterSocketVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ImRouterSocket_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ImRouterSocket_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ImRouterSocket_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ImRouterSocket_Read(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> Read(This,pv,cb,pcbRead)

#define ImRouterSocket_Write(This,pv,cb,pcbWritten)	\
    (This)->lpVtbl -> Write(This,pv,cb,pcbWritten)


#define ImRouterSocket_Cancel(This)	\
    (This)->lpVtbl -> Cancel(This)

#define ImRouterSocket_SetCallback(This,pBSC)	\
    (This)->lpVtbl -> SetCallback(This,pBSC)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ImRouterSocket_Cancel_Proxy( 
    ImRouterSocket __RPC_FAR * This);


void __RPC_STUB ImRouterSocket_Cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ImRouterSocket_SetCallback_Proxy( 
    ImRouterSocket __RPC_FAR * This,
    /* [in] */ IBindStatusCallback __RPC_FAR *pBSC);


void __RPC_STUB ImRouterSocket_SetCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ImRouterSocket_INTERFACE_DEFINED__ */


#ifndef __ImRouterSimpleTransport_INTERFACE_DEFINED__
#define __ImRouterSimpleTransport_INTERFACE_DEFINED__

/* interface ImRouterSimpleTransport */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ImRouterSimpleTransport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC000152-CEE5-11D2-A953-00105A46D6E4")
    ImRouterSimpleTransport : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetConnectionStatus( 
            /* [in] */ LPCTSTR pszDeviceType,
            /* [out] */ IM_CONNECTIONSTATUS __RPC_FAR *pCONNECTIONSTATUS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Connect( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OpenCustomServer( 
            /* [in] */ LPCTSTR pszDeviceType,
            /* [in] */ LPCOLESTR szServerName,
            /* [in] */ BYTE bMajor,
            /* [in] */ BYTE bMinor,
            /* [in] */ DWORD dwBuild,
            /* [out] */ ImRouterSocket __RPC_FAR *__RPC_FAR *ppCustomServer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCallback( 
            /* [in] */ ImConnectionStatusCallback __RPC_FAR *pCSC) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ImRouterSimpleTransportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ImRouterSimpleTransport __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ImRouterSimpleTransport __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ImRouterSimpleTransport __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConnectionStatus )( 
            ImRouterSimpleTransport __RPC_FAR * This,
            /* [in] */ LPCTSTR pszDeviceType,
            /* [out] */ IM_CONNECTIONSTATUS __RPC_FAR *pCONNECTIONSTATUS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            ImRouterSimpleTransport __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenCustomServer )( 
            ImRouterSimpleTransport __RPC_FAR * This,
            /* [in] */ LPCTSTR pszDeviceType,
            /* [in] */ LPCOLESTR szServerName,
            /* [in] */ BYTE bMajor,
            /* [in] */ BYTE bMinor,
            /* [in] */ DWORD dwBuild,
            /* [out] */ ImRouterSocket __RPC_FAR *__RPC_FAR *ppCustomServer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCallback )( 
            ImRouterSimpleTransport __RPC_FAR * This,
            /* [in] */ ImConnectionStatusCallback __RPC_FAR *pCSC);
        
        END_INTERFACE
    } ImRouterSimpleTransportVtbl;

    interface ImRouterSimpleTransport
    {
        CONST_VTBL struct ImRouterSimpleTransportVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ImRouterSimpleTransport_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ImRouterSimpleTransport_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ImRouterSimpleTransport_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ImRouterSimpleTransport_GetConnectionStatus(This,pszDeviceType,pCONNECTIONSTATUS)	\
    (This)->lpVtbl -> GetConnectionStatus(This,pszDeviceType,pCONNECTIONSTATUS)

#define ImRouterSimpleTransport_Connect(This)	\
    (This)->lpVtbl -> Connect(This)

#define ImRouterSimpleTransport_OpenCustomServer(This,pszDeviceType,szServerName,bMajor,bMinor,dwBuild,ppCustomServer)	\
    (This)->lpVtbl -> OpenCustomServer(This,pszDeviceType,szServerName,bMajor,bMinor,dwBuild,ppCustomServer)

#define ImRouterSimpleTransport_SetCallback(This,pCSC)	\
    (This)->lpVtbl -> SetCallback(This,pCSC)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ImRouterSimpleTransport_GetConnectionStatus_Proxy( 
    ImRouterSimpleTransport __RPC_FAR * This,
    /* [in] */ LPCTSTR pszDeviceType,
    /* [out] */ IM_CONNECTIONSTATUS __RPC_FAR *pCONNECTIONSTATUS);


void __RPC_STUB ImRouterSimpleTransport_GetConnectionStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ImRouterSimpleTransport_Connect_Proxy( 
    ImRouterSimpleTransport __RPC_FAR * This);


void __RPC_STUB ImRouterSimpleTransport_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ImRouterSimpleTransport_OpenCustomServer_Proxy( 
    ImRouterSimpleTransport __RPC_FAR * This,
    /* [in] */ LPCTSTR pszDeviceType,
    /* [in] */ LPCOLESTR szServerName,
    /* [in] */ BYTE bMajor,
    /* [in] */ BYTE bMinor,
    /* [in] */ DWORD dwBuild,
    /* [out] */ ImRouterSocket __RPC_FAR *__RPC_FAR *ppCustomServer);


void __RPC_STUB ImRouterSimpleTransport_OpenCustomServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ImRouterSimpleTransport_SetCallback_Proxy( 
    ImRouterSimpleTransport __RPC_FAR * This,
    /* [in] */ ImConnectionStatusCallback __RPC_FAR *pCSC);


void __RPC_STUB ImRouterSimpleTransport_SetCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ImRouterSimpleTransport_INTERFACE_DEFINED__ */



#ifndef __RTSOCKLib_LIBRARY_DEFINED__
#define __RTSOCKLib_LIBRARY_DEFINED__

/* library RTSOCKLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_RTSOCKLib;

EXTERN_C const CLSID CLSID_RouterSimpleTransport;

#ifdef __cplusplus

class DECLSPEC_UUID("EC100152-CEE5-11D2-A953-00105A46D6E4")
RouterSimpleTransport;
#endif

EXTERN_C const CLSID CLSID_RouterSocket;

#ifdef __cplusplus

class DECLSPEC_UUID("EC100151-CEE5-11D2-A953-00105A46D6E4")
RouterSocket;
#endif
#endif /* __RTSOCKLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
