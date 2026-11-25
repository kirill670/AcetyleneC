// W32STD.H
//
// Copyright (c) 1994-2001 Symbian Ltd.  All rights reserved.
//

// Standard window server header file
//

#ifndef __W32STD_H__
#define __W32STD_H__

#ifndef __FNTSTORE_H__
#include <fntstore.h>
#endif
#ifndef __BITDEV_H__
#include <bitdev.h>
#endif
#ifndef __BITSTD_H__
#include <bitstd.h>
#endif


_LIT(KWSERVThreadName,"Wserv");

class RWindowBase;
class RWindow;
class RWsBuffer;


/**
 *
 * Screen mode enforcement flags.
 *
 * Screen mode enforcement ensures that windows must meet certain requirements if they are to be displayed. When the screen mode changes,
 * window groups that are incorrectly set up, according to these requirements, are locked out. The windows are notified of the change,
 * and will be displayed if they are updated (according to the current enforcement requirement) to match the new screen mode.
 *
 */
enum TScreenModeEnforcement
	{
/**
 *
 * No enforcement.
 * All windows that are the children of window groups will be displayed - irrespective of the screen mode.
 * This is not properly supported and is provided for testing purposes.
 *
 */
	ESizeEnforcementNone,
/**
 *
 * Pixels and rotation enforcement.
 * Group windows must be set up for the correct rotation and be working in the correct size in pixels to be displayed.
 *
 */
	ESizeEnforcementPixelsAndRotation,
/**
 *
 * Pixels and Twips enforcement.
 * Group windows must have the correct rotation and be working in the correct size in pixels and twips to be displayed.
 * This setting might be used if the display pixels are not square, and would distort fonts when rotated.
 *
 */
	ESizeEnforcementPixelsTwipsAndRotation,
	};

struct TPixelsAndRotation
	{
	TSize iPixelSize;
	CFbsBitGc::TGraphicsOrientation iRotation;
	};

struct TPixelsTwipsAndRotation
	{
	TSize iPixelSize;
	TSize iTwipsSize;
	CFbsBitGc::TGraphicsOrientation iRotation;
	};

enum {
/** The length of the log message text buffer in characters. Currently this is 128.
 */
	KLogMessageLength=0x80
	};

/**
 *
 * Log message text.
 *
 * This defines the length of the log text message buffer which is used in <code>RWsSession::LogMessage()</code>.
 * Note: In version 6.0 the maximum message length is 128.
 *
 * @since 5.0
 * @lib ""
 */
typedef TBuf<KLogMessageLength> TLogMessageText;

/**
 *
 * Password window group priority.
 *
 * This priority is assigned to the password window group when the window server is displaying the password window. 
 * This is the highest priority, which ensures that machine password window is in front of all other windows - 
 * hence password tests cannot be bypassed.
 *
 */
enum
	{
/** Password window group priority.
 */
	KPasswordWindowGroupPriority=1000
	};

enum {
/** Switch ordinal position to owning window.
 */
	KOrdinalPositionSwitchToOwningWindow=0x80000000
	};

/**
 *
 * Window corner types.
 *
 * Corners may be specified square or stepped, with varying numbers of pixels removed to make the stepping. Picturing a corner as
 * the top left corner of a window, the numbers denote the number of pixels removed from the top row to give corners.
 *
 */
enum TCornerType
// Bottom 16 bits available for corner type
	{
/** Square corner.
 */
	EWindowCornerSquare,
/** Corner pixel removed.
 */
	EWindowCorner1,
/**
 *
 * Two pixel step.
 * 3 pixels are removed - the corner pixel and a single pixel from each side.
 *
 */
	EWindowCorner2,
/**
 *
 * Three pixel step.
 * 5 pixels are removed - the corner pixel, the two pixels next to it and the 2 pixels above or below it.
 *
 */
	EWindowCorner3,
/**
 *
 * Five pixel step.
 * 12 pixels are removed - the corner pixel, the four pixels next to it, the four pixels above or below it,
 * the pixel which was diagonal to the corner pixel, and the pixels to both sides of that pixel.
 *
 */
	EWindowCorner5,
	EWindowCornerRegion,		// Private
/**
 *
 * Corner type mask.
 * This value is used by the window server, and may be used by developers, to separate <code>TCornerType</code>
 * and <code>TCornerFlags</code> values from a <code>TInt</code> whichcontains both types.
 *
 */
	ECornerTypeMask=0xFFFF
	};
/**
 *
 * Corner flags.
 *
 * These are used by <code>RWindowBase::SetCornerType()</code> to set which corners of a window
 * are not to have corner types applied to them.
 *
 */
enum TCornerFlags
// Top 16 bits available for corner flags
	{
/** Do not apply corner shape to top left corner.
 */
	EWindowCornerNotTL=0x10000,
/** Do not apply corner shape to top right corner.
 */
	EWindowCornerNotTR=0x20000,
/** Do not apply corner shape to bottom left corner.
 */
	EWindowCornerNotBL=0x40000,
/** Do not apply corner shape to bottom right corner.
 */
	EWindowCornerNotBR=0x80000,
	};

enum TWindowBackupType
	{
	EWindowBackupAreaBehind=0x0001,
	EWindowBackupFullScreen=0x0002,
	};

/**
 *
 * Types of standard events.
 *
 * These are events that the window server passes to its clients - as opposed to events that the base passes to the window server.
 *
 */
enum TEventCode
	{
/**
 *
 * Null event.
 * This can be sent, but should be ignored by clients.
 *
 */
	EEventNull,
/**
 *
 * Key event.
 * This is the event that is sent when a character has been received from the keyboard.
 * When the user presses a key (other than the modifier keys), an <code>EEventKeyDown</code> event, and <code>EEventKey</code> event,
 * and an <code>EEventKeyUp</code> event are generated in that order.
 *
 */
	EEventKey,
/**
 *
 * Key up event.
 * When the user presses a key (other than the modifier keys), an <code>EEventKeyDown</code> event, and <code>EEventKey</code> event,
 * and an <code>EEventKeyUp</code> event are generated in that order.
 *
 */
	EEventKeyUp,
/**
 *
 * Key down event. When the user presses a key (other than the modifier keys), an <code>EEventKeyDown</code> event,
 * and <code>EEventKey</code> event, and an <code>EEventKeyUp</code> event are generated in that order.
 *
 */
	EEventKeyDown,
/**
 *
 * Modifier changed event. This is an event generated by the window server when the state of one of the modifier keys changes.
 * This event type is not reported unless explicitly requested by a window.
 * See <code>RWindowTreeNode::EnableModifierChangedEvents()</code>.
 *
 */
	EEventModifiersChanged,
/**
 *
 * Pointer event.
 * This event is sent when the user presses or releases a pointer button
 * (or the equivalent action, depending on the type of pointing device), drags the pointer, or uses the pointer to switch on the device.
 * If the current input type (see <code>TXYInputType</code>) is "mouse" or "relative mouse" -
 * i.e. it generates pointer move events as well as drag events - then this event type is also generated whenever the pointer is moved.
 *
 */
	EEventPointer,			//5
/**
 *
 * Pointer enter event.
 * This occurs when the user moves the pointer into a window with a pointer button pressed (or equivalent action depending on the type of
 * pointing device). If move events are being generated,this event also occurs when the user moves the pointer into the window.
 *
 */
	EEventPointerEnter,
/**
 *
 * Pointer exit event.
 * Occurs when the user moves the pointer out of a window with a pointer button pressed (or equivalent action depending on the type of
 * pointing device). If move events are being generated, this event also occurs when the user moves the pointer out of the window.
 *
 */
	EEventPointerExit,
/**
 *
 * Pointer move buffer ready event.
 * Occurs when the pointer move buffer is ready to be retrieved by the client.
 *
 */
	EEventPointerBufferReady,
/**
 *
 * Occurs as a duplicate of each pointer event if a window sets pointer capture with the <code>TCaptureFlagDragDrop</code> flag set.
 *
 */
	EEventDragDrop,
/**
 *
 * Drag drop event.
 * Occurs when a window group loses keyboard focus.
 *
 */
	EEventFocusLost,		//10
/**
 *
 * Focus gained event.
 * Occurs when a window group gains keyboard focus.
 *
 */
	EEventFocusGained,
/**
 *
 * On event.
 * This event type is not reported unless explicitly requested by a window. See <code>RWindowTreeNode::EnableOnEvents()</code>.
 *
 */
	EEventSwitchOn,
/**
 *
 * Password event.
 * Occurs when the window server enters password mode. It is sent to the group window of the currently active password window.
 * This is the window server mode where the user is required to enter a password before any further actions can be performed.
 *
 */
	EEventPassword,
/**
 *
 * Window group changed event. This occurs whenever a window group is destroyed, and whenever a window group's name changes
 * This event type is not reported unless explicitly requested by a window. See <code>RWindowTreeNode::EnableGroupChangeEvents()</code>.
 *
 */
	EEventWindowGroupsChanged,
/**
 *
 * Error event.
 * Occurs when an error occurs. See <code>TWsErrorMessage::TErrorCategory</code> for the types of errors.
 * This event type is not reported unless explicitly requested by a window. See <code>RWindowTreeNode::EnableErrorMessages()</code>.
 *
 */
	EEventErrorMessage,		//15
/**
 *
 * Message ready event.
 * Occurs when a session sends a message to this window group using <code>RWsSession::SendMessageToWindowGroup()</code>.
 *
 */
	EEventMessageReady,
	EEventMarkInvalid,	// For internal use only
/**
 *
 * Off event.
 * This is issued when an off event is received by the window server from the base.
 * If for some reason the event can't be delivered, or there is no-one to deliver them to,
 * then a call to the base is made to power down the processor.
 * This event is only delivered if explicitly requested using <code>RWsSession:RequestOffEvent()</code>.
 *
 */
	EEventSwitchOff,
/**
 *
 * Off event issued to off-event requesting windows when the off key is pressed.
 * This replaces <code>EEventShellSwitchOff</code> which was used prior to version 6.0.
 *
 */
	EEventKeySwitchOff,
/**
 *
 * Screen size mode change event.
 * This is issued, for example, if the screen size mode has changed, e.g. opening the flip on the Ericsson R380 smartphone.
 *
 */
	EEventScreenDeviceChanged, //20
/**
 *
 * Event set whenever the focus window group changes. Requested by <code>RWindowTreeNode::EnableFocusChangeEvents()</code>
 *
 */
	EEventFocusGroupChanged,
/**
 *
 * Case opened event.
 * These events will be sent to those windows that have requested <code>EEventSwitchOn</code> events.
 * Unlike with <code>EEventSwitchOn</code> events, the screen will not be switched on first.
 *
 */
	EEventCaseOpened,
/**
 *
 * Case closed events.
 * These events will be sent to those windows that have requested <code>EEventSwitchOff</code> events.
 * Unlike <code>EEventSwitchOff</code> events, which make a call to the base to power down the processor if for some reason the event
 * can't be delivered (or there is no-one to deliver them to), failure to deliver case closed events has no repercussions.
 *
 */
	EEventCaseClosed,
	//Codes for events only passed into Key Click DLL's
	EEventKeyRepeat=100,
	//Event codes from EEventUser upwards may be used for non-wserv events.
	//No event codes below this should be defined except by the window server
/**
 *
 * User defined event. See <code>RWs::SendEventToWindowGroup()</code>
 * The client is allowed to use this and all higher values to define their own events.
 * These events can be sent between windows of the same client or windows of different clients.
 *
 */
	EEventUser=1000,
	};

