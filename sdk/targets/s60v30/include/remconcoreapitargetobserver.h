// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** @file
@publishedAll
@released
*/

#ifndef REMCONCOREAPITARGETOBSERVER_H
#define REMCONCOREAPITARGETOBSERVER_H

#include <e32base.h>
#include <remconcoreapi.h>

/**
Clients must implement this interface in order to instantiate objects of type 
CRemConCoreApiTarget. This interface passes incoming commands from RemCon to 
the client. 
In order to minimise the number of virtual functions the client has to 
implement, (a) they aren't pure, and (b) most commands are presented via 
'Command' with an operation ID. 
Commands which are associated with command-specific data come instead through 
specific methods, e.g. 'Play', which comes with a play speed.
*/
class MRemConCoreApiTargetObserver
	{
public:
	/** 
	A command has been received. 
	@param aOperationId The operation ID of the command.
	@param aButtonAct The button action associated with the command.
	*/
	virtual void MrccatoCommand(TRemConCoreApiOperationId aOperationId, 
		TRemConCoreApiButtonAction aButtonAct);
	
	/** 
	A 'play' command has been received. 
	@param aSpeed The playback speed.
	@param aButtonAct The button action associated with the command.
	*/
	virtual void MrccatoPlay(TRemConCoreApiPlaybackSpeed aSpeed, 
		TRemConCoreApiButtonAction aButtonAct);

	/**
	A 'tune function' command has been received.
	@param aTwoPart If EFalse, only aMajorChannel is to be used. Otherwise, 
	both aMajorChannel and aMinorChannel are to be used.
	@param aMajorChannel The major channel number.
	@param aMinorChannel The minor channel number.
	@param aButtonAct The button action associated with the command.
	*/
	virtual void MrccatoTuneFunction(TBool aTwoPart, 
		TUint aMajorChannel, 
		TUint aMinorChannel,
		TRemConCoreApiButtonAction aButtonAct);

	/** 
	A 'select disk function' has been received.
	@param aDisk The disk.
	@param aButtonAct The button action associated with the command.
	*/
	virtual void MrccatoSelectDiskFunction(TUint aDisk,
		TRemConCoreApiButtonAction aButtonAct);
	
	/** 
	A 'select AV input function' has been received.
	@param aAvInputSignalNumber The AV input.
	@param aButtonAct The button action associated with the command.
	*/
	virtual void MrccatoSelectAvInputFunction(TUint8 aAvInputSignalNumber,
		TRemConCoreApiButtonAction aButtonAct);

	/** 
	A 'select audio input function' has been received.
	@param aAudioInputSignalNumber The audio input.
	@param aButtonAct The button action associated with the command.
	*/
	virtual void MrccatoSelectAudioInputFunction(TUint8 aAudioInputSignalNumber,
		TRemConCoreApiButtonAction aButtonAct);
	};

#endif // REMCONCOREAPITARGETOBSERVER_H
