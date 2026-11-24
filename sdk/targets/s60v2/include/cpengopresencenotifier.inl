/*
* ==============================================================================
*  Name        : CPEngOPresenceNotifier.inl
*  Part of     : Presence API
*  Interface   : CPEngOPresenceNotifier.h
*  Description : Inline functions for ECOM plugin PEngOpenPresence.dll
*  Version     : 1.0
*
*  Copyright © 2003 Nokia Corporation.
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

// -----------------------------------------------------------------------------
// CPEngOPresenceNotifier::CPEngOPresenceNotifier
// Constructor
// -----------------------------------------------------------------------------
//
inline CPEngOPresenceNotifier::CPEngOPresenceNotifier()
    {
    }

// -----------------------------------------------------------------------------
// CPEngOPresenceNotifier::~CPEngOPresenceNotifier
// Destructor
// -----------------------------------------------------------------------------
//
inline CPEngOPresenceNotifier::~CPEngOPresenceNotifier()
    {
    // Destroy any instance variables and then
    // inform the framework that this specific 
    // instance of the interface has been destroyed.
    REComSession::DestroyedImplementation(iDtor_ID_Key);
    REComSession::FinalClose();
    }

// -----------------------------------------------------------------------------
// CPEngOPresenceNotifier::CPEngOPresenceNotifier
// 1st phase constructor
// Returns: <new CPEngOPresenceNotifier>
// -----------------------------------------------------------------------------
//
inline CPEngOPresenceNotifier* CPEngOPresenceNotifier::NewL()
    {
    _LIT8(KDefaultImplementation,"CPEngOPresenceNotifier");

    // Set up the interface find for the default resolver.
    TEComResolverParams resolverParams;
    resolverParams.SetDataType( KDefaultImplementation( ) );
    resolverParams.SetWildcardMatch(EFalse);

    TAny *ptr = REComSession::CreateImplementationL(
                                KCPEngOPresenceNotifierInterfaceUid, 
                                _FOFF(CPEngOPresenceNotifier,iDtor_ID_Key),
                                resolverParams );
    return REINTERPRET_CAST( CPEngOPresenceNotifier*,ptr );
    }

