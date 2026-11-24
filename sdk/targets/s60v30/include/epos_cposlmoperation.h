/*
* ==============================================================================
*  Name        : EPos_CPosLmOperation.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks API
*  Description :
*     See class description below
*  Version     : 1.16    2005/07/07 13:40:47
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

#ifndef CPOSLMOPERATION_H
#define CPOSLMOPERATION_H

//  INCLUDES
#include <e32base.h>

// FORWARD DECLARATION
class CPosLmOperation;

// STATIC FUNCTIONS
/**
*  Executes the operation synchronously and then deletes it.
*
*  All functions which returns a @ref CPosLmOperation object can be run
*  incrementally. If the client is not interested in running it
*  incrementally, it can call @ref CPosLmOperation::ExecuteL to run the
*  whole operation in one batch. This can be simplified by using
*  @ref ExecuteAndDeleteLD. It runs the operation and deletes the object
*  when it is done.
*
*  For instance, to use this function for
*  @ref CPosLandmarkDatabase::InitializeL, the client would call
*
*  ExecuteAndDeleteLD(database->InitializeL());
*
*  The operation object should not be on the cleanup stack when this function
*  is called.
*
*  @since S60 3.0
*  @param aOperation The operation to handle. It will be deleted when the
*   function returns.
*/
inline void ExecuteAndDeleteLD(CPosLmOperation* aOperation);

// CLASS DECLARATION

/**
*  Base class for handles to landmark operations.
*
*  Long running operations in the Landmarks API returns an object of this class
*  so that the client can run it incrementally and check the progress of the
*  operation.
*
*  The operation must explicitly be run by the client. The operation can
*  be run incrementally by calling @ref NextStep until it does not return
*  status @p KPosLmOperationNotComplete. Alternately the operation can be
*  run synchronously by calling @ref ExecuteL.
*
*  @ref ExecuteAndDeleteLD can be used to handle the operation object if
*  it is run in synchronous mode.
*
*  @lib eposlandmarks.lib
*  @since S60 3.0
*  @version $Revision: 1.16 $, $Date: 2005/07/07 13:40:47 $
*/
class CPosLmOperation : public CBase
    {
    public:  // Constructors and destructor

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CPosLmOperation();

    public: // New functions

        /**
        * Incremental execution of the operation.
        *
        * The client should use an active object and call this function until
        * it does not complete with status @p KPosLmOperationNotComplete.
        *
        * When the operation has finished, this function will complete with
        * status @p KErrNone if the operation was successful, or an error code
        * if some error was encountered.
        *
        * This function also returns a progress of the operation. Progress is a
        * floating point number in the interval [0.0,1.0]. 0.0 indicates that
        * the operation has not started and 1.0 indicates that the operation
        * has completed.
        *
        * Note that this function is asynchronous which means that status and
        * progress may not be set when the function returns. They are only
        * guaranteed to be set when the request is completed.
        *
        * The only way to cancel an operation is to delete the operation
        * object. This will also cancel any outstanding request to
        * @ref NextStep.
        *
        * If this function is called when the operation is already complete,
        * the function will panic with error code @p EPosInvalidOperationMode.
        *
        * @since S60 3.0
        * @param aStatus The request status. Will be completed when the step
        *   has been performed. The request status will be @p KRequestPending
        *   if the step has not completed. It will be
        *   @p KPosLmOperationNotComplete if the step has completed but more
        *   steps are needed before the operation will be completed. The
        *   request status will be @p KErrNone if the operation has finished
        *   successfully. The status will be set to an error code if the
        *   operation has failed.
        * @param aProgress Will be set to the progress of the operation when
        *   the step has finished.
        */
        virtual void NextStep(
        /* OUT */   TRequestStatus& aStatus,
        /* OUT */   TReal32& aProgress
        ) = 0;

        /**
        * Synchronous execution of the operation.
        *
        * When this function returns, the operation has finished.
        *
        * If this function is called when the operation is already complete,
        * or if the operation has been started incrementally using
        * @ref NextStep, this function will panic with error code
        * @p EPosInvalidOperationMode.
        *
        * @since S60 3.0
        */
        virtual void ExecuteL() = 0;

    protected:

        /**
        * C++ default constructor.
        */
        IMPORT_C CPosLmOperation();

    private:

        // By default, prohibit copy constructor
        CPosLmOperation( const CPosLmOperation& );
        // Prohibit assigment operator
        CPosLmOperation& operator= ( const CPosLmOperation& );

    };

#include "EPos_CPosLmOperation.inl"

#endif      // CPOSLMOPERATION_H

// End of File
