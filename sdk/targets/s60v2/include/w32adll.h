// W32ADLL.H
//
// Copyright (c) Symbian Software Ltd 1995 - 2005. All rights reserved.
//

// Header for writing animated DLL add ons
//

#if !defined(__W32ADLL_H__)
#define __W32ADLL_H__

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__BITSTD_H__)
#include <bitstd.h>
#endif

/**
@publishedAll
@deprecated
*/
const TUint KWservAnimDllUidValue8=268435858;

/**
@publishedAll
@deprecated
*/
const TUid KWservAnimDllUid8={KWservAnimDllUidValue8};

/**
@publishedAll
@released
*/
const TUint KWservAnimDllUidValue16=268450594;

/**
@publishedAll
@released
*/
const TUid KWservAnimDllUid16={KWservAnimDllUidValue16};
#if defined(_UNICODE)

/**
@publishedAll
@released
*/
const TUint KWservAnimDllUidValue=KWservAnimDllUidValue16;
#else
const TUint KWservAnimDllUidValue=KWservAnimDllUidValue8;
#endif

/**
@publishedAll
@released
*/
const TUid KWservAnimDllUid={KWservAnimDllUidValue};

//
// Contains functions callable from animated DLLs
//


class TWindowInfo
/** Animation window information.

Stores the window position and display mode for the animation.
During a redraw of the animation window, the redraw regions
can be retrieved by calling GetRedrawRegionAndRedrawShadowRegion().

@publishedAll 
@released
@see TWindowInfo::GetRedrawRegionAndRedrawShadowRegion() */
	{
public:
	/** The screen position. */
	TRect iScreenPos;
	/** The display mode.
	
	This is the minimum display mode that the screen has to be in to display this window. */
	TDisplayMode iMode;
public:
	/** Constructs an animation window information object. */
	inline TWindowInfo() : iRegionPair(NULL) {}
public:
	/** Stores a pair of region pointers. */
	struct TRegionPair
		{
		const TRegion* iRegion1;
		const TRegion* iRegion2;
		};
	/** Returns the current redraw region and redraw shadow region.
	This function must only be called from an override of CWindowAnim's pure virtual Redraw function.
	The region pointers retrieved must not be used beyond the end of the Redraw override.
	@param aRedrawRegion The redraw region in screen coordinates.
	@param aRedrawShadowRegion The redraw shadow region in screen coordinates. */
	inline void GetRedrawRegionAndRedrawShadowRegion(const TRegion*& aRedrawRegion, const TRegion*& aRedrawShadowRegion) const
		{
		if (iRegionPair)
			{
			aRedrawRegion=iRegionPair->iRegion1;
			aRedrawShadowRegion=iRegionPair->iRegion2;
			iRegionPair=NULL;
			}
		else
			{
			aRedrawRegion=NULL;
			aRedrawShadowRegion=NULL;
			}
		}
private:
	mutable const TRegionPair* iRegionPair;
	TAny *iFree2;
	friend class CWsAnim;
	};


class MEventHandler
/** Event handler interface.

The interface provides a function to handle raw events, e.g. key presses, 
pen events, power buttons etc. Raw events are passed to the OfferRawEvent() 
function when the MAnimGeneralFunctions::GetRawEvents() function has been 
called.

@publishedAll
@released */
	{
public:
	/** Handles raw events. 
	
	If the incoming event can be handled, the function should 
	process it and then return true. If it cannot be processed the function should 
	return false, and the event will be passed to other event handling code.
	
	This function must be implemented in every animation DLL. If event 
	handling is not required, the function should simply return false.
	
	@param aRawEvent The raw event to be processed
	@return ETrue if the raw event is handled by this function, EFalse if the function 
	chooses not to process it. */
	virtual TBool OfferRawEvent(const TRawEvent &aRawEvent)=0;
	};


