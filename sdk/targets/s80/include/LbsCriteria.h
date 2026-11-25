/*
* ==============================================================================
*  Name        : LbsCriteria.h
*  Part of     : Mobile Location Framework/Core
*  Interface   : --
*  Description :
*   ?description_line
*  Version     :
*
*  Copyright (c) 2004 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
*
* ==============================================================================
*/
// LbsCriteria.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __LBSCRITERIA_H__
#define __LBSCRITERIA_H__

#include <LbsCommon.h>


class TPositionSelectionOrder
/**
 * This class is used as part of the TPositionCriteria class to chose a
 * positioning module that will provide the desired quality of information.
 * It allows position-quality-metrics to be given priorities, enabling them
 * to be given preference in the decision.
 *
 * @publishedAll
 */
	{
public:
	/**
	 * Specifies the priority of selection parameters.
	 */
	enum TOrder
		{
		EOrderDontCare   = 0,
		EOrderDefault    = 1,
		EOrderVeryLow    = 25,
		EOrderLow        = 50,
		EOrderFairlyLow  = 75,
		EOrderMedium     = 100,
		EOrderFairlyHigh = 125,
		EOrderHigh       = 150,
		EOrderVeryHigh   = 175
		};

	/**
	 * Specifies the quality of position metrics that can be prioritized.
	 */
	enum TField
		{
		EFieldTimeToFirstFix,
		EFieldTimeToNextFix,
		EFieldHorizontalAccuracy,
		EFieldVerticalAccuracy,
		EFieldCost,
		EFieldPower,
		EFieldNumFields,       // Do not use this value. Must appear after all other field values.
		EFieldLast = KMaxTInt8 // Do not use this value. Must appear at end.
		};

	IMPORT_C TPositionSelectionOrder();

	IMPORT_C TInt SetOrderTimeToFirstFix(TOrder aOrder);
	IMPORT_C TInt SetOrderTimeToNextFix(TOrder aOrder);

	IMPORT_C TInt SetOrderHorizontalAccuracy(TOrder aOrder);
	IMPORT_C TInt SetOrderVerticalAccuracy(TOrder aOrder);

	IMPORT_C TInt SetOrderCostIndicator(TOrder aOrder);
	IMPORT_C TInt SetOrderPowerConsumption(TOrder aOrder);

	IMPORT_C void ResetSelectionOrder();
	IMPORT_C void ClearSelectionOrder();

	IMPORT_C TUint NumSelectionItems() const;
	IMPORT_C TInt GetSelectionItem(TUint aIndex,
	                               TField& aField,
	                               TOrder& aOrder) const;

protected:
	struct SItem
	/**
	 * Stores a field / priority pair.
	 *
	 * @publishedAll
	 */
		{
		/** A position quality metric identifier. */
		TField iField;
		/** The priority given to the iField position quality metric. */
		TOrder iOrder;
		};

protected:
	TInt AddItem(TField aField, TOrder aOrder);

protected:
	/** The number of selection items in the iItems array. */
	TUint iNumItems;
	/** Array of users position quality priorities. */
	SItem iItems[KPositionMaxSectionFields];
	};


// If the following line generates an error, too many fields have been added
// to the TPositionSelectionOrder::TOrder enumeration, some must be removed
// to maintain BC.
POSITION_COMPILE_TIME_ASSERT(TPositionSelectionOrder::EFieldNumFields <= KPositionMaxSectionFields);


class TPositionCriteriaBase : public TPositionClassTypeBase
/**
 * The base class for classes used to store position module selection
 * criteria information.
 *
 * @publishedAll
 */
	{
protected:
	IMPORT_C TPositionCriteriaBase();
	IMPORT_C TPositionCriteriaBase(TPositionModuleInfo::TCapabilities aCapabilityMask);

public:
	IMPORT_C void AddRequiredCapabilities(TPositionModuleInfo::TCapabilities aCapabilityMask);
	IMPORT_C void ClearRequiredCapabilities();
	IMPORT_C TPositionModuleInfo::TCapabilities RequiredCapabilities() const;

	IMPORT_C void SetRequiredQuality(const TPositionQuality& aPosQuality);
	IMPORT_C void GetRequiredQuality(TPositionQuality& aPosQuality) const;

	IMPORT_C void SetSelectionOrder(const TPositionSelectionOrder& aSelectionOrder); 
	IMPORT_C void GetSelectionOrder(TPositionSelectionOrder& aSelectionOrder) const;

	IMPORT_C void ResetCriteria();
	IMPORT_C void ClearCriteria();

protected:
	/** The capabilities a positioning module must have. */
	TPositionModuleInfo::TCapabilities iRequiredCaps;
	/** The quality required of a positioning module. */
	TPositionQuality iRequiredQuality;
	/** The priorities assigned to the various quality metrics. */
	TPositionSelectionOrder	iSelectionOrder;
	};


class TPositionCriteria : public TPositionCriteriaBase
/**
 * The standard class criteria class for selecting a positioning module.
 *
 * @publishedAll
 */
	{
public:
	IMPORT_C TPositionCriteria();
	IMPORT_C TPositionCriteria(TPositionModuleInfo::TCapabilities aCapabilityMask);

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[4];
	};

#endif // __LBSCRITERIA_H__
