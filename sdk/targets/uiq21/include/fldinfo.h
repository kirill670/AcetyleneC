// FLDINFO.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __FLDINFO_H__
#define __FLDINFO_H__

#include <e32std.h>


/**
 *
 * Gets information about the fields found in a range of characters by
 * <code>CPlainText::FindFields()</code>.
 *
 * This information is the number of fields fully or partially within the
 * range and the start position and length of the first field found.
 *
 * @since 5.0
 * @lib " field.lib "
 */

class TFindFieldInfo
// information returned from a "Find the fields in this range" request
	{
public:
	IMPORT_C TBool operator==(const TFindFieldInfo& aInfo)const;
	IMPORT_C TBool operator!=(const TFindFieldInfo& aInfo)const;
public:
	TInt iFieldCountInRange; // number of fields found in the specified range
	TInt iFirstFieldPos; // character position of the start of the first field in the range
	TInt iFirstFieldLen; // length of the first field in the range
	};


#endif