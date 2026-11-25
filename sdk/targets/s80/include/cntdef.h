// CNTDEF.H
//
// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
//

#ifndef __CNTDEF_H__
#define __CNTDEF_H__

#include <e32base.h>
#include <d32dbms.h>
//
#include "cntdef.hrh"

// Constants
const TInt KSpeedDialPhoneLength = 32;
const TInt KCntMinSpeedDialIndex = 1;
const TInt KCntMaxSpeedDialIndex = 9;
//Phone Match Length
const TInt KMaxPhoneMatchLength = 15;
const TInt KLowerSevenDigits = 7;

//used for firstname, lastname, companyname and e-mail address
const TInt KCntMaxTextFieldLength=255;

// Type definitions
typedef TBuf<KSpeedDialPhoneLength> TSpeedDialPhoneNumber;

/** Contact item ID. These are used to uniquely identify contact items within a 
contacts database. Contact items include contact cards, contact card templates, 
contact card groups and own cards. Contact item IDs are also used to uniquely 
identify agents. */
typedef TInt32 TContactItemId; 

/** A UID which identifies a contact item field's type. The possible values are 
defined as UIDs in cntdef.h.*/
typedef TUid TFieldType;

/** A contact item field's storage type. 

This is an unsigned integer value which identifies the type of data stored 
in a contact item field. The possible values are defined in cntdef.hrh as:

- KStorageTypeText (used by CContactTextFields)

- KStorageTypeStore (used by CContactStoreFields)

- KStorageTypeContactItemId (used by CContactAgentFields)

- KStorageTypeDateTime (used by CContactDateFields)

Note that numeric fields are not supported. Numbers (e.g. telephone 
numbers) are stored in the database using text fields. */
typedef TUint TStorageType;

/** Machine identifier. 

This is used when synchronising the contact database to identify the 
machine with which the database has been synchronised. 
@see CContactDatabase::SetLastSyncDateL() 
@see CContactDatabase::GetLastSyncDateL(). */
typedef TInt32 TContactSyncId;

/*
 * The third UID of the contacts database file, c:\system\data\contacts.cdb, 
 * is defined as KUidContactsDbFile. This should be used by file recogniser
 * implementations.
 */
const TInt KUidContactsDbFileValue=0x100065FF;
const TUid KUidContactsDbFile={KUidContactsDbFileValue};


/** NULL contact item ID. Indicates that no contact item is present. */
const TContactItemId KNullContactId=-1;
const TContactItemId KGoldenTemplateId=0;

/** Identifies a vCard that has been pasted from the clipboard into the Contacts application. */
const TUid KClipboardUidTypeVCard={0x100038f6};

/** Identifies a contact card (CContactCard). */
const TUid KUidContactCard={0x10001309};
/** Identifies a contact group (CContactGroup). */
const TUid KUidContactGroup={0x1000130A};
/** Identifies the system template (CContactTemplate). */
const TUid KUidContactTemplate={0x1000130B};
/** Identifies an own card (CContactOwnCard). */
const TUid KUidContactOwnCard={0x10004F95}; 
/** Identifies a non-system template (CContactCardTemplate). */
const TUid KUidContactCardTemplate={0x10004FF1};
const TUid KUidContactICCEntry={0x101F4A6F};

/** Identifies any CContactItem-derived class (all of the above). */
const TUid KUidContactItem={0x10005673}; 
/** This identifies the CContactCard and CContactGroup classes.
It is used internally by the contacts model. */
const TUid KUidContactCardOrGroup={0x10005F71};  


/*
 * Speed-dial UIDs. 
 * These are used to indicate the speed-dial position for a particular field.
 * They are added to the content type of a phone number field set as a 
 * speed-dial using CContactDatabase::SetFieldAsSpeedDialL().
 */
