// ETBUFFER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**@file ETBUFFER.H
   @publishedAll*/
	
#if !defined(__ET_BUFFER_H__)
#define __ET_BUFFER_H__

//
//	Number of server-side slots for each notification (greater than 1)
//
/**
@internalTechnology
*/
const TUint KSlotNumbersDefault				= 1;
//
//	RCall
//
/**
@internalComponent
*/
const TUint KSlotNumbersCallCapsChange		= 2;
const TUint KSlotNumbersCallStatusChange	= 4;


//
//	RLine
//
/**
@internalComponent
*/
const TUint KSlotNumbersLineStatusChange	= 4;
const TUint KSlotNumbersLineCallAddedChange = 4;



#endif