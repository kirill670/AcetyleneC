/*
* =============================================================================
*  Name        : cknflopr.h
*  Part of     : CKON
*  Interface   : Progress Banner API
*  Description : The CCknFloatingProgressIndicatorBase class implements a base
*                class for the Progress Bar which appears in the right bottom
*                corner of the application area.
*                The CCknFloatingProgressBar class implements a Progress Bar
*                which displays text and a growing slide as an indicator for
*                the time taken for and action or size of transmission.
*                The CCknFloatingProgressBall class implements a Progress Bar
*                which displays an animation when the time taken is not known.
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
* =============================================================================
*/


#ifndef CKNFLOPR_H
#define CKNFLOPR_H


// INCLUDES
#include <eikbctrl.h>
#include <eiklabel.h>
#include <eikon.hrh>

// CLASS DECLARATIONS

/**
* The <code>CCknFloatingProgressIndicatorBase</code> class implements a base
* class for the Progress Bar that appears in the top right corner of the 
* application area.
*
* @lib cknctl.lib
* @since Series90 1.0
* @internal
*/

class CCknFloatingProgressIndicatorBase : public CEikBorderedControl
    {
    public:
    // Constructors and destructor


        /**
        * The object destructor.
        */
        virtual ~CCknFloatingProgressIndicatorBase();
    // New methods
        
        /**
        * Sets and changes the text of a Floating Progress Indicator
        * object.
        *
        * @param aText Reference to the descriptor wich contains the text
        *        to be set
        * @remarks
        * @see
        */
        IMPORT_C void SetTextL(const TDesC& aText);
        /**
        * Gets a pointer font used in displaying text.
        *
        * @return Pointer font
        * @remarks
        * @see
        */
        IMPORT_C const CFont* Font() const;
        /**
        * Returns the maximum length that is available for text, in pixels.
        *
        * @return maximum length in pixels left for text after allowance for
        *         the indicator width
        * @remarks 
        */
        IMPORT_C TInt TextMaxWidthInPixels() const;

    // Methods from base classes

        /**
        * Method for setting the layout of a Floating Progress Indicator
        * object.
        *
        * @remarks Called whenever the control's size may have changed
        * - e.g. when SetTextL() is called.
        * @see CCoeControl
        */
        void SizeChanged();
        /**
        * Method for calculating the size of a Floating Progress Indicator
        * object.
        *
        * @return the minimum size
        * @remarks Used when calculating the position of the control.
        * @see CCoeControl
        */
        IMPORT_C TSize MinimumSize();
    protected:  // Methods
    // Methods from base classes
        /**
        * Method for getting the number of component controls in a Floating
        * Progress Indicator object.
        *
        * @return number of component controls
        * @remarks
        * @see CCoeControl.
        */
        IMPORT_C TInt CountComponentControls() const;
        /**
        * Method for getting pointer of type <code>CCoeControl</code>
        * to a component control by index.
        *
        * @param aIndex Index of the component control to be returned 
        *        (0 for text label; 1 for progress indicator)
        * @return pointer of type <code>CCoeControl</code>
        * @remarks Used to access either of the component controls
        * @see CCoeControl.
        */
        IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

    // New Methods
        
        /**
        * Method for doing base construction for a Floating Progress Indicator
        * object.
        *
        * @param aIndicatorControl Pointer to a control to be set as progress
        *        indicator
        * @remarks Called by inheriting classes to perform
        *          common initialisation.
        */
        void BaseConstructL(CCoeControl* aIndicatorControl);
        /**
        * Method for getting a pointer to the second component control.
        *
        * @return pointer of type <code>CCoeControl</code>
        * @remarks The returned pointer is to the progess indicator component 
        *          control
        */
        CCoeControl* ProgressIndicator() const;

        /**
        * Method for setting the position of the Floating Progress Indicator
        *
        * @param aPos Pointer to the <code>TPoint</code> object. If 
        * <code>aPos==NULL</code> then the default position will be used
        * @return
        * @remarks The default position is the top right. If specified,
        *          the bottom right of the component is set to <code>aPos</code>.
        */
        void SetDefaultPosition(const TPoint* aPos);
    private: //Methods
        void Draw(const TRect& aRect) const; //From CCoeControl
    private:     // Data
        CEikLabel* iText;
        CCoeControl* iProgressIndicator;
    };

