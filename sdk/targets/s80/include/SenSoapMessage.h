/*
 * =========================================================================
 *  Name     : SenSoapMessage.h
 *  Part of  : SenUtils
 *  Created  : 2004/06/14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Utils/inc/SenSoapMessage.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.3 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */
 



#ifndef SEN_SOAP_MESSAGE_H
#define SEN_SOAP_MESSAGE_H

#include <SenWsSecurityHeader.h>
#include <SenSoapEnvelope.h>


class CSenSoapMessage :
    public CSenSoapEnvelope
    {
public:
    IMPORT_C static CSenSoapMessage* NewL();
    IMPORT_C virtual ~CSenSoapMessage();

public:
    IMPORT_C void SetSecurityHeaderL(const TDesC& aData);
	IMPORT_C TPtrC AddSecurityTokenL(TPtrC aNewToken);

protected:
	IMPORT_C CSenSoapMessage::CSenSoapMessage();    
	// From CSenSoapEnvelope
    IMPORT_C virtual void ParseHeaderL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs
        );

protected:
    IMPORT_C void BaseConstructL();

protected:
	IMPORT_C virtual CSenWsSecurityHeader* NewSecurityHeaderLC(
													const TDesC* aData=NULL);

protected:
    CSenWsSecurityHeader* ipSecurityHeader; // Owned, but element not owned
    };

#endif // SEN_SOAP_MESSAGE_H
