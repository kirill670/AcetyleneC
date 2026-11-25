// cfshared.inl
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#if !defined(__CFSHARED_INL__)
#define __CFSHARED_INL__

inline const TCFModuleName& TCFSubModuleAddress::Module() const 
/**
@return Reference to the module name part of the address.
@publishedPartner
*/
	{
	return iModule;
	}

inline const TCFSubModuleName& TCFSubModuleAddress::SubModule() const 
/**
@return Submodule name part of the address.
@publishedPartner
*/
	{
	return iSubModule;
	}


#endif // __CFSHARED_INL__
