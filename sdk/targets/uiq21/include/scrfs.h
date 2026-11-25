/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Aug 13 14:12:50 2002
 */
/* Compiler settings for scrfs.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation bounds_check stub_data 
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

#ifndef __scrfs_h__
#define __scrfs_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IRFS_FWD_DEFINED__
#define __IRFS_FWD_DEFINED__
typedef interface IRFS IRFS;
#endif 	/* __IRFS_FWD_DEFINED__ */


#ifndef __IRFSSink_FWD_DEFINED__
#define __IRFSSink_FWD_DEFINED__
typedef interface IRFSSink IRFSSink;
#endif 	/* __IRFSSink_FWD_DEFINED__ */


#ifndef __RFS_FWD_DEFINED__
#define __RFS_FWD_DEFINED__

#ifdef __cplusplus
typedef class RFS RFS;
#else
typedef struct RFS RFS;
#endif /* __cplusplus */

#endif 	/* __RFS_FWD_DEFINED__ */


#ifndef __IRFSSink_FWD_DEFINED__
#define __IRFSSink_FWD_DEFINED__
typedef interface IRFSSink IRFSSink;
#endif 	/* __IRFSSink_FWD_DEFINED__ */


#ifndef __RFSDataCallback_FWD_DEFINED__
#define __RFSDataCallback_FWD_DEFINED__

#ifdef __cplusplus
typedef class RFSDataCallback RFSDataCallback;
#else
typedef struct RFSDataCallback RFSDataCallback;
#endif /* __cplusplus */

#endif 	/* __RFSDataCallback_FWD_DEFINED__ */


#ifndef __RFSConnection_FWD_DEFINED__
#define __RFSConnection_FWD_DEFINED__

#ifdef __cplusplus
typedef class RFSConnection RFSConnection;
#else
typedef struct RFSConnection RFSConnection;
#endif /* __cplusplus */

#endif 	/* __RFSConnection_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "rtsock.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_scrfs_0000 */
/* [local] */ 

#define	KRfsErrNone	( 0 )

#define	KRfsErrNotFound	( -1 )

#define	KRfsErrGeneral	( -2 )

#define	KRfsErrCancel	( -3 )

#define	KRfsErrNoMemory	( -4 )

#define	KRfsErrNotSupported	( -5 )

#define	KRfsErrArgument	( -6 )

#define	KRfsErrTotalLossOfPrecision	( -7 )

#define	KRfsErrBadHandle	( -8 )

#define	KRfsErrOverflow	( -9 )

#define	KRfsErrUnderflow	( -10 )

#define	KRfsErrAlreadyExists	( -11 )

#define	KRfsErrPathNotFound	( -12 )

#define	KRfsErrDied	( -13 )

#define	KRfsErrInUse	( -14 )

#define	KRfsErrServerTerminated	( -15 )

#define	KRfsErrServerBusy	( -16 )

#define	KRfsErrCompletion	( -17 )

#define	KRfsErrNotReady	( -18 )

#define	KRfsErrUnknown	( -19 )

#define	KRfsErrCorrupt	( -20 )

#define	KRfsErrAccessDenied	( -21 )

#define	KRfsErrLocked	( -22 )

#define	KRfsErrWrite	( -23 )

#define	KRfsErrDisMounted	( -24 )

#define	KRfsErrEof	( -25 )

#define	KRfsErrDiskFull	( -26 )

#define	KRfsErrBadDriver	( -27 )

#define	KRfsErrBadName	( -28 )

#define	KRfsErrCommsLineFail	( -29 )

#define	KRfsErrCommsFrame	( -30 )

#define	KRfsErrCommsOverrun	( -31 )

#define	KRfsErrCommsParity	( -32 )

#define	KRfsErrTimedOut	( -33 )

#define	KRfsErrCouldNotConnect	( -34 )

#define	KRfsErrCouldNotDisconnect	( -35 )

#define	KRfsErrDisconnected	( -36 )

#define	KRfsErrBadLibraryEntryPoint	( -37 )

#define	KRfsErrBadDescriptor	( -38 )

#define	KRfsErrAbort	( -39 )

#define	KRfsErrTooBig	( -40 )

#define	KRfsErrDivideByZero	( -41 )

#define	KRfsErrBadPower	( -42 )

#define	KRfsErrDirFull	( -43 )

#define	KRfsErrNotAttached	( -500 )

#define	KRfsErrAlreadyAttached	( -501 )

#define	KRfsErrMoreData	( -502 )


enum TRfsMachine
    {	ERfsMachineLocal	= 1,
	ERfsMachineRemote	= 2
    };
#define	KRfsMaxUids	( 3 )

#define	KRfsMaxFileName	( 256 )

#define	KRfsMaxDosFileName	( 16 )

#define	KRfsMaxDataTypeLength	( 256 )

#define	KRfsMaxDataSize	( 2048 )

#define	ERfsFileAttrNormal	( 0 )

#define	ERfsFileAttrReadOnly	( 0x1 )

