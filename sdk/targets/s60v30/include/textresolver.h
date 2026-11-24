/*
* ============================================================================
*  Name     : CTextResolver from TextResolver.h
*  Part of  : CommonEngine.dll
*
*  Description:
*  - resolve an error code to display text
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
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


#if !defined TEXT_RESOLVER_H
#define TEXT_RESOLVER_H

#include <coemain.h>    //  CCoeEnv
#include <TextResolver.hrh> // Resource flags 

// DEFINES
typedef CArrayFixFlat<TInt> CErrorResourceIdArray;
typedef CArrayFixFlat<TInt> CErrorResourceFlagArray;

/**
* This class offers methods to
*  - resolve an error code to display text
*
*
* Usage (typically as instance variable)
*
*   #include <textresolver.h>
*
*   // Construction of an CTextResolver instance:
*   CTextResolver* iTextResolver = CTextResolver::NewLC(*iCoeEnv); 
*
*   //... code producing an KErr*, stored in the variable "err"...
*
*   // Error Resolving, Simple:
*
*   TPtrC buf;
*   if (err != KErrNone)
*        buf.Set(iTextResolver->ResolveErrorUnlimited(err)); // Add Context to 2nd param if needed.
*
*   // Note that buf will only be valid as long as CTextResolver 
*   // instance is alive and no new error is resolved by the same instance.
*   // If for some reason you need to store the resolved error beyond immediate use, make a copy of it.
*
*   // Error Resolving, Advanced:
*
*   TInt textId;
*   TUint flags;
*   TPtrC buf;
*   if (err != KErrNone)
*        buf.Set(iTextResolver->ResolveErrorUnlimited(err, textId, flags)); // Add Context to 4th param if needed.
*    
*   CleanupStack::PopAndDestroy(); // iTextResolver, Free loaded resources 
*
*/

class CTextResolver : public CBase
    {

    public:

        // Optional error contexes for aiding the mapping of
        // error codes to texts in a unique way.
        // If no context is given the assumption is that error codes
        // are unique.
        enum TErrorContext
            {
            // Context defined automatically from error code value.
            // Here it is assumed that each error code is in unique and in
            // own range. This applies for Symbian OS, Etel, BIO errors
            ECtxAutomatic = 0,
            ECtxNoCtx = 1, // No context in returned string, just ':' and newline
			ECtxNoCtxNoSeparator = 2   // No context, ':' or newline added to returned string.

            // More contexes to be added, if needed.
            // caller error is not in unique among all the errors.
            // (for example -15 or -23 used as subsystem error and they mean totally else
            // for some else subsystem)
            // For those errors we need to add a context which must is set
            // by the caller
            };
    public:
        /**
         * Constructors.
         */
        IMPORT_C static CTextResolver* NewL(CCoeEnv& aEnv);
        IMPORT_C static CTextResolver* NewLC(CCoeEnv& aEnv);

        IMPORT_C static CTextResolver* NewL();
        IMPORT_C static CTextResolver* NewLC();

        
        /** Destructor */
        IMPORT_C ~CTextResolver();

        /**
         * This version is for advanced use:
         * Resolve given Symbian OS error (KErr*) and return the resolved text.
         * Resolved text can be of any length.
         * @param aError any error code, for example ETel error.
         * @param aTextId ID of the returned text.
         * @param aFlags Priority of the returned error.
         *        The priority is defined by the this module !
         * @param aContext Context of the error 
         * @return Error text for the mapped error.
         *         For non-mapped errors returns "Unmapped error" with
         *         error code included.
         */
		IMPORT_C const TDesC& ResolveErrorString(
             TInt aError,
             TInt& aTextId,
             TUint& aFlags,
             TErrorContext aContext = ECtxAutomatic);
		 /**
         * For "Normal" Use:
         * Resolve given Symbian OS error (KErr*) and return the resolved text.
         * Resolved text can be of any length.
         * @param aError any error code, for example ETel error.
         * @param aContext Context of the error 
         * @return Error text for the mapped error.
         *         For non-mapped errors returns "Unmapped error" with
         *         error code included.
         */
	    IMPORT_C const TDesC& ResolveErrorString(
             TInt aError,
             TErrorContext aContext = ECtxAutomatic);
	private:
        
        virtual TInt ResourceForError(TInt aError);
        virtual void LoadResourceFilesL();

        // Construction
        CTextResolver(CCoeEnv& aEnv);
        CTextResolver();
        void ConstructL();

        // Utility
        void FindFullPathOfResourceFile(TFileName& aResFile) const;
        void ReadResourcesToArraysL(TInt& aError, TInt& aTextId);
        void Reset();
        void PrepareReaderLC(TResourceReader& reader);

        // returns NULL if fails
        HBufC* ReadUnicodeString(const TInt& aTextId);

        // returns false if any memory allocation fails or initial values 
        // of necessary pointers are NULL, indicating alloc failure earlier.
        TBool AddContextAndSeparator(TErrorContext aContext);

    private:
        
        CCoeEnv*                            iCoe;
        RResourceFile                       iRFile;
        TInt                                iRDSupport;
        TInt                                iBaseResourceFileOffset;
        CArrayFix<TInt>*                    iStartError;
        CArrayFix<TInt>*                    iAppTexts;
        CArrayPtr<CErrorResourceIdArray>*   iErrorTexts;
        CArrayPtr<CErrorResourceFlagArray>* iFlags;
        HBufC*                              iTextBuffer;
        HBufC*                              iAppNameText;
        HBufC*                              iContextSeparator;
        RFs                                 iFs;
        TPtrC                               iTruncatedTextPointer;
    };

#endif

// Enf of File
