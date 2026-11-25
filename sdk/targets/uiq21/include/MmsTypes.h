// MMSTypes.h
//
// Copyright © 2001 Symbian Ltd. All rights reserved.

#ifndef __MMSTYPES_H__
#define __MMSTYPES_H__



_LIT( KMmsHeaderContentLocation, "text/vnd.wap.sl");
_LIT( KMmsHeaderMessageType, "X-Mms-Message-Type");
_LIT( KMmsHeaderTransactionId, "X-Mms-Transaction-ID");
_LIT( KMmsHeaderVersion, "X-Mms-MMS-Version");
_LIT( KMmsHeaderMessageClass, "X-Mms-Message-Class");
_LIT( KMmsHeaderExpiry, "X-Mms-Expiry");
_LIT( KMmsHeaderDeliveryTime, "X-Mms-Delivery-Time");
_LIT( KMmsHeaderPriority, "X-Mms-Priority");
_LIT( KMmsHeaderSenderVisibility, "X-Mms-Sender-Visibility");
_LIT( KMmsHeaderDeliveryReport, "X-Mms-Delivery-Report");
_LIT( KMmsHeaderDate, "Date");
_LIT( KMmsHeaderFrom, "From");
_LIT( KMmsHeaderTo, "To");
_LIT( KMmsHeaderCc, "Cc");
_LIT( KMmsHeaderBcc, "Bcc");
_LIT( KMmsHeaderSubject, "Subject");

_LIT( KMmsContentType, "Content-Type");

_LIT( KMessageTypeSendReq, "m-send-req");
_LIT( KMessageTypeNotificationInd, "m-notification-ind");
_LIT( KMessageTypeNotifyrespInd, "m-notifyresp-ind");
_LIT( KMessageTypeRetrieveConf, "m-retrieve-conf");
_LIT( KMessageTypeAcknowledgeInd, "m-acknowledge-ind");
_LIT( KMessageTypeDeliveryInd, "m-delivery-ind");


enum TMMSFieldCode
	{
	EMmsBcc = 0x01,
	EMmsCc = 0x02,
	EMmsContentLocation = 0x03,
	EMmsContentType = 0x04,
	EMmsDate = 0x05,
	EMmsDeliveryReport = 0x06,
	EMmsDeliveryTime = 0x07,
	EMmsExpiry = 0x08,
	EMmsFrom = 0x09,
	EMmsMessageClass = 0x0A,
	EMmsMessageID = 0x0B,
	EMmsMessageType = 0x0C,
	EMmsVersion = 0x0D,
	EMmsMessageSize = 0x0E,
	EMmsPriority = 0x0F,
	EMmsReadReply = 0x10,
	EMmsReportAllowed = 0x11,
	EMmsResponseState = 0x12,
	EMmsResponseText = 0x13,
	EMmsSenderVisibility = 0x14,
	EMmsStatus = 0x15,
	EMmsSubject = 0x16,
	EMmsTo = 0x17,
	EMmsTransactionID = 0x18,
	EMmsSFieldLast
	};

/**
 * An enumeration used to identify valid values
 * for MMS headers that take a yes/no value (e.g. X-MMS-Report-Allowed)
 *
 * @note
 * The explicit values set here match those in the MMS spec and <b>must not be changed unless the spec changes</b>.
 */
enum TMmsTimeToken
	{
	EMmsAbsolute = 128,
	EMmsRelative
	};


enum TMmFromToken
	{
	EMmsAddressPresent = 128,
	EMmsInsertAddToken
	};


/**
 *  As defined in WAP-230-WSP-20010705-a, Table 38
 */  
enum TWspParameterCode
	{
	EWspCharset = 0x01,

    //Fix for the defect CKH-5BBJR6: IOT Failure using a T68i & logica MMS server
	EWspStart	= 0x0a,

    //Fix for defect INC022293: adding the decoding of content-type parameters that may contain a filename
    EWspName    = 0x05,
    EWspFilename= 0x06
	};

_LIT8(KWspCharsetBig5, "big5");
_LIT8(KWspCharsetUCS2,"iso-10646-ucs-2");
_LIT8(KWspCharsetIso88591,"iso-8859-1");
_LIT8(KWspCharsetIso88592,"iso-8859-2");
_LIT8(KWspCharsetIso88593,"iso-8859-3");
_LIT8(KWspCharsetIso88594,"iso-8859-4");
_LIT8(KWspCharsetIso88595,"iso-8859-5");
_LIT8(KWspCharsetIso88596,"iso-8859-6");
_LIT8(KWspCharsetIso88597,"iso-8859-7");
_LIT8(KWspCharsetIso88598,"iso-8859-8");
_LIT8(KWspCharsetIso88599,"iso-8859-9");
_LIT8(KWspCharsetShiftJIS, "shift_JIS");
_LIT8(KWspCharsetUSascii, "us-ascii");
_LIT8(KWspCharsetUTF8, "utf-8");

const TUint KWapMultipartRelated = 0x33; // shoud be placed elsewhere.
const TUint KWapCharsetMibeValue_Utf8 = 0x6A; 
#endif
