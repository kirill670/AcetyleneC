// MmfController.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//


#ifndef __MMFCONTROLLER_H__
#define __MMFCONTROLLER_H__

#include <mmf/server/mmfdatasource.h>
#include <mmf/server/mmfdatasink.h>
#include <mmf/common/mmfcontrollerframework.h>
#include <mmf/common/mmfcontrollerpluginresolver.h>
#include <mmfPluginInterfaceUIDs.hrh>


/**
@publishedAll

Error category denoting a general controller error.

@see TMMFEvent
@since 7.0s
*/
const TUid KMMFErrorCategoryControllerGeneralError = {0x101F76D3};
/**
 * @publishedAll
 */
const TUid KMMFEventCategoryPlaybackComplete = {0x101f7ea0};

/**
 * @internalComponent
 */
const TUid KUidInterfaceMMFDataSinkHolder = {0x101F76D4};
/**
 * @internalComponent
 */
const TUid KUidInterfaceMMFDataSourceHolder = {0x101F76D5};

/**
 * @internalComponent
 *
 * Create a const TUid with the same values as the controller 
 * ECOM plugin interface UID
 */
const TUid KUidInterfaceMMFController = {KMmfUidPluginInterfaceController};

/**
@internalComponent

IPC messages for interface <code>KUidInterfaceMMFController</code> in the controller framework.
*/
enum TMMFControllerMessages
	{
	EMMFControllerAddDataSource,
	EMMFControllerAddDataSink,
	EMMFControllerRemoveDataSource,
	EMMFControllerRemoveDataSink,
	EMMFControllerReset,
	EMMFControllerPrime,
	EMMFControllerPlay,
	EMMFControllerPause,
	EMMFControllerStop,
	EMMFControllerGetPosition,
	EMMFControllerSetPosition,
	EMMFControllerGetDuration,
	EMMFControllerGetNumberOfMetaDataEntries,
	EMMFControllerGetSizeOfMetaDataEntry,//use internally
	EMMFControllerGetMetaDataEntry,
	EMMFControllerSetPrioritySettings
	};



