// f32\inc\f32fsys.h
//
// Copyright (c) 1995-2005 Symbian Ltd. All rights reserved.
//
/**
@file
@publishedPartner
@released
*/

#if !defined(__F32FSYS_H__)
#define __F32FSYS_H__
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif
//
#if defined(_UNICODE)
#define KFileSystemUidValue KFileSystemUidValue16
#define KFileServerUidValue KFileServerUidValue16
#define KFileServerDllUidValue KFileServerDllUidValue16
#else
#define KFileSystemUidValue KFileSystemUidValue8
#define KFileServerUidValueKFileServerUidValue8
#define KFileServerDllUidValueKFileServerDllUidValue8
#endif


const TInt KFileShareLockGranularity=2;
const TInt KAsyncRequestArrayGranularity=2;

/**
@publishedPartner
@released

File system UID value 16.
*/
const TInt KFileSystemUidValue16=0x100039df;




/**
@publishedPartner
@released

File system UID value 8.
*/
const TInt KFileSystemUidValue8=0x1000008f;




/**
@publishedPartner
@released

File server UID value 16.
*/
const TInt KFileServerUidValue16=0x100039e3;




/**
@publishedPartner
@released

File server UID value 8.
*/
const TInt KFileServerUidValue8=0x100000bb;




/**
@publishedPartner
@released

File server DLL UID value 16.
*/
const TInt KFileServerDllUidValue16=0x100039e4;




/**
@publishedPartner
@released

File server DLL UID value 8.
*/
const TInt KFileServerDllUidValue8=0x100000bd;




/**
@publishedPartner
@released

Local file system UID value.
*/
const TInt KLocalFileSystemUidValue=0x100000d6;




/**
@publishedPartner
@released

Estart component UID value.
*/
const TInt KEstartUidValue=0x10272C04;



/**
@publishedPartner
@released
Maximum length of a volume name.
*/
const TInt KMaxVolumeNameLength=11;




/**
@publishedPartner
@released

First local drive indicator.
*/
const TInt KFirstLocalDrive=EDriveC;


const TInt KMaxExtensionCount=2;
//
const TInt KDriveInvalid=-1;
//
_LIT(KMediaPWrdFile, "c:\\sys\\data\\mmcstore");
//




/**
@publishedPartner
@released

Enumeration to specify whether, on opening a file, a new file will be created,
an existing file will be opened or an existing file will be replaced.
*/
enum TFileOpen {EFileOpen,EFileCreate,EFileReplace};




/**
@publishedPartner
@released

The file share mode.
*/
typedef TFileMode TShare;




class CMountCB;
class CFileSystem;
class CFileCB;
class CDirCB;
class CFileShare;
class CSessionFs;
class CFsPlugin;
class TFileBody;

//
class CFsObjectCon;

/**
@publishedPartner
@released
*/
class CFsObject : public CBase

	{
public:
	IMPORT_C CFsObject();
	IMPORT_C virtual TInt Open();
	IMPORT_C virtual void Close();
	IMPORT_C TInt SetName(const TDesC* aName);
	IMPORT_C TName Name() const;
	IMPORT_C virtual TBool IsCorrectThread();
protected:
	void DoClose();
	TInt UniqueID() const;
	inline TInt Inc() {return(User::SafeInc(iAccessCount));}
	inline TInt Dec() {return(User::SafeDec(iAccessCount));}
	IMPORT_C ~CFsObject();
private:
	TInt iAccessCount;
	CFsObjectCon* iContainer;
	HBufC* iName;
friend class CFsObjectCon;
friend class CFsObjectIx;
	};




class CFsRequest;

/**
@publishedPartner
@released
*/
class CFsDispatchObject : public CFsObject
	{
public:
	CFsDispatchObject();
	TInt DriveNumber() {return(iDriveNumber);}
	IMPORT_C void Close();
	IMPORT_C virtual TBool IsCorrectThread();
protected:
	void DoInitL(TInt aDrvNumber);
	void Dispatch();
	~CFsDispatchObject();
private:
	CFsRequest* iRequest;
	TInt iDriveNumber;
friend class TFsCloseObject;
	};




/**
Notifier class must be unique to each thread so one per drive or threaded plugin should be used
allocated in the file system. No longer global

@publishedPartner
@released
*/
NONSHARABLE_CLASS(CAsyncNotifier) : public CBase
	{
public:
	IMPORT_C static CAsyncNotifier* New();
	IMPORT_C ~CAsyncNotifier();
	IMPORT_C TInt Notify(const TDesC& aLine1,const TDesC& aLine2,const TDesC& aButton1,const TDesC& aButton2,TInt& aButtonVal);
	inline void SetMount(CMountCB* aMount) { iMount = aMount; };
protected:
	CAsyncNotifier();
	TInt Connect(); 
private:
	RNotifier iNotifier;
	CMountCB* iMount;
	};




class CProxyDriveFactory;

/**
@publishedPartner
@released
*/
struct TExtensionInfo
	{
	TBool iIsPrimary;
	CProxyDriveFactory* iFactory;
	};




/**
@publishedPartner
@released
*/
struct TDriveExtInfo
	{
	TDriveExtInfo();
	TInt iCount;
	TExtensionInfo iInfo[KMaxExtensionCount];
	};




