/*
* ============================================================================
*  Name       : PtiCore.h
*  Part of    : PtiEngine
*  Description: Predective text input engine core interface.
*  Version:
*
*  Copyright © 2003 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/
#ifndef _PTI_CORE_H
#define _PTI_CORE_H

// INCLUDES
#include <badesca.h> 
#include "PtiDefs.h"
#include "PtiLanguage.h"
#include "PtiUserDictionary.h"

// FORWARD DECLARATIONS
class CPtiEngine;
class MPtiEngineCompositionDataInterface;
class MPtiUserDictionaryEntry;

const TInt KDefaultCoresGran = 3;

class MPtiCore
	{
	// General API
	public:
		virtual void InitializeL(CPtiEngine* aOwner, TDes* aTextBuffer, CArrayPtrFlat<CPtiCoreLanguage>* aLanguageList, TBool aUseDefautUserDictionary) = 0;
		virtual void DropLanguages(CArrayPtrFlat<CPtiCoreLanguage>* aLanguageList) = 0;
		virtual TInt OpenLanguageL(CPtiCoreLanguage *aLanguage) = 0;
		virtual TInt CloseLanguageL() = 0;	
		virtual TPtrC GetCurrentWord() const = 0;
		virtual TInt CommitCurrentWord() = 0;		
		virtual MPtiCoreInfo* GetCoreInfo() = 0;
		virtual TInt SetReordering(TBool aStatus) = 0;
		virtual void AppendKeyPress(TPtiKey aKey) = 0;
		virtual void DeleteKeyPress() = 0;
		virtual void ClearBuffer() = 0;
		virtual TInt SetCurrentInputSequence(TPtrC8 aInput) = 0;
		virtual TInt Convert(TPtiCharConversion aType,
							 TAny* aInput,
							 TInt aInputLength,
							 TAny* aOutput) = 0;

		virtual TInt SetExternalKeyMapL(TPtiEngineInputMode aMode,
			                            TPtiKey aKey,
									    TDesC& aKeyMap,
										TPtiTextCase aCase) = 0;
		virtual TInt GetSpelling(TUint16 aInput, TDes& aOutput, TPtiSpelling aType) = 0;
		virtual TInt CancelTimerActivity() = 0;
		virtual TInt HandleCommandL(TPtiEngineCommand aCommand, TAny* aParams) = 0;

	// Predictive latin API
		virtual TInt NumberOfCandidates() = 0;
		virtual TInt GetCandidateListL(CDesCArray& aList) = 0;
		virtual TInt GetNextWordCandidateListL(CDesCArray& aList) = 0;
		virtual TInt GetFirstCandidate(TDes& aResult) = 0;
		virtual TInt GetNextCandidate(TDes& aResult) = 0;
		virtual TInt GetPreviousCandidate(TDes& aResult) = 0;
	
	// User dictionary API
	public:
		virtual TInt AddUserDictionaryEntry(MPtiUserDictionaryEntry& aEntry, CPtiUserDictionary* aDict) = 0;
		virtual TInt RemoveUserDictionaryEntry(MPtiUserDictionaryEntry& aEntry, CPtiUserDictionary* aDict) = 0;
        virtual TInt NumberOfEntriesInUserDictionary(CPtiUserDictionary* aDict) = 0;
		virtual TInt GetUserDictionaryEntry(TInt aIndex, MPtiUserDictionaryEntry& aResult, CPtiUserDictionary* aDict) = 0;
		virtual CPtiUserDictionary* CreateEmptyUserDictionaryL(TInt aMaxSize) = 0;
		virtual TInt AttachUserDictionary(CPtiUserDictionary* aDict) = 0;
		virtual TBool DetachUserDictionary(CPtiUserDictionary* aDict) = 0;		

	// Chinese API
	public:
		virtual TPtrC GetCandidatePage() = 0;
		virtual TBool NextCandidatePage() = 0;
		virtual TBool PreviousCandidatePage() = 0;
		virtual TBool MoreCandidatePages() = 0;
		virtual void SetCandidatePageLength(TInt aLength) = 0;
		virtual TPtrC GetPhoneticSpelling(TInt aIndex) const = 0; 
		virtual TInt PhoneticSpellingCount() const = 0;	
	    virtual TBool SelectPhoneticSpelling(TInt aIndex) = 0;
	    virtual TInt SelectedPhoneticSpelling() const = 0; 
		virtual TBool ToneMark(TText& aToneMark) const = 0;
		virtual TBool IsToneMarkValidForSpelling() = 0;
		virtual TBool SetPredictiveChineseChar(const TDesC& aChar) = 0;
		virtual TBool SetToneMark(TInt aToneMark) = 0;

	// Japanese API
	public:
		virtual TPtrC ReadingTextL() = 0;
		virtual MPtiEngineCompositionDataInterface* CompositionData() = 0;
	};


class CPtiCore : public CBase, public MPtiCore
	{
	public: // Plugin household methods
		IMPORT_C static CPtiCore* CreateCoreL(TUid aCoreUid);
		IMPORT_C static CArrayFix<TInt>* ListCoresLC();

	public: 
		IMPORT_C ~CPtiCore();

	public:
	/*
	 * This section provides empty default implementations for most of the 
	 * MPtiCore mthods.
	 */

	// 	General methods.
		IMPORT_C TInt SetCurrentInputSequence(TPtrC8 aInput);
		IMPORT_C TInt Convert(TPtiCharConversion aType,
							  TAny* aInput,
							  TInt aInputLength,
							  TAny* aOutput);
		IMPORT_C TInt GetSpelling(TUint16 aInput,
			                      TDes& aOutput,
								  TPtiSpelling aType);
		IMPORT_C TInt SetExternalKeyMapL(TPtiEngineInputMode aMode,
			                             TPtiKey aKey,
									     TDesC& aKeyMap,
										 TPtiTextCase aCase);
		IMPORT_C TInt CommitCurrentWord();		
		IMPORT_C TPtrC GetCurrentWord() const;

	// Predictive latin API
		IMPORT_C TInt NumberOfCandidates();
		IMPORT_C TInt GetCandidateListL(CDesCArray& aList);
		IMPORT_C TInt GetNextWordCandidateListL(CDesCArray& aList);
		IMPORT_C TInt GetFirstCandidate(TDes& aResult);
		IMPORT_C TInt GetNextCandidate(TDes& aResult);
		IMPORT_C TInt GetPreviousCandidate(TDes& aResult);
	
	// User dictionary API
	public:
		IMPORT_C TInt AddUserDictionaryEntry(MPtiUserDictionaryEntry& aEntry, CPtiUserDictionary* aDict);
		IMPORT_C TInt RemoveUserDictionaryEntry(MPtiUserDictionaryEntry& aEntry, CPtiUserDictionary* aDict);
        IMPORT_C TInt NumberOfEntriesInUserDictionary(CPtiUserDictionary* aDict);
		IMPORT_C TInt GetUserDictionaryEntry(TInt aIndex, MPtiUserDictionaryEntry& aResult, CPtiUserDictionary* aDict);
		IMPORT_C CPtiUserDictionary* CreateEmptyUserDictionaryL(TInt aMaxSize);
		IMPORT_C TInt AttachUserDictionary(CPtiUserDictionary* aDict);
		IMPORT_C TBool DetachUserDictionary(CPtiUserDictionary* aDict);		

	// Chinese API
	public:
		IMPORT_C TPtrC GetCandidatePage();
		IMPORT_C TBool NextCandidatePage();
		IMPORT_C TBool PreviousCandidatePage();
		IMPORT_C TBool MoreCandidatePages();
		IMPORT_C void SetCandidatePageLength(TInt aLength);
		IMPORT_C TPtrC GetPhoneticSpelling(TInt aIndex) const; 
		IMPORT_C TInt PhoneticSpellingCount() const;	
	    IMPORT_C TBool SelectPhoneticSpelling(TInt aIndex);
	    IMPORT_C TInt SelectedPhoneticSpelling() const; 
		IMPORT_C TBool ToneMark(TText& aToneMark) const;
		IMPORT_C TBool IsToneMarkValidForSpelling();
		IMPORT_C TBool SetPredictiveChineseChar(const TDesC& aChar);
		IMPORT_C TBool SetToneMark(TInt aToneMark);

	// Japanese API
	public:
		IMPORT_C TPtrC ReadingTextL();
		IMPORT_C MPtiEngineCompositionDataInterface* CompositionData();

	private:
		inline void SetDestructorKeyId(TInt aDtorKeyId);

	private:
		TInt iDtorKeyId;
		TInt Reserved_1;
	};


inline void CPtiCore::SetDestructorKeyId(TInt aDtorKeyId)
	{
	iDtorKeyId = aDtorKeyId;
	}

#endif _PTI_CORE_H

// End of file