#define	ERfsFileAttrHidden	( 0x2 )

#define	ERfsFileAttrSystem	( 0x4 )

#define	ERfsFileAttrVolume	( 0x8 )

#define	ERfsFileAttrDirectory	( 0x10 )

#define	ERfsFileAttrArchive	( 0x20 )

#define	ERfsFileAttrMatchMask	( 0x16 )

#define	ERfsFileAttrMaskSupported	( 0x3f )

typedef /* [public][public][public] */ struct  __MIDL___MIDL_itf_scrfs_0000_0001
    {
    DWORD dwFileAttr;
    DWORD dwSize;
    FILETIME ftModified;
    DWORD dwType[ 3 ];
    TCHAR pszFileName[ 256 ];
    TCHAR pszDosFileName[ 16 ];
    TCHAR pszDataType[ 256 ];
    }	TRfsFileInfo;


enum TRfsCopyDirection
    {	ERfsPCToPC	= 0,
	ERfsPCToDevice	= ERfsPCToPC + 1,
	ERfsDeviceToPC	= ERfsPCToDevice + 1,
	ERfsDeviceToDevice	= ERfsDeviceToPC + 1
    };

enum TRfsCopyMode
    {	ERfsFileCopyNoOverwrite	= 0,
	ERfsFileCopyOverwriteAlways	= ERfsFileCopyNoOverwrite + 1,
	ERfsFileCopyOverwriteOlder	= ERfsFileCopyOverwriteAlways + 1
    };
#define	KRfsDriveAttUnknown	( 0 )

#define	KRfsDriveAttLocal	( 0x1 )

#define	KRfsDriveAttRom	( 0x2 )

#define	KRfsDriveAttRedirected	( 0x4 )

#define	KRfsDriveAttSubsted	( 0x8 )

#define	KRfsDriveAttInternal	( 0x10 )

#define	KRfsDriveAttRemovable	( 0x20 )

#define	KRfsMediaAttUnknown	( 0 )

#define	KRfsMediaAttVariableSize	( 0x1 )

#define	KRfsMediaAttDualDensity	( 0x2 )

#define	KRfsMediaAttFormattable	( 0x4 )

#define	KRfsMediaAttWriteProtected	( 0x8 )

#define	KRfsMaxVolumeName	( 32 )

#define	KRfsMaxDeviceName	( 4 )


enum TRfsMediaType
    {	ERfsMediaNotPresent	= 0,
	ERfsMediaUnknown	= ERfsMediaNotPresent + 1,
	ERfsMediaFloppy	= ERfsMediaUnknown + 1,
	ERfsMediaHardDisk	= ERfsMediaFloppy + 1,
	ERfsMediaCdRom	= ERfsMediaHardDisk + 1,
	ERfsMediaRam	= ERfsMediaCdRom + 1,
	ERfsMediaFlash	= ERfsMediaRam + 1,
	ERfsMediaRom	= ERfsMediaFlash + 1,
	ERfsMediaRemote	= ERfsMediaRom + 1
    };
#define	KRfsMaxIdStringLength	( 128 )

typedef /* [public][public] */ struct  __MIDL___MIDL_itf_scrfs_0000_0002
    {
    DWORD dwMediaType;
    DWORD dwMediaAttr;
    DWORD dwDriveAttr;
    DWORD dwBatteryInfo;
    DWORD dwUniqueId;
    DWORD dwSizeLow;
    DWORD dwSizeHigh;
    DWORD dwFreeLow;
    DWORD dwFreeHigh;
    TCHAR pszVolumeName[ 32 ];
    TCHAR pszDeviceName[ 4 ];
    TCHAR pszDeviceId[ 128 ];
    TCHAR pszDeviceAlias[ 128 ];
    }	TRfsDeviceInfo;

#define	ERfsMaxDrives	( 26 )


enum TRfsDrives
    {	ERfsDriveA	= 0,
	ERfsDriveB	= ERfsDriveA + 1,
	ERfsDriveC	= ERfsDriveB + 1,
	ERfsDriveD	= ERfsDriveC + 1,
	ERfsDriveE	= ERfsDriveD + 1,
	ERfsDriveF	= ERfsDriveE + 1,
	ERfsDriveG	= ERfsDriveF + 1,
	ERfsDriveH	= ERfsDriveG + 1,
	ERfsDriveI	= ERfsDriveH + 1,
	ERfsDriveJ	= ERfsDriveI + 1,
	ERfsDriveK	= ERfsDriveJ + 1,
	ERfsDriveL	= ERfsDriveK + 1,
	ERfsDriveM	= ERfsDriveL + 1,
	ERfsDriveN	= ERfsDriveM + 1,
	ERfsDriveO	= ERfsDriveN + 1,
	ERfsDriveP	= ERfsDriveO + 1,
	ERfsDriveQ	= ERfsDriveP + 1,
	ERfsDriveR	= ERfsDriveQ + 1,
	ERfsDriveS	= ERfsDriveR + 1,
	ERfsDriveT	= ERfsDriveS + 1,
	ERfsDriveU	= ERfsDriveT + 1,
	ERfsDriveV	= ERfsDriveU + 1,
	ERfsDriveW	= ERfsDriveV + 1,
	ERfsDriveX	= ERfsDriveW + 1,
	ERfsDriveY	= ERfsDriveX + 1,
	ERfsDriveZ	= ERfsDriveY + 1
    };
