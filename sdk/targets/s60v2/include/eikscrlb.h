// EIKSCRLB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
		
#if !defined(__EIKSCRLB_H__)
#define __EIKSCRLB_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__EIKSBOBS_H__)
#include <eiksbobs.h>
#endif

#if !defined(__AKNSCBUT_H__)
#include <aknscbut.h>
#endif

#include <lafpublc.h>

class CEikCba;
class CAknDoubleSpanScrollIndicator;
class CEikScrollBarExtensionImpl;
class CEikScrollBarExtension;
class CAknDoubleSpanScrollBarExtension;

const TInt KEikScrollEventFromVBar=0;
const TInt KEikScrollEventFromHBar=0x01;
const TInt KEikScrollEventBarMask=0x01;

const TInt KButtonPositionMask=KLafScrollBarButtonPositionMask; // sets all bits in EButtonsXxx range
const TInt KDisplayComponentsMask=0x1f; // sets all bits in determining which components exist

//
// TEikScrollBarModel class
//

class TEikScrollBarModel
	{
public:
	inline TEikScrollBarModel();
	IMPORT_C TEikScrollBarModel(TInt aScrollSpan,TInt aThumbSpan=0,TInt aThumbPosition=0);
	// operators
	IMPORT_C TBool operator==(const TEikScrollBarModel aModel) const;
	inline TBool operator!=(const TEikScrollBarModel aModel) const; 
public:
	IMPORT_C TBool ScrollBarUseful() const;
	IMPORT_C TInt MaxThumbPos() const;
	IMPORT_C void CheckBounds();
    enum TEikScrollBarModelType
		{
		EEikScrollBarModel               = 0x00000000,
		EAknDoubleSpanScrollBarModel     = 0x80000000
		};        
    TEikScrollBarModel::TEikScrollBarModelType ScrollBarModelType() const;
public:
	TInt iScrollSpan;
	TInt iThumbSpan;
	TInt iThumbPosition;            
	};

inline TEikScrollBarModel::TEikScrollBarModel() {}
inline TBool TEikScrollBarModel::operator!=(const TEikScrollBarModel aModel) const { return !(*this==aModel); }


