/*
* ==============================================================================
*  Name        : cknprogi.h
*  Part of     : CKON
*  Interface   : 
*  Description : CCknProgressInfo class implements a control used to
*				 indicate the progress of an operation.

*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef CKNPROGI_H
#define CKNPROGI_H

// INCLUDES
#include <cknbctrl.h>
#include <gulicon.h>
#include <eikon.hrh>

// FORWARD DECLARATIONS
class CCknProgressInfoExt;


/**
*  CCknProgressInfo class implements a control used to 
*  indicate the progress of an operation.
*
*  @lib cknctl.lib
*  @since Series90 1.0
*/
class CCknProgressInfo : public CCknBorderedControl
	{
	public:
	enum TGaugeType
		{
		ECknDefiniteGauge,
		ECknIncrementalGauge,
		ECknContinuousGauge
		};
    struct SProgressInfoData
        {
        TInt iWidth;
        TInt iHeight;
        TInt iFinalValue;
        };
	struct SInfo
		{
		TGaugeType iGaugeType;
		TInt iBlockMinimumSize;
		TEikProgressTextType iTextType;
		TRgb iFillTextColor;
		TRgb iEmptyTextColor;
		const CFont* iFont;
		};


		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CCknProgressInfo* NewL();

		/**
		* Two-phased constructor.
		* @param aData Defines a control bar size and maximum value.
		*/
		IMPORT_C static CCknProgressInfo* NewL(const SProgressInfoData& aData);

		/**
		* Destructor.
		*/
		IMPORT_C ~CCknProgressInfo();
	

		/**
		* Adds the specified increment to the current progress value and redraws the control.
		* 
		* @param aInc The increment to add to the current progress value.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void IncrementAndDraw(TInt aInc);

		/**
		* Redraws the control with the specified value as the new progress value.
		* 
		* @param aValue The new progress value.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetAndDraw(TInt aValue);

		/**
		* Completes construction from resource.
		* 
		* @param aReader The resource reader.
		* The resource ID is ECknCtProgressInfo and resource struct is not needed.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

		/**
		* Sets the final value for the progress information control.
		* 
		* @param aFinalValue The final value for the progress information control.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetFinalValue(TInt aFinalValue);

		/**
		* Gets the current value for how far the operation has progressed.
		* 
		* @return The value for how far the operation has progressed.
		* <BR><B>Type of return value:</B> TInt
		*/
		inline TInt CurrentValue() const { return(iCurrentValue); }

		/**
		* Sets text display info.
		* 
		* @param aInfo Holds information about the progress information control.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetInfo(const SInfo& aInfo);

		/**
		* Sets control bar width, height, and max value.
		* 
		* @param aData Defines a control bar size and maximum value.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetData(const SProgressInfoData& aData);

		/**
		* Gets a reference to the SInfo struct used to define the progress information control.
		* 
		* @return Reference to the SInfo struct.
		* <BR><B>Type of return value:</B> const SInfo&
		*/
		inline const SInfo& Info() const { return(iInfo); }
	public:
		static TInt UpdateContinuous(TAny* aObject);
	public: 

		/**
		* From CCoeControl.
		* Activates the progress information control.
		* 
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ActivateL();

		/**
		* From CCoeControl.
		* Sets the size of the control as having changed.
		* 
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SizeChanged();

		/**
		* From CCoeControl.
		* Gets the minimum size required to draw the control.
		* 
		* @return The minimum size required to draw the control.
		* <BR><B>Type of return value:</B> TSize
		*/
		IMPORT_C TSize MinimumSize();

		/**
		* From CCoeControl.
		* Handles a change to the control's resources.
		* 
		* @param aType A message UID value.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u

		/**
		* From CCoeControl.
		* Sets control dimmed.
		* 
		* @param aDimmed <code>ETrue</code> to dim the control, 
		* 			<code>EFalse</code> to set the control as not dimmed
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void SetDimmed(TBool aDimmed);

		/**
		* From CCoeControl.
		* Sets this control as visible or invisible.
		* 
		* @param aVisible <code>ETrue</code> to make the control visible, 
		* 			<code>EFalse</code> to make it invisible
		* <BR><B>Type of return value:</B> void
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		virtual void MakeVisible(TBool aVisible);
	protected: 

		/**
		* From CCoeControl.
		* Draws the control.
		* @param aRect Optional. If supplied, the screen rectangle to be updated.
		*/
		IMPORT_C void Draw(const TRect& aRect) const;
	protected:

		/**
		* C++ default constructor.
		*/
		CCknProgressInfo();

		/**
		* C++ constructor.
		* @param aData Defines a control bar size and maximum value.
		*/
		CCknProgressInfo(const SProgressInfoData& aData);

		/**
		* Second phase constructor.
		*/
		void ConstructL();
	protected:

		/**
		* Gets the current value of the progress text.
		* @param aTextBuf The buffer from which the text is obtained.
		* @return The control's text.
		*/
		IMPORT_C virtual const TDesC* EvaluateText(TDes& aTextBuf) const;
		void CalculateNumBlocks();
	private: // internal use
		void CheckSizeCalculated();
		CFbsBitmap* CreateBlockBitmapL(const TSize& aBlockSize, TBool aForceDimmed = EFalse) const;
		void DrawSlider(CWindowGc& aGc,const TRect& aInvalidRect) const;
	private:
		SProgressInfoData iData;
		SInfo iInfo;
		TInt iCurrentValue;
		TInt iNumBlocks;
		TInt iFlags;
		TPoint iSliderPos;
		TPoint iIconPos;
		TInt iBlockGap;
		TInt iResourceTotalBlocks;
		TInt iResourceSliderBlocks;
		TInt iResourceContinuousInterval;
		TInt iRedrawRangeFirstBlock;
		TInt iRedrawRangeLastBlock;
		CPeriodic* iPeriodic;
		TAny* iReserved;
	};

#endif	// CKNPROGI_H

// End of File
