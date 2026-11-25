// SMILConstants.h
//
/** @file SMILConstants.h
 * This file contains DTD-specific XML constants
 */

#ifndef __SMILCONSTANTS_H__
#define __SMILCONSTANTS_H__

#include <e32base.h>

			
const TInt KSMILElementa				= 0;
const TInt KSMILElementanchor			= 1;
const TInt KSMILElementanimation		= 2;
const TInt KSMILElementarea				= 3;
const TInt KSMILElementaudio			= 4;
const TInt KSMILElementbody				= 5;
const TInt KSMILElementhead				= 6;
const TInt KSMILElementimg				= 7;
const TInt KSMILElementlayout			= 8;
const TInt KSMILElementpar				= 9;
const TInt KSMILElementref				= 10;
const TInt KSMILElementregion			= 11;
const TInt KSMILElementroot_layout		= 12;
const TInt KSMILElementseq				= 13;
const TInt KSMILElementsmil				= 14;
const TInt KSMILElementswitch			= 15;
const TInt KSMILElementtext				= 16;
const TInt KSMILElementtextstream		= 17;
const TInt KSMILElementvideo			= 18;
const TInt KSMILElementmeta				= 19;


_LIT(KXMLVersionTag, "<?XML version=\"1.0\" ?>");
_LIT(KXMLDocTypeTag, "<!DOCTYPE smil SYSTEM \"mms_smil.dtd\">");

//Literal definitions for element names
_LIT(KXMLSMILElta, "a");
_LIT(KXMLSMILEltanchor, "anchor");
_LIT(KXMLSMILEltanimation, "animation");
_LIT(KXMLSMILEltarea, "area");
_LIT(KXMLSMILEltaudio, "audio");
_LIT(KXMLSMILEltbody, "body");
_LIT(KXMLSMILElthead, "head");
_LIT(KXMLSMILEltimg, "img");
_LIT(KXMLSMILEltlayout, "layout");
_LIT(KXMLSMILEltpar, "par");
_LIT(KXMLSMILEltref, "ref");
_LIT(KXMLSMILEltregion, "region");
_LIT(KXMLSMILEltroot_layout, "root-layout");
_LIT(KXMLSMILEltseq, "seq");
_LIT(KXMLSMILEltsmil, "smil");
_LIT(KXMLSMILEltswitch, "switch");
_LIT(KXMLSMILElttext, "text");
_LIT(KXMLSMILElttextstream, "textstream");
_LIT(KXMLSMILEltvideo, "video");
_LIT(KXMLSMILEltmeta, "meta");