//
// TAknDoubleSpanScrollBarModel class
//
// This class is binary compatible with TEikScrollBarModel and can
// be used in places where TEikScrollBarModel is used but few restrictions exist:
//
// - Base class (TEikScrollBarModel) public members must NOT be accessed directly.
// - Base class (TEikScrollBarModel) public methods must NOT be called.
//
// If this model is not supported by the scrollbar system, then values are stored
// as in the base class for compatibility resons. See ModelIsSupported()-method 
// documentation for more information.
//
class TAknDoubleSpanScrollBarModel : public TEikScrollBarModel
	{

public:
    
   /**
    * Default constructor.
    */
    IMPORT_C TAknDoubleSpanScrollBarModel();

   /**
    * Constructor which converts TEikScrollBarModel into TAknDoubleSpanScrollBarModel.
    *
    * @since    2.6
    * @param    aEikModel a model that will be converted.
    * 
    * Allowed range for TEikScrollBarModel values is from 0x1FFF7FFF to -0x1FFF7FFF. 
    * Values outside the allowed range will be truncated to max or min value. 
    * Value will be internally  stored with 15 bit accuracy, this means 
    * that the actual stored value may differ from the value given as parameter.
    * 
    * Values will be converted as:
    * 
    * TEikScrollBarModel        TAknDoubleSpanScrollBarModel
    * ------------------        ----------------------------
    * iScrollSpan          ->    ScrollSpan
    * iThumbPosition       ->    FocusPosition
    * iThumbSpan           ->    WindowSize
    * 0                    ->    FieldPosition            
    * 0                    ->    FieldSize
    *
    *
    * Values will be internally  stored with 15 bit accuracy, this means that the 
    * actual stored value may differ from the value given inside parameter.
    *
    */
    IMPORT_C TAknDoubleSpanScrollBarModel(const TEikScrollBarModel& aEikModel);
    
    
   /**
    *  Set methods for model attributes. These MUST be used instead of setting
    *  base class model values directly.
    *
    *  @since    2.6
    *  @param    aValue Value to be stored. Allowed range 0x1FFF7FFF to -0x1FFF7FFF. 
    *                   Value outside the allowed range will be truncated to max
    *                   or min value. Value will be internally  stored with 
    *                   15 bit accuracy, this means that the actual stored value
    *                   may differ from the value given as parameter.
    *
    *                   This inaccuracy means that e.g. following can happen:
    *                       TInt value1 = 23456789;                   
    *                       TInt value2 = 0;                   
    *
    *                       model.SetScrollSpan(value1);
    *                       value2 = model.ScrollSpan();
    *                       if (value1 != value2)
    *                           {
    *                           // we can end up here !!!!  
    *                           }
    *
    */
    IMPORT_C void SetScrollSpan(TInt aValue);    // Size of the scrolled list. 
    IMPORT_C void SetFocusPosition(TInt aValue); // Position of the current field in the list.
    IMPORT_C void SetWindowSize(TInt aValue);    // Size of the visible part of the list. 
    IMPORT_C void SetFieldSize(TInt aValue);     // Size of the current field. (Optional double span)
    IMPORT_C void SetFieldPosition(TInt aValue); // Position inside the current field. (Optional double span)  
    
    
   /**
    *  Get methods for model attributes. These MUST be used instead of getting
    *  base class model values directly.
    *
    * @since    2.6
    * @return   Values from range 0x1FFF7FFF to -0x1FFF7FFF. 
    *           Values are internally  stored with 15 bit accuracy, this means that 
    *           the returned value may differ from the value which was set using the
    *           corresponding set method. Difference can be about 0x3FFF in the high
    *           end of the range.
    *
    */
    IMPORT_C TInt ScrollSpan() const;    // Size of the scrolled list.
    IMPORT_C TInt FocusPosition() const; // Position of the current field in the list.
    IMPORT_C TInt WindowSize() const;    // Size of the visible part of the list. 
    IMPORT_C TInt FieldSize() const;     // Size of the current field. (Optional double span)
    IMPORT_C TInt FieldPosition() const; // Position inside the current field. (Optional double span)


   /**
    * This method can be used to query if this model type is supported by the device. If model 
    * is not supported then this model and the behaviour of ALL methods defaults to TEikScrollBarModel 
    * behaviour with following rules:
    *
    * TAknDoubleSpanScrollBarModel              TEikScrollBarModel
    * ----------------------------              ------------------  
    * ScrollSpan methods                ->      iScrollSpan
    * FocusPosition methods             ->      iThumbPosition
    * WindowSize methods                ->      iThumbSize
    * FieldPosition methods             ->      N/A
    * FieldSize methods                 ->      N/A
    *
    * @since    2.6
    * @return   ETrue if this model is supported by the devices scrollbar system. Otherwise EFalse is
    *           returned.
    *
    */
    static TBool ModelIsSupported();

private:   
   /**
    * Gets the internal scale value. 
    *
    * @since    2.6
    * @return   Internal scaling value.
    *
    */
    TUint16 Scale() const;

   /**
    * Sets the internal scale value. 
    *
    * @since    2.6
    * @param    aScale  New internal scaling value.
    *
    */
    void SetScale(TUint16 aScale);    

private:   
   /**
    *  Get methods for model attributes values without scaling.
    *
    *  @since    2.6
    *  @return   Stored value without scaling. 
    *
    */
    TInt16 ScrollSpanValue() const;
    TInt16 FocusPositionValue() const;
    TInt16 FieldPositionValue() const;
    TInt16 FieldSizeValue() const;
    TInt16 WindowSizeValue() const;

   /**
    *  Set methods for model attributes values without scaling.
    *
    *  @since    2.6
    *  @param    aValue Value without scaling to be stored. 
    *
    */
    void SetScrollSpanValue(TInt16 aValue);
    void SetFocusPositionValue(TInt16 aValue);
    void SetFieldPositionValue(TInt16 aValue);
    void SetFieldSizeValue(TInt16 aValue);
    void SetWindowSizeValue(TInt16 aValue);

   /**
    *  Gets two lowest bytes from TInt and constructs TInt16 from those.
    *
    *  @since    2.6
    *  @param    aInt  Value from which the lowest bytes are extracted.     
    *  @return   TInt16 constructed from two lowest bytes.
    */
    TInt16 LowBytes(TInt aInt) const;

   /**
    *  Gets two highest bytes from TInt and constructs TInt16 from those.
    *
    *  @since    2.6
    *  @param    aInt  Value from which the highest bytes are extracted.     
    *  @return   TInt16 constructed from two highest bytes.
    */    
    TInt16 HighBytes(TInt aInt) const;
    
    
   /**
    *  Sets two lowest bytes of TInt.
    *
    *  @since    2.6
    *  @param    aInt    TInt of which the lowest bytes are set.     
    *  @param    aValue  Value for the lowest bytes.     
    */    
    void SetLowBytes(TInt& aInt, TInt16 aValue);

   /**
    *  Sets two highest bytes of TInt.
    *
    *  @since    2.6
    *  @param    aInt    TInt of which the highest bytes are set.     
    *  @param    aValue  Value for the highest bytes.     
    */        
    void SetHighBytes(TInt& aInt, TInt16 aValue);
    
    
   /**
    *  Constructs a scaled TInt16 value from given TInt value. Changes
    *  internal member variable values using ReScale()-method if needed.
    *
    *  @since    2.6
    *  @param    aNonScaledValue    Value which will be changed to scaled one.
    *  @return   Scaled value.
    */        
    TInt16 PrepareScaledValue(TInt aNonScaledValue);
    
   /**
    *  Changes the used scale value and updates all stored attribute values
    *  if needed.
    *
    *  @since    2.6
    *  @param    aNewScale    New value to be used scaling.
    *
    */        
    void ReScale(TUint16 aNewScale);
    
   /**
    *  Sets the scrollbar type.
    *
    *  @since    2.6
    *  @param    aModelType    Scrollbar type. Supported types are 
    *                          EEikScrollBarModel and EAknDoubleSpanScrollBarModel.
    *
    */        
    void SetScrollBarModelType(TEikScrollBarModelType aModelType);

   /**
    *  Checks if given parameter is between internal min and max values.
    *
    *  @since    2.6
    *  @param    aValue        Value to be checked.
    *  @return                 Checked value which will be between internal min 
    *                          and max values. 
    *
    */        
    TInt CheckMinMaxValue(TInt aValue);
    };