/** Window server hot keys.
 */
enum THotKey
	{
/**
 *
 * Enables logging of all messages to and from the window server.
 * Note that this requires that the type of logging has been set up in the wsini.ini file,
 * and that the appropriate logging DLL is available.
 * Default key mapping: <Ctrl><Alt><Shift>E
 *
 */
	EHotKeyEnableLogging,
/**
 *
 * Disables logging if active, does nothing otherwise.
 * Note that logging requires that the type of logging has been set up in the wsini.ini file,
 * and that the appropriate logging DLL is available.
 * Default key mapping: <Ctrl><Alt><Shift>D
 *
 */
	EHotKeyDisableLogging,
/**
 *
 * Dumps a list of all windows to the log. (If logging is disabled, it is temporarily enabled in order to do this.)
 * Default key mapping: <Ctrl><Alt><Shift>W
 *
 */
	EHotKeyStateDump,
/**
 *
 * Kills the foreground application.
 * Default key mapping: <Ctrl><Alt><Shift>K
 *
 */
	EHotKeyOfDeath,
/**
 *
 * Shuts down the window server.
 * Be cautious! This may mean resetting the machine to re-start the window server.
 * Default key mapping: release (not set), debug (<Ctrl><Alt><Shift>X).
 *
 */
	EHotKeyShutDown,
/**
 *
 * Dumps a list of cells allocated on the window server's heap to the log.
 * (If logging is disabled, it is temporarily enabled in order to do this.)
 * Note that logging requires that the type of logging has been set up in the wsini.ini file,
 * and that the appropriate logging DLL is available.
 * Default key mapping: <Ctrl><Alt><Shift>H
 *
 */
	EHotKeyHeapDump,
/**
 *
 * Increases the LCD contrast.
 * Default key mapping: <code>EKeyIncContrast</code>. Note that this value is from an enum in e32keys.h.
 *
 */
	EHotKeyIncContrast,
	EHotKeyDecContrast,
/**
 *
 * Switches the machine off.
 * Default key mapping:<code>EKeyOff</code>. Note that this value is from an enum in e32keys.h.
 *
 */
	EHotKeyOff,
/**
 *
 * Switches the backlight on.
 * Default key mapping: <code>EKeyBacklightOn</code>. Note that this value is from an enum in e32keys.h.
 *
 */
	EHotKeyBacklightOn,
/**
 *
 * Switches the backlight off.
 * Default key mapping: <code>EKeyBacklightOff</code>. Note that this value is from an enum in e32keys.h.
 *
 */
	EHotKeyBacklightOff,
/**
 *
 * Toggles the backlight.
 * Default key mapping: <code>EKeyBacklightToggle</code>. Note that this value is from an enum in e32keys.h.
 *
 */
	EHotKeyBacklightToggle,
/**
 *
 * Switch to screen size 0.
 * This, and the following 3 keys are used to switch screen sizes on the real hardware.
 * For example, on the Ericsson R380 smartphone this is generated every time the flip is closed.
 *
 */
	EHotKeyScreenDimension0,
/**
 *
 * Switch to screen size 1.
 * On the Ericsson R380 smartphone this is generated every time the flip is opened.
 *
 */
	EHotKeyScreenDimension1,
/** Switch to screen size 2.
 */
	EHotKeyScreenDimension2,
/** Switch to screen size 3.
 */
	EHotKeyScreenDimension3,
/**
 *
 * Cycles the display though its possible sizes. This is used only while debugging.
 * A device may have several screen sizes, each with a default orientation.
 * For example the Ericsson R380 has different display sizes when the flip lid is opened and closed.
 * Default key mapping: debug : <Ctrl><Alt><Shift> U. Release : none.
 *
 */
	EHotKeyCycleDisplaySize,		//Used for debug purposes only
/**
 *
 * Cycle the screen orientation through the specified rotations for the particular size mode you are in.
 * The Ericsson R380 smartphone uses this feature for flipping between right and left handed use.
 * For rectangular display modes you can only specify 2 orientations, 180 degrees apart.
 * For square modes you can specify 4 rotations (90 degrees) or however many you want.
 * Specification of the list of rotations takes place in the WSINI.INI file.
 * Default key mapping: debug : <Ctrl><Alt><Shift> O. Release : none.
 *
 */
	EHotKeyCycleOrientation,
	EHotKeyIncBrightness,
/**
 *
 * Decreases the LCD contrast.
 * Default key mapping: <code>EKeyDecContrast</code>. Note that this value is from an enum in e32keys.h.
 *
 */
	EHotKeyDecBrightness,
/**
 *
 * Value for first hot key.
 * Used with <code>EHotKeyLastKeyType</code> to make it easy to write a
 * <code>for</code> loop that steps through all the different key values.
 *
 */
	EHotKeyFirstKeyType=EHotKeyEnableLogging,		//Must always be set to the first one
/**
 *
 * Value for last hot key.
 * Used with <code>EHotKeyFirstKeyType</code> to make it easy to write a
 * <code>for</code> loop that steps through all the different key values.
 *
 */
	EHotKeyLastKeyType=EHotKeyDecBrightness,		//Must always be set to the last one
	};

/**
 *
 * Password mode flags.
 *
 */
enum TPasswordMode
	{
/**
 *
 * Release ownership of password handling.
 * This allows another window to become the password window.
 * A client will be panicked with code 46 if it sets this mode when it is not the current password window.
 *
 */
	EPasswordCancel,

/** No password handling performed by this window, but prevents any other window becoming the password window.
 */
	EPasswordNone,
/**
 *
 * Password mode enabled only once a day.
 * The password mode is a window server mode where the user is required to enter a password before any further actions can be performed.
 * Note:
 * Currently new days start at 4 am.
 *
 */
	EPasswordOnceADay,

/** Password mode enabled every time the machine is switched on.
 */
	EPasswordAlways,

/** Equivalent to setting the password mode to <code>EPasswordAlways</code> and triggering an instant password check.
 */
	EPasswordAlwaysTriggerNow,

/** Equivalent to setting the password mode to <code>EPasswordOnceADay</code> and triggering an instant password check.
 */
	EPasswordOnceADayTriggerNow,
	};

struct TTextCursor
    {
	enum EType
		{
		ETypeNone,		// Do not use in app interface, private for window server use only
		ETypeRectangle,
		ETypeHollowRectangle,
		ETypeFirst=ETypeRectangle,			//Must be the first available cursor type
		ETypeLast=ETypeHollowRectangle,		//Must be the last available cursor type
		};
	enum EFlags
		{
		EFlagNoFlash=0x1,
//private flags
		EUserFlags=0x0000FFFF,
		EFlagClipped=0x10000,
		EPrivateFlags=0xFFFF0000,
		};
	EType iType;
    TInt iHeight;
    TInt iAscent;
    TInt iWidth;
    TUint iFlags;
	TRgb iColor;
    };

enum TSpriteFlags
	{
	ESpriteFlash=0x1,
	ESpriteNoChildClip=0x2,
	ESpriteNoShadows=0x4,
// Private flags, do not use
	ESpriteNonSystemFlags=0x0000FFFF,
	ESpriteSystemFlags=	  0xFFFF0000,
	ESpritePointer=0x10000,
	ESpriteOOM=0x20000,
	ESpriteDisabled=0x40000,
	ESpriteActive=0x80000,
	};
struct TSpriteMember
	{
	CFbsBitmap *iBitmap;		// If NULL, there is no sprite for the time specified
	CFbsBitmap *iMaskBitmap;
	TBool iInvertMask;
	CGraphicsContext::TDrawMode iDrawMode;	// Only applies if mask is NULL
	TPoint iOffset;				// Offset from sprites central position
	TTimeIntervalMicroSeconds32 iInterval;
	};

/**
 *
 * Event reporting control.
 *
 * This enumeration defines flags which can be used to control how events are reported.
 *
 */
enum TEventControl
	{
/** Requested events are sent in all circumstances.
 */
	EEventControlAlways,
/** Events are delivered only when the requesting window's window group has keyboard focus.
 */
	EEventControlOnlyWithKeyboardFocus,
/** Events are delivered only when the requesting window or any of its children are visible on the screen.
 */
	EEventControlOnlyWhenVisible
	};

/**
 *
 * Pointer event filter types.
 *
 * These flags are used by <code>RWindowBase::PointerFilter()</code> to define which pointer events are filtered out by the window server
 * and not sent to the client session. They also allow the window server to simulate a move event prior to each pen down event.
 *
 */
enum TPointerFilter
	{
	//Basic Types
/** Filter out both pointer enter and pointer exit events for this window.
 */
	EPointerFilterEnterExit=0x1,
/** Filter out pointer-move events for this window.
 */
	EPointerFilterMove=0x2,
/** Filter out pointer-drag events for this window.
 */
	EPointerFilterDrag=0x4,
/**
 *
 * Simulates a pointer move event before each pen down event.
 * This makes the pen appear more like a mouse - with simulated movement between two pointer events.
 * You can only get these events while you are in penmode.
 *
 */
	EPointerGenerateSimulatedMove=0x8,
	//Combinations of the above
/**
 *
 * Filter Move and Drag-pointer events from the event stream and simulate the move event before each pen down event.
 * This enum is useful when you want to get <code>SimulateMoveEvents</code>. Use it as shown below to turn on simulated moves:
 * win->PointerFilter(EPointerMoveEvents, EPointerGenerateSimulateMoves)
 *
 */
	EPointerMoveEvents=EPointerFilterMove|EPointerGenerateSimulatedMove,
	};

