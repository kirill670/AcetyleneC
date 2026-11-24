/*
* ==============================================================================
*  Name        : MSenContentHandlerClient.h
*  Part of     : Web Services Xml
*  Interface   : 
*  Description : Central place for debug-type macros
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

#ifndef __MSENCONTENTHANDLERCLIENT_H
#define __MSENCONTENTHANDLERCLIENT_H

//  INCLUDES
#include <xml\Attribute.h>

using namespace Xml;

// CLASS DECLARATION

/**
* Interface for SAX Parser Callback events.
* If an application (client) needs to be informed of basic parsing events, 
* it implements this interface and registers an instance with the SAX parser 
* using the SetContentHandler() method.
* The parser uses the instance to report basic document-related events like 
* the start and end of elements.*  
* 
* 
*/
class MSenContentHandlerClient
	{
    public: // New functions

		/**
		* Receive notification of the beginning of a document.
		* @return KErrNone or some of the system-wide Symbian error codes.
		*/		
		virtual TInt StartDocument() = 0;

		/**
		* Receive notification of the end of a document.
		* @return KErrNone or some of the system-wide Symbian error codes.
		*/
		virtual TInt EndDocument() = 0;

		/**
		* Receive notification of the beginning of an element.
		* @param aURI:			The Namespace URI, or the empty string if the element 
		*						has no Namespace URI or if Namespace processing is not 
		*						being performed.
		* @param aLocalName:	The local name (without prefix)
		* @param aName:			The qualified name
		* @param apAttrs:		The attributes attached to the element. 
		*						If there are no attributes, it shall be an empty array.
		*						Namespaces declared in the current element will be 
		*						located in the array also.
		*        
		* @return				KErrNotSupported	If the class implementing this 
		*											interface doesn't override this.
		*						KErrNone or other system-wide Symbian error codes.
		*/
		inline virtual TInt StartElement(	const TDesC8& /*aURI*/, 
											const TDesC8& /*aLocalName*/, 
											const TDesC8& /*aName*/, 
											const RAttributeArray& /* apAttrs */)
		{
			return KErrNotSupported;
		}

		/**
		* Receive notification of the end of an element.
		* @param aURI:			The Namespace URI, or the empty string if the element 
		*						has no Namespace URI or if Namespace processing is not 
		*						being performed.
		* @param aLocalName:	The local name (without prefix)
		* @param aName:			The qualified name
		*
		* @return				KErrNotSupported	If the class implementing this 
		*											interface doesn't override this.
		*						KErrNone or other system-wide Symbian error codes.
		*/
		inline virtual TInt EndElement(	const TDesC8& /*aURI*/, 
										const TDesC8& /*aLocalName*/, 
										const TDesC8& /*aName*/)
		{
			return KErrNotSupported;
		}

		/**
		* Receive notification of character data inside an element.
		* @param aBuff: The characters.
		* @param aStart: The start position in the character buffer.
		* @param aLength: The number of characters to use from the character buffer.
		* @return				KErrNotSupported	If the class implementing this 
		*											interface doesn't override this.
		*						KErrNone or other system-wide Symbian error codes.
		*/
		inline virtual TInt Characters(const TDesC8& /*aBuf*/, 
		   							   const TInt /*aStart*/, 
									   const TInt /*aLength*/)
		{
			return KErrNotSupported;
		}

		/**
		* Receive notification of a processing instruction
		* @param aTarget:		The processing instruction target.
		* @param aData:			The processing instruction data, 
		*						or null if none is supplied.
		* @return				KErrNotSupported	If the class implementing this 
		*											interface doesn't override this.
		*						KErrNone or other system-wide Symbian error codes.
		*/
		inline virtual TInt ProcessingInstructions(const TDesC8& /*aTarget*/, 
												   const TDesC8& /*aData*/)
		{
			return KErrNotSupported;
		}

		/**
		* Receive notification of a skipped entity.
		* @param aName: The name of the skipped entity.
		* @return				KErrNotSupported	If the class implementing this 
		*											interface doesn't override this.
		*						KErrNone or other system-wide Symbian error codes.
		*/
		inline virtual TInt SkippedEntity(const TDesC8& /*aName*/)
		{
			return KErrNotSupported;
		} 

		/**
		* Receive notification of error situation during parsing.
		* @param aErrorCode: Error status code.
		* @param aSeverity: Error Severity.
		* @return				KErrNotSupported	If the class implementing this 
		*											interface doesn't override this.
		*						KErrNone or other system-wide Symbian error codes.
		*/
		inline virtual TInt Error(TInt /*aErrorCode*/)
		{
			return KErrNotSupported;
		}

		/**
		* Receive notification of prefix mapping start.
		* @param aPrefix: The prefix
		* @param aUri: The URI mapped to the prefix.
		* @return				KErrNotSupported	If the class implementing this 
		*											interface doesn't override this.
		*						KErrNone or other system-wide Symbian error codes.
		*/
		inline virtual TInt StartPrefixMappingL(  const TDesC8& /* aPrefix */, 
												  const TDesC8& /* aUri */)
		{
			return KErrNotSupported;
		}
			
		/**
		* Receive notification of prefix mapping end.
		* @param aPrefix: The prefix
		* @return				KErrNotSupported	If the class implementing this 
		*											interface doesn't override this.
		*						KErrNone or other system-wide Symbian error codes.
		*/
		inline virtual TInt EndPrefixMappingL(const TDesC8& /* aPrefix */)
		{
			return KErrNotSupported;
		}
			
		/**
		* Receive notification of ignorable whitespace in element content.
		* @param aBytes: The whitespace characters.
		* @return				KErrNotSupported	If the class implementing this 
		*											interface doesn't override this.
		*						KErrNone or other system-wide Symbian error codes.
		*/
		inline virtual TInt OnIgnorableWhiteSpaceL(const TDesC8& /* aBytes */) 
		{
			return KErrNotSupported;
		}

		/**
		*	This method obtains the interface matching the specified UID.
		* @param	aUid	the UID identifying the required interface.
		* @return	NULL if no interface matching the UID is found or method is not
		*			overridden in the implementing class.
		*			Otherwise, the this pointer cast to that interface.
		*/
		inline virtual TAny* GetExtendedInterface(const TInt32 /* aUid */)
		{
		  return NULL;
		}
	};

// __MSENCONTENTHANDLERCLIENT_H   
#endif
            
// End of File