//
// CEikScrollBar
//

class CEikScrollThumb;
class CEikScrollBarFrame;
  
/**
 * The CEikScrollBar class implements a scroll bar. Scroll bars are used when the contents of a view require a greater
 * area than can be physically displayed. Scroll bars allow a user to move different parts of the content
 * into the view and to indicate what proportion of the total contents are visible at any one time.
 */
class CEikScrollBar : public CEikBorderedControl, public MCoeControlObserver
	{
friend class CEikScrollBarExtension;
friend class CAknDoubleSpanScrollBarExtension;
    
public:
	enum TOrientation
		{
		EVertical = SLafScrollBar::EVertical,
		EHorizontal = SLafScrollBar::EHorizontal
		};

	enum TScrollBarType
		{
		ENormalScrollBar	=0x0,
		EArrowHead			=0x200,
		EDoubleSpan			=0x400
		};

	enum TEikScrollBarFlags
		{
		EEikScrollBarDefaultBehaviour   =SLafScrollBar::EEikScrollBarDefaultBehaviour,
		EEikScrollBarNoNudgeButtons		=SLafScrollBar::EEikScrollBarNoNudgeButtons,
		EEikScrollBarHasPageButtons		=SLafScrollBar::EEikScrollBarHasPageButtons,	
		EEikScrollBarHasHomeEndButtons	=SLafScrollBar::EEikScrollBarHasHomeEndButtons,
		EEikScrollBarNoShaftOrThumb		=SLafScrollBar::EEikScrollBarNoShaftOrThumb,	
		EEikScrollBarShaftButNoThumb	=SLafScrollBar::EEikScrollBarShaftButNoThumb,	
		EButtonsAtStartOfShaft			=SLafScrollBar::EButtonsAtStartOfShaft,	
		EButtonsAtEndOfShaft			=SLafScrollBar::EButtonsAtEndOfShaft,			
		EButtonsEitherSideOfShaft		=SLafScrollBar::EButtonsEitherSideOfShaft,
		ENoAutoDimming					=SLafScrollBar::ENoAutoDimming		
		};

	typedef TEikScrollBarFlags TAknScrollBarFlags;

public:
	IMPORT_C ~CEikScrollBar();
	IMPORT_C CEikScrollBar();
public:
	// second phase construction
	IMPORT_C virtual void ConstructL(MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
	TOrientation aOrientation,TInt aLength,TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);

	// set state functions
	IMPORT_C void SetLengthL(TInt aLength);
	IMPORT_C void SetModelL(const TEikScrollBarModel* aModel);
	IMPORT_C void SetModel(const TEikScrollBarModel* aModel);
	IMPORT_C void SetLengthAndModelL(TInt aLength,const TEikScrollBarModel* aModel);
	IMPORT_C void SetModelThumbPosition(TInt aThumbPos);
	IMPORT_C void SetFocusPosToThumbPos(TInt aFocusPosition);
	IMPORT_C static TInt DefaultScrollBarBreadth();
	inline void SetScrollBarObserver(MEikScrollBarObserver* aScrollBarObserver);    // not available before Release 005u

	// information retreival functions
	inline const TEikScrollBarModel* Model() const;
	IMPORT_C TInt ThumbPosition() const;
	IMPORT_C TInt ScrollBarBreadth() const;
	IMPORT_C static TInt MinVisibleLength(const TInt aScrollBarFlags);

	// Button dimming functions
	IMPORT_C void SetDecreaseButtonsDimmed(TBool aDimmed);
	IMPORT_C void SetIncreaseButtonsDimmed(TBool aDimmed);
	IMPORT_C void SetAllButtonsDimmed(TBool aDimmed);

	inline CAknScrollButton* IncreaseNudgeButton() const;
	inline CAknScrollButton* DecreaseNudgeButton() const;

	// This function should only be used by CEikCba
	IMPORT_C void SetContainingCba(CEikCba* aCba);

	IMPORT_C void MakeVisible(TBool aVisible);

protected:      // from CCoeControl
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C TInt CountComponentControls() const;
private: // from MCoeControlObserver
	IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
private: // virtual - reserved from CCoeControl
	IMPORT_C virtual void Reserved_2();

protected:
	friend class CEikScrollBarFrame;
	// enums
	enum TPrivateScrollBarFlags
		{
		ENoComponentsToDisplay          =0x10000,
		EIncreaseButtonsDimmed          =0x20000,
		EDecreaseButtonsDimmed          =0x40000
		};

	enum TPointerDownOn
		{
		ENone,
		EHomeButton,
		EDecreasePageButton,
		EDecreaseNudgeButton,
		EDecreaseShaft,
		EThumb,
		EIncreaseShaft,
		EIncreaseNudgeButton,
		EIncreasePageButton,
		EEndButton
		};

	enum TShaftRedrawRequired
		{
		ENoRedrawRequired,
		ERedrawShaft
		};

	enum TWhichButtons
		{
		EIncreaseOnly,
		EDecreaseOnly,
		EAll
		};

	struct SEikScrollBarButtons
		{
		CAknScrollButton* iDecreaseNudge;
		CAknScrollButton* iIncreaseNudge;
		};


private:
	// construction/destruction
	IMPORT_C virtual void CreateButtonL(CAknScrollButton*& aButton,CAknScrollButton::TType aType);

	void SizeChanged();

	// set state functions
	void DoSetModel(const TEikScrollBarModel* aModel);

	CEikCba* Cba() const;

	// These functions are for use only be CEikScrollBarFrame (a friend class)
	void AddExternalFrameL(CEikScrollBarFrame* aFrame);
	void RemoveExternalFrame(CEikScrollBarFrame* aFrame);

	void DisconnectExternalFrames();

protected:
	void CreateRequiredComponentsL();
	void DestroyButton(CAknScrollButton*& aButton);
	IMPORT_C virtual void SetButtonPositionL(CAknScrollButton* aButton);
public:
    TScrollBarType ScrollBarType();
public:
	TDblQueLink iSBLink;
protected:
	SEikScrollBarButtons iButtons;
	TOrientation iOrientation;
private:
	TEikScrollBarModel iModel;
protected:    
    CEikScrollBarExtensionImpl* iExtension;
  };


