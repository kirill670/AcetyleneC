/*
* =============================================================================
*  Name        : eikparse.h
*  Part of     : CKON
*  Interface   : Rich Text Editor API
*  Description : Parsing manager class used by Rich Text Editor.
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* =============================================================================
*/

#ifndef __EIKPARSE_H__
#define __EIKPARSE_H__

// INCLUDES
#include <mparser.h>
#include <EikEdwob.h>
#include <eikcmobs.h>

// FORWARD DECLARATIONS
class CEikRichTextEditor;
class CEikonEnv;
class CEikButtonGroupContainer;

// CONSTANTS
/** @internal */
const TInt KNullStartPos    =-1;

/**
*  The <code>CEikParserManager</code> class provides the parsing manager used 
*  by the <code>CEikRichTextEditor</code> class to ensure that text is parsed 
*  correctly.
*  @internal to CKON.
*/
class CEikParserManager : public CBase, public MEikEdwinObserver, public MEikCommandObserver
    {
    public:

        /**
        * Static constructor.
        */
        static CEikParserManager* NewL(CEikRichTextEditor& aEditor);

        /**
        * Destructor.
        */
        ~CEikParserManager();
    public:
        void Start(TInt aStartPos,TInt aLength);
        void AddParserCommandButtonL(TInt aTagStart, TInt aTagLength);
        void RemoveParserCommandButton();
        TInt TagEndPos() const;

    private:
        CEikParserManager(CEikRichTextEditor& aEditor);
        void ConstructL();
        void Start();
        void StartTimer();
        void Reset();
        static TInt ParseTextCallbackL(TAny* aSelf);
        void ParseTextL();
    
    private: // from MEikEdwinObserver
        void HandleEdwinEventL(CEikEdwin* aEdwin,TEdwinEvent aEventType);
    //from MEikCommandObserver
        void ProcessCommandL(TInt aCommandId);

    private:
        CPeriodic* iTimer;
        CEikRichTextEditor& iEditor;
        TInt iStartPos; // start of changed area
        TInt iLength; // length of changed area
        MParser* iParser;
        TInt iTagStart; // start of tag cursor is over
        TInt iTagLength; // length of tag cursor is over
        TBool iStateChanged;
        TInt iParseScanDelay;
    };


#endif  // EIKPARSE_H

// End of File