//Literal definitions for attribute names
_LIT(KXMLSMILAttAbstract, "abstract");
_LIT(KXMLSMILAttAccessKey, "accesskey");
_LIT(KXMLSMILAttActuate, "actuate");
_LIT(KXMLSMILAttAlt, "alt");
_LIT(KXMLSMILAttAuthor, "author");
_LIT(KXMLSMILAttBackground_color, "background-color");
_LIT(KXMLSMILAttBackgroundColor, "backgroundColor");
_LIT(KXMLSMILAttBegin, "begin");
_LIT(KXMLSMILAttBottom, "bottom");
_LIT(KXMLSMILAttClass, "class");
_LIT(KXMLSMILAttClipBegin, "clipBegin");
_LIT(KXMLSMILAttClipEnd, "clipEnd");
_LIT(KXMLSMILAttClose, "close");
_LIT(KXMLSMILAttContent, "content");
_LIT(KXMLSMILAttCoords, "coords");
_LIT(KXMLSMILAttCopyright, "copyright");
_LIT(KXMLSMILAttCustomTest, "customTest");
_LIT(KXMLSMILAttDestinationLevel, "destinationLevel");
_LIT(KXMLSMILAttDestinationPlaystate, "destinationPlaystate");
_LIT(KXMLSMILAttDur, "dur");
_LIT(KXMLSMILAttEnd, "end");
_LIT(KXMLSMILAttEndsync, "endsync");
_LIT(KXMLSMILAttExternal, "external");
_LIT(KXMLSMILAttFill, "fill");
_LIT(KXMLSMILAttFit, "fit");
_LIT(KXMLSMILAttHeight, "height");
_LIT(KXMLSMILAttHRef, "href");
_LIT(KXMLSMILAttId, "id");
_LIT(KXMLSMILAttLeft, "left");
_LIT(KXMLSMILAttLongDesc, "longdesc");
_LIT(KXMLSMILAttMax, "max");
_LIT(KXMLSMILAttMin, "min");
_LIT(KXMLSMILAttName, "name");
_LIT(KXMLSMILAttNoHRef, "nohref");
_LIT(KXMLSMILAttOpen, "open");
_LIT(KXMLSMILAttRegion, "region");
_LIT(KXMLSMILAttRepeatCount, "repeatCount");
_LIT(KXMLSMILAttRepeatDur, "repeatDur");
_LIT(KXMLSMILAttRight, "right");
_LIT(KXMLSMILAttShape, "shape");
_LIT(KXMLSMILAttShow, "show");
_LIT(KXMLSMILAttShowBackground, "showBackground");
_LIT(KXMLSMILAttSkipContent, "skip-content");
_LIT(KXMLSMILAttSourceLevel, "sourceLevel");
_LIT(KXMLSMILAttSourcePlaystate, "sourcePlaystate");
_LIT(KXMLSMILAttSrc, "src");
_LIT(KXMLSMILAttSystem_bitrate, "system-bitrate");
_LIT(KXMLSMILAttSystem_captions, "system-captions");
_LIT(KXMLSMILAttSystem_language, "system-language");
_LIT(KXMLSMILAttSystem_overdub_or_caption, "system-overdub-or-caption");
_LIT(KXMLSMILAttSystem_required, "system-required");
_LIT(KXMLSMILAttSystem_screen_depth, "system-screen-depth");
_LIT(KXMLSMILAttSystem_screen_size, "system-screen-size");
_LIT(KXMLSMILAttSystemAudioDesc, "systemAudioDesc");
_LIT(KXMLSMILAttSystemBitrate, "systemBitrate");
_LIT(KXMLSMILAttSystemCPU, "systemCPU");
_LIT(KXMLSMILAttSystemCaptions, "systemCaptions");
_LIT(KXMLSMILAttSystemComponent, "systemComponent");
_LIT(KXMLSMILAttSystemLanguage, "systemLanguage");
_LIT(KXMLSMILAttSystemOperatingSystem, "systemOperatingSystem");
_LIT(KXMLSMILAttSystemOverdubOrSubtitle, "systemOverdubOrSubtitle");
_LIT(KXMLSMILAttSystemRequired, "systemRequired");
_LIT(KXMLSMILAttSystemScreenDepth, "systemScreenDepth");
_LIT(KXMLSMILAttSystemScreenSize, "systemScreenSize");
_LIT(KXMLSMILAttTabIndex, "tabindex");
_LIT(KXMLSMILAttTarget, "target");
_LIT(KXMLSMILAttTitle, "title");
_LIT(KXMLSMILAttTop, "top");
_LIT(KXMLSMILAttType, "type");
_LIT(KXMLSMILAttWidth, "width");
_LIT(KXMLSMILAttXMLLang, "xml:lang");
_LIT(KXMLSMILAttXMLns, "xmlns");
_LIT(KXMLSMILAttZIndex, "z-index");

// Literals for allowed values for the actuate attribute
_LIT(KXMLSMILAttValActuateOnRequest, "onRequest");
_LIT(KXMLSMILAttValActuateOnLoad, "onLoad");

// Literals for allowed values for the close attribute
_LIT(KXMLSMILAttValCloseNever, "never");
_LIT(KXMLSMILAttValCloseWhenNotActive, "whenNotActive");

// Literals for allowed values for the destinationPlaystate attribute
_LIT(KXMLSMILAttValDestinationPlaystatePlay, "play");
_LIT(KXMLSMILAttValDestinationPlaystatePause, "pause");
_LIT(KXMLSMILAttValDestinationPlaystateStop, "stop");