/**
@publishedAll

Client representation of a controller plugin for the Multimedia Framework.

This class allows a client to load a controller plugin into a new thread and access the
functionality provided by that plugin.
@released
@since 7.0s
*/
class RMMFController
	{
public:
/**
Constructor.
@since 7.0s
*/
	IMPORT_C RMMFController();

/**
Load a controller plugin by specifying the uid of the plugin to load.

Creates a new thread and loads the specified controller into the new thread.  Use the classes
<code>CMMFControllerPluginSelectionParameters<\code> and <CMMFFormatSelectionParamters<\code>
to find the uid of the controller to load.

@param "aControllerUid"		"The uid of the controller plugin to be loaded."
@param "aPrioritySettings"	"The priority settings for this plugin, used by the policy 
							component to arbitrate between different controllers that are 
							attempting to use the same hardware resource simultaneously."
@return	"One of the standard error codes."
@see CMMFControllerPluginSelectionParamters
@since 7.0s
*/
	IMPORT_C TInt Open(TUid aControllerUid, const TMMFPrioritySettings& aPrioritySettings);

/**
Close the controller plugin.  

Calling this method will unload the controller plugin and close down the controller thread.
@since	7.0s
*/
	IMPORT_C void Close();

/**
Set the priority settings for this controller.

@param "aPrioritySettings"	"The priority settings for this plugin, used by the policy 
							component to arbitrate between different controllers that are 
							attempting to use the same hardware resource simultaneously."
@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt SetPrioritySettings(const TMMFPrioritySettings& aPrioritySettings) const;

/**
Add a data source to the controller.

A typical data source would be a file, descriptor, audio input (microphone) or camera.
A controller plugin may require multiple data sources to be added (for example a video
recorder controller would require two); the exact number is plugin-specific.
Data sources are plugins themselves, and are loaded by the controller framework
inside the controller thread.

@param "aSourceUid"			"The uid of the data source to be added. For more information, 
							see the documentation for the data source you wish to add."
@param "aSourceInitData"	"Data used to initialise the data source.  The exact contents
							of this data are dependent on the type of data source. For more
							information, see the documentation for the data source you wish
							to add."
@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt AddDataSource(TUid aSourceUid, const TDesC8& aSourceInitData);

/**
Add a data sink to the controller.

A typical data sink would be a file, descriptor, audio output (speaker) or display.
A controller plugin may require multiple data sinks to be added (for example a video
playing controller would require two); the exact number is plugin-specific.
Data sinks are plugins themselves, and are loaded by the controller framework
inside the controller thread.

@param "aSinkUid"			"The uid of the data sink to be added. For more information, 
							see the documentation for the data sink you wish to add."
@param "aSinkInitData"		"Data used to initialise the data sink.  The exact contents
							of this data are dependent on the type of data sink. For more
							information, see the documentation for the data sink you wish
							to add."
@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt AddDataSink(TUid aSinkUid, const TDesC8& aSinkInitData);

/**
Add a data source to the controller, and receive a handle to allow removal and direct
communication with that data source.

A typical data source would be a file, descriptor, audio input (microphone) or camera.
A controller plugin may require multiple data sources to be added (for example a video
recorder controller would require two); the exact number is plugin-specific.
Data sources are plugins themselves, and are loaded by the controller framework
inside the controller thread.

@param "aSourceUid"			"The uid of the data source to be added. For more information, 
							see the documentation for the data source you wish to add."
@param "aSourceInitData"	"Data used to initialise the data source.  The exact contents
							of this data is dependent on the type of data source. For more
							information, see the documentation for the data source you wish
							to add."
@param "aHandleInfo"		"This object is filled in by the controller framework, and identifies
							the data source inside the controller framework.  This allows
							the caller to send custom commands directly to the data source, and
							to also remove the data source from the controller.  Note that
							not all data sources support custom commands, and not all
							controller plugins support the removal of a data source."
@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt AddDataSource(TUid aSourceUid, const TDesC8& aSourceInitData, TMMFMessageDestination& aHandleInfo);

/**
Add a data sink to the controller, and receive a handle to allow removal and direct
communication with that data sink.

A typical data sink would be a file, descriptor, audio output (speaker) or display.
A controller plugin may require multiple data sinks to be added (for example a video
playing controller would require two); the exact number is plugin-specific.
Data sinks are plugins themselves, and are loaded by the controller framework
inside the controller thread.

@param "aSinkUid"			"The uid of the data sink to be added. For more information, 
							see the documentation for the data sink you wish to add."
@param "aSinkInitData"		"Data used to initialise the data sink.  The exact contents
							of this data are dependent on the type of data sink. For more
							information, see the documentation for the data sink you wish
							to add."
@param "aHandleInfo"		"This object is filled in by the controller framework, and identifies
							the data sink inside the controller framework.  This allows
							the caller to send custom commands directly to the data sink, and
							to also remove the data sink from the controller.  Note that
							not all data sinks support custom commands, and not all
							controller plugins support the removal of a data sink."
@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt AddDataSink(TUid aSinkUid, const TDesC8& aSinkInitData, TMMFMessageDestination& aHandleInfo);

/**
Remove a data source from the controller.

In certain situations, it may be necessary to remove a data source from a controller, for
example when you need to play a different file of the same format as the current one.

It should be noted that not all controller plugins will support the removal of a data source.

@param "aHandleInfo"		"The handle object returned by the controller framework when the 
							data source was added."
@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt RemoveDataSource(const TMMFMessageDestination& aSourceHandleInfo);

/**
Remove a data sink from the controller.

In certain situations, it may be necessary to remove a data sink from a controller, for
example when you need change output devices on the fly.

It should be noted that not all controller plugins will support the removal of a data sink.

@param "aHandleInfo"		"The handle object returned by the controller framework when the 
							data sink was added."
@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt RemoveDataSink(const TMMFMessageDestination& aSinkHandleInfo);

/**
Revert the controller plugin back to the state it is in just after it has been Opened.

Note: all sources and sinks will be removed from the controller.

@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt Reset();

/**
Prepare the controller to start playing.
The controller should initialise its sources, sinks and buffers. This moves the controller
from the STOPPED to the PRIMED state.

@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt Prime();

/**
Start the controller playing.
The controller will begin transferring data from its data source(s) to its data sink(s).

This moves the controller from the PRIMED to the PLAYING state.

<code>Play()<\code> means "Start Playing" - i.e. this method will return as soon as
playback has begun.
If the data transfer comes to an end due to an internal event (e.g. source runs out of data),
the caller will be notified via the <code>ReceiveEvents()<\code> interface.

Note: Prime() must have been called prior to calling Play().

@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt Play();

/**
Pause the controller.

The controller will cease transferring data from its data source(s) to its data sink(s).
A subsequent call to <code>Play()<\code> will result in the data transfer resuming from the
same place as when the <code>Pause()<\code> was called.

This moves the controller from the PLAYING back to the PRIMED state.

Note: Play() must have been called prior to calling Pause().

@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt Pause();

/**
Stop the controller.

The controller will cease transferring data from its data source(s) to its data sink(s), reset
its position and delete any allocated buffers.  
In effect, calling <code>Stop()<\code> undoes any actions performed by the controller 
during the call to <code>Prime()<\code>.

This moves the controller from the PRIMED back to the STOPPED state.

@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt Stop();
	
/**
Get the current position microseconds.  

Note: The controller must be in the PRIMED or PLAYING state before this can be called.

@param "aPosition" "The current position in microseconds, filled in by the controller framework."
@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt GetPosition(TTimeIntervalMicroSeconds& aPosition) const;

/**
Set the current position microseconds.  

Note: The controller must be in the PRIMED or PLAYING state before this can be called.

@param "aPosition"	"The new transfer position in microseconds."
@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt SetPosition(const TTimeIntervalMicroSeconds& aPosition) const;

/**
Get the duration of the clip in microseconds.  

Note: The controller must be in the PRIMED or PLAYING state before this can be called.

@param "aDuration"			"The duration of the clip in microseconds, filled in by the 
							controller framework."
@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt GetDuration(TTimeIntervalMicroSeconds& aDuration) const;

/**
Get the number a meta data entries in the clip.

A clip may contain zero or more entries of meta data, e.g Author, Copyright etc.

@param "aNumberOfEntries" "The number of meta data entries in the clip, filled in by the controller framework."
@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt GetNumberOfMetaDataEntries(TInt& aNumberOfEntries) const;

/**
Get a particular meta data entry from the clip.

All meta data entries can be retrieved by multiple calls to this method, iterating 
<code>aIndex<\code> from 0 to the value returned by <code>GetNumberOfMetaDataEntries<\code>.

@param	"aIndex" "The index of the meta data entry to retrieve."
@return	"The meta data entry retrieved from the controller plugin.  Ownership of the entry is
		passed to the caller."
@leave	""	"One of the standard system-wide error codes."
@see	CMMFMetaDataEntry
@since	7.0s
*/
	IMPORT_C CMMFMetaDataEntry* GetMetaDataEntryL(TInt aIndex) const;

/**
Send a custom command synchronously to the controller plugin.

Custom commands allow controller plugins to extend the standard API.  

Note: This method will not return until the controller plugin has serviced the command.

@param	"aDestination"	"The destination of the custom command, consisting of the uid of
						the interface of this custom command and a special handle id
						<code>KMMFObjectHandleController<\code>	to indicate that the custom 
						command is to be handled by the controller plugin."
@param "aFunction"		"The function number to indicate which function is to be called
						on the controller's custom command interface."
@param "aDataTo1"		"A reference to data to be copied to the controller plugin. The exact
						contents of the data are dependent on the custom command interface
						of the controller.  Use a value of KNullDesC8 if you have no data to send."
@param "aDataTo2"		"A reference to data to be copied to the controller plugin. The exact
						contents of the data are dependent on the custom command interface
						of the controller.  Use a value of KNullDesC8 if you have no data to send."
@param "aDataFrom"		"A reference to an area of memory to which the controller plugin will 
						write any data to be passed back to the client."
@return	"The result of the custom command.  Exact range of values is dependent on the
		custom command interface."
@since	7.0s
*/
	IMPORT_C TInt CustomCommandSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom);


