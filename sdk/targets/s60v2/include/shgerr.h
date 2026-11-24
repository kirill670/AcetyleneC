// SHGERR.H
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.


#if !defined(__SHGERR_H__)
#define __SHGERR_H__

/** Gets an error string resource number from a TShgError error code. */
#define SHG_ERROR_RESOURCE(x) (R_SHG_ERROR_ARGUMENT_TYPE_MISMATCH-1-x)

/** Spreadsheet engine error codes. 
@publishedAll
@released
*/
enum TShgError
	{
	/** Success. */
	EShgNoError=0,
	/** Argument type mismatch. */
	EShgArgumentTypeMismatch=-1,
	/** Cell is protected. */
	EShgCellProtected=-2,
	/** Formula is too complex, */
	EShgFormulaTooComplex=-3,
	/** Illegal character specified. */
	EShgIllegalCharacter=-4,
	/** Invalid range specified. */
	EShgInvalidRange=-5,
	/** Invalid name specified. */
	EShgInvalidName=-6,
	/** Mismatched left bracket. */
	EShgMismatchedLeftBracket=-7,
	/** Mismatched right bracket. */
	EShgMismatchedRightBracket=-8,
	/** Syntax error. */
	EShgSyntaxError=-9,
	/** Shifting cells moves them off the worksheet. */
	EShgShiftingCellsGoesOffWorkSheet=-10,
	/** Shifting cells loses cell data. */
	EShgShiftingCellsLosesCellData=-11,
	/** Non-adjacent selections. */
	EShgNonadjacentSelections=-12,
	/** Incompatible copy and paste areas. */
	EShgIncompatibleCopyAndPasteAreas=-13,
	/** Paste operation is off the worksheet. */
	EShgPasteOffWorksheet=-14,
	/** Paste operation is not available. */
	EShgPasteNotAvailable=-15,
	/** Paste area is the wrong shape. */
	EShgPasteAreaIsWrongShape=-16,
	/** Illegal worksheet name. */
	EShgIllegalWorkSheetName=-17,
	/** Worksheet name is already used. */
	EShgWorkSheetNameAlreadyUsed=-18,
	/** The current worksheet cannot be deleted. */
	EShgCannotDeleteCurrentWorkSheet=-19,
	/** Invalid cell. */
	EShgInvalidCell=-20,
	/** Name already exists. */
	EShgNameAlreadyExists=-21,
	/** Name does not exist. */
	EShgNameDoesNotExist=-22,
	/** Bad name data. */
	EShgBadNameData=-23,
	/** Name contains illegal characters. */
	EShgNameContainsIllegalCharacters=-24,
	/** Formulas cannot be named. */
	EShgNamedFormulaNotSupported=-25,
	/** Error in attempting to delete cell data. */
	EShgClearError=-26,
	/** Invalid worksheet name length. */
	EShgInvalidWorkSheetNameLength=-27
	};
#endif

