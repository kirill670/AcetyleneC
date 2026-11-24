/*
* ==============================================================================
*  Name        : SenXmlServiceDescription.h
*  Part of     : Web Services Description
*  Interface   : 
*  Description : Class implements the most common value object used in WSF, 
*                which is used to  describe some invocable service. 
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

#ifndef SEN_XML_SERVICE_DESCRIPTION_H
#define SEN_XML_SERVICE_DESCRIPTION_H

//  INCLUDES
#include <e32base.h>
#include <e32des8.h>
#include <e32std.h>
#include <MSenServiceDescription.h>
#include <MSenProviderPolicy.h>
#include <SenDomFragment.h>

// CONSTANTS
const TInt KStateParsingCredentials			= 12;
const TInt KStateParsingSingleCredential	= 122;
const TInt KStateParsingProviderPolicy		= 1222;

// FORWARD DECLARATIONS
class CSenCredential;
class CSenProviderPolicy;

// DATA TYPES
typedef RPointerArray<CSenCredential> RCredentialList;

// CLASS DECLARATION

/**
* CSenXmlServiceDescription class implements the most
* common value object used in WSF, which is used to 
* describe some invocable service. 
*
* Class offers basic properties which describe some
* service and methods to manipulate this info. These
* properties are stored in XML fragment format and 
* a class instance can be represented as one XML tree.
*
* The main properties for service description are:
*    - contract (typically some URI)
*    - endpoint (typically some URL)
*    - frameworkID
*
*  @lib SenServDesc.lib
*  @since Series60 3.0
*/
class CSenXmlServiceDescription : public CSenDomFragment,
								  public MSenServiceDescription,
								  public MSenProviderPolicy
    {
    public:  // Constructors and destructor
        
		/**
		* Standard 2 phase constructor
		* @return a pointer to a new CSenXmlServiceDescription instance.
		*/
		IMPORT_C static CSenXmlServiceDescription* NewL();

		/**
		* Standard 2 phase constructor
		* @return a pointer to a new CSenXmlServiceDescription instance,
		*        which is left on cleanup stack.
		*/
		IMPORT_C static CSenXmlServiceDescription* NewLC();

		/**
		* Standard 2 phase constructor
		* @param aNamespaceURI namespace URI for the service description.
		* @return a pointer to a new CSenXmlServiceDescription instance
		*/
		IMPORT_C static CSenXmlServiceDescription* NewL(const TDesC8& aNamespaceURI);

		/**
		* Standard 2 phase constructor
		* @param aNamespaceURI namespace URI for the service description.
		* @return a pointer to a new CSenXmlServiceDescription instance,
		*        which is left on cleanup stack.
		*/
		IMPORT_C static CSenXmlServiceDescription* NewLC(const TDesC8& aNamespaceURI);

		/**
		* Standard 2 phase constructors
		* @param aEndpoint the service endpoint. Note that endpoint cannot 
		*        include characters which are illegal in XML. If endpoint
		*        is an URL which contains illegal characters (like '&'-char),
		*        those need to be encoded into XML entity form (like &amp;).
		*        EncodeHttpCharactersLC() method from XmlUtils can be used
		*        for encoding of basic XML entities.
		* @param aContract identifies the service type. 
		* @return a pointer to a new CSenXmlServiceDescription instance
		*/
		IMPORT_C static CSenXmlServiceDescription* NewL(const TDesC8& aEndPoint,
													    const TDesC8& aContract);

		/**
		* Standard 2 phase constructors
		* @param aEndpoint the service endpoint. Note that endpoint cannot 
		*        include characters which are illegal in XML. If endpoint
		*        is an URL which contains illegal characters (like '&'-char),
		*        those need to be encoded into XML entity form (like &amp;).
		*        EncodeHttpCharactersLC() method from XmlUtils can be used
		*        for encoding of basic XML entities.
		* @param aContract identifies the service type. 
		* @return a pointer to a new CSenXmlServiceDescription instance,
		*        which is left on cleanup stack.
		*/
		IMPORT_C static CSenXmlServiceDescription* NewLC(const TDesC8& aEndPoint,
														 const TDesC8& aContract);
        
        /**
        * Destructor.
        */
		IMPORT_C virtual ~CSenXmlServiceDescription();

        // New functions

		/**
		* Setter for the framework ID.
		* The developer may use a FrameworkID to search for a session of	
		* (i.e. connection to) a certain service invocation framework.
		* @since Series60 3.0
		* @param aFrameworkId
		* If set to KNullDesC8, then any matching framework may be used.
		* The default frameworkID in WSF is "ID-WSF" 
		* (KDefaultIdWsfFrameworkID).
		* Note that Basic Web Services MUST use "WS-I" 
		* (KDefaultBasicWebServicesFrameworkID).
		*/
		IMPORT_C void SetFrameworkIdL(const TDesC8& aFrameworkID);

		/**
		* Method returns the localname for this service description.
		* This is the localname of the element, when this class is
		* represented as an XML element.
		* @since Series60 3.0
		* @return descriptor to XML localname of this service description
		*/
		IMPORT_C virtual const TDesC8& NewElementName();
		
		/**
		* Returns list of credentials. Ownership is not transferred, any
		* modifications to the contents of the list modify the real objects.
		* @since Series60 3.0
		* @return the list of credentials (CSenCredential objects).
		*/
		IMPORT_C  RCredentialList& Credentials();        

        // Functions from base classes
    
		// From MSenProviderPolicy
		IMPORT_C virtual void SetIapIdL(TUint32 aIapId);
		IMPORT_C virtual TInt IapId(TUint32& aCurrentIapId);
		IMPORT_C virtual void SetIdentityProviderIdsL(
										CSenIdentityProviderIdArray8& aList);

		IMPORT_C virtual TInt AddIdentityProviderIdL(TDesC8& aProviderId);
		IMPORT_C virtual TInt RebuildFrom(MSenProviderPolicy& aTemplate);
		IMPORT_C virtual const CSenIdentityProviderIdArray8&
													IdentityProviderIds8L();
		
		IMPORT_C virtual TBool Accepts(MSenProviderPolicy& aPolicyPattern);
		
		// From MSenServiceDescription 
		IMPORT_C TDescriptionClassType DescriptionClassType();
		IMPORT_C TBool Matches(MSenServiceDescription& aPattern);
		IMPORT_C TPtrC8 Contract();
		IMPORT_C virtual TInt HasFacetL(const TDesC8& aURI, TBool& aHasFacet);
		IMPORT_C virtual TInt FacetValue(TDesC8& aURI, HBufC8*& aValueTo);
		IMPORT_C virtual TInt AddFacetL(const CSenFacet& aFacet);
		IMPORT_C virtual TInt SetFacetL(const CSenFacet& aFacet);
		IMPORT_C virtual TInt RemoveFacet(const TDesC8& aURI);
		IMPORT_C virtual TInt FacetsL(RFacetArray& aFacetArray);
		IMPORT_C virtual TInt ScoreMatchL(MSenServiceDescription& aPattern);
		IMPORT_C TPtrC8 Endpoint();
		IMPORT_C TPtrC8 FrameworkId();
		IMPORT_C TPtrC8 FrameworkVersion();
		IMPORT_C void SetContractL(const TDesC8& aContract);
		IMPORT_C void SetEndPointL(const TDesC8& aEndPoint);
		
		// From CSenBaseFragment 
		
		/** 
		* Gets the service description as XML fragment in UTF-8 format.
		* @since Series60 3.0
		* @return the service description as XML, which ownership is
		*         transferred to the caller.
		*/
		IMPORT_C virtual HBufC8* AsXmlL();

		/**
		* Gets the service description as XML, in Unicode (UCS-2)
		* @since Series60 3.0
		* @return the service description as XML, which ownership is
		*         transferred to the caller.
		*/
		IMPORT_C virtual HBufC* AsXmlUnicodeL();

		/**
		* Writes this service description as XML, in UTF-8 form to a stream
		* @since Series60 3.0
		* @param aWriteStream	to write into.
		*/
		IMPORT_C virtual void WriteAsXMLToL(RWriteStream& aWriteStream);


		// From CSenDomFragment 
		
		/**
		* Method looks for FrameworkID attribute from the given XML attribute
		* array and if one is found, sets its value for this instance. In
		* addition, all the namespace attributes are copied. All other
		* attributes are discarded.
		* @since Series60 3.0
		* @param aAttributes	the attribute list.
		*/
		IMPORT_C void SetAttributesL(const RAttributeArray& aAttributes);

		/**
		* Resumes the parsing. Called by the delegate fragment 
		* in order to notify owner, which needs to regain 
		* (take over) parsing. For example, when a policy fragment
		* is parsed, the service description fragment should
		* resume parsing the rest of its own XML document 
		* representation.
		* @since Series60 3.0
		* @param aNsUri		The namespace URI of the current element
		* @param aLocalName	The local name of the current element
		* @param aQName		The qualified name of the current element
		*/
		IMPORT_C void ResumeParsingFromL(const TDesC8& aNsUri,
										 const TDesC8& aLocalName,
										 const TDesC8& aQName);
		        
    protected:  // New functions
		
		/**
		* C++ default constructor.
		* @param aType enumeration defining the type of this class.
		*/
		IMPORT_C CSenXmlServiceDescription(TDescriptionClassType aType);
		
		/**
		 * Basic ConstructL function.
		 */
		IMPORT_C void ConstructL();

		/**
		* Basic ConstructL function.
		* @since Series60 3.0
		* @param aNamespaceURI for this service description, which is
		*        also an XML element.
		*/
		IMPORT_C void ConstructL(const TDesC8& aNamespaceURI);

        /**
		* Basic ConstructL function.
		* @since Series60 3.0
		* @param aEndpoint the service endpoint. Note that endpoint cannot 
		*        include characters which are illegal in XML. If endpoint
		*        is an URL which contains illegal characters (like '&'-char),
		*        those need to be encoded into XML entity form (like &amp;).
		*        EncodeHttpCharactersLC() method from XmlUtils can be used
		*        for encoding of basic XML entities.
		* @param aContract identifies the service type, typically some URN.
		*/
		IMPORT_C void ConstructL(const TDesC8& aEndPoint, const TDesC8& aContract);

		// Functions from base classes
		
		// From CSenDomFragment 
		
		/**
		* Callback function which implements the XML content handler interface.
		* @since Series60 3.0
		* @param aNsURI		The namespace URI of the new element
		* @param aLocalName	The local name of the new element
		* @param aQName		The qualified name of the new element
		* @param aAttributes	The attributes of the new element
		*/
		IMPORT_C virtual void StartElementL(const TDesC8& aNsUri,
										    const TDesC8& aLocalName,
											const TDesC8& aQName,
											const RAttributeArray& aAttributes);

		// From CSenBaseFragment 
		/**
		* Callback function which implement the XML content handler interface.
		* @since Series60 3.0
		* @param aNsUri		The namespace URI of the new element
		* @param aLocalName	The local name of the new element
		* @param aQName		The qualified name of the new element
		*/
		IMPORT_C virtual void EndElementL(const TDesC8& aNsUri,
										  const TDesC8& aLocalName,
										  const TDesC8& aQName);

	private:
		TInt FacetValueL(TDesC8& aURI, HBufC8*& aValueTo);
		TInt RemoveFacetL(const TDesC8& aURI);

    protected: // Data
		// the type of this class instance
		const TDescriptionClassType iType;

    private: // Data
    	HBufC8*	iFrameworkId;
		CSenCredential*	iCredential;
		RCredentialList	iCredentialList;

		// Timestamp indicating validity of credentials. Using SenDateUtils 
		// FromXmlDateTimeL and ToXmlDateTimeUtf8L is recommended for conversions.
		TTime iNotOnOrAfter;
		CSenProviderPolicy*	iProviderPolicy;
   	};

// SEN_XML_SERVICE_DESCRIPTION_H
#endif

// End of File


