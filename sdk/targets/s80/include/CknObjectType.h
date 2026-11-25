/*
* ==============================================================================
*  Name        : cknobjecttype.h
*  Part of     : CKON
*  Interface   : Object Dialog API
*  Description : Object type constants
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


#ifndef CKNOBJECTTYPE_H
#define CKNOBJECTTYPE_H

// CONSTANTS

/**
 * The enumeration <code>TCknObjectType</code> specifies object types used by 
 * <code>CCknCopyObjectDialog</code>, <code>CCknDeleteConfirmationNote</code>,
 * <code>CCknPropertiesDialog</code>, and <code>CCknRenameObjectDialog</code>.
 */
enum TCknObjectType
    {
    /** [what] */
    EObjectTypeDefault,
    /** [what] */
    EObjectTypeDocument,
    /** [what] */
    EObjectTypeHTMLDocument,
    /** [what] */
    EObjectTypeXMLDocument,
    /** [what] */
    EObjectTypeMessage,
    /** [what] */
    EObjectTypeImage,
    /** [what] */
    EObjectTypeApplication,
    /** [what] */
    EObjectTypeLink,
    /** [what] */
    EObjectTypePresentation,
    /** [what] */
    EObjectTypeBookmark,
    /** [what] */
    EObjectTypeCertificate,
    /** [what] */
    EObjectTypeVideoClip,
    /** [what] */
    EObjectTypeSoundClip,
    /** [what] */
    EObjectTypeWorkbook,
    /** [what] */
    EObjectTypeLoginScript,
    /** [what] */
    EObjectTypeAudioTrack
    };

/** the maximum length for an object type descriptor */
const TInt KMaxFileTypeLength=64;

#endif      // CKNOBJECTTYPE_H   
            
// End of File