/**
Send a custom command synchronously to the controller plugin.

Custom commands allow controller plugins to extend the standard API.  

Note: This method will not return until the controller plugin has serviced the command.

@param	"aDestination"	"The destination of the custom command, consisting of the uid of
						the interface of this custom command and a special handle id
						<code>KMMFObjectHandleController<\code>	to indicate that the custom 
						command is to be handled by the controller plugin."
@param "aFunction"		"The function number to indicate which function is to be called
						on the controller's custom command interface."
@param "aDataTo1"		"A reference to data to be copied to the controller plugin. The exact
						contents of the data are dependent on the custom command interface
						of the controller. Use a value of KNullDesC8 if you have no data to send."
@param "aDataTo2"		"A reference to data to be copied to the controller plugin. The exact
						contents of the data are dependent on the custom command interface
						of the controller. Use a value of KNullDesC8 if you have no data to send."
@return	"The result of the custom command.  Exact range of values is dependent on the
		custom command interface."
@since	7.0s
*/
	IMPORT_C TInt CustomCommandSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2);

/**
Send a custom command asynchronously to the controller plugin.

Custom commands allow controller plugins to extend the standard API.  

Note: This method will return immediately.  The RunL of the active object owning the <code>aStatus<\code>
parameter will be called when the command is completed by the controller plugin.

@param	"aDestination"	"The destination of the custom command, consisting of the uid of
						the interface of this custom command and a special handle id
						<code>KMMFObjectHandleController<\code>	to indicate that the custom 
						command is to be handled by the controller plugin."
@param "aFunction"		"The function number to indicate which function is to be called
						on the controller's custom command interface."
@param "aDataTo1"		"A reference to data to be copied to the controller plugin. The exact
						contents of the data are dependent on the custom command interface
						of the controller. Use a value of KNullDesC8 if you have no data to send."
@param "aDataTo2"		"A reference to data to be copied to the controller plugin. The exact
						contents of the data are dependent on the custom command interface
						of the controller. Use a value of KNullDesC8 if you have no data to send."
@param "aDataFrom"		"A reference to an area of memory to which the controller plugin will 
						write any data to be passed back to the client."
@param "aStatus"		"The TRequestStatus of an active object.  This will  contain the 
						result of the custom command on completion.  The exact range of 
						result values is dependent on the custom command interface."
@since	7.0s
*/
	IMPORT_C void CustomCommandAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom, TRequestStatus& aStatus);

/**
Send a custom command asynchronously to the controller plugin.

Custom commands allow controller plugins to extend the standard API.  

Note: This method will return immediately.  The RunL of the active object owning the <code>aStatus<\code>
parameter will be called when the command is completed by the controller plugin.

@param	"aDestination"	"The destination of the custom command, consisting of the uid of
						the interface of this custom command and a special handle id
						<code>KMMFObjectHandleController<\code>	to indicate that the custom 
						command is to be handled by the controller plugin."
@param "aFunction"		"The function number to indicate which function is to be called
						on the controller's custom command interface."
@param "aDataTo1"		"A reference to data to be copied to the controller plugin. The exact
						contents of the data are dependent on the custom command interface
						of the controller. Use a value of KNullDesC8 if you have no data to send."
@param "aDataTo2"		"A reference to data to be copied to the controller plugin. The exact
						contents of the data are dependent on the custom command interface
						of the controller. Use a value of KNullDesC8 if you have no data to send."
@param "aStatus"		"The TRequestStatus of an active object.  This will  contain the 
						result of the custom command on completion.  The exact range of 
						result values is dependent on the custom command interface."
@since	7.0s
*/
	IMPORT_C void CustomCommandAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TRequestStatus& aStatus);

