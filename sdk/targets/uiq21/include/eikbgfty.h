// EIKBGFTY.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKBGFTY_H__
#define __EIKBGFTY_H__

#include <eikbtgpc.h>
#include <coemain.h>

/**
 *
 * Stores the button group factory functions which are registered.
 *
 * Provides the facility to add and remove these functions from the
 * storage array. This class is derived from <code>CCoeStatic</code>,
 * allowing application-wide access.
 *
 * @since 6.1
 * @lib "eikcoctl.lib"
 */
class EikButtonGroupFactory
	{
public:
	/**
	 * Defines information required to create a button group.
	 * @lib "eikcoctl.lib"
	 */
	class TCreationData
		{
	public:
		IMPORT_C TCreationData(CEikButtonGroupContainer::TUse aUse,
						MEikCommandObserver* aCommandObserver,
						TInt aResourceId,TUint aFlags,
						CEikButtonGroupContainer::TOrientation aOrientation);
	public:
		CEikButtonGroupContainer::TUse iUse;
		MEikCommandObserver* iCommandObserver;
		TInt iResourceId;
		TUint iFlags;
		CEikButtonGroupContainer::TOrientation iOrientation;
		};
public:
	static MEikButtonGroup* CreateButtonGroupByTypeL(TInt aButtonGroupType,TCreationData& aCreationData,TBool& aAddToButtonGroupStack);
	};

/**
 *
 * Defines a pointer to a function which creates a button group by type.
 * @since 6.1
 * @lib ""
 */
typedef MEikButtonGroup* (*TCreateButtonGroupByTypeFunction)(TInt,EikButtonGroupFactory::TCreationData&,TBool&);

/**
 * The CEikButtonGroupFactoryArray class actually stores the button group factory functions
 * which are registered.  It also provides facility to add and remove these functions from
 * the storage array.  Notably this class is CCoeStatic derived, allowing application wide
 * access.
 *
 * @since App-Framework_6.1
 */
class CEikButtonGroupFactoryArray : public CCoeStatic
	{
public:
	IMPORT_C static void AppendFactoryFunctionL(TCreateButtonGroupByTypeFunction aCreateButtonGroupByTypeFunction);
	IMPORT_C static void RemoveFactoryFunction(TCreateButtonGroupByTypeFunction aCreateButtonGroupByTypeFunction);
public:
	static CArrayFixFlat<TCreateButtonGroupByTypeFunction>* ButtonGroupFactoryFuncArray();
public:
	~CEikButtonGroupFactoryArray();
private:
	inline CEikButtonGroupFactoryArray();
	inline static CEikButtonGroupFactoryArray* Self();
private:
	CArrayFixFlat<TCreateButtonGroupByTypeFunction>* iButtonGroupFactoryFuncArray;
	};

#endif
