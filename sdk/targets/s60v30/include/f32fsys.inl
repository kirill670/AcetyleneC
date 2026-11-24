// f32\inc\f32fsys.inl
//
// Copyright (c) 1995-2001 Symbian Ltd. All rights reserved.
//

#define __IS_DRIVETHREAD() {__ASSERT_DEBUG(IsDriveThread(),DriveFault(ETrue));}
#define __IS_MAINTHREAD() {__ASSERT_DEBUG(IsMainThread(),DriveFault(EFalse));}


// Class TDrive

/**
*/
inline TInt TDrive::GetReason() const
	{
	__IS_DRIVETHREAD(); 
	return(iReason);
	}




/**
*/
inline void TDrive::SetChanged(TBool aValue)
	{
//	__IS_DRIVETHREAD();//scan drive running in new thread 
	iChanged=aValue;
	}




/**
*/
inline TBool TDrive::IsChanged()
	{
//	__IS_DRIVETHREAD();
	return(iChanged);
	}




/**
*/
inline TInt TDrive::DriveNumber() const
	{return(iDriveNumber);}




/**
*/
inline TBool TDrive::IsMounted() const
	{
	__IS_DRIVETHREAD();
	return(iCurrentMount!=NULL);
	}




/**
*/
inline TBool TDrive::IsLocal()
	{return(Att()&KDriveAttLocal);}




/**
*/
inline TBool TDrive::IsRom()
	{return(Att()&KDriveAttRom);}




/**
*/
inline TBool TDrive::IsRemovable()
	{return(Att()&KDriveAttRemovable);}




/**
*/
inline TBool TDrive::IsSubsted()
	{return(Att()&KDriveAttSubsted);}//	KDriveAttSubsted = 0x08




/**
*/
inline CMountCB& TDrive::CurrentMount() const
	{
	__IS_DRIVETHREAD();
	return(*iCurrentMount);
	}




/**
*/
inline TDrive& TDrive::SubstedDrive()const
	{
	__IS_MAINTHREAD();
	return(*iSubstedDrive);
	}




/**
*/
inline void TDrive::SetSubstedDrive(TDrive* aDrive)
	{
	__IS_MAINTHREAD();
	iSubstedDrive=aDrive;
	}




/**
*/
inline HBufC& TDrive::Subst() const
	{
	__IS_MAINTHREAD();
	return(*iSubst);
	}




/**
*/
inline void TDrive::SetSubst(HBufC* aSubst)
	{
	__IS_MAINTHREAD();
	iSubst=aSubst;
	}




inline CFsObjectCon& TDrive::Mount() const
	{return(*iMount);}
inline CFileSystem& TDrive::FSys()
	{return(*iFSys);}
inline CFileSystem*& TDrive::GetFSys()
	{return(iFSys);}
inline TDriveExtInfo& TDrive::ExtInfo()
	{
	__IS_DRIVETHREAD();
	return(iExtInfo);
	}
inline void TDrive::SetNotifyOn()
	{
	__IS_DRIVETHREAD();
	iDriveFlags &= ~ENotifyOff;
	}
inline void TDrive::SetNotifyOff()
	{
	__IS_DRIVETHREAD();
	iDriveFlags |= ENotifyOff;
	}
inline void TDrive::Lock()
	{iLock.Wait();}
inline void TDrive::UnLock()
	{iLock.Signal();}

inline TInt TDrive::ReservedSpace() const
	{return iReservedSpace;}

inline void TDrive::SetReservedSpace(const TInt aReservedSpace)
	{iReservedSpace=aReservedSpace; }

// Class CMountCB

/**
Gets a reference to the object representing the drive on which
the volume is mounted.

@return The drive on which the volume is mounted.
*/
inline TDrive& CMountCB::Drive() const
	{return(*iDrive);}




/**
Sets a pointer to the object representing the drive on which
the volume is mounted.

@param aDrive A pointer to the drive on which the volume is mounted.
*/
inline void CMountCB::SetDrive(TDrive* aDrive)
	{iDrive=aDrive;}