/**
Register to receive events from the controller plugin.

Events can be generated at any time, and are generally associated with things that occur
due to something happening internally within the controller. For example, an event will
be generated if the controller stops playing due to reaching the end of a file.
	
@param	"aEventPckg"	"A reference to a TMMFEventPckg object that must be member data
						of the active object calling this method.  The details of the event
						will be copied into this object when an event occurs."
@param "aStatus"		"The TRequestStatus of the active object calling this method."
@see	TMMFEvent
@see	CMMFControllerEventMonitor
@since	7.0s
*/
	IMPORT_C void ReceiveEvents(TMMFEventPckg& aEventPckg, TRequestStatus& aStatus);

/**
Cancel a previous registration to receive events from the controller plugin.

This must be called from the <code>DoCancel()<\code> method of the active object using the
ReceiveEvents() API.

@return "One of the standard system-wide error codes."
@see	TMMFEvent
@since	7.0s
*/
	IMPORT_C TInt CancelReceiveEvents();

private:
/**
The controller proxy.  Used to pass messages to the controller thread.
*/
	RMMFControllerProxy iControllerProxy;

/**
Used to hold the destination information for messages for the standard controller plugin interface.
*/
	TMMFMessageDestinationPckg iDestinationPckg;
	};



/**
@publishedAll

Defines an object to which a client may have a direct handle.

This class provides a way of identifying objects within the controller framework, and a means
of passing commands to those objects.

@released
@since 7.0s
*/
class CMMFObject : public CBase
	{
friend class CMMFObjectContainer;//to set the handle
public:
	IMPORT_C ~CMMFObject();

/**
Constructor.

@param "aInterfaceId"	"The UID of the interface provided by this object."
@since 7.0s
*/
	IMPORT_C CMMFObject(TUid aInterfaceId);

/**
Returns the handle of the object.

@return "The handle of this object."
@since 7.0s
*/
	IMPORT_C const TMMFMessageDestination& Handle();

/*
Compares two CMMFObjects by comparing their handles.

@param "aOther"	"The object to be compared with this object."
@return "ETrue if the objects are the same"
@return "EFalse if the objects are different."
@since 7.0s
**/
	IMPORT_C TBool operator==(const CMMFObject& aOther);

/*
Passes a message to the object to handle.

This is a pure virtual method to be implemented by concrete classes derived from this class.

The message passed in MUST be completed by the object; however, it can be copied to be 
completed at a later time, should some other asynchronous action need to occur first.

@param "aMessage"	"The message to be handled.  This MUST be completed by the object."
@since 7.0s
**/
	virtual void HandleRequest(TMMFMessage& aMessage) = 0;
private:
	void SetHandle(const TMMFMessageDestination& aNewHandle);
private:
	TMMFMessageDestination iHandle;
	};


/**
@publishedAll

Container class to hold the CMMFObject-derived objects in the controller framework.

@released
@since 7.0s
*/
class CMMFObjectContainer : public CBase
	{
public:
/**
Constructor.

@since	7.0s
*/
	IMPORT_C CMMFObjectContainer();

/**
Destructor.

Deletes all objects owned by the container.

@since	7.0s
*/
	IMPORT_C ~CMMFObjectContainer();

/**
Add an object to the container.

Once the object has been added, its ownership is transferred to the container.	
@param	"aObject" "A reference to the object to be added to the container."
@return	"One of the standard system-wide error codes.  If the return code is not KErrNone, then
		ownership of the object still remains with the caller."
@since	7.0s
*/
	IMPORT_C TInt AddMMFObject(CMMFObject& aObject);

/**
Removes and destroys an object from the container.

This method ensures that the object is no longer in the container, and that it gets deleted.
Even if the object is not found in the container's array of objects, it will be deleted.
@param	"aObject" "A reference to the object to be deleted."
@since	7.0s
*/
	IMPORT_C void RemoveAndDestroyMMFObject(CMMFObject& aObject);

/**
Find an object in the container using a handle.

@param	"aObjectHandle" "The handle of the object to be located."
@param	"aObjectFound"	"A reference to a pointer to the object found in the container."
@return	"One of the standard system-wide error codes."
@since	7.0s
*/
	IMPORT_C TInt FindMMFObject(const TMMFMessageDestination& aObjectHandle, CMMFObject*& aObjectFound);

/**
Removes and destroys all objects from the container.

@since	7.0s
*/
	IMPORT_C void DeleteAllObjects();
private:
/**
Internal method to find an object in the array.
*/
	TInt FindMMFObject(const CMMFObject& aObject, TInt& aPositionInArray);

/**
Internal method used to generate the object handle for a newly added object.
*/
	TInt GenerateObjectHandle();
private:
/**
The array of objects.
*/
	RPointerArray<CMMFObject> iObjects;

/**
The next available object handle.
*/
	TInt iNextObjectHandle;
	};