struct TPointerEvent
	{
	/*
	 *
	 * *Pointer event types.
	 *
	 * Note that the user actions that cause these events will vary according to the type of pointing device used.
	 */
	enum TType
		{
	/*
	 *
	 * *Button 1 or pen down.
	 */
		EButton1Down,
	/*
	 *
	 * *Button 1 or pen up.
	 */
		EButton1Up,
	/*
	 *
	 * *Button 2 down.
	 * This is the middle button of a 3 button mouse.
	 */
		EButton2Down,
	/*
	 *
	 * *Button 2 up.
	 * This is the middle button of a 3 button mouse.
	 */
		EButton2Up,
	/*
	 *
	 * *Button 3 down.
 	 */
		EButton3Down,
	/*
	 *
	 * *Button 3 up.
	 */
		EButton3Up,
	/*
	 *
	 * *Drag event.
	 * These events are only received when button 1 is down.
 	 */
		EDrag,
	/*
	 *
	 * *Move event.
	 * These events are only received when button 1 is up and the XY input mode is not pen.
	 */
		EMove,
	/*
	 *
	 * *Button repeat event.
	 */
		EButtonRepeat,
	/*
	 *
	 * *Switch on event caused by a screen tap.
	 */
		ESwitchOn,
		};
	TType iType;	// Type of pointer event
	TUint iModifiers;	// State of pointing device and associated buttons
	TPoint iPosition; 	// Window co-ordinates of mouse event
	TPoint iParentPosition; 	// position relative to parent window
	};

struct TKeyEvent
	{
	TUint iCode;
	TInt iScanCode;
	TUint iModifiers;	// State of modifier keys and pointing device
	TInt iRepeats;		// Count of auto repeats generated
	};

struct TModifiersChangedEvent
	{
	TUint iChangedModifiers;	// Bits set mean this modifier has changed
	TUint iModifiers;			// Current state of modifiers
	};

struct TWsErrorMessage
	{
	/*
	 *
	 * *Error event types.
	 */
	enum TErrorCategory
		{
	/*
	 *
	 * *An error that occurs while the window server is calculating a drawing region for a particular window.
	 * When the window server can't calculate a drawing region due to lack of memory it goes into a mode
	 * where it draws the whole of a window. Any window that is covering this window is also told to redraw.
	 */
		EDrawingRegion,
	/*
	 *
	 * *An error occured while trying to turn the backlight on or off.
	 * This would usually only happen when the batteries are low.
	 */
		EBackLight,		//For backlight and brightness
	/*
	 *
	 * *An error occured while trying to enable logging.
	 */
		ELogging,
	/*
	 *
	 * *An error that occured while trying to change the contrast.
	 */
		EContrast,
		};
	TErrorCategory iErrorCategory;
	TUint iError;
	};

/**
 *
 * Window server redraw event.
 *
 * All redraw events generated by the window server are delivered to the client in an object of this type.
 * The class provides a handle to the window which generated the redraw event, and the rectangle which should be redrawn.
 *
 * @since 5.0
 * @lib "N/A"
 */
class TWsRedrawEvent
	{
public:
	inline TUint Handle() const;
	inline TRect Rect() const;
protected:
	TUint iHandle;
	TRect iRect;			// Rectangle to redraw
	};

/**
 *
 * Priority key events.
 *
 * These events are configured using <code>RWindowGroup::AddPriorityKey()</code>, and obtained by the client
 * using the functions <code>RWsSession::PriorityKeyReady()</code> and <code>RWsSession::GetPriorityKey()</code>.
 *
 * @since 5.0
 * @lib "N/A"
 */
class TWsPriorityKeyEvent
	{
public:
	inline TKeyEvent *Key() const;
	inline TUint Handle() const;
	inline void SetHandle(TUint aHandle);
protected:
	TUint iHandle;
	TUint8 iEventData[sizeof(TKeyEvent)];
	};

/**
 *
 * Window server event.
 *
 * All events generated by the window server, except redraw events and priority key events, are delivered to the client in a
 * <code>TWsEvent</code>. The client obtains the <code>TWsEvent</code> by calling <code>RWsSession::GetEvent()</code>.
 * The type of data contained in the <code>TWsEvent</code> depends on the type of event.
 * The client can inquire the event type using <code>Type()</code>, and then retrieve the appropriate type of data.
 *
 * @since 5.0
 * @lib "N/A"
 */
class TWsEvent
	{
public:
	/*
	 *
	 * *Event data size.
	 *
	 * @since 
	 */
	enum
		{
	/*
	 *
	 * *The size of a <code>TPointer</code> event.
	 * This is the maximum number of bytes worth of data that can be returned by <code>EventData()</code>.
	 * Note:
	 * Currently this size is 6 bytes.
	 */
		EWsEventDataSize=sizeof(TPointerEvent)
		};
public:
	inline TPointerEvent *Pointer() const;
	inline TKeyEvent *Key() const;
	inline TModifiersChangedEvent *ModifiersChanged() const;
	inline TWsErrorMessage *ErrorMessage() const;
	inline TUint8 *EventData() const;
	inline TInt Type() const;
	inline TUint Handle() const;
	inline TTime Time() const;
	inline void SetType(TInt aType);
	inline void SetHandle(TUint aHandle);
	inline void SetTimeNow();
protected:
	TInt iType;
	TUint iHandle;
	TTime iTime;
	TUint8 iEventData[EWsEventDataSize];
	};

class RWsPointerCursor;

/**
 *
 * Pointer cursor mode flags.
 *
 * These flags define the current cursor mode, and hence which sprite to use for the pointer cursor.
 *
 */
enum TPointerCursorMode
	{
/** Don't have a pointer cursor.
 */
	EPointerCursorNone,
/** The default system pointer cursor is used whenever there is a pointer cursor.
 */
	EPointerCursorFixed,
/**
 *
 * The default system pointer cursor is used unless the window the pointer cursor is above specifies one
 * - in which case that cursor is used.
 *
 */
	EPointerCursorNormal,
/** There is no pointer cursor unless the pointer is above a window that has specified one.
 */
	EPointerCursorWindow,
/**
 *
 * First pointer cursor mode.
 * This is used in test code for iterating though available modes.
 *
 */
	EPointerCursorFirstMode=EPointerCursorNone,
/**
 *
 * The final pointer cursor mode.
 * This is used in test code for iterating though available modes. It will be updated if more modes are added.
 *
 */
	EPointerCursorLastMode=EPointerCursorWindow,
	};

enum TLongCaptureFlags
	{
	ELongCaptureShortEventImmediately=0x01,		//The normal key event is delivered straight away
	ELongCaptureRepeatEvents=0x02,			//The long event repeats
	//Combinations of the above
	ELongCaptureNormal=ELongCaptureShortEventImmediately,
	ELongCaptureWaitShort=0,
	};

/**
 *
 * Base class for all classes whose objects are clients of the windowserver engine.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class MWsClientClass
	{
	friend class CWindowGc;
public:
	MWsClientClass();
	MWsClientClass(RWsBuffer *aBuffer);
	inline TInt WsHandle() const;
protected:
	void Write(const TAny *aData, TInt aLength,const TAny *aData2, TInt aLength2,TUint aOpcode) const;
	void Write(const TAny *aBuf, TInt aBufLen,TUint aOpcode) const;
	void Write(TUint aOpcode) const;
	void WriteInt(TInt aInt, TUint aOpcode) const;
	void WriteRect(const TRect &aRect, TUint aOpcode) const;
	void WritePoint(const TPoint &aPoint, TUint aOpcode) const;
	void WriteSize(const TSize &aSize, TUint aOpcode) const;
	TInt WriteReply(TUint aOpcode) const;
	TInt WriteReplyInt(TInt aInt, TUint aOpcode) const;
	TInt WriteReply(const TAny *aBuf, TInt aBufLen,TUint aOpcode) const;
	TInt WriteReply(const TAny *aBuf, TInt aBufLen,const TAny *aBuf2, TInt aBuflen2,TUint aOpcode) const;
	TInt WriteReplyP(TAny *aPackage,TUint aOpcode) const;
	TInt WriteReplyIntP(TInt aInt, TAny *aPackage,TUint aOpcode) const;
	TInt WriteReplyP(const TAny *aBuf, TInt aBufLen,TAny *aPackage,TUint aOpcode) const;
	TInt WriteReplyP(const TAny *aBuf, TInt aBufLen,const TAny *aBuf2, TInt aBuflen2,TAny *aPackage,TUint aOpcode) const;
protected:
	TInt32 iWsHandle;
	RWsBuffer *iBuffer;
	};

/**
 *
 * Window server session.
 *
 * The session between the client and the window server can be used to mediate asynchronous events,
 * and for client interface control and system control. A description of each of these capabilities is given below.
 * This class is not intended for user derivation.
 * Mediating asynchronous events:
 * Primarily, the session mediates asynchronous events to the user. Three event streams are available: the standard event stream which
 * all applications must use; the redraw event stream which must be used by all applications except those which exclusively use
 * backed-up windows; and the priority key event stream which may be used for abort keys and the like for specialist applications.
 * All these events are mediated as standard asynchronous services. Typical window server client programs encapsulate
 * each service they require in an active object whose <code>RunL()</code> identifies the event and calls the appropriate
 * member function of a class associated with an application framework, or a window.
 * Client interface control:
 * The client's interface with the window server has several aspects, each of which is controlled through the window server session.
 * Flushing defines how requests to the window server are handled.
 * System control:
 * Many system-wide settings may be controlled by any application through its window server session.
 * Typically, these functions are only used by the system shell and its associated sessions/applications.
 * Auto-repeat and double-click.
 * Query all window groups in the system.
 * Setting the default shadow vector
 * Setting the system pointer cursors
 * Counting resources used by the window server. This is only useful for debugging checks.
 * Getting and checking the state of the modifier keys (SHIFT, CTRL AND FN)
 * Setting the window server background colour
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class RWsSession : public MWsClientClass, public RSessionBase
	{
	friend class RWsBuffer;
	friend class RWindowTreeNode;
	friend class CWsScreenDevice;
	friend class CWsBitmap;
	friend class RAnimDll;
	friend class RWsSpriteBase;
	friend class RDirectScreenAccess;
	friend class RSoundPlugIn;
public:
	/*
	 *
	 * *Compute mode flags.
	 *
	 * When a window group takes focus or loses it, the window server can boost its client's thread or process priority
	 * to provide a better response to the user. How it alters the priority as determined by the current compute mode of the client.
	 * @since 
	 */
	enum TComputeMode
		{
	/*
	 *
	 * *Client priority is permanently set to its current level - it is not altered or set by the windowing system if the focus changes.
	 * Thus if <code>ComputeMode()</code> is called with this flag when a client is in the foreground,
	 * it will subsequently have foreground priority even if it is in the background.
	 */
		EPriorityControlDisabled,
	/*
	 *
	 * *Client process's priority is always set to <code>EPriorityBackground</code>.
	 */
		EPriorityControlComputeOn,
	/*
	 *
	 * *Client process's priority is set to <code>EPriorityForeground</code> when the window group takes focus,
	 * and set to <code>EPriorityBackground</code> when it loses focus.
	 * This is the default behaviour.
	 */
		EPriorityControlComputeOff
		};
	enum {ESystemInfoArraySize=16};
	enum TLoggingCommand
		{
		ELoggingEnable,
		ELoggingDisable,
		ELoggingStatusDump,		//Window Tree Dump
		ELoggingHeapDump,
		};
	struct SSystemInfo
		{
		TInt iInfo[ESystemInfoArraySize];
		};
