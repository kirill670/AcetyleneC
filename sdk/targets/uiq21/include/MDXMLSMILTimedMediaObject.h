// MDXMLSMILTimedMediaObject.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILTimedMediaObject.h
 * This file is now obsolete as it refers to a now-removed abstract class.
 * Unfortunately, some badly behaved modules have explicit references to the file
 * which are beyond my authority to remove.  Therefore, it is kept as a null file :-(
 * Modules which use the SMIL translator should include MDXMLSMIL.h which includes the 
 * relevant header files in the right order.
 */

#ifndef __MDXMLSMILTIMEDMEDIAOBJECT_H__
#define __MDXMLSMILTIMEDMEDIAOBJECT_H__

// Included purely for SC
class CMDXMLSMILTimedMediaObject : public CMDXMLSMILMediaObject 
	{
public:
	IMPORT_C virtual ~CMDXMLSMILTimedMediaObject();

protected:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILTimedMediaObject( CMDXMLDocument* aOwnerDocument );

	};

#endif

// End of File