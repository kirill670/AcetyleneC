// SHGTOKEN.H
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.

#if !defined(__SHGTOKEN_H__)
#define __SHGTOKEN_H__

#if !defined(__E32STD_H__)
#include <e32def.h>
#endif

/** Size of formula token. */
const TInt KTokenByteSize = 2;

class Token
/** Formula token class and argument flag definitions. 
@publishedAll
@released
*/
	{
public:
	/** Formula token class flag definitions. */
	enum TLexTokenClass	
		{
		/** Token represents an operator. */
		EClassOperator=0,
		/** Token represents a delimiter. */
		EClassDelimiter=1,
		/** Token represents a function. */
		EClassFunction=2,
		/** Token represents an operand. */
		EClassOperand=3
		};
	/** Function argument type flag definitions. */
	enum TFunctionArgumentType 
		{
		/** Function expects a number argument. */
		ETypeNumber=0x00,
		/** Function expects a range argument. */
		ETypeRange=0x01,
		/** Function expects any argument type. */
		ETypeAll=0x02,
		/** Function expects a variable argument. */
		ETypeVariable=0x03
		};
	/** Function multiple arguments flag definition. */
	enum 
		{
		/** Function has multiple arguments. */
		EMultipleArguments=0xff
		};
	};

/** Tokens for parts of a formula.

In the descriptions below, the string equivalent of a token is given as for 
the English language spreadsheet engine resource file. 
@publishedAll
@released
*/
enum TFormulaToken
	{
// Operators
	/** Indicates start of the formula string. */
	ETokStart=0,
	/** Less than comparison operator. */
	ETokOpLT,
	/** Less than or equal comparison operator. */
	ETokOpLE,
	/** Greater than comparison operator. */
	ETokOpGT,
	/** Greater than or equal comparison operator. */
	ETokOpGE,
	/** Not equal comparison operator. */
	ETokOpNE,
	/** Equality comparison operator. */
	ETokOpEQ,
	/** Addition operator. */
	ETokOpAdd,
	/** Subtraction operator. */
	ETokOpSub,
	/** Multiplication operator. */
	ETokOpMul,
	/** Division operator. */
	ETokOpDiv,
	/** To the power operator. */
	ETokOpPower,
	/** Unary plus operator. */
	ETokOpUnaryPlus,
	/** Unary minus operator. */
	ETokOpUnaryMinus,
	/** Logical "NOT" operator. */
	ETokOpNOT,//unary
	/** Logical "AND" operator. */
	ETokOpAND,
	/** Logical "OR" operator. */
	ETokOpOR,
	/** String concatenation operator ("&"). */
	ETokOpConcatenate,
// Delimiters 
	/** Open bracket. */
	ETokDmOpnBkt,
	/** Indicates first delimiter token. */
	ETokFirstDelimiter=ETokDmOpnBkt,
	/** Close bracket. */
	ETokDmClsBkt,
	/** Argument separator (comma). */
	ETokDmArgumentSeparator,
	/** End-of-line delimiter (NULL). */
	ETokDmEOL,
// Other Delimiters		
	/** Database special token. */
	ETokDmDBSTK,
	/** Stop punctuation character. */
	ETokDmStop,
	/** Colon character. */
	ETokDmCOLON,
	/** Absolute reference character. */
	ETokDmAbsolute,
	/** Backtick character. */
	ETokDmTick,
	/** Quote character. */
	ETokDmQuote,
	/** Hat (caret) character. */
	ETokDmHAT,
	/** Backslash character. */
	ETokDmBackSlash,
// Lexer Flag - never put into formulae
	/** Internal lexer flag. */
	ETokLexNoTokSaved,
// Operands
	/** Real number operand. */
	ETokCnReal,
	/** Integer operand. */
	ETokCnInt,
	/** 8-bit integer operand. */
	ETokCnInt8,
	/** 16-bit integer operand. */
	ETokCnInt16,
	/** Reserved for future use. */
	ETokCnNull,//reserved
	/** Reserved for future use. */
	ETokCnArray,// reserved
	/** Name operand. */
	ETokCnName,
	/** Text operand. */
	ETokCnText,
	/** Cell reference operand. */
	ETokCnCell,		
	/** Range reference operand. */
	ETokCnRange,
// Stat function helpers
	/** Statistical function range delimiter token. */
	ETokFnStatRange,
	/** Statistical function literal delimiter token. */
	ETokFnStatLit,
	/** Statistical function end delimiter token. */
	ETokFnStatEnd,

// Functions - ETokFnError is the first function in Functions[]

// Error functions
	/** Indicates first function token. */
	ETokFirstFn,
	/** Null ("#NULL!") error.
	
	The information in the cell refers to an intersection of ranges that do not 
	in fact intersect. */
	ETokFnErrNull=ETokFirstFn,
	/** Division by zero ("#DIV/0!") error. */
	ETokFnErrDivByZero,
	/** Bad value ("#VALUE!") error.
	
	A formula contains the wrong kind of item, such as =3+"ghost". */
	ETokFnErrValue,
	/** Bad reference ("#REF!") error. */
	ETokFnErrRef,
	/** Bad name ("#NAME?") error. */
	ETokFnErrName,
	/** Bad number ("#NUM!") error.
	
	The information in the cell involves an impossible calculation, or one whose 
	result lies outside of the sheet's range. */
	ETokFnErrNum,
	/** Not available ("#N/A") error.
	
	No information is available for the current cell. */
	ETokFnErrNa,

// Logical functions
	/** FALSE returns FALSE or 0. */
	ETokFnFALSE,
	/** IF(x,then,else) where x, then and else may be cell references, values or expressions. 
	Returns the value of then if x is non-zero (true), or the value of else if 
	x is zero (false). */
	ETokFnIF,
	/** TRUE returns TRUE or 1. */
	ETokFnTRUE,

// Information functions
	/** CELL(information,range) returns a type of information about the upper left 
	cell in a range. The text string 'information' can have the values "ROW" , 
	"COL", "ADDRESS" or "CONTENTS", which return the row number, column number, 
	cell reference or the contents respectively. */
	ETokFnCELL,
	/** ERROR.TYPE(x) returns a number between 1 and 7, according to the type of error 
	value (see ETokFnErrNull etc.) that exists in cell x. */
	ETokFnERRORTYPE,
	/** ISBLANK(x) returns TRUE if x contains no information, or FALSE if x contains 
	information. */
	ETokFnISBLANK,
	/** ISERR(x) where x is a cell reference returns TRUE if the value in x is any 
	error except #N/A, otherwise it returns FALSE. */
	ETokFnISERR,
	/** ISERROR(x) where x is a cell reference returns TRUE if the value in x is any 
	error, otherwise it returns FALSE. */
	ETokFnISERROR,
	/** ISLOGICAL(x) returns TRUE if the information in cell x is logical, FALSE if 
	it is not. */
	ETokFnISLOGICAL,
	/** ISNA(x) where x is a cell reference returns TRUE if the value in x is #N/A, 
	or FALSE if the value in x is not #N/A. */
	ETokFnISNA,
	/** ISNONTEXT(x) returns TRUE if the information in x is not text, or FALSE if 
	the information in x is text. */
	ETokFnISNONTEXT,
	/** ISNUMBER(x) returns TRUE if x is a number or a cell containing either a number 
	or a formula which returns a number. Otherwise it returns FALSE. */
	ETokFnISNUMBER,
	/** ISTEXT(x) returns TRUE if the information in x is text, or FALSE if the information 
	in x is not text. */
	ETokFnISTEXT,
	/** N(x) returns the number in a cell or in the top left cell of a range. If the 
	cell does not contain a number, Sheet returns FALSE. */
	ETokFnN,
	/** TYPE(x) returns a code according to the type of information x contains. */
	ETokFnTYPE,

	// lookup functions
	/** ADDRESS(row_number,column_number) returns an absolute cell reference as a string, 
	given the row and column numbers, e.g. =ADDRESS(5,4) returns '$D$5'. */
	ETokFnADDRESS,
	/** COLUMN(x) returns the column number of a cell, or the number of the first column 
	in a range. */
	ETokFnCOLUMN,
	/** COLUMNS(range) returns the number of columns in a range. */
    ETokFnCOLUMNS,
	/** HLOOKUP(x,range,offset) looks along the top row of a range until it finds x. 
	It then counts down to the cell which is offset rows below, taking the row 
	that x is in as 1, and returns the value contained in that cell. The values 
	in the first row of the range must be in ascending order. */
	ETokFnHLOOKUP,
	/** INDEX(range,column,row) returns the contents of the cell at position (column,row) 
	in range, where the top left cell in range is column 1, row 1. */
	ETokFnINDEX,
	/** INDIRECT(x) returns the information stored in the first cell that the cell 
	x refers to. So, if B5 contains 'A2' and A2 contains '6', the function =INDIRECT(B5) 
	will return 6. */
    ETokFnINDIRECT,
	/** LOOKUP(x, range1, range2) looks for x (either a string or a number) in range 
	1, then returns the value in the corresponding cell in range2. Each of the 
	ranges should be either a single row or a single column of cells, and they 
	must both be equal in length. */
	ETokFnLOOKUP,
	/** OFFSET(reference,rows,columns) returns a new reference offset by rows and columns 
	from the one you specify. Use positive numbers for rows and columns to offset 
	right and down, and negative ones to offset left and up. If a range is specified 
	in reference, the offset will be from the top left corner of the range. */
    ETokFnOFFSET,
	/** ROW(x) returns the row number of a cell, or the number of the first row in 
	a range. */
	ETokFnROW,
	/** ROWS(range) returns the number of rows in a range. */
	ETokFnROWS,
	/** VLOOKUP(x,range,offset) works the same way as HLOOKUP, but counts down first, 
	then across. The values in the first column of the range must be in ascending 
	order. */
    ETokFnVLOOKUP,

	// text functions
	/** CHAR(x) returns the character indicated by the character code x. */
	ETokFnCHAR,
	/** CODE(string) returns the character code for the first character in string. 
	E.g. =CODE("Hillcrest") returns the value 72, the character code for 'H'. */
	ETokFnCODE,
	/** EXACT(string1,string2) will return TRUE if string1 is exactly the same as string2, 
	otherwise it will return FALSE. The comparison takes account of case and accents. */
	ETokFnEXACT,
	/** FIND(searchstring,string,start_position) returns the position in string where 
	searchstring starts. The search begins at start_position. Make start position 
	1 to start searching from the first character, 2 to start at the second, and 
	so on. */
	ETokFnFIND,
	/** LEFT(string,n) returns the first n letters of string. E.g. =LEFT("discotheque",5) 
	will return 'disco'. */
	ETokFnLEFT,
	/** LEN(string) returns the number of characters, including spaces, in the string. 
	E.g. =LEN("Hillcrest") will return the value 9. */
	ETokFnLENGTH,
	/** LOWER(string) returns the string converted entirely to lower case. E.g. =LOWER("Clive") 
	will return 'clive'. */
	ETokFnLOWER,
	/** MID(string,start_position,n) returns a string n characters long, taken from 
	the start_position in string. For the start position, 0 is the first character, 
	1 the second and so on. */
	ETokFnMID,
	/** PROPER(string) returns the string with the first letter of each word in upper 
	case and the rest in lower case. E.g. =PROPER("clive browning") returns 'Clive 
	Browning'. */
	ETokFnPROPER,	
	/** REPLACE(string,start_position,n,newstring) removes n characters from string, 
	starting from start_position, then inserts newstring at start_position, and 
	returns the resulting string. E.g. =REPLACE("electorate",6,5,"ion") returns 
	'election'. */
	ETokFnREPLACE,	
	/** REPT(string,n) returns string repeated n times. E.g. =REPT("*",50) will return 
	a bar '*****' 50 characters long. */
	ETokFnREPT,	
	/** RIGHT(string,n) returns the last n letters of a string. E.g. =RIGHT("farmhouse",5) 
	will return 'house'. */
    ETokFnRIGHT,
	/** STRING(x,n) returns a number x as a string to n decimal places. So, =STRING(3.1416,3) 
	returns the string '3.142'. */
	ETokFnSTRING,
	/** T(x) returns the text contained in a cell or in the top left cell of a range. 
	If the cell does not contain text, blank text (an "empty string") is returned. */
	ETokFnT,
	/** TRIM(string) returns the string with leading and trailing spaces removed, and 
	reduces multiple spaces to a single space. */
	ETokFnTRIM,
	/** UPPER(string) returns the string converted to upper case. */
	ETokFnUPPER,
	/** VALUE(string) converts a string to a number. E.g. =VALUE("45.9") returns the 
	number 45.9. */
	ETokFnVALUE,

// Ddate and time functions
	/** DATE(year,month,day) returns the day number for the specified year, month and 
	day. */
    ETokFnDATE,		
	/** DATEVALUE(datestring) returns the appropriate number, given the date string. 
	E.g. =DATEVALUE("31 Jul 97") returns a value of 35642. */
	ETokFnDATEVALUE,
	/** DAY(x) returns the day of the month (1 to 31) according to the day number x. 
	E.g. =DAY(15476) returns 15, since day 15476 is the 15th of the month. */
    ETokFnDAY,
	/** HOUR(x) returns the hour number between 0 and 23, according to the time value 
	x. E.g. =HOUR(0.6) returns 14. */
	ETokFnHOUR,
	/** MINUTE(x) returns the minute number between 0 and 59, according to the time 
	value x. E.g. =MINUTE(0.612) returns 41. */
	ETokFnMINUTE,
	/** MONTH(x) returns the month number between 1 and 12, according to the day value 
	x. E.g. =MONTH(15476) returns 5, since day 15476 falls in May. */
	ETokFnMONTH,
	/** NOW returns the value of the present time, combining both date and time numbers. 
	E.g. 35642.5 is noon on 31/07/1997. */
	ETokFnNOW,
	/** SECOND(x) returns the second number between 0 and 59, according to the time 
	number x. E.g. =SECOND(0.612) returns 16. */
	ETokFnSECOND,
	/** TIME(hour,minute,second) returns the time number for the specified hour, minute 
	and second. */
    ETokFnTIME,		
	/** TIMEVALUE(timestring) returns the appropriate number, given the timestring. 
	E.g. =TIMEVALUE("15:52:12") returns 0.66125. */
	ETokFnTIMEVAL,
	/** TODAY returns the day number of the current day. */
	ETokFnTODAY,
	/** YEAR(x) returns the year number (from 0 to 255) from the day number x. E.g. 
	=YEAR(35642) returns 97, since day 35642 falls in 1997. */
	ETokFnYEAR,

// Mathematical functions
	/** ABS(value) returns the absolute value of a number, i.e. regardless of whether 
	it is positive or negative. */
	ETokFnABS,
	/** ACOS(value) returns the arcCosine (inverse cosine) of a value. */
	ETokFnACOS,
	/** ASIN(value) returns the arcSine (inverse sine) of a value. */
	ETokFnASIN,		
	/** ATAN(value) returns the arcTangent (inverse tangent) of a value. */
	ETokFnATAN,
	/** ATAN2(x_value,y_value) returns the angle, in radians, whose tangent is y/x. */
	ETokFnATAN2,
	/** COS(value) returns the cosine of a value. */
	ETokFnCOS,
	/** DEGREES(value) converts a value from radians into degrees. */
	ETokFnDEGREES,
	/** EXP(value) returns the value of e raised to the power of a value. */
	ETokFnEXP,
	/** FACT(value) returns the factorial of a value. */
	ETokFnFACT,
	/** INT(value) rounds a value down to the nearest whole number. */
	ETokFnINT,
	/** LN(value) returns the natural logarithm of a value. */
	ETokFnLN,
	/** LOG10(value) returns the base-10 logarithm of a value. */
	ETokFnLOG10,
	/** MOD(value1,value2) returns the remainder (called the modulus) when value1 is 
	divided by value2. */
	ETokFnMOD,
	/** PI inserts 'pi' in a cell, sum or formula. */
	ETokFnPI,
	/** RADIANS(value) converts a value from degrees into radians. */
	ETokFnRADIANS,
	/** RAND returns a random number between zero and one. Use +RAND to insert a random 
	number in a cell which does not change with each recalculation. */
	ETokFnRAND,
	/** ROUND(number,number_of_digits) to round a number to a given number of digits. 
	Make the second number a negative to round to a digit to the left of the decimal 
	point. E.g. -2 to round to the nearest 100. */
	ETokFnROUND,
	/** SIGN(value) indicates the sign of a value. It returns 1 if the sign is positive, 
	-1 if the sign is negative, and 0 if the value is 0. */
	ETokFnSIGN,
	/** SIN(value) returns the sine of a number. */
	ETokFnSIN,
	/** SQRT(value) returns the square root of a number. */
	ETokFnSQRT,
	/** SUMPRODUCT(range1,range2) returns the sum of the products of corresponding 
	items in two ranges. I.e., the first item in range1 is multiplied by the first 
	item in range2, the second by the second, and so on. The result is the sum 
	total of all these products. */
	ETokFnSUMPRODUCT,
	/** TAN(value) returns the tangent of a value. */
	ETokFnTAN,
	/** TRUNC(value) returns a number or the number stored in a cell with any fraction 
	removed. So, =TRUNC(5.845) returns 5. TRUNC and INT only differ where the 
	value is negative, as INT always rounds down to the lower number, where TRUNC 
	just removes the section after the decimal point. */
	ETokFnTRUNC,

// Financial functions
	/** CTERM(interest,future_value,principal) returns the number of periods it will 
	take for an investment of principal to reach future_value at a given interest 
	rate. CTERM uses the formula: term = ln(future_value/principal)/ln(1+interest) */
	ETokFnCTERM,	
	/** DDB(cost,salvage,life,period) returns the depreciation per period, assuming 
	that the asset loses much more of its value at the beginning of its life than 
	at the end. DDB uses the formula: depreciation per period=(book value*2)/life 
	where:book value at the start of each period= (total cost-total depreciation 
	over all previous periods). */
	ETokFnDDB,
	/** FV(interest,term,payment) returns the matured value of an investment given 
	the interest rate, the term, and the payment per period. FV uses the formula: 
	fv=payment*(((1+interest)term)-1)/interest where term is the number of periods. */
	ETokFnFV,
	/** IRR(guess,cash_flows) calculates the Internal Rate of Return of an investment, 
	to give the approximate interest rate earned. 'Guess' is a number you suppose 
	to be close to the IRR. */
	ETokFnIRR,
	/** NPV(interest,cash_flows) calculates the Net Present Value of an investment: 
	what it would be worth if you had it as a lump sum now rather than a future 
	receipt. Interest is the interest rate per receipt period. NPV assumes the 
	receipt occurs at the beginning the period. If the receipt occurs at the end 
	of the period, use the formula: npv = first_receipt + NPV(interest,remaining_receipts) */
	ETokFnNPV,
	/** PMT(interest,term,principal) returns the amount to be repaid per period on 
	a loan, given the interest rate, the number of repayment periods and the principal 
	amount loaned. The function assumes repayment is made at the end of each period. 
	If repayment is at the beginning of each period, use the formula =PMT(interest,term,principal)/(1+interest). 
	PMT uses the formula: payment=principal*interest/(1-(1+interest)-term). */
	ETokFnPMT,
	/** PV(interest,term,payment) returns the present value of an investment given 
	the interest rate, the term, and the payment per period. PV uses the formula: 
	present_value = payment * (1-(1+interest)-n) / interest. */
	ETokFnPV,
	/** RATE(future_value,principal,periods) returns the interest rate for an investment, 
	principal, to reach future_value over the given number of periods. RATE uses 
	the formula: interest rate = ((future_value/principal)1/periods) - 1. */
	ETokFnRATE,
	/** SLN(cost,salvage,life) returns the depreciation per period for the asset's 
	life. SLN assumes that the asset loses the same amount of its value during 
	each period, and uses the formula: depreciation per period=(cost-salvage)/life. */
	ETokFnSLN,
	/** SYD(cost,salvage,life,period) returns the depreciation per period, assuming 
	that the asset loses more of its value at the beginning of its life than at 
	the end. SYD uses the formula: depreciation per period= (cost-salvage)*(life-period+1)/(life*(life+1)/2). */
    ETokFnSYD,			
	/** TERM(payments,interest,future_value) returns the number of payments needed 
	to accumulate future_value from a series of payments earning a periodic interest 
	rate. TERM uses the formula: number of payments= ln(1+future_value*interest/payment)/ln(1+interest) 
	where ln is the natural logarithm. */
	ETokFnTERM,

// Statistical functions
	/** COMBIN(n1,n2) returns the number of possible unique groups containing a number, 
	n2, of items that could be made from a given total number of items, n1. */
	ETokFnCOMBIN,
	/** PERMUT(n1,n2) returns the number of possible permutations for a number, n2, 
	of items selected from a given total number of items, n1. Unlike COMBIN, PERMUT 
	treats the order of the possible groups as being important, so xy is different 
	from yx. */
	ETokFnPERMUT,

// Added for App engines 5.2
	/** POWER(x,y) returns the value of x raised to the power y. */
	ETokFnPOWER,

	/** Indicates last non-statistical function token. */
	ETokLastFn=ETokFnPOWER,

// Statistical list functions
	/** Indicates first statistical function token. */
	ETokFirstFnBeginStat,
	/** AVERAGE(list) returns the average of the numbers in the list. E.g. =AVERAGE(3,4,5,6) 
	returns 4.5. */
	ETokFnBeginAVERAGE=ETokFirstFnBeginStat,
	/** CHOOSE(x,list) returns the xth item in the list, taking the first item to be 
	number 1. The list may contain both text strings and values. */
	ETokFnBeginCHOOSE,
	/** COUNT(list) returns the number of cells in the list which contain numerical 
	information. Blank cells are not counted. */
	ETokFnBeginCOUNT,
	/** COUNTA(list) returns the number of cells in the list which contain any information. 
	This excludes blank cells, but includes those which contain blank text (i.e. 
	where the cell contains a ' (apostrophe) mark). */
	ETokFnBeginCOUNTA,
	/** COUNTBLANK(list) returns the number of blank cells in the list. This counts 
	empty cells, or formulae which do not return any text. */
	ETokFnBeginCOUNTBLANK,
	/** MAX(list) returns the maximum value in a list. MAX takes account of + and - 
	signs, so 2 is larger than -10. */
	ETokFnBeginMAX,
	/** MIN(list) returns the minimum value in a list. MIN takes account of + and - 
	signs, so 2 is larger than -10. */
	ETokFnBeginMIN,	
	/** PRODUCT(list) calculates the product of a list of values. */
	ETokFnBeginPRODUCT,
	/** STDEVP(list) returns the standard deviation of the values in the list, treating 
	them as a population. */
	ETokFnBeginSTDEVP,
	/** STDEV(list) returns the standard deviation of the values in the list, treating 
	them as a sample. */
	ETokFnBeginSTDEV,
	/** SUM(list) returns the sum of a list of values. */
	ETokFnBeginSUM,
	/** SUMSQ(list) calculates the sum of the squares of a list of values. E.g. =SUMSQ(3,5) 
	returns 34. */
	ETokFnBeginSUMSQ,
	/** VARP(list) returns the population variance of a list of values, treating them 
	as a population. */
	ETokFnBeginVARP,
	/** VAR(list) returns the variance of values in a list, treating them as a sample. */
	ETokFnBeginVAR,

	/** Indicates the last statistical function token. */
	ETokLastFnBeginStat=ETokFnBeginVAR,
	/** Same as ETokLastFnBeginStat. */
	ETokLastArrayFn=ETokLastFnBeginStat,
	};
#endif