//
public:
	IMPORT_C RWsSession();
	IMPORT_C TInt Connect();
	IMPORT_C void Close();
	IMPORT_C TVersion Version();

	IMPORT_C TInt SetHotKey(THotKey aType, TUint aKeyCode, TUint aModifierMask, TUint aModifier);
	IMPORT_C TInt ClearHotKeys(THotKey aType);
	IMPORT_C TInt RestoreDefaultHotKey(THotKey aType);
//
	IMPORT_C void EventReady(TRequestStatus *aStat);
	IMPORT_C void EventReadyCancel();
	IMPORT_C void GetEvent(TWsEvent &aEvent);
	IMPORT_C void PurgePointerEvents();
//
	IMPORT_C void RedrawReady(TRequestStatus *aStat);
	IMPORT_C void RedrawReadyCancel();
	IMPORT_C void GetRedraw(TWsRedrawEvent &aEvent);
//
	IMPORT_C void PriorityKeyReady(TRequestStatus *aStat);
	IMPORT_C void PriorityKeyReadyCancel();
	IMPORT_C void GetPriorityKey(TWsPriorityKeyEvent &aEvent);
//
	IMPORT_C void Flush();
	IMPORT_C TBool SetAutoFlush(TBool aState);
	IMPORT_C void SetKeyboardRepeatRate(const TTimeIntervalMicroSeconds32 &aInitialTime, const TTimeIntervalMicroSeconds32 &aTime);
	IMPORT_C void GetKeyboardRepeatRate(TTimeIntervalMicroSeconds32 &aInitialTime, TTimeIntervalMicroSeconds32 &aTime);
	IMPORT_C void GetDoubleClickSettings(TTimeIntervalMicroSeconds32 &aInterval, TInt &aDistance);
	IMPORT_C void SetDoubleClick(const TTimeIntervalMicroSeconds32 &aInterval, TInt aDistance);
//
	IMPORT_C TInt NumWindowGroups() const;
	IMPORT_C TInt WindowGroupList(CArrayFixFlat<TInt> *aWindowList);
	IMPORT_C TInt NumWindowGroups(TInt aPriority) const;
	IMPORT_C TInt WindowGroupList(TInt aPriority, CArrayFixFlat<TInt> *aWindowList);
	IMPORT_C TInt GetFocusWindowGroup();
	IMPORT_C TInt GetDefaultOwningWindow();
	IMPORT_C TInt SetWindowGroupOrdinalPosition(TInt aIdentifier, TInt aPosition);
	IMPORT_C TInt GetWindowGroupClientThreadId(TInt aIdentifier, TThreadId &aThreadId);
	IMPORT_C TInt GetWindowGroupHandle(TInt aIdentifier);
	IMPORT_C TInt GetWindowGroupOrdinalPriority(TInt aIdentifier);
	IMPORT_C TInt SendEventToWindowGroup(TInt aIdentifier, const TWsEvent &aEvent);
	IMPORT_C TInt SendEventToAllWindowGroups(const TWsEvent &aEvent);
	IMPORT_C TInt SendEventToAllWindowGroups(TInt aPriority, const TWsEvent &aEvent);
	IMPORT_C TInt SendEventToOneWindowGroupsPerClient(const TWsEvent &aEvent);
	IMPORT_C TInt GetWindowGroupNameFromIdentifier(TInt aIdentifier, TDes &aWindowName);
	IMPORT_C TInt FindWindowGroupIdentifier(TInt aPreviousIdentifier,const TDesC& aMatch,TInt aOffset=0);
	IMPORT_C TInt FindWindowGroupIdentifier(TInt aPreviousIdentifier,TThreadId aThreadId);
	IMPORT_C TInt SendMessageToWindowGroup(TInt aIdentifier, TUid aUid, const TDesC8 &aParams);
	IMPORT_C TInt SendMessageToAllWindowGroups(TUid aUid, const TDesC8& aParams);
	IMPORT_C TInt SendMessageToAllWindowGroups(TInt aPriority, TUid aUid, const TDesC8& aParams);
	IMPORT_C TInt FetchMessage(TUid &aUid, TPtr8 &aParams, const TWsEvent& aMessageEvent);
//
	IMPORT_C void SetShadowVector(const TPoint &aVector);
	IMPORT_C TPoint ShadowVector() const;
//
	IMPORT_C void SetBackgroundColor(TRgb aColor);
	IMPORT_C TRgb GetBackgroundColor() const;
//
	IMPORT_C TInt SetSystemPointerCursor(const RWsPointerCursor &aPointerCursor,TInt aCursorNumber);
	IMPORT_C void ClearSystemPointerCursor(TInt aCursorNumber);
	IMPORT_C TInt ClaimSystemPointerCursorList();
	IMPORT_C void FreeSystemPointerCursorList();
//
	IMPORT_C TInt ResourceCount();
	IMPORT_C void PasswordEntered();
	IMPORT_C void ComputeMode(TComputeMode aMode);
//
	IMPORT_C TInt HeapCount() const;
	IMPORT_C void MarkStart();
	IMPORT_C void CheckNum(TUint aCount);
	IMPORT_C void MarkEnd(TUint aCount);
	IMPORT_C void HeapSetFail(RHeap::TAllocFail aType,TInt aValue);
	IMPORT_C void SetModifierState(TEventModifier aModifier,TModifierState aState);
	IMPORT_C TInt GetModifierState() const;
//
	IMPORT_C TInt RequestOffEvents(TBool aOn,RWindowTreeNode *aWin=NULL);
	IMPORT_C TDisplayMode GetDefModeMaxNumColors(TInt& aColor,TInt& aGray) const;
	IMPORT_C TInt GetColorModeList(CArrayFixFlat<TInt> *aModeList) const;
//
	IMPORT_C void SetPointerCursorArea(const TRect& aArea);
	IMPORT_C void SetPointerCursorArea(TInt aScreenSizeMode,const TRect& aArea);
	IMPORT_C TRect PointerCursorArea() const;
	IMPORT_C TRect PointerCursorArea(TInt aScreenSizeMode) const;
	IMPORT_C void SetPointerCursorMode(TPointerCursorMode aMode);
	IMPORT_C TPointerCursorMode PointerCursorMode() const;
	IMPORT_C void SetDefaultSystemPointerCursor(TInt aCursorNumber);
	IMPORT_C void ClearDefaultSystemPointerCursor();
	IMPORT_C void SetPointerCursorPosition(const TPoint& aPosition);
	IMPORT_C TPoint PointerCursorPosition() const;

	IMPORT_C void SetDefaultFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap);
	IMPORT_C void PrepareForSwitchOff();		//For SYMBIAN use only!!
	IMPORT_C void SetBufferSizeL(TInt aBufSize);
#if defined(__WINS__)
// Function for WINS behaviour only
//
	IMPORT_C void SetRemoveKeyCode(TBool aRemove);
	IMPORT_C void SimulateXyInputType(TXYInputType aInputType);		//Only for testing WSERV
#endif
// Raw event simulation is designed purely for Wserv testing at the moment
// Althoug it is possible it may in future be used by applications
//
	IMPORT_C void SimulateRawEvent(TRawEvent aEvent);
	IMPORT_C void SimulateKeyEvent(TKeyEvent aEvent);
	IMPORT_C void LogCommand(TLoggingCommand aCommand);
	IMPORT_C void LogMessage(const TLogMessageText &aMessage);
//
// Functions for test code use only
//
	IMPORT_C void SystemInfo(TInt &aSystemInfoNumber, SSystemInfo &aSystemInfo);
	IMPORT_C void TestWrite(TInt aHandle,TInt aOpcode,const TAny *aData, TInt aLength);
	IMPORT_C void TestWriteReply(TInt aHandle,TInt aOpcode,const TAny *aData, TInt aLength);
	IMPORT_C void TestWriteReplyP(TInt aHandle,TInt aOpcode,const TAny *aData,TInt aLength,TDes8 *aReplyPackage);
private:
	TInt doWindowGroupList(TInt aPriority, CArrayFixFlat<TInt> *aWindowList, TInt aNumOpcode, TInt aListOpcode);
	TInt doSetHotKey(TInt aOpcode, TInt aType, TUint aKeycode, TUint aModifierMask, TUint aModifiers);
	void doReadEvent(TRequestStatus *aStat, TInt aOpcode);
private:
	void connectL();
	TInt DoFlush(const TPtr8 *aBuf, TAny *aPackage);
	void DirectAcessActivation(TBool aIsNowActive);
	};

typedef TInt (*AnimCommand)(TPtr8 *aBufPtr,TAny *aPackage);

/**
 *
 * Handle to a node in the server-side window tree.
 *
 * This handle class is used as the base for both window groups and the windows within them; it is not intended for user derivation,
 * and may not be directly constructed: use one of the standard derived classes instead.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class RWindowTreeNode : public MWsClientClass
	{
	friend class RWindowGroup;
	friend class RWindowBase;
	friend class CWindowGc;
	friend class RAnimDll;
	friend class RWsSprite;
public:
	/*
	 *
	 * *Fade control flags.
	 *
	 * These flags define whether fading is applied to all child windows when <code>SetFaded()</code> is called on a window.
	 * @since 
	 */
	enum TFadeControl
		{
	/*
	 *
	 * * Include all child windows in fading/un-fading action.
	 */
		EFadeIncludeChildren=ETrue,
	/*
	 *
	 * *Fade only the parent window.
	 * Note that it will cause a panic if this value is used when <code>SetFaded()</code> is called on a window group.
	 */
		EFadeWindowOnly=EFalse,
		};
protected:
	RWindowTreeNode();
	RWindowTreeNode(RWsSession &aWs);
