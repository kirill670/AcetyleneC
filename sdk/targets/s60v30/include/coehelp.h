// COEHELP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEHELP_H__)
#define __COEHELP_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

/** Holds the name of the help context.

@publishedAll
@released */
typedef TBuf<30> TCoeContextName;


class TCoeHelpContext
/** Help context.

This class contains the information required to link the control and the appropriate 
context sensitive help topic. This information includes the UID of the help 
file and the literal descriptor for the appropriate help topic context.

@see CCoeControl::GetHelpContext() 
@publishedAll
@released */
	{
public:
	IMPORT_C TCoeHelpContext();
	IMPORT_C TCoeHelpContext(TUid aMajor,const TDesC& aContext);
	IMPORT_C TBool IsNull() const;
	IMPORT_C TBool operator==(const TCoeHelpContext& aContext) const;
	IMPORT_C TBool operator!=(const TCoeHelpContext& aContext) const;
public:
	/** The UID of the context sensitive help file containing the topic information. */
	TUid iMajor;
	/** The name of the help context. This is the literal descriptor generated from 
	a context string by the context sensitive help compiler. */
	TCoeContextName iContext;
private:
    TInt iTCoeHelpContext_Reserved1;
	};

#endif
