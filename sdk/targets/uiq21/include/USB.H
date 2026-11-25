//
// usb.h - USB definitions
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//
#ifndef __USB_H__
#define __USB_H__

// Chapter 9 request types
const TUint8 KUsbRequestType_DirShift   = 7;
const TUint8 KUsbRequestType_DirMask    = (1 << KUsbRequestType_DirShift);

const TUint8 KUsbRequestType_DirToDev   = (0 << KUsbRequestType_DirShift);
const TUint8 KUsbRequestType_DirToHost  = (1 << KUsbRequestType_DirShift);

const TUint8 KUsbRequestType_TypeShift  = 5;
const TUint8 KUsbRequestType_TypeMask   = (3 << KUsbRequestType_TypeShift);
const TUint8 KUsbRequestType_TypeStd    = (0 << KUsbRequestType_TypeShift);
const TUint8 KUsbRequestType_TypeClass  = (1 << KUsbRequestType_TypeShift);
const TUint8 KUsbRequestType_TypeVendor = (2 << KUsbRequestType_TypeShift);


const TUint8 KUsbRequestType_DestShift  = 0;
const TUint8 KUsbRequestType_DestMask   = (0x1f << KUsbRequestType_DestShift);
const TUint8 KUsbRequestType_DestDevice = (0x00 << KUsbRequestType_DestShift);
const TUint8 KUsbRequestType_DestIfc    = (0x01 << KUsbRequestType_DestShift);
const TUint8 KUsbRequestType_DestEp     = (0x02 << KUsbRequestType_DestShift);
const TUint8 KUsbRequestType_DestOther  = (0x03 << KUsbRequestType_DestShift);

// Chapter 9 endpoint zero requests
const TUint8 KUsbRequest_GetStatus      = 0;
const TUint8 KUsbRequest_ClearFeature   = 1;
const TUint8 KUsbRequest_SetFeature     = 3;
const TUint8 KUsbRequest_SetAddress     = 5;
const TUint8 KUsbRequest_GetDescriptor  = 6;
const TUint8 KUsbRequest_SetDescriptor  = 7;
const TUint8 KUsbRequest_GetConfig      = 8;
const TUint8 KUsbRequest_SetConfig      = 9;
const TUint8 KUsbRequest_GetInterface   = 10;
const TUint8 KUsbRequest_SetInterface   = 11;
const TUint8 KUsbRequest_SynchFrame     = 12;

// Descriptor type codes
const TUint8 KUsbDescType_Device        = 1;
const TUint8 KUsbDescType_Config        = 2;
const TUint8 KUsbDescType_String        = 3;
const TUint8 KUsbDescType_Interface     = 4;
const TUint8 KUsbDescType_Endpoint      = 5;

// These are from the CDC (valid also for Audio class)
const TUint8 KUsbDescType_CS_Interface  = 0x24;
const TUint8 KUsbDescType_CS_Endpoint   = 0x25;

// Descriptor sizes
const TInt KUsbDescSize_Device          = 18;
const TInt KUsbDescSize_Config          = 9;
const TInt KUsbDescSize_Interface       = 9;
const TInt KUsbDescSize_Endpoint        = 7;
const TInt KUsbDescMaxSize_String       = 255;
const TInt KUsbStringDescStringMaxSize  = 252;				// (it's actually 253, but that's awkward)

// Descriptor indices for string descriptors
const TInt KUsbDescStringIndex_Manufact = 14;
const TInt KUsbDescStringIndex_Product  = 15;
const TInt KUsbDescStringIndex_Serial   = 16;
const TInt KUsbDescStringIndex_Config   = 6;

// Endpoint attribute codes
const TUint8 KUsbEpAttr_Control         = 0;
const TUint8 KUsbEpAttr_Isochronous     = 1;
const TUint8 KUsbEpAttr_Bulk            = 2;
const TUint8 KUsbEpAttr_Interrupt       = 3;

// Feature settings
const TInt KUsbFeature_EndpointHalt     = 0;
const TInt KUsbFeature_RemoteWakeup     = 1;

// Address masks
const TUint8 KUsbEpAddress_In           = 0x80;
const TUint8 KUsbEpAddress_Portmask     = 0x0f;

// Device Status values
const TUint16 KUsbDevStat_SelfPowered   = (1 << 0);
const TUint16 KUsbDevStat_RemoteWakeup  = (1 << 1);

// Endpoint Status values
const TUint16 KUsbEpStat_Halt           = (1 << 0);


//
// USB Descriptor handling
//
//--------------------------------------------------
// USB transfers data in little-endian fashion.
// The following macros swap the byte order in
// words (16 bit) and in longwords (32 bit), such that
// they are in little-endian order afterwards.
//--------------------------------------------------

#if defined(__BIG_ENDIAN__)	      // Hitachi SuperH, Motorola 68k
#define SWAP_BYTES_16(x)   \
  ((((x) >> 8) & 0x00ff) | \
   (((x) << 8) & 0xff00))
#define SWAP_BYTES_32(x)        \
  ((((x) >> 24) & 0x000000ff) | \
   (((x) >> 8)  & 0x0000ff00) | \
   (((x) << 24) & 0xff000000) | \
   (((x) << 8)  & 0x00ff0000))
#else                             // ARM, Intel
#define SWAP_BYTES_16(x)  (x)
#define SWAP_BYTES_32(x)  (x)
#endif // defined(__BIG_ENDIAN__)


static inline TUint8 LowByte(TUint16 aWord)
	{
	return static_cast<TUint8>(aWord & 0x00ff);
	}

static inline TUint8 HighByte(TUint16 aWord)
	{
	return static_cast<TUint8>((aWord >> 8) & 0x00ff);
	}


// just for your convenience...
const TUint8 KEp0_Out = 0;
const TUint8 KEp0_In  = 1;
const TUint8 KEp0_Rx = KEp0_Out;
const TUint8 KEp0_Tx = KEp0_In;


// USB Implementers Forum, Inc, (USB-IF) assigned Vendor IDs
const TUint16 KUsbVendorId_Symbian = 0x0E22;				// Symbian Ltd


#endif // __USB_H__