public:
	IMPORT_C void Close();
	IMPORT_C void Destroy();
	IMPORT_C TUint32 Parent() const;
	IMPORT_C TUint32 PrevSibling() const;
	IMPORT_C TUint32 NextSibling() const;
	IMPORT_C TUint32 Child() const;
	IMPORT_C TInt OrdinalPriority() const;
	IMPORT_C TInt OrdinalPosition() const;
	IMPORT_C TInt FullOrdinalPosition() const;
	IMPORT_C void SetOrdinalPosition(TInt aPos);
	IMPORT_C void SetOrdinalPosition(TInt aPos,TInt aOrdinalPriority);
	IMPORT_C TInt SetPointerCursor(TInt aCursorNumber);
	IMPORT_C void SetCustomPointerCursor(const RWsPointerCursor &aPointerCursor);
	IMPORT_C TInt EnableOnEvents(TEventControl aCircumstances=EEventControlOnlyWithKeyboardFocus);
	IMPORT_C void DisableOnEvents();
	IMPORT_C TInt EnableGroupChangeEvents();
	IMPORT_C void DisableGroupChangeEvents();
	IMPORT_C TInt EnableFocusChangeEvents();
	IMPORT_C void DisableFocusChangeEvents();
	IMPORT_C TInt EnableErrorMessages(TEventControl aCircumstances);
	IMPORT_C void DisableErrorMessages();
	IMPORT_C TInt EnableModifierChangedEvents(TUint aModifierMask, TEventControl aCircumstances);
	IMPORT_C void DisableModifierChangedEvents();
	IMPORT_C void SetNonFading(TBool aNonFading);
	IMPORT_C void SetFaded(TBool aFaded,TFadeControl aIncludeChildren);
	IMPORT_C void SetFaded(TBool aFaded,TFadeControl aIncludeChildren,TUint8 aBlackMap,TUint8 aWhiteMap);
	IMPORT_C void ClearPointerCursor();
protected:
	__DECLARE_TEST;
	};

/**
 *
 * Client-side handle to a server-side window.
 *
 * The server-side windows of handles derived from this class can be displayed on the device's screen, and associated with pointer events.
 * This class is not for user derivation; however derived classes form part of the standard Window Server client library.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class RWindowBase : public RWindowTreeNode
	{
public:
	/*
	 *
	 * *Capture behaviour flags.
	 *
	 * The first three flags actually control state, the remaining flags are commonly used combinations of these.
	 * @since 
	 */
	enum TCaptureFlags
		{
// Flags, these can be combined to customise pointer capture
	/*
	 *
	 * * If set, capture is enabled, disabled otherwise.
	 */
		TCaptureFlagEnabled=0x01,
	/*
	 *
	 * * If set, drag-drop events are sent to the window in which the pointer was lifted. Drag-drop is a tap-drag-lift sequence.
	 */
		TCaptureFlagDragDrop=0x02,
	/*
	 *
	 * * Capture events from windows belonging to any group, not just the group of the window on which the flag was set
	 */
		TCaptureFlagAllGroups=0x04,
// States, made up of a set of flags
	/*
	 *
	 * * Equivalent to disabling all the above flags.
	 */
		TCaptureDisabled=0,
	/*
	 *
	 * * Equivalent to <code>TCaptureFlagEnabled</code>.
	 */
		TCaptureEnabled=TCaptureFlagEnabled,
	/*
	 *
	 * * Shorthand for the OR of the first three flags.
	 */
		TCaptureDragDrop=TCaptureFlagEnabled|TCaptureFlagDragDrop|TCaptureFlagAllGroups,
		};
protected:
	RWindowBase();
	RWindowBase(RWsSession &aWs);
public:
	IMPORT_C void Activate();
	IMPORT_C void SetPosition(const TPoint &point);
	IMPORT_C TInt SetSizeErr(const TSize &size);
	IMPORT_C TInt SetExtentErr(const TPoint &point,const TSize &size);
	IMPORT_C TSize Size() const;
	IMPORT_C TPoint InquireOffset(const RWindowTreeNode &aWindow) const;
	IMPORT_C void PointerFilter(TUint32 aFilterMask, TUint32 aFilter);
	IMPORT_C void SetPointerGrab(TBool aState);
	IMPORT_C void ClaimPointerGrab(TBool aSendUpEvent=ETrue);
	IMPORT_C void SetPointerCapture(TInt aFlags);
	IMPORT_C void SetVisible(TBool aState);
	IMPORT_C void SetShadowHeight(TInt aHeight);
	IMPORT_C void SetShadowDisabled(TBool aState);
	IMPORT_C TPoint Position() const;
	IMPORT_C TInt SetCornerType(TCornerType aCornerType, TInt aCornerFlags=0);
	IMPORT_C TInt SetShape(const TRegion &aRegion);
	IMPORT_C TInt SetRequiredDisplayMode(TDisplayMode aMode);
	IMPORT_C TDisplayMode DisplayMode();
	IMPORT_C void EnableBackup(TUint aBackupType=EWindowBackupAreaBehind);
	IMPORT_C void RequestPointerRepeatEvent(TTimeIntervalMicroSeconds32 aTime,const TRect &aRect);
	IMPORT_C void CancelPointerRepeatEventRequest();
	IMPORT_C TInt AllocPointerMoveBuffer(TInt aMaxPoints, TUint aFlags);
	IMPORT_C void FreePointerMoveBuffer();
	IMPORT_C void EnablePointerMoveBuffer();
	IMPORT_C void DisablePointerMoveBuffer();
	IMPORT_C TInt RetrievePointerMoveBuffer(TDes8 &aBuf);
	IMPORT_C void DiscardPointerMoveBuffer();
	IMPORT_C TInt AddKeyRect(const TRect &aRect, TInt aScanCode, TBool aActivatedByPointerSwitchOn);
	IMPORT_C void RemoveAllKeyRects();
	IMPORT_C TInt PasswordWindow(TPasswordMode aPasswordMode);
	IMPORT_C void FadeBehind(TBool aFade);
	IMPORT_C TBool IsFaded();
	IMPORT_C TBool IsNonFading();
	IMPORT_C TInt MoveToGroup(TInt aIdentifier);
protected:
	TInt construct(const RWindowTreeNode &parent,TUint32 aHandle, TInt aType, TDisplayMode aDisplayMode);
	};

