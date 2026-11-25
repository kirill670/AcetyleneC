// ===========================================================================
//
// Copyright        :   Nokia 2004
//
// Program          :   External View Framework
//
// Identification   :   Common includes - between Client and Server
//
// ===========================================================================

#if !defined (__EVCOMMON_H__)
#define __EVCOMMON_H__

const TUid KCExternalViewPlugInInterfaceUid = {0x101F8EE5};

// Document Meta data
class TDocumentMetaData
{
public:
    TFileName   iFilename;
    TBuf<64>    iMime;
};

// Page Meta data
class TPageMetaData
{
public:
    TDocumentMetaData   iDocData;
    TInt                iPageNo;
    TInt                iSubPageNo;
    TBool               iPreCache;

};

#endif // __EVCOMMON_H__