/**
 * The CEikArrowHeadScrollBar class is a scroll bar which uses only
 * two small nudge button arrows to scroll up and down. It has no shaft.
 * It therefore takes up very little space.
 *
 * @since ER5U 
 * @ internal
 * Internal to Symbian
 *
 */
class CEikArrowHeadScrollBar : public CEikScrollBar
	{
public:
	IMPORT_C CEikArrowHeadScrollBar(CCoeControl* aParentWindow);
	IMPORT_C ~CEikArrowHeadScrollBar();
public: // from CEikScrollBar
	IMPORT_C void ConstructL(MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
				TOrientation aOrientation,TInt aLength,TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);
private: // from CEikScrollBar
	void CreateButtonL(CAknScrollButton*& aButton,CAknScrollButton::TType aType);
	void SetButtonPositionL(CAknScrollButton* aButton);
private:
	CCoeControl* iParentControl;
	};


/**
 * The CAknDoubleSpanScrollBar class is a scroll bar without buttons, 
 * but it has a shaft. Additionally it has in its shaft a double 
 * span feature which means that there can be another thumb inside the thumb 
 * if needed.
 *
 * This class uses TAknDoubleSpanScrollBarModel instead of TEikScrollBarModel
 * as its internal scrollbar model. TAknDoubleSpanScrollBarModel in binary 
 * compatible with TEikScrollBarModel. User must take care that TAknDoubleSpanScrollBarModel 
 * is really used in API calls in places where TEikScrollBarModel is declared.
 * 
 * @since 2.6 
 *
 */
