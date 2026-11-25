// EIKAPP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKAPP_H__)
#define __EIKAPP_H__

#include <apparc.h>
#include <apaflrec.h>

class CCoeEnv;

/**
 *
 * The root of all Uikon applications.
 *
 * <code>CEikApplication</code> builds on <code>CApaApplication</code>,
 * providing a basis for applications working within the framework
 * provided by Uikon. It also contains an interface to the resource file
 * and the document.Each Uikon application class is derived from
 * <code>CEikApplication</code>. Application writers must provide at
 * least an implementation of the form of <code>CreateDocumentL()</code>
 * that has no parameters.The applications resource file can be changed
 * from the default by overriding <code>ResourceFileName()</code>.
 *
 * @since 6.0
 * @lib "eikcore.lib"
 */
class CEikApplication : public CApaApplication
	{
public:
	IMPORT_C ~CEikApplication();
	inline TInt ResourceFileOffset() const;
	inline CApaProcess* Process() const;
	inline const TApaAppCaption& AppCaption() const;
	IMPORT_C virtual void GetDefaultDocumentFileName(TFileName& aDocumentName) const;
	IMPORT_C virtual TFileName BitmapStoreName() const;
	// from CApaApplication
	IMPORT_C CApaAppInfoFileReader* OpenAppInfoFileLC() const;
	IMPORT_C CDictionaryStore* OpenIniFileLC(RFs& aFs) const;
	IMPORT_C void Capability(TDes8& aInfo) const;
	IMPORT_C void SetToIniFileNameL(TParse& aParser) const;
protected: // from CApaApplication
	IMPORT_C void PreDocConstructL();
	IMPORT_C CApaDocument* CreateDocumentL(CApaProcess* aProcess);
private:
	// reserved virtual function from CApaApplication
	IMPORT_C virtual void Reserved_1();
protected: // new function
	IMPORT_C CEikApplication();
public: // new function
	IMPORT_C virtual TFileName ResourceFileName() const;
private: // new function
	virtual CApaDocument* CreateDocumentL()=0;
private: // internal use
	void ParseWithAppName(TParse& aParse,const TDesC& aFileName) const;
	void ReadCaptionNameL();
protected:
	CCoeEnv* iCoeEnv;
	TInt iResourceFileOffset;
private:
	CApaProcess* iProcess;
	TApaAppCaption iCaption;
	TApaAppCapabilityBuf* iCapabilityBuf;
	TUint iAppFlags;
	TInt iSpare;
	};

/**
 *
 * Gets the offset value defined for this applications default resource
 * file.
 *
 * As the resource file offset can also be accessed through
 * <code>iResourceFileOffset</code>, this function should not be needed
 * by any apps.
 *
 * @returns   "TInt"
 *            Offset of a resource file.
 */
inline TInt CEikApplication::ResourceFileOffset() const
	{ return(iResourceFileOffset); }

/**
 * Gets the managing process.
 *
 * @returns   "CApaProcess*"
 *            A pointer to the process object managing this
 *            applications documents.
 */
inline CApaProcess* CEikApplication::Process() const
	{ return(iProcess); }

/**
 * Gets the caption for this application.
 * Captions are displayed in the task list.
 *
 * @returns   "TApaAppCaption&"
 *            Application caption.
 */
inline const TApaAppCaption& CEikApplication::AppCaption() const
	{ return(iCaption);	}

#endif
