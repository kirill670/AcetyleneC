// FRMLAYDT.H
//
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//

#ifndef __FRMLAYDT_H__
#define __FRMLAYDT_H__

#include <e32std.h>
#include <txtlaydc.h>
#include "frmvis.h"

/**
 * Some enums. The rest of this class has been deleted.
 *
 * @since 5.0
 * @lib ""
 */

class CLayoutData
	{
public:
	enum
		{
		EFLargeNumber = KMaxTInt / 3,	// must be less than KMaxTInt/2 to avoid overflow problems
		EFMaximumTBoxLength = 256,
		EFFontHeightIncreaseFactor = 7,	// by default, increase the font height by this percentage
		EFMinimumLineDescent = 3,		// by default, this is the minimum line descent
		EFBaseLinePosition = 82			// position down ViewRect for BaseLine
		};
	enum
		{
		EFHeightForFormattingAllText=EFLargeNumber,
		EFBodyWidthForNoWrapping=EFLargeNumber
		};
	
	/**
	 *
	 * Flags used when converting between layout coordinates and document
	 * position (see <code>CTextLayout::XyPosToDocPosL()</code> and
	 * <code>DocPosToXyPosL()</code>).
	 * @since 
	 */
	enum		
		{
		/**
		 * Count individual characters and don't treat the end of the line specially.
		 * @deprecated 6.2
		 */
		EFIndividualChars = 0,
		/**
		 * Only consider the beginnings and ends of whole lines. Only useful in
		 * XyToDocPos functions.
		 */
		EFWholeLinesOnly = 1,
		/**
		 * Only consider the beginnings and ends of whole TBoxs so as not to
		 * access the document. Only useful in XyToDocPos functions.
		 */
		EFWholeTBoxesOnly=EFWholeLinesOnly,
		/**
		 * Disambiguate the end position of a line from the start position of
		 * the next line. If both positions are the same, a position at the end
		 * of the line will be invalid, and the position before will be
		 * returned instead.
		 */
		EFDisambiguateEndOfLine = 2,
		};	
	
	/**
	 *
	 * Format modes.
	 * @since 
	 */

	enum TFormatMode
		{
		/** Dimensions stored in pixels with no mapping between format and image device. */
		EFScreenMode, 
		/** Dimensions stored in twips with no mapping. */
		EFPrintMode,
		/** Dimensions stored in twips with partial mapping. */
		EFPrintPreviewMode, 
		/** Dimensions stored in twips with full mapping. */
		EFWysiwygMode
		};
private:
	// not constructable
	CLayoutData(CLayoutData&);
	};

#endif
