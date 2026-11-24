/*
* ==============================================================================
*  Name        : EPos_CPosLmOperation.inl
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : --
*  Description :
*
*  Version     : 1.5    2005/02/15 13:36:27
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


// -----------------------------------------------------------------------------
// ExecuteAndDeleteLD
//
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
inline void ExecuteAndDeleteLD(CPosLmOperation* aOperation)
    {
    CleanupStack::PushL(aOperation);
    aOperation->ExecuteL();
    CleanupStack::PopAndDestroy(aOperation);
    }


//  End of File
