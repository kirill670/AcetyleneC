// MDXMLSMILDocument.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
/** @file MDXMLSMILDocument.h
 * This file contains the declaration of the CMDXMLSMILDocument class which
 * is the DTD-specific root class for a Mini-DOM tree.
 */

#if !defined(__MDXMLSMILDOCUMENT_H__)
#define __MDXMLSMILDOCUMENT_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class CMDXMLElement;

/**
 *	This object represents a document - it owns the root
 *	element of the DOM tree and is not itself an XML node.
 */
class CMDXMLSMILDocument : public CMDXMLDocument
{
public:
	/**
	 * Factory function
	 * @returns Returns the created CMDXMLDocument
	 * @exception Can Leave due to OOM
	 */
  	IMPORT_C static CMDXMLSMILDocument* NewL();

	/**
	 * Factory function
	 * @returns Returns the created CMDXMLDocument
	 * @exception Can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILDocument* NewLC();

	IMPORT_C virtual ~CMDXMLSMILDocument();

private:
	/**
	 * Constructor
	 */
  	CMDXMLSMILDocument();

	/**
	 * Two Phase Constructor.
	 */
  	void ConstructL();
};


#endif
