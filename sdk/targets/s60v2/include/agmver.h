// AGMVER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMVER_H__
#define __AGMVER_H__

#include <e32std.h>

class RReadStream;
class RWriteStream;

class TAgnVersion : public TVersion
/** The version number of the agenda model, consisting of major, minor and build 
numbers.

An object of this class is returned by the CAgnEntryModel functions ModelVersion() 
and FileVersion(). ModelVersion() returns the version of the model object 
being used while FileVersion() returns the version of model that was used 
to create the file. 
@publishedAll
@released
*/
	{
public:
	inline TAgnVersion(TVersion aVersion) : TVersion(aVersion) {};
	inline TAgnVersion() {};
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;	
	};

#endif
