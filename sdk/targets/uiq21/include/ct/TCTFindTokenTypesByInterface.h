// Copyright (c) Symbian Ltd 2001

#ifndef __TCTFINDTOKENTYPESBYINTERFACE_H__
#define __TCTFINDTOKENTYPESBYINTERFACE_H__

#include <ct/MCTTokenTypeFilter.h>

/**@ingroup ct */
/**@{ */

/** A filter that returns only those token types that match the
    required set of interfaces. On construction, an array containing
    the required interfaces is passed in. Token types will be matched if
    every interface in the suplied array is supported by the token type.*/
class TCTFindTokenTypesByInterface : public MCTTokenTypeFilter
	{
 public:
	/** Constructor.
		@param aInterfaces An array of the interfaces that the token type
		must support.
	*/
	IMPORT_C TCTFindTokenTypesByInterface(const TArray<TUid> aInterfaces);

	/** Return ETrue if all the interfaces associated with the filter
        are supported by the token type. */
	virtual TBool Accept(const CCTTokenTypeInfo& aTokenType) const;

 private:
	const TArray<TUid> iInterfaces;
	};
///@}
#endif // __TCTFINDTOKENTYPESBYINTERFACE_H__
