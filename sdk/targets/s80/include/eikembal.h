/*
* ==============================================================================
*  Name        : eikembal.h
*  Part of     : UIKON
*  Interface   : Embeddable App API
*  Description : Embeddable application list class.
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

#ifndef EIKEMBAL_H
#define EIKEMBAL_H

// INCLUDES
#include <e32base.h>
#include <f32file.h>
#include <bamdesca.h>
#include <apadef.h>
#include <apaid.h>

// FORWARD DECLARATIONS
class CEikDocument;
class CApaProcess;
class RApaLsSession;


/**
 *  The <code>CEikEmbeddableAppList</code> class creates a list of embeddable 
 *  applications. When constructed, this class automatically gets a list of 
 *  all of the embeddable applications that can currently be accessed. 
 *  <code>CreateEmbeddedDocumentL()</code> can be used to create a document 
 *  for a particular embeddable application. 
 *
 *  @lib eikcore.lib
 *  @since Series90 1.0
 */
class CEikEmbeddableAppList : public CArrayFixFlat<TApaAppInfo>, public MDesCArray
    {
    public:

        /**
        * The default object constructor.
        */
        IMPORT_C CEikEmbeddableAppList();

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikEmbeddableAppList();

        /**
        * Completes construction of a <code>CEikEmbeddableAppList</code> 
        * object. 
        *
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL();

        /**
        * Completes construction of a <code>CEikEmbeddableAppList</code> 
        * object. This method uses a filter to define a subset of 
        * applications to be present in the list. 
        * 
        *
        * @param aFilter A filter used to define the application's capabilities
        * @remarks
        * @see <code>TApaEmbeddabilityFilter</code> in apaid.h
        */
        IMPORT_C void ConstructL(const TApaEmbeddabilityFilter& aFilter);

        /**
        * Creates and returns a new embedded document.
        *
        * @param aIndex The index of the embedded application to create a 
        *               document for 
        * @param aProcess The process in which to create the document
        * @return the created document
        * @remarks
        * @see <code>CApaProcess</code> in apaarc.h
        */
        IMPORT_C CEikDocument* CreateEmbeddedDocumentL(TInt aIndex,CApaProcess* aProcess);
    private: // from MDesCArray
        IMPORT_C TInt MdcaCount() const;
        IMPORT_C TPtrC MdcaPoint(TInt aIndex) const;
    private: // utility methods
        TInt GetAppListL(const TApaEmbeddabilityFilter& aFilter);
        TInt DoGetAppListL(RApaLsSession& aLs, const TApaEmbeddabilityFilter& aFilter);
        void SortAppListL();
    };

#endif  // EIKEMBAL_H

// End of File
