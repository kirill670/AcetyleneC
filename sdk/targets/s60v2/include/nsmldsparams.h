/*
* ==============================================================================
*  Name        : nsmldsparams.h
*  Part of     : Nokia SyncML / DS Utils (DS parameters)
*  Interface   : CNSmlParamList, CNSmlParamXXX
*  Description : DS parameters header
*  Version     : $Revision: 8 $ $Modtime: 18.06.03 14:13 $
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

#ifndef __CNSMLDSPARAMS_H__
#define __CNSMLDSPARAMS_H__

// ------------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------------
#include <e32base.h>
#include <s32strm.h>
#include <badesca.h>

// ------------------------------------------------------------------------------------------------
// Predefined parameter IDs DO NOT OVERRIDE THESE! 1 - 3
// ------------------------------------------------------------------------------------------------
enum TNSmlDefaultParamIds
	{
	ENSmlParamIdLocalDatabase = 1,
	ENSmlParamIdRemoteDatabase,
	ENSmlParamIdSyncType,
	ENSmlParamIdSyncTypeValues
	};

// ------------------------------------------------------------------------------------------------
// TNSmlParamType
// ------------------------------------------------------------------------------------------------
enum TNSmlParamType
	{
	ENSmlParamHBufC,
	ENSmlParamDateTime,
	ENSmlParamDateTimeRange,
	ENSmlParamNumber,
	ENSmlParamBoolean,
	ENSmlParamNumberRange, // range selector (a - b)
	ENSmlParamFileName,	// may define UID to filter files
	ENSmlParamDirectoryName,
	ENSmlParamChoiceList
	};

// ------------------------------------------------------------------------------------------------
// Class forwards
// ------------------------------------------------------------------------------------------------
class CNSmlParam;

// ------------------------------------------------------------------------------------------------
// CNSmlParamList
// ------------------------------------------------------------------------------------------------
class CNSmlParamList : public CBase
	{
public:
	/**
    * Two-phase constructor for CNSmlParamList class.
	* @return CNSmlParamList* Pointer to newly created instance.
    */
	IMPORT_C static CNSmlParamList* NewL();

	/**
    * Two-phase constructor for CNSmlParamList class. Leaves instance into cleanupstack.
	* @return CNSmlParamList* Pointer to newly created instance.
    */
	IMPORT_C static CNSmlParamList* NewLC();

	/**
    * C++ destructor.
    */
	IMPORT_C ~CNSmlParamList();

	/**
    * Returns number of parameters in list.
	* @return TInt Number of parameters in list.
    */
	IMPORT_C TInt Count() const;

	/**
    * Returns parameter at index aIndex from list.
	* @return const CNSmlParam* Constant pointer to parameter at index aIndex.
    */
	IMPORT_C const CNSmlParam* Get( TInt aIndex ) const;

	/**
    * Returns parameter with id aId from list.
	* @return const CNSmlParam* Constant pointer to parameter with id aId from list.
    */
	IMPORT_C const CNSmlParam* GetById( TUint32 aId ) const;

	/**
    * Adds new parameter to the list.
	* @param aParam Pointer to parameter to add to the list.
    */
	IMPORT_C void AddL( CNSmlParam* aParam );

	/**
    * Removes parameter at index aIndex from list.
	* @param aIndex Index to parameter to be removed.
	* @return CNSmlParam* Pointer to removed parameter.
    */
	IMPORT_C CNSmlParam* Remove( TInt aIndex );

protected:
	void ConstructL();

private:
	CArrayPtr<CNSmlParam>* iParams;
	};

