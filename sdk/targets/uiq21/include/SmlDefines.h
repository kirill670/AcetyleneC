//
// SMLDEFINES.H
//

#if !defined(__SMLDEFINES_H__)
#define __SMLDEFINES_H__
#include <e32std.h>

const TInt KSmlClientMajorVersion = 1;
const TInt KSmlClientMinorVersion = 0;
_LIT(KSmlDirectoryLocation, "\\System\\SyncML\\");


enum TSmlEncoding
	{
	ESmlEncodingUTF8,
	ESmlEncodingBinary
	};


const TUid	KSmlDataStoreUid = {0x10009F1C};
const TUid  KSmlDbDataStoreUid = {0x10009F1D};
const TUint KSmlDbAdapterUid = 0x100097C3;
const TUint KSmlUidTransport = 0x10009F19;

#endif