typedef /* [public][public][public] */ struct  __MIDL___MIDL_itf_scrfs_0000_0003
    {
    CHAR cMajor;
    CHAR cMinor;
    SHORT sBuild;
    }	TRfsRomVersion;


enum TRfsMachineType
    {	ERfsMachineUnknown	= 0,
	ERfsMachinePC	= ERfsMachineUnknown + 1,
	ERfsMachineHC	= ERfsMachinePC + 1,
	ERfsMachineMC	= ERfsMachineHC + 1,
	ERfsMachineSeries3	= ERfsMachineMC + 1,
	ERfsMachineSeries3a	= ERfsMachineSeries3 + 1,
	ERfsMachineWorkabout	= ERfsMachineSeries3a + 1,
	ERfsMachineSiena	= ERfsMachineWorkabout + 1,
	ERfsMachineSeries3c	= ERfsMachineSiena + 1,
	ERfsMachineEpoc32	= 32
    };
typedef /* [public][public][public] */ struct  __MIDL___MIDL_itf_scrfs_0000_0004
    {
    SHORT sWidth;
    SHORT sHeight;
    }	TRfsSize;


enum TRfsLanguage
    {	ERfsLangTest	= 0,
	ERfsLangEnglish	= ERfsLangTest + 1,
	ERfsLangFrench	= ERfsLangEnglish + 1,
	ERfsLangGerman	= ERfsLangFrench + 1,
	ERfsLangSpanish	= ERfsLangGerman + 1,
	ERfsLangItalian	= ERfsLangSpanish + 1,
	ERfsLangSwedish	= ERfsLangItalian + 1,
	ERfsLangDanish	= ERfsLangSwedish + 1,
	ERfsLangNorwegian	= ERfsLangDanish + 1,
	ERfsLangFinnish	= ERfsLangNorwegian + 1,
	ERfsLangAmerican	= ERfsLangFinnish + 1,
	ERfsLangSwissFrench	= ERfsLangAmerican + 1,
	ERfsLangSwissGerman	= ERfsLangSwissFrench + 1,
	ERfsLangPortuguese	= ERfsLangSwissGerman + 1,
	ERfsLangTurkish	= ERfsLangPortuguese + 1,
	ERfsLangIcelandic	= ERfsLangTurkish + 1,
	ERfsLangRussian	= ERfsLangIcelandic + 1,
	ERfsLangHungarian	= ERfsLangRussian + 1,
	ERfsLangDutch	= ERfsLangHungarian + 1,
	ERfsLangBelgianFlemish	= ERfsLangDutch + 1,
	ERfsLangAustralian	= ERfsLangBelgianFlemish + 1,
	ERfsLangBelgianFrench	= ERfsLangAustralian + 1
    };

enum TRfsDaylightSavingZone
    {	ERfsDstHome	= 0x40000000,
	ERfsDstNone	= 0,
	ERfsDstEuropean	= 1,
	ERfsDstNorthern	= 2,
	ERfsDstSouthern	= 4
    };
typedef /* [public][public][public] */ struct  __MIDL___MIDL_itf_scrfs_0000_0005
    {
    FILETIME ftHomeTime;
    SHORT sCountryCode;
    SHORT sUniversalTimeOffset;
    SHORT sDaylightSaving;
    DWORD dwHomeDaylightSavingZone;
    }	TRfsTime;

typedef /* [public][public][public] */ struct  __MIDL___MIDL_itf_scrfs_0000_0006
    {
    SHORT sTotalRamInBytes;
    SHORT sTotalRomInBytes;
    SHORT sMaxFreeRamInBytes;
    SHORT sFreeRamInBytes;
    SHORT sInternalDiskRamInBytes;
    SHORT sRomIsReprogrammable;
    }	TRfsMemoryInfo;

#define	KRfsMaxMachineNameSize	( 17 )

#define	KRfsMaxPropertyLength	( 1024 )

typedef /* [public][public] */ struct  __MIDL___MIDL_itf_scrfs_0000_0007
    {
    UINT uiType;
    TRfsRomVersion rrvRomVersion;
    TCHAR pszMachineName[ 17 ];
    TRfsSize rsDisplaySizePixels;
    DWORD dwMachineUniqueIdLow;
    DWORD dwMachineUniqueIdHigh;
    SHORT sLanguage;
    TRfsMemoryInfo rmiMemoryInfo;
    TRfsTime rtSystemTime;
    TCHAR pszMachineId[ 128 ];
    }	TRfsMachineInfo;


