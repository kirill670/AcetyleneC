/*
* ==============================================================================
*  Name        : cknanim.h
*  Part of     : CKON
*  Interface   : Animation API
*  Description : 
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

#ifndef CKNANIM_H
#define CKNANIM_H


// INCLUDES
#include <coecntrl.h>


// DATA TYPES


// FORWARD DECLARATIONS
class TResourceReader;
class RAnimDll;
class RBitmapAnim;
class CBitmapAnimClientData;
class CBitmapFrameData;
class CCknAnimationControlIdler;

/**
* The <code>CCknAnimationControl</code> class implements Ckon's interface to
* the Animation .dll. Clients must call <code>NewL()</code> and, after 
* construction, <code>SetContainerWindowL()</code>. There are three methods
* to initialize the contents of the Animation: <code>StaticConstructL()</code>, 
* <code>ConstructFromClientDataL()</code>, and <code>ConstructFromResourceL()</code>.
* The size of the control should be set after the contents have been 
* initialized, using the size returned from the method 
* <code>MinimumSize()</code>.
*
* @lib cknctl.lib
* @since Series90 1.0
*/
class CCknAnimationControl : public CCoeControl
    {
    public:
        /**
        * Constructs and returns a pointer to a <code>CCknAnimationControl</code> 
        * object.
        *
        * @return the newly instantiated object
        * @remarks
        * @see
        */
        IMPORT_C static CCknAnimationControl* NewL();
        
        /**
        * The object destructor.
        */
        IMPORT_C virtual ~CCknAnimationControl();
        
        /**
        * Creates a resource reader from the Animation control resource 
        * <code>aResourceId</code>.
        * There are two alternative methods that can be used to initialize 
        * the contents of the Animation.
        *
        * @param aResourceId The resource identifier for the Animation
        * @remarks  The resource struct is <code>ANIM</code> and the control 
        *           ID is <code>ECknCtAnimationControl</code>
        * @see      <code>ConstructFromClientDataL()</code>
        * @see      <code>ConstructFromResourceL()</code>
        */
        IMPORT_C void StaticConstructL(TInt aResourceId);

        /**
        * Initializes the Animation with information supplied in a
        * <code>CBitmapAnimClientData</code> object. 
        * There are two alternative methods that can be used to initialize 
        * the contents of the Animation.
        *
        * @param aBitmapAnimData The data that describes the Animation
        * @remarks Ownership of the argument is transferred on calling
        *           this method
        * @see <code>StaticConstructL()</code>
        * @see <code>ConstructFromResourceL()</code>
        * @see <code>CBitmapAnimClientData</code>
        */
        IMPORT_C void ConstructFromClientDataL(CBitmapAnimClientData* aBitmapAnimData);

        /**
        * Starts the Animation.
        *
        * @remarks
        * @see
        */
        IMPORT_C void StartAnimationL();

        /**
        * Stops the Animation.
        *
        * @remarks
        * @see
        */
        IMPORT_C void StopAnimationL();

        /**
        * Starts or stops the Animation depending on the value of the boolean 
        * parameter.
        *
        * @param aStart Defines whether to start or stop the
        *               Animation. If <code>ETrue</code> start Animation; 
        *               otherwise, stop it
        * @remarks
        * @see
        */
        IMPORT_C void AnimateL(TBool aStart);

        /**
        * Returns the total length of the client Animation, in milliseconds.
        *
        * @return the total length, in milliseconds
        * @remarks
        * @see
        */
        IMPORT_C const TInt Duration() const;
        /**
        * Constructs the Animation control with information supplied in a 
        * resource file. The control ID is <code>ECknCtAnimationControl</code>. 
        * There are two alternative methods that can be used to initialize 
        * the contents of the Animation.
        *
        * @param aReader A resource reader
        * @remarks The resource type is <code>ANIM</code>
        * @see <code>StaticConstructL()</code>
        * @see <code>ConstructFromClientDataL()</code>
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
        
        /**
        * Gets the minimum size for the Animation control.
        * 
        * @return the minimum size of the Animation control
        * @remarks The returned value from this method should be used to set 
        *          the size of the control following the initialization of the
        *          contents 
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual TSize MinimumSize();
    private: //Methods
        // from CCoeControl
        virtual void SizeChanged();
        virtual void PositionChanged();
    protected:  // Methods
        /**
        * C++ default constructor.
        *
        * @return
        * @remarks  Sets iMaximumWidth to the default value (240 pixels),
        *           but does no further object initialisation
        * @see
        */
        CCknAnimationControl();
        /**
        * Second phase constructor.
        *
        * @return
        * @remarks
        * @see
        */
        void BaseConstructL();
    private:
        // Classes
        class CCknAnimationControlIdler : public CIdle
            {
        public:
            static CCknAnimationControlIdler* NewL();
        private:
            CCknAnimationControlIdler() : CIdle(EPriorityHigh) { }
            };
        enum TAnimationControlFlags
            {
            EInitialized=0x01
            };
        // Methods
        void InitializeL();
        void ReadAnimDataFromResourceL(TResourceReader &aReader);
        CBitmapFrameData* ReadFrameDataFromResourceL(TResourceReader& aReader, const TDesC& aFileName, TUid aMbmUid);
        void CreateAndStartIdlerL();
        static TInt StartAnimationCallBackL(TAny* aThis);
        void DoStartAnimationL();
    private:     // Data
        CBitmapAnimClientData* iBitmapAnimData;
        RBitmapAnim* iAnimation;
        RAnimDll* iAnimDll;
        TUint32 iFlags;
        CCknAnimationControlIdler* iStartAnimationIdler;
    protected:     // Data
        /** BC mode. */
        TBool iBcMode;
    };

/**
*  CCknAnimationControlBC is added for BC where the resource file didn't have a mbmUid,
*  in BC mode that member data is not read from the resource file
*
*  This class should not be used by user clients. Use CCknAnimationControl.
*  @deprecated
*  @internal
*
*  Link against CKNCTL.LIB
*/
class CCknAnimationControlBC : public CCknAnimationControl
    {
    public:  // Declarations
    friend class CCknCtlLibrary;
    private: //Methods
        CCknAnimationControlBC();
        IMPORT_C static CCknAnimationControlBC* NewL(); // for BC access via .def file only
    };


#endif      // CKNANIM_H   
            
// End of File
