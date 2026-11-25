
// Copyright (c) Symbian Ltd 2001
#ifndef __MCTTOKENTYPEFILTER_H__
#define __MCTTOKENTYPEFILTER_H__

class CCTTokenTypeInfo;

/**@ingroup ct */
/**@{ */

/** A filter that is used to control which token types appear in a
    list returned by CCTTokenTypeInfo::ListL. Each possible token type
    is offered to the filter in turn, which returns ETrue if it is to
    be included. For most clients one of the 3 defined subclasses,
    TCTAllTokenTypes (which returns everything),
    TCTFindTokenTypesByInterface (which finds token types that support
    all of a supplied set of interfaces) or
    TCTFindTokenTypesByInterfaceAndAttribute (which matches for a
    particular list of interfaces, and a particular set of
    attribute/value pairs) will do what is wanted. Clients wanting
    more unusual matching criterea may need to write their own
    subclasses.
*/
class MCTTokenTypeFilter
	{
 public:
	/** Returns ETrue if the supplied token type should be included in
        the list, or EFalse otherwise */
	virtual TBool Accept(const CCTTokenTypeInfo& aTokenType) const = 0;
	};
///@}
#endif // __MCTTOKENTYPEFILTER_H__