// ------------------------------------------------------------------------------------------------
// CNSmlParam
// ------------------------------------------------------------------------------------------------
class CNSmlParam : public CBase
	{
public:
	/**
    * C++ destructor.
	*/
	IMPORT_C ~CNSmlParam();

	/**
    * Returns type of parameter.
	* @return TNSmlParamType Parameter type.
    */
	IMPORT_C TNSmlParamType Type() const; // Param type

	/**
    * Returns id of parameter.
	* @return TUin32 Parameter id.
    */
	IMPORT_C TUint32 Id() const; // Unique ID of this parameter (Unique inside one DSA only!)

	/**
    * Returns value of mandatory property.
	* @return TBool Mandatory property's value.
    */
	IMPORT_C TBool Mandatory() const;

	/**
    * Returns visibility value.
	* @return TBool ETrue if this parameter is visible in UI.
    */
	IMPORT_C TBool Visible() const;

	/**
    * Sets visibility.
	* @param aVisible Sets visibility of the parameter.
    */
	IMPORT_C void SetVisible( TBool aVisible );

	/**
    * Parameter internalizer.
	* @param aStream Stream from which this parameter will be internalized.
    */
	IMPORT_C virtual void InternalizeL( RReadStream& aStream );

	/**
    * Parameter externalizer.
	* @param aStream Stream into which this parameter will be externalized.
    */
	IMPORT_C virtual void ExternalizeL( RWriteStream& aStream ) const;

protected:
	/**
    * C++ constructor.
	* @param aType Type of parameter.
	* @param aId Parameter id.
	* @param aMandatory ETrue if this paramater is mandatory (i.e. must contain value).
    */
	IMPORT_C CNSmlParam( const TNSmlParamType aType, const TUint32 aId, TBool aMandatory = EFalse );

private:
	TUint32 iId;
	TNSmlParamType iType;
	TBool iMandatory;
	TBool iVisible;
	};

// ------------------------------------------------------------------------------------------------
// CNSmlParamHBufC
// ------------------------------------------------------------------------------------------------
class CNSmlParamHBufC : public CNSmlParam
	{
public:
	IMPORT_C static CNSmlParamHBufC* NewL( TUint32 aId, TInt aMaxLength, TBool aMandatory = EFalse );
	IMPORT_C static CNSmlParamHBufC* NewLC( TUint32 aId, TInt aMaxLength, TBool aMandatory = EFalse );
	
	IMPORT_C ~CNSmlParamHBufC();
	IMPORT_C HBufC* Value() const;
	IMPORT_C void SetValueL( const TDesC& aValue );
	IMPORT_C TInt MaxLength() const;

	IMPORT_C void InternalizeL( RReadStream& aStream );
	IMPORT_C void ExternalizeL( RWriteStream& aStream ) const;

private:
	CNSmlParamHBufC( TUint32 aId, TBool aMandatory );
	void ConstructL( TInt aMaxLength );

private:
	HBufC* iValue;
	TInt iMaxLength;
	};

// ------------------------------------------------------------------------------------------------
// CNSmlParamDateTime
// ------------------------------------------------------------------------------------------------
class CNSmlParamDateTime : public CNSmlParam
	{
public:
	IMPORT_C static CNSmlParamDateTime* NewL( TUint32 aId, const TTime& aMinValue = Time::MinTTime(), const TTime& aMaxValue = Time::MaxTTime(), TBool aMandatory = EFalse );
	IMPORT_C static CNSmlParamDateTime* NewLC( TUint32 aId, const TTime& aMinValue = Time::MinTTime(), const TTime& aMaxValue = Time::MaxTTime(), TBool aMandatory = EFalse );
	
	IMPORT_C TTime Value() const;
	IMPORT_C void SetValue( const TTime& aValue );
	IMPORT_C TTime Min() const;
	IMPORT_C TTime Max() const;

	IMPORT_C void InternalizeL( RReadStream& aStream );
	IMPORT_C void ExternalizeL( RWriteStream& aStream ) const;

protected:
	TTime iValue;
	TTime iMin;
	TTime iMax;

private:
	CNSmlParamDateTime( TUint32 aId, const TTime& aMinValue, const TTime& aMaxValue, TBool aMandatory = EFalse );

	};