class MAnimGeneralFunctions
/** General animation utility functions interface. 

The interface provides functions to set the animation timing, 
event functions, and other general functions.

You do not have to create an object of this type. The class is implemented 
by the window server and provides utility functions to all CAnim-derived 
classes via the CAnim::iFunctions pointer.

It is not intended for user derivation.

@publishedAll
@released */
	{
public:
	/** Animation synchronisation flags. 
	
	The animation can be synchronised to any of these values; 
	the Animate() call will take place at the start of the new unit (day, hour, etc...). */
	enum TAnimSync
		{
		/** Not synchronised. Animate() is called after some number of flash cycles - 
		set by SetSync(). */
		ESyncNone,
		/** Animate() every flash tick. This occurs twice a second, on the second and after 
		7/12ths of a second, e.g. the function is called in a flash-on (7/12 seconds) - 
		flash-off (5/12 seconds) cycle. */
		ESyncFlash,
		/** Animate() called as soon after every second as system activity allows. */
		ESyncSecond,
		/** Animate() called as soon after every minute as system activity allows. */
		ESyncMinute,
		/** Animate() called as soon after midnight every day as system activity allows. */
		ESyncDay,
		};
	enum
		{
		EWindowExtensionInterface=1,
		};
	//Timing functions
	/** Calls the DLL's Animate() function then deactivates the graphics context. 
	
	This allows users to do drawing from their own active object.
	
	Note:
	
	If the user calls the CAnim-derived classes' Animate() function directly, 
	or otherwise does drawing from their own active object, then this will not 
	deactivate the graphics context. This causes the window server to panic the 
	client.
	
	Alternatively, use CFreeTimerWindowAnim, which allows you to deactivate the 
	graphics context yourself.
	
	@param aDateTime The parameter passed into the animation DLL's Animate() 
	function. */
	virtual void Animate(TDateTime *aDateTime)=0;
	/** Sets the synchronisation mode. 
	
	This determines the time intervals between calls to the Animate() function.
	
	@param aSyncMode The synchronisation mode. */
	virtual void SetSync(TAnimSync aSyncMode)=0;
	/** Sets the repeat interval. 
	
	If the synchronisation mode is TAnimSync::ESyncNone, then the Animate() function 
	is called at intervals defined by some number of flash ticks. There are two 
	flash ticks a second, with a 7/12 second - 5/12 second cycle. If the function 
	is called when the synchronisation mode is not TAnimSync::ESyncNone, then 
	the window server panics the client.
	
	If the new interval is greater than the current countdown, then the call does 
	not affect the current countdown. For example, if the countdown has 10 flash 
	ticks remaining, and the interval is set to 20, the new interval does not 
	apply until the current countdown is complete. 
	
	However if the new interval is less the current countdown, then the new interval 
	applies immediately i.e. the countdown is reset to the interval value.
	
	If the interval is set to zero the countdown stops, and the Animate() function 
	is no longer called.
	
	@param aInterval The number of flash ticks between calls to the Animate() 
	function. */
	virtual void SetInterval(TInt aInterval)=0;
	/** Sets the next interval. 
	
	This function immediately resets the current countdown to the specified number 
	of flash ticks, irrespective of its current value. After the countdown expires, 
	the interval returns to its usual rate. Note that this may be zero (i.e. 
	not at all).
	
	To call this function, the synchronisation mode must be TAnimSync::ESyncNone, 
	otherwise the window server panics the client.
	
	Note: there are two flash ticks a second, with a 7/12 second - 5/12 second cycle.
	
	@param aInterval The interval to the next Animate(). If the value is less 
	than 1, it automatically gets set to 1.
	@see SetInterval() */
	virtual void SetNextInterval(TInt aInterval)=0;
	/** Gets the system time as it was when Animate() was last called.
	
	@return The system time when Animate() was last called. */
	virtual TDateTime SystemTime() const=0;
	/** Tests the flash cycle state. 
	
	The flash cycle has 2 states: on (7/12 second) or off (5/12 second).
	
	@return ETrue if in the on part of the flash cycle, otherwise EFalse. */
	virtual TBool FlashStateOn() const=0;
	/** Gets the current synchronisation mode.
	
	@return The current sync mode. */
	virtual TAnimSync Sync() const=0;
	//Other functions generally useful
	/** Gets a pointer to the screen device. 
	
	For example, this might be used to gain access to twips to pixel conversion functions.
	
	@return A pointer to the screen device. */
	virtual const CFbsScreenDevice *ScreenDevice()=0;
	/** Creates and duplicates a bitmap from a handle. 
	
	This function might be used to duplicate client side bitmaps on the server side.
	
	@param aHandle A handle to the bitmap to be duplicated.
	@return A pointer to the duplicate bitmap. */
	virtual CFbsBitmap *DuplicateBitmapL(TInt aHandle)=0;
	/** Creates and duplicates a font from a handle.
	
	This function might be used to duplicate client side fonts on the server side.
	
	@param aHandle A handle to the font to be duplicated.
	@return A pointer to the duplicate font. */
	virtual CFbsFont *DuplicateFontL(TInt aHandle)=0;
	/** Closes a duplicate font.
	
	@param Pointer to the duplicate font.
	@see DuplicateFontL() */
	virtual void CloseFont(CFbsFont *)=0;
	/** Gets a reference to the calling client's thread.
	
	@return A reference to the calling client's thread. */
	virtual const RThread &Client()=0;
	virtual void ReplyBuf(const TDesC8 &aDes)=0;				// Reply a buffer to the client
#if defined(_UNICODE)
	virtual void ReplyBuf(const TDesC16 &aDes)=0;				// Reply a buffer to the client
#endif
	/** Panics the client. 
	
	This will result in the client thread being destroyed. */
	virtual void Panic() const=0;
	//Event functions
	/** Switches animation raw event handling on and off.
	
	If raw event handling is switched on, then raw events, e.g. pointer, key, or power events
	are all offered to the animation event handling code's MEventHandler::OfferRawEvent().
	
	@param aGetEvents If ETrue, raw events are passed to the animation 
	event handling code. If EFalse, events are not passed to the animation. */
	virtual void GetRawEvents(TBool aGetEvents) const=0;
	/** Posts a raw event, just as if it had come from the kernel.
	
	@param aRawEvent The raw event */
	virtual void PostRawEvent(const TRawEvent &aRawEvent) const=0;
	/** Posts a key event.
	
	The function is similar to PostRawEvent() but should be 
	used for posting key events. 
	
	@param aRawEvent The key event. */
	virtual void PostKeyEvent(const TKeyEvent &aRawEvent) const=0;
	/** Get the address of an object which can retrieve information from and send
	information to the client-side.

	@return A pointer to RMessagePtr2. Complete must be called on the returned object (or a 
	copy of it) if and only if Message is called from an override of CAnim's CommandReplyL which 
	has been caused by a client-side RAnim::AsyncCommandReply call. If Message is called outside 
	an override of CAnim's CommandReplyL or outside an override of CWindowAnim's ConstructL or 
	CSpriteAnim's ConstructL, the it returns NULL. 
	@see RMessagePtr2 */
	virtual const RMessagePtr2* Message()=0; // replaces Reserved1
	virtual TAny* ExtendedInterface(TInt aInterface)=0; // replaces Reserved2
	private:
#if defined(__BC_FUTURE_PROOFING__)
	virtual void Reserved1() const;
	virtual void Reserved2() const;
	virtual void Reserved3() const;
#endif
	};

