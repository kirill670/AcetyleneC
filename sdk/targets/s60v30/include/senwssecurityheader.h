/*
* ==============================================================================
*  Name        : SenWsSecurityHeader.h
*  Part of     : Web Services Framework / Utils
*  Interface   : 
*  Description : CSenWsSecurityHeader represents security header functionality
*                according to oasis wss spesifications (2004/01)
*  Version     :
*
*  Copyright © 2002-2005 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/

#ifndef SEN_WS_SECURITY_HEADER_H
#define SEN_WS_SECURITY_HEADER_H

//  INCLUDES
#include <SenBaseFragment.h>

// CONSTANTS
_LIT8(KSecurityName, "Security");
_LIT8(KSecurityXmlNs, "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd");
_LIT8(KSecurityXmlNsPrefix, "wsse");

// FORWARD DECLARATIONS
class CSenIdentityProvider;

// CLASS DECLARATION

/**
* CSenWsSecurityHeader represents security header functionality according to 
* oasis web services security (WSS) specifications (2004/01)
* @lib SenUtils.lib
* @since Series60 3.0
*/
class CSenWsSecurityHeader : public CSenBaseFragment
    {
    public:  // Constructors and destructor
        
		/**
		* Basic constructor
		*/
	    IMPORT_C static CSenWsSecurityHeader* NewL();
	    
		/**
		* Basic constructor.
		* @param	aData	Data to be set as header's content.
		*/
		IMPORT_C static CSenWsSecurityHeader* NewL(const TDesC8& aData);

        /**
        * Destructor.
        */
	    IMPORT_C virtual ~CSenWsSecurityHeader();

        // New functions
	
		/**
		* Constructs a username token.
		* @since Series60 3.0
		* @param  aIdentityProvider  Identity provider which is used to get
		* the authorization ID used in username token. Method takes the
		* AuthzID out from aIdentityProvider, and uses it as username for
		* this token.
		* Format of the token is as follows:
		*
		* <wsse:UsernameToken>
		*	<wsse:Username>
		*		username
		*	</wsse:Username>
		* </wsse:UsernameToken>"
		*
		* The above token assumes, that wsse namespace is declared in 
		* top level of the security header.
		* @return a pointer to buffer containing the username token. Does not
		*         return NULL. Ownership is transferred to the caller.
		*/
		IMPORT_C HBufC8* UsernameTokenL(CSenIdentityProvider &aIdentityProvider);

		/**
		* Constructs a username token.
		* @since Series60 3.0
		* @param  aUsername		User name which is used in the username 
		*						token.
		* @param  aToken		Ref-to-pointer which will contain the token
		*						in return. Shouldn't contain any data when
		*						called, or data will be lost.
		* @return KErrNone or some system-wide Symbian error code.
		*/
		IMPORT_C static TInt UsernameTokenL(const TDesC8& aUsername,
											HBufC8*& aToken);
		/**
		* Basic getter for XML namespace of the WS security header.
		* Subclasses should override this to use different namespace 
		* @since Series60 3.0
		* @return the WS security header namespace as string
		*/
		IMPORT_C virtual TPtrC8 XmlNs();
		
		/**
		* Basic getter for XML namespace prefix of the WS security header.
		* Subclasses should override this to use different namespace prefix
		* @since Series60 3.0
		* @return the WS security header namespace prefix as string
		*/
		IMPORT_C virtual TPtrC8 XmlNsPrefix();    
        
    protected:  
	    
	    /**
	    * C++ default constructor
	    */
	    IMPORT_C CSenWsSecurityHeader();
	    
	    /**
	    * Basic BaseConstructL function 
	    */
	    IMPORT_C void BaseConstructL();
        
        // Functions from base classes
		
	    /**
	    * From CSenBaseFragment Basic BaseConstructL function 
		* @since Series60 3.0
	    * @param aData will be used as current token (content) of this security 
		*		 header
	    */
		IMPORT_C void BaseConstructL(const TDesC8& aData);
    };

#endif // SEN_WS_SECURITY_HEADER_H

// End of File