/**
@publishedAll

CMMFObject-derived class to wrap a Data Source.

Allows a handle to be attributed to a data source, so it can be removed from the controller and
the client can send messages directly to it.

@released
@since 7.0s
*/
class CMMFDataSourceHolder : public CMMFObject
	{
public:
/**
Constructor.

@param "aDataSource"	"The data source to be wrapped."
@since 7.0s
*/
	IMPORT_C CMMFDataSourceHolder(MDataSource& aDataSource);

/**
Destructor.

Note - this deletes the data source.
@since 7.0s
*/
	IMPORT_C ~CMMFDataSourceHolder();

/**
Returns a reference to the data source.

@return "The data source."
@since 7.0s
*/
	IMPORT_C MDataSource& DataSource();

	//from CMMFObject
/**
Implementation of the pure virtual function inherited from CMMFObject.

Passes the request directly to the data source.

@param "aMessage" "The message to be handled."
@since 7.0s
*/
	IMPORT_C void HandleRequest(TMMFMessage& aMessage);
private:
/*
Pointer to the data source owned by this object.
**/
	MDataSource* iDataSource;
	};

/**
@publishedAll

CMMFObject-derived class to wrap a Data Sink.

Allows a handle to be attributed to a data sink, so it can be removed from the controller and
the client can send messages directly to it.

@released
@since 7.0s
*/
class CMMFDataSinkHolder : public CMMFObject
	{
public:
/**
Constructor.

@param "aDataSink"	"The data sink to be wrapped."
@since 7.0s
*/
	IMPORT_C CMMFDataSinkHolder(MDataSink& aDataSink);

/**
Destructor.

Note - this deletes the data sink.
@since 7.0s
*/
	IMPORT_C ~CMMFDataSinkHolder();

/**
Returns a reference to the data sink.

@return "The data sink."
@since 7.0s
*/
	IMPORT_C MDataSink& DataSink();
	//from CMMFObject
/**
Implementation of the pure virtual function inherited from CMMFObject.

Passes the request directly to the data sink.

@param "aMessage" "The message to be handled."
@since 7.0s
*/
	IMPORT_C void HandleRequest(TMMFMessage& aMessage);

private:
/**
Pointer to the data sink owned by this object.
*/
	MDataSink* iDataSink;
	};


/**
@publishedAll

Base class for client-side custom command classes.

In order facilitate the use of the more common custom commands, it is desirable to write
a concrete API class for the client to use.  This API class can then be use to wrap all the code
involved to formulate the custom command messages.

@released
@since 7.0s
*/
class RMMFCustomCommandsBase
	{
public:
/**
Constructor.

@param	"aController"	"A reference to the controller client class that will be used to send
						custom commands to the controller plugin."
@param	"aInterfaceId"	"The uid of the custom command interface that is provided by this client
						API class."
@since 7.0s
*/
	IMPORT_C RMMFCustomCommandsBase(RMMFController& aController, TUid aInterfaceId);
protected:
/**
The controller.

Derived classes should use <code>iController.CustomCommandSync()<\code> and 
<code>iController.CustomCommandAsync()<\code> to send the custom commands to the controller
plugin.
*/
	RMMFController& iController;
/**
The destination package.

Derived classes must pass this into <code>iController.CustomCommandSync()<\code> and 
<code>iController.CustomCommandAsync()<\code> as the destination argument.
*/
	TMMFMessageDestinationPckg iDestinationPckg;
	};

/**
@publishedAll

Base class to define the interface of a custom command parser.

In order to facilitate the support of common custom commands by controller plugins, a
custom command parser object can be used.  A set of custom command parsers are created
by the controller plugin (one for each interface supported), and added to the custom command 
parser manager in the controller framework.  The controller plugin must also derive from a set of 
concrete interfaces (provided in the form of mixin classes). Then, a custom command supported by
one of the custom command parsers will appear to the controller as a concrete API call, rather than
a call to its own custom command API.

@released
@since 7.0s
*/
class CMMFCustomCommandParserBase : public CBase
	{
public:
/**
Pure virtual method to be implemented by derived classes.

Derived classes must implement the code to decode the message from the client.
@param "aMessage" "The message to be serviced. This message must be completed by the derived class."
@since 7.0s
*/
	virtual void HandleRequest(TMMFMessage& aMessage) = 0;

/**
Returns the uid of the custom command interface provided by this parser.

@return The interface UID.
@since 7.0s
*/
	IMPORT_C TUid InterfaceId();
/**
Destructor.

@since 7.0s
*/
	IMPORT_C ~CMMFCustomCommandParserBase();
protected:
/**
Constructor.

@param "aInterfaceId"	"The uid of the custom command interface provided by this parser.
						This must be the same as the interface id of the corresponding client
						API class. See RMMFCustomCommandsBase."
@since 7.0s
*/
	IMPORT_C CMMFCustomCommandParserBase(TUid aInterfaceId);
private:
/**
The uid of the custom command interface provided by this parser.
*/
	TUid iInterfaceId;
	};

/**
@publishedAll

Class to manage custom command parsers.

An object of this type is owned by the controller framework to contain all the custom command
parsers for the controller plugin.
@released
@since 7.0s
*/
class CMMFCustomCommandParserManager : public CBase
	{
public:
/**
Factory constructor.

@leave	""	"This method can leave with one of the standard system-wide error codes."
@return "A pointer to the newly created object."
@since 7.0s
*/
	static CMMFCustomCommandParserManager* NewL();

/**
Destructor.

Deletes all custom command parsers added to the manager.
@since 7.0s
*/
	~CMMFCustomCommandParserManager();

/**
Attempts to find a custom command parser capable of handling the message.

@param	"aMessage" "The message to be handled."
@return "ETrue if the message has been handled."
@return "EFalse if the message has not been handled."
@since 7.0s
*/
	TBool HandleRequest(TMMFMessage& aMessage);

/**
Adds a custom command parser to the manager.  The manager takes ownership of the parser.

@param "aParser" "A reference to the parser to be added to the manager."
@leave	"" "This method will leave if it fails to add the parser.  If it does leave, ownership
		of the parser will remain with the caller."
@since 7.0s
*/
	void AddCustomCommandParserL(CMMFCustomCommandParserBase& aParser);
private:
	CMMFCustomCommandParserManager();
private:
/**
The array of custom command parsers.
*/
	RPointerArray<CMMFCustomCommandParserBase> iParsers;
	};