enum TRfsCancelOption
    {	ERfsCancelFirstFileOp	= 0,
	ERfsCancelFirstDeviceOp	= ERfsCancelFirstFileOp + 1,
	ERfsCancelFirstFileAndDeviceOp	= ERfsCancelFirstDeviceOp + 1,
	ERfsCancelAllFileOps	= ERfsCancelFirstFileAndDeviceOp + 1,
	ERfsCancelAllDeviceOps	= ERfsCancelAllFileOps + 1,
	ERfsCancelAllOps	= ERfsCancelAllDeviceOps + 1
    };


extern RPC_IF_HANDLE __MIDL_itf_scrfs_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_scrfs_0000_v0_0_s_ifspec;

#ifndef __IRFS_INTERFACE_DEFINED__
#define __IRFS_INTERFACE_DEFINED__

/* interface IRFS */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C IID IID_IRFS;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC000153-CEE5-11D2-A953-00105A46D6E4")
    IRFS : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Attach( 
            /* [in] */ IUnknown __RPC_FAR *pEventSink,
            /* [in] */ DWORD dwThread,
            /* [out] */ DWORD __RPC_FAR *pdwCookie,
            /* [out] */ BOOL __RPC_FAR *bConnected) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Detach( 
            /* [in] */ DWORD dwCookie) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CancelRequest( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ WORD wCancelOption) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeviceList( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeviceInfo( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ DWORD dwDevice) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeviceLabel( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ DWORD dwDevice,
            /* [in] */ LPCTSTR pszLabel) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DirectoryOpen( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszDirectory) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DirectoryRead( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ DWORD dwHandle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DirectoryClose( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ DWORD dwHandle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DirectoryDelete( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszDirectory) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DirectoryCreate( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszDirectory) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileInfo( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszFile) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileSetAttr( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszFile,
            /* [in] */ DWORD dwFileAttr) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileCopy( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ LPCTSTR pszSource,
            /* [in] */ LPCTSTR pszDestination,
            /* [in] */ DWORD rcdCopyDirection,
            /* [in] */ DWORD rcmCopyMode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileDelete( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszFile) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileRename( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszFile,
            /* [in] */ LPCTSTR pszNewName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MachineType( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MachineInfo( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MachineOwner( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MachineSyncTime( 
            /* [in] */ DWORD dwCookie) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FormatOpen( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwDrive) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FormatRead( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwHandle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FormatClose( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwHandle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetProperty( 
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectionReason( 
            /* [in] */ DWORD dwCookie) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetServerPID( 
            /* [out] */ DWORD __RPC_FAR *dwPID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRFSVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRFS __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRFS __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRFS __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Attach )( 
            IRFS __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pEventSink,
            /* [in] */ DWORD dwThread,
            /* [out] */ DWORD __RPC_FAR *pdwCookie,
            /* [out] */ BOOL __RPC_FAR *bConnected);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Detach )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelRequest )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ WORD wCancelOption);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeviceList )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeviceInfo )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ DWORD dwDevice);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeviceLabel )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ DWORD dwDevice,
            /* [in] */ LPCTSTR pszLabel);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DirectoryOpen )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszDirectory);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DirectoryRead )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ DWORD dwHandle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DirectoryClose )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ DWORD dwHandle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DirectoryDelete )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszDirectory);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DirectoryCreate )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszDirectory);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FileInfo )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszFile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FileSetAttr )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszFile,
            /* [in] */ DWORD dwFileAttr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FileCopy )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ LPCTSTR pszSource,
            /* [in] */ LPCTSTR pszDestination,
            /* [in] */ DWORD rcdCopyDirection,
            /* [in] */ DWORD rcmCopyMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FileDelete )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszFile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FileRename )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine,
            /* [in] */ LPCTSTR pszFile,
            /* [in] */ LPCTSTR pszNewName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MachineType )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MachineInfo )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MachineOwner )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwMachine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MachineSyncTime )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FormatOpen )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwDrive);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FormatRead )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwHandle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FormatClose )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwHandle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperty )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [in] */ DWORD dwUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectionReason )( 
            IRFS __RPC_FAR * This,
            /* [in] */ DWORD dwCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetServerPID )( 
            IRFS __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *dwPID);
        
        END_INTERFACE
    } IRFSVtbl;

    interface IRFS
    {
        CONST_VTBL struct IRFSVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRFS_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRFS_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRFS_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRFS_Attach(This,pEventSink,dwThread,pdwCookie,bConnected)	\
    (This)->lpVtbl -> Attach(This,pEventSink,dwThread,pdwCookie,bConnected)

#define IRFS_Detach(This,dwCookie)	\
    (This)->lpVtbl -> Detach(This,dwCookie)

#define IRFS_CancelRequest(This,dwCookie,wCancelOption)	\
    (This)->lpVtbl -> CancelRequest(This,dwCookie,wCancelOption)

#define IRFS_DeviceList(This,dwCookie,dwMachine)	\
    (This)->lpVtbl -> DeviceList(This,dwCookie,dwMachine)

#define IRFS_DeviceInfo(This,dwCookie,dwMachine,dwDevice)	\
    (This)->lpVtbl -> DeviceInfo(This,dwCookie,dwMachine,dwDevice)

#define IRFS_DeviceLabel(This,dwCookie,dwMachine,dwDevice,pszLabel)	\
    (This)->lpVtbl -> DeviceLabel(This,dwCookie,dwMachine,dwDevice,pszLabel)

#define IRFS_DirectoryOpen(This,dwCookie,dwMachine,pszDirectory)	\
    (This)->lpVtbl -> DirectoryOpen(This,dwCookie,dwMachine,pszDirectory)

#define IRFS_DirectoryRead(This,dwCookie,dwMachine,dwHandle)	\
    (This)->lpVtbl -> DirectoryRead(This,dwCookie,dwMachine,dwHandle)

#define IRFS_DirectoryClose(This,dwCookie,dwMachine,dwHandle)	\
    (This)->lpVtbl -> DirectoryClose(This,dwCookie,dwMachine,dwHandle)

#define IRFS_DirectoryDelete(This,dwCookie,dwMachine,pszDirectory)	\
    (This)->lpVtbl -> DirectoryDelete(This,dwCookie,dwMachine,pszDirectory)

#define IRFS_DirectoryCreate(This,dwCookie,dwMachine,pszDirectory)	\
    (This)->lpVtbl -> DirectoryCreate(This,dwCookie,dwMachine,pszDirectory)

#define IRFS_FileInfo(This,dwCookie,dwMachine,pszFile)	\
    (This)->lpVtbl -> FileInfo(This,dwCookie,dwMachine,pszFile)

#define IRFS_FileSetAttr(This,dwCookie,dwMachine,pszFile,dwFileAttr)	\
    (This)->lpVtbl -> FileSetAttr(This,dwCookie,dwMachine,pszFile,dwFileAttr)

#define IRFS_FileCopy(This,dwCookie,pszSource,pszDestination,rcdCopyDirection,rcmCopyMode)	\
    (This)->lpVtbl -> FileCopy(This,dwCookie,pszSource,pszDestination,rcdCopyDirection,rcmCopyMode)

#define IRFS_FileDelete(This,dwCookie,dwMachine,pszFile)	\
    (This)->lpVtbl -> FileDelete(This,dwCookie,dwMachine,pszFile)

#define IRFS_FileRename(This,dwCookie,dwMachine,pszFile,pszNewName)	\
    (This)->lpVtbl -> FileRename(This,dwCookie,dwMachine,pszFile,pszNewName)

#define IRFS_MachineType(This,dwCookie,dwMachine)	\
    (This)->lpVtbl -> MachineType(This,dwCookie,dwMachine)

#define IRFS_MachineInfo(This,dwCookie,dwMachine)	\
    (This)->lpVtbl -> MachineInfo(This,dwCookie,dwMachine)

#define IRFS_MachineOwner(This,dwCookie,dwMachine)	\
    (This)->lpVtbl -> MachineOwner(This,dwCookie,dwMachine)

#define IRFS_MachineSyncTime(This,dwCookie)	\
    (This)->lpVtbl -> MachineSyncTime(This,dwCookie)

#define IRFS_FormatOpen(This,dwCookie,dwDrive)	\
    (This)->lpVtbl -> FormatOpen(This,dwCookie,dwDrive)

#define IRFS_FormatRead(This,dwCookie,dwHandle)	\
    (This)->lpVtbl -> FormatRead(This,dwCookie,dwHandle)

#define IRFS_FormatClose(This,dwCookie,dwHandle)	\
    (This)->lpVtbl -> FormatClose(This,dwCookie,dwHandle)

#define IRFS_GetProperty(This,dwCookie,dwUID)	\
    (This)->lpVtbl -> GetProperty(This,dwCookie,dwUID)

#define IRFS_ConnectionReason(This,dwCookie)	\
    (This)->lpVtbl -> ConnectionReason(This,dwCookie)

#define IRFS_GetServerPID(This,dwPID)	\
    (This)->lpVtbl -> GetServerPID(This,dwPID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_Attach_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pEventSink,
    /* [in] */ DWORD dwThread,
    /* [out] */ DWORD __RPC_FAR *pdwCookie,
    /* [out] */ BOOL __RPC_FAR *bConnected);


void __RPC_STUB IRFS_Attach_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_Detach_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IRFS_Detach_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_CancelRequest_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ WORD wCancelOption);