class CAknDoubleSpanScrollBar : public CEikScrollBar
	{
public:
	IMPORT_C CAknDoubleSpanScrollBar(CCoeControl* aParentWindow);
	IMPORT_C ~CAknDoubleSpanScrollBar();

   /**
    * Sets fixed layout to scrollbar. If set, then scrollbar size
    * changes done by the CEikScrollBarFrame class are disabled. 
    *
    * @since    2.6
    * @param    aScrollBarRect     Scrollbar rectangle.         
    *
    */     
    IMPORT_C void SetFixedLayoutRect(TRect aScrollBarRect);

   /**
    * Method for constructing the object.
    *
    * @since    2.6
    * @param    aWindowOwning       True if scrollbar is to be a window owning control. 
    * @param    aScrollBarObserver  Same as in CEikScrollBar::ConstructL()
    * @param    aParent             Same as in CEikScrollBar::ConstructL()
    * @param    aOrientation        Same as in CEikScrollBar::ConstructL()
    * @param    aLength             Same as in CEikScrollBar::ConstructL()    
    * @param    aScrollBarFlags     Same as in CEikScrollBar::ConstructL()
    *
    */     
    IMPORT_C void ConstructL(TBool aWindowOwning, MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
				TOrientation aOrientation,TInt aLength,TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);
   /**
    * Gets the fixed layoutrect of the scrollbar.    
    * @since    2.6
    * @return   Scrollbar rectangle. 
    *
    */     
    TRect FixedLayoutRect();

public: // from CEikScrollBar
	IMPORT_C void ConstructL(MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
				TOrientation aOrientation,TInt aLength,TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);
    IMPORT_C void MakeVisible(TBool aVisible);

protected: // from CCoeControl
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
    IMPORT_C TInt CountComponentControls() const;

private:  // from CCoeControl
    IMPORT_C void SizeChanged();

private: // from CEikScrollBar
	void CreateButtonL(CAknScrollButton*& aButton,CAknScrollButton::TType aType);
	void SetButtonPositionL(CAknScrollButton* aButton);

   /**
    * Sets scrollbar background transparency as given in the parameter.
    * 
    * @param    aTransparentBackground   If ETrue then scrollbar will have transparent background.
    * @since    2.6
    *
    */     
    void SetTransparentBackground(TBool aTransparentBackground);


private:
	CCoeControl* iParentControl;
	};


//
// Inlines
//

inline void CEikScrollBar::SetScrollBarObserver(MEikScrollBarObserver* /*aScrollBarObserver*/)
	{ }

inline const TEikScrollBarModel* CEikScrollBar::Model() const
	{ return &iModel; }

inline CAknScrollButton* CEikScrollBar::IncreaseNudgeButton() const
	{ return iButtons.iIncreaseNudge; }

inline CAknScrollButton* CEikScrollBar::DecreaseNudgeButton() const
	{ return iButtons.iDecreaseNudge; }


#endif