/**
@publishedPartner
@released

Represents a drive in the file server.

Note that drives may act as substitutes for paths on other drives,
in which case any access to this drive letter will be translated into
a reference to the assigned path. In this way drives can act as short
cuts to paths on other drives.
*/
class TDrive
	{
public:
	TDrive();
	void CreateL(TInt aDriveNumber);
	TInt CheckMount();
	TInt CheckMountAndEntryName(const TDesC& aName);
	TInt FinaliseMount();
	void MountMedia(TBool aForceMount);
	void FlushCachedFileInfoL();
	void DriveInfo(TDriveInfo& anInfo);
	TInt Volume(TVolumeInfo& aVolume);
	TInt SetVolume(const TDesC& aName);
	TInt MkDir(const TDesC& aName);
	TInt RmDir(const TDesC& aName);
	TInt Delete(const TDesC& aName);
	TInt Rename(const TDesC& anOldName,const TDesC& aNewName);
	TInt Replace(const TDesC& anOldName,const TDesC& aNewName);
	TInt Entry(const TDesC& aName,TEntry& anEntry);
	TInt SetEntry(const TDesC& aName,const TTime& aTime,TUint aMask,TUint aVal);
	TInt FileTemp(CFsRequest* aRequest,TInt& aHandle,const TDesC& aPath,TDes& aName,TUint aMode);
	TInt FileOpen(CFsRequest* aRequest,TInt& aHandle,const TDesC& aName,TUint aMode,TFileOpen anOpen);
	TInt DirOpen(CSessionFs* aSession,TInt& aHandle,const TDesC& aName,TUint anAtt,const TUidType& aUidType);
	TInt CheckDisk();
	TInt ScanDrive();
	TInt ReadFileSection(const TDesC& aName,TInt aPos,TAny* aTrg,TInt aLength,const RMessagePtr2& aMessage);
	TInt GetShortName(const TDesC& aLongName,TDes& aShortName);
	TInt GetLongName(const TDesC& aShortName,TDes& aLongName);
	TInt IsFileOpen(const TDesC& aFileName,TBool& anAnswer);
	TInt IsFileInRom(const TDesC& aFileName,TUint8*& aFileStart);
	TInt LockDevice(TMediaPassword& aOld,TMediaPassword& aNew,TBool aStore);
	TInt UnlockDevice(TMediaPassword& aPassword,TBool aStore);
	TInt ClearDevicePassword(TMediaPassword& aPassword);
	TInt EraseDevicePassword();
	TInt FreeDiskSpace(TInt64& aFreeDiskSpace);
	TInt ForceRemountDrive(const TDesC8* aMountInfo,TInt aMountInfoMessageHandle,TUint aFlags);
	TBool IsWriteProtected();
	TInt MountExtension(CProxyDriveFactory* aFactory,TBool aIsPrimary);
	TInt DismountExtension(CProxyDriveFactory* aFactory,TBool aIsPrimary);
	TInt ExtensionName(TDes& aExtensionName,TInt aPos);
	TInt ControlIO(const RMessagePtr2& aMessage,TInt aCommand,TAny* aParam1,TAny* aParam2);	
	void SetAtt(TUint aValue);
	IMPORT_C TUint Att();
	IMPORT_C TBool GetNotifyUser();		
	IMPORT_C void Dismount();		
	IMPORT_C TBool IsWriteableResource() const;	
	IMPORT_C TBool IsCurrentWriteFunction() const; 
	inline TInt GetReason() const;	
	inline void SetChanged(TBool aValue);	
	inline TBool IsChanged();			
	inline TInt DriveNumber() const;
	inline TBool IsMounted() const;
	inline TBool IsLocal();				
	inline TBool IsRom();				
	inline TBool IsRemovable();			
	inline TBool IsSubsted() ;			
	inline CMountCB& CurrentMount() const;
	inline TDrive& SubstedDrive() const;
	inline void SetSubstedDrive(TDrive* aDrive);
	inline HBufC& Subst() const;
	inline void SetSubst(HBufC* aSubst);
	inline CFsObjectCon& Mount() const;	
	inline CFileSystem& FSys();			
	inline CFileSystem*& GetFSys();
	inline TDriveExtInfo& ExtInfo();	
	inline void SetNotifyOn();			
	inline void SetNotifyOff();	
	inline TInt ReservedSpace() const;
	inline void SetReservedSpace(const TInt aReservedSpace);
public:
	void DismountLock();
	TInt DismountUnlock(TBool aReset = EFalse);
	TInt DismountLocked();
	void SetDismountPending(TBool aPending);
	TBool DismountPending();
	void ForceDismount();
	TInt ActiveMounts();
	void ReactivateMounts();
private:
	void MountMediaL(TBool aForceMount,CMountCB*& aMount);
	void SetVolumeL(const TDesC& aName,HBufC*& aBuf);
	void DirOpenL(CSessionFs* aSession,TInt& aHandle,const TDesC& aName,TUint anAtt,const TUidType& aUidType,CDirCB*& aDir);
	void FileOpenL(CFsRequest* aRequest,TInt& aHandle,const TDesC& aName,TUint aMode,TFileOpen anOpen,CFileCB*& aFileCB,CFileShare*& aFileShare);
	TInt CheckMountAndEntryNames(const TDesC& anOldName,const TDesC& aNewName);
	CFileCB* LocateFileByPath(const TDesC& aPath);
	TInt CheckDirectories(const TDesC& anOldName,const TDesC& aNewName);
	void DoEntryL(const TDesC& aName,TEntry& anEntry);
	void ReadSectionL(const TDesC& aName,TInt aPos,TAny* aTrg,TInt aLength,const RMessagePtr2& aMessage);
	TInt ValidateShare(CFileCB& aFile,TShare aReqShare);
	TInt CheckAttributes(const TDesC& aName,TUint& aSetAttMask,TUint& aClearAttMask);
	TBool IsExtensionMounted(CProxyDriveFactory* aFactory);
	CFileCB* LocateFile(const TDesC& aName);
	TBool ReMount();
	IMPORT_C TBool IsDriveThread() const;
	IMPORT_C TBool IsMainThread() const;
	IMPORT_C void DriveFault(TBool aDriveError) const;
	inline void Lock();
	inline void UnLock();
private:
	enum { ENotifyOff = 1, EDismountPending = 2 };	// for iDriveFlags
private:
	TInt iDriveNumber;
	TUint iAtt;
	TBool iChanged;
	TInt iReason;
	TInt iMountNumber;
	CFileSystem* iFSys;
	CMountCB* iCurrentMount;
	TDrive* iSubstedDrive;
	HBufC* iSubst;
	CFsObjectCon* iMount;
	RMutex iLock;
	TDriveExtInfo iExtInfo;	
	TInt iDriveFlags;
	TInt iReservedSpace;
	TInt iDismountLock;
friend class LocalDrives;		// for access to iChanged flag
	};

class CFileCB;
class CDirCB;




