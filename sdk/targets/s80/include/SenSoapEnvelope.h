/*
 * =========================================================================
 *  Name     : SenSoapEnvelope.h
 *  Part of  : SenUtils
 *  Created  : 2004/06/14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Utils/inc/SenSoapEnvelope.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.4 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */
 


#ifndef SEN_SOAP_ENVELOPE_H
#define SEN_SOAP_ENVELOPE_H

#include <SenBaseFragment.h>

// CONSTANTS
_LIT(KSoapXmlns, "http://schemas.xmlsoap.org/soap/envelope/");
_LIT(KEnvelopeName, "Envelope");
_LIT(KEnvelopeQName, "S:Envelope");
_LIT(KHeaderName, "Header");
_LIT(KHeaderQName, "S:Header");
_LIT(KBodyName, "Body");
_LIT(KBodyQName, "S:Body");

const TInt KStateParsingSoapHeader	= 20; // ignore state (even num)
const TInt KStateParsingSoapBody	= 40; // ignore state (even num)
const TInt KStateParsingSoapFault	= 5;  // save state (odd number)

class CSenSoapEnvelope :
    public CSenBaseFragment
    {
public:
    IMPORT_C static CSenSoapEnvelope* NewL();
    IMPORT_C virtual ~CSenSoapEnvelope();

public:
    // From CSenBaseFragment
    IMPORT_C virtual void StartElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs);

    IMPORT_C virtual void EndElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName);

//	IMPORT_C void CharactersL( // 2004-09-10, matmatt
//		const TDesC& aChars,
//		TInt /*aStart*/,
//		TInt /*aLength*/);


public:
    IMPORT_C virtual TPtrC SetBodyL(const TDesC& aBody);
    IMPORT_C virtual CSenElement& BodyL();
    IMPORT_C virtual CSenElement& HeaderL();
    IMPORT_C virtual CSenElement& AddHeaderL(CSenElement& aHeaderElement);
	IMPORT_C virtual HBufC* BodyAsString();

protected:
    /**
     *  This method should be overridden by subclasses. Default impl
     *  does nothing.
     */
    IMPORT_C virtual void ParseHeaderL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs
        );

protected:
    IMPORT_C void BaseConstructL();

protected:
	CSenBaseFragment* ipBodyFragment;
	CSenSoapEnvelope();

	};
#endif // SEN_SOAP_ENVELOPE_H