class MAnimGeneralFunctionsWindowExtension
/** General Window utility functions interface. 

The member functions define the interface for querying and manipulating 
the window and screen attributes.

You obtain one by calling: iFunctions->ExtendedInterface(MAnimGeneralFunctions::EWindowExtensionInterface) 
and casting the result.

It is not intended for user derivation.

@publishedAll 
@released */
	{
public:
	/** Class contains the information pertaining to a window group: name, priority, 
	focusability. */
	class TWindowGroupInfo
		{
	public:
	/** Window is focusable flag. */
		enum
			{
			EIsFocusable=0x0001,
			};
	public:
	/** Function returns the ability of focus. Returns ETrue if focusable else returns EFalse. */
		inline TBool IsFocusable() const {return iFlags&EIsFocusable;}
	public:
	/** Window group attributes. */
		TInt iId;
		TUint32 iFlags;
		TInt iOrdinalPriority;
		TInt iNameLength;
		TInt iParentId;
		};
public:
	/** This function returns the total number of screens. */
	virtual TInt Screens() const=0;

	/** This function returns the screen number, which is presently in focus. */
	virtual TInt FocusScreens() const=0;

	/* This function changes the focused screen.

	@param aScreenNo				Screen number. */
	virtual void SetFocusScreen(TInt aScreenNo)=0;

	/** This function returns the number of window groups available for the specified screen.

	@param aScreen The screen number.
	@return The number of window groups. */
	virtual TInt WindowGroups(TInt aScreen) const=0;
	
	/** This function takes a screen number and an ordinal position and returns the complete window 
	groups information of the specified window. If the window group does not exist the function returns EFalse.
	
	Note: The ordinal position specified should be the total or full ordinal position of all group windows
	of all priorities on that screen.

	@param aInfo   					Complete window information.
	@param aScreen 					Screen number.
	@param aFullordinalPosition 	Ordinal position of the window.
	@return ETrue if window group info exist, EFalse otherwise.  */
	virtual TBool WindowGroupInfo(TWindowGroupInfo& aInfo,TInt aScreen,TInt aFullOrdinalPosition) const=0;

	/** This functions takes a screen number and an ordinal position and returns the window group name.
	If the window group does not exist the function returns false.

	Note: The ordinal position specified should be the total or full ordinal position of all group windows 
	of all priorities on that screen.

	Note: If the name does not fit into the descriptor provided then it will be truncated.

	@param aWindowName 				Window name.
	@param aScreen 					Screen number.
	@param aFullordinalPosition 	Ordinal position of the window.
	@return ETrue if window group name exist, EFalse otherwise. */
	virtual TBool WindowGroupName(TPtrC& aWindowName,TInt aScreen,TInt aFullOrdinalPosition) const=0;
	
	/** This function changes the ordinal position and priority of the window group with specified id.

	@param aWindowGroupId 			Window group id.
	@param aPos 					Ordinal position to move the window to.
	@param aOrdinalPriority 		New ordinal priority or the window.
	@return KErrNotExist if there is no window group with the specified Id, KErrNone otherwise. */
	virtual TInt SetOrdinalPosition(TInt aWindowGroupId,TInt aPos,TInt aOrdinalPriority)=0;
private:
	virtual void Reserved1() const;
	virtual void Reserved2() const;
	virtual void Reserved3() const;
	virtual void Reserved4() const;
	};