/**
Gets a reference to a heap descriptor containing the name of
the mounted volume.

@return A reference to a heap descriptor containing the volume name.
*/
inline HBufC& CMountCB::VolumeName()
	{return(*iVolumeName);}




/**
Sets a pointer to a heap descriptor containing the name of the mounted volume.

@param aName A pointer to a heap descriptor containing the name of
             the mounted volume to be set.
*/
inline void CMountCB::SetVolumeName(HBufC* aName)
	{iVolumeName=aName;}




/**
Tests whether the client is notified of any read or write failures.

The notification status is a property of the current session with
the file server, the value of which is stored in CSessionFs::iNotifyUser.
If set to true, the client will receive notifications from the file system.

Typically, this function might be used to save the current notification
state prior to temporarily disabling notifiers. This allows the original
notification state to be restored. 

Note that GetNotifyUser() is only available once the drive has been set for
the mount control block (using SetDrive()), since the notification status
is held by the session and accessed via the drive.

@return True if the client receives notifications from the file system,
        false otherwise.
*/
inline TBool CMountCB::GetNotifyUser() const
	{return(Drive().GetNotifyUser());}




/**
*/
inline void CMountCB::SetNotifyOn()
	{Drive().SetNotifyOn();}




/**
*/
inline void CMountCB::SetNotifyOff()
	{Drive().SetNotifyOff();}




/**
Locks the mount by incrementing the internal lock counter.

The mount becomes locked on formatting or on the opening of a resource
(a file or a directory) or raw disk subsession.
A format, resource or raw disk subsession can only be opened if the mount
is not locked.
*/
inline void CMountCB::IncLock()
	{iLockMount++;}




/**
Unlocks the mount by decrementing the internal lock counter.

The mount becomes locked on formatting or on the opening of a resource
(a file or a directory) or raw disk subsession.
A format, resource or raw disk subsession can only be opened if the mount
is not locked.
*/
inline void CMountCB::DecLock()
	{iLockMount--;}




/**
Gets the current lock status.

It delivers the current lock status by returning the internal lock counter.

@return The current lock status.
*/
inline TInt CMountCB::LockStatus()
	{return(iLockMount);}




/**
Tests whether the mount is currently locked. 

A mount is locked when the internal lock counter is greater than zero.
On creation, the lock counter is set to zero.

The mount becomes locked on formatting or on the opening of a resource
(a file or a directory) or raw disk subsession.
A format, resource or raw disk subsession can only be opened if the mount
is not locked.

@return True if the mount is locked, false, otherwise.
*/
inline TInt CMountCB::Locked()
	{return iLockMount>0; }




/**
Tests whether the mount control block represents the current mount on
the associated drive.

A drive has only one mount which is accessible: the current mount.
Any mount other than the current mount relates to a partition (i.e. volume)
that was present on a removable media which has since been removed.
The reason the mount has persisted is because resources (i.e. files/directories)
are still open on it.

This function is only available when the drive has been set for the mount
control block (using SetDrive()), since the current mount is held by the drive.

@return True if the mount is the current mount on the drive, false otherwise.
*/
inline TBool CMountCB::IsCurrentMount()
	{return(this==&iDrive->CurrentMount());}




/**
*/
inline TInt64 CMountCB::Size()
	{return(iSize);}




/**
Set the unique mount number
@param aMountNumber - The unique mount number
*/
const TInt KMountDismounted = 0x80000000;
inline void CMountCB::SetMountNumber(TInt aMountNumber)
	{ iMountNumber = (aMountNumber &~ KMountDismounted); }




/**
Set the mount to be dismounted
*/
inline void CMountCB::SetDismounted(TBool aDismounted)
	{
	if(aDismounted)
		iMountNumber |= KMountDismounted;
	else
		iMountNumber &= ~KMountDismounted;
	}