// ------------------------------------------------------------------------------------------------
// CNSmlParamNumber
// ------------------------------------------------------------------------------------------------
class CNSmlParamNumber : public CNSmlParam
	{
public:
	IMPORT_C static CNSmlParamNumber* NewL( TUint32 aId, TInt aMinValue = KMinTInt32, TInt aMaxValue = KMaxTInt32 );
	IMPORT_C static CNSmlParamNumber* NewLC( TUint32 aId, TInt aMinValue = KMinTInt32, TInt aMaxValue = KMaxTInt32 );
	
	IMPORT_C TInt Value() const;
	IMPORT_C void SetValue( TInt aValue );
	IMPORT_C TInt Min() const;
	IMPORT_C TInt Max() const;

	IMPORT_C void InternalizeL( RReadStream& aStream );
	IMPORT_C void ExternalizeL( RWriteStream& aStream ) const;

protected:
	TInt iValue;
	TInt iMin;
	TInt iMax;

private:
	CNSmlParamNumber( TUint32 aId, TInt aMinValue, TInt aMaxValue );
	};

// ------------------------------------------------------------------------------------------------
// CNSmlParamDateTimeRange
// ------------------------------------------------------------------------------------------------
class CNSmlParamDateTimeRange : public CNSmlParam
	{
public:
	IMPORT_C static CNSmlParamDateTimeRange* NewL( TUint32 aId, const TTime& aMinValue = Time::MinTTime(), const TTime& aMaxValue = Time::MaxTTime(), TBool aMandatory = EFalse );
	IMPORT_C static CNSmlParamDateTimeRange* NewLC( TUint32 aId, const TTime& aMinValue = Time::MinTTime(), const TTime& aMaxValue = Time::MaxTTime(), TBool aMandatory = EFalse );
	
	IMPORT_C TTime From() const;
	IMPORT_C void SetFrom( const TTime& aFrom );
	IMPORT_C TTime To() const;
	IMPORT_C void SetTo( const TTime& aTo );
	IMPORT_C TTime Min() const;
	IMPORT_C TTime Max() const;

	IMPORT_C void InternalizeL( RReadStream& aStream );
	IMPORT_C void ExternalizeL( RWriteStream& aStream ) const;

protected:
	TTime iFrom;
	TTime iTo;
	TTime iMin;
	TTime iMax;

private:
	CNSmlParamDateTimeRange( TUint32 aId, const TTime& aMinValue, const TTime& aMaxValue, TBool aMandatory );
	};

// ------------------------------------------------------------------------------------------------
// CNSmlParamBoolean
// ------------------------------------------------------------------------------------------------
class CNSmlParamBoolean : public CNSmlParam
	{
public:
	IMPORT_C static CNSmlParamBoolean* NewL( TUint32 aId );
	IMPORT_C static CNSmlParamBoolean* NewLC( TUint32 aId );

	IMPORT_C TBool Value() const;
	IMPORT_C void SetValue( TBool aValue );

	IMPORT_C void InternalizeL( RReadStream& aStream );
	IMPORT_C void ExternalizeL( RWriteStream& aStream ) const;

protected:
	TBool iValue;

private:
	CNSmlParamBoolean( TUint32 aId );	
	};

// ------------------------------------------------------------------------------------------------
// CNSmlParamNumberRange
// ------------------------------------------------------------------------------------------------
class CNSmlParamNumberRange : public CNSmlParam
	{
public:
	IMPORT_C static CNSmlParamNumberRange* NewL( TUint32 aId, TInt aMinValue = KMinTInt32, TInt aMaxValue = KMaxTInt32 );
	IMPORT_C static CNSmlParamNumberRange* NewLC( TUint32 aId, TInt aMinValue = KMinTInt32, TInt aMaxValue = KMaxTInt32 );

	IMPORT_C TInt From() const;
	IMPORT_C void SetFrom( TInt aFrom );
	IMPORT_C TInt To() const;
	IMPORT_C void SetTo( TInt aTo );
	IMPORT_C TInt Min() const;
	IMPORT_C TInt Max() const;

	IMPORT_C void InternalizeL( RReadStream& aStream );
	IMPORT_C void ExternalizeL( RWriteStream& aStream ) const;

protected:
	TInt iFrom;
	TInt iTo;
	TInt iMin;
	TInt iMax;

private:
	CNSmlParamNumberRange( TUint32 aId, TInt aMinValue, TInt aMaxValue );
	};

