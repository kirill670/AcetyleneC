// Copyright (c) 2006 Symbian Software Ltd.  All rights reserved.
//
// commdbconnpref.inl
//

/**
@file
@deprecated since v9.1. Functionality is replaced with commsdat.
*/

inline TBool TCommDbConnPref::operator==(const TCommDbConnPref& aPref) const
/**
Overloaded function for operator "==" 

@param aPref Reference to the class TCommDbConnPref
@return ETrue if Successful if both the objects are equal else EFalse
*/
	{
	return (Compare(aPref) == 0);
	}

inline TBool TCommDbConnPref::operator!=(const TCommDbConnPref& aPref) const
/**
Overloaded function for operator "!=" 

@param aPref Reference to the class TCommDbConnPref
@return Etrue if Successful if the objects are not equal else EFalse
*/
	{
	return (Compare(aPref) != 0);
	}

inline SCommDbConnPref* TCommDbConnPref::PrefPtr() const
	{
	return (SCommDbConnPref*)UserPtr();
	}

inline TCommDbConnPref& TCommDbConnPref::Cast(const TConnPref& aPref)
/**
Casts the TConnPref object to TCommDbConnPref

@param aPref Connection preferences.
@return Reference to TCommDbConnPref
*/
	{
	return *((TCommDbConnPref*)&aPref);
	}

inline SCommDbMultiConnPref* TCommDbMultiConnPref::PrefPtr() const
	{
	return (SCommDbMultiConnPref*)UserPtr();
	}

inline TCommDbMultiConnPref& TCommDbMultiConnPref::Cast(const TConnPref& aPref)
/**
Casts the TConnPref object to TCommDbMultiConnPref

@param aPref Connection preferences.
@return Reference to TCommDbMultiConnPref
*/
	{
	return *((TCommDbMultiConnPref*)&aPref);
	}