void __RPC_STUB IRFS_CancelRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_DeviceList_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine);


void __RPC_STUB IRFS_DeviceList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_DeviceInfo_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine,
    /* [in] */ DWORD dwDevice);


void __RPC_STUB IRFS_DeviceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_DeviceLabel_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine,
    /* [in] */ DWORD dwDevice,
    /* [in] */ LPCTSTR pszLabel);


void __RPC_STUB IRFS_DeviceLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_DirectoryOpen_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine,
    /* [in] */ LPCTSTR pszDirectory);


void __RPC_STUB IRFS_DirectoryOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_DirectoryRead_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine,
    /* [in] */ DWORD dwHandle);


void __RPC_STUB IRFS_DirectoryRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_DirectoryClose_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine,
    /* [in] */ DWORD dwHandle);


void __RPC_STUB IRFS_DirectoryClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_DirectoryDelete_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine,
    /* [in] */ LPCTSTR pszDirectory);


void __RPC_STUB IRFS_DirectoryDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_DirectoryCreate_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine,
    /* [in] */ LPCTSTR pszDirectory);


void __RPC_STUB IRFS_DirectoryCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_FileInfo_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine,
    /* [in] */ LPCTSTR pszFile);


void __RPC_STUB IRFS_FileInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_FileSetAttr_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine,
    /* [in] */ LPCTSTR pszFile,
    /* [in] */ DWORD dwFileAttr);