/**
Returns the unique mount number
@return The unique mount number
*/
inline TInt CMountCB::MountNumber() const
	{ return(iMountNumber &~ KMountDismounted); }




/**
Returns ETrue if the mount is flagged as dismounted.
@return ETrue if the mount is flagged as dismounted
*/
inline TBool CMountCB::IsDismounted() const
	{ return(iMountNumber & KMountDismounted); }




// Class CFileCB
/**
Sets the mount associated with the file.

@param aMount The mount.
*/
inline void CFileCB::SetMount(CMountCB * aMount)
	{iMount=aMount;}

/**
Gets a reference to the object representing the drive on which
the file resides.

@return A reference to the file's drive.
*/
inline TDrive& CFileCB::Drive()
	{return(*iDrive);}




/**
Gets a reference to the object representing the drive on which the file was created.

The 'created drive' is only different from the 'drive', as returned by Drive(), if 
the 'drive' was a substitute for the 'created drive' in the file server session.

@return A reference to the drive on which the file was created.
*/
inline TDrive& CFileCB::CreatedDrive()
	{return(*iCreatedDrive);}




/**
Gets a reference to the object representing the mount on which the file resides.

@return The file's mount.
*/
inline CMountCB& CFileCB::Mount()
	{return(*iMount);}




/**
Gets a reference to a heap descriptor containing the full file name.

@return A heap descriptor containing the full file name.
*/
inline HBufC& CFileCB::FileName()
	{return(*iFileName);}

/**
Gets a reference to a heap descriptor containing the folded full file name.

@return A heap descriptor containing the full file name.
*/
inline HBufC& CFileCB::FileNameF()
	{return(*iFileNameF);}

/**
Gets the hash of the folded filename

@return hash of the folded file name
*/
inline TUint32 CFileCB::NameHash() const
	{return(iNameHash);}


/**
Gets a reference to the file share lock being used by the file.

@return The file share lock.
*/
inline RArray<SFileShareLock>& CFileCB::Lock()
	{return(*iLock);}




/**
Gets the file object's unique ID, as returned by CObject::UniqueID().

@return The object's unique ID.

@see CObject
*/
inline TInt CFileCB::UniqueID() const
	{return(CFsObject::UniqueID());}




/**
Gets the iShare value, which defines the level of access allowed to the file.

@return The value of iShare

@see CFileCB::iShare
*/
inline TShare CFileCB::Share()
	{return(iShare);}




/**
Sets the iShare value, which defines the level of access allowed to the file.

@param aShare The new value.

@see CFileCB::iShare
*/
inline void CFileCB::SetShare(TShare aShare)
	{iShare=aShare;}




/**
Gets the size of the file.

@return The size of the file.
*/
inline TInt CFileCB::Size()
	{return(iSize);}




/**
Sets the size of the file.

@param aSize The size of the file.
*/
inline void CFileCB::SetSize(TInt aSize)
	{iSize=aSize;}




/**
Gets the file's attributes.

@return An integer containing the file attribute bit mask.
*/
inline TInt CFileCB::Att()
	{return(iAtt);}




/**
Sets the file's attributes.

@param aAtt The file attribute bit mask.
*/
inline void CFileCB::SetAtt(TInt aAtt)
	{iAtt=aAtt;}	




/**
Gets the universal time when the file was last modified.

@return The universal time when the file was last modiified.
*/
inline TTime CFileCB::Modified()
	{return(iModified);}




/**
Sets the universal time when the file was last modified.

@param aModified The universal time when the file was last modified.
*/
inline void CFileCB::SetModified(TTime aModified)
	{iModified=aModified;}




/**
Tests whether the file is corrupt.

@return ETrue if the file is corrupt; EFalse otherwise.
*/
inline TBool CFileCB::FileCorrupt()
	{return iFileCorrupt;}




/**
Sets whether the file is corrupt.

@param aFileCorrupt ETrue, if the file is corrupt; EFalse, otherwise.
*/
inline void CFileCB::SetFileCorrupt(TBool aFileCorrupt)
	{iFileCorrupt=aFileCorrupt;}




