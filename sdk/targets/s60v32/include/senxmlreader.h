/*
* ==============================================================================
*  Name        : SenXmlReader.h
*  Part of     : Web Services Xml
*  Interface   : 
*  Description : Class extends Symbian XML framework parser functionality
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

#ifndef __SENXMLREADER_H
#define __SENXMLREADER_H

//  INCLUDES
#include <xml\Parser.h>
#include <xml\ParserFeature.h> // for TParserFeature enumeration
#include <xml\ContentHandler.h>
#include <badesca.h>

using namespace Xml;

// CONSTANTS
const TInt KSenDefaultParserFeature = (TInt)EReportNamespaceMapping;

// FORWARD DECLARATIONS
class MSenContentHandlerClient;
class RFs;

// CLASS DECLARATION

/**
* Class extends Symbian XML framework parser functionality
* Callers of this class must register some handler which will
* then receive XML callback events from underlying Symbian
* XML framework.
* 
* 
*/
class CSenXmlReader : public CBase, public MContentHandler
	{
	public:  // Constructors and destructor
	
	    /**
	    * Standard two-phase constructor.
	    * 
	    * @return pointer to a new CSenXmlReader instance.
	    */
		IMPORT_C static CSenXmlReader* NewL();

	    /**
	    * Standard two-phase constructor.
	    * 
	    * @return pointer to a new CSenXmlReader instance
	    * which is left on cleanup stack.
	    */
		IMPORT_C static CSenXmlReader* NewLC();

		/**
		* A constructor with parser feature enabling.
		* 
		* @param aParserFeature is typically some enumeration introduced 
		*			in Xml::TParserFeature or some other feature introduced in 
		*			some XML parser implementation.
		*	Leave codes:
		*		KErrArgument	if aParserFeature value is negative.
		*/ 
	 	IMPORT_C static CSenXmlReader* NewL(TInt aParserFeature);

		/**
		* A constructor with parser feature enabling.
 		* 
		* @param aParserFeature is typically some enumeration introduced 
		*			in Xml::TParserFeature or some other feature introduced in 
		*			some XML parser implementation.
		*	Leave codes:
		*		KErrArgument	if aParserFeature value is negative.
		*/ 
		IMPORT_C static CSenXmlReader* NewLC(TInt aParserFeature);
        
		/**
		* Destructor.
		*/
		IMPORT_C virtual ~CSenXmlReader();

        // New functions

		/**
		* Method to allow client to register a content event handler (for XML) for
		* the current reader.
		* 
		* @param aContentHandler The new event handler.
		*/
		IMPORT_C virtual void SetContentHandler(
					MSenContentHandlerClient& aContentHandler);

		/**
		* Method for checking which feature has been enabled in the parser.
		* 
		* @return the corresponding integer id of the feature
		*/
		IMPORT_C virtual TInt EnabledParserFeature();

		/**
		* DEPRECATED. Use EnabledParserFeature() instead.
		*/
		IMPORT_C virtual TInt ParserFeature();

		/**
		* Method for enabling a parser feature.
		* 
		* @param aParserFeature is typically some enumeration introduced 
		*			in Xml::TParserFeature or some other feature introduced in 
		*			some XML parser implementation.
		* @return KErrNone or some system-wide error code, if an error has occured.
		*/
		TInt SetParserFeature(TInt aParserFeature);		

		/**
		* Parse an XML buffer.
		* 
		* @param aBuff Buffer containing document to parse.
		*/
		IMPORT_C void ParseL(const TDesC8& aBuff);

		/**
		* Parse an XML document.
		* 
		* @param aRFs An open filesession.
		* @param aFileToParse Filename of file to parse.
		*/
		IMPORT_C void ParseL(RFs &aRFs, const TDesC& aFileToParse);
		
		// Functions from base classes 
	
		// Callback functions implementing Symbian MContentHandler interface

		/**
		* 
		*	Leave codes:
		*		KErrSenXmlContentHandlerNotSet	if XML content handler
		*		for this XML reader has not been set. This leave can
		*       be avoided calling SetContentHandlerL() method prior
		*       parsing some XML document.
		*/
		virtual void OnStartDocumentL(const RDocumentParameters& aDocParam, 
									  TInt aErrorCode);

		/**
		* 
		*	Leave codes:
		*		KErrSenXmlContentHandlerNotSet	if XML content handler
		*		for this XML reader has not been set. This leave can
		*       be avoided calling SetContentHandlerL() method prior
		*       parsing some XML document.
		*/
		virtual void OnEndDocumentL(TInt aErrorCode);

		/**
		* 
		*	Leave codes:
		*		KErrSenXmlContentHandlerNotSet	if XML content handler
		*		for this XML reader has not been set. This leave can
		*       be avoided calling SetContentHandlerL() method prior
		*       parsing some XML document.
		*/
		virtual void OnStartElementL(const RTagInfo& aElement, 
									 const RAttributeArray& aAttributes, 
									 TInt aErrorCode);

		/**
		* 
		*	Leave codes:
		*		KErrSenXmlContentHandlerNotSet	if XML content handler
		*		for this XML reader has not been set. This leave can
		*       be avoided calling SetContentHandlerL() method prior
		*       parsing some XML document.
		*/
		virtual void OnEndElementL(const RTagInfo& aElement, TInt aErrorCode);

		/**
		* 
		* @param aBytes is the actual XML data, content in UTF-8 form
		* @param aErrorCode KErrNone, or some system-wide error code
		*        if an error has occured.
		*/
		virtual void OnContentL(const TDesC8& aBytes, TInt aErrorCode);

		/**
		* 
		*	Leave codes:
		*		KErrSenXmlContentHandlerNotSet	if XML content handler
		*		for this XML reader has not been set. This leave can
		*       be avoided calling SetContentHandlerL() method prior
		*       parsing some XML document.
		*/
		virtual void OnStartPrefixMappingL(const RString& aPrefix, 
										   const RString& aUri, 
										   TInt aErrorCode);

		/**
		* 
		*	Leave codes:
		*		KErrSenXmlContentHandlerNotSet	if XML content handler
		*		for this XML reader has not been set. This leave can
		*       be avoided calling SetContentHandlerL() method prior
		*       parsing some XML document.
		*/
		virtual void OnEndPrefixMappingL(const RString& aPrefix, TInt aErrorCode);

		/**
		* 
		*	Leave codes:
		*		KErrSenXmlContentHandlerNotSet	if XML content handler
		*		for this XML reader has not been set. This leave can
		*       be avoided calling SetContentHandlerL() method prior
		*       parsing some XML document.
		*/
		virtual void OnIgnorableWhiteSpaceL(const TDesC8& aBytes, TInt aErrorCode);

		/**
		* 
		*	Leave codes:
		*		KErrSenXmlContentHandlerNotSet	if XML content handler
		*		for this XML reader has not been set. This leave can
		*       be avoided calling SetContentHandlerL() method prior
		*       parsing some XML document.
		*/
		virtual void OnSkippedEntityL(const RString& aName, TInt aErrorCode);

		/**
		* 
		*	Leave codes:
		*		KErrSenXmlContentHandlerNotSet	if XML content handler
		*		for this XML reader has not been set. This leave can
		*       be avoided calling SetContentHandlerL() method prior
		*       parsing some XML document.
		*/
		virtual void OnProcessingInstructionL(const TDesC8& aTarget, 
											  const TDesC8& aData, 
											  TInt aErrorCode);

		/**
		* 
		*	Leave codes:
		*		KErrSenXmlContentHandlerNotSet	if XML content handler
		*		for this XML reader has not been set. This leave can
		*       be avoided calling SetContentHandlerL() method prior
		*       parsing some XML document.
		*/
		virtual void OnError(TInt aErrorCode);

       	/**
		* This method obtains the interface matching the specified UID.
		* 
		* @param	aUid	the UID identifying the required interface.
		* @return	NULL	if no interface matching the UID is found.
		*					Otherwise, the this pointer cast to that interface.
		*	Leave codes:
		*		KErrSenXmlContentHandlerNotSet	if XML content handler
		*		for this XML reader has not been set. This leave can
		*       be avoided calling SetContentHandlerL() method prior
		*       parsing some XML document.
		*/
		virtual TAny* GetExtendedInterface(const TInt32 aUid);			

	protected:
		
		/**
		* C++ constructor.
		*/
		IMPORT_C CSenXmlReader(TInt aParserFeature);
		
		/**
		* Symbian 2nd phase constructor.
		*/
		void ConstructL();
		
		// New functions
		
		/**
		* This method re-initializes encapsulated CParser class instance.
		* 
		*/
		void RecreateParserL();
			
	private: // Data
       	// Owned instance of Symbian XML framework (default) XML parser
		CParser* iParser;
		// Not owned pointer to XML content handler.
		MSenContentHandlerClient* iContentHandler;
		// Owned pointer to XML namespace prefix strings
		CDesC8Array* ipNsPrefixes;
		// Owned pointer to XML namespace URI strings
		CDesC8Array* ipNsUris;
		// Owned string pool for XML attribute handling.
		RStringPool iStringPool;
       	// Integer indicating currently enabled features
		TInt iEnabledFeature;
	};

// __SENXMLREADER_H
#endif
            
// End of File