void __RPC_STUB IRFS_FileSetAttr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_FileCopy_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ LPCTSTR pszSource,
    /* [in] */ LPCTSTR pszDestination,
    /* [in] */ DWORD rcdCopyDirection,
    /* [in] */ DWORD rcmCopyMode);


void __RPC_STUB IRFS_FileCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_FileDelete_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine,
    /* [in] */ LPCTSTR pszFile);


void __RPC_STUB IRFS_FileDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_FileRename_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine,
    /* [in] */ LPCTSTR pszFile,
    /* [in] */ LPCTSTR pszNewName);


void __RPC_STUB IRFS_FileRename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_MachineType_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine);


void __RPC_STUB IRFS_MachineType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_MachineInfo_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine);


void __RPC_STUB IRFS_MachineInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_MachineOwner_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwMachine);


void __RPC_STUB IRFS_MachineOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_MachineSyncTime_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IRFS_MachineSyncTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_FormatOpen_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwDrive);


void __RPC_STUB IRFS_FormatOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_FormatRead_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwHandle);


void __RPC_STUB IRFS_FormatRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_FormatClose_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwHandle);


void __RPC_STUB IRFS_FormatClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_GetProperty_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [in] */ DWORD dwUID);


void __RPC_STUB IRFS_GetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_ConnectionReason_Proxy( 
    IRFS __RPC_FAR * This,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IRFS_ConnectionReason_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFS_GetServerPID_Proxy( 
    IRFS __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *dwPID);


void __RPC_STUB IRFS_GetServerPID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRFS_INTERFACE_DEFINED__ */


#ifndef __IRFSSink_INTERFACE_DEFINED__
#define __IRFSSink_INTERFACE_DEFINED__

/* interface IRFSSink */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C IID IID_IRFSSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC000154-CEE5-11D2-A953-00105A46D6E4")
    IRFSSink : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnConnect( 
            /* [in] */ LONG lResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDisconnect( 
            /* [in] */ LONG lResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDeviceList( 
            /* [in] */ LONG lResult,
            /* [in] */ DWORD dwDriveMask) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDeviceInfo( 
            /* [in] */ LONG lResult,
            /* [full][in] */ TRfsDeviceInfo __RPC_FAR *prdiInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDeviceLabel( 
            /* [in] */ LONG lResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDirectoryOpen( 
            /* [in] */ LONG lResult,
            /* [in] */ DWORD dwHandle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDirectoryRead( 
            /* [in] */ LONG lResult,
            /* [full][in] */ TRfsFileInfo __RPC_FAR *prfiInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDirectoryClose( 
            /* [in] */ LONG lResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDirectoryDelete( 
            /* [in] */ LONG lResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDirectoryCreate( 
            /* [in] */ LONG lResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFileInfo( 
            /* [in] */ LONG lResult,
            /* [full][in] */ TRfsFileInfo __RPC_FAR *prfiInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFileSetAttr( 
            /* [in] */ LONG lResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFileCopy( 
            /* [in] */ LONG lResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFileDelete( 
            /* [in] */ LONG lResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFileRename( 
            /* [in] */ LONG lResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnMachineType( 
            /* [in] */ LONG lResult,
            /* [in] */ DWORD dwType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnMachineInfo( 
            /* [in] */ LONG lResult,
            /* [full][in] */ TRfsMachineInfo __RPC_FAR *prmiInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnMachineOwner( 
            /* [in] */ LONG lResult,
            /* [in] */ LPCTSTR pszOwner) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnMachineSyncTime( 
            /* [in] */ LONG lResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFormatOpen( 
            /* [in] */ LONG lResult,
            /* [in] */ DWORD dwHandle,
            /* [in] */ DWORD dwCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFormatRead( 
            /* [in] */ LONG lResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFormatClose( 
            /* [in] */ LONG lResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnGetProperty( 
            /* [in] */ LONG lResult,
            /* [in] */ LPCTSTR pszProperty) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnConnectionReason( 
            /* [in] */ LONG lResult,
            /* [in] */ DWORD dwReason) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CopyProgress( 
            /* [in] */ WORD wPercentCopied,
            /* [out] */ BOOL __RPC_FAR *bCancel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRFSSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRFSSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRFSSink __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnConnect )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDisconnect )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDeviceList )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult,
            /* [in] */ DWORD dwDriveMask);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDeviceInfo )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult,
            /* [full][in] */ TRfsDeviceInfo __RPC_FAR *prdiInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDeviceLabel )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDirectoryOpen )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult,
            /* [in] */ DWORD dwHandle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDirectoryRead )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult,
            /* [full][in] */ TRfsFileInfo __RPC_FAR *prfiInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDirectoryClose )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDirectoryDelete )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDirectoryCreate )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFileInfo )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult,
            /* [full][in] */ TRfsFileInfo __RPC_FAR *prfiInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFileSetAttr )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFileCopy )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFileDelete )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFileRename )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnMachineType )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult,
            /* [in] */ DWORD dwType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnMachineInfo )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult,
            /* [full][in] */ TRfsMachineInfo __RPC_FAR *prmiInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnMachineOwner )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult,
            /* [in] */ LPCTSTR pszOwner);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnMachineSyncTime )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFormatOpen )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult,
            /* [in] */ DWORD dwHandle,
            /* [in] */ DWORD dwCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFormatRead )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFormatClose )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnGetProperty )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult,
            /* [in] */ LPCTSTR pszProperty);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnConnectionReason )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ LONG lResult,
            /* [in] */ DWORD dwReason);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyProgress )( 
            IRFSSink __RPC_FAR * This,
            /* [in] */ WORD wPercentCopied,
            /* [out] */ BOOL __RPC_FAR *bCancel);
        
        END_INTERFACE
    } IRFSSinkVtbl;

    interface IRFSSink
    {
        CONST_VTBL struct IRFSSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRFSSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRFSSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRFSSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRFSSink_OnConnect(This,lResult)	\
    (This)->lpVtbl -> OnConnect(This,lResult)

#define IRFSSink_OnDisconnect(This,lResult)	\
    (This)->lpVtbl -> OnDisconnect(This,lResult)

#define IRFSSink_OnDeviceList(This,lResult,dwDriveMask)	\
    (This)->lpVtbl -> OnDeviceList(This,lResult,dwDriveMask)

#define IRFSSink_OnDeviceInfo(This,lResult,prdiInfo)	\
    (This)->lpVtbl -> OnDeviceInfo(This,lResult,prdiInfo)

#define IRFSSink_OnDeviceLabel(This,lResult)	\
    (This)->lpVtbl -> OnDeviceLabel(This,lResult)

#define IRFSSink_OnDirectoryOpen(This,lResult,dwHandle)	\
    (This)->lpVtbl -> OnDirectoryOpen(This,lResult,dwHandle)

#define IRFSSink_OnDirectoryRead(This,lResult,prfiInfo)	\
    (This)->lpVtbl -> OnDirectoryRead(This,lResult,prfiInfo)

#define IRFSSink_OnDirectoryClose(This,lResult)	\
    (This)->lpVtbl -> OnDirectoryClose(This,lResult)

#define IRFSSink_OnDirectoryDelete(This,lResult)	\
    (This)->lpVtbl -> OnDirectoryDelete(This,lResult)

#define IRFSSink_OnDirectoryCreate(This,lResult)	\
    (This)->lpVtbl -> OnDirectoryCreate(This,lResult)

#define IRFSSink_OnFileInfo(This,lResult,prfiInfo)	\
    (This)->lpVtbl -> OnFileInfo(This,lResult,prfiInfo)

#define IRFSSink_OnFileSetAttr(This,lResult)	\
    (This)->lpVtbl -> OnFileSetAttr(This,lResult)

#define IRFSSink_OnFileCopy(This,lResult)	\
    (This)->lpVtbl -> OnFileCopy(This,lResult)

#define IRFSSink_OnFileDelete(This,lResult)	\
    (This)->lpVtbl -> OnFileDelete(This,lResult)

#define IRFSSink_OnFileRename(This,lResult)	\
    (This)->lpVtbl -> OnFileRename(This,lResult)

#define IRFSSink_OnMachineType(This,lResult,dwType)	\
    (This)->lpVtbl -> OnMachineType(This,lResult,dwType)

#define IRFSSink_OnMachineInfo(This,lResult,prmiInfo)	\
    (This)->lpVtbl -> OnMachineInfo(This,lResult,prmiInfo)

#define IRFSSink_OnMachineOwner(This,lResult,pszOwner)	\
    (This)->lpVtbl -> OnMachineOwner(This,lResult,pszOwner)

#define IRFSSink_OnMachineSyncTime(This,lResult)	\
    (This)->lpVtbl -> OnMachineSyncTime(This,lResult)

#define IRFSSink_OnFormatOpen(This,lResult,dwHandle,dwCount)	\
    (This)->lpVtbl -> OnFormatOpen(This,lResult,dwHandle,dwCount)

#define IRFSSink_OnFormatRead(This,lResult)	\
    (This)->lpVtbl -> OnFormatRead(This,lResult)

#define IRFSSink_OnFormatClose(This,lResult)	\
    (This)->lpVtbl -> OnFormatClose(This,lResult)

#define IRFSSink_OnGetProperty(This,lResult,pszProperty)	\
    (This)->lpVtbl -> OnGetProperty(This,lResult,pszProperty)

#define IRFSSink_OnConnectionReason(This,lResult,dwReason)	\
    (This)->lpVtbl -> OnConnectionReason(This,lResult,dwReason)

#define IRFSSink_CopyProgress(This,wPercentCopied,bCancel)	\
    (This)->lpVtbl -> CopyProgress(This,wPercentCopied,bCancel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnConnect_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult);


void __RPC_STUB IRFSSink_OnConnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnDisconnect_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult);


