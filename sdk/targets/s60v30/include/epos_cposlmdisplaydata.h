/*
* ==============================================================================
*  Name        : EPos_CPosLmDisplayData.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks Search API
*  Description :
*     See class description below
*  Version     : 1.10    2005/03/21 08:02:49
*
*  Copyright (c) 2002-2005 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
*
* ==============================================================================
*/

#ifndef CPOSLMDISPLAYDATA_H
#define CPOSLMDISPLAYDATA_H

//  INCLUDES
#include <e32base.h>

// CONSTANT DECLARATIONS
const TInt KPosLmNoNewItems = -1;

// FORWARD DECLARATIONS
class CPosLmDisplayItem;
class CPosLmPartialReadParameters;

// CLASS DECLARATION

/**
* Displayable data collection.
*
* A displayable data collection consists of displayable items
* (@ref CPosLmDisplayItem). A displayable data collection either
* consists of landmark items (if a landmark search has been started)
* or category items (if a category search has been started).
* Items of different types cannot be mixed in the collection.
*
* Displayable data is used in @ref CPosLandmarkSearch and
* @ref CPosLmMultiDbSearch to hold search results. The collection is
* populated with new results every time the next search step is executed.
* Displayable items contain full or partial (see @ref SetPartialReadParameters)
* landmark data or full category data, and can be used to display search
* results already during the search and also after it has completed.
*
* Note: The single class instance may only be used by one search
* instance at a time.
*
* @version $Revision: 1.10 $, $Date: 2005/03/21 08:02:49 $
*/
class CPosLmDisplayData : public CBase
    {

    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLmDisplayData* NewL();

        /**
        * Destructor.
        */
        virtual ~CPosLmDisplayData();

    public:  // New functions

        /**
        * Returns the index of the next match found during current asynchronous
        * search operation. If the search is executed synchronously, then all
        * indexes of the matches found during the search are returned one
        * by one.
        *
        * After each search step, the new item indexes are returned in
        * ascending order according to the specified sort preference in
        * the search.
        *
        * @return The item index or @p KPosLmNoNewItems when no new items
        *   are available.
        */
        IMPORT_C TInt NewItemIndex();

        /**
        * Returns the number of items in the collection.
        *
        * @return The number of items.
        */
        IMPORT_C TInt Count() const;

        /**
        * Resets the collection and deletes all contained items.
        */
        IMPORT_C void Reset();

        /**
        * Returns the displayable item specified by index.
        * The index must be strictly less than @ref Count and not less than 0,
        * otherwise this function panics with @p EPosInvalidIndex.
        *
        * @param aItemIndex A displayable item index.
        * @return A displayable item.
        */
        IMPORT_C CPosLmDisplayItem& DisplayItem(
        /* IN */        TInt aItemIndex
        ) const;

        /**
        * Sets the partial read parameters for this display data.
        *
        * Partial read parameters are used to define which landmark data should
        * be read during a landmark search. If no partial read parameters are
        * set, the whole landmark will be read.
        *
        * This function only affects the searches which are started after
        * it is called. The current search is not affected.
        *
        * If landmarks are sorted by name, the name will always be a part of
        * the landmark in the display data, even if it is not requested.
        *
        * Note: Partial read parameters are only used for landmark searches.
        *
        * @param aPartialSettings The partial read parameters.
        */
        IMPORT_C void SetPartialReadParametersL(
        /* IN */        const CPosLmPartialReadParameters& aPartialSettings
        );

        /**
        * Unsets the partial read parameters for this display data.
        *
        * This means that from now on all landmarks added to this display data
        * instance will contain all information.
        *
        * To have any affect, this function must be called before a search is
        * started. If it is called during a search, it will only affect
        * the next search.
        *
        * Note: Partial read parameters will only have effect on landmarks
        * searches.
        *
        * @param aPartialSettings The partial read parameters.
        */
        IMPORT_C void UnsetPartialReadParameters();

        /*
        * Returns the partial read parameters set for this display data.
        *
        * @return Partial read parameters or NULL if not set.
        */
        CPosLmPartialReadParameters* PartialReadParameters() const;

        /*
        * Returns a reference to all the displayable items.
        * This array owns its displayable items.
        *
        * @return The items array.
        */
        RPointerArray<CPosLmDisplayItem>& DisplayItems();

        /*
        * Returns a reference to the new displayable items.
        * This array does not own its displayable items.
        * New displayable items are always a subset of all displayable items.
        *
        * @return The new item indexes array.
        */
        RPointerArray<CPosLmDisplayItem>& NewDisplayItems();

    private:

        /**
        * C++ default constructor.
        */
        CPosLmDisplayData();

    private:    // Data

        RPointerArray<CPosLmDisplayItem> iDisplayItems;

        RPointerArray<CPosLmDisplayItem> iNewDisplayItems;

        CPosLmPartialReadParameters* iPartialParameters;

    };

#endif      // CPOSLMDISPLAYDATA_H

// End of File
