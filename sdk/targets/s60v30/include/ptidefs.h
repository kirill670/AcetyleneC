/*
* ============================================================================
*  Name       : PtiDefs.h
*  Part of    : PtiEngine
*  Description: Predective text input engine definitions
*  Version:
*
*  Copyright © 2003-2005 Nokia Corporation.
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
#ifndef _PTI_DEFS_H
#define _PTI_DEFS_H

#include <e32keys.h>

const TInt KMaxLanguageNameLength = 50;

const TInt KErrPtiEngineBase = (-1000); //based on the value of leave in PtiEngine
enum TPtiError
    {
    KErrNoActiveLanguage = KErrPtiEngineBase-1,   
    KErrLanguageNotFound = KErrPtiEngineBase-2,
    KErrNoSuitableCore = KErrPtiEngineBase-3,
    KErrNotAllowed = KErrPtiEngineBase-4,
    KErrTooLongWord = KErrPtiEngineBase-5,
    KErrInvalidWord = KErrPtiEngineBase-6,
    KErrTooLongReading = KErrPtiEngineBase-7,
    KErrInvalidReading = KErrPtiEngineBase-8,
    KErrUserDic = KErrPtiEngineBase-9
    };


enum TPtiEngineInputMode
    {
    EPtiEngineInputModeNone = 0,
    EPtiEngineMultitapping,             // Basic multitapping input for latin languages.
    EPtiEnginePredictive,               // Predictive input for latin languages.
    EPtiEngineWordCompletion,           // Predictive input with word completion for latin languages.
    EPtiEngineNumeric,                  // Latin numeric input mode.  
    EPtiEngineQwerty,                   // Basic qwerty input mode.
    EPtiEnginePinyin,                   // Chinese pinyin mode.        
    EPtiEngineStroke,                   // Chinese stroke mode.
    EPtiEngineZhuyin,                   // Chinese zhuyin mode. 
    EPtiEngineHiraganaKanji,            // Hiragana/Kanji mode.
    EPtiEngineHiraganaKanjiPredictive,  // Predictive Hiragana/Kanji mode.
    EPtiEngineKatakana,                 // Half-width Katakana mode. 
    EPtiEngineFullWidthKatakana,        // Full-width Katakana mode.
    EPtiEngineFullWidthNumeric,         // Full-width Alphabet mode (for Japanese input).
    EPtiEngineFullWidthAlphabet,        // Full-width Alphabet mode (for Japanese input).
    EPtiEngineHiragana,                 // Hiragana only mode. 
    EPtiEnginePinyinByPhrase,           // Pinyin phrase input.         
    EPtiEngineZhuyinByPhrase,           // Zhuyin phrase input.
    EPtiEngineZhuyinQwerty,             // Zhuyin qwerty input. 
    EPtiEngineZhuyinPhraseQwerty,       // Zhuyin phrase qwerty input. 
    EPtiEnginePinyinQwerty,             // Pinyin qwerty input.
    EPtiEnginePinyinPhraseQwerty,       // Pinyin phrase qwerty input. 
    EPtiEngineStrokeQwerty,             // Stroke qwerty input.
    EPtiEngineNormalCangjieQwerty,      // Normal Cangjie qwerty input
    EPtiEngineEasyCangjieQwerty,        // Easy Cangjie qwerty input
    EPtiEngineAdvCangjieQwerty,         // Advanced Cangjie qwerty input
    EPtiEngineHiraganaKanjiQwerty,      // Hiragana/Kanji qwerty input mode.
    EPtiEngineHiraganaKanjiPredictiveQwerty,  // Predictive Hiragana/Kanji qwerty input mode.
    EPtiEngineKatakanaQwerty,           // Half-width Katakana qwerty input mode. 
    EPtiEngineFullWidthKatakanaQwerty,  // Full-width Katakana qwerty input mode.
    EPtiEngineFullWidthNumericQwerty,   // Full-width Alphabet qwerty input mode (for Japanese input).
    EPtiEngineFullWidthAlphabetQwerty,  // Full-width Alphabet qwerty input mode (for Japanese input).
    EPtiEngineHiraganaQwerty,           // Hiragana only qwerty input mode. 
    EPtiEngineMaxInputModes = EPtiEngineHiraganaQwerty
    };



// Key ids for conventional phone key pad.
enum TPtiKey
    {
    EPtiKeyNone = 0,
    
    EPtiKey1    = '1',
    EPtiKey2    = '2',
    EPtiKey3    = '3',
    EPtiKey4    = '4',
    EPtiKey5    = '5',
    EPtiKey6    = '6',
    EPtiKey7    = '7',
    EPtiKey8    = '8',
    EPtiKey9    = '9',
    EPtiKeyStar = '*',
    EPtiKey0    = '0',
    EPtiKeyHash = '#',

    // alternate names
    EPtiKeyPunct = EPtiKey1,
    EPtiKeyABC   = EPtiKey2,
    EPtiKeyDEF   = EPtiKey3,
    EPtiKeyGHI   = EPtiKey4,
    EPtiKeyJKL   = EPtiKey5,
    EPtiKeyMNO   = EPtiKey6,
    EPtiKeyPQRS  = EPtiKey7,
    EPtiKeyTUV   = EPtiKey8,
    EPtiKeyWXYZ  = EPtiKey9,

    // qwerty keys
    // values are same as incoming scan codes from key driver.
    EPtiKeyQwerty1     = 0x31,
    EPtiKeyQwerty2     = 0x32,
    EPtiKeyQwerty3     = 0x33,
    EPtiKeyQwerty4     = 0x34,
    EPtiKeyQwerty5     = 0x35,
    EPtiKeyQwerty6     = 0x36,
    EPtiKeyQwerty7     = 0x37,
    EPtiKeyQwerty8     = 0x38,
    EPtiKeyQwerty9     = 0x39,
    EPtiKeyQwerty0     = 0x30,

	EPtiKeyQwertyPlus  = 0x2b,
    EPtiKeyQwertyMinus = EStdKeyMinus,
    EPtiKeyQwertyComma = EStdKeyComma,
    EPtiKeyQwertySemicolon = EStdKeySemiColon,
    EPtiKeyQwertyFullstop = EStdKeyFullStop,
    EPtiKeyQwertyHash = EStdKeyHash,
    EPtiKeyQwertySlash = EStdKeyForwardSlash,
    EPtiKeyQwertyApostrophe = EStdKeySingleQuote,
    EPtiKeyQwertySpace = EStdKeySpace,

    EPtiKeyQwertyA = 0x41,
    EPtiKeyQwertyB = 0x42,
    EPtiKeyQwertyC = 0x43,
    EPtiKeyQwertyD = 0x44,
    EPtiKeyQwertyE = 0x45,
    EPtiKeyQwertyF = 0x46,
    EPtiKeyQwertyG = 0x47,
    EPtiKeyQwertyH = 0x48,
    EPtiKeyQwertyI = 0x49,
    EPtiKeyQwertyJ = 0x4a,
    EPtiKeyQwertyK = 0x4b,
    EPtiKeyQwertyL = 0x4c,
    EPtiKeyQwertyM = 0x4d,
    EPtiKeyQwertyN = 0x4e,
    EPtiKeyQwertyO = 0x4f,
    EPtiKeyQwertyP = 0x50,
    EPtiKeyQwertyQ = 0x51,
    EPtiKeyQwertyR = 0x52,
    EPtiKeyQwertyS = 0x53,
    EPtiKeyQwertyT = 0x54,
    EPtiKeyQwertyU = 0x55,
    EPtiKeyQwertyV = 0x56,
    EPtiKeyQwertyW = 0x57,
    EPtiKeyQwertyX = 0x58,
    EPtiKeyQwertyY = 0x59,
    EPtiKeyQwertyZ = 0x5a
    };



enum TPtiEngineCapsBits
    {
    EWordCompletion          = 0x01,
    EReordering              = 0x02,
    ENextWordPrediction      = 0x04,
    ESupportUserDictionaries = 0x08,
    ESupportSCTToneMarks     = 0x10,
    ESupportCangjieInput     = 0x20
    };


enum TPtiTextCase
    {
    EPtiCaseLower = 0,
    EPtiCaseUpper,
    EPtiCaseChrLower,     // Only needed with qwerty input.
    EPtiCaseChrUpper      // Only needed with qwerty input.  
    };


enum TPtiCharConversion
    {
    EPtiSimplifiedToComplex = 0x01,  // Chinese simplified to Chinese complex
    EPtiUcs2ToUtf8 = 0x02,           // Unicode to utf8
    EPtiUcs2ToBig5 = 0x04,           // Unicode to big5
    EPtiUcs2ToGB = 0x08,             // Unicode to Guo-Biao 
    EPtiUtf8ToUcs2 = 0x10,           // Utf8 to Unicode
    EPtiKo2ToWc = 0x20,              // KSC5601 to Hangul Syllable
    EPtiWcToKo2 = 0x30,              // Hangul Syllable to KSC5601
    EPtiBig5ToUcs2 = 0x40,           // Big5 to Unicode
    EPtiComplexToSimplified = 0x80   // Chinese complex to Chinese simplified
    };


enum TPtiSpelling   
    {
    EPtiStrokes = 0x01,
    EPtiPinyin = 0x02,
    EPtiBopomofo = 0x04,
    EPtiZhuyin = 0x08
    };


enum TPtiChineseVariant
    {
    EPtiChineseVariantPrc = 0,
    EPtiChineseVariantHk, 
    EPtiChineseVariantTw 
    };


enum TPtiEngineCommand
    {
    EPtiCommandNone,
    EPtiCommandUserActionLeft,
    EPtiCommandUserActionRight,
    EPtiCommandUserActionConvert,
    EPtiCommandUserActionPrevious,
    EPtiCommandUserActionLengthen,
    EPtiCommandUserActionShorten,
    EPtiCommandUserActionCancel,
    EPtiCommandUserActionComplete,
    EPtiCommandUserActionAllComplete,
    EPtiCommandUserActionGetCurrentIndexOfCandidates,
    EPtiCommandUserActionCompleteCandidate,
    EPtiCommandUserActionCompleteFull0,
    EPtiCommandUserActionCompleteFull1,
    EPtiCommandUserActionCompleteFull2,
    EPtiCommandUserActionCompleteFull3,
    EPtiCommandUserActionCompleteFull4,
    EPtiCommandUserActionCompleteFull5,
    EPtiCommandUserActionCompleteFull6,
    EPtiCommandUserActionCompleteFull7,
    EPtiCommandUserActionCompleteFull8,
    EPtiCommandUserActionCompleteFull9,
    EPtiCommandUserActionCompleteHalf0,
    EPtiCommandUserActionCompleteHalf1,
    EPtiCommandUserActionCompleteHalf2,
    EPtiCommandUserActionCompleteHalf3,
    EPtiCommandUserActionCompleteHalf4,
    EPtiCommandUserActionCompleteHalf5,
    EPtiCommandUserActionCompleteHalf6,
    EPtiCommandUserActionCompleteHalf7,
    EPtiCommandUserActionCompleteHalf8,
    EPtiCommandUserActionCompleteHalf9,
    EPtiCommandEnableToneMarks,
    EPtiCommandDisableToneMarks,
    EPtiCommandResetToneMark,
    EPtiCommandIncrementToneMark,
    EPtiCommandIncrementToneMarkOverrideInvalid,
    EPtiCommandReloadLearningInfo,
    EPtiCommandUserDictionaryDelaySaving,
    EPtiCommandUserDictionarySaveNow,
    EPtiCommandUserActionSetCurrentIndexOfCandidates,  
    EPtiCommandUseLatinDefaultKeyMap,       
    EPtiCommandUseLatinCaseUpperOnlyKeyMap, 
    EPtiCommandUseLatinCaseLowerOnlyKeyMap,
	EPtiCommandResetLearningInfo,
	EPtiCommandPollQwertyDeadKeyRootFlag,             // Indicates that dead key root char was added to buffer.
	EPtiCommandGetAndClearDeadKeyRootChar,
	EPtiCommandDeadKeyWaiting,
	EPtiCommandQueryAndClearGetAllFlag,
	EPtiCommandGetAndClearVowelSequence,			
    EPtiCommandSetMultitapTimer         // Set multitap timer for japanese varint only
    // More commands can be added here...
    };


class TPtiLangName
    {
    public:
        TInt iLanguageCode;
        TBuf<KMaxLanguageNameLength> iName;
    };


// This is language code for 'numeric' language.
// It is langugae object which is always available and
// has only numeric input mode.
#define ELangNumeric 0x5000


class MPtiCoreInfo 
    {
    public: 
        virtual TBool WordCompletion() const = 0;
        virtual TBool Reordering() const = 0;
        virtual TInt MaximumWordLength() const = 0;
        virtual TInt MaximumNumberOfCandidates() const = 0;
        virtual TBool NextWordPrediction() const = 0;
        virtual TPtrC VendorString() const = 0;
        virtual TUint32 CapsBits() const = 0;
        virtual TInt32 Uid() const = 0;
        virtual TUint32 CharConversions() const = 0;
        virtual TUint32 Spellings() const = 0;
    };



class TPtiCoreInfo : public MPtiCoreInfo
    {
    public:
        inline TBool WordCompletion() const;
        inline TBool Reordering() const;
        inline TInt MaximumWordLength() const;
        inline TInt MaximumNumberOfCandidates() const;
        inline TBool NextWordPrediction() const;
        inline TPtrC VendorString() const;
        inline TInt32 Uid() const;
        inline TUint32 CharConversions() const;
        inline TUint32 Spellings() const;

        inline TUint32 CapsBits() const;
        inline void SetCapsBits(TUint32 aBits);
        inline void SetVendorString(const TDesC& aStr);
        inline void SetMaxWordLength(TInt aMaxLen);
        inline void SetUid(TInt32 aUid);
        inline void SetSpellings(TUint32 aSpellings);
        inline void SetMaxNumberOfCandidates(TInt aMax);
        inline void SetCharConversions(TUint32 aConvs);

	private:
		TUint32 iCapsBits;
		TPtrC iVendorIdStr;
		TInt iMaxWordLength;
		TInt iMaxNumberOfCandidates;
		TInt32 iUid;
		TUint32 iCharConversions;
		TUint32 iSpellings;
	};


#define KPtiEngineChineseSeparator 0x0027

// Tone marks for pinyin input
enum
    {
    KPtiPinyinTone0 = 0x02C9,
    KPtiPinyinTone1 = 0x02CA,
    KPtiPinyinTone2 = 0x02C7,
    KPtiPinyinTone3 = 0x02CB,
    KPtiPinyinTone4 = 0x0020
    };

// Tone marks for zhuyin input
enum
    {
    KPtiZhuyinTone0 = 0x0020,
    KPtiZhuyinTone1 = 0x02CA,
    KPtiZhuyinTone2 = 0x02C7,
    KPtiZhuyinTone3 = 0x02CB,
    KPtiZhuyinTone4 = 0x02D9
    };


class TPtiNumericKeyBinding
	{
	public:
		TUint16 iChar;	
		TPtiKey iKey;
		TPtiTextCase iCase;		
	};


#include "PtiDefs.inl"

#endif // _PTI_DEFS_H

// End od file
