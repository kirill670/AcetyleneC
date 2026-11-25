/*
* ==============================================================================
*  Name        : eikctgrp.h
*  Part of     : ckon
*  Interface   : Control API
*  Description : Manages layout of a group of controls
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

#ifndef EIKCTGRP_H
#define EIKCTGRP_H

// INCLUDES
#include <eikbctrl.h>
#include <lafpublc.h>

/**
 *
 * Wraps a control pointer.
 * The control pointer is wrapped with other information such as: an ID,
 * whether the control is of a fixed size or is stretchable and, if a set
 * size, the controls length. This class is used by * <code>CEikControlGroup</code>.
 * Note that the pointer to the control and it's ID are public member data.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class TEikGroupControl
	{
	public:

		/**
		* C++ default constructor.
		*/
		inline TEikGroupControl();

/**
 * Constructor.
 *
 * This function wraps <code>aControl</code> with the specified
 * information.
 *
 * @param     "CCoeControl* aControl"
 *            The control.
 * @param     "TInt aId"
 *            The controls ID.
 * @param     "TInt aLength"
 *            The controls length in pixels.
 * @param     "TInt aFlags"
 *            The controls flags. This determines whether the
 *            control is of a fixed size or can be stretched.
 */
		inline TEikGroupControl(CCoeControl* aControl,TInt aId,TInt aLength,TInt aFlags);
	public:
		CCoeControl* iControl;
		TInt iId;
	public:

		/**
		* Checks whether the length is set
		* @return The state of the variable holding the length
		* <BR><B>Type of return value:</B> TBool
		* <BR><B>Range of return value:</B> ETrue if the control’s length is set. EFalse if the control’s length is not set
		*/
		inline TBool IsLengthSet() const;

		/**
		* Returns the length
		* @return Gets the control’s length.
		* <BR><B>Type of return value:</B> TInt
		* <BR><B>Range of return value:</B> Positive integer
		*/
		inline TInt Length() const;

		/**
		* Tests whether the control is stretchable.
		* @return
		* <BR><B>Type of return value:</B> TBool
		* <BR><B>Range of return value:</B> ETrue if the EAllowStretch flag is set. EFalse otherwise
		*/
		inline TBool IsStretchable() const;

		/**
		* Sets the control’s length. Also sets the ESetLength flag, indicating the control is not stretchable.
		* @param aLength The control’s length
		* <BR><B>Type of return value:</B> void
		*/
		inline void SetLength(TInt aLength);

		/**
		* Sets the control as stretchable. 
		* @return
		* <BR><B>Type of return value:</B> void
		*/
		inline void SetStretchable();
	public:
	/**
	 * Specifies whether the control is of a specific length or is
	 * stretchable.
	 */
	enum TControlFlags
		{
		ESetLength		=0x01,		/** Specifies the control is of a set length, and so cannot be stretched. */
		EAllowStretch	=0x02		/** Specifies the control can be stretched. */
		};
	private:
		TInt iLength;
		TInt iFlags;
	};