/**
@publishedPartner
@released

A file server interface class representing a mount.

An instance of this object is referred to as a mount control block.

A mount control block needs to be created for a specific volume (partition) on
a drive in order to be able to access that volume. Volumes may be permanent
or represent removable media. Note that removable media may also be mounted directly onto
a device with no drive. Volumes can be formatted, unlike drives.

The volume represented is either a currently mounted volume in the system or,
in the case of removable volumes, a volume that has been removed but still has
subsession objects open.

A plug-in file system implements this class.
*/
class CMountCB : public CFsDispatchObject
	{
public:
	IMPORT_C CMountCB();
	IMPORT_C ~CMountCB();
	IMPORT_C TBool operator!=(const CMountCB& aMount) const;
	IMPORT_C TBool MatchEntryAtt(TUint anAtt,TUint aMatt) const;
	IMPORT_C void SetDiskSpaceChange(TInt64 aFreeDiskSpace);
	inline TDrive& Drive() const;
	inline void SetDrive(TDrive* aDrive);
	inline HBufC& VolumeName();
	inline void SetVolumeName(HBufC* aName);
	inline TBool GetNotifyUser() const;
	inline void SetNotifyOn();
	inline void SetNotifyOff();
	inline void IncLock();
	inline void DecLock();
	inline TInt LockStatus();
	inline TBool IsCurrentMount();
	inline TBool Locked();
	inline TInt64 Size();
	
// Pure virtual

    /**
    Attempts to set the mount control block properties using
    the current mount (i.e. volume) on the associated drive.

    The function should set the volume name (iVolumeName),
    the unique ID (iUniqueID) and the volume size (iSize)
    by reading and processing the current mount.

    When aForceMount is set to ETrue, the properties of a corrupt volume should
    be forcibly stored. The classic case of when this is desirable is when
    a corrupt volume needs to be formatted.

    The function should leave, on error detection, with an appropriate error code.

    @param aForceMount Indicates whether the properties of a corrupt
                       volume should be stored.
                       
    @leave KErrCorrupt The properties of the current mount on the drive were
           not successfully mounted due to corruption of volume information,
           assuming that aForceMount is not set.
    */
	virtual void MountL(TBool aForceMount) =0;


    /**
    Checks whether the mount control block represents the current mount on
    the associated drive.

    The function should read mount information from the current volume,
    and check it against the mount information from this mount - typically
    iVolumeName and iUniqueID. If the mount information matches, the function
    should return KErrNone, otherwise it should return KErrGeneral.

    Called by the associated TDrive object when the drive has no current mounts,
    which is the case on first access to the drive and following a volume
    change on a drive associated with removable media. In this circumstance,
    this function is called systematically on every mount control block owned
    by the drive. If ReMount() calls for all existing mount
    control blocks fail, the drive creates a new mount control block and calls
    CMountCB::MountL() on that object; the new object is added to the list of
    mount control blocks owned by the drive.

    @return KErrNone if the mount represented by this object is found to be
            the current mount;
            KErrGeneral if this object is found not to represent
            the current mount;
            otherwise one of the other sytem wide error codes.
    */
	virtual TInt ReMount() =0;


    /**
    Carries out any clean-up necessary for a volume dismount. 

    Dismounting a volume will always succeed, so the function does not need
    to return an error value. Any cached information should be discarded and no
    attempt should be made to access the volume. For removable media it may be
    that the media has already been removed. This function is called when
    a media change is detected.
    */
	virtual void Dismounted() =0;


    /**
    Gets volume information.

    The only information that the function has to supply is the free space,
    TVolumeInfo::iFree, since the remaining members have already been set by
    the calling function.

    The function should leave, on error detection, with
    an appropriate error code.

    @param aVolume On return, a reference to the filled volume
                   information object.
    */
	virtual void VolumeL(TVolumeInfo& aVolume) const =0;


    /**
    Sets the volume name for the mount, thus writing the new volume name
    to the corresponding volume.

    This function should leave on error detection.

    @param aName A reference to a descriptor containing the new volume name.

    @leave KErrBadName If the specified volume name is longer than the maximum
           allowed length for a volume name
    */
	virtual void SetVolumeL(TDes& aName) =0;


    /**
    Creates a new directory on the mount.

    The directory to be created is identified through its full name in aName.
    The full name is in the form:
    @code
    \\dirA\\dirB\\dirC\\dirD
    @endcode
    where dirD is the new directory to be created in \\dirA\\dirB\\dirC\\.
    This means that dirC is the leaf directory in which dirD will be created.

    The function should leave, on error detection, with an appropriate
    error code.

    @param aName A reference to a descriptor containing the full name of
                 the directory to be created.
                 
    @leave  KErrPathNotFound Part of the path in aName does not exist.
    @leave  KErrAlreadyExists dirD already exists in \\dirA\\dirB\\dirC\\
    @leave  KErrAccessDenied dirD already exists but is not a directory.
    @leave  KErrDirFull There is no room in \\dirA\\dirB\\dirC\\ for the new entry,
            which is especially applicable to the root directory.
    */
	virtual void MkDirL(const TDesC& aName) =0;


    /**
    Removes the directory specified by aName (its full name) from the volume.

    The directory specified by aName is in the form:
    @code
    \\dirA\\dirB\\dirC\\dirD
    @endcode
    where dirD is the directory to be removed from \\dirA\\dirB\\dirC\\.
    This means that dirC is the leaf directory from which dirD should be removed.

    The function can assume that the directory exists and is not read-only. 

    The function should leave with a suitable error code if it cannot complete
    successfully for any reason. 
    
    @param aName A reference to a descriptor containing the full name of
                 the directory to be removed.
    
    @leave KErrInUse dirD contains entries other than the parent (..)
           and current (.) entries.
    */
	virtual void RmDirL(const TDesC& aName) =0;


    /**
    Deletes the specified file from the mount.

    The function can assume that the file is closed.

    The file name specified by aName is of the form:
    @code
    \\dirA\\dirB\\dirC\\file.ext
    @endcode
    
    The extension is optional.

    The function should leave on error detection, with
    an appropriate error code.

	@param aName A reference to a descriptor containing the full path name
	             of the file that will be removed.
	
	@leave KErrAccessDenied aName specifies a file whose attributes state that
	       the file is read-only or aName specifies a directory.
    */
	virtual void DeleteL(const TDesC& aName) =0;


    /**
    Renames or moves a single file or directory on the mount.

    It can be used to move a file or directory since both
    anOldName and anNewName specify the respective entries with full names;
    for example,
    @code
    \\dirA\\dirB\\dirC\\oldEntryName
    @endcode
    
    and
    
    @code
    \\dirE\\dirF\\dirG\\newEntryName
    @endcode

    If oldEntryName is a file, it can be assumed that it is closed.
    If oldEntryName is a directory, it can be assumed that there are no
    open files in this directory. Furthermore, if newEntryName specifies
    a directory, it can be assumed that it is not a subdirectory of oldEntryName.

    The function should leave with an appropriate error code if it cannot
    complete successfully for any reason. 

	@param anOldName A reference to a descriptor containing the full entry
	                 name of the entry to be renamed.

	@param anNewName A reference to a descriptor containing the new full entry
	                 name for the entry to be renamed.
 
    @leave KErrAlreadyExists The new entry already exists.
    */
	virtual void RenameL(const TDesC& anOldName,const TDesC& anNewName) =0;


    /**
    Replaces one file on the mount with another.

    The function can assume that both anOldName and, if it exists, anNewName
    contain the full file names of files, and that these files are not open.

    If the file aNewName does not exist it should be created.

    The file anOldName should have its contents, attributes, and the universal
    date and time of its last modification, copied to the file aNewName,
    overwriting any existing contents and attribute details.
    Finally anOldName should be deleted.

    The function should leave with an appropriate error code if it cannot
    complete successfully for any reason.

    @param anOldName A reference to a descriptor containing the full file name
                     of the file to replace the file specified by anNewName
    @param anNewName A reference to a descriptor containing the new full file
                     name for the entry to be replaced.
    */
	virtual void ReplaceL(const TDesC& anOldName,const TDesC& anNewName) =0;


    /**
    Gets the entry details for the specified file or directory.

    anEntry should be filled with details from the file or directory with the
    full name aName. aName is of the form
    @code
    \\dirA\\dirB\\dirC\\entry.
    @endcode
    
    Note that anEntry.iType (the entry UID) should only be set for a file whose
    size is greater than or equal to sizeof(TCheckedUid).

    The function should leave with an appropriate error code if it cannot
    complete successfully for any reason.

    @param aName   A reference to a descriptor containing the full name of
                   the entry whose details are required.
    @param anEntry On return, a reference to the filled entry object.
    
    @leave KErrPathNotFound The entry, aName, cannot be found.
    */
	virtual void EntryL(const TDesC& aName,TEntry& anEntry) const =0;


    /**
    Sets entry details for a specified file or directory.

    The entry identfied by the full name descriptor aName should have
    its modification time and its attributes mask updated as required.

    The entry receives a new universal modified time from aTime.
    The entry attributes are set with aSetAttMask and cleared
    with aClearAttMask:
    the bits that are set in aSetAttMask should be set
    in the entry attribute mask;
    the bits that are set in aClearAttMask
    should be cleared from the entry attribute mask.

    The function can assume that aSetAttMask and aClearAttMask do not change
    the type of attribute (i.e. volume or directory). Furthermore, if aName
    specifies a file, it can be assumed that this file is closed.

    The function should leave with an appropriate error code on error detection.
    
    @param aName         A reference to a descriptor containing the full name of
                         the entry to be updated.
    @param aTime         A reference to the time object holding the new universal
                         modified time for aName.
    @param aSetAttMask   Attribute mask for setting the entry's attributes.
    @param aClearAttMask Attribute mask for clearing the entry's attributes.
    */
	virtual void SetEntryL(const TDesC& aName,const TTime& aTime,TUint aSetAttMask,TUint aClearAttMask) =0;


    /**
    Customises the opening of a new or existing file on the mount.

    The function is called internally (via TDrive::FileOpen()) as a result of
    a call by the client, and the file is created, if necessary, and opened by
    the calling function. However this function implements any replacement
    functionality, as well as any other behaviour particular to the file system.

    If anOpen specifies EFileReplace (rather than EFileCreate or EFileOpen) then,
    if replacement functionality is required, the data contained in the file
    should be discarded, the archive attribute should be set, and the size of
    the file should be set to zero. Note that it can be assumed that if anOpen
    specifies EFileReplace then the file already exists.

    After successful completion of the function, the file control block pointer
    will be added to the file server's global files container.

    The function should leave with a suitable error code if it cannot be completed
    successfully.

    @param aName  The full name of the file that will be opened.
    @param aMode  The file share mode. The following share modes are available:
                  EFileShareExclusive;
                  EFileShareReadersOnly;
                  EFileShareAny;
                  EFileShareReadersOrWriters;
                  EFileStream;
                  EFileStreamText;
                  EFileRead;
                  EFileWrite.
    @param anOpen IndicatES how the file will be opened. It can be one of
                  the following:
                  EFileOpen;
                  EFileCreate;
                  EFileReplace.
    @param aFile  Pointer to the file control block which will, on success,
                  represent the open file.
                  
    @leave KErrAccessDenied aName may specify a directory, or the function may
           be attempting to open a file on a ROM drive.
    */
	virtual void FileOpenL(const TDesC& aName,TUint aMode,TFileOpen anOpen,CFileCB* aFile) =0;


    /**
    Customises the opening of a directory on the mount.

    The function is called internally, and the directory will have been created
    and initialised by the calling function. Any customisation specific to
    a file system should be implemented in this function.

    Note that aName is of the form
    @code
    \\dirA\\dirB\\dirC\\file.ext
    @endcode
    
    where \\dirA\\dirB\\dirC\\ is the directory to be opened and file.ext is
    an optional entry name and extension.

    After successful completion of the function, the directory control block
    pointer will be added to the file server global directories container.

    The function should leave with a suitable error code if it cannot complete
    successfully for any reason.

    @param aName A reference to a descriptor containing the full name of
                 the directory that will be opened.
    @param aDir  Points to a directory control block which will, on success,
                 represent the open directory.
    */
	virtual void DirOpenL(const TDesC& aName,CDirCB* aDir) =0;


    /**
    Reads the specified length of data from the specified position on
    the volume directly into the client thread.

    It can be assumed that if this function is called,
    then there has been a successful mount.

    This function should leave with an appropriate error code when
    an error is detected.

    @param aPos     Start position in the volume for the read operation,
                    in bytes.
    @param aLength  The number of bytes to be read.
    @param aTrg     A pointer to the buffer into which data is to be read.
    @param anOffset The offset at which to start adding data to the read buffer.
    @param aMessage
    */
	virtual void RawReadL(TInt64 aPos,TInt aLength,const TAny* aTrg,TInt anOffset,const RMessagePtr2& aMessage) const = 0;


    /**
    Writes a specified length of data from the client thread to the volume
    at the specified position.

    It can be assumed that if this function is called, then there has been
    a successful mount.

    This function should leave with an appropriate error code when
    an error is detected.

    @param aPos     Start position in the volume for the write operation,
                    in bytes.
    @param aLength  The number of bytes to be written.
    @param aSrc     Pointer to the buffer from which data will be written.
    @param anOffset The offset in the buffer at which to start writing data.
    @param aMessage
    */
	virtual void RawWriteL(TInt64 aPos,TInt aLength,const TAny* aSrc,TInt anOffset,const RMessagePtr2& aMessage) = 0;


    /**
    Gets the short name of the file or directory with the given full name.

    This function is used in circumstances where a file system mangles
    Symbian OS natural names, in order to be able to store them on
    a file system that is not entirely compatible.

    The function should leave with a suitable error code if it cannot complete
    successfully for any reason.

	@param aLongName  A reference to a descriptor containing the full name
	                  of the entry.
	@param aShortName On return, a reference to a descriptor containing
	                  the short name of the entry.
    
    @leave KErrNotFound The entry specified by its long name cannot be found.
    */
	virtual void GetShortNameL(const TDesC& aLongName,TDes& aShortName) = 0;


    /**
    Gets the long name of the file or directory associated with
    the given short name.

    This function is used in circumstances where a file system mangles
    Symbian OS natural names in order to be able to store them on
    a file system that is not entirely compatible. 

    The function should leave with a suitable error code if it cannot complete
    successfully for any reason.

	@param aShorName  A reference to a descriptor containing the short name
	                  of the entry.

    @param aLongName  On return, a reference to a descriptor containing
                      the long name of the entry.

    @leave KErrNotFound The entry specified by its short name cannot be found.
    */
	virtual void GetLongNameL(const TDesC& aShorName,TDes& aLongName) = 0;


    /**
    Reads a specified section of the file, regardless of the file's lock state.

    The function should leave with a suitable error code if it cannot complete
    successfully for any reason.
    
    @param aName   A reference to a descriptor containing the full name of
                   the file to be read from
    @param aPos    The byte position to start reading from.
    @param aTrg    A pointer to the buffer into which data is to be read.
    @param aLength The length of data to be read, in bytes.
    @param aMessage

	@leave KErrEof aPos is past the end of the file.
    */
	virtual void ReadSectionL(const TDesC& aName,TInt aPos,TAny* aTrg,TInt aLength,const RMessagePtr2& aMessage)=0;


// virtual

    /**
    Checks the integrity of the file system on the volume and returns an
    appropriate error value. 

    The default implementation must be overridden by a derived class.
    
    @return KErrNone if the file system is stable; otherwise one of
            the other system wide error codes.
            The default implementation returns KErrNotSupported.
    */
	virtual TInt CheckDisk() {return(KErrNotSupported);}
	
	
	/**
    Scans through and corrects errors found in the volume.

    The default implementation must be overridden by a derived class.
    
    @return KErrNone if no errors are found or all errors are corrected;
            otherwise one of the other system wide error codes.
            The default implementation returns KErrNotSupported.
    */
	virtual TInt ScanDrive() {return(KErrNotSupported);}
	IMPORT_C virtual void IsFileInRom(const TDesC& aFileName,TUint8*& aFileStart);
	
	
	/**
    */
	virtual TInt ControlIO( const RMessagePtr2& /*aMessage*/,TInt /*aCommand*/,TAny* /*aParam1*/,TAny* /*aParam2*/)  {return(KErrNotSupported);}


	/**
	Locks a media which supports password protection and replaces
	the old password with a new one. 

    If aStore is set to ETrue, then the new password should be saved to
    the password store file, KMediaPWrdFile, using the exported file server
    function WriteToDisk(). 

    The password file is used to initialise the password store on boot up,
    so the user does not need to be prompted for the password again if
    it is saved here.

    The default implementation must be overridden in a derived class.

    @param aOld   A reference to the old password.
    @param aNew   A reference to the new password.
    @param aStore ETrue if the new password is to be saved to 
                  the password file store; EFalse if not.

    @return KErrNone if successful; otherwise another of the system wide
            error codes. The default implementation returns KErrNotSupported.
    */
	virtual TInt Lock(TMediaPassword& /*aOld*/,TMediaPassword& /*aNew*/,TBool /*aStore*/) {return(KErrNotSupported);}


	/**
	Unlocks a media which supports password protection.

    If aStore is set to ETrue then the password should be saved to
    the password store file specified by KMediaPWrdFile using the exported file
    server function WriteToDisk().

    The password file is used to initialise the password store on boot up,
    so the user does not need to be prompted for the password again if
    it is saved here.

    The default implementation must be overridden in a derived class.

    @param aPassword A reference to the password.
    @param aStore    ETrue if the password is to be saved to
                     the password store file; EFalse otherwise.
                     
    @return KErrNone if successful; otherwise another of the system wide
            error codes. The default implementation returns KErrNotSupported.                     
    */
	virtual TInt Unlock(TMediaPassword& /*aPassword*/,TBool /*aStore*/) {return(KErrNotSupported);}


	/**
	Clears a password from a media that supports write protection. 

    The default implementation must be overridden in a derived class.

    @param aPassword A reference to the password to be cleared.

    @return KErrNone if successful; otherwise another of the system wide
            error codes. The default implementation returns KErrNotSupported.
    */
	virtual TInt ClearPassword(TMediaPassword& /*aPassword*/) {return(KErrNotSupported);}


	/**
    */
	virtual TInt ForceRemountDrive(const TDesC8* /*aMountInfo*/,TInt /*aMountInfoMessageHandle*/,TUint /*aFlags*/) {return(KErrNotSupported);}

    
	virtual	void FinaliseMountL(){return;}


	/**
	Erase a password from a media that supports write protection. 

    The default implementation must be overridden in a derived class.

    @return KErrNone if successful; otherwise another of the system wide
            error codes. The default implementation returns KErrNotSupported.
    */
	virtual TInt ErasePassword() {return(KErrNotSupported);}

protected:
	inline void SetMountNumber(TInt aMountNumber);
	inline void SetDismounted(TBool aDismounted=ETrue);
	inline TInt MountNumber() const;
	inline TBool IsDismounted() const;

	void InitL(TInt aDrvNumber);
	
	/**
	Return a pointer to a specified interface extension - to allow future extension of this class without breaking
	binary compatibility.
	@param aInterfaceId Interface identifier of the interface to be retrieved.
	@param aInterface A reference to a pointer that retrieves the specified interface.
	@param aInput An arbitrary input argument.
	@return KErrNone If the interface is supported, KErrNotSupported otherwise.
	*/	
	IMPORT_C virtual TInt GetInterface(TInt aInterfaceId,TAny*& aInterface,TAny* aInput);

protected:

    /**
    Unique mount number set by the TDrive object representing the drive on
    which the object resides.
    */
	TInt iMountNumber;


    /**
    Unique ID from the volume. Set in MountL().
    
    @see CMountCB::MountL
    */
	TUint iUniqueID;


    /**
    Size of the volume. First set in MountL().

    @see CMountCB::MountL
    */
	TInt64 iSize;


    /**
    A list of all open files on that mount.
    Set by the TDrive object representing the drive of which the mount resides.
    */
	TDblQue<CFileCB> iMountQ;
	friend class TDrive;
private:
	TInt iLockMount;
	TDrive* iDrive;
	HBufC* iVolumeName;
//
	TAny* CMountCB_Reserved;
	};