/** Field maps to the first speed dial position. */
const TUid KUidSpeedDialOne={KUidSpeedDialOneValue}; 
/** Field maps to the second speed dial position. */
const TUid KUidSpeedDialTwo={KUidSpeedDialTwoValue};
/** Field maps to the third speed dial position. */
const TUid KUidSpeedDialThree={KUidSpeedDialThreeValue};
/** Field maps to the fourth speed dial position. */
const TUid KUidSpeedDialFour={KUidSpeedDialFourValue};
/** Field maps to the fifth speed dial position. */
const TUid KUidSpeedDialFive={KUidSpeedDialFiveValue};
/** Field maps to the sixth speed dial position. */
const TUid KUidSpeedDialSix={KUidSpeedDialSixValue};
/** Field maps to the seventh speed dial position. */
const TUid KUidSpeedDialSeven={KUidSpeedDialSevenValue};
/** Field maps to the eighth speed dial position. */
const TUid KUidSpeedDialEight={KUidSpeedDialEightValue};
/** Field maps to the ninth speed dial position. */
const TUid KUidSpeedDialNine={KUidSpeedDialNineValue};

/* 
 * Contact field type UIDs.
 */
/** Address field. */
const TUid KUidContactFieldAddress={KUidContactFieldAddressValue};
/** Post office box field. */
const TUid KUidContactFieldPostOffice={KUidContactFieldPostOfficeValue};
/** Extended address field. */
const TUid KUidContactFieldExtendedAddress={KUidContactFieldExtendedAddressValue};
/** Locality field. */
const TUid KUidContactFieldLocality={KUidContactFieldLocalityValue};
/** Region field. */
const TUid KUidContactFieldRegion={KUidContactFieldRegionValue};
/** Post code field. */
const TUid KUidContactFieldPostcode={KUidContactFieldPostCodeValue};
/** Country field. */
const TUid KUidContactFieldCountry={KUidContactFieldCountryValue};

/** Company name field. */
const TUid KUidContactFieldCompanyName={KUidContactFieldCompanyNameValue};
/** Phone number field. */
const TUid KUidContactFieldPhoneNumber={KUidContactFieldPhoneNumberValue};
/** Given name field. */
const TUid KUidContactFieldGivenName={KUidContactFieldGivenNameValue};
/** Family name field. */
const TUid KUidContactFieldFamilyName={KUidContactFieldFamilyNameValue};
/** Additional name field. */
const TUid KUidContactFieldAdditionalName={KUidContactFieldAdditionalNameValue};
/** Name suffix field. */
const TUid KUidContactFieldSuffixName={KUidContactFieldSuffixNameValue};
/** Name prefix field. */
const TUid KUidContactFieldPrefixName={KUidContactFieldPrefixNameValue};
/** Hidden field. */
const TUid KUidContactFieldHidden={KUidContactFieldHiddenValue};
const TUid KUidContactFieldDefinedText={KUidContactFieldDefinedTextValue};
/** Email address field. */
const TUid KUidContactFieldEMail={KUidContactFieldEMailValue};
/** Telephone number used for a messaging service. */
const TUid KUidContactFieldMsg={KUidContactFieldMsgValue};
/** Telephone number used for SMS messages. */
const TUid KUidContactFieldSms={KUidContactFieldSmsValue};
/** Fax number field. */
const TUid KUidContactFieldFax={KUidContactFieldFaxValue};
/** Comment field. */
const TUid KUidContactFieldNote={KUidContactFieldNoteValue};
const TUid KUidContactStorageInline={KUidContactFieldStorageInlineValue};
/** Birthday field. */
const TUid KUidContactFieldBirthday={KUidContactFieldBirthdayValue};
/** URL field. */
const TUid KUidContactFieldUrl={KUidContactFieldUrlValue};
/** Template label field (a label which is used to refer to a template, for instance "work 
template", "personal template"). */
const TUid KUidContactFieldTemplateLabel={KUidContactFieldTemplateLabelValue};
/** A picture field. For instance a logo or a photo property would be mapped to this field 
type. */
const TUid KUidContactFieldPicture={KUidContactFieldPictureValue};
/** Used internally by the contacts model. */
const TUid KUidContactFieldDTMF={KUidContactFieldDTMFValue};
/** Identifies a ring tone field. This is a ring tone that is associated with a contact item. */
const TUid KUidContactFieldRingTone={KUidContactFieldRingToneValue};
/** Identifies a job title field. */
const TUid KUidContactFieldJobTitle={KUidContactFieldJobTitleValue};
/** Identifies an instant messaging address field. */
const TUid KUidContactFieldIMAddress = { KUidContactFieldIMAddressValue };
/** Identifies a Second Name field. */
const TUid KUidContactFieldSecondName = { KUidContactFieldSecondNameValue };