/**
@publishedAll

Base class for controller plugins.

A controller plugin for the multimedia framework must derive from this class and implement
all the pure virtual functions.

@released
@since 7.0s
*/
class CMMFController : public CBase
	{
public:
/**
Uses ECOM to instantiate a new controller plugin.

@param "aControllerUid" "The unique ID of the controller to be instantiated from ECOM."
@param "aEventHandler"	"A reference to an event handling object that can be used by the 
						controller to send events back to the client."
@return "A pointer to the new controller plugin."
@leave	""	"This method can leave with any of the system-wide error codes."
@since	7.0s
*/
	static CMMFController* NewL(TUid aControllerUid, MAsyncEventHandler& aEventHandler);

/**
Handles a message from the client.

Decodes the message and calls one of the private DoXxx methods to unpackaged the parameters.

@param "aMessage" "The message to be handled."
@leave	""	"This method can leave with any of the system-wide error codes."
@since	7.0s
*/
	IMPORT_C virtual void HandleRequestL(TMMFMessage& aMessage);

	IMPORT_C virtual ~CMMFController();
protected:
	CMMFController(){};

	// virtual functions to be implemented by controller plugin

/**
Add a data source to the controller plugin.

NOTE: The data source is owned by the controller framework, NOT by the controller plugin.
Under no circumstances should the controller plugin delete the data source.
@param "aDataSource"	"A reference to the data source to be added.  The controller plugin 
						may call <code>aDataSource.DataSourceType()<\code> to find out
						exactly what type of source it is."
@leave	""	"The controller plugin may leave during this method.  If the controller plugin does
		not support the data source, it should leave with <code>KErrNotSupported<\code>.
@since 7.0s
*/
	virtual void AddDataSourceL(MDataSource& aDataSource) = 0;

/**
Add a data sink to the controller plugin.

NOTE: The data sink is owned by the controller framework, NOT by the controller plugin.
Under no circumstances should the controller plugin delete the data sink.
@param "aDatasink"		"A reference to the data sink to be added.  The controller plugin 
						may call <code>aDatasink.DatasinkType()<\code> to find out
						exactly what type of sink it is."
@leave	""	"The controller plugin may leave during this method.  If the controller plugin does
		not support the data sink, it should leave with <code>KErrNotSupported<\code>.
@since 7.0s
*/
	virtual void AddDataSinkL(MDataSink& aDataSink) = 0;

/**
Remove a data source from the controller plugin.

NOTE: The data source is owned by the controller framework, NOT by the controller plugin.
Under no circumstances should the controller plugin delete the data source.
@param "aDataSource"	"A reference to the data source to be removed.
@leave	""	"The controller plugin may leave during this method.  If the controller plugin does
		not support the removal of data sources, it should leave with 
		<code>KErrNotSupported<\code>.  If the controller plugin leaves, the data source will
		not be destroyed by the controller framework.  If it does not leave, the data source
		will be destroyed.
@since 7.0s
*/
	virtual void RemoveDataSourceL(MDataSource& aDataSource) = 0;

/**
Remove a data sink from the controller plugin.

NOTE: The data sink is owned by the controller framework, NOT by the controller plugin.
Under no circumstances should the controller plugin delete the data sink.
@param "aDatasink"	"A reference to the data sink to be removed.
@leave	""	"The controller plugin may leave during this method.  If the controller plugin does
		not support the removal of data sinks, it should leave with 
		<code>KErrNotSupported<\code>.  If the controller plugin leaves, the data sink will
		not be destroyed by the controller framework.  If it does not leave, the data sink
		will be destroyed.
@since 7.0s
*/
	virtual void RemoveDataSinkL(MDataSink& aDataSink) = 0;

/**
Reset the controller plugin.

The controller should revert back to its newly constructed state. If the Reset is successful
(i.e. it doesn't leave), the controller framework will delete all objects added to the
MMFObjectManager including any sources and sinks.
@leave	""	"The controller plugin may leave during this method.  If the controller plugin does
		not support being reset, it should leave with <code>KErrNotSupported<\code>.
@since 7.0s
*/
	virtual void ResetL() = 0;

/**
Prime the controller plugin.

The controller must prepare to start playing, by initialising its sources, sinks and buffers. 
This moves the controller from the STOPPED to the PRIMED state.
@leave	""	"The controller plugin may leave during this method with any of the standard
		system-wide error codes."
@since 7.0s
*/
	virtual void PrimeL() = 0;

/**
A partner to the PrimeL() method that is overridable to allow Asynchronous
completion in the controller whilst maintaining a Synchronous client API.

The default implementation of this is to call PrimeL() and complete the message with KErrNone.


@leave	""	"The controller plugin may leave during this method with any of the standard
		system-wide error codes."
@since 7.0s
*/

	IMPORT_C virtual void PrimeL(TMMFMessage& aMessage);


/**
Commence playback.

The controller must now begin transferring data from its source(s) to its sink(s).
This moves the controller from the PRIMED to the PLAYING state.

Note: this method must return once playing has commenced, and not wait until playing is complete.
@leave	""	"The controller plugin may leave during this method with any of the standard
		system-wide error codes."
@since 7.0s
*/
	virtual void PlayL()= 0;

/**
A partner to the PlayL() method that is overridable to allow Asynchronous
completion in the controller whilst maintaining a Synchronous client API.

The default implementation of this is to call PlayL() and complete the message with KErrNone.


@leave	""	"The controller plugin may leave during this method with any of the standard
		system-wide error codes."
@since 7.0s
*/

	IMPORT_C virtual void PlayL(TMMFMessage& aMessage);


/**
Pause the controller plugin.


The controller must now cease transferring data from its source(s) to its sink(s).
This moves the controller from the PLAYING back to the PRIMED state.

A subsequent call to <code>Play()<\code> will cause the controller plugin to resume playback
from the point it was paused (unless there has been a call to <code>SetPosition()<\code> in
the meantime.

@leave	""	"The controller plugin may leave during this method with any of the standard
		system-wide error codes."
@since 7.0s
*/
	virtual void PauseL()= 0;


/**
A partner to the PauseL() method that is overridable to allow Asynchronous
completion in the controller whilst maintaining a Synchronous client API.

The default implementation of this is to call PauseL() and complete the message with KErrNone.


@leave	""	"The controller plugin may leave during this method with any of the standard
		system-wide error codes."
@since 7.0s
*/

	IMPORT_C virtual void PauseL(TMMFMessage& aMessage);


	
/**
Stop the controller plugin.

The controller must now undo anything that occurred during the call to <code>Prime()<\code>.
This moves the controller from the PRIMED back to the STOPPED state.

@leave	""	"The controller plugin may leave during this method with any of the standard
		system-wide error codes."
@since 7.0s
*/
	virtual void StopL()= 0;

/**
A partner to the StopL() method that is overridable to allow Asynchronous
completion in the controller whilst maintaining a Synchronous client API.

The default implementation of this is to call StopL() and complete the message with KErrNone.


@leave	""	"The controller plugin may leave during this method with any of the standard
		system-wide error codes."
@since 7.0s
*/

	IMPORT_C virtual void StopL(TMMFMessage& aMessage);



/**
Get the current position.

The controller plugin should calculate the current position in microseconds.

@return	"The current position in microseconds."
@leave	""	"The controller plugin may leave during this method with any of the standard
		system-wide error codes."
@since 7.0s
*/
	virtual TTimeIntervalMicroSeconds PositionL() const = 0;

/**
Set the current position.

The controller plugin should reposition itself to the position provided.

@param	"The desired position in microseconds."
@leave	""	"The controller plugin may leave during this method with any of the standard
		system-wide error codes."
@since 7.0s
*/
	virtual void SetPositionL(const TTimeIntervalMicroSeconds& aPosition) = 0;

/**
Get the duration of the clip.

The controller plugin should calculate the clip duration in microseconds.

@return	"The clip duration in microseconds."
@leave	""	"The controller plugin may leave during this method with any of the standard
		system-wide error codes."
@since 7.0s
*/
	virtual TTimeIntervalMicroSeconds DurationL() const = 0;

/**
Set the priority settings.

The new priority settings must be applied to any resource being used by the controller
plugin that requires priority settings (for example the sound device).

@param	"aPrioritySettings" "The new priority settings"
@since 7.0s
*/
	virtual void SetPrioritySettings(const TMMFPrioritySettings& aPrioritySettings) = 0;

/**
Handle a custom command.

Custom commands allow a controller plugin to define its own API.  If the controller framework
does not understand a message from the client, it is assumed this is a custom command for the 
plugin and passed into this interface.

The more common custom commands can be handled by Custom Command Parsers on behalf of the 
controller plugin.  This allows the controller plugin to implement a concrete interface
(defined by mixin classes) rather than having to decode the command itself.  For more 
information, @see CMMFCustomCommandParserBase.

The controller plugin must always complete the message passed into this method, 
even if it does not support the interface required by the message.

@param "aMessage" "The message to be handled by the controller plugin."
@since 7.0s
*/
	virtual void CustomCommand(TMMFMessage& aMessage)
		{aMessage.Complete(KErrNotSupported);};//default implementation

/**
Retrieve the number of meta data entries in the clip.

@param "aNumberOfEntries"	"The controller plugin must set this to the number of meta data entries
							in the clip."
@leave	""	"The controller plugin may leave during this method with any of the standard
		system-wide error codes."
@since 7.0s
*/
	virtual void GetNumberOfMetaDataEntriesL(TInt& aNumberOfEntries) = 0;

/**
Retrieve a meta data entry from the clip.

@param	"aIndex"	"The index of the meta data entry to retrieve."
@return "A pointer to a newly created CMMFMetaDataEntry object containing the meta information.
		The controller framework will take ownership of the object when this method returns."
@leave	""	"The controller plugin may leave during this method with any of the standard
		system-wide error codes."
@since 7.0s
*/
	virtual CMMFMetaDataEntry* GetMetaDataEntryL(TInt aIndex) = 0;


	// Utility functions to be used by controller plugins

/**
Send an event to the client.

The controller plugin can use this method to send an event to the client.

@param	"aEvent"	"The event to be sent to the client."
@return "One of the system-wide error codes."
@since 7.0s
*/
	IMPORT_C TInt DoSendEventToClient(const TMMFEvent& aEvent);

/**
Get a reference to the Mmf object container.

The controller plugin may add CMMFObject-derived objects to the container to allow them
to receive messages directly from the client.

@return "A reference to the MMFObjectContainer."
@leave	""	"This method can leave with one of the standard system-wide error codes."
@since 7.0s
*/
	IMPORT_C CMMFObjectContainer& MMFObjectContainerL();

/**
Add a custom command parser to the controller framework.

If the controller framework receives a request it does not understand, it will 
search through its list of custom command parsers before passing the request
on to the controller plugin as a custom command.

By using the custom command parsers, the controller plugin can implement a concrete
API rather than having to decode the common custom commands itself.

@param	"aParser"	"The parser to be added to the controller framework. The controller framework
					takes ownership of the parser if the call does not leave".
@leave	""	"This method can leave with one of the standard system-wide error codes."
@since 7.0s
*/
	IMPORT_C void AddCustomCommandParserL(CMMFCustomCommandParserBase& aParser);
	
private:
	void ConstructL(MAsyncEventHandler& aEventHandler);
	// IPC decode functions
	TBool DoAddDataSourceL(TMMFMessage& aMessage);
	TBool DoAddDataSinkL(TMMFMessage& aMessage);
	TBool DoRemoveDataSourceL(TMMFMessage& aMessage);
	TBool DoRemoveDataSinkL(TMMFMessage& aMessage);
	TBool DoResetL(TMMFMessage& aMessage);
	TBool DoPrimeL(TMMFMessage& aMessage);
	TBool DoPlayL(TMMFMessage& aMessage);
	TBool DoPauseL(TMMFMessage& aMessage);
	TBool DoStopL(TMMFMessage& aMessage);
	TBool DoGetPositionL(TMMFMessage& aMessage);
	TBool DoSetPositionL(TMMFMessage& aMessage);
	TBool DoGetDurationL(TMMFMessage& aMessage);
	TBool DoSetPrioritySettingsL(TMMFMessage& aMessage);
	void DoCustomCommand(TMMFMessage& aMessage);
	TBool DoGetNumberOfMetaDataEntriesL(TMMFMessage& aMessage);
	TBool DoGetSizeOfMetaDataEntryL(TMMFMessage& aMessage);
	TBool DoGetMetaDataEntryL(TMMFMessage& aMessage);
private:
/**
Buffer to assist copy of meta data over the thread boundary.
*/
	CBufFlat* iMetaDataBuffer;

/**
Required by ECOM.
*/
	TUid iDtor_ID_Key;

/**
The event handler for the controller plugin.
*/
	MAsyncEventHandler* iAsyncEventHandler;

/**
The MMF object container.
*/
	CMMFObjectContainer* iMMFObjectContainer;

/**
The custom command parser manager.
*/
	CMMFCustomCommandParserManager* iCustomCommandParserManager;
	};