void __RPC_STUB IRFSSink_OnDisconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnDeviceList_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult,
    /* [in] */ DWORD dwDriveMask);


void __RPC_STUB IRFSSink_OnDeviceList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnDeviceInfo_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult,
    /* [full][in] */ TRfsDeviceInfo __RPC_FAR *prdiInfo);


void __RPC_STUB IRFSSink_OnDeviceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnDeviceLabel_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult);


void __RPC_STUB IRFSSink_OnDeviceLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnDirectoryOpen_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult,
    /* [in] */ DWORD dwHandle);


void __RPC_STUB IRFSSink_OnDirectoryOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnDirectoryRead_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult,
    /* [full][in] */ TRfsFileInfo __RPC_FAR *prfiInfo);


void __RPC_STUB IRFSSink_OnDirectoryRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnDirectoryClose_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult);


void __RPC_STUB IRFSSink_OnDirectoryClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnDirectoryDelete_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult);


void __RPC_STUB IRFSSink_OnDirectoryDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnDirectoryCreate_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult);


void __RPC_STUB IRFSSink_OnDirectoryCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnFileInfo_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult,
    /* [full][in] */ TRfsFileInfo __RPC_FAR *prfiInfo);


void __RPC_STUB IRFSSink_OnFileInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnFileSetAttr_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult);


