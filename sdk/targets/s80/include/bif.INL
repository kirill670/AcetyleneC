// BIF.INL
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

//
// BIO-message Information File (BIF) Reader and Writer Classes
// 

#ifndef BIF_INL__
#define BIF_INL__

inline const TEntry& CBioInfoFileReader::FileEntry() const
/** Gets the BIF file as a TEntry.

@return BIF file server entry */
	{
	return iEntry;
	}

#endif

