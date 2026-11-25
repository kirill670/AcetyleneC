// Copyright (c) Symbian Ltd 2001

#ifndef __TCTALLTOKENTYPES_H__
#define __TCTALLTOKENTYPES_H__

#include <ct/MCTTokenTypeFilter.h>

/**@ingroup ct */
/**@{ */

/** A filter that includes all token types. See MCTTokenTypeFilter. Used by
    CCTTokenTypeInfo::List
*/
class TCTAllTokenTypes : public MCTTokenTypeFilter
	{
 public:
	/** Always returns ETrue. */
	IMPORT_C virtual TBool Accept(const CCTTokenTypeInfo& aTokenType) const;
	};
///@}
#endif // __TCTALLTOKENTYPES_H__