/**
 * The <code>CCknFloatingProgressBar</code> class implements a Progress Banner 
 * that contains a Progress Bar. It displays text and a growing slide as an 
 * indicator of the duration of an operation.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CCknFloatingProgressBar : public CCknFloatingProgressIndicatorBase
    {
    public:
    // Constructors and destructor

        /**
        * Starts the two-phase object construction.
        *
        * @param aText A reference to the descriptor that contains the text
        *        to be shown in the Progress Bar
        * @param aFinalValue The upper limit of the range covered by the 
        *        progress indicator
        * @return the pointer to the new Progress Bar
        * @remarks <code>aFinalValue</code> must not be zero to avoid a
        *          divide-by-zero error
        */
        IMPORT_C static CCknFloatingProgressBar* NewL(const TDesC& aText, 
                                                 TInt aFinalValue);

        /**
        * Starts the two-phase object construction.
        *
        * @param aText A reference to the descriptor that contains the text
        *        to be shown in the Progress Bar
        * @param aFinalValue The value that the Progress Bar is set to, 
        *                    when the progress being monitored is complete
        * @param aPos The bottom right corner of the control. <code>aPos</code>
        *             can be <code>NULL</code>
        * @param aTextType Progress text type; either none, fraction, or percent. See 
        *                  enum <code>TEikProgressTextType</code> in eikon.hrh
        * @return the pointer to the new Progress Bar
        * @remarks <code>aFinalValue</code> must not be zero to avoid a
        *          divide-by-zero error
        */
    
        IMPORT_C static CCknFloatingProgressBar* NewL(const TDesC& aText, 
                                                 TInt aFinalValue, 
                                                 const TPoint* aPos, 
                TEikProgressTextType aTextType=EEikProgressTextPercentage);
    // New methods
        
        /**
        * Updates the value of a 
        * <code>CCknFloatingProgressBar</code> object and redraws the Progress
        * Bar.
        *
        * @param aNewValue The value to be set
        * @remarks If <code>aNewValue</code> is greater than the final value 
        *          (the upper range limit), <code>aNewValue</code> is changed 
        *          to be the same as the final value
        */
        IMPORT_C void UpdateValue(TInt aNewValue);

        /**
        * Sets the final value, that is, the upper limit, of a 
        * <code>CCknFloatingProgressBar</code> object. When the current value 
        * reaches this, following a call to <code>UpdateValue</code> the 
        * Progress Bar is completely filled.
        *
        * @param aFinalValue The upper range limit for the control
        * @remarks <code>aFinalValue</code> must be greater than 0, otherwise 
        *          the application crashes with an unhandled divide-by-zero 
        *          error. This method can be called at any time after the 
        *          Progress Bar is created and rescales the filled 
        *          part of the Progress Bar
        * @see
        */
        IMPORT_C void SetFinalValue(TInt aFinalValue);
    private: //Methods
        CCknFloatingProgressBar(TInt aFinalValue);
        void ConstructL(TEikProgressTextType aTextType);
    private:     // Data
        TInt iFinalValue;
    };

/**
 * The <code>CCknFloatingProgressBall</code> class implements a Progress Banner
 * that displays a Progress Ball animation when the duration of the operation 
 * is not known.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CCknFloatingProgressBall : public CCknFloatingProgressIndicatorBase
    {
    public:
    // Constructors and destructor

        /**
        * Starts the two-phase object construction.
        *
        * @param aText A reference to a descriptor to be shown in the  
        *              Progress Banner
        * @return pointer to a new Progress Banner

        */
        IMPORT_C static CCknFloatingProgressBall* NewL(const TDesC& aText);

        /**
        * Starts the two-phase object construction.
        *
        * @param aText A reference to a descriptor to be shown in the  
        *              Progress Banner
        * @param aPos The bottom right corner of the control
        * @return a pointer to a new Progress Banner
        * @remarks Used to position the control. <code>aPos</code>
        *          can be <code>NULL</code>, in which case the control is 
        *          positioned at the top right corner of the owning control's 
        *          rectangle
        */
        IMPORT_C static CCknFloatingProgressBall* NewL(const TDesC& aText, 
                                                  const TPoint* aPos);
    private: //Methods
        void ConstructL();
    };


#endif      // CKNFLOPR_H   
            
// End of File
