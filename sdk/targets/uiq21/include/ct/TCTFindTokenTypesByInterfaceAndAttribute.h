// Copyright (c) Symbian Ltd 2001

#ifndef __TCTFINDTOKENTYPESBYINTERFACEANDATTRIBUTE_H__
#define __TCTFINDTOKENTYPESBYINTERFACEANDATTRIBUTE_H__

#include <ct/MCTTokenTypeFilter.h>


struct TCTTokenTypeAttribute;

/**@ingroup ct */
/**@{ */

/** A filter that returns only those token types that match the
    required set of interfaces and attributes. On construction, an
    array containing the required interfaces and an array of required
    attributes/values is passed in. Token types will be matched if
    every interface in the suplied array is supported by the token
    type, and every attribute is defined and has the same value.*/
class TCTFindTokenTypesByInterfaceAndAttribute : public MCTTokenTypeFilter
	{
 public:
	/** Constructor.
		@param aInterfaces An array of the interfaces that the token type
		must support.
		@param aAttributes An array of the attributes and values that
		must be defined for the token type.
	*/
	IMPORT_C TCTFindTokenTypesByInterfaceAndAttribute(const TArray<TUid> aInterfaces,
													  const TArray<TCTTokenTypeAttribute> aAttributes);

	/** Return ETrue if all the interfaces and attributes associated
        with the filter are supported by the token type. */
	virtual TBool Accept(const CCTTokenTypeInfo& aTokenType) const;

 private:
	const TArray<TUid> iInterfaces;
	const TArray<TCTTokenTypeAttribute> iAttributes;
	};

///@}
#endif // __TCTFINDTOKENTYPESBYINTERFACEANDATTRIBUTE_H__
