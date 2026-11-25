// K32VIDEO.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __K32VIDEO_H__
#define __K32VIDEO_H__
#include <K32STD.H>
#include <D32VIDEO.H>
#include <e32ver.h>
//
const TInt KMajorVersionNumber=1;
const TInt KMinorVersionNumber=0;
const TInt KBuildVersionNumber=KE32BuildVersionNumber;
//
enum TStopMode {EStopNormal,EStopEmergency};
//
class DLddVideo;
class DPddVideo : public CBase
	{
public:
	virtual TInt Start() =0;
	virtual void Stop(TStopMode aMode) =0;
	virtual TInt CheckSupported(TVideoMode aMode) const =0;
	virtual void Configure(TVideoMode aMode) =0;
	virtual void SetPaletteEntry(TInt aIndex,TUint aEntry)=0;
	virtual void Caps(TDes8& aCaps) const =0;
	virtual void Blit(const TText* aBuffer,TColour aColour,TInt aLength,TInt aX,TInt aY) =0;
	virtual void SetPixel(TInt aX,TInt aY,TColour aColour) =0;
	virtual void ScrollUp(const TRect& aRect) =0;
	virtual void Clear(const TRect& aRect) =0;
	virtual TInt GetPixel(const TPoint& aPoint) =0;
	virtual void SetWord(const TPoint& aPoint,TInt aWord) =0;
	virtual TInt GetWord(const TPoint& aPoint) =0;
	virtual void SetLine(const TPoint& aPoint,const TPixelLine& aPixelLine) =0;
 	virtual void GetLine(const TPoint& aPoint,TPixelLine& aPixelLine) =0;
	};
//
class DLddFactoryVideo : public DLogicalDevice
	{
public:
	DLddFactoryVideo();
	virtual TInt Install();
	virtual void GetCaps(TDes8 &aDes) const;
	virtual DLogicalChannel *CreateL();
	};
//
class DLddVideo : public DLogicalChannel
	{
public:
	DLddVideo(DLogicalDevice *aDevice);
	~DLddVideo();
protected:
	virtual void DoCreateL(TInt aUnit,CBase *aDriver,const TDesC *anInfo,const TVersion &aVer);
	virtual void DoCancel(TInt aReqNo);
	virtual void DoRequest(TInt aReqNo,TAny *a1,TAny *a2);
	virtual TInt DoControl(TInt aFunction,TAny *a1,TAny *a2);
 	void Start();
	void Stop(TStopMode aMode);
public:
	TVideoMode iVideoMode;
private:
	DPddVideo *iDriver;
	};
#endif

