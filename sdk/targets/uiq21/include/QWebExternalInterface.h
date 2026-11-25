// QWebExternalInterface.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#if !defined(_QWEBEXTERNALINTERFACE_H_)
#define _QWEBEXTERNALINTERFACE_H_

/**
* The maximum length of an URL.
*/
const TInt KWebMaxUrlLen = 450;

/**
* The Quartz Web application's UID
*/
const TUid KUidQWebApp = {0x100051e6};

/**
* The DNL UID for the Quartz Web List view. This is the bookmark list in the
* web application. This view does not have any custom message IDs.
*/
const TUid KUidQWebListView = {0x10005fb9};

/**
* The DNL UID for the Quartz Web page view. This is the HTML view that renders
* all the pages and where plug-ins (such as Java) run. It can take one message,
* which is KQWebCustomMsgId and it signals that there is a TQWebDNLUrlEntryBuf
* comming with an URL in it.
*/
const TUid KUidQWebPageView = {0x10005fba};

/**
* This is a message used only in the DNL for the Page view. It signals that
* there is a TQWebDNLUrlEntryBuf with an URL, and that URL should be opened.
*/
const TUid KQWebCustomMsgId = {1};

/**
* When KQWebCustomMsgId is used as a message when you enter the page view, this
* is the correct class to send the URL in.
*/
class TQWebDNLUrlEntry
{
public:
	/**
	* The URL as a string.
	*/
	TBufC<KWebMaxUrlLen> iUrl; // The url to open
};

/**
* To be able to send the TQWebDNLUrlEntry to the ViewActivatedL method, it
* needs to be put into a package buffer. This is the buffer that should be
* used for this purpose.
*/
typedef TPckgBuf<TQWebDNLUrlEntry> TQWebDNLUrlEntryBuf;

#endif