class CFileShare;

/**
@publishedPartner
@released

File share lock

The lock specifies the lowest and highest position in the file to be locked.

Note that files may have many locks on it, but overlapping sections cannot
be locked.

This is used by a file control block, a CFileCB object.

@see CFileCB
*/
struct SFileShareLock
	{
	/**
	The owning file share object.
    */
	CFileShare* owner;


	/**
	The start of the section of the file to be locked.
	*/
	TInt posLow;


	/**
	The end of the section of the file to be locked.
    */
	TInt posHigh;
	};


/**
@internalTechnology
*/
class TAsyncReadRequest
	{
public:
	TAsyncReadRequest(TInt aEndPos, CFileShare* aOwningShareP, CFsRequest* aRequestP);
	TBool CompleteIfMatching(CFileShare* aOwningShareP, TRequestStatus* aStatusP, TInt aError);
private:
	TAsyncReadRequest();
public:
	TInt iEndPos;					// The request is completed file length >= iEndPos.
	CFileShare* iOwningShareP;		// The share that owns this outstanding request.
	const TRequestStatus* iStatusP;	// Used to identify the request when cancelling.
	CSessionFs* iSessionP;			// The owning session of the original request.
	RMessage2 iMessage;				// The message to be completed when data is available.
	};

/**
@publishedPartner
@released

A file server interface class representing an open file.

An instance of this object is referred to as a file control block.

A file control block needs to be created for a specific file to be able to
access that file within a directory.

A plug-in file system implements this class.
*/
class CFileCB : public CFsDispatchObject
	{
public:
	IMPORT_C CFileCB();
	IMPORT_C ~CFileCB();
	IMPORT_C void InitL(TDrive* aDrive,TDrive* aCreatedDrive,HBufC* aName,RArray<SFileShareLock>* aLock);
	inline void SetMount(CMountCB * aMount);
	inline TDrive& Drive();
	inline TDrive& CreatedDrive();
	inline CMountCB& Mount();
	inline HBufC& FileName();
	inline HBufC& FileNameF();
	inline RArray<SFileShareLock>& Lock();
	inline TInt UniqueID() const;
	TInt FindLock(TInt aPosLow,TInt aPosHigh);
	TInt AddLock(CFileShare* aFileShare,TInt aPos,TInt aLength);
	TInt RemoveLock(CFileShare* aFileShare,TInt aPos,TInt aLength);
	TInt CheckLock(CFileShare* aFileShare,TInt aPos,TInt aLength);
	void RemoveLocks(CFileShare* aFileShare);
	inline TShare Share();
	inline void SetShare(TShare aShare);
	inline TInt Size();
	inline void SetSize(TInt aSize);
	inline TInt Att();
	inline void SetAtt(TInt aAtt);
	inline TTime Modified();
	inline void SetModified(TTime aModified);
	inline TBool FileCorrupt();
	inline void SetFileCorrupt(TBool aFileCorrupt);
	inline TBool BadPower();
	inline void SetBadPower(TBool aBadPower);
	inline TUint32 NameHash() const;

// Pure virtual
    
    
    /**
    Renames the file with the full file name provided.

    Because the full name of the file includes the path, the function can
    also be used to move the file.

    It can be assumed that no other sub-session has access to the file:
    i.e. the file has not been opened in EFileShareAny share mode.
    It can also be assumed that the file has been opened for writing. 

    The function should leave with KErrAlreadyExists if aNewName already exists.
    An appropriate error code should also be generated if the function leaves
    before completion for any other reason.

	@param aNewName The new full name of the file.
	
	@see CFileCB::iFileName
    */
	virtual void RenameL(const TDesC& aNewName) =0;
	
	
    /**
    Reads a specified number of bytes from the open file starting at
    the specified postition, and writes the result into a descriptor.

    It can be assumed that aPos is inside the file and aLength > 0.
    The file should only be read up to its end regardless of
    the value of aPos + aLength. The number of bytes read should be stored
    in aLength on return.

    If the function leaves before completion for any reason it should generate
    an appropriate error code, and in this situation,
    the arguments are not valid on return.

	@param aPos     Represents a position relative to the start of the file
	                where ReadL() should start to read.
	@param aLength  On entry, specifies the number of bytes to be read
	                from the file. On return, this should contain the number
	                of bytes read, but this is not valid if the function leaves.
	@param aDes     Pointer to a descriptor into which the data should be written.
	@param aMessage
    */
    virtual void ReadL(TInt aPos,TInt& aLength,const TAny* aDes,const RMessagePtr2& aMessage) =0;
	
	
    /**
    Writes data to the open file.

    iModified and iSize are set by the file server after this function
    has completed successfully.

    It can be assumed that aPos is within the file range and aLength > 0.
    When aPos + aLength is greater than the file size then the file should
    be enlarged using SetSizeL(). The number of bytes written should be
    returned through the argument aLength. 

    If the function leaves before completion for any reason it should generate
    an appropriate error code, and in this situation the arguments are
    not valid on return.

   	@param aPos     Represents a position relative to the start of the file
   	                where WriteL() should start to write.
	@param aLength  Specifies the number of bytes to be written to the file.
	                On return, the number of bytes written, but this is not
	                valid if the function leaves.
	@param aDes     Pointer to a descriptor containing the data to be written
	                to the file.
	@param aMessage 
	
	@see CFileCB::iModified
	@see CFileCB::iSize
	@see CFileCB::SetSizeL
	
    @leave KErrDiskFull The operation cannot be completed because the disk is full.
    */
	virtual void WriteL(TInt aPos,TInt& aLength,const TAny* aDes,const RMessagePtr2& aMessage) =0;
	
	
    /**
    Extends or truncates the file by re-setting the file size.

    The function should not change iModified and iSize attributes of
    the file object: this is done by the file server.
    If the file is extended, nothing should be written in the extended area.

    The function should leave with a suitable error code on error detection.

    @param aSize The new file size in number of bytes.
    
    @leave KErrDiskFull The operation cannot be completed because the disk is full.
    
    @see CFileCB::iModified
	@see CFileCB::iSize
    */
	virtual void SetSizeL(TInt aSize) =0;
	
	
    /**
    Sets the attribute mask, iAtt, and the modified time of the file, iModified.

    If aMask|aVal does not equal zero, then aMask should be OR'ed with iAtt,
    whilst the inverse of aVal should be AND'ed with iAtt.
    If the modified flag is set in aMask then iModified should be set to aTime.

    The function should leave with a suitable error code on error detection.

	@param aTime The new modified time, if the modified flag is set in aMask.
	@param aMask Bit mask containing bits set (to 1) that are to be set (to 1)
	             in iAtt.
	@param aVal  Bitmask containing bits set (to 1) that are to be unset (to 0)
	             in iAtt.
	
    @see CFileCB::iModified
	@see CFileCB::iAtt
    */
    virtual void SetEntryL(const TTime& aTime,TUint aMask,TUint aVal) =0;
	
	
    /**
    Flushes, to disk, the cached information necessary for the integrity
    of recently written data, such as the file size.

    The function should leave with a suitable error code on error detection.
    */
	virtual void FlushDataL() =0;
	
	
    /**
    Flushes, to disk, all cached file data (e.g. attributes, modification time,
    file size). 

    The modified bit in the file attributes mask should be cleared if
    the flush was successful.

    The function should leave with a suitable error code on error detection.
    */
	virtual void FlushAllL() =0;
	IMPORT_C virtual TInt Address(TInt& aPos) const;
	IMPORT_C void SetArchiveAttribute();

protected:
	
	/**
	Return a pointer to a specified interface extension - to allow future extension of this class without breaking
	binary compatibility.
	@param aInterfaceId Interface identifier of the interface to be retrieved.
	@param aInterface A reference to a pointer that retrieves the specified interface.
	@param aInput An arbitrary input argument.
	@return KErrNone If the interface is supported, KErrNotSupported otherwise.
	*/	
	IMPORT_C virtual TInt GetInterface(TInt aInterfaceId,TAny*& aInterface,TAny* aInput);
	
private:

	void DemoteShare(CFileShare* aFileShare);
	void PromoteShare(CFileShare* aFileShare);

	RArray<TAsyncReadRequest>& AsyncReadRequests();
	TInt AddAsyncReadRequest(CFileShare* aFileShareP, TInt aPos, TInt aLength, CFsRequest* aRequestP);
	TInt CancelAsyncReadRequest(CFileShare* aShareP, TRequestStatus* aStatusP);
	void NotifyAsyncReaders();

protected:

    /**
    Inititally, the mode that the file was opened with, which defines the level
    of access allowed to the file. Set by the TDrive object
    (representing the drive on which the file resides) when the file
    control block is created.
    */
	TShare iShare;


    /**
    The size of the file.
    */
    TInt iSize;


    /**
    The attributes of the file.
    */
	TInt iAtt;


    /**
    The universal time at which the file was last modified.
    */
	TTime iModified;


    /**
    Indicates whether the file that the object represents is corrupt:
    true if it is corrupt, false otherwise.
    */
	TBool iFileCorrupt;


    /**
    Indicates whether a recent access to the file that the object represents
    failed due to KErrBadPower.
    */
	TBool iBadPower;

public:

	/**
	The full name of the file, including drive and extensions.
	*/
	HBufC* iFileName;

	/**
	The full name of the file, including drive and extensions - Folded.
	*/
	HBufC* iFileNameF;

private:
	TUint32	iNameHash;
	TDrive* iCreatedDrive;
	TDrive* iDrive;
	CMountCB* iMount;
	RArray<SFileShareLock>* iLock;
	TDblQueLink iMountLink;
	
private:
	TFileBody* iBody;

	friend class TDrive;
	friend class CMountCB;
	friend class CFileShare;
	friend class TFsFileRead;
	friend class TFsFileWrite;
	friend class TFsFileSetSize;
	friend class TFsFileReadCancel;
	};




