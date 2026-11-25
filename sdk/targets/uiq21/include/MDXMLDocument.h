// MDXMLDocument.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
/** @file MDXMLDocument.h
 * This file contains the declaration of the CMDXMLDocument class which
 * is the root class for a Mini-DOM tree.
 */

#if !defined(__MDXMLDOCUMENT_H__)
#define __MDXMLDOCUMENT_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class CMDXMLElement;

/**
 *	This object represents a document - it owns the root
 *	element of the DOM tree and is not itself an XML node.
 */
class CMDXMLDocument : public CBase
{
public:
	/**
	 * Factory function
	 * @returns Returns the created CMDXMLDocument
	 * @exception Can Leave due to OOM
	 */
  	IMPORT_C static CMDXMLDocument* NewL();

	/**
	 * Factory function
	 * @returns Returns the created CMDXMLDocument
	 * @exception Can Leave due to OOM
	 */
  	IMPORT_C static CMDXMLDocument* NewLC();

  	IMPORT_C virtual ~CMDXMLDocument();
   
	/**
   	 * @return Returns the root elememnt of the DOM tree.
   	 */
  	inline CMDXMLElement* DocumentElement() {return iRootElement;}

	/**
  	 * @sets the version string.
  	 * @Param replacement tag, this must be complete, starting <!XML and finishing >
  	 * @return ETrue if operation succeeds, EFalse if formal parameter does not 
  	 * begin with <?XML or does not end with an >
  	 * @exception can Leave due to OOM
  	 */
  	IMPORT_C TBool SetVersionTagL(const TDesC& aVersionTag);

  	/**
  	 * @sets the doctype string.
  	 * @Param replacement tag, this must be complete, starting <!DOCTYPE and finishing >
 	 * @return ETrue if operation succeeds, EFalse if formal parameter does not 
  	 * begin with <!DOCTYPE or does not end with an angle bracket
  	 * @exception can Leave due to OOM
  	 */
  	IMPORT_C TBool SetDocTypeTagL(const TDesC& aDocTypeTag);

  	/**
  	 * @gets the version string.
  	 */
  	inline const TDesC& VersionTag() const {return *iVersionTag;}

  	/**
  	 * @gets the doctype string.
  	 */
  	inline const TDesC& DocTypeTag() const  {return *iDocTypeTag;}

protected:  
  	CMDXMLDocument();

protected:
	/**
  	 * @sets the root elememnt of the DOM tree.
  	 */
  	inline void SetDocumentElement(CMDXMLElement* aRootElement) {iRootElement = aRootElement;}


private:
  	void ConstructL();
  
private:
   	CMDXMLElement* iRootElement;	///< Root element node of the DOM tree

protected:
	HBufC* iVersionTag;				///< XML Version text
  	HBufC* iDocTypeTag;				///< Document type text
};


#endif