/**
 *
 * Blank window.
 *
 * A blank window may have its extent and colour changed, but nothing else may be drawn to it.
 * Blank windows provide no functionality that is not provided by the <code>RWindow</code> class.
 * However, they are useful when the application requires a window that cannot be drawn to, for example a container window.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class RBlankWindow : public RWindowBase
	{
public:
	IMPORT_C RBlankWindow();
	IMPORT_C RBlankWindow(RWsSession &aWs);
	IMPORT_C TInt Construct(const RWindowTreeNode &parent, TUint32 aHandle);
	IMPORT_C void SetColor(TRgb aColor);
	IMPORT_C void SetSize(const TSize &size);
	IMPORT_C void SetExtent(const TPoint &point,const TSize &size);
	};

/**
 *
 * Handle to a drawable window.
 *
 * <code>RDrawableWindow</code>s are <code>RWindowBase</code> which can be drawn to. This class is not intended for user derivation,
 * and cannot be initialised directly. The two concrete derived classes, <code>RWindow</code> and <code>RBackedUpWindow</code>,
 * allow drawing but use different protocols because <code>RWindow</code> relies on the client to redraw invalid areas.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class RDrawableWindow : public RWindowBase
	{
protected:
	RDrawableWindow();
	RDrawableWindow(RWsSession &aWs);
public:
	IMPORT_C void Scroll(const TPoint &aOffset);
	IMPORT_C void Scroll(const TRect &aClipRect, const TPoint &aOffset);
	IMPORT_C void Scroll(const TPoint &aOffset, const TRect &aRect);
	IMPORT_C void Scroll(const TRect &aClipRect, const TPoint &aOffset, const TRect &aRect);
private:
	void doScroll(const TRect &aClipRect, const TPoint &aOffset, const TRect &aRect, TInt aOpcode);
	};

/**
 *
 * Handle to a standard window.
 *
 * An <code>RWindow</code> is a handle to a server-side window which can be displayed and drawn to,
 * and whose redraws are performed by the application.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class RWindow : public RDrawableWindow
	{
public:
	IMPORT_C RWindow();
	IMPORT_C RWindow(RWsSession &aWs);
	IMPORT_C TInt Construct(const RWindowTreeNode &parent,TUint32 aHandle);
	IMPORT_C void BeginRedraw();
	IMPORT_C void BeginRedraw(const TRect &aRect);
	IMPORT_C void EndRedraw();
	IMPORT_C void Invalidate();
	IMPORT_C void Invalidate(const TRect &aRect);
	IMPORT_C void GetInvalidRegion(RRegion &aRegion);
	IMPORT_C void SetBackgroundColor(TRgb aColor);
	IMPORT_C void SetBackgroundColor();
	IMPORT_C void SetSize(const TSize &size);
	IMPORT_C void SetExtent(const TPoint &point,const TSize &size);
	};

class RBackedUpWindow : public RDrawableWindow
	{
public:
	IMPORT_C RBackedUpWindow();
	IMPORT_C RBackedUpWindow(RWsSession &aWs);
	IMPORT_C TInt Construct(const RWindowTreeNode &parent,TDisplayMode aDisplayMode, TUint32 aHandle);
	IMPORT_C TInt BitmapHandle();
	IMPORT_C void UpdateScreen();
	IMPORT_C void UpdateScreen(const TRegion &aRegion);
	IMPORT_C void UpdateBackupBitmap();
	IMPORT_C void MaintainBackup();
	};

/**
 *
 * Client-side handle to a server-side window group.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class RWindowGroup : public RWindowTreeNode
	{
public:
	IMPORT_C RWindowGroup();
	IMPORT_C RWindowGroup(RWsSession &aWs);
	IMPORT_C TInt Construct(TUint32 aClientHandle);
	IMPORT_C TInt Construct(TUint32 aClientHandle, TBool aInitialFocusState);
	IMPORT_C void EnableReceiptOfFocus(TBool aState);
	IMPORT_C void AutoForeground(TBool aState);
	IMPORT_C void SetOrdinalPriorityAdjust(TInt aAdjust);
	IMPORT_C TInt32 CaptureKey(TUint aKeycode, TUint aModifierMask, TUint aModifier);
	IMPORT_C TInt32 CaptureKey(TUint aKeycode, TUint aModifierMask, TUint aModifier, TInt aPriority);
	IMPORT_C void CancelCaptureKey(TInt32 aCaptureKey);
	IMPORT_C TInt32 CaptureKeyUpAndDowns(TUint aScanCode, TUint aModifierMask, TUint aModifier);
	IMPORT_C TInt32 CaptureKeyUpAndDowns(TUint aScanCode, TUint aModifierMask, TUint aModifier, TInt aPriority);
	IMPORT_C void CancelCaptureKeyUpAndDowns(TInt32 aCaptureKey);
	IMPORT_C TInt32 CaptureLongKey(TUint aInputKeyCode,TUint aOutputKeyCode,TUint aModifierMask,TUint aModifier
																										,TInt aPriority,TUint aFlags);
	IMPORT_C TInt32 CaptureLongKey(TTimeIntervalMicroSeconds32 aRepeatTime,TUint aInputKeyCode,TUint aOutputKeyCode
																	,TUint aModifierMask,TUint aModifier,TInt aPriority,TUint aFlags);
	IMPORT_C void CancelCaptureLongKey(TInt32 aCaptureKey);
	IMPORT_C TInt AddPriorityKey(TUint aKeycode, TUint aModifierMask, TUint aModifier);
	IMPORT_C void RemovePriorityKey(TUint aKeycode, TUint aModifierMask, TUint aModifier);
	IMPORT_C void SetTextCursor(RWindowBase &aWin, const TPoint &aPos, const TTextCursor &aCursor);
	IMPORT_C void SetTextCursor(RWindowBase &aWin, const TPoint &aPos, const TTextCursor &aCursor, const TRect &aClipRect);
	IMPORT_C void CancelTextCursor();
	IMPORT_C void SetOwningWindowGroup(TInt aIdentifier);
	IMPORT_C void DefaultOwningWindow();
	IMPORT_C TInt SetName(const TDesC &aName);
	IMPORT_C TInt Name(TDes &aWindowName) const;
	IMPORT_C TInt Identifier() const;
	IMPORT_C void DisableKeyClick(TBool aState);
	IMPORT_C TInt EnableScreenChangeEvents();
	IMPORT_C void DisableScreenChangeEvents();
	IMPORT_C void SimulatePointerEvent(TRawEvent aEvent);
private:
	TInt32 doCaptureKey(TUint aKey, TUint aModifierMask, TUint aModifiers, TInt aPriority, TInt aOpcode);
	void doCancelCaptureKey(TInt32 aCaptureKeyHandle, TInt aOpcode);
	};

/**
 *
 * Window server bitmap.
 *
 * This is a bitmap to which the window server already has a handle.
 * Functions which take a window server bitmap are faster than equivalent functions which take a <code>CFbsBitmap</code>.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class CWsBitmap : public CFbsBitmap, public MWsClientClass
	{
public:
	IMPORT_C CWsBitmap();
	IMPORT_C CWsBitmap(RWsSession &aWs);
	IMPORT_C ~CWsBitmap();
	IMPORT_C TInt Create(const TSize& aSizeInPixels,TDisplayMode aDispMode);
	IMPORT_C TInt Duplicate(TInt aHandle);
	IMPORT_C TInt Load(const TDesC& aFileName,TInt32 aId,TBool aShareIfLoaded=ETrue);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void Reset();
private:
	TInt createWsBitmap(TInt aErr);
	};

/**
 *
 * Window graphics context.
 *
 * Most window graphics context drawing functions map to equivalent <code>CFbsBitGc</code> functions they are implemented on the screen 
 * with any co-ordinates being relative to the top left corner of the window. However extra clipping is applied. The drawing will always 
 * be clipped to the visible part of the window, in addition it will be clipped to the non-invalid part if you are not doing a redraw and 
 * to the region being validated if you are doing a redraw. Note:In general, server side functions which encounter conditions which would 
 * normally cause a leave, do not leave but instead return an error value indicating the leave condition. In this way the leave can be 
 * handled on the appropriate side of the client/server boundary. For example, a client can choose to wrap server calls with 
 * <code>User::LeaveIfError()</code> - which causes a leave with the specified error.The above advice is true of many functions in this 
 * class, and in its derived classes.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class CWindowGc : public CBitmapContext, public MWsClientClass
	{
	friend class CWsScreenDevice;
public:
	IMPORT_C CWindowGc(CWsScreenDevice *aDevice);
	IMPORT_C virtual ~CWindowGc();
	IMPORT_C virtual TInt Construct();
	IMPORT_C virtual void Activate(RDrawableWindow &aWindow);
	IMPORT_C virtual void Deactivate();
//====================FROM CGraphicsContext.H===============================
	IMPORT_C virtual CGraphicsDevice* Device() const;
	IMPORT_C virtual void SetOrigin(const TPoint &aPos=TPoint(0,0));
	IMPORT_C virtual void SetDrawMode(TDrawMode aDrawingMode);
	IMPORT_C virtual void SetClippingRect(const TRect& aRect);
	IMPORT_C virtual void CancelClippingRect();
	IMPORT_C virtual void Reset();

	IMPORT_C virtual void UseFont(const CFont *aFont);
	IMPORT_C virtual void DiscardFont();
	IMPORT_C virtual void SetUnderlineStyle(TFontUnderline aUnderlineStyle);
	IMPORT_C virtual void SetStrikethroughStyle(TFontStrikethrough aStrikethroughStyle);
// Used to do justified text properly
	IMPORT_C virtual void SetWordJustification(TInt aExcessWidth,TInt aNumGaps);
// Used primarily to get accurate WYSIWYG
	IMPORT_C virtual void SetCharJustification(TInt aExcessWidth,TInt aNumChars);

	IMPORT_C virtual void SetPenColor(const TRgb &aColor);
	IMPORT_C virtual void SetPenStyle(TPenStyle aPenStyle);
	IMPORT_C virtual void SetPenSize(const TSize& aSize);

	IMPORT_C virtual void SetBrushColor(const TRgb &aColor);
	IMPORT_C virtual void SetBrushStyle(TBrushStyle aBrushStyle);
	IMPORT_C virtual void SetBrushOrigin(const TPoint &aOrigin);
	IMPORT_C virtual void UseBrushPattern(const CFbsBitmap *aBitmap);
	IMPORT_C virtual void DiscardBrushPattern();
//
// Move the internal position, as used by DrawLineTo & DrawLineBy, and set by MoveTo,
// MoveBy, DrawLine, DrawLineTo, DrawLineBy and DrawPolyline
	IMPORT_C virtual void MoveTo(const TPoint &aPoint);
	IMPORT_C virtual void MoveBy(const TPoint &aVector);
	IMPORT_C virtual void Plot(const TPoint &aPoint);
//
//  Line drawing subject to pen color, width and style and draw mode
	IMPORT_C virtual void DrawArc(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd);
	IMPORT_C virtual void DrawLine(const TPoint &aPoint1,const TPoint &aPoint2);
	IMPORT_C virtual void DrawLineTo(const TPoint &aPoint);
	IMPORT_C virtual void DrawLineBy(const TPoint &aVector);
	IMPORT_C virtual void DrawPolyLine(const CArrayFix<TPoint> *aPointList);
	IMPORT_C virtual void DrawPolyLine(const TPoint* aPointList,TInt aNumPoints);
//
// Filled outlines
// Outlines subject to pen color, width and style and draw mode
// (set pen to ENullPen for no outline)
// Fill subject to brush style (color, hash or pattern) and origin and
// drawing mode (set brush to ENullBrush for no fill)
	IMPORT_C virtual void DrawPie(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd);
	IMPORT_C virtual void DrawEllipse(const TRect &aRect);
	IMPORT_C virtual void DrawRect(const TRect &aRect);
	IMPORT_C virtual void DrawRoundRect(const TRect &aRect,const TSize &aEllipse);
	IMPORT_C virtual TInt DrawPolygon(const CArrayFix<TPoint> *aPointList,TFillRule aFillRule=EAlternate);
	IMPORT_C virtual TInt DrawPolygon(const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule=EAlternate);
//
// Uses the bitmap's Twips size and does a "stretch" blit in general
	IMPORT_C virtual void DrawBitmap(const TPoint &aTopLeft, const CFbsBitmap *aSource);
	IMPORT_C virtual void DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aSource);
	IMPORT_C virtual void DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aSource, const TRect &aSourceRect);
//
// Text drawing subject to drawing mode
// Subject to used font, pen color, drawing mode, 
// word and char justification
	IMPORT_C virtual void DrawText(const TDesC &aString,const TPoint &aPosition);
//
// Subject to same as above plus brush for background
// (set brush to ENullBrush for no effect on background)
	IMPORT_C virtual void DrawText(const TDesC &aString,const TRect &aBox,TInt aBaselineOffset,TTextAlign aHoriz=ELeft,TInt aLeftMrg=0);
//================Extra functions from CBitmapContext==============
	IMPORT_C virtual void Clear();
	IMPORT_C virtual void Clear(const TRect &aRect);
	IMPORT_C virtual void CopyRect(const TPoint &aOffset,const TRect &aRect);
	IMPORT_C virtual void BitBlt(const TPoint &aPos, const CFbsBitmap *aDevice);
	IMPORT_C virtual void BitBlt(const TPoint &aPos, const CFbsBitmap *aDevice, const TRect &aRect);
	IMPORT_C virtual void BitBltMasked(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aSourceRect,const CFbsBitmap* aMaskBitmap,TBool aInvertMask);
	IMPORT_C virtual void BitBlt(const TPoint &aPos, const CWsBitmap *aDevice);
	IMPORT_C virtual void BitBlt(const TPoint &aPos, const CWsBitmap *aDevice, const TRect &aRect);
	IMPORT_C virtual void BitBltMasked(const TPoint& aPoint,const CWsBitmap *aBitmap,const TRect& aSourceRect,const CWsBitmap *aMaskBitmap,TBool aInvertMask);
	IMPORT_C virtual void MapColors(const TRect& aRect,const TRgb* aColors,TInt aNumPairs=2,TBool aMapForwards=ETrue);

	IMPORT_C virtual void DrawTextVertical(const TDesC& aText,const TPoint& aPosition,TBool aUp);
	IMPORT_C virtual void DrawTextVertical(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TBool aUp,TTextAlign aVert=ELeft,TInt aMargin=0);
//=================Extra functions specific to wserv GDI==============
	IMPORT_C virtual void SetDitherOrigin(const TPoint& aPoint);
	IMPORT_C virtual TInt SetClippingRegion(const TRegion &aClippingRegion);
	IMPORT_C virtual void CancelClippingRegion();
//=================Functions also supplied by CFbsBitGc==============
	IMPORT_C void SetFaded(TBool aFaded);
	IMPORT_C void SetFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap);
////=============================================================
private: // Private code
	TRgb Color(TInt aOpcode)const;
	void SetJustification(TInt aExcessWidth,TInt aNumGaps, TInt aOpcode);
	void DrawArcOrPie(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd, TInt aOpcode);
	void doDrawPolyLine(const CArrayFix<TPoint> *aPointArray, const TPoint* aPointList,TInt aNumPoints);
	TInt doDrawPolygon(const CArrayFix<TPoint> *aPointArray,const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule);
	void WriteTextPos(TInt aOpcode,TInt aOpcodePtr,const TPoint &aPos,const TDesC &aBuf) const;
	void WriteTextCommand(TAny *aCmd, TInt aLen,const TDesC &aBuf,TInt aOpcode,TInt aOpcodePtr) const;
private: // Private data
	CFbsFont *iFont;
	CWsScreenDevice *iDevice;
	};

/**
 *
 * Software device screen.
 *
 * An object of this class can be used to inquire or set parameters of the software screen,
 * and determine the physical limits of the device.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class CWsScreenDevice : public CBitmapDevice, public MWsClientClass
	{
public:
	IMPORT_C CWsScreenDevice();
	IMPORT_C CWsScreenDevice(RWsSession &aWs);
	IMPORT_C ~CWsScreenDevice();
	IMPORT_C TInt Construct();
//==== From CGraphicsDevice ====//
	IMPORT_C TDisplayMode DisplayMode() const;
	IMPORT_C TSize SizeInPixels() const;
	IMPORT_C TSize SizeInTwips() const;
	IMPORT_C TInt HorizontalTwipsToPixels(TInt aTwips) const;
	IMPORT_C TInt VerticalTwipsToPixels(TInt aTwips) const;
	IMPORT_C TInt HorizontalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt VerticalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TRect PointerRect() const;
	IMPORT_C TInt CreateContext(CGraphicsContext *&aGc);
    inline TInt CreateContext(CWindowGc *&aGc);
	IMPORT_C TInt GetNearestFontInTwips(CFont*& aFont,const TFontSpec& aFontSpec);
	IMPORT_C TInt NumTypefaces() const;
	IMPORT_C void TypefaceSupport(TTypefaceSupport& aTypefaceSupport,TInt aTypefaceIndex) const;
	IMPORT_C TInt FontHeightInTwips(TInt aTypefaceIndex,TInt aHeightIndex) const;
// ==== From CBitmapDevice ====//
    IMPORT_C void GetPixel(TRgb &aColor,const TPoint &aPixel) const;
    IMPORT_C void GetScanLine(TDes8 &aBuf,const TPoint &aPixel,TInt aLength, TDisplayMode aDispMode) const;
	IMPORT_C TInt AddFile(const TDesC& aName,TInt& aId);
	IMPORT_C void RemoveFile(TInt aId=0);
	IMPORT_C TInt GetNearestFontInPixels(CFont*& aFont,const TFontSpec& aFontSpec);
	IMPORT_C TInt FontHeightInPixels(TInt aTypefaceIndex,TInt aHeightIndex) const;
	IMPORT_C void ReleaseFont(CFont* aFont);
//===== From CFbsScreenDevice ====//
	IMPORT_C void PaletteAttributes(TBool& aModifiable,TInt& aNumEntries) const;
	IMPORT_C void SetPalette(CPalette* aPalette);
	IMPORT_C TInt GetPalette(CPalette*& aPalette) const;
//===== Extra functions ====//
	IMPORT_C TInt SetCustomPalette(const CPalette* aPalette);
 	IMPORT_C TInt GetFontById(CFont *&aFont,TUid aUid,const TAlgStyle& aAlgStyle);
	IMPORT_C TBool RectCompare(const TRect &aRect1,const TRect &aRect2);
	IMPORT_C TInt CopyScreenToBitmap(const CFbsBitmap *aBitmap) const;
	IMPORT_C TInt CopyScreenToBitmap(const CFbsBitmap *aBitmap, const TRect &aRect) const;
//===== Screen Rotation functions ====//
	IMPORT_C void SetScreenSizeAndRotation(const TPixelsTwipsAndRotation &aSizeAndRotation);
	IMPORT_C void GetDefaultScreenSizeAndRotation(TPixelsTwipsAndRotation &aSizeAndRotation) const;
	IMPORT_C void SetScreenSizeAndRotation(const TPixelsAndRotation &aSizeAndRotation);
	IMPORT_C void GetDefaultScreenSizeAndRotation(TPixelsAndRotation &aSizeAndRotation) const;
	IMPORT_C TScreenModeEnforcement ScreenModeEnforcement() const;
	IMPORT_C void SetScreenModeEnforcement(TScreenModeEnforcement aMode) const;
	IMPORT_C void GetScreenModeSizeAndRotation(TInt aMode, TPixelsTwipsAndRotation &aSizeAndRotation) const;
	IMPORT_C void GetScreenModeSizeAndRotation(TInt aMode, TPixelsAndRotation &aSizeAndRotation) const;
	IMPORT_C void SetCurrentRotations(TInt aMode, CFbsBitGc::TGraphicsOrientation aRotation) const;
	IMPORT_C TInt GetRotationsList(TInt aMode, CArrayFixFlat<TInt> *aRotationList) const;
	IMPORT_C TInt NumScreenModes() const;
	IMPORT_C void SetScreenMode(TInt aMode);
	IMPORT_C TInt CurrentScreenMode() const;
private: // Private data
	CFbsTypefaceStore* iTypefaceStore;
	TSize iPhysicalScreenSizeInTwips;
	TSize iDisplaySizeInPixels;
	friend class CWindowGc;
	};

/**
 *
 * Sprite base class.
 * 
 * @since 5.0
 * @lib "ws32.lib"
 */