/**
@publishedPartner
@released
*/
NONSHARABLE_CLASS(CFileShare) : public CFsDispatchObject
	{
public:
	CFileShare(CFileCB* aFileCB);
	~CFileShare();
	TInt CheckMount();
	void InitL();
	inline CFileCB& File();
public:
	TUint iMode;
	TInt iPos;
private:
	CFileCB* iFile;
	};




/**
@publishedPartner
@released

A file server interface class representing an open directory

An instance of this object is referred to as a directory control block.

A directory control block must be created for a specific directory to access
that directory within a volume.

A plug-in file system implements this class.
*/
class CDirCB : public CFsDispatchObject
	{
public:
	IMPORT_C CDirCB();
	IMPORT_C ~CDirCB();
	TInt CheckMount();
	IMPORT_C void InitL(TDrive* aDrive);
	inline void SetMount(CMountCB * aMount){iMount=aMount;};
	inline TDrive& Drive();
	inline CMountCB& Mount();
	inline TBool Pending();
	inline void SetPending(TBool aPending);
	

    /**
    Gets information from the first suitable entry in the directory,
    starting from the current read position.

    The function should read successive entries until a suitable entry is found.
    An entry is suitable if the entry attributes match the criteria set by this
    object's attributes, which are set on initialisation.
    For example, if the directory control block has the attribute
    KEntryAttMaskSupported, and the file has the attribute KEntryAttVolume,
    then the entry will be deemed unsuitable and the next entry will be read.

    This function is called by the file server.

    If, on return, the entry's full file name, TEntry::iName, is longer than
    the maximum buffer size, then the entry cannot be returned to the client.
    In this case the file server will set iPending to true and will call
    StoreLongEntryName() before calling this function again.
    In this case (when iPending is true), the function should re-read
    the last entry to be read; it should also set iPending to false and
    should not advance the current read position.

    The time stored in the iModified member of anEntry should not be converted,
    but left as UTC time.

    When storing the iName member of anEntry, the current (.),
    or parent marker (..) in the directory should not be returned.

    If the KEntryAttAllowUid flag is set in the iAtt member of anEntry, then
    the entry UID type of an entry will be read. If, on reading the UID from
    a file, KErrCorrupt is generated, because the file is corrupt,
    ReadL() should not leave with this error message, but should return
    as normal.
    If any other errors are raised the function should leave.

    All of the properties of a TEntry, other than the UID types, are always read.

    ReadL() should leave with a suitable error code if it cannot complete
    successfully for any reason. 

    @param anEntry Entry information object.
    */
	virtual void ReadL(TEntry& anEntry) =0;
	
public:
	IMPORT_C virtual void StoreLongEntryNameL(const TDesC& aName);
	
protected:
	/**
	Return a pointer to a specified interface extension - to allow future extension of this class without breaking
	binary compatibility.
	@param aInterfaceId Interface identifier of the interface to be retrieved.
	@param aInterface A reference to a pointer that retrieves the specified interface.
	@param aInput An arbitrary input argument.
	@return KErrNone If the interface is supported, KErrNotSupported otherwise.
	*/	
	IMPORT_C virtual TInt GetInterface(TInt aInterfaceId,TAny*& aInterface,TAny* aInput);
	
protected:
    /**
    Bitmask of the attributes of interest.

    Set using the the TDrive friend class instance representing
    the directory's drive after the object is made.
    */
	TUint iAtt;
	
	
	/**
	Set after construction using the TDrive friend class instance representing
	the directory's drive.
	*/
	TUidType iUidType;


    /**
    Flag to indicate whether preceding entry details should be returned when
    multiple entries are being read.
    */
	TBool iPending;
	friend class TDrive;
private:
	TDrive* iDrive;
	CMountCB* iMount;
	TUint32 iReserved;				// Reserved for future expansion
	};




