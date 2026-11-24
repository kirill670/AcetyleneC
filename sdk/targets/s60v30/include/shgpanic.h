// SHGPANIC.H
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.

#if !defined(__SHGPANIC_H__)
#define __SHGPANIC_H__

#if !defined(__E32DEF_H__)
#include <e32def.h>
#endif

/** Spreadsheet engine panic (category "SHENG") codes. 
@internalComponent
@released
*/
enum TShgPanic
	{
	/** General programming error. */
	EShgPanicBug=1,

	/** Internal evaluation stack error. */
	EShgPanicStackMemoryAllocation,
	/** Internal evaluation stack error. */
	EShgPanicStackBounds,
	/** Internal evaluation stack error. */
	EShgPanicStackPointerOutsideBounds,
	/** Internal evaluation stack error. */
	EShgPanicStackOverflow,
	/** Internal evaluation stack error. */
	EShgPanicStackUnderflow,
	/** Internal evaluation stack error. */
	EShgPanicStackMaxItemSizeIncorrect,
	/** Internal evaluation stack error. */
	EShgPanicBadStackValue,
	/** Internal evaluation stack error. */
	EShgPanicStackSafetyMarginTooSmall,

	/** Internal formula error. */
	EShgPanicFormulaNotFound,
	/** Internal formula error. */
	EShgPanicFormulaCellNotListMember,

	/** Internal limits error. */
	EShgPanicRowOutOfRange,
	/** Internal limits error. */
	EShgPanicColumnOutOfRange,
	/** Internal limits error. */
	EShgPanicInvalidCellCount,
	/** Internal type error. */
	EShgPanicBadCellType,
	/** Request to read formula of non-formula type cell. */
	EShgPanicNotFormulaCell,

	/** Formula function token unknown. */
	EShgPanicUnknownFunction,
	/** Formula operator token unknown. */
	EShgPanicUnknownOperator,
	/** Formula token unknown. */
	EShgPanicUnknownToken,
	/** Formula delimiter token unknown. */
	EShgPanicUnknownDelimiter,
	/** Internal evaluation stack error. */
	EShgPanicParametersNotConsumed,
	/** Internal base time error. */
	EShgPanicWrongBaseTime,

	/** Internal array error. */
	EShgPanicBadArrayIndex,
	/** Internal name error. */
	EShgPanicNameNotFound,
	/** Internal name error. */
	EShgPanicNameAlreadyExists,

	/** Internal array error. */
	EShgPanicOrderedArrayMemberNotFound,
	/** Internal range error. */
	EShgPanicCellOutsideRange,
	/** Internal pointer error. */
	EShgPanicNullCellPointer,

	/** Internal data error. */
	EShgPanicDataFactoryNotSet,
	/** Internal workbook error. */
	EShgPanicWorkBookNewFailed,
	/** Internal workbook error. */
	EShgPanicWorkBookIdOutOfRange,
	/** Specified worksheet cannot be found. */
	EShgPanicWorkSheetNameNotFound,
	/** Worksheet name cannot be used as specified as it is already in use. */
	EShgPanicWorkSheetNameAlreadyUsed,
	/** Internal workbook error. */
	EShgPanicWorkBookIllegalArrayPos,
	/** Internal worksheet error. */
	EShgPanicNoSuchWorkSheet,

	/** Internal error. */
	EShgPanicContainerInsertionOverIter,

	/** Internal error. */
	EShgPanicCellDataIncorrectSize,

	/** Attempted to get NULL template additional data. */
	EShgPanicTemplateAdditionalDataIsNull,
	/** Internal error. */
	EShgPanicDefaultAdditionalDataIsNull,
	/** Invalid number format. */
	EShgPanicInvalidNumberFormat
	};

GLREF_C void Panic(TShgPanic);
#endif
