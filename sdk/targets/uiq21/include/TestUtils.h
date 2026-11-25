// TestUtils.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// This contains CTestUtils 



class CTestUtils
{
public:

	IMPORT_C  static CTestUtils * NewL(CLog * aLogSystem );
	IMPORT_C  void RunUtils( const TDesC& Text  );

private:
	void Construct(CLog * aLogSystem );
	void RunUtilsL( const TDesC& Text  );

	void ChangeDirL (const TDesC& aDirname ); 
	void MakedirL (const TDesC&) ;
	void CopyFileL (const TDesC& anOld,const TDesC& aNew); 
	void DeleteFileL (const TDesC& aFile); 
	void MakeReadWriteL(const TDesC& aFile);

	// pointer to Logging object which handles File and Console logging
	CLog * iLogSystem;


};