void __RPC_STUB IRFSSink_OnFileSetAttr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnFileCopy_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult);


void __RPC_STUB IRFSSink_OnFileCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnFileDelete_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult);


void __RPC_STUB IRFSSink_OnFileDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnFileRename_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult);


void __RPC_STUB IRFSSink_OnFileRename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnMachineType_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult,
    /* [in] */ DWORD dwType);


void __RPC_STUB IRFSSink_OnMachineType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnMachineInfo_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult,
    /* [full][in] */ TRfsMachineInfo __RPC_FAR *prmiInfo);


void __RPC_STUB IRFSSink_OnMachineInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnMachineOwner_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult,
    /* [in] */ LPCTSTR pszOwner);


void __RPC_STUB IRFSSink_OnMachineOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnMachineSyncTime_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult);


void __RPC_STUB IRFSSink_OnMachineSyncTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnFormatOpen_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult,
    /* [in] */ DWORD dwHandle,
    /* [in] */ DWORD dwCount);


void __RPC_STUB IRFSSink_OnFormatOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnFormatRead_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult);


void __RPC_STUB IRFSSink_OnFormatRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnFormatClose_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult);


void __RPC_STUB IRFSSink_OnFormatClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnGetProperty_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult,
    /* [in] */ LPCTSTR pszProperty);


void __RPC_STUB IRFSSink_OnGetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_OnConnectionReason_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ LONG lResult,
    /* [in] */ DWORD dwReason);


void __RPC_STUB IRFSSink_OnConnectionReason_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRFSSink_CopyProgress_Proxy( 
    IRFSSink __RPC_FAR * This,
    /* [in] */ WORD wPercentCopied,
    /* [out] */ BOOL __RPC_FAR *bCancel);


void __RPC_STUB IRFSSink_CopyProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRFSSink_INTERFACE_DEFINED__ */



#ifndef __SCRFSLib_LIBRARY_DEFINED__
#define __SCRFSLib_LIBRARY_DEFINED__

/* library SCRFSLib */
/* [helpstring][version][uuid] */ 



EXTERN_C IID LIBID_SCRFSLib;

EXTERN_C CLSID CLSID_RFS;

#ifdef __cplusplus

class DECLSPEC_UUID("EC100153-CEE5-11D2-A953-00105A46D6E4")
RFS;
#endif

EXTERN_C CLSID CLSID_RFSDataCallback;

#ifdef __cplusplus

class DECLSPEC_UUID("EC100154-CEE5-11D2-A953-00105A46D6E4")
RFSDataCallback;
#endif

EXTERN_C CLSID CLSID_RFSConnection;

#ifdef __cplusplus

class DECLSPEC_UUID("EC100155-CEE5-11D2-A953-00105A46D6E4")
RFSConnection;
#endif
#endif /* __SCRFSLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