/*
 * CContactICCEntry (Telephony specific) UIDs.
 */
const TUid KUidContactFieldICCSlot={KUidContactFieldICCSlotValue};
const TUid KUidContactFieldICCPhonebook={KUidContactFieldICCPhonebookValue};
const TUid KUidContactFieldICCGroup={KUidContactFieldICCGroupValue};

/** Identifies a voice dial field. This is a voice recording associated with a telephone number 
field in the item. */
const TUid KUidContactsVoiceDialField={KUidContactsVoiceDialFieldValue};

/** Indicates no field present. */
const TUid KUidContactFieldNone={KUidContactFieldNoneValue};
/** Used in field type matching to indicate that all field types match. */
const TUid KUidContactFieldMatchAll={0x110FFF22};

/*
 * Contact field type vCard mappings.
 * The vCard mapping describes how the field should be handled by the 
 * vCard import/export code. 
 */
/** Field type maps to the Post office box field in an ADR vCard property value. */
const TUid KUidContactFieldVCardMapPOSTOFFICE={KIntContactFieldVCardMapPOSTOFFICE};
/** Field type maps to the Extended address field in an ADR vCard property value. */
const TUid KUidContactFieldVCardMapEXTENDEDADR={KIntContactFieldVCardMapEXTENDEDADR};
/** Field type maps to vCard property ADR. */
const TUid KUidContactFieldVCardMapADR={KIntContactFieldVCardMapADR};
/** Field type maps to the Locality field in an ADR vCard property value. */
const TUid KUidContactFieldVCardMapLOCALITY={KIntContactFieldVCardMapLOCALITY};
/** Field type maps to the Region field in an ADR vCard property value. */
const TUid KUidContactFieldVCardMapREGION={KIntContactFieldVCardMapREGION};
/** Field type maps to the Postcode field in an ADR vCard property value. */
const TUid KUidContactFieldVCardMapPOSTCODE={KIntContactFieldVCardMapPOSTCODE};
/** Field type maps to the Country field in an ADR vCard property value. */
const TUid KUidContactFieldVCardMapCOUNTRY={KIntContactFieldVCardMapCOUNTRY};