/**
@publishedAll

Mixin class that the user of the class CMMFControllerEventMonitor must derive from.
@released
@since 7.0s
*/
class MMMFControllerEventMonitorObserver
	{
public: 
/**
Handle an event that has been generated.

@param "aEvent"	"The event to be handled."
@since 7.0s
*/
	virtual void HandleEvent(const TMMFEvent& aEvent) = 0;
	};

/**
@publishedAll

Active object utility class that can be used to monitor a controller plugin for events.
If an event occurs, the client will be notified via the MMMFControllerEventMonitorObserver interface.
@released
@since 7.0s
*/
class CMMFControllerEventMonitor : public CActive
	{
public:
/**
Constructs a controller event monitor object.

@param "aObserver"		"A reference to the observer of the active object.  The observer will be
						notified when an event occurs."
@param "aMMFController"	"A reference to the client controller interface class."
@return	"A pointer to the new event monitor."
@leave	""	"This method can leave with one of the standard system-wide error codes."
@since 7.0s
*/
	IMPORT_C static CMMFControllerEventMonitor* NewL(MMMFControllerEventMonitorObserver& aObserver, 
		RMMFController& aMMFController);
/**
Destructor.
*/
	~CMMFControllerEventMonitor();
/**
Tells the controller event monitor to start listening for events.

The controller plugin must have been opened before this method is called.

@since 7.0s
*/
	IMPORT_C void Start();

private:
/**
Calls <code>HandleEvent<\code> on iObserver.
@leave "" "This will not leave."
@since 7.0s
*/
	void RunL();

/**
Cancels the outstanding request on iMMFController.
@since 7.0s
*/
	void DoCancel();

/**
Constructs a controller event monitor object.

@param "aObserver"		"A reference to the observer of the active object.  The observer will be
						notified when an event occurs."
@param "aMMFController"	"A reference to the client controller interface class."
@since 7.0s
*/
	CMMFControllerEventMonitor(MMMFControllerEventMonitorObserver& aObserver, 
		RMMFController& aMMFController);
private:
	MMMFControllerEventMonitorObserver& iObserver;
	RMMFController& iMMFController;
	TMMFEventPckg iEventPckg;
	};

#endif