class MAnimWindowFunctions
/** Window utility functions interface. 

The member functions define the interface for querying and manipulating 
the window in which the animation takes place.

You do not have to create an object of this type. The class is implemented 
by the window server, and provides these utility functions to all CWindowAnim 
and CFreeTimerWindowAnim derived classes via the iWindowFunctions pointer.

It is not intended for user derivation.

@publishedAll 
@released */
	{
public:
	/** Activates the graphics context.
	
	This function should be called to enable drawing in the CAnim-derived classes'
	Command(), CommandReplyL(), Animate(), or FocusChanged() functions.
	
	Note: this function is called automatically by the animation DLL framework in the 
	Redraw() function. */
	virtual void ActivateGc()=0;
	/** Sets the rectangle that this animation is to draw to.
	
	This function must be called as part of the initialisation/construction of 
	the CAnim-derived object, i.e. in CAnim::ConstructL(). This is so that the 
	window server knows which area the animation is operating in.
	
	@param aRect The rectangle to be drawn to. */
	virtual void SetRect(const TRect &aRect)=0;
	/** Gets the window size.
	
	@return The window size, in pixels. */
	virtual TSize WindowSize() const=0;
	/** Tests whether to draw the animation. 
	
	If the window is completely hidden, there is normally no need to draw 
	the animation. However in some conditions the animation should be drawn even 
	if it is obscured. The window server is aware of these cases, and returns 
	ETrue if it is not safe to draw the animation.
	
	@return True if the window is completely hidden and there is no requirement 
	to continue drawing the animation, otherwise false. */
	virtual TBool IsHidden()=0;
	/** Sets the visibility of the window the animation is drawing to.
	
	This does the same as RWindowBase::SetVisible().
	
	@param aState True for visible, false otherwise. */
	virtual void SetVisible(TBool aState)=0;
	/** Forces a redraw of a rectangular part of the window.
	
	The function causes a redraw message on the part of the window specified, 
	which provides a non-immediate way to do drawing.
	
	It can be used to redraw the whole of the window, not just the part used by 
	the animation.
	
	@param aRect The rectangle to be redrawn. These co-ordinates are relative 
	to the origin of the window. */
	virtual void Invalidate(const TRect &aRect)=0;
	/** Gets window information.
	
	@param aData The window information. */
	virtual void Parameters(TWindowInfo &aData)=0;
	/** Gets the visible region.

	This region is the area of the visible window which 
	is currently unshadowed. If there is not enough memory to calculate this region 
	then aRegion's error flag is set.
	
	@param aRegion The visible region. */
	virtual void VisibleRegion(TRegion& aRegion)=0;
	//virtual void CopyScreen(CFbsBitGc *aBitmapGc,TRect aRect)=0;
private:
	virtual void Reserved() const;
#if defined(__BC_FUTURE_PROOFING__)
	virtual void Reserved1() const;
	virtual void Reserved2() const;
	virtual void Reserved3() const;
#endif
	};