/** Field type maps to vCard property AGENT. */
const TUid KUidContactFieldVCardMapAGENT={KIntContactFieldVCardMapAGENT};
/** Field type maps to vCard property BDAY. */
const TUid KUidContactFieldVCardMapBDAY={KIntContactFieldVCardMapBDAY};
/** Field type maps to vCard property EMAIL. */
const TUid KUidContactFieldVCardMapEMAILINTERNET={KIntContactFieldVCardMapEMAILINTERNET};
/** Field type maps to vCard property GEO. */
const TUid KUidContactFieldVCardMapGEO={KIntContactFieldVCardMapGEO};
/** Field type maps to vCard property LABEL. */
const TUid KUidContactFieldVCardMapLABEL={KIntContactFieldVCardMapLABEL};
/** Field type maps to vCard property LOGO. */
const TUid KUidContactFieldVCardMapLOGO={KIntContactFieldVCardMapLOGO};
/** Field type maps to vCard property MAILER. */
const TUid KUidContactFieldVCardMapMAILER={KIntContactFieldVCardMapMAILER};
/** Field type maps to vCard property NOTE. */
const TUid KUidContactFieldVCardMapNOTE={KIntContactFieldVCardMapNOTE};
/** Field type maps to vCard property ORG. */
const TUid KUidContactFieldVCardMapORG={KIntContactFieldVCardMapORG};
/** Field type maps to vCard property PHOTO. */
const TUid KUidContactFieldVCardMapPHOTO={KIntContactFieldVCardMapPHOTO};
/** Field type maps to vCard property ROLE. */
const TUid KUidContactFieldVCardMapROLE={KIntContactFieldVCardMapROLE};
/** Field type maps to vCard property SOUND. */
const TUid KUidContactFieldVCardMapSOUND={KIntContactFieldVCardMapSOUND};
/** Field type maps to vCard property TEL. */
const TUid KUidContactFieldVCardMapTEL={KIntContactFieldVCardMapTEL};
/** Field type maps to vCard property parameter FAX. */
const TUid KUidContactFieldVCardMapTELFAX={KIntContactFieldVCardMapTELFAX};
/** Field type maps to vCard property TITLE. */
const TUid KUidContactFieldVCardMapTITLE={KIntContactFieldVCardMapTITLE};
/** Field type maps to vCard property URL. */
const TUid KUidContactFieldVCardMapURL={KIntContactFieldVCardMapURL};
/** Field maps to the vCard property N (name). Must be used in conjunction with 
a name-related field type (e.g. KUidContactFieldGivenName) to form the given 
name field mapping. */
const TUid KUidContactFieldVCardMapUnusedN={KIntContactFieldVCardMapUnusedN};
/** Field type maps to vCard property FN (the display name). */
const TUid KUidContactFieldVCardMapUnusedFN={KIntContactFieldVCardMapUnusedFN};
/** Mapping between the vCard property and field type is not required. */
const TUid KUidContactFieldVCardMapNotRequired={KIntContactFieldVCardMapNotRequired};
/** Unknown mapping between a field type and a vCard extension property. */
const TUid KUidContactFieldVCardMapUnknownXDash={KIntContactFieldVCardMapUnknownXDash};
/** Unknown mapping between field type and non-extension vCard property. */
const TUid KUidContactFieldVCardMapUnknown={KIntContactFieldVCardMapUnknown};
/** Field type maps to vCard property UID. */
const TUid KUidContactFieldVCardMapUID={KIntContactFieldVCardMapUID};
/** Field type maps to vCard property parameter WORK. */
const TUid KUidContactFieldVCardMapWORK={KIntContactFieldVCardMapWORK};
/** Field type maps to vCard property parameter HOME. */
const TUid KUidContactFieldVCardMapHOME={KIntContactFieldVCardMapHOME};
/** Field type maps to vCard property parameter MSG. */
const TUid KUidContactFieldVCardMapMSG={KIntContactFieldVCardMapMSG};
/** Field type maps to vCard property parameter VOICE. */
const TUid KUidContactFieldVCardMapVOICE={KIntContactFieldVCardMapVOICE};
/** Field type maps to vCard property parameter FAX. */
const TUid KUidContactFieldVCardMapFAX={KIntContactFieldVCardMapFAX};
/** Field type maps to vCard property parameter PREF. */
const TUid KUidContactFieldVCardMapPREF={KIntContactFieldVCardMapPREF};
/** Field type maps to vCard property parameter CELL. */
const TUid KUidContactFieldVCardMapCELL={KIntContactFieldVCardMapCELL};
/** Field type maps to vCard property parameter PAGER. */
const TUid KUidContactFieldVCardMapPAGER={KIntContactFieldVCardMapPAGER};
/** Field type maps to vCard property parameter BBS. */
const TUid KUidContactFieldVCardMapBBS={KIntContactFieldVCardMapBBS};
/** Field type maps to vCard property parameter MODEM. */
const TUid KUidContactFieldVCardMapMODEM={KIntContactFieldVCardMapMODEM};
/** Field type maps to vCard property parameter CAR. */
const TUid KUidContactFieldVCardMapCAR={KIntContactFieldVCardMapCAR};
/** Field type maps to vCard property parameter ISDN. */
const TUid KUidContactFieldVCardMapISDN={KIntContactFieldVCardMapISDN};
/** Field type maps to vCard property parameter VIDEO. */
const TUid KUidContactFieldVCardMapVIDEO={KIntContactFieldVCardMapVIDEO};
const TUid KUidContactFieldVCardMapDOM={KIntContactFieldVCardMapDOM};
/** Field type maps to vCard property parameter INTL. */
const TUid KUidContactFieldVCardMapINTL={KIntContactFieldVCardMapINTL};
/** Field type maps to vCard property parameter POSTAL. */
const TUid KUidContactFieldVCardMapPOSTAL={KIntContactFieldVCardMapPOSTAL};
/** Field type maps to vCard property parameter PARCEL. */
const TUid KUidContactFieldVCardMapPARCEL={KIntContactFieldVCardMapPARCEL};
/** Field type maps to vCard property parameter value GIF. */
const TUid KUidContactFieldVCardMapGIF={KIntContactFieldVCardMapGIF};
/** Field type maps to vCard property parameter value CGM. */
const TUid KUidContactFieldVCardMapCGM={KIntContactFieldVCardMapCGM};
/** Field type maps to vCard property parameter value WMF. */
const TUid KUidContactFieldVCardMapWMF={KIntContactFieldVCardMapWMF};
/** Field type maps to vCard property parameter value BMP. */
const TUid KUidContactFieldVCardMapBMP={KIntContactFieldVCardMapBMP};
/** Field type maps to vCard property parameter value MET. */
const TUid KUidContactFieldVCardMapMET={KIntContactFieldVCardMapMET};
/** Field type maps to vCard property parameter value PMB. */
const TUid KUidContactFieldVCardMapPMB={KIntContactFieldVCardMapPMB};
/** Field type maps to vCard property parameter value DIB. */
const TUid KUidContactFieldVCardMapDIB={KIntContactFieldVCardMapDIB};
/** Field type maps to vCard property parameter value PICT. */
const TUid KUidContactFieldVCardMapPICT={KIntContactFieldVCardMapPICT};
/** Field type maps to vCard property parameter value TIFF. */
const TUid KUidContactFieldVCardMapTIFF={KIntContactFieldVCardMapTIFF};
/** Field type maps to vCard property parameter value PDF. */
const TUid KUidContactFieldVCardMapPDF={KIntContactFieldVCardMapPDF};
/** Field type maps to vCard property parameter value PS. */
const TUid KUidContactFieldVCardMapPS={KIntContactFieldVCardMapPS};
/** Field type maps to vCard property parameter value JPEG. */
const TUid KUidContactFieldVCardMapJPEG={KIntContactFieldVCardMapJPEG};
/** Field type maps to vCard property parameter value MPEG. */
const TUid KUidContactFieldVCardMapMPEG={KIntContactFieldVCardMapMPEG};
/** Field type maps to vCard property parameter value MPEG2. */
const TUid KUidContactFieldVCardMapMPEG2={KIntContactFieldVCardMapMPEG2};
/** Field type maps to vCard property parameter value AVI. */
const TUid KUidContactFieldVCardMapAVI={KIntContactFieldVCardMapAVI};
/** Field type maps to vCard property parameter value QTIME. */
const TUid KUidContactFieldVCardMapQTIME={KIntContactFieldVCardMapQTIME};
/** Field type maps to vCard property TZ. */
const TUid KUidContactFieldVCardMapTZ={KIntContactFieldVCardMapTZ};
/** Field type maps to vCard property KEY. */
const TUid KUidContactFieldVCardMapKEY={KIntContactFieldVCardMapKEY};
/** Field type maps to vCard property parameter value X509. */
const TUid KUidContactFieldVCardMapX509={KIntContactFieldVCardMapX509};
/** Field type maps to vCard property parameter value PGP. */
const TUid KUidContactFieldVCardMapPGP={KIntContactFieldVCardMapPGP};
/** Used internally by the contacts model. */
const TUid KUidContactFieldVCardMapSMIME={KIntContactFieldVCardMapSMIME};
/** The field contains a Wireless Village instant messaging ID. */
const TUid KUidContactFieldVCardMapWV={KIntContactFieldVCardMapWV};
/** Field type mapping of a vCard property to contacts Second Name Field */
const TUid KUidContactFieldVCardMapSECONDNAME={KIntContactFieldVCardMapSECONDNAME};

