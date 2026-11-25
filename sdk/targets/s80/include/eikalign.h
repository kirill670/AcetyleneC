/*
* ==============================================================================
*  Name        : eikalign.h
*  Part of     : ckon
*  Interface   : Control API
*  Description : Aligned control
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef EIKALIGN_H
#define EIKALIGN_H

// INCLUDES
#include <coecntrl.h>
#include <gulalign.h>
#include <gulutil.h>


/**
 *
 * This class extends the <code>CCoeControl</code> class in order to
 * support extra functionality such as control alignment and margins.
 *
 * It is only intended as a simple building block for controls.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikAlignedControl : public CCoeControl
	{
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikAlignedControl();

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikAlignedControl();

		/**
		* Sets all margins.
		* @param aValue The number of pixels to which all margins will be set
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetAllMarginsTo(TInt aValue);

		/**
		* Sets control alignment.
		* @param aAlign The alignment
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetAlignment(TGulAlignmentValue aAlign);
	protected: //from CCoeControl

		/**
		* See CCoeControl
		*/
		IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
	public:
		TMargins8 iMargin;
		TGulAlignment iAlignment;
	};



#endif	// EIKALIGN_H

// End of File
