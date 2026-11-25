// CUSTOMSERVERSHARED.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__CUSTOMSERVERSHARED_H__)
#define __CUSTOMSERVERSHARED_H__
//
enum TFileRequestType
    { 

	EReqRfsQueryVersion = 0,
	EReqRfsCloseServer = 0xff,

    EReqRfsrvOpen= 0x0f, //EReqReserved, // 0x0f
	EReqOpenDir,                // 0x10
    EResponse,                  // 0x11
	EReqReadDir,                // 0x12
	EReqGetDriveList,           // 0x13
    EReqVolume,                 // 0x14
	EReqSetVolumeLabel,         // 0x15
	EReqOpenFile, 
	EReqTempFile, 
    EReqReadFile, 
	EReqWriteFile,              // 0x19
	EReqSeekFile,               // 0x1a
	EReqDelete, 
	EReqRemoteEntry,            // 0x1c
    EReqFlush, 
	EReqSetSize, 
	EReqRename,                 // 0x1f
	EReqMkDirAll,               // 0x20
	EReqRmDir, 
	EReqSetAtt,
    EReqAtt, 
	EReqSetModified,            // 0x24
	EReqModified, 
	EReqSetSessionPath, 
	EReqSessionPath, 
    EReqReadWriteFile, 
	EReqCreateFile,             // 0x29
	EReqReplaceFile,            // 0x2a
	EReqPathTest,
    EReqLock, 
	EReqUnLock, 
	EReqOpenDirUid,             // 46
	EReqDriveName, 
	EReqSetDriveName,
	EReqReplace, 
	EReqShortPath,              // 50
	EReqLongPath,               // 51
    };
//
// Chunk size used by RFS and RPCS
#define MAX_DATACHUNK_SIZE	20480
//
#endif