/**
Gets the iBadPower value.

@return The value of iBadPower

@see CFileCB::iBadPower
*/
inline TBool CFileCB::BadPower()
	{return (iBadPower);};




/**
Sets the iBadPower value.

@param aBadPower ETrue, if an operation on the file has failed due
                 to bad power;
				 EFalse if power has been found to be good.

@see CFileCB::iBadPower
*/
inline void CFileCB::SetBadPower(TBool aBadPower)
	{iBadPower=aBadPower;}





// Class CFileShare
inline CFileCB& CFileShare::File()
	{return(*iFile);}




// Class CDirCB

/**
Gets a reference to the object representing the drive on which
the directory resides.

@return A reference to the directory's drive.
*/
inline TDrive& CDirCB::Drive()
	{return(*iDrive);}




/**
Gets a reference to the object representing the mount on which
the directory resides.

@return A reference to the directory's mount.
*/
inline CMountCB& CDirCB::Mount()
	{return(*iMount);}




/**
Tests whether the preceding entry details should be returned when
multiple entries are being read.

@return True if the preceding entry details should be returned;
        false otherwise.
*/
inline TBool CDirCB::Pending()
	{return iPending;}




/**
Sets whether the preceding entry details should be returned when
multiple entries are being read.

@param aPending ETrue if the preceding entry details should be returned;
                EFalse otherwise.
*/
inline void CDirCB::SetPending(TBool aPending)
	{iPending=aPending;}




// class CFormatCB

/**
Gets the object representing the drive on which the disk to
be formatted resides.

@return The drive for the format action.
*/
inline TDrive& CFormatCB::Drive()
	{return(*iDrive);}




/**
Gets the object representing the mount on which the disk to
be formatted resides.

@return The mount for the format action.
*/
inline CMountCB& CFormatCB::Mount()
	{return(*iMount);}




/**
Gets the mode of the format operation.

@return The value of the format mode.
*/
inline TFormatMode CFormatCB::Mode()
	{return(iMode);}




/**
Gets the current stage in the format operation.

@return The stage the current format operation has reached.
*/
inline TInt& CFormatCB::CurrentStep()
	{return(iCurrentStep);}




// class CRawDiskCB

/**
Gets a reference to an object representing the drive on which the disk resides.

@return  A reference to the drive on which the disk resides.
*/
inline TDrive& CRawDiskCB::Drive()
	{return(iMount->Drive());}




/**
Gets an object representing the mount on which the disk resides.

@return The mount on which the disk resides.
*/
inline CMountCB& CRawDiskCB::Mount()
	{return(*iMount);}




/**
Tests whether the mount on which the disk resides is write protected.

@return True if the mount is write protected, false otherwise.
*/
inline TBool CRawDiskCB::IsWriteProtected() const
	{ return(iFlags & EWriteProtected); }





/**
Stores the write protected state of the disk.
*/
inline void CRawDiskCB::SetWriteProtected()
	{ iFlags |= EWriteProtected; }




/**
Tests whether the disk contents has changed (due to a write operation)

@return True if the disk contents has changed
*/
inline TBool CRawDiskCB::IsChanged() const
	{ return(iFlags & EChanged); }




/**
Set a flag to state that the disk contents has changed (due to a write operation)
*/
inline void CRawDiskCB::SetChanged()
	{ iFlags |= EChanged; }




// class CProxyDriveFactory
inline void CProxyDriveFactory::SetLibrary(RLibrary aLib)
	{iLibrary=aLib;}
inline RLibrary CProxyDriveFactory::Library() const
	{return(iLibrary);}

// class CProxyDrive
inline CMountCB* CProxyDrive::Mount() const
	{return(iMount);}

// class CLocDrvMountCB
inline CProxyDrive* CLocDrvMountCB::LocalDrive() const
	{return(iProxyDrive);}	

