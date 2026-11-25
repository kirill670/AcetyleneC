/*
* ==============================================================================
*  Name        : cknfepspecificextensions.h
*  Part of     : CKON
*  Interface   : FEP API
*  Description : Defines a clipboard support mixin class.
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

#ifndef CKNFEPSPECIFICEXTENSIONS_H
#define CKNFEPSPECIFICEXTENSIONS_H

#include <coeinput.h>

// CONSTANTS

/** The UID defining the Specific extension supporting Clipboard operations */
const TUint KCknFepSpecificExtensions=0x101F879F;

/**
 * The <code>TCoeInputCapabilities::MCoeFepSpecificExtensions</code> 
 * declaration exists to prevent a base class undefined error
 * in <code>MCknFepSpecificExtensions</code>.
 *
 * @lib cknctl.lib
 * @since Series 90 1.0
 */
class TCoeInputCapabilities::MCoeFepSpecificExtensions
    {
    public:
    };

/**
 * The <code>MCknFepSpecificExtensions</code> class is a mixin class, which
 * allows controls to specify their support for clipboard operations. It is 
 * meant to be used as a <code>MCoeFepSpecificExtensions</code> and returned 
 * in the <code>InputCapabilities()</code> method of the control that needs to 
 * specify its clipboard support.
 *
 * @lib cknctl.lib
 * @since Series 90 1.0
 */
class MCknFepSpecificExtensions : public TCoeInputCapabilities::MCoeFepSpecificExtensions
    {
    public:
	/** 
	 * The <code>TClipboardFlags</code> enumeration defines values that define the 
	 * clipboard functionality.
	 */
    enum TClipboardFlags
        {
        /** There is No Clipboard support */
        ENone=0x0,
        /** Clipboard opperation Copy is supported. */
        ESupportsCopy=0x0001,
        /** Clipboard opperation Paste is supported. */
        ESupportsPaste=0x0002,
        /** The contents of the control are read only. */
        EReadOnly=0x0004,
        };

        /**
        * Called by a FEP to determine what Clipboard operations are supported
		* by a control.
        * 
        * @return a combination of <code>TClipboardFlags</code>, which 
        *         specified which clipboard operations are currently enabled. 
        *         The TClipboardFlags enum has these values:
        *         <code>ENone</code> = <code>0x0</code>
        *         <code>ESupportsCopy</code> = <code>0x0001</code>
        *         <code>ESupportsPaste</code> = <code>0x0002</code>
        *         <code>EReadOnly</code> = <code>0x0004</code>
        * @remarks
        * @see
        */
        virtual TUint ClipboardOperationSupport() const=0;

        /**
        * This method is reserved for later use.
        * 
        * @remarks
        * @see
        */
        IMPORT_C virtual void CknFepSpecificExtensions_Reserved_1();

        /**
        * This method is reserved for later use.
        * 
        * @remarks
        * @see
        */
        IMPORT_C virtual void CknFepSpecificExtensions_Reserved_2();

    };

#endif  // CKNFEPSPECIFICEXTENSIONS_H

// End of File