class RWsSpriteBase : public MWsClientClass
// Client side class base class for sprites and pointer cursors
	{
protected:
	IMPORT_C RWsSpriteBase();
	IMPORT_C RWsSpriteBase(RWsSession &aWs);
public:
	IMPORT_C TInt Activate();
	IMPORT_C TInt AppendMember(const TSpriteMember &aSpriteList);
	IMPORT_C void UpdateMember(TInt aIndex);
	IMPORT_C TInt UpdateMember(TInt aIndex, const TSpriteMember &aMemberData);
	IMPORT_C void Close();
	};

/**
 *
 * Sprite.
 *
 * This class defines functions to create and initialise a sprite, and to set its position.
 * It also inherits the functions of <code>RWsSpriteBase</code>.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class RWsSprite : public RWsSpriteBase
// Client side class for sprites
	{
public:
	IMPORT_C RWsSprite();
	IMPORT_C RWsSprite(RWsSession &aWs);
	IMPORT_C TInt Construct(RWindowTreeNode &aWindow, const TPoint &aPos, TInt aFlags);
	IMPORT_C void SetPosition(const TPoint &aPos);
	};

/**
 *
 * Pointer cursor.
 *
 * The pointer cursor is created in a similar way to a sprite.
 * It is first created, and then one or more sprite members containing the bitmaps to be displayed are added.
 * After a pointer cursor has been created and activated, it does not become visible until the application calls
 * <code>RWindowTreeNode::SetPointerCursor()</code> or <code>RWindowTreeNode::SetCustomPointerCursor()</code>. The pointer cursor's
 * origin automatically tracks the position of the pointing device, and the origin forms the pointer cursor's "hot spot", i.e., the point
 * whose co-ordinates are sent to the client if a pointer event occurs. If the pointer cursor's bitmap needs to extend to the left or
 * upwards from the pointer position, its sprite member should be given a negative offset in<code> TSpriteMember::iOffset</code>.
 * Note:
 * Pointer cursors are rarely used in pure pen architectures, but they are supported for mouse or tablet use.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class RWsPointerCursor : public RWsSpriteBase
	{
	friend class RWindowTreeNode;
	friend class RWsSession;
public:
	IMPORT_C RWsPointerCursor();
	IMPORT_C RWsPointerCursor(RWsSession &aWs);
	IMPORT_C TInt Construct(TInt aFlags);
	};

class RAnim;
/**
 *
 * Client-side interface to the server-side animation DLL.
 *
 * This is the client side class matching the server side <code>CAnimDLL</code> class.
 * It provides functions to create, load, close, and destroy a server-side <code>CAnimDll</code> object.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class RAnimDll : public MWsClientClass
	{
public:
	IMPORT_C RAnimDll();
	IMPORT_C virtual ~RAnimDll();
	IMPORT_C RAnimDll(RWsSession &aWs);
	IMPORT_C TInt Load(const TDesC &aFileName);
	IMPORT_C void Destroy();
	IMPORT_C virtual void Close();
private:
	TInt CommandReply(TInt aHandle, TInt aOpcode, const TPtrC8 &aArgs);
	TInt CommandReply(TInt aHandle, TInt aOpcode);
	void Command(TInt aHandle, TInt aOpcode, const TPtrC8 &aArgs);
	void Command(TInt aHandle, TInt aOpcode);
	TInt CreateInstance(const MWsClientClass &aDevice, TInt aType, const TPtrC8 &aArgs, TBool aIsWindow);
	void DestroyInstance(TInt aHandle);
private:
	friend class RAnim;
	};

/**
 *
 * Client-side handle to a server-side animation class.
 *
 * This class should be sub-classed to provide a client side interface to the server side animation DLL.
 * The server side animation DLL is derived from <code>CAnim</code>.
 *
 * @since 5.0
 * @lib "ws32.lib"
 */
class RAnim
	{
public:
	IMPORT_C virtual ~RAnim();
	IMPORT_C virtual void Close();
	IMPORT_C void Destroy();
protected:
	IMPORT_C RAnim();
	IMPORT_C RAnim(RAnimDll &aAnimDll);
	IMPORT_C TInt Construct(const RWindowBase &aDevice, TInt aType, const TDesC8 &aParams);
	IMPORT_C TInt Construct(const RWsSprite &aDevice, TInt aType, const TDesC8 &aParams);
	IMPORT_C TInt CommandReply(TInt aOpcode, const TPtrC8 &aArgs);
	IMPORT_C TInt CommandReply(TInt aOpcode);
	IMPORT_C void Command(TInt aOpcode, const TPtrC8 &aArgs);
	IMPORT_C void Command(TInt aOpcode);
private:
	TInt32 iHandle;
	RAnimDll *iAnimDll;
	};

/**
 *
 * Client-side handle to a server-side direct screen access class.
 *
 * This class provides the client-server communications for 
 * <code>CDirectScreenAccess</code>.
 *
 * @lib "ws32.lib"
 */
class RDirectScreenAccess : public MWsClientClass
	{
public:
/** Reason codes for server termination of direct screen access.
 */
	enum TTerminationReasons
		{
/** Client cancel called.
 */
		ETerminateCancel,
/** Permitted region has changed.
 */
		ETerminateRegion,
/** Screen mode has changed.
 */
		ETerminateScreenMode,
/** Screen orientation has changed.
 */
		ETerminateRotation,
		};
/** Priority values.
 */
	enum TPriority
		{
/** Very high priority.
 */
		EPriorityVeryHigh=100,
		};
public:
	IMPORT_C RDirectScreenAccess();
	IMPORT_C RDirectScreenAccess(RWsSession& aWs);
	IMPORT_C TInt Construct();
	IMPORT_C TInt Request(RRegion*& aRegion,TRequestStatus& aStatus,const RWindowBase& aWindow); 
	IMPORT_C void Completed();
	IMPORT_C void Cancel();
	IMPORT_C void Close();
private:
	RWsSession* iWs;
	RThread iWsThread;
	TRequestStatus* iAborted;
	TRequestStatus* iAbortedBackup;
	};

/**
 *
 * Mixin class for calling back direct screen access clients
 * when direct screen access should be aborted.
 *
 * @lib "ws32.lib"
 */