/** Name of the WORK property parameter. */
_LIT(KVersitParamWork,"WORK");
/** Name of the HOME property parameter. */
_LIT(KVersitParamHome,"HOME");
/** Name of the MSG property parameter. */
_LIT(KVersitParamMsg,"MSG");
/** Name of the VOICE property parameter. */
_LIT(KVersitParamVoice,"VOICE");
/** Name of the FAX property parameter. */
_LIT(KVersitParamFax,"FAX");
/** Name of the PREF property parameter. */
_LIT(KVersitParamPref,"PREF");
/** Name of the CELL property parameter.*/
_LIT(KVersitParamCell,"CELL");
/** Name of the PAGER property parameter. */
_LIT(KVersitParamPager,"PAGER");
/** Name of the BBS property parameter. */
_LIT(KVersitParamBbs,"BBS");
/** Name of the MODEM property parameter. */
_LIT(KVersitParamModem,"MODEM");
/** Name of the CAR property parameter. */
_LIT(KVersitParamCar,"CAR");
/** Name of the ISDN property parameter. */
_LIT(KVersitParamIsdn,"ISDN");
/** Name of the VIDEO property parameter. */
_LIT(KVersitParamVideo,"VIDEO");
/** Name of the DOM property parameter. */
_LIT(KVersitParamDom,"DOM");
/** Name of the GIF property parameter. */
_LIT(KVersitParamGif,"GIF");
/** Name of the CGM property parameter. */
_LIT(KVersitParamCgm,"CGM");
/** Name of the WMF property parameter. */
_LIT(KVersitParamWmf,"WMF");
/** Name of the BMP property parameter. */
_LIT(KVersitParamBmp,"BMP");
/** Name of the MET property parameter. */
_LIT(KVersitParamMet,"MET");
/** Name of the PMB property parameter. */
_LIT(KVersitParamPmb,"PMB");
/** Name of the DIB property parameter. */
_LIT(KVersitParamDib,"DIB");
/** Name of the PICT property parameter. */
_LIT(KVersitParamPict,"PICT");
/** Name of the TIFF property parameter. */
_LIT(KVersitParamTiff,"TIFF");
/** Name of the PDF property parameter. */
_LIT(KVersitParamPdf,"PDF");
/** Name of the PS property parameter. */
_LIT(KVersitParamPs,"PS");
/** Name of the JPEG property parameter. */
_LIT(KVersitParamJpeg,"JPEG");
/** Name of the MPEG property parameter. */
_LIT(KVersitParamMpeg,"MPEG");
/** Name of the MPEG2 property parameter. */
_LIT(KVersitParamMpeg2,"MPEG2");
/** Name of the AVI property parameter. */
_LIT(KVersitParamAvi,"AVI");
/** Name of the QTIME property parameter. */
_LIT(KVersitParamQtime,"QTIME");
/** Name of the X509 property parameter. */
_LIT(KVersitParamX509,"X509");
/** Name of the PGP property parameter. */
_LIT(KVersitParamPGP,"PGP");