// Literals for allowed values for the endsync attribute
_LIT(KXMLSMILAttValEndsyncFirst, "first");
_LIT(KXMLSMILAttValEndsyncLast, "last");
_LIT(KXMLSMILAttValEndsyncAll, "all");
_LIT(KXMLSMILAttValEndsyncIDREF, "IDREF");

// Literals for allowed values for the external attribute
_LIT(KXMLSMILAttValExternalTrue, "true");
_LIT(KXMLSMILAttValExternalFalse, "false");

// Literals for allowed values for the fill attribute
_LIT(KXMLSMILAttValFillRemove, "remove");
_LIT(KXMLSMILAttValFillFreeze, "freeze");
_LIT(KXMLSMILAttValFillHold, "hold");
_LIT(KXMLSMILAttValFillTransition, "transition");

// Literals for allowed values for the fit attribute
_LIT(KXMLSMILAttValFitHidden, "hidden");
_LIT(KXMLSMILAttValFitFill, "fill");
_LIT(KXMLSMILAttValFitMeet, "meet");
_LIT(KXMLSMILAttValFitScroll, "scroll");
_LIT(KXMLSMILAttValFitSlice, "slice");

// Literals for allowed values for the nohref attribute
_LIT(KXMLSMILAttValNoHRefNoHRef, "nohref");

// Literals for allowed values for the open attribute
_LIT(KXMLSMILAttValOpenAlways, "always");
_LIT(KXMLSMILAttValOpenWhenActive, "whenActive");

// Literals for allowed values for the shape attribute
_LIT(KXMLSMILAttValShapeRect, "rect");
_LIT(KXMLSMILAttValShapeCircle, "circle");
_LIT(KXMLSMILAttValShapePoly, "poly");
_LIT(KXMLSMILAttValShapeDefault, "default");

// Literals for allowed values for the show attribute
_LIT(KXMLSMILAttValShowNew, "new");
_LIT(KXMLSMILAttValShowPause, "pause");
_LIT(KXMLSMILAttValShowReplace, "replace");

// Literals for allowed values for the showBackground attribute
_LIT(KXMLSMILAttValShowBackgroundAlways, "always");
_LIT(KXMLSMILAttValShowBackgroundWhenActive, "whenActive");

// Literals for allowed values for the skip-content attribute
_LIT(KXMLSMILAttValSkipContentTrue, "true");
_LIT(KXMLSMILAttValSkipContentFalse, "false");

// Literals for allowed values for the sourcePlaystate attribute
_LIT(KXMLSMILAttValSourcePlaystatePlay, "play");
_LIT(KXMLSMILAttValSourcePlaystatePause, "pause");
_LIT(KXMLSMILAttValSourcePlaystateStop, "stop");

// Literals for allowed values for the system-captions attribute
_LIT(KXMLSMILAttValSystem_captionsOn, "on");
_LIT(KXMLSMILAttValSystem_captionsOff, "off");

// Literals for allowed values for the system-overdub-or-caption attribute
_LIT(KXMLSMILAttValSystem_overdub_or_captionOverdub, "overdub");
_LIT(KXMLSMILAttValSystem_overdub_or_captionCaption, "caption");

// Literals for allowed values for the systemAudioDesc attribute
_LIT(KXMLSMILAttValSystemAudioDescOn, "on");
_LIT(KXMLSMILAttValSystemAudioDescOff, "off");

// Literals for allowed values for the systemCaptions attribute
_LIT(KXMLSMILAttValSystemCaptionsOn, "on");
_LIT(KXMLSMILAttValSystemCaptionsOff, "off");

// Literals for allowed values for the systemOverdubOrSubtitle attribute
_LIT(KXMLSMILAttValSystemOverdubOrSubtitleOverdub, "overdub");
_LIT(KXMLSMILAttValSystemOverdubOrSubtitleSubtitle, "subtitle");

// Enumerated values for attribute Actuate
enum TDOMAttActuateType
	{
	EAttActuateUndefined,
	EAttActuateOnRequest,
	EAttActuateOnLoad
	};