class MAbortDirectScreenAccess
	{
public:

/**
 *
 * Called when circumstances invalidate direct screen access.
 *
 * @param      "RDirectScreenAccess::TTerminationReasons aReason"
 *             The reason why direct screen access has to be aborted.
 */
	virtual void AbortNow(RDirectScreenAccess::TTerminationReasons aReason)=0;
	};

/**
 *
 * Mixin class for calling back direct screen access clients
 * when direct screen access can be restarted.
 *
 * @lib "ws32.lib"
 */
class MDirectScreenAccess : public MAbortDirectScreenAccess
	{
public:

/**
 *
 * Called when direct screen access can be restarted.
 *
 * @param      "RDirectScreenAccess::TTerminationReasons aReason"
 *             The reason why direct screen access was previously aborted.
 */
	virtual void Restart(RDirectScreenAccess::TTerminationReasons aReason)=0;
	};

/**
 *
 * Application direct screen access class.
 *
 * @lib "ws32.lib"
 */
class CDirectScreenAccess : public CActive
	{
public:
	IMPORT_C static CDirectScreenAccess* NewL(RWsSession& aWs,CWsScreenDevice& aScreenDevice,RWindowBase& aWindow,MDirectScreenAccess& aAbort);
	~CDirectScreenAccess();
	IMPORT_C void StartL();
	inline CFbsBitGc* Gc();
	inline CFbsScreenDevice*& ScreenDevice();
	inline RRegion* DrawingRegion();
private:
	enum TFlags
		{
		EDirectCheckModeChange=0x1,
		EDirectCheckSizeModeChange=0x2,
		};
private:
	inline CDirectScreenAccess(RWsSession& aWs,CWsScreenDevice* aScreenDevice,RWindowBase& aWindow,MDirectScreenAccess& aAbort);
	void ConstructL(RWsSession& aWs);
	void CreateScreenObjectsL(TDisplayMode aCurrentMode);
	void UpdateSizeAndRotation(CFbsBitGc* aGc);
	static TInt Restart(TAny* aDirect);
	void Restart();
	//Pure virtual functions from CActive
	void DoCancel();
	void RunL();
private:
	CFbsBitGc* iGc;
	CFbsScreenDevice* iScreenDevice;
	RRegion* iDrawingRegion;
	RWindowBase& iWindow;
	CWsScreenDevice* iWsScreenDevice;
	MDirectScreenAccess& iAbort;
	RDirectScreenAccess iDirectAccess;
	RDirectScreenAccess::TTerminationReasons iReason;
	CIdle* iRestart;
	TSize iScreenSize;
	TBool iAborting;
	TUint iFlags;
	};

/**
 *
 * Key and pen event feedback plugin client class.
 *
 * @lib "ws32.lib"
 */
class RSoundPlugIn : public MWsClientClass
	{
public:
/** Error code indicating that the plugin has been changed.
 */
	enum {ESoundWrongPlugIn=KMinTInt};
public:
	IMPORT_C RSoundPlugIn();
	IMPORT_C RSoundPlugIn(RWsSession &aWs);
	IMPORT_C TInt Construct(TUid aUid=KNullUid);
	IMPORT_C void Close();
	IMPORT_C void Destroy();
	IMPORT_C TBool IsLoaded(TBool& aIsChangeable);
	IMPORT_C TInt Unload();
	IMPORT_C TInt Load(const TDesC &aFileName);
	IMPORT_C void SetKeyClick(TBool aEnabled);
	IMPORT_C void SetPenClick(TBool aEnabled);
	IMPORT_C TBool KeyClickEnabled();
	IMPORT_C TBool PenClickEnabled();
	IMPORT_C TInt CommandReply(TInt aOpcode, const TPtrC8 &aArgs);
	};

/**
 *
 * Gets the server side handle for the object.
 *
 * @returns   "TInt"
 *            The server-side handle for the object.
 */
inline TInt MWsClientClass::WsHandle() const
	{return(iWsHandle);}

/**
 *
 * Creates a window graphics context for this device.
 *
 * @param     "CWindowGc*& aGc"
 *            On successful return, contains a new graphics context referring to this screen device.
 * @returns   "TInt"
 *            <code>KErrNone</code> if successful, otherwise one of the system-wide error codes.
 */
inline TInt CWsScreenDevice::CreateContext(CWindowGc *&aGc)
	{return(CreateContext((CGraphicsContext *&)aGc));}

/**
 *
 * Gets the handle of the window which is the target of the redraw event.
 *
 * This is the handle that was passed to the window's <code>Construct()</code> function:
 * typically it will be a pointer to the object owning the window, providing access to its member functions.
 *
 * @returns   "TUint"
 *            The window's handle.
 */
inline TUint TWsRedrawEvent::Handle() const
	{return(iHandle);}

/**
 *
 * Get rectangle to redraw.
 *
 * @returns   "TRect"
 *            The rectangle that requires redrawing.
 *            Co-ordinates are relative to the window whose handle is given by <code>Handle()</code>.
 */
inline TRect TWsRedrawEvent::Rect() const
	{return(iRect);}

/**
 *
 * Gets the pointer event.
 *
 * This function can be used to get information about the pointer event
 * if <code>Type()</code> returns an event of type <code>EEventPointer</code>. or <code>EEventDragDrop</code>.
 *
 * @returns   "TPointerEvent*"
 *            Structure containing pointer event data.
 */
inline TPointerEvent *TWsEvent::Pointer() const
	{return((TPointerEvent *)&iEventData);}

/**
 *
 * Gets the key event.
 *
 * This function can be used to get information about the key event
 * if <code>Type()</code> returns an event of type <code>EEventKey</code>, <code>EEventKeyUp</code> or <code>EEventKeyDown</code>.
 *
 * @returns   "TKeyEvent*"
 *            Structure containing key event data
 */
inline TKeyEvent *TWsEvent::Key() const
	{return((TKeyEvent *)&iEventData);}

/**
 *
 * Gets modifier changed event.
 *
 * This function can be used to get information about the modifier changed event
 * if <code>Type()</code> returns an event of type <code>EEventModifiersChanged</code>.
 *
 * @returns   "TModifiersChangedEvent*"
 *            Structure containing modifier changed event data
 */
inline TModifiersChangedEvent *TWsEvent::ModifiersChanged() const
	{return((TModifiersChangedEvent *)&iEventData);}

/**
 *
 * Gets an error event.
 *
 * This function can be used to get information about the error event
 * if <code>Type()</code> returns an event of type <code>EEventErrorMessage</code>.
 *
 * @returns   "TWsErrorMessage"
 *            The error event.
 */
inline TWsErrorMessage *TWsEvent::ErrorMessage() const
	{return((TWsErrorMessage *)&iEventData);}

/**
 *
 * Gets information about the event.
 *
 * This function gives you direct access to the event data as a whole. The event can be a keyboard or pen event or it could be a new
 * special event that only you and another application know about. You are limited to <code>EWsEventDataSize</code> bytes worth of data.
 *
 * @returns   "TUint8*"
 *            A pointer to the event data.
 */
inline TUint8 *TWsEvent::EventData() const
	{return((TUint8 *)&iEventData);}

/**
 *
 * Gets the type of event that occurred.
 *
 * @returns   "TInt"
 *            The event type. Event types are defined in <code>TEventCode</code>.
 */
inline TInt TWsEvent::Type() const
	{return(iType);}

/**
 *
 * Gets the window handle.
 *
 * This is the handle that was passed to the window's <code>Construct()</code> function:
 * typically it will be a pointer to the client-side object owning the window, providing access to its member functions.
 *
 * @returns   "TUint"
 *            The window handle.
 */
inline TUint TWsEvent::Handle() const
	{return(iHandle);}

/**
 *
 * Gets the time when the event occurred.
 *
 * @returns   "TTime"
 *            The time when the event occurred.
 */
inline TTime TWsEvent::Time() const
	{return(iTime);}

/**
 *
 * Sets event type.
 *
 * @param     "TInt aType"
 *            The event type. Event types are defined in <code>TEventCode</code>.
 */
inline void TWsEvent::SetType(TInt aType)
	{iType=aType;}

/**
 *
 * Sets the event handle.
 *
 * This is the client handle of the window that is being sent the event.
 *
 * @param     "TUint aHandle"
 *            The event handle.
 */
inline void TWsEvent::SetHandle(TUint aHandle)
	{iHandle=aHandle;}

/**
 *
 * Sets the event time to current time.
 *
 */
inline void TWsEvent::SetTimeNow()
	{iTime.HomeTime();}

/**
 *
 * Gets the handle for the window group which added the priority key.
 *
 * This is the handle that was passed to the window group's <code>Construct()</code> function.
 * Since most applications have only one window group, however, this function is rarely used.
 *
 * @returns   "TUint"
 *            The window group handle.
 */
inline TUint TWsPriorityKeyEvent::Handle() const
	{return(iHandle);}

/**
 *
 * Gets the priority key event.
 *
 * @returns   "TKeyEvent*"
 *            Structure containing priority key event data
 */
inline TKeyEvent *TWsPriorityKeyEvent::Key() const
	{return((TKeyEvent *)&iEventData);}

/**
 *
 * Sets the window group event handle.
 *
 * This is the client handle of the window that is being sent the event.
 *
 * @param     "TUint aHandle"
 *            The event handle.
 */
inline void TWsPriorityKeyEvent::SetHandle(TUint aHandle)
	{iHandle=aHandle;}

inline CDirectScreenAccess::CDirectScreenAccess(RWsSession& aWs,CWsScreenDevice* aScreenDevice,RWindowBase& aWindow,MDirectScreenAccess& aAbort)
		:CActive(RDirectScreenAccess::EPriorityVeryHigh), iWindow(aWindow), iAbort(aAbort), iDirectAccess(aWs)
		{iWsScreenDevice=aScreenDevice;}

/**
 *
 * Get a graphics context to use for drawing.
 *
 * @returns   "CFbsBitGc*"
 *            A graphics context for use only while direct screen access is valid.
 *            Ownership is not transferred.
 */
inline CFbsBitGc* CDirectScreenAccess::Gc()
	{ return iGc; }

/**
 *
 * Get a screen device to use for screen information.
 *
 * @returns   "CFbsScreenDevice*&"
 *            Screen device for use only while direct screen access is valid.
 *            Ownership is not transferred.
 */
inline CFbsScreenDevice*& CDirectScreenAccess::ScreenDevice()
	{ return iScreenDevice; }

/**
 *
 * Get the region that it is valid to draw to.
 *
 * @returns   "RRegion*"
 *            Pointer to a region. Ownership is not transferred.
 */
inline RRegion* CDirectScreenAccess::DrawingRegion()
	{ return iDrawingRegion; }

#endif
