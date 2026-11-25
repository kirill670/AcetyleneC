// INSTRESULT.H
// Copyright (c) 1997-2002 Symbian Ltd. All rights reserved.
//
// Implementation of the CInstCapResult class
//

#ifndef _INSTRESULT_H__
#define _INSTRESULT_H__

#include <instform.h>
#include <e32base.h>

class CInstCapResult : public CBase
	{
	public:
		IMPORT_C virtual ~CInstCapResult();

		static CInstCapResult* NewLC(TInt aNumber);
		static CInstCapResult* NewLC(const TDesC& aString);
		TBool operator==(const CInstCapResult& aResult);
		TBool operator!=(const CInstCapResult& aResult);
		TBool operator>(const CInstCapResult& aResult);
		TBool operator<(const CInstCapResult& aResult);
		TBool operator>=(const CInstCapResult& aResult);
		TBool operator<=(const CInstCapResult& aResult);
		TBool operator&&(const CInstCapResult& aResult);
		TBool operator||(const CInstCapResult& aResult);
		TBool Exists();
	private:
		void ConstructL(const TDesC& aString);
	public:
		enum TResultType
			{
			EString,
			ENumber
			};
		TResultType iType;
		TInt iNumber;
		HBufC *iString;
	};

#endif
