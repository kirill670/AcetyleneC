/*
* ==============================================================================
*  Name        : CPEngOPresenceFetcher.inl
*  Part of     : Presence API
*  Interface   : CPEngOPresenceFetcher.h
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
// CPEngOPresenceFetcher::CPEngOPresenceFetcher
// Constructor
// -----------------------------------------------------------------------------
//
inline CPEngOPresenceFetcher::CPEngOPresenceFetcher()
    {
    }

// -----------------------------------------------------------------------------
// CPEngOPresenceFetcher::~CPEngOPresenceFetcher
// Destructor
// -----------------------------------------------------------------------------
//
inline CPEngOPresenceFetcher::~CPEngOPresenceFetcher()
    {
    // Destroy any instance variables and then
    // inform the framework that this specific 
    // instance of the interface has been destroyed.
    REComSession::DestroyedImplementation(iDtor_ID_Key);
    REComSession::FinalClose();
    }

// -----------------------------------------------------------------------------
// CPEngOPresenceFetcher::CPEngOPresenceFetcher
// 1st phase constructor
// Returns: <new CPresenceFetcher>
// -----------------------------------------------------------------------------
//
inline CPEngOPresenceFetcher* CPEngOPresenceFetcher::NewL()
    {
    _LIT8(KDefaultImplementation,"CPEngOPresenceFetcher");

    // Set up the interface find for the default resolver.
    TEComResolverParams resolverParams;
    resolverParams.SetDataType( KDefaultImplementation( ) );
    resolverParams.SetWildcardMatch(EFalse);

    TAny *ptr = REComSession::CreateImplementationL(
                                KCPEngOPresenceFetcherInterfaceUid, 
                                _FOFF(CPEngOPresenceFetcher,iDtor_ID_Key),
                                resolverParams );
    return REINTERPRET_CAST( CPEngOPresenceFetcher*,ptr );
    }