/**
@publishedPartner
@released

A file server interface class representing a format operation on a disk.

An instance of this object is referred to as a format control block.

The type of format operation to be applied depends on the type of disk,
and is stored in iMode. Each format operation has a number of steps and
is kept track of using iCurrentStep.

A format control block needs to be created for a specific mount control block
for the disk controlled via that mount to be formatted.

A plug-in file system provides an implementation of this class.
*/
class CFormatCB : public CFsDispatchObject
	{
public:
	IMPORT_C CFormatCB();
	IMPORT_C ~CFormatCB();
	IMPORT_C TInt CheckMount();
	void InitL(TDrive* aDrive,TFormatMode aMode);
    void SetSpecialInfo(const TDesC8& aInfo);
	inline TDrive& Drive();
	inline CMountCB& Mount();
	inline TFormatMode Mode();
	inline TInt& CurrentStep();
// Pure virtual

    /**
    Performs a formatting step on the drive.

    The step performed should depend on the values of iMode and iCurrentStep. 

    It can be assumed that there are no resources open on the mount,
    that the media is formattable, and that the media is not write protected.

    If iMode == EQuickFormat, then only meta data is to be written.
    This should be carried out in a single step, with iCurrentStep set
    to zero on completion.

    If iMode != EQuickFormat, then the format step performed by
    this function should depend on iCurrentStep. When the function
    returns with iCurrentStep set to zero, the formatting of the drive is complete.

    On error detection, the function should leave with an appropriate error code.

    @see CFormatCB::iMode
    @see CFormatCB::iCurrentStep
    */
	virtual void DoFormatStepL() =0;
	
protected:
	/**
	Return a pointer to a specified interface extension - to allow future extension of this class without breaking
	binary compatibility.
	@param aInterfaceId Interface identifier of the interface to be retrieved.
	@param aInterface A reference to a pointer that retrieves the specified interface.
	@param aInput An arbitrary input argument.
	@return KErrNone If the interface is supported, KErrNotSupported otherwise.
	*/	
	IMPORT_C virtual TInt GetInterface(TInt aInterfaceId,TAny*& aInterface,TAny* aInput);
		
protected:

    /**
    The stage the current format operation has reached.
    */
	TInt iCurrentStep;
	
	
	/**
	The mode of the format operation.
	
	This is set by the file server when the format control block is created.
	*/
	TFormatMode iMode;

    /**
    Buffer containing user-specified format parameters.
    */
    TSpecialFormatInfoBuf iSpecialInfo;
private:
	TDrive* iDrive;
	CMountCB* iMount;
	TUint32 iReserved;				// Reserved for future expansion
	};




