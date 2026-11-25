// Copyright (c) 2000 By Symbian Ltd. All Rights Reserved.

#ifndef _JAR_FILE_H_
#define _JAR_FILE_H_

#include <JarFileDecoder.h>
#include <JarManifest.h>
#include <JarAttributeNameTable.h>

/**
 * This class represents a Jar file. It provides the functions to access
 * the main elements of a Jar file.
 */
class CJarFile : public CActive, public MJarFileInitObserver
	{
public:
	IMPORT_C static CJarFile* NewL();
	IMPORT_C void Open(RFs& aFs, const TDesC& aJarFileName, TRequestStatus& aStatus);
	IMPORT_C void Close();
	IMPORT_C virtual ~CJarFile();
	IMPORT_C HBufC8* ReadFileL(const TDesC& aInternalFilename, TUint32& aBytesRead);
	IMPORT_C void HashL(TDes8& aHash);
	/**
	 * This function returns the size of the archive in bytes. This is 
	 * the logical size of the archive. The size on disk may differ due
	 * to compression or encryption.
	 */
	IMPORT_C TInt SizeL();

protected:
	/**
	 * The constructor.
	 */
	CJarFile();
	/**
	 * The second-phase constructor.
	 */
	void ConstructL();
	

public:
	IMPORT_C const CJarManifest& Manifest() const;

private:	
	void RunL();
	void DoCancel();
	TInt RunError(TInt aError);
	void LoadManifestL();

private:	// from MJarFileInitObserver
	virtual void NotifyInitComplete(TInt aResult);
    virtual TBool NotifyInitStatus(TJarFileInitStatus aStatus);
	
private:
	/**
	 * This is the object that will actually read and decrypt (if it is encrypted)
	 * the contents of the Jar file and return them to this class.
	 */
	CJarFileInterface* iJarFileDecoder;
	CJarAttributeNameTable *iJarNameTable;
	CJarManifest*			iManifest;		// owned
	TRequestStatus* iCallerRequestStatus;
	TBool iReportStatus;
};

#endif /* !_JAR_FILE_H_ */