class MAnimFreeTimerWindowFunctions : public MAnimWindowFunctions
/** Free timer animation utility functions interface.

The class inherits functions from MAnimWindowFunctions, and defines the additional 
interface required for window operations which support animations with their 
own timers.

You do NOT have to create an object of this type. The class is implemented 
by the window server, and provides utility functions to all CFreeTimerWindowAnim 
derived classes via the WindowFunctions() member. 

It is not intended for user derivation.

@publishedAll 
@released */
	{
public:
	/** Deactivates the graphics context. 
	
	This function is used in the context of a CFreeTimerWindowAnim derived class 
	when writing animation DLLs with their own timer. Within the timer's RunL(), 
	the ActivateGc() function should be called prior to drawing to the window. 
	DeactivateGc() should be called after drawing is finished. */
	virtual void DeactivateGc()=0;
	/** Forces the screen to update. */
	virtual void Update()=0;
private:
	virtual void Reserved3() const;
	};

class MAnimSpriteFunctions
/** Sprite animation utility functions interface.

The interface includes functions for querying and manipulating a sprite.

You do NOT have to create an object of this type. The class is implemented 
by the window server, and provides utility functions to all CSpriteAnim derived 
classes via the CSpriteAnim::iSpriteFunctions pointer. 

It is not intended for user derivation.

@publishedAll 
@released */
	{
public:
	/** Gets sprite member data.
	
	Each member of the sprite is effectively a bitmap, which is displayed for a 
	different amount of time.
	
	@param aMember The index of the sprite member for which information is required.
	@return A pointer to the sprite member. */
	virtual TSpriteMember *GetSpriteMember(TInt aMember) const=0;
	/** Redraws part of a sprite.
	
	The updates a sprite on the screen, possibly after the bitmap for a particular 
	sprite member has been changed.
	
	Two types of redraw are possible. A full update takes the bitmap off the screen 
	and then re-draws it. This is 'safe' in that the screen always reflects 
	the contents of the sprite bitmap. However it can result in flicker. Use the 
	aRect parameter to specify the (small) part of the sprite which has been changed, 
	then any flicker will only occur in this rectangle. 
	
	A full update is required if you have removed pixels from the mask, i.e. made 
	pixels in the sprite transparent when they were not before. If drawing is 
	additive, e.g. you are using a mask or the draw mode is EDrawModePEN, a partial 
	update is possible. Otherwise the aFullUpdate argument is ignored and a full 
	update is always done.
	
	Note: if the sprite member aMember is not visible then there is no need for a change 
	to the display, so the aRect and aFullUpdate parameters are ignored.
	
	@param aMember The index of the sprite member that is to be updated.
	@param aRect The part of the sprite member which has changed.
	@param aFullUpdate ETrue for a full update, EFalse otherwise. */
	virtual void UpdateMember(TInt aMember,const TRect& aRect,TBool aFullUpdate)=0;
	/** Turns a sprite on or off.
	
	In effect this makes the sprite bitmap visible.
	
	@param aActive ETrue to turn sprite on. EFalse to turn it off. */
	virtual void Activate(TBool aActive)=0;
	/** Finishes constructing the sprite.
	
	It also sets the currently displayed sprite member to zero.
	
	This function must be called after members change size. */
	virtual void SizeChangedL()=0;
	/** Set the sprite's position.
	
	@param aPos The new position of the sprite. */
	virtual void SetPosition(const TPoint &aPos)=0;
private:
	virtual void Reserved() const;
#if defined(__BC_FUTURE_PROOFING__)
public:
	/** Returns the visibility of the sprite.
	
	A sprite can be seen if it is neither obscured by another window nor hidden.
	
	@return ETrue if the sprite can be seen, EFalse otherwise. */
	virtual TBool SpriteCanBeSeen() const = 0;
private:
	virtual void Reserved2() const;
	virtual void Reserved3() const;
	virtual void Reserved4() const;
#endif
	};