/**
@publishedPartner
@released

A file server interface class representing a raw disk.

An instance of this object is referred to as a raw disk control block.

This is not an abstract base class and does not need to be derived from
when implementing a file system. This is because direct disk access is
implemented by the file server directly calling RawReadL() and RawWriteL()
from the derived CMountCB object of the file system.
*/
NONSHARABLE_CLASS(CRawDiskCB) : public CFsDispatchObject
	{
public:
	CRawDiskCB();
	~CRawDiskCB();
	void InitL(CMountCB* aMount,TBool aIsWriteProtected);
	inline CMountCB& Mount();
	inline TDrive& Drive();
	inline TBool IsWriteProtected() const;
	inline void SetChanged();
private:
	enum { EWriteProtected = 1, EChanged = 2 };
	inline void SetWriteProtected();
	inline TBool IsChanged() const;
private:
	CMountCB* iMount;
	TBool iFlags;
	};




/**
@publishedPartner
@released

A file server interface class, representing the factory class for a file system.

A plug-in file system implements this class.

Creates objects derived from CMountCB, CFileCB, CDirCB and CFormatCB.

@see CMountCB
@see CFileCB
@see CDirCB
@see CFormatCB
*/
class CFileSystem : public CFsObject
	{
public:
	IMPORT_C CFileSystem();
	IMPORT_C ~CFileSystem();
	IMPORT_C virtual TInt Remove();
	IMPORT_C virtual TBool QueryVersionSupported(const TVersion& aVer) const;
	IMPORT_C virtual TBool IsExtensionSupported() const;
	IMPORT_C void SetLibrary(RLibrary aLib);
	IMPORT_C RLibrary Library() const;
// Pure virtual
    
    
    /**
    Installs the file system.

    The function should set the name of the file system object through a call
    to CObject::SetName(), thus making it accessible, internally, 
    using FileSystems->FindByFullName(). This enables the file server
    to find and handle installed file systems. 
    The function should also set the file system version.
    The version is determined by the file system implementation.
    It is used in calls to CFileSystem::QueryVersionSupported().

    This function is called as a result of a call to RFs::AddFileSystem().
    
    @return KErrNone if succesful; otherwise one of the other  system-wide error
    codes.
    
    @see RFs::AddFileSystem
    @see CObject::SetName
    @see RFs
    @see CObject
    */
	virtual TInt Install() =0;
	
		
	/**
	Creates a new mount control block, a CMountCB derived object. 

    On success, a pointer to the new mount object should be returned,
    otherwise the function should leave.

	@return A pointer to the new mount object.

    @see CMountCB
	*/
	virtual CMountCB* NewMountL() const =0;
	
	
	/**
	Creates a new file control block, i.e. a CFileCB derived object.

    On success, a pointer to the new file object should be returned,
    otherwise the function should leave.

    @return A pointer to the new file object.
    
    @see CFileCB
	*/
	virtual CFileCB* NewFileL() const =0;
	
	
	/**
	Creates a new directory control block, i.e. a CDirCB derived object.

    On success, a pointer to the new directory control block should be returned,
    otherwise the function should leave.

    @return A pointer to the new directory object.
    
    @see CDirCB
	*/
	virtual CDirCB* NewDirL() const =0;
	
	
	/**
	Creates a new volume format control block, i.e. a CFormatCB derived object.

    On success, a pointer to the new volume format control block should be returned,
    otherwise the function should leave.

    @return A pointer to the new volume format object.
    
    @see CFormatCB
	*/
	virtual CFormatCB* NewFormatL() const =0;
	
	
	/**
	Retrieves drive information.

    The function should set anInfo.iMediaAtt and anInfo.iType according to
    the specified drive number.

    Note that anInfo.iDriveAtt and anInfo.iBatteryState will already have been
    set by the calling function.

    The function can obtain the necessary information by calling
    the appropriate TBusLocalDrive::Caps() function using the argument aDriveNumber.

	@param anInfo       On return, contains the drive information.
	@param aDriveNumber The drive number.
	*/
	virtual void DriveInfo(TDriveInfo& anInfo,TInt aDriveNumber) const =0;
		
//#ifndef __DATA_CAGING__
    virtual TInt DefaultPath(TDes& aPath) const;
//#endif

protected:	
	/**
	Return a pointer to a specified interface extension - to allow future extension of this class without breaking
	binary compatibility.
	@param aInterfaceId Interface identifier of the interface to be retrieved.
	@param aInterface A reference to a pointer that retrieves the specified interface.
	@param aInput An arbitrary input argument.
	@return KErrNone If the interface is supported, KErrNotSupported otherwise.
	*/	
	IMPORT_C virtual TInt GetInterface(TInt aInterfaceId,TAny*& aInterface,TAny* aInput);
	
protected:
	TVersion iVersion;
private:
	RLibrary iLibrary;
	TUint32 iReserved;				// Reserved for future expansion
	};




/**
@publishedPartner
@released
*/
class CProxyDrive : public CBase	
	{
public:
	CProxyDrive(CMountCB* aMount);
	~CProxyDrive();		
	inline CMountCB* Mount() const;
// virtual
	IMPORT_C virtual TInt ControlIO(const RMessagePtr2& aMessage,TInt aCommand,TAny* aParam1,TAny* aParam2);
	IMPORT_C virtual TInt Read(TInt64 aPos,TInt aLength,const TAny* aTrg,TInt aThreadHandle,TInt aOffset,TInt aFlags);
	IMPORT_C virtual TInt Write(TInt64 aPos,TInt aLength,const TAny* aSrc,TInt aThreadHandle,TInt anOffset,TInt aFlags);
	IMPORT_C virtual TInt DeleteNotify(TInt64 aPos, TInt aLength);
	IMPORT_C virtual TInt GetLastErrorInfo(TDes8& aErrorInfo);
	
// pure virtual
	virtual TInt Initialise()=0;
	virtual TInt Dismounted()=0;
	virtual TInt Enlarge(TInt aLength)=0;
	virtual TInt ReduceSize(TInt aPos, TInt aLength)=0;
	virtual TInt Read(TInt64 aPos,TInt aLength,const TAny* aTrg,TInt aThreadHandle,TInt anOffset)=0;
	virtual TInt Read(TInt64 aPos,TInt aLength,TDes8& aTrg)=0;
	virtual TInt Write(TInt64 aPos,TInt aLength,const TAny* aSrc,TInt aThreadHandle,TInt anOffset)=0;
	virtual TInt Write(TInt64 aPos,const TDesC8& aSrc)=0;
	virtual TInt Caps(TDes8& anInfo)=0;
	virtual TInt Format(TFormatInfo& anInfo)=0;
	virtual TInt Format(TInt64 aPos,TInt aLength)=0;
	virtual TInt SetMountInfo(const TDesC8* aMountInfo,TInt aMountInfoThreadHandle=KCurrentThreadHandle)=0;
	virtual TInt ForceRemount(TUint aFlags=0)=0;
	virtual TInt Unlock(TMediaPassword &aPassword, TBool aStorePassword)=0;
	virtual TInt Lock(TMediaPassword &aOldPassword, TMediaPassword &aNewPassword, TBool aStorePassword)=0;
	virtual TInt Clear(TMediaPassword &aPassword)=0;
	virtual TInt ErasePassword()=0;
	
protected:
	/**
	Return a pointer to a specified interface extension - to allow future extension of this class without breaking
	binary compatibility.
	@param aInterfaceId Interface identifier of the interface to be retrieved.
	@param aInterface A reference to a pointer that retrieves the specified interface.
	@param aInput An arbitrary input argument.
	@return KErrNone If the interface is supported, KErrNotSupported otherwise.
	*/	
	IMPORT_C virtual TInt GetInterface(TInt aInterfaceId,TAny*& aInterface,TAny* aInput);
		
private:
	CMountCB* iMount;
	TUint32 iReserved;				// Reserved for future expansion
	};




/**
@publishedPartner
@released
*/
class CLocDrvMountCB : public CMountCB
	{
public:
	IMPORT_C CLocDrvMountCB();
	IMPORT_C ~CLocDrvMountCB();			
	IMPORT_C TInt CreateLocalDrive(TBusLocalDrive& aLocDrv);
	IMPORT_C TInt InitLocalDrive();
	IMPORT_C void DismountedLocalDrive();
	inline CProxyDrive* LocalDrive() const;	
private:
	CProxyDrive* iProxyDrive;
	};




