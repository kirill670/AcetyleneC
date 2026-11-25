/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jun 13 22:42:14 2003
 */
/* Compiler settings for G:\Symbian_Connect\mRouterClients\mRouterSocket\mRouterSocket.idl:
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

#ifndef __mRouterSocket_h__
#define __mRouterSocket_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ImRouterSock_FWD_DEFINED__
#define __ImRouterSock_FWD_DEFINED__
typedef interface ImRouterSock ImRouterSock;
#endif 	/* __ImRouterSock_FWD_DEFINED__ */


#ifndef __mRouterSock_FWD_DEFINED__
#define __mRouterSock_FWD_DEFINED__

#ifdef __cplusplus
typedef class mRouterSock mRouterSock;
#else
typedef struct mRouterSock mRouterSock;
#endif /* __cplusplus */

#endif 	/* __mRouterSock_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_mRouterSocket_0000 */
/* [local] */ 

typedef 
enum tagMROUTER_CONNECTIONSTATUS
    {	MROUTER_CONNECTED	= 0,
	MROUTER_DISCONNECTED	= MROUTER_CONNECTED + 1
    }	MROUTER_CONNECTIONSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_mRouterSocket_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mRouterSocket_0000_v0_0_s_ifspec;

#ifndef __ImRouterSock_INTERFACE_DEFINED__
#define __ImRouterSock_INTERFACE_DEFINED__

/* interface ImRouterSock */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ImRouterSock;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC0001E0-CEE5-11D2-A953-00105A46D6E4")
    ImRouterSock : public ISequentialStream
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ LPCTSTR pszDevice,
            /* [in] */ LPCTSTR pszService) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Cancel( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCallback( 
            /* [in] */ IBindStatusCallback __RPC_FAR *pBSC) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RawWrite( 
            /* [in] */ const unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RawRead( 
            /* [out] */ unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetConnectionStatus( 
            /* [out] */ MROUTER_CONNECTIONSTATUS __RPC_FAR *csStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ImRouterSockVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ImRouterSock __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ImRouterSock __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ImRouterSock __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            ImRouterSock __RPC_FAR * This,
            /* [length_is][size_is][out] */ void __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            ImRouterSock __RPC_FAR * This,
            /* [size_is][in] */ const void __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            ImRouterSock __RPC_FAR * This,
            /* [in] */ LPCTSTR pszDevice,
            /* [in] */ LPCTSTR pszService);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Cancel )( 
            ImRouterSock __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCallback )( 
            ImRouterSock __RPC_FAR * This,
            /* [in] */ IBindStatusCallback __RPC_FAR *pBSC);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RawWrite )( 
            ImRouterSock __RPC_FAR * This,
            /* [in] */ const unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RawRead )( 
            ImRouterSock __RPC_FAR * This,
            /* [out] */ unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConnectionStatus )( 
            ImRouterSock __RPC_FAR * This,
            /* [out] */ MROUTER_CONNECTIONSTATUS __RPC_FAR *csStatus);
        
        END_INTERFACE
    } ImRouterSockVtbl;

    interface ImRouterSock
    {
        CONST_VTBL struct ImRouterSockVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ImRouterSock_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ImRouterSock_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ImRouterSock_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ImRouterSock_Read(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> Read(This,pv,cb,pcbRead)

#define ImRouterSock_Write(This,pv,cb,pcbWritten)	\
    (This)->lpVtbl -> Write(This,pv,cb,pcbWritten)


#define ImRouterSock_Init(This,pszDevice,pszService)	\
    (This)->lpVtbl -> Init(This,pszDevice,pszService)

#define ImRouterSock_Cancel(This)	\
    (This)->lpVtbl -> Cancel(This)

#define ImRouterSock_SetCallback(This,pBSC)	\
    (This)->lpVtbl -> SetCallback(This,pBSC)

#define ImRouterSock_RawWrite(This,pv,cb,pcbWritten)	\
    (This)->lpVtbl -> RawWrite(This,pv,cb,pcbWritten)

#define ImRouterSock_RawRead(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> RawRead(This,pv,cb,pcbRead)

#define ImRouterSock_GetConnectionStatus(This,csStatus)	\
    (This)->lpVtbl -> GetConnectionStatus(This,csStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ImRouterSock_Init_Proxy( 
    ImRouterSock __RPC_FAR * This,
    /* [in] */ LPCTSTR pszDevice,
    /* [in] */ LPCTSTR pszService);


void __RPC_STUB ImRouterSock_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ImRouterSock_Cancel_Proxy( 
    ImRouterSock __RPC_FAR * This);


void __RPC_STUB ImRouterSock_Cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ImRouterSock_SetCallback_Proxy( 
    ImRouterSock __RPC_FAR * This,
    /* [in] */ IBindStatusCallback __RPC_FAR *pBSC);


void __RPC_STUB ImRouterSock_SetCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ImRouterSock_RawWrite_Proxy( 
    ImRouterSock __RPC_FAR * This,
    /* [in] */ const unsigned char __RPC_FAR *pv,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbWritten);


void __RPC_STUB ImRouterSock_RawWrite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ImRouterSock_RawRead_Proxy( 
    ImRouterSock __RPC_FAR * This,
    /* [out] */ unsigned char __RPC_FAR *pv,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbRead);


void __RPC_STUB ImRouterSock_RawRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ImRouterSock_GetConnectionStatus_Proxy( 
    ImRouterSock __RPC_FAR * This,
    /* [out] */ MROUTER_CONNECTIONSTATUS __RPC_FAR *csStatus);


void __RPC_STUB ImRouterSock_GetConnectionStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ImRouterSock_INTERFACE_DEFINED__ */



#ifndef __MROUTERSOCKETLib_LIBRARY_DEFINED__
#define __MROUTERSOCKETLib_LIBRARY_DEFINED__

/* library MROUTERSOCKETLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MROUTERSOCKETLib;

EXTERN_C const CLSID CLSID_mRouterSock;

#ifdef __cplusplus

class DECLSPEC_UUID("EC1001E0-CEE5-11D2-A953-00105A46D6E4")
mRouterSock;
#endif
#endif /* __MROUTERSOCKETLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
