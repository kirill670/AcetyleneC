/*
 * =========================================================================
 *  Name     : SenWsSecurityHeader.h
 *  Part of  : SenUtils
 *  Created  : 2004/06/14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Utils/inc/SenWsSecurityHeader.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.5 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */
 


#ifndef SEN_WS_SECURITY_HEADER_H
#define SEN_WS_SECURITY_HEADER_H

#include <SenBaseFragment.h>
_LIT(KSecurityName, "Security");

// NEW 1.0:
//_LIT(KSecurityXmlns, "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wsswssecurity-utility-1.0.xsd");
//_LIT(KSecurityXmlnsPrefix, "wsu");

// DRAFT;
_LIT(KSecurityXmlns, "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wsswssecurity-secext-1.0.xsd");
_LIT(KSecurityXmlnsPrefix, "wsse");

// AOL demo:
//_LIT(KSecurityXmlns, "http://schemas.xmlsoap.org/ws/2003/06/secext");
//_LIT(KSecurityXmlnsPrefix, "wsse");


// FORWARD DECLARATIONS
class CSenIdentityProvider;

class CSenWsSecurityHeader :
    public CSenBaseFragment
    {
public:
    IMPORT_C static CSenWsSecurityHeader* NewL();
    IMPORT_C static CSenWsSecurityHeader* NewL(const TDesC& aData);
    IMPORT_C virtual ~CSenWsSecurityHeader();
	IMPORT_C HBufC* UsernameTokenL(CSenIdentityProvider &aIdentityProvider);
	IMPORT_C static TInt UsernameTokenL(const TDesC8& username, 
												HBufC8*& aToken);
	IMPORT_C virtual TPtrC Xmlns();
	IMPORT_C virtual TPtrC XmlnsPrefix();

protected:
    IMPORT_C CSenWsSecurityHeader();
    IMPORT_C void BaseConstructL();
    IMPORT_C void BaseConstructL(const TDesC& aData);
private:
    };

#endif // SEN_WS_SECURITY_HEADER_H
