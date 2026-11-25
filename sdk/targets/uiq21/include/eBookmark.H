// eBookmark.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __EBookmark_H__
#define __EBookmark_H__

#if !defined(__APMREC_H__)
#include <apmrec.h>
#endif

const TInt KMaxQualiferLength=12;

class CEBookmarkRecognizer : public CApaDataRecognizerType
// Recognizes eBookmark from files with eBm extension and BEGIN: and URL: fields
	{
public: // from CApaDataRecognizerType
	CEBookmarkRecognizer();
	TUint PreferredBufSize();
	TDataType SupportedDataTypeL(TInt aIndex) const;
private: 
	// from CApaDataRecognizerType
	void DoRecognizeL(const TDesC& aName, const TDesC8& aBuffer);

private:
	};

#endif // __EBookmark_H__