// Enumerated values for attribute Close
enum TDOMAttCloseType
	{
	EAttCloseUndefined,
	EAttCloseNever,
	EAttCloseWhenNotActive
	};

// Enumerated values for attribute DestinationPlaystate
enum TDOMAttDestinationPlaystateType
	{
	EAttDestinationPlaystateUndefined,
	EAttDestinationPlaystatePlay,
	EAttDestinationPlaystatePause,
	EAttDestinationPlaystateStop
	};

// Enumerated values for attribute External
enum TDOMAttExternalType
	{
	EAttExternalUndefined,
	EAttExternalTrue,
	EAttExternalFalse
	};

// Enumerated values for attribute Fill
enum TDOMAttFillType
	{
	EAttFillUndefined,
	EAttFillRemove,
	EAttFillFreeze,
	EAttFillHold,
	EAttFillTransition
	};

// Enumerated values for attribute Fit
enum TDOMAttFitType
	{
	EAttFitUndefined,
	EAttFitHidden,
	EAttFitFill,
	EAttFitMeet,
	EAttFitScroll,
	EAttFitSlice
	};

// Enumerated values for attribute NoHRef
enum TDOMAttNoHRefType
	{
	EAttNoHRefUndefined,
	EAttNoHRefNoHRef
	};

// Enumerated values for attribute NoHRref
enum TDOMAttNoHRrefType
	{
	EAttNoHRrefUndefined,
	EAttNoHRrefNoHRef
	};

// Enumerated values for attribute Open
enum TDOMAttOpenType
	{
	EAttOpenUndefined,
	EAttOpenAlways,
	EAttOpenWhenActive
	};

// Enumerated values for attribute Shape
enum TDOMAttShapeType
	{
	EAttShapeUndefined,
	EAttShapeRect,
	EAttShapeCircle,
	EAttShapePoly,
	EAttShapeDefault
	};

// Enumerated values for attribute Show
enum TDOMAttShowType
	{
	EAttShowUndefined,
	EAttShowNew,
	EAttShowPause,
	EAttShowReplace
	};

// Enumerated values for attribute ShowBackground
enum TDOMAttShowBackgroundType
	{
	EAttShowBackgroundUndefined,
	EAttShowBackgroundAlways,
	EAttShowBackgroundWhenActive
	};

// Enumerated values for attribute SkipContent
enum TDOMAttSkipContentType
	{
	EAttSkipContentUndefined,
	EAttSkipContenttrue,
	EAttSkipContentfalse
	};

// Enumerated values for attribute SourcePlaystate
enum TDOMAttSourcePlaystateType
	{
	EAttSourcePlaystateUndefined,
	EAttSourcePlaystatePlay,
	EAttSourcePlaystatePause,
	EAttSourcePlaystateStop
	};

// Enumerated values for attribute System-captions
enum TDOMAttSystem_captionsType
	{
	EAttSystem_captionsUndefined,
	EAttSystem_captionsOn,
	EAttSystem_captionsOff
	};

// Enumerated values for attribute System-overdub-or-caption
enum TDOMAttSystem_overdub_or_captionType
	{
	EAttSystem_overdub_or_captionUndefined,
	EAttSystem_overdub_or_captionOverdub,
	EAttSystem_overdub_or_captionCaption
	};

// Enumerated values for attribute SystemAudioDesc
enum TDOMAttSystemAudioDescType
	{
	EAttSystemAudioDescUndefined,
	EAttSystemAudioDescOn,
	EAttSystemAudioDescOff
	};

// Enumerated values for attribute SystemCaptions
enum TDOMAttSystemCaptionsType
	{
	EAttSystemCaptionsUndefined,
	EAttSystemCaptionsOn,
	EAttSystemCaptionsOff
	};

// Enumerated values for attribute SystemOverdubOrSubtitle
enum TDOMAttSystemOverdubOrSubtitleType
	{
	EAttSystemOverdubOrSubtitleUndefined,
	EAttSystemOverdubOrSubtitleOverdub,
	EAttSystemOverdubOrSubtitleSubtitle
	};

#endif