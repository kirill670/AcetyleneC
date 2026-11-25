// MSVUIDS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVUIDS_H__)
#define __MSVUIDS_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__MSVSTD_HRH__)
#include "msvstd.hrh"
#endif

// Entry type Uids
const TUid KUidMsvNullEntry={0};
/** Root entry of entire index */
const TUid KUidMsvRootEntry={KUidMsvRootEntryValue};
/** Service */
const TUid KUidMsvServiceEntry={KUidMsvServiceEntryValue};
/** Folder */
const TUid KUidMsvFolderEntry={KUidMsvFolderEntryValue};
/** Message */
const TUid KUidMsvMessageEntry={KUidMsvMessageEntryValue};
/** Entry */
const TUid KUidMsvAttachmentEntry={KUidMsvAttachmentEntryValue};

// Local Service Uid
/** An operation that affects only local entries. */
const TUid KUidMsvLocalServiceMtm={KUidMsvLocalServiceMtmValue};
/** An operation performed by the Message Server. */
const TUid KUidMsvServerMtm={KUidMsvServerMtmValue};
#endif
