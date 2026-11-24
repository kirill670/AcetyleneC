/*
* ==============================================================================
*  Name        : EPos_CPosLandmarkSearch.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks Search API
*  Description :
*     See class description below
*  Version     : 1.20    2005/03/21 07:39:03
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

#ifndef CPOSLANDMARKSEARCH_H
#define CPOSLANDMARKSEARCH_H

//  INCLUDES
#include <e32base.h>
#include <EPos_CPosLandmarkDatabase.h>
#include <EPos_CPosLmCategoryManager.h>
#include <EPos_CPosLmItemIterator.h>
#include <EPos_CPosLmOperation.h>
#include <EPos_TPosLmSortPref.h>

// FORWARD DECLARATIONS
class CPosLmSearchCriteria;
class CPosLmDisplayData;

// CONSTANT DECLARATIONS
const TInt KPosLmMaxNumOfMatchesUnlimited = -1;

// CLASS DECLARATION

/**
*  This class is used to perform searches for landmarks or landmark categories
*  in a landmark database.
*
*  To search a landmark database, an instance of this class is created,
*  supplying the database to search. The client creates a criterion object to
*  specify what to search for. There are different criterion classes which all
*  inherit from @ref CPosLmSearchCriteria. For instance, the client can search
*  for landmarks which contain a certain text string by passing a
*  @ref CPosLmTextCriteria.
*
*  Some criterion classes are used for searching for landmarks (e.g.
*  @ref CPosLmCategoryCriteria is used for searching for landmarks which
*  contain a certain category) and some are used
*  to search for landmark categories (e.g. @ref CPosLmCatNameCriteria is used
*  to search for landmark categories by specifying a category name which may
*  contain wild-card characters).
*
*  Searches can be run in incremental mode.
*  @ref StartLandmarkSearchL and @ref StartCategorySearchL both return a
*  @p CPosLmOperation object which is used to execute the search. If it is
*  run incrementally the client can supervise the progress of the operation.
*  If it is sufficient to run the search synchronously, the client only has to
*  call @p CPosLmOperation::ExecuteL. The client can cancel
*  the search by deleting the @p CPosLmOperation object.
*
*  By default, these functions start a new search, but the client can specify
*  that only previous matches should be searched. This can be used to refine
*  the search when there are many matches.
*
*  During the search execution a read-lock is acquired for each database.
*
*  Only one search can be performed at a time by the single instance of
*  the class. If a search is already running, the search function leaves
*  with error code @p KErrInUse.
*
*  After search completion, the client can make a second search and specify
*  that only the matches from the previous search shall be considered.
*
*  The client can also set a limit on how many search matches should be
*  returned (see @ref SetMaxNumOfMatches).
*
*  The client retrieves the matches from the search by requesting an iterator
*  (see @ref MatchIteratorL) or by using display data (see @ref SetDisplayData).
*
*  @p NetworkServices capability is required for remote databases.
*
*  @version $Revision: 1.20 $, $Date: 2005/03/21 07:39:03 $
*/
class CPosLandmarkSearch : public CBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * The client takes ownership of the returned search object.
        *
        * @param aDatabase The landmark database to search.
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLandmarkSearch* NewL(
        /* IN  */       CPosLandmarkDatabase&  aDatabase
        );

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CPosLandmarkSearch();

    public: // New functions

        /**
        * Retrieves the maximum number of search matches limit.
        *
        * By default the maximum number of matches is unlimited.
        *
        * @return The maximum number of search matches or
        *   @p KPosLmMaxNumOfMatchesUnlimited if unlimited.
        */
        IMPORT_C TInt MaxNumOfMatches() const;

        /**
        * Sets the maximum number of search matches limit.
        *
        * If the limit is set, the search operation will stop when this limit
        * is reached.
        *
        * By default the maximum number of matches is unlimited.
        *
        * If a new value for maximum number of matches is set when a search is
        * ongoing, it will not affect the current search. The new maximum will
        * be utilized in the next search.
        *
        * @param aMaxNumOfMatches the maximum number of search matches.
        *   KPosLmMaxNumOfMatchesUnlimited means that the number of matches is
        *   unlimited.
        */
        IMPORT_C void SetMaxNumOfMatches(
        /* IN  */       TInt  aMaxNumOfMatches = KPosLmMaxNumOfMatchesUnlimited
        );

        /**
        * Starts a search for landmarks.
        *
        * If there are no previous matches and the client specifies that
        * previous matches should be used, this function leaves with error
        * code @p KErrArgument.
        *
        * If a search is already running, this function leaves with error
        * code @p KErrInUse.
        *
        * If the search criterion is not valid for landmark searching, this
        * function leaves with error code @p KErrArgument.
        *
        * If the search criterion is not supported, this function leaves
        * with error code @p KErrNotSupported.
        *
        * The client takes ownership of the returned operation object.
        *
        * This function requires @p ReadUserData capability.
        *
        * @param aCriteria The search criterion.
        * @param aSearchOnlyPreviousMatches This flag may be used to perform a
        *   search within the results of previous search.
        * @returns A handle to the search operation.
        */
        virtual CPosLmOperation* StartLandmarkSearchL(
        /* IN  */       const CPosLmSearchCriteria&  aCriteria,
        /* IN  */       TBool  aSearchOnlyPreviousMatches = EFalse
        ) = 0;

        /**
        * Starts a search for landmarks.
        *
        * This overload of the @ref StartLandmarkSearchL function lets the
        * client define the sort order for the search matches.
        *
        * Only sorting by landmark name is supported. If the client tries to
        * sort by another attribute, this function will leave with error code
        * @p KErrNotSupported.
        *
        * If there are no previous matches and the client specifies that
        * previous matches should be used, this function leaves with error
        * code @p KErrArgument.
        *
        * If a search is already running, this function leaves with error
        * code @p KErrInUse.
        *
        * If the search criterion is not valid for landmark searching, this
        * function leaves with error code @p KErrArgument.
        *
        * If the search criterion is not supported, this function leaves
        * with error code @p KErrNotSupported.
        *
        * The client takes ownership of the returned operation object.
        *
        * This function requires @p ReadUserData capability.
        *
        * @param aCriteria The search criterion.
        * @param aSortPref A sort preference object.
        * @param aSearchOnlyPreviousMatches This flag may be used to perform a
        *   search within the results of previous search.
        * @returns A handle to the search operation.
        */
        virtual CPosLmOperation* StartLandmarkSearchL(
        /* IN  */       const CPosLmSearchCriteria&  aCriteria,
        /* IN  */       const TPosLmSortPref&  aSortPref,
        /* IN  */       TBool  aSearchOnlyPreviousMatches = EFalse
        ) = 0;

        /**
        * Starts a search for landmark categories.
        *
        * The criterion which defines whether a landmark category is a match or
        * not is passed as input to this function.
        *
        * If a search is already running, this function leaves with error
        * code @p KErrInUse.
        *
        * If the search criterion is not valid for landmark category searching,
        * this function leaves with error code @p KErrArgument.
        *
        * If the search criterion is not supported, this function leaves
        * with error code @p KErrNotSupported.
        *
        * The client takes ownership of the returned operation object.
        *
        * This function requires @p ReadUserData capability.
        *
        * @param aCriteria The search criterion.
        * @param aSortPref Sort preference for the search results.
        * @param aSearchOnlyPreviousMatches This flag may be used to perform a
        *   search within the results of previous search.
        * @returns A handle to the search operation.
        */
        virtual CPosLmOperation* StartCategorySearchL(
        /* IN  */       const CPosLmSearchCriteria&  aCriteria,
        /* IN  */       CPosLmCategoryManager::TCategorySortPref  aSortPref,
        /* IN  */       TBool  aSearchOnlyPreviousMatches = EFalse
        ) = 0;

        /**
        * Returns the number of matches so far in the search.
        *
        * This function can also be called during a search operation.
        *
        * @return The number of search matches.
        */
        virtual TUint NumOfMatches() const = 0;

        /**
        * Creates an iterator object to iterate the matching landmarks or
        * landmark categories.
        *
        * This function can also be called during a search in order to read the
        * matches encountered so far. Note that the iterator will not iterate
        * any new matches. If new matches are found, a new iterator must be
        * created.
        *
        * If a sort preference was specified when the search was started,
        * the landmarks/categories will be sorted when the search is complete
        * but the items are not necessarily sorted if this function is called
        * during a search.
        *
        * Note: If the client has set display data and resets the display data
        * during a search, the sort order in the iterator might be incorrect.
        *
        * The client takes ownership of the returned iterator object.
        *
        * Note that the iterator iterates matches in @ref CPosLandmarkSearch.
        * It cannot be used after the search object has been deleted. Make sure
        * to delete the iterator first.
        *
        * @return A search match iterator.
        */
        virtual CPosLmItemIterator* MatchIteratorL() = 0;

        /**
        * Display data can be used as an alternative way to get result
        * from a database search. Landmarks or categories are added to the
        * display data collection during a search depending on the search type.
        *
        * This function may replace the combination of using
        * @ref MatchIteratorL and reading landmark or category data.
        * Result data is read already during the search and no duplicate
        * access to database is needed.
        *
        * The display data object will be reset each time a new search is
        * started. No items during the search are removed from the
        * collection. New found matches can be added every time next
        * search step is completed, see @ref CPosLmDisplayData::NewItemIndex.
        *
        * Note: The database index of displayable data items in
        * @ref CPosLmDisplayData will be set to 0 as it has no meaning in a
        * single database search.
        *
        * If the client sets display data during an ongoing search, this
        * function panics with @p EPosSearchOperationInUse.
        *
        * The client owns the display data object. If the client deletes it
        * during a search, this may lead to unexpected errors. The client must
        * call @ref UnsetDisplayData before it deletes the display data object.
        *
        * Note: If the client resets the display data during a search, the sort
        * order in the iterator might become incorrect.
        *
        * @param aData The displayable data.
        */
        virtual void SetDisplayData(
        /* IN/OUT */        CPosLmDisplayData& aData
        ) = 0;

        /**
        * Unsets display data. No further data will be added to the display
        * data that was set with @ref SetDisplayData.
        *
        * If the client unsets display data during an ongoing search, this
        * function panics with @p EPosSearchOperationInUse.
        */
        virtual void UnsetDisplayData() = 0;

    protected:

        /**
        * C++ default constructor.
        */
        IMPORT_C CPosLandmarkSearch();

    private:

        // By default, prohibit copy constructor
        CPosLandmarkSearch( const CPosLandmarkSearch& );
        // Prohibit assigment operator
        CPosLandmarkSearch& operator= ( const CPosLandmarkSearch& );

    private:    // Data

        TUid iDtorIdKey;
        TInt iMaxNumOfMatches;
    };

// CPOSLANDMARKSEARCH_H
#endif

// End of File
