// RHTTPPropertySet.h
//
// Copyright (C) 2001 Symbian Ltd.

/** 
	@file RHTTPPropertySet.h
	@public
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __RHTTPPROPERTYSET_H__
#define __RHTTPPROPERTYSET_H__ 

// System includes
#include <http/thttphdrval.h> 

// Forward declarations
class CHeaderFieldPart;

/** 
	@public
	@class			RHTTPPropertySet
	@since			7.0
	A set of named THTTPHdrVal objects. Used for storing arbitrary
	collections of information.  
 */

//##ModelId=3C4C188201EA
class RHTTPPropertySet
	{
 public:
	/** Default (uninitialised) constructor. An object constructed in this way
		means 'use text-mode HTTP with default settings'
	 */
	//##ModelId=3A63217800E0
	IMPORT_C RHTTPPropertySet();
	
	/** Returns a property.
		@param aPropertyName The name of the property.
		@param aVal The returned value of the property (if defined)
		@returns ETrue if the property exists
	*/
	//##ModelId=3C4C1882021F
	IMPORT_C TBool Property(RStringF aPropertyName, THTTPHdrVal& aVal) const;

	/** Sets or creates a property. 
		@param aPropertyName The name of the property
		@param aValue The new value of the property
		@exception KErrNoMemory There was not enough memory.
	 */
	//##ModelId=3C4C1882021C
	IMPORT_C void SetPropertyL(RStringF aPropertyName, THTTPHdrVal aValue);

	/** Removes a named property. 
		@param aPropertyName The name of the property
	 */
	//##ModelId=3C4C18820213
	IMPORT_C void RemoveProperty(RStringF aPropertyName);

	/** Removes all properties
	 */
	//##ModelId=3C4C18820212
	IMPORT_C void RemoveAllProperties();

 protected:
	//##ModelId=3C4C18820208
	CHeaderFieldPart* iImplementation;

	friend class CHeaderFieldPart;
	friend class CHTTPSession;
	};



#endif //	__RHTTPPROPERTYSET_H__ 
