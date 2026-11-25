/*
 * =========================================================================
 *  Name     : RXMLReader.h
 *  Part of  : SenXmlInterface
 *  Descr.   :
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 *
 *  Copyright © 2002 Nokia Corporation.
 *  This material, including documentation and any related 
 *  computer programs, is protected by copyright controlled by 
 *  Nokia Corporation. All rights are reserved. Copying, 
 *  including reproducing, storing, adapting or translating, any 
 *  or all of this material requires the prior written consent of 
 *  Nokia Corporation. This material also contains confidential 
 *  information which may not be disclosed to others without the 
 *   prior written consent of Nokia Corporation.
 * ==============================================================================
 */


#ifndef __RXMLREADER_H
#define __RXMLREADER_H

//  INCLUDES
#include <F32File.h>

#include <MXMLContentHandler.h>
#include <MWBXMLContentHandler.h>
#include <XMLUtils.h>


// CLASS DECLARATION
class CXMLReader;
/**
*  Interface for XML Parser.
*  
*  @lib XMLInterface.dll
*  @since ?Series60_version
*/
class RXMLReader
{
public: // New functions

	inline RXMLReader();

/** 
* Creates the parser. 
* This function leaves with an apropriate code if the create failed.
* 
*/
	IMPORT_C void CreateL();

/** 
* Destroys the parser. 
* 
*/
	IMPORT_C void Destroy();

/** 
* Destroys the parser. 
* 
*/
	IMPORT_C void Close();
	

/**
* Enables/Dissables a feature.
* @since ?Series60_version
* @param aFeature: The feature to Enable/Dissable.
* @param aStatus: TRUE Enables the feature, FALSE Dissables.
* @return KErrNone if OK, KErrNotSupported if feature not supported.
*/
	IMPORT_C TInt SetFeature(TXMLFeature aFeature, TBool aStatus);

/**
* Check if a feature is Enabled.
* @since ?Series60_version
* @param aFeature: The feature to check.
* @param aStatus: TRUE if aFeature is Enabled. 
* @return KErrNone if OK, KErrNotSupported if feature not supported.
*/
	IMPORT_C TInt GetFeature(TXMLFeature aFeature, TBool& aStatus);

/**
* Allow an application to register a content event handler (for XML).
* @since ?Series60_version
* @param aContentHandler: The handler.
* @return Status, KErrNone if OK.
*/
	IMPORT_C TInt SetContentHandler(MXMLContentHandler* aContentHandler);

/**
* Allow an application to register a content event handler (for WBXML).
* @since ?Series60_version
* @param aContentHandler: The handler.
* @return Status, KErrNone if OK.
*/
	IMPORT_C TInt SetContentHandler(MWBXMLContentHandler* aContentHandler);

/**
* Parse an XML document.
* @since ?Series60_version
* @param aRFs: An open filesession.
* @param aFileToParse: Filename of file to parse.
* @return
*/
	IMPORT_C void ParseL(RFs &aRFs, const TDesC& aFileToParse);

/**
* Parse an XML document.
* @since ?Series60_version
* @param aBuff: Buffer containing document to parse. 
* @return 
*/
	IMPORT_C void ParseL(const TDesC8& aBuff);

/**
* Gets what is encoding of document from the root tag.
* @since ?Series60_version
* @param aBuff: The content.
* @return UID of character set declared in the content or 0 if not present.
*/
	IMPORT_C TUint GetProcessInstructionEncodingL(const TDesC8& aBuff);

/**
* Sets Encoding of document.
* @since ?Series60_version
* @param aEncoding: The encoding.
* @return 
*/

	IMPORT_C void SetEncodingL(TUint aEncoding);




private:
	friend class CXMLReader;

	CXMLReader* iImplementation;
};

inline RXMLReader::RXMLReader()
		: iImplementation(0)
	{
	}

#endif      // __RXMLREADER_H   
            
// End of File