/**
@publishedPartner
@released
*/
NONSHARABLE_CLASS(CLocalProxyDrive) : public CProxyDrive
	{
public:	
	static CLocalProxyDrive* New(CMountCB* aMount,TBusLocalDrive& aLocDrv);
// virtual
	virtual TInt Initialise();	
	virtual TInt Dismounted();
	virtual TInt Enlarge(TInt aLength);
	virtual TInt ReduceSize(TInt aPos, TInt aLength);
	virtual TInt Read(TInt64 aPos,TInt aLength,const TAny* aTrg,TInt aThreadHandle,TInt aOffset, TInt aFlags);
	virtual TInt Read(TInt64 aPos,TInt aLength,const TAny* aTrg,TInt aThreadHandle,TInt anOffset);
	virtual TInt Read(TInt64 aPos,TInt aLength,TDes8& aTrg);
	virtual TInt Write(TInt64 aPos,TInt aLength,const TAny* aSrc,TInt aThreadHandle,TInt aOffset,TInt aFlags);
	virtual TInt Write(TInt64 aPos,TInt aLength,const TAny* aSrc,TInt aThreadHandle,TInt anOffset);
	virtual TInt Write(TInt64 aPos,const TDesC8& aSrc);
	virtual TInt Caps(TDes8& anInfo);
	virtual TInt Format(TFormatInfo& anInfo);
	virtual TInt Format(TInt64 aPos,TInt aLength);
	virtual TInt SetMountInfo(const TDesC8* aMountInfo,TInt aMountInfoThreadHandle=KCurrentThreadHandle);
	virtual TInt ForceRemount(TUint aFlags=0);
	virtual TInt ControlIO(const RMessagePtr2& aMessage,TInt aCommand,TAny* aParam1,TAny* aParam2);
	virtual TInt Unlock(TMediaPassword &aPassword, TBool aStorePassword);
	virtual TInt Lock(TMediaPassword &aOldPassword, TMediaPassword &aNewPassword, TBool aStorePassword);
	virtual TInt Clear(TMediaPassword &aPassword);
	virtual TInt ErasePassword();
	virtual TInt DeleteNotify(TInt64 aPos, TInt aLength);
	virtual TInt GetLastErrorInfo(TDes8& aErrorInfo);
private:
	CLocalProxyDrive(CMountCB* aMount,TBusLocalDrive& aLocDrv);
private:
	TBusLocalDrive& iLocDrv;
	};




/**
@publishedPartner
@released
*/
class CBaseExtProxyDrive : public CProxyDrive
	{
public:
	IMPORT_C CBaseExtProxyDrive(CProxyDrive* aProxyDrive, CMountCB* aMount);
	IMPORT_C ~CBaseExtProxyDrive();
	IMPORT_C virtual TInt Initialise();
	IMPORT_C virtual TInt Dismounted();
	IMPORT_C virtual TInt Enlarge(TInt aLength);
	IMPORT_C virtual TInt ReduceSize(TInt aPos, TInt aLength);
	IMPORT_C virtual TInt Read(TInt64 aPos,TInt aLength,const TAny* aTrg,TInt aThreadHandle,TInt aOffset,TInt aFlags);
	IMPORT_C virtual TInt Read(TInt64 aPos,TInt aLength,const TAny* aTrg,TInt aThreadHandle,TInt anOffset);
	IMPORT_C virtual TInt Read(TInt64 aPos,TInt aLength,TDes8& aTrg);
	IMPORT_C virtual TInt Write(TInt64 aPos,TInt aLength,const TAny* aSrc,TInt aThreadHandle,TInt aOffset,TInt aFlags);
	IMPORT_C virtual TInt Write(TInt64 aPos,TInt aLength,const TAny* aSrc,TInt aThreadHandle,TInt anOffset);
	IMPORT_C virtual TInt Write(TInt64 aPos,const TDesC8& aSrc);
	IMPORT_C virtual TInt Caps(TDes8& anInfo);
	IMPORT_C virtual TInt Format(TFormatInfo& anInfo);
	IMPORT_C virtual TInt Format(TInt64 aPos,TInt aLength);
	IMPORT_C virtual TInt SetMountInfo(const TDesC8* aMountInfo,TInt aMountInfoThreadHandle=KCurrentThreadHandle);
	IMPORT_C virtual TInt ForceRemount(TUint aFlags=0);
	IMPORT_C virtual TInt Unlock(TMediaPassword &aPassword, TBool aStorePassword);
	IMPORT_C virtual TInt Lock(TMediaPassword &aOldPassword, TMediaPassword &aNewPassword, TBool aStorePassword);
	IMPORT_C virtual TInt Clear(TMediaPassword &aPassword);
	IMPORT_C virtual TInt ControlIO(const RMessagePtr2& aMessage,TInt aCommand,TAny* aParam1,TAny* aParam2);
	IMPORT_C virtual TInt ErasePassword();
	IMPORT_C virtual TInt GetLastErrorInfo(TDes8& aErrorInfo);
protected:
	/**
	Return a pointer to a specified interface extension - to allow future extension of this class without breaking
	binary compatibility.
	@param aInterfaceId Interface identifier of the interface to be retrieved.
	@param aInterface A reference to a pointer that retrieves the specified interface.
	@param aInput An arbitrary input argument.
	@return KErrNone If the interface is supported, KErrNotSupported otherwise.
	*/	
	IMPORT_C virtual TInt GetInterface(TInt aInterfaceId,TAny*& aInterface,TAny* aInput);	
private:
	CProxyDrive* iProxy;
	};




/**
@publishedPartner
@released
*/
class CProxyDriveFactory : public CFsObject
	{
public:
	IMPORT_C CProxyDriveFactory();
	IMPORT_C virtual TInt Remove();
	inline void SetLibrary(RLibrary aLib);
	inline RLibrary Library() const;
// pure virtual
	virtual TInt Install() =0;			
	virtual CProxyDrive* NewProxyDriveL(CProxyDrive* aProxy,CMountCB* aMount)=0;
private:
	RLibrary iLibrary;
	};




/**
@publishedPartner
@released

Gets the local bus drive.

@param aLocalDrive The local drive number.

@return The local bus drive.
*/
IMPORT_C TBusLocalDrive& GetLocalDrive(TInt aLocalDrive);




/**
*/
IMPORT_C TBool IsValidLocalDriveMapping(TInt aDrive);




/**
*/
IMPORT_C TBool DriveNumberToLocalDriveNumber(TInt aDrive);



struct TFatUtilityFunctions;
/**
@internalTechnology
*/
IMPORT_C const TFatUtilityFunctions* GetFatUtilityFunctions();




/**
@publishedPartner
@released

Copies data to a buffer.

If necessary, the buffer, a heap descriptor, is allocated or re-allocated
before copying takes place.

@param aBuf A reference to a pointer to heap descriptor forming the buffer.
            This will be allocated if it does not already exist,
            or re-allocated if the existing buffer is not large enough.
@param aDes The data to be copied.
*/
IMPORT_C void AllocBufferL(HBufC*& aBuf,const TDesC& aDes);





/**
@publishedPartner
@released

Notifies sessions of a debug event if aFunction has the KDebugNotifyMask set.

This function can only be used in debug builds or if _DEBUG
or _DEBUG_RELEASE is defined.

@param aFunction A function.
@param aDrive    A drive.
*/
IMPORT_C void DebugNotifySessions(TInt aFunction,TInt aDrive);




/**
@publishedPartner
@released

Writes data from a buffer to a file.

Called by the mount control block lock and the unlock functions.

@param aFileName The file to be written to.
@param aBuf      The data to be written.
*/
IMPORT_C void WriteToDisk(const TDesC& aFileName,const TDesC8& aBuf);




/**
*/
IMPORT_C CProxyDrive* CreateProxyDriveL(CProxyDrive* aConcreteDrive,CMountCB* aMount);




/**
@deprecated 6.1
*/
IMPORT_C TInt CompareFilenames(const TDesC& aFileName1,const TDesC& aFileName2);
//
/**
*/
IMPORT_C CFileSystem* GetFileSystem(const TDesC& aName);
#include <f32fsys.inl>
#endif