class CAnimGc : public CBitmapContext
/** Animation graphics context. 

An object of this type is linked into CAnim by the window server, which allows 
you to draw to the animation window. The object's functions allow you to set 
and cancel the clipping region, and to draw to the visible window using 
the inherited CBitmapContext functions. 

@publishedAll
@released */
	{
public:
	/** Sets the clipping region.
	
	Only the parts of the animation which are within the clipping region are drawn.
	
	@param aRegion The clipping region. */
	virtual void SetClippingRegion(const TRegion &aRegion)=0;
	/** Cancels the clipping region.
	
	@see SetClippingRegion() */
	virtual void CancelClippingRegion()=0;
	};

class CWsAnim; // Forward ref for friend declaration


class CAnim : public CBase , public MEventHandler
/** Server side animated object base interface.

Animations implement this interface, which is called by the window server 
to pass commands from clients, perform a step in the animation, or to pass 
window server events (if required) so that the animation can handle them 
before the application.

The functions are all pure virtual, and must be implemented in 
the derived class to provide server side behaviour. The functions will be 
called by the window server with optional arguments passed in from the client 
side animation class RAnim.

You should derive from CWindowAnim, CFreeTimerWindowAnim or CSpriteAnim, 
depending on whether the animation is to draw to a sprite or a window,
rather than directly from this class.

The derived class is constructed in the DLL factory class CAnimDll::CreateInstanceL() 
function.

The operation to perform an animation step is called by the window server 
on a timer. The timing properties are set through an MAnimGeneralFunctions 
member, which also provides other utility functions. 

@publishedAll 
@released */
	{
public:
	/** Implements client-side initiated commands, returning a value. 
	
	The window server calls this function in response to application calls to 
	the client side command function RAnim::CommandReplyL(). The arguments passed 
	to the function by the window server are the same as were used on the client 
	side function call.
	
	This function returns values to the client side, and should be used to return 
	error codes for commands which might leave.
	
	@param aOpcode Opcode understood by the class.
	@param aArgs Arguments packaged on the client side, for example as a struct 
	of a type determined by the aOpcode argument. These mirror the aArgs argument 
	passed in to RAnim::CommandReply().
	@return Value passed back to client side function when this function completes. 
	Typically this would be KErrNone or another of the system-wide error codes. 
	However any value may be returned to the client side.
	@see RAnim */
	virtual TInt CommandReplyL(TInt aOpcode, TAny *aArgs)=0;
	/** Implements client-side initiated commands. 
	
	The window server calls this function in response to application calls to 
	the client side command function RAnim::Command(). The arguments passed to 
	the function by the window server are the same as were used on the client 
	side function call.
	
	Because this function does not return errors, it is not safe for commands 
	which might leave.
	
	@param aOpcode Opcode understood by the class
	@param aArgs Arguments packaged on the client side, for example as a struct 
	of a type determined by the aOpcode argument. These mirror the aArgs argument 
	passed in to RAnim::Command().
	@see RAnim */
	virtual void Command(TInt aOpcode, TAny *aArgs)=0;
	/** Main animation function, called by the window server. 
	
	The drawing code which implements a given animation should be provided here.
	
	This function is called at a frequency determined by the SetSync() helper 
	function. Note that if sync is not set, then this function will never be 
	called. This effect can be exploited to use the animation framework, with 
	its server side speed, for what are strictly not animations, e.g. for streaming 
	video images.
	
	The aDateTime parameter will be null if the current time (as determined by 
	the window server) matches the time implied by the sync period, modulo normalisation, 
	otherwise it will contain a valid (non-normalised) time.
	
	Normalisation is to some specified granularity, for example if one minute 
	is specified as the animation frequency, then in effect the window server 
	will decide whether the implied time is correct to the minute, but not to 
	the second.
	
	Implied time is the time implied by the (normalised) actual time of the previous 
	animation call plus the sync interval. For example if the last call was at 
	time 't' and the sync interval is 1 second then if the time at this call 
	is t + 1 second, then actual time and implied time match and the value placed 
	into aDateTime will be NULL.
	
	Cases in which the two may not match include, for example, system time having 
	been reset between animation calls (perhaps British Summer Time or other daylight 
	saving time has just come into effect). The intention is that when system 
	time changes, a mechanism is provided to alert the animation code and allow 
	it to reset itself. The assumption is that somewhere in its initialisation 
	code, the animation will have performed a CAnimFunctions utility call to set 
	a base time, which is then implicitly tracked by incrementing by a suitable 
	interval; when aDateTime is non-NULL after a call to Animate(), base time 
	should be reset.
	
	@param aDateTime Null if the current time w.r.t. the window server matches 
	the time implied by the synch period. Otherwise a valid (non-normalised) time. */
	virtual void Animate(TDateTime *aDateTime)=0;
private:
	inline CAnim() {}
#if defined(__BC_FUTURE_PROOFING__)
	virtual void Reserved1() const {};
	virtual void Reserved2() const {};
	virtual void Reserved3() const {};
#endif
protected:
	/** Pointer to a class containing functions implemented by the window server. 
	
	These are available to any CAnim derived class.
	
	Note that this value is automatically set for you by the animation framework. 
	You do not need to assign a value to this pointer. 
	@publishedAll
	@released	*/
	MAnimGeneralFunctions *iFunctions;
	friend class CWsAnim;
	friend class CWindowAnim;
	friend class CSpriteAnim;
	};


