// C32COMM.INL
//
// Copyright (c) Symbian Software Ltd. 1997-2004.  All rights reserved.
//

// PLEASE NOTE: This file is part of Version 1 of C32 - that is, the single-threaded version.
// The multi-threaded C32 version of this file is in c32\INC


/**
 * @file
 *
 * implements inline methods of RComm
 */

inline void RComm::SetSignals(TUint aSetMask, TUint aClearMask)
/** Sets or clears RS232 output lines (DTR and RTS).

For many applications, these lines will be read and set under driver control 
as determined by the handshaking options selected.

@param aSetMask Set the handshaking lines in the mask. 
@param aClearMask Clear the handshaking lines in the mask. 
@publishedAll

*/
	{
	SetSignalsToMark(aSetMask);
	SetSignalsToSpace(aClearMask);
	}
