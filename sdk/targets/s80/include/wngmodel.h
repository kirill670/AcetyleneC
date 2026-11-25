/*
* ==============================================================================
*  Name        : wngmodel.h
*  Part of     : Word Engine
*  Interface   : 
*  Description : Model
*  Version     : 
*
*  Copyright (c) 2002 Nokia Corporation.
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


#if !defined(__WNGMODEL_H__)
#define __WNGMODEL_H__

//  INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <f32file.h>
#include <s32std.h>

#include <wngversion.h>

// CONSTANTS
const TUid KUidMsWordStyleBase={0x101F5728};
const TInt KMsWordStyleCount=91;

// MACROS

// DATA TYPES

/**	\brief	Type for an array of style short cuts.
*
*			Redefinition of CArrayFixFlat<TChar> as CStyleShortCutList;
*/
typedef CArrayFixFlat<TChar> CStyleShortCutList;

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
// Classed decalred in this file
class CWordModel;
class CWordProfileModel;
//
// Classes referenced
class RReadStream;
class RWriteStream;
class CSecureStore;
class CParaFormatLayer;
class CCharFormatLayer;
class CRichText;
class CStyleList;
class MFieldFileNameInfo;
class MFieldNumPagesInfo;
class CStreamStore;
class CStreamDictionary;
class CPrintSetup;

// CLASS DECLARATION



/* \class CWordModel
*    \brief Word processor engine interface.
*    
*    This is essentially a thin layer over the rich text support 
*    (CRichText etc.) provided by the Application Framework's ETEXT
*    component.
*
*  @lib WPeng
*  @since ?Series90_version
*/
class CWordModel : public CBase 
	{
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
		IMPORT_C static CWordModel* NewL(const MFieldFileNameInfo* aFileNameInfo,const MFieldNumPagesInfo* aFieldNumPagesInfo,const TDesC& aDriverPath);
		// Performs a minimal initialisation.
		//
		IMPORT_C static CWordModel* NewL(const MFieldFileNameInfo* aFileNameInfo,const MFieldNumPagesInfo* aFieldNumPagesInfo);

        /**
        * Destructor.
        */
		IMPORT_C ~CWordModel();

    public: // New functions
        
		// Save/Load
		IMPORT_C void StoreL(CStreamStore& aStore,CStreamDictionary& aStreamDic,const CSecurityBase* aSecurity)const;
		IMPORT_C void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aStreamDic,const CSecurityBase* aSecurity,
							   const MFieldFileNameInfo* aFileNameInfo=NULL,const MFieldNumPagesInfo* aNumPagesInfo=NULL,
							   MPictureFactory* aPictureFactory=NULL);
		IMPORT_C void StartRestore(TInt &aState);
		IMPORT_C TBool RestoreStepL(TInt &aState, const CStreamStore& aStore,const CStreamDictionary& aStreamDic,const CSecurityBase* aSecurity,
							   const MFieldFileNameInfo* aFileNameInfo=NULL,const MFieldNumPagesInfo* aNumPagesInfo=NULL,
							   MPictureFactory* aPictureFactory=NULL);
		//
		// Handles
		inline CRichText* Text();
		inline CStyleList* StyleList();
		inline CArrayFix<TInt>* PageTable();
		inline CStyleShortCutList* StyleShortCutList();
		inline TChar& NormalStyleShortCut();
		#if !defined(__HILDON__)
			inline CPrintSetup* PrintSetup();
		#endif
		IMPORT_C void RestoreMinimalL(const CStreamStore& aStore,const CStreamDictionary& aStreamDic,const CSecurityBase* aSecurity,
							   const MFieldFileNameInfo* aFileNameInfo=NULL,const MFieldNumPagesInfo* aNumPagesInfo=NULL,
							   MPictureFactory* aPictureFactory=NULL);

    public: // Functions from base classes


    protected:  // New functions
        

		template <class T> inline void DummyToPreventWarnings( T){}

		IMPORT_C CWordModel();
		IMPORT_C void ConstructL(const MFieldFileNameInfo* aFileNameInfo,const MFieldNumPagesInfo* aNumPagesInfo);
		IMPORT_C void ConstructMinimalL(const MFieldFileNameInfo* aFileNameInfo,const MFieldNumPagesInfo* aFieldNumPagesInfo,const TDesC& aDriverPath);
		void ConstructGlobalLayersL();
		//
		TStreamId StoreStylesL(CStreamStore& aStore)const;
		void RestoreStylesL(const CStreamStore& aStore,TStreamId aId);
		//
		TStreamId StoreFieldDataL(CStreamStore& aStore)const;
		void RestoreFieldDataL(const CStreamStore& aStore,TStreamId aId);
		TStreamId StoreTextDataL(CStreamStore& aStore,const CSecurityBase* aSecurity)const;
		void RestoreTextDataL(const CStreamStore& aStore,TStreamId aId,const CSecurityBase* aSecurity);
		TStreamId StoreMarkupDataL(CStreamStore& aStore)const;
		void RestoreMarkupDataL(const CStreamStore& aStore,TStreamId aId);

    protected:  // Functions from base classes
        

    private:

        /**
        * C++ default constructor.
        */

        /**
        * By default Symbian 2nd phase constructor is private.
        */

        // Prohibit copy constructor if not deriving from CBase.
        // Prohibit assigment operator if not deriving from CBase.

		void InitPrintSetupL(const MFieldFileNameInfo* aFileNameInfo,const MFieldNumPagesInfo* aNumPagesInfo,const TDesC& aDriverPath);

    public:     // Data
    
    protected:  // Data

    private:    // Data

		CParaFormatLayer* iParaFormatLayer;
		CCharFormatLayer* iCharFormatLayer;
		CRichText* iText;
		CStyleList* iStyleList;
		CPrintSetup* iPrintSetup;
		CStyleShortCutList* iStyleShortCutList;
		TChar iNormalStyleShortCut;
		CArrayFix<TInt>* iPageTable;

    public:     // Friend classes
    protected:  // Friend classes
    private:    // Friend classes


	};


#include <wngmodel.inl>


#endif      // __WNGMODEL_H__
            
// End of File