// ------------------------------------------------------------------------------------------------
// CNSmlParamFileName
// ------------------------------------------------------------------------------------------------
class CNSmlParamFileName : public CNSmlParam
	{
public:
	IMPORT_C static CNSmlParamFileName* NewL( TUint32 aId, const TUid& aUid = TUid::Null(), TBool aMandatory = EFalse );
	IMPORT_C static CNSmlParamFileName* NewLC( TUint32 aId, const TUid& aUid = TUid::Null(), TBool aMandatory = EFalse );

	IMPORT_C TFileName Value() const;
	IMPORT_C void SetValue( const TFileName& aValue );
	IMPORT_C TUid Uid() const;
	IMPORT_C void SetUid( const TUid& aUid );

	IMPORT_C void InternalizeL( RReadStream& aStream );
	IMPORT_C void ExternalizeL( RWriteStream& aStream ) const;

protected:
	TFileName iValue;
	TUid iUid;

private:
	CNSmlParamFileName( TUint32 aId, const TUid& aUid, TBool aMandatory );	
	};

// ------------------------------------------------------------------------------------------------
// CNSmlParamDirectoryName
// ------------------------------------------------------------------------------------------------
class CNSmlParamDirectoryName : public CNSmlParam
	{
public:
	IMPORT_C static CNSmlParamDirectoryName* NewL( TUint32 aId, TBool aMandatory = EFalse );
	IMPORT_C static CNSmlParamDirectoryName* NewLC( TUint32 aId, TBool aMandatory = EFalse );

	IMPORT_C TFileName Value() const;
	IMPORT_C void SetValue( const TFileName& aValue );

	IMPORT_C void InternalizeL( RReadStream& aStream );
	IMPORT_C void ExternalizeL( RWriteStream& aStream ) const;

protected:
	TFileName iValue;

private:
	CNSmlParamDirectoryName( TUint32 aId, TBool aMandatory );	
	};

// ------------------------------------------------------------------------------------------------
// CNSmlParamChoiceListBase
// ------------------------------------------------------------------------------------------------
class CNSmlParamChoiceListBase : public CNSmlParam
	{
public:
	enum TNSmlChoiceValueType
		{
		ENSmlChoiceResource,	// Choices are read from resource (string array)
		ENSmlChoiceValues		// Choices are stored as ready-to-be-used values
		};

	IMPORT_C ~CNSmlParamChoiceListBase();

	IMPORT_C TPtrC DesC( TInt aIndex ) const;
	IMPORT_C TInt ResourceId() const;
	IMPORT_C void SetChoicesL( TInt aResourceId );
	IMPORT_C void SetChoicesL( const CDesCArray& aChoices );
	IMPORT_C TInt NumberOfChoices() const;
	IMPORT_C TNSmlChoiceValueType GetValueType() const;

protected:
	CNSmlParamChoiceListBase( const TNSmlParamType aType, const TUint32 aId, TBool aMandatory = EFalse );

	void InternalizeL( RReadStream& aStream );
	void ExternalizeL( RWriteStream& aStream ) const;
		
protected:
	TInt iResourceId;
	CDesCArray* iChoices;
	TNSmlChoiceValueType iValueType;
	};

// ------------------------------------------------------------------------------------------------
// CNSmlParamChoiceList
// ------------------------------------------------------------------------------------------------
class CNSmlParamChoiceList : public CNSmlParamChoiceListBase
	{
public:
	IMPORT_C static CNSmlParamChoiceList* NewL( TUint32 aId, TBool aMandatory = EFalse );
	IMPORT_C static CNSmlParamChoiceList* NewLC( TUint32 aId, TBool aMandatory = EFalse );
	
	IMPORT_C TInt Value() const; // index of the current selection
	IMPORT_C void SetValue( TInt aValue );

	IMPORT_C void InternalizeL( RReadStream& aStream );
	IMPORT_C void ExternalizeL( RWriteStream& aStream ) const;

protected:
	TInt iSelected;

private:
	CNSmlParamChoiceList( TUint32 aId, TBool aMandatory );
	};

#endif // __CNSMLDSPARAMS_H__