class CWindowAnim : public CAnim
/** Window animation interface. 

This interface is provided to create animations other than sprites. A window 
animation can be provided by deriving from this class.

The interface inherits from CAnim and has access to its functions. It additionally 
can access an interface for querying and manipulating the window in which 
the animation takes place, using its iWindowFunctions member.

The derived class is constructed in the DLL factory class CAnimDll::CreateInstanceL().

@publishedAll
@released 
@see CFreeTimerWindowAnim
@see CSpriteAnim */
	{
public:
	/** Server side construction and initialisation of an animation class. 
	
	Note: the aHasFocus argument allows the animation to start in a known focus state. 
	For example, an animation may or may not have focus, depending on how it was 
	started. Together with the FocusChanged() function, this allows an animation 
	to always know its focus state.
	
	@param aArgs Packaged arguments which may be required during construction. 
	These are transferred from the aParams argument of the client side constructor's 
	RAnim::Construct().
	@param aHasFocus Specifies whether or not the animation has window server focus. */
	virtual void ConstructL(TAny *aArgs, TBool aHasFocus)=0;
	/** Redraws the objects.
	
	The function is called by the window server when it needs to redraw the object. 
	The object must provide all the low level drawing code. */
	virtual void Redraw()=0;
	/** Notifies change of focus.
	
	The function is called by the window server to notify a change of focus, 
	allowing the animation code to track whether it does or does not have focus, 
	and to change its appearance accordingly.
	
	@param aState Indicates whether the focus has or has not changed. */
	virtual void FocusChanged(TBool aState)=0;
protected:
	/** Protected constructor.
	
	Prevents objects of this class being directly constructed. */
	inline CWindowAnim() {}
private:
#if defined(__BC_FUTURE_PROOFING__)
	virtual void ReservedW1() const {};
	virtual void ReservedW2() const {};
#endif
protected:
	/** Pointer to a class containing functions implemented by the window server.
	
	These are available to any CWindowAnim-derived class.
	
	Note that this and the iGc pointer are automatically set for you by the 
	animation framework - you do not need to assign a value to them.*/
	MAnimWindowFunctions *iWindowFunctions;
	/** Pointer to the graphics context. */
	CAnimGc *iGc;
	friend class CWsAnim;
	};


