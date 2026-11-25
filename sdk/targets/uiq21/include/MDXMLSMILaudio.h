// MDXMLSMILaudio.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILaudio.h
 * This file contains the declaration of the CMDXMLSMILaudio class.
 * This class represents an audio element and is specific to the SMIl 2.0 Basic DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILAUDIO_H__
#define __MDXMLSMILAUDIO_H__

#include <e32base.h>
#include "MDXMLSMILMediaObject.h"
#include "MDXMLSMILTimedMediaObject.h"


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILaudio : public CMDXMLSMILTimedMediaObject
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILaudio
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILaudio* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILaudio
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILaudio* NewL( CMDXMLDocument* aOwnerDocument );

	/**
	 * This factory function creates a new audio element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILaudio* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);

	/**
	 * @param aNode pointer to cast from
	 * @return Returns an audio pointer if the node is of type audio, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILaudio* CastToSMILaudio( CMDXMLNode* aNode );

	/**
	 * @return Returns a pointer to the next audio sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILaudio* NextaudioSibling();

	/**
	 * @return Returns a pointer to the previous audio sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILaudio* PreviousaudioSibling();

	IMPORT_C virtual ~CMDXMLSMILaudio();

private:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILaudio( CMDXMLDocument* aOwnerDocument );

	};

#endif

// End of File