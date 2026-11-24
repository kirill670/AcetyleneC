// GFP.H
//
// Copyright (c) 1999-2004 Symbian Software Ltd.  All rights reserved.
//
// Header file for the Generic File parser

#if !defined (__GFP_H__)
#define __GFP_H__

#include "bsp.h"

#ifdef __MESSAGING_API_V2__
class CMsvGenericFileParser : public CBaseScriptParser2
#else
class CMsvGenericFileParser : public CBaseScriptParser
#endif // __MESSAGING_API_V2__
/**
@internalComponent
@released
*/
    {
public:
#ifdef __MESSAGING_API_V2__
    IMPORT_C static CMsvGenericFileParser* NewL(CRegisteredParserDll& aRegisteredParserDll, CMsvEntry& aEntry, RFs& aFs);
#else
    IMPORT_C static CMsvGenericFileParser* NewL(CRegisteredParserDll& aRegisteredParserDll, CMsvServerEntry& aEntry, RFs& aFs);
#endif // __MESSAGING_API_V2__

    ~CMsvGenericFileParser();

    void ParseL(TRequestStatus& aStatus, const TDesC& aSms);
    void ProcessL(TRequestStatus& aStatus);

private:
    void DoCancel();
    void RunL();

private:
    enum TParseSession
        { 
        //EUnfoldMessage,     //  Don't have to unfold the message, just save it
        EParseMessage,      //  Parsing 
        ECompleteMessage    //  Completing ..
        };

#ifdef __MESSAGING_API_V2__
    CMsvGenericFileParser(CRegisteredParserDll& aRegisteredParserDll, CMsvEntry& aEntry, RFs& aFs);
#else
    CMsvGenericFileParser(CRegisteredParserDll& aRegisteredParserDll, CMsvServerEntry& aEntry, RFs& aFs);
#endif // __MESSAGING_API_V2__
    void ConstructL();

    void ChangeStateL(TParseSession aState);    // Advance state machine to next state
    void ParseMessageL();
    void CompleteMessageL();
	void GetResourceFileL(TFileName& aFileName);

    void RequestComplete(TRequestStatus& aStatus, TInt aError);

    TInt            iState;                 // Current session state
	TBuf<256>		iDescriptionText;		// Holds on to the description text.

    TRequestStatus* iReport;
    TInt            iCompleted;             // Stores completion code from previous session state
	TInt32			iBioType;
    };


#endif // __GFP_H__
