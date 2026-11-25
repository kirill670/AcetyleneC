// EIKCTGRP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCTGRP_H__)
#define __EIKCTGRP_H__

#include <eikbctrl.h>
#include <lafpublc.h>

/**
 *
 * Wraps a control pointer.
 *
 * The control pointer is wrapped with other information such as; an ID,
 * whether the control is of a fixed size or is stretchable and, if a set
 * size, the controls length. This class is used by
 * <code>CEikControlGroup</code>.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class TEikGroupControl
	{
public:
	inline TEikGroupControl();
	inline TEikGroupControl(CCoeControl* aControl,TInt aId,TInt aLength,TInt aFlags);
public:
	CCoeControl* iControl;
	TInt iId;
public:
	inline TBool IsLengthSet() const;
	inline TInt Length() const;
	inline TBool IsStretchable() const;
	inline void SetLength(TInt aLength);
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
	IMPORT_C CEikControlGroup();
	IMPORT_C ~CEikControlGroup();
	IMPORT_C void ConstructL(TStartCorner aStart,TOrientation aOrientation);
	IMPORT_C virtual void AddControlL(CCoeControl* aControl,TInt aId);
	IMPORT_C virtual void AddControlL(TEikGroupControl& aGroupControl);
	IMPORT_C void InsertControlL(TEikGroupControl& aGroupControl,TInt aIndex);
	IMPORT_C void DeleteControl(TInt aIndex,TInt aCount);
	IMPORT_C void SetLengthInPixels(TInt aLength);
	IMPORT_C void SetBreadthInPixels(TInt aBreadth);
	IMPORT_C void SetControlSpacing(TInt aHSpacing,TInt aVSpacing);
	IMPORT_C void SetControlLayout(TStartCorner aStart,TOrientation aOrientation);
	IMPORT_C void SetNumberOfLines(TInt aNumLines,TBool aDistributeEvenly);
	IMPORT_C void SetControlsAllSameSize();
	IMPORT_C void LayoutControls();
	IMPORT_C CCoeControl* ControlById(TInt aId) const;
	IMPORT_C TInt IndexById(TInt aId) const;
	IMPORT_C void Reset();
	IMPORT_C TInt ControlId(CCoeControl* aControl) const;
	IMPORT_C CCoeControl* Control(TInt aIndex) const; // as requested by Bill
	IMPORT_C CArrayFix<TEikGroupControl>* ControlArray() const;
	IMPORT_C TOrientation Orientation() const;
	IMPORT_C void ControlSpacing(TInt& aHSpacing,TInt& aVSpacing) const;
public: // from CCoeControl
	IMPORT_C TSize MinimumSize();
    IMPORT_C TInt CountComponentControls() const;
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
protected:
	enum
		{
		EDistributeEvenly	=0x40,
		EAllSameSize		=0x80
		};
protected: // from CCoeControl
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
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


/**
 * Default constructor.
 */
inline TEikGroupControl::TEikGroupControl()
	{ iControl=NULL; iId=iFlags=iLength=0; }

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
inline TEikGroupControl::TEikGroupControl(CCoeControl* aControl,TInt aId,TInt aLength,TInt aFlags)
	: iControl(aControl),iId(aId),iLength(aLength),iFlags(aFlags)
	{}

/**
 * Tests whether the controls length is set.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the controls length is set.
 *            <code>EFalse</code> if the controls length is not set.
 */
inline TBool TEikGroupControl::IsLengthSet() const
	{ return iFlags&ESetLength; }

/**
 * Gets the controls length.
 *
 * @returns   "TInt"
 *            The controls length.
 */
inline TInt TEikGroupControl::Length() const
	{ return iLength; }

/**
 * Tests whether the control is stretchable.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the <code>EAllowStretch</code>
 *            flag is set. <code>EFalse</code> otherwise.
 */
inline TBool TEikGroupControl::IsStretchable() const
	{ return iFlags&EAllowStretch; }

/**
 * Sets the controls length.
 *
 * Also sets the <code>ESetLength</code> flag, indicating the control is
 * not stretchable.
 *
 * @param     "TInt aLength"
 *            The controls length.
 */
inline void TEikGroupControl::SetLength(TInt aLength)
	{ iLength=aLength; iFlags|=ESetLength; }

/**
 * Sets the control as stretchable.
 */
inline void TEikGroupControl::SetStretchable()
	{ iFlags|=EAllowStretch; }

#endif
