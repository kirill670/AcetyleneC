// FLDBASE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __FLDBASE_H__
#define __FLDBASE_H__

#include <e32std.h>
#include <e32base.h>
#include <s32stor.h>

// Classes defined:
class CTextField;
class MTextFieldFactory;


/**
 *
 * The abstract base class for all fields.
 *
 * A field contains information which relates to a text object and is
 * automatically updated. Examples of fields are the page number and the
 * current date and time. Fields must implement the pure virtual
 * functions defined in this class, including <code>Value()</code> which
 * should calculate and return the field's new value, and
 * <code>Type()</code> which returns the field's type UID. The type UID
 * identifies the field type to the field factory (see class
 * <code>MTextFieldFactory</code>).
 *
 * @since 5.0
 * @lib " field.lib "
 */

class CTextField : public CBase
// Abstract class: derive from this to instantiate a particular type of field (eg date etc)
	{
public:
	IMPORT_C virtual TStreamId StoreL(CStreamStore& aStore)const; // calls ExternalizeL()
	IMPORT_C virtual void RestoreL(const CStreamStore& aStore,TStreamId aId); // calls InternalizeL()
	//
	// Should be replaced by concrete derived classes.
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream)const; // Externalize state info for the field
	
	/**
	 *
	 * Internalises the field data.
	 *
	 * Pure virtual. Called by <code>RestoreL()</code>.
	 *
	 * @param     " RReadStream& aStream "
	 *            Stream from which the field data should be
	 *            internalised.
	 */

	virtual void InternalizeL(RReadStream& aStream)=0;
	//
	
	/**
	 *
	 * Sets <code>aValueText</code> to the current field value if the buffer
	 * is large enough.
	 *
	 * If not, <code>aValueText</code> is not changed, and the function
	 * returns the length which is required to hold the field's value.
	 *
	 * @param     " TPtr& aValueText "
	 *            Descriptor which on return contains the field's
	 *            updated value.
	 * @returns   " TInt "
	 *            Zero on success, otherwise, the length of the buffer
	 *            which is required to hold the field's updated value.
	 */

	virtual TInt Value(TPtr& aValueText)=0; 
	//	
	/**
	 *
	 * Returns the field's type UID.
	 *
	 * @returns   " TUid "
	 *            The field's type UID.
	 */
	virtual TUid Type()const=0;
	};


/**
 *
 * Abstract base class for field factories.
 *
 * Defines a single pure virtual function <code>NewFieldL()</code>.To use
 * fields in editable text,1) Define a field factory class (derived from
 * <code>MTextFieldFactory</code>). It must implement the pure virtual
 * <code>NewFieldL()</code> function, to create and return fields given a
 * type.2) Create an instance of the field factory and set this to be the
 * editable text object's field factory (see
 * <code>CPlainText::SetFieldFactory()</code>, or you can specify a field
 * factory in the text object 's <code>NewL()</code>).3) Create a new
 * field (<code>CPlainText::NewTextFieldL()</code>), specifying the field
 * type UID (the built in field type UID values are defined in flddef.h).
 * This calls the factory's <code>NewFieldL()</code> function.4) Insert
 * the field into the text object
 * (<code>CPlainText::InsertFieldL()</code>).5) Evaluate the field
 * (<code>CPlainText::UpdateFieldL()</code>) and then re-evaluate as
 * required.
 *
 * @since 5.0
 * @lib ""
 */

class MTextFieldFactory
// Abstract class that should be derived from by any application that wishes to support fields
	{
public:
	
	/**
	 *
	 * Implementations of this function should create a field of the type
	 * specified, returning NULL if the field type is not recognised or
	 * supported.
	 *
	 * @param     " TUid aFieldType "
	 *            The field's type UID.
	 * @returns   " CTextField* "
	 *            Pointer to the new text field, or NULL if the factory
	 *            does not recognise or support the field type.
	 */

	virtual CTextField* NewFieldL(TUid aFieldType)=0; 
	// Creates a field of the type specified
	// Returns NULL if it does not recognise/support the field type
	};


#endif
