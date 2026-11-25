//
// SMILEntityConverter.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
/** @file SMILEntityConverter.h
 * This class represents a DTD-specific entity converter for an XML parser or composer.
 */

#ifndef __MDXMLSMILENTITYCONVERTER_H
#define __MDXMLSMILENTITYCONVERTER_H

#include <e32std.h>
#include <eikenv.h>
#include "MDXMLEntityConverter.h"

class CMDXMLSMILEntityConverter: public CMDXMLEntityConverter
	{
public:
	/**
	 * Constructor
	 */
	CMDXMLSMILEntityConverter();
	virtual ~CMDXMLSMILEntityConverter();

	
public:
	/**
	 * Outputs a block of text to a composer with offending characters replaced by
	 * entity references.
	 * @param aComposer the composer to be used for output
	 * @param aTextToConvert The text to be converted.
	 * @return Returns KErrNone if succcessful or a file write error
	 * @exception can Leave due to OOM
	 */
	virtual TInt OutputComposedTextL( CMDXMLComposer* aComposer, const TDesC& aTextToConvert );

protected:
	/**
	 * DTD Specific entity to text converter
	 * Takes a block of text and converts any entity references found to the 
	 * appropriate text.  We hope that this can happen in-situ.
	 * @param aTextToConvert Text to be converted - replacement text goes
	 * out in the same
	 */
	virtual void DTDEntityToText(TDes& aTextToConvert);
	};

#endif
