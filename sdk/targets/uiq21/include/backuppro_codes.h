// Copyright (c) 2001 Intuwave Ltd.  All rights reserved.

#ifndef _Backuppro_codes_H_
#define _Backuppro_codes_H_

// 40Kb
const int KBckRawPacketSize = 40938; // 40K - (11 bytes for each request)
const int KBckPacketSize = KBckRawPacketSize - 4; // 40K - (11 bytes for each request) - 4 bytes for size parameter

enum TBackupCmdCode
	{
	EBackupCmdCloseAllFiles,		// close all non-system apps/files
	EBackupCmdCloseFile,			// close a particular file
	EBackupCmdResumeAllFiles,		// open all files
	EBackupCmdResumeFile,			// open a particular file
	EBackupCmdGetCloseAllFilesError,// EBackupCmdCloseAllFiles may return an error, if operating in synchronous mode it
									// is returned when the custom server completes, if operating in asynchronous mode
									// then this command must be called after the broadcast has been received in order
									// to interrogate the custom server as to if there was an error encountered or not
	EBackupCmdGetSnapshot,			// EBackupCmdGetSnapshot retrieves a snapshot of a directory of a drive
	EBackupCmdGetFiles				// EBackupCmdGetFile retrieves file data
	};

enum TBackupFileLockFlags
	{
	EBackupTakeLock,
	EBackupReleaseLockReadOnly,
	EBackupReleaseLockNoAccess
	};

enum TBackupSnapshotFlags
	{
	EBackupNoFlags = 0,
	EBackupRecurse = 1,
	};
	
#endif