class CFreeTimerWindowAnim : public CWindowAnim
/** Free timer animation interface.

This interface allows animations to have their own timers or other active 
objects, and to draw to the window when the timer completes. The implication 
of this is that animations derived from this class can have an extremely short 
user-defined time between calls to the Animate() function, unlike the 
other animation classes, which are tied to the (approximately) half second 
flash cycle.

The interface inherits from CWindowAnim and has access to its functions. It 
additionally can access functions declared in the MAnimFreeTimerWindowFunctions 
interface, using WindowFunctions(). 

In order to draw to the window inside the RunL() of your own timer, you will 
need call the ActivateGc() function before doing any drawing, and the DeactivateGc() 
function after finishing the drawing.

@publishedAll 
@released 
@see CSpriteAnim */
	{
protected:
	inline MAnimFreeTimerWindowFunctions* WindowFunctions()
	/** Gets the free timer utility functions.
	
	These functions include all the MAnimWindowFunctions, 
	and additional functions to deactivate the graphics context and to force the 
	screen to update.
	
	@return A pointer to the free timer utility functions. */
		{return STATIC_CAST(MAnimFreeTimerWindowFunctions*,iWindowFunctions);}
private:
#if defined(__BC_FUTURE_PROOFING__)
	virtual void ReservedF1() const {};
#endif
	};


class CSpriteAnim : public CAnim
/** Sprite animation interface.

Sprites are bitmaps that can overlay a window or the screen. A sprite animation 
can be provided by deriving from this class.

The interface inherits from CAnim and has access to its functions. It additionally 
can access an interface for querying and manipulating a sprite, using its 
iSpriteFunctions member. 

The derived class is constructed in the DLL factory class CAnimDll::CreateInstanceL() 
function.

@publishedAll 
@released 
@see CFreeTimerWindowAnim
@see CWindowAnim */
	{
public:
	/** Server side construction and initialisation of an animation class. 
	
	@param aArgs Packaged arguments which may be required during construction. 
	These are transferred from the aParams argument of the client side constructor's 
	RAnim::Construct(). */
	virtual void ConstructL(TAny *aArgs)=0;
protected:
	inline CSpriteAnim() 
	/** Protected constructor.
	
	Ensures that only derived classes can be constructed. */
		{}
private:
#if defined(__BC_FUTURE_PROOFING__)
	virtual void ReservedS1() const {};
	virtual void ReservedS2() const {};
#endif
protected:
	/** Pointer to a class containing functions implemented by the window server.
	
	These are available to any CSpriteAnim-derived class.
	
	Note that this value is automatically set for you by the animation framework. 
	You do not need to assign a value to this pointer. */
	MAnimSpriteFunctions *iSpriteFunctions;
	friend class CWsAnim;
	};


class CAnimDll : public CBase
/** Animation DLL factory interface. 

An animation DLL class must be a derived class of CAnimDll, and can be thought 
of as a server side factory class. CAnimDll consists of a single pure virtual 
factory function, CreateInstanceL(TInt aType), which is used to create new 
instances of animation objects of type CAnim contained in the DLL. Animation 
DLL objects are created by the CreateCAnimDllL() function, which is called 
by the window server at the request of the client.

For efficiency reasons, it makes sense to collect multiple animation classes 
into a single DLL, even if they are otherwise logically quite separate classes. 

@publishedAll 
@released */
	{
public:
	/** Factory function for animation DLLs.
	
	It must be provided in the derived class.
	
	The parameter can be used to differentiate between multiple animation 
	classes contained in the same animation DLL.
	
	@param aType Identifies an animation class to be constructed. This is the 
	same value as the aType argument of the client side animation constructor 
	RAnim::Construct(). It is passed from the client side by the animation framework.
	@return Pointer to a CAnim-derived animation class object. */
	virtual CAnim *CreateInstanceL(TInt aType)=0;
	};

#endif
