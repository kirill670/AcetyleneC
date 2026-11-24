// W32CLICK.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

// Definition of class that needs to be provided by a Key Click plugin
//

#ifndef __W32CLICK_H__
#define __W32CLICK_H__

#ifndef __E32STD_H__
#include <e32std.h>
#endif
#ifndef __E32BASE_H__
#include <e32base.h>
#endif
#ifndef __W32STD_H__
#include <w32std.h>
#endif


// A pointer to a TClickMakerData object is passed to CClickMaker's OtherEvent function for
// EEventScreenDeviceChanged events.

struct TClickMakerData
/**
@publishedAll 

*/
	{
	TInt screenDeviceMode;
	};


class CClickMaker: public CBase
/** Key or pointer click plug-in provider interface.

This class should be implemented by a plug-in DLL in order to produce a sound 
when a key is pressed, a key auto repeats or when the screen is tapped with 
a pointer. When any of these events occur, the window server informs the plug-in 
DLL, which can then make the sound.

The details of the event are also passed to the plug-in so that the sound 
can be tailored to the precise event, e.g. clicking on different keys on the 
keypad or on different parts of the screen could make different sounds.

The name of the initial plug-in to use can be specified in the wsini.ini configuration 
file using the KEYCLICKPLUGIN or KEYCLICKPLUGINFIXED keywords. When the operating 
system boots, wsini.ini is read for the name of this plug-in. If a plug-in 
name exists, the window server will try to load it. At a later time, any client 
of the window server can request a new plug-in to be loaded or the current 
one to be unloaded, using the RSoundPlugIn class.

The plug-in is a polymorphic DLL which implements the CClickMaker interface. 
Its first UID is KDynamicLibraryUidValue and its second UID is 0x10004F63. 
Its first exported function should create an object of the CClickMaker sub-class 
and should have the following signature:

EXPORT_C CClickMaker* CreateClickMakerL() 

@publishedAll 

@see RSoundPlugIn */
	{
public:
	/** This function is called by the window server whenever there is a key event, 
	to generate the sound.
	
	It must be implemented by the key or pointer click plug-in.
	
	If the sound cannot be made, the function should continue without leaving.
	
	@param aType The type of key event: EEventKey, EEventKeyUp, EEventKeyDown 
	or EEventKeyRepeat.
	@param aEvent The key event details. */
	virtual void KeyEvent(TEventCode aType,const TKeyEvent& aEvent)=0;
	/** This function is called by the window server whenever there is a pointer event, 
	to generate the sound.
	
	It must be implemented by the key or pointer click plug-in.
	
	If the sound cannot be made, the function should continue without leaving.
	
	The iParentPosition data member of aEvent is not the position of the pointer 
	event relative to origin of the parent window. Instead it is the position 
	on the screen. This is because the parent window has no meaning inside the 
	plug-in like it does to the window server client and furthermore, knowledge 
	of the screen position may be useful to the plug-in.
	
	@param aEvent The pointer event details. */
	virtual void PointerEvent(const TPointerEvent& aEvent)=0;
	/** This function is intended for future expansion of the interface, in case it 
	needs to support sounds for other types of event.
	
	It is not currently called by the window server.
	
	@param aType Not used.
	@param aParam Not used. */
	virtual void OtherEvent(TInt aType,TAny* aParam=NULL)=0;
	/** This function may be implemented by the key or pointer click plug-in to enable 
	the plug-in to communicate with the window server client.
	
	If this is not required, the implementation may simply return zero.
	
	It is called by RSoundPlugIn::CommandReply() which returns the value returned 
	by this function.
	
	The return value can be generated either by returning it from the function 
	or by leaving with the value. In either case, the client will get back the 
	value concerned.
	
	@param aOpcode Opcode understood by both the window server client and the 
	plug-in DLL.
	@param aArgs Arguments packaged by the window server client.
	@return A value passed back to the client. This may be KErrNone or another 
	of the system-wide error codes. */
	virtual TInt CommandReplyL(TInt aOpcode, TAny *aArgs)=0;
	};

#endif
