// Euniw.h
//
// Copyright (c) Symbian Software Ltd 1999-2004.  All rights reserved.
//
/**
@file
@publishedPartner
@released
*/

#if !defined(__EUNIW_H__)
#define __EUNIW_H__

#include "e32def.h"
#define WIN32_LEAN_AND_MEAN
#pragma warning( disable : 4201 ) // nonstandard extension used : nameless struct/union
#include <windows.h>
#pragma warning( default : 4201 ) // nonstandard extension used : nameless struct/union

#ifdef __cplusplus
extern "C" {
#endif


// Declare function pointers for each function
typedef BOOL (WINAPI *UNIW_CreateDirectory) (LPCTSTR ,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
typedef HANDLE (WINAPI *UNIW_CreateFile) (LPCTSTR ,DWORD ,DWORD ,LPSECURITY_ATTRIBUTES ,DWORD ,DWORD ,HANDLE);
typedef HANDLE (WINAPI *UNIW_CreateMutex) (LPSECURITY_ATTRIBUTES , BOOL, LPCTSTR);
typedef HANDLE (WINAPI *UNIW_CreateSemaphore) (LPSECURITY_ATTRIBUTES ,LONG ,LONG ,LPCTSTR);
typedef LRESULT (WINAPI *UNIW_DefWindowProc) (HWND hWnd, UINT,WPARAM ,LPARAM);
typedef BOOL (WINAPI *UNIW_DeleteFile) (LPCTSTR);
typedef LONG (WINAPI *UNIW_DispatchMessage) (CONST MSG*);
typedef HANDLE (WINAPI *UNIW_FindFirstFile) (LPCTSTR ,LPWIN32_FIND_DATA);
typedef BOOL (WINAPI *UNIW_FindNextFile) (HANDLE ,LPWIN32_FIND_DATA);
typedef DWORD (WINAPI *UNIW_GetCurrentDirectory) (DWORD ,LPTSTR);
typedef BOOL (WINAPI *UNIW_GetDiskFreeSpace) (LPCTSTR ,LPDWORD ,LPDWORD ,LPDWORD ,LPDWORD);
typedef UINT (WINAPI *UNIW_GetDriveType) (LPCTSTR);
typedef DWORD (WINAPI *UNIW_GetEnvironmentVariable) (LPCTSTR ,LPTSTR ,DWORD);
typedef DWORD (WINAPI *UNIW_GetFileAttributes) (LPCTSTR);
typedef DWORD (WINAPI *UNIW_GetFullPathName) (LPCTSTR ,DWORD ,LPTSTR ,LPTSTR*);
typedef BOOL (WINAPI *UNIW_GetMessage) (LPMSG ,HWND ,UINT ,UINT);
typedef DWORD (WINAPI *UNIW_GetModuleFileName)(HMODULE , LPTSTR ,DWORD);
typedef HMODULE (WINAPI *UNIW_GetModuleHandle) (LPCTSTR);
typedef int  (WINAPI *UNIW_GetObject) (HGDIOBJ, int, LPVOID);
typedef DWORD (WINAPI *UNIW_GetTempPath) (DWORD ,LPTSTR);
typedef BOOL (WINAPI *UNIW_GetVolumeInformation) (LPCTSTR ,LPTSTR ,DWORD ,LPDWORD ,LPDWORD ,LPDWORD ,LPTSTR,DWORD);
typedef HMODULE (WINAPI *UNIW_LoadLibrary) (LPCTSTR);
typedef BOOL (WINAPI *UNIW_MoveFile) (LPCTSTR ,LPCTSTR);
typedef HANDLE (WINAPI *UNIW_OpenMutex) (DWORD , BOOL ,LPCTSTR);
typedef VOID (WINAPI *UNIW_OutputDebugString) (LPCTSTR);
typedef BOOL (WINAPI *UNIW_PeekMessage) (LPMSG ,HWND ,UINT ,UINT ,UINT);
typedef BOOL (WINAPI *UNIW_PostMessage) (HWND ,UINT ,WPARAM ,LPARAM);
typedef BOOL (WINAPI *UNIW_RemoveDirectory) (LPCTSTR);
typedef BOOL (WINAPI *UNIW_ReadConsoleInput) (HANDLE , PINPUT_RECORD, DWORD, LPDWORD);
typedef ATOM (WINAPI *UNIW_RegisterClass) (CONST WNDCLASS *);
typedef BOOL (WINAPI *UNIW_SetConsoleTitle) (LPCTSTR);
typedef BOOL (WINAPI *UNIW_SetEnvironmentVariable) (LPCTSTR ,LPCTSTR);
typedef BOOL (WINAPI *UNIW_SetFileAttributes) (LPCTSTR ,DWORD);
typedef BOOL (WINAPI *UNIW_SetVolumeLabel) (LPCTSTR ,LPCTSTR);

typedef struct _tagEuniwInit {

	UNIW_CreateDirectory* CreateDirectoryU;
	UNIW_CreateFile* CreateFileU;
	UNIW_CreateMutex* CreateMutexU;
	UNIW_CreateSemaphore* CreateSemaphoreU;
	UNIW_DeleteFile* DeleteFileU;
	UNIW_FindFirstFile* FindFirstFileU;
	UNIW_FindNextFile* FindNextFileU;
	UNIW_GetCurrentDirectory* GetCurrentDirectoryU;
	UNIW_GetDiskFreeSpace* GetDiskFreeSpaceU;
	UNIW_GetEnvironmentVariable* GetEnvironmentVariableU;
	UNIW_GetFileAttributes* GetFileAttributesU;
	UNIW_GetFullPathName* GetFullPathNameU;
	UNIW_GetDriveType* GetDriveTypeU;
	UNIW_GetModuleFileName* GetModuleFileNameU;
	UNIW_GetModuleHandle* GetModuleHandleU;
	UNIW_GetTempPath* GetTempPathU;
	UNIW_GetVolumeInformation* GetVolumeInformationU;
	UNIW_LoadLibrary* LoadLibraryU;
	UNIW_MoveFile* MoveFileU;
	UNIW_OpenMutex* OpenMutexU;
	UNIW_OutputDebugString* OutputDebugStringU;
	UNIW_ReadConsoleInput* ReadConsoleInputU;
	UNIW_RegisterClass* RegisterClassU;
	UNIW_RemoveDirectory*  RemoveDirectoryU;
	UNIW_SetConsoleTitle* SetConsoleTitleU;
	UNIW_SetEnvironmentVariable* SetEnvironmentVariableU;
	UNIW_SetFileAttributes* SetFileAttributesU;
	UNIW_SetVolumeLabel* SetVolumeLabelU;
	} EUNIWINIT;

void InitEuniw(EUNIWINIT*,TUint);

#ifdef __cplusplus
	}
#endif

#endif