/**
 *
 * This class holds an array of controls wrapped with related
 * information.
 *
 * This related information is an ID, whether the control is of a fixed
 * size or is stretchable and, if a set size, the controls length.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikControlGroup : public CEikBorderedControl
	{
friend class CTestControlGroup; // test code
	public:
	/**
	 * Specifies the corner of the control group from which to start control
	 * layout.
	 */
	enum TStartCorner
		{
		EFromTopLeft=SLafControlGroup::EFromTopLeft,			/** Layout begins from the top left corner of the control group. */
		EFromTopRight=SLafControlGroup::EFromTopRight,			/** Layout begins from the top right corner of the control group. */
		EFromBottomLeft=SLafControlGroup::EFromBottomLeft,		/** Layout begins from the bottom left corner of the control group. */
		EFromBottomRight=SLafControlGroup::EFromBottomRight		/** Layout begins from the bottom right corner of the control group. */
		};
	/**
	 * Specifies the control groups orientation.
	 */
	enum TOrientation
		{
		ELayHorizontally=SLafControlGroup::ELayHorizontally,	/** Sets the control groups orientation to horizontal. */
		ELayVertically	=SLafControlGroup::ELayVertically		/** Sets the control groups orientation to vertical. */
		};
	public: // new functions

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikControlGroup();

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikControlGroup();

		/**
		* Completes construction of the control group
		* @param aStart The corner of the control from which to start control layout
		* @param aOrientation The control group’s orientation
		* @return
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructL(TStartCorner aStart,TOrientation aOrientation);

		/**
		* Wraps, then adds, a control to the control group array. Wraps aControl with aId to generate a TEikGroupControl which is appended to the control group array.
		* @param aControl The control to add to the control group
		* @param aId The control’s ID. 
		* @return
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void AddControlL(CCoeControl* aControl,TInt aId);

		/**
		* Wraps, then adds, a control to the control group array. Wraps aControl with aId to generate a TEikGroupControl which is appended to the control group array.
		* @param aGroupControl The control to add
		* @return
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void AddControlL(TEikGroupControl& aGroupControl);

		/**
		* Adds a wrapped control to the control group array at the given index position.
		* @param aGroupControl The control to add to the group. 
		* @param aIndex The index for the added control
		* @return
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void InsertControlL(TEikGroupControl& aGroupControl,TInt aIndex);

		/**
		* Deletes the specified controls
		* @param aIndex The index at which to start deletion. 
		* @param aCount The number of controls to delete from the group, starting with the control at aIndex
		* @return
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void DeleteControl(TInt aIndex,TInt aCount);

		/**
		* Sets the control group’s length in pixels.
		* @param aLength The control group’s length in pixels. 
		* @return
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetLengthInPixels(TInt aLength);

		/**
		* Sets the control group’s breadth in pixels.
		* @param aBreadth The control group’s breadth in pixels
		* @return
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetBreadthInPixels(TInt aBreadth);

		/**
		* Sets the control group’s horizontal and vertical spacing.
		* @param aHSpacing The control group’s horizontal spacing
		* @param aVSpacing The control group’s vertical spacing
		* @return
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetControlSpacing(TInt aHSpacing,TInt aVSpacing);

		/**
		* Sets the control group’s layout
		* @param aStart The corner of the control from which to start control layout
		* @param aOrientation The control group’s orientation
		* @return
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetControlLayout(TStartCorner aStart,TOrientation aOrientation);

		/**
		* Sets the control group’s number of lines and whether to distribute the controls in the group evenly.
		* @param aNumLines The number of lines in the control group.
		* @param aDistributeEvenly If ETrue, distributes the controls evenly
		* @return
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetNumberOfLines(TInt aNumLines,TBool aDistributeEvenly);

		/**
		* Sets all controls within the control group to be the same size.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetControlsAllSameSize();

		/**
		* Lays out the controls in the control group.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void LayoutControls();

		/**
		* Gets the control identified by the given ID.
		* @param aId The ID of the control to get
		* @return
		* <BR><B>Type of return value:</B> CCoeControl*
		*/
		IMPORT_C CCoeControl* ControlById(TInt aId) const;

		/**
		* Gets the index of the control with the given ID.
		* @param aId The ID of the control for which the index is obtained
		* @return The control's index
		* <BR><B>Type of return value:</B> TInt
		* <BR><B>Range of return value:</B> Positive value
		*/
		IMPORT_C TInt IndexById(TInt aId) const;

		/**
		* Deletes all controls from the control group array.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void Reset();

		/**
		* Gets the specified control’s ID.
		* @param aControl The control for which the ID is obtained
		* @return The control's id
		* <BR><B>Type of return value:</B> TInt
		*/
		IMPORT_C TInt ControlId(CCoeControl* aControl) const;

		/**
		* Gets the control identified by the given index.
		* @param aIndex The index of the control to get. 
		* @return The control identified by aIndex
		* <BR><B>Type of return value:</B> CCoeControl*
		* <BR><B>Range of return value:</B>
		*/
		IMPORT_C CCoeControl* Control(TInt aIndex) const; // as requested by Bill

		/**
		* Gets the control array.
		* @return Pointer to the array of TEikGroupControl
		* <BR><B>Type of return value:</B> CArrayFix<TEikGroupControl>*
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		IMPORT_C CArrayFix<TEikGroupControl>* ControlArray() const;

		/**
		* Get the control group’s orientation.
		* @return the control group’s orientation.
		* <BR><B>Type of return value:</B> TOrientation
		* <BR><B>Range of return value:</B> ELayHorizontally or ELayVertically
		*/
		IMPORT_C TOrientation Orientation() const;

		/**
		* Get the horizontal and vertical values for the control's spacing
		* @param aHSpacing The horizontal value
		* @param aVSpacing The vertical value
		* @return Spacing values
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ControlSpacing(TInt& aHSpacing,TInt& aVSpacing) const;
	public: // from CCoeControl

		/**
		* Get the group control's minimum size
		* @return The group control's minimum size
		* <BR><B>Type of return value:</B> TSize
		*/
		IMPORT_C TSize MinimumSize();

		/**
		* Get the number of controls in the group control
		* @return The number of component controls
		* <BR><B>Type of return value:</B> TInt
		*/
		IMPORT_C TInt CountComponentControls() const;

		/**
		* Gets the list of logical colours used to draw the control. Appends the list to aColorUseList paired with an explanation of how the colours are used.
		* @param aColorUseList List of logical colours
		* @return The list of colors
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

		/**
		* Handles a change to the control's resources which are shared across the environment. For example, colours or fonts.
		* @param aType The type of resource that has changed
		* @return
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	protected:
	enum
		{
		EDistributeEvenly	=0x40,
		EAllSameSize		=0x80
		};
	protected: // from CCoeControl

		/**
		* See CCoeControl
		*/
		IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

		/**
		* See CCoeControl
		*/
		IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
	private: // from CCoeControl
		IMPORT_C void Reserved_2();
	private: // new functions
		IMPORT_C TInt Adjacent(TInt aRow,TInt aColumn,TInt aCtrlIndex,TInt aTotalRows,TInt aTotalColumns) const;
		IMPORT_C TStartCorner StartCorner() const;
		IMPORT_C void DeleteAllComponents();
		IMPORT_C TSize ControlMinimumSize(TInt aIndex) const;
		IMPORT_C TInt ControlMinimumLength(TInt aIndex);
		IMPORT_C TSize LargestControlSize() const;
		IMPORT_C TBool DistributeEvenly() const;
		IMPORT_C TBool AllSameSize();
	private: // from CCoeControl
		IMPORT_C void SizeChanged();
		IMPORT_C void Draw(const TRect& aRect) const;
	protected:
		CArrayFix<TEikGroupControl>* iControlArray;
	private:
		TInt iLayout;
		TInt iLines;
		TInt iHSpacing;
		TInt iVSpacing;
		TInt iBreadth;
		TInt iLength;
		TSize iLargestControl;
	};


inline TEikGroupControl::TEikGroupControl()
	{ iControl=NULL; iId=iFlags=iLength=0; }

inline TEikGroupControl::TEikGroupControl(CCoeControl* aControl,TInt aId,TInt aLength,TInt aFlags)
	: iControl(aControl),iId(aId),iLength(aLength),iFlags(aFlags)
	{}

inline TBool TEikGroupControl::IsLengthSet() const
	{ return iFlags&ESetLength; }

inline TInt TEikGroupControl::Length() const
	{ return iLength; }

inline TBool TEikGroupControl::IsStretchable() const
	{ return iFlags&EAllowStretch; }

inline void TEikGroupControl::SetLength(TInt aLength)
	{ iLength=aLength; iFlags|=ESetLength; }

inline void TEikGroupControl::SetStretchable()
	{ iFlags|=EAllowStretch; }


#endif	// EIKCTGRP_H

// End of File
