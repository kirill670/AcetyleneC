/*
* ==============================================================================
*  Name        : eikbgfty.h
*  Part of     : CKON
*  Interface   : Button Group API
*  Description : Classes for constructing button groups using factory functions.
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


#ifndef EIKBGFTY_H
#define EIKBGFTY_H

// INCLUDES
#include <eikbtgpc.h>
#include <coemain.h>


/**
 * The <code>EikButtonGroupFactory</code> class stores the Button Group factory 
 * functions, which are registered. The class provides the facility to add and 
 * remove these functions from the storage array. This class is derived from 
 * <code>CCoeStatic</code>, allowing application-wide access.
 *
 * @lib eikcoctl.lib
 * @since 6.1
 */
class EikButtonGroupFactory
    {
    public:
    /**
     * Defines the information required to create a Button Group.
     *
     * @lib eikcoctl.lib
     */
    class TCreationData
        {
    public:
       /**
        * The object constructor. This constructor takes arguments required to 
        * create a Button Group.
        *
        * @param aUse The type of Button Group container.
        * @param aCommandObserver A command observer to be notified of commands 
        *                         on the container
        * @param aResourceId A resource containing descriptions of buttons in 
        *                    the Button Group. This can be <code>NULL</code> if 
        *                    buttons are to be added dynamically
        * @param aFlags The Button Group's flags
        * @param aOrientation The orientation of the Button Group's container.
        *                     This only needs to be specified for devices that 
        *                     can lay out their buttons either horizontally or 
        *                     vertically
        * @remarks
        * @see eikbtgpc.h for the range of values in
        *      <code>CEikButtonGroupContainer::TUse</code> and 
        *      <code>CEikButtonGroupContainer::TOrientation aOrientation</code>
        */
        IMPORT_C TCreationData(CEikButtonGroupContainer::TUse aUse,
                        MEikCommandObserver* aCommandObserver,
                        TInt aResourceId,TUint aFlags,
                        CEikButtonGroupContainer::TOrientation aOrientation);
    public:
        /** @internal */
        CEikButtonGroupContainer::TUse iUse;
        /** @internal */
        MEikCommandObserver* iCommandObserver;
        /** @internal */
        TInt iResourceId;
        /** @internal */
        TUint iFlags;
        /** @internal */
        CEikButtonGroupContainer::TOrientation iOrientation;
        };
    public:

        /**
        * Creates a button group of a specified type.
        *
        * @param aButtonGroupType The type of Button Group to create
        * @param aCreationData Definitions for the group and its buttons
        * @param aAddToButtonGroupStack If <code>ETrue</code>, the new Button 
        *                               Group is added to the Button Group 
        *                               control stack
        * @return the button group.
        * @remarks Button Group types supported in Series 90 are defined in
        *          TEikStockButtonGroupControls in uikon.hrh and 
        *          TEikReferenceButtonGroupControls in eikon.hrh
        * @see 
        * @internal
        */
        static MEikButtonGroup* CreateButtonGroupByTypeL(TInt aButtonGroupType,TCreationData& aCreationData,TBool& aAddToButtonGroupStack);
    };

       /**
        * defines a pointer to a method that creates a Button Group by type
        *
        * @since 6.1
        */
        typedef MEikButtonGroup* (*TCreateButtonGroupByTypeFunction)(TInt,EikButtonGroupFactory::TCreationData&,TBool&);

/**
 * The <code>CEikButtonGroupFactoryArray</code> class actually stores the 
 * Button Group factory functions, which are registered. It also provides 
 * the facility to add and remove these functions from the storage array. 
 * Notably, this class is derived from <code>CCoeStatic</code>, allowing 
 * application-wide access.
 *
 * @lib eikcoctl.lib
 * @since App-Framework_6.1
 */
class CEikButtonGroupFactoryArray : public CCoeStatic
    {
    public:

       /**
        * Adds a Button Group factory function to the storage array. 
        *
        * @param aCreateButtonGroupByTypeFunction The Button group factory 
        *                                         function to add
        * @remarks If the storage array does not exist yet, a new one is 
        *          created and the factory function is added as the first 
        *          element
        * @see
        */
        IMPORT_C static void AppendFactoryFunctionL
            (TCreateButtonGroupByTypeFunction aCreateButtonGroupByTypeFunction);

       /**
        * Removes a Button Group factory function from the storage array.
        *
        * @param aCreateButtonGroupByTypeFunction The Button Group factory 
        *                                         function to remove
        * @remarks
        * @see
        */
        IMPORT_C static void RemoveFactoryFunction(TCreateButtonGroupByTypeFunction aCreateButtonGroupByTypeFunction);
    public:
       /** @internal */
        static CArrayFixFlat<TCreateButtonGroupByTypeFunction>* ButtonGroupFactoryFuncArray();
    public:

       /**
        * The object destructor.
        */
        ~CEikButtonGroupFactoryArray();
    private:
        inline CEikButtonGroupFactoryArray();
        inline static CEikButtonGroupFactoryArray* Self();
    private:
        CArrayFixFlat<TCreateButtonGroupByTypeFunction>* iButtonGroupFactoryFuncArray;
    };


#endif  // EIKBGFTY_H

// End of File