_LIT8(KVersitParam8Work,"WORK");
_LIT8(KVersitParam8Home,"HOME");
_LIT8(KVersitParam8Msg,"MSG");
_LIT8(KVersitParam8Voice,"VOICE");
_LIT8(KVersitParam8Fax,"FAX");
_LIT8(KVersitParam8Pref,"PREF");
_LIT8(KVersitParam8Cell,"CELL");
_LIT8(KVersitParam8Pager,"PAGER");
_LIT8(KVersitParam8Bbs,"BBS");
_LIT8(KVersitParam8Modem,"MODEM");
_LIT8(KVersitParam8Car,"CAR");
_LIT8(KVersitParam8Isdn,"ISDN");
_LIT8(KVersitParam8Video,"VIDEO");
_LIT8(KVersitParam8Dom,"DOM");
_LIT8(KVersitParam8Gif,"GIF");
_LIT8(KVersitParam8Cgm,"CGM");
_LIT8(KVersitParam8Wmf,"WMF");
_LIT8(KVersitParam8Bmp,"BMP");
_LIT8(KVersitParam8Met,"MET");
_LIT8(KVersitParam8Pmb,"PMB");
_LIT8(KVersitParam8Dib,"DIB");
_LIT8(KVersitParam8Pict,"PICT");
_LIT8(KVersitParam8Tiff,"TIFF");
_LIT8(KVersitParam8Pdf,"PDF");
_LIT8(KVersitParam8Ps,"PS");
_LIT8(KVersitParam8Jpeg,"JPEG");
_LIT8(KVersitParam8Mpeg,"MPEG");
_LIT8(KVersitParam8Mpeg2,"MPEG2");
_LIT8(KVersitParam8Avi,"AVI");
_LIT8(KVersitParam8Qtime,"QTIME");
_LIT8(KVersitParam8X509,"X509");
_LIT8(KVersitParam8PGP,"PGP");

