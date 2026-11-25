/*
* ==============================================================================
*  Name        : MXMLAttributes.h
*  Part of     : ?Subsystem_name / ?Module_name
*  Interface   : ?Interface_category, ?Interface_name
*  Description : ?Description
*  Version     : ?Version
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef __MXMLATTRIBUTES_H
#define __MXMLATTRIBUTES_H

//  INCLUDES
#include <e32std.h>

// CLASS DECLARATION

/**
*  Interface for a list of XML elemnet attributes.
*  Contains a list of attributes belonging to a certain element and is returned in the 
*  MXMLContentHandler::StartElement() callback.
*
*  @lib XMLInterface.dll
*  @since ?Series60_version
*
*/

class MXMLAttributes
{
public:
   
/**
* Look up the index of an attribute by name.
* @since ?Series60_version
* @param aName: Name of attribute to look up
* @return Index of aName
*/
	virtual TInt GetIndex(TDesC& aName) = 0;

/**
* Get the number of attributes in the list.
* @since ?Series60_version
* @param none
* @return The number of attributes in the list.
*/
	virtual  TInt GetLength() = 0;
	
/**
* Look up the name of an attribute by index.
* @since ?Series60_version
* @param aIndex: Index of attribute to look up.
* @return Name of attribute at index aIndex.
*/
	virtual TPtrC GetName(TInt aIndex) = 0;

/**
* Look up an attribute's value by name.
* @since ?Series60_version
* @param aName: Name of attribute to look up
* @return Value of attribute aName.
*/
	virtual TPtrC GetValue(TDesC& aName) = 0;

/**
* Look up an attribute's value by index.
* @since ?Series60_version
* @param aIndex: Index of attribute to look up.
* @return Value of attribute at aIndex.
*/
	virtual TPtrC GetValue(TInt& aIndex) = 0;

/**
* Look up an attribute's type by index.
* @since ?Series60_version
* @param aIndex: Index of attribute to look up.
* @return Type of attribute at aIndex.
*/
// R&D: Feature: GetType missing from Attributes
	virtual TPtrC GetType(TInt aIndex) = 0;

/**
* Look up an attribute's type by name.
* @since ?Series60_version
* @param aIndex: Index of attribute to look up.
* @return ?description
*/
// R&D: Feature: GetType missing from Attributes
	virtual TPtrC GetType(TDesC& aName) = 0;
  
};

#endif      // __MXMLATTRIBUTES_H  
            
// End of File
