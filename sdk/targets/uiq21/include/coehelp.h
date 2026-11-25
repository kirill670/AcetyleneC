// COEHELP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEHELP_H__)
#define __COEHELP_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

/**
 * Context name.
 * @since 5.1
 */
typedef TBuf<30> TCoeContextName;

/**
 *
 * Help context.
 *
 * This class contains the information required to link the control and
 * the appropriate context sensitive help topic. This information
 * includes the UID of the help file and the literal descriptor for the
 * appropriate help topic context.
 *
 * @since 5.1
 * @lib "cone.lib"
 */
class TCoeHelpContext
	{
public:
	IMPORT_C TCoeHelpContext();
	IMPORT_C TCoeHelpContext(TUid aMajor,const TDesC& aContext);
	IMPORT_C TBool IsNull() const;
	IMPORT_C TBool operator==(const TCoeHelpContext& aContext) const;
	IMPORT_C TBool operator!=(const TCoeHelpContext& aContext) const;
public:
	TUid iMajor;
	TCoeContextName iContext;
	};

#endif