class CContactIdArray : public CBase
/** Array of contact item IDs (TContactItemIds). 

Instances of this class are used in several contact database functions, 
for instance CContactDatabase::DeleteContactsL(). 
@publishedAll
@released
*/ 
	{
public:
	IMPORT_C static CContactIdArray* NewL();
	IMPORT_C static CContactIdArray* NewLC();
	IMPORT_C static CContactIdArray* NewL(const CContactIdArray* aArray);
	IMPORT_C static CContactIdArray* NewLC(const CContactIdArray* aArray);
	IMPORT_C ~CContactIdArray();
	inline const TContactItemId& operator[](TInt aIndex) const;
	inline TContactItemId& operator[](TInt aIndex);
	inline TInt Count() const;
	inline void Reset();
	IMPORT_C TInt Find(TContactItemId aId) const;
	IMPORT_C void AddL(TContactItemId aId);

	inline void Remove(TInt aIndex);
	inline void Remove(TInt aIndex,TInt aCount);
	inline void InsertL(TInt aIndex,TContactItemId aId);
	IMPORT_C void MoveL(TInt aOldIndex,TInt aNewIndex);
	IMPORT_C void ReverseOrder();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	
public:  // intended for internal Contacts Model usage only	
	void Sort();
	
private:
	CContactIdArray();
	void ConstructL();
	void CloneL(const CContactIdArray* aArray);
private:
	CArrayFixFlat<TContactItemId> *iIds;
	};
inline const TContactItemId& CContactIdArray::operator[](TInt aIndex) const
/** Gets the indexed TContactItemId. 

@param aIndex The position of the contact ID within the array, relative to zero. 
This must be non-negative and less than the number of objects in the array 
otherwise the operator raises a panic.
@return A reference to a const element of the array. */
	{ return (*iIds)[aIndex]; }

inline TContactItemId& CContactIdArray::operator[](TInt aIndex)
/** Gets the indexed TContactItemId. 

@param aIndex The position of the contact ID within the array, relative to zero. 
This must be non-negative and less than the number of objects in the array 
otherwise the operator raises a panic.
@return A reference to a non-const element of the array. */
	{ return (*iIds)[aIndex]; }

inline TInt CContactIdArray::Count() const
/** Gets the number of contact IDs in the array.

@return The number of contact IDs in the array. */
	{ return iIds->Count(); }

inline void CContactIdArray::Reset()
/** Removes all contact IDs from the array. */
	{ iIds->Reset(); }

inline void CContactIdArray::Remove(TInt aIndex)
/** Removes the indexed contact ID from the array.

The index value must not be negative and must not be greater than the number 
of elements in the array, otherwise the function raises a panic.

@param aIndex The index of the contact ID to remove. */
	{ iIds->Delete(aIndex); }

inline void CContactIdArray::Remove(TInt aIndex,TInt aCount)
/** Removes a block of contact IDs from the array.

This function raises a panic if any of the following are true:- 

- aCount is negative

- aIndex is negative or is greater than the number of elements currently in 
the array

- the sum of aIndex and aCount is greater than the number of elements currently 
in the array

@param aIndex The index of the first contact ID to remove.
@param aCount The number of contiguous contact IDs to delete from the array. 
If this is not specified, a value of one is assumed. */
	{ iIds->Delete(aIndex,aCount); }

inline void CContactIdArray::InsertL(TInt aIndex,TContactItemId aId)
/** Inserts a contact ID into the array.

The index must be valid or a panic occurs.

The function may attempt to expand the array buffer. If there is insufficient 
memory available, the function leaves. The leave code is one of the system 
error codes. If the function leaves, the array is left in the state it was 
in before the call. 

@param aIndex The index at which to insert the contact ID.
@param aId The contact ID to insert. */
	{ iIds->InsertL(aIndex,aId); }

#endif
