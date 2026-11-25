// Copyright (c) Symbian 2001

#ifndef __TCTTOKENTYPEATTRIBUTE_H__
#define __TCTTOKENTYPEATTRIBUTE_H__

/**@file */

/**@defgroup Attributes Attribute UIDs */

/**@{ */

/// Indicates if the token is implemented in software. A boolean value.
const TUid KCTSoftware = {0x101F527B};
/// Indicates if the token is removable. A boolean value.
const TUid KCTRemovable = {0x101F527C};
///Indicates if the token type provides its own access control. A boolean value
const TUid KCTAccessControlled = {0x101F527D};
/// The maximum number of tokens of this type. An integer value.
const TUid KCTMaxTokenCount = {0x101F527E};
/// The minimum number of tokens of this type. An integer value.
const TUid KCTMinTokenCount = {0x101F527F};
///@}

/**@ingroup ct */
/**@{ */


/** Arbitrary attributes can be stored as UID/Value pairs. This allows
    any attributes that can be represented as 32 bit integers to be
    associated with token types.  */
struct TCTTokenTypeAttribute
	{
	/** The UID of the attribute. */
	TUid iUID;
	/** The value of the attribute.*/
	TInt iVal;
	};
///@}
#endif // __TCTTOKENTYPEATTRIBUTE_H__
