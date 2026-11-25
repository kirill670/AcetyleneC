// AGMVER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMVER_H__
#define __AGMVER_H__

#include <e32std.h>

class RReadStream;
class RWriteStream;

/**
 *
 * The version number of the agenda model (consisting of major, minor and
 * build numbers).
 *
 * An object of this class is returned by the <code>CAgnEntryModel</code>
 * functions <code>ModelVersion()</code> and <code>FileVersion()</code>.
 * <code>ModelVersion()</code> returns the version of the model object
 * being used while <code>FileVersion()</code> returns the version of
 * model that was used to create the currently loaded file.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class TAgnVersion : public TVersion
	{
public:
	inline TAgnVersion(TVersion aVersion) : TVersion(aVersion) {};
	inline TAgnVersion() {};
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;	
	};

#endif