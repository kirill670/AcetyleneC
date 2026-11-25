#ifndef _JADFILE_H__
#define _JADFILE_H__

#include <jarmetafile.h>
#include <jarattributenametable.h>
#include <f32file.h>
#include <s32file.h>
#include <MidpTypes.h>
#include <MJarManifestAttributes.h>

class CJarCommonAttributes;

class CJadFile : public CJarMetaFile, public MJarManifestAttributes
	{
	public:
		// Construction & initialisation
		IMPORT_C static CJadFile* NewL(RFs& aFs, const TDesC& aName);
		virtual ~CJadFile();
		/**
		 * This function returns the name of the file.
		 */
		IMPORT_C const TDesC& FileName() const;

	public: // From MJarManifestAttributes
		virtual const TDesC& MIDletName() const;
		virtual const TDesC& MIDletVendor() const;
		virtual const TDesC& MicroEditionProfile() const;
		virtual const TDesC& MicroEditionConfiguration() const;
		virtual const TDesC& MIDletDescription() const;
		virtual const TDesC& MIDletIcon() const;
		virtual const TDesC& MIDletInfoURL() const;
		virtual const TDesC& MIDletPermissions() const;
		virtual const TDesC& MIDletPermissionsOpt() const;
		virtual TInt MIDletDataSize() const;
		virtual TMIDletVersion MIDletVersion() const;
		virtual TInt NumberOfMIDlets() const;
		virtual TMIDletInfo MIDlet(TInt n) const;
		virtual const TDesC& MIDletInstallNotify() const;
		virtual const TDesC& MIDletDeleteNotify() const;
		virtual const TDesC& MIDletDeleteConfirm() const;
		static IMPORT_C void GetMIDletInstallNotifyL(RFs& aFs, const TDesC& aFileName, HBufC*& aInstallNotifyURL);

	public: // other attributes
		IMPORT_C const TDesC& MIDletJarURL() const;
		IMPORT_C TInt MIDletJarSize() const;

		/**
		 * Returns JAR file signature as provided in JAD file.
		 * @return Base64-encoded signature, or NULL if the JAD file 
		 *     does not contain a signature.
		 */
		IMPORT_C const TDesC& MIDletSignature() const;

		/**
		 * Returns the specified certificate as base64 encoding.
		 * @param aChain Chain number (1-based) of the certificate.
		 * @param aCertNo Certificate number in the chain (1-based).
		 * @return Pointer to base64-encoded certificate, or NULL if 
		 *     there is no such certificate in the JAD file.
		 */
		IMPORT_C const TDesC& MIDletCertificate(TUint aChain, TUint aCertNo) const;

	private:
		CJadFile(RFs& aFs);
		void ConstructL(const TDesC& aName);

	private:
		/**
		 * The name of the file.
		 */
		HBufC* iJadFileName;
		CJarCommonAttributes* iCommonAttributes;
		CJarAttributeNameTable*	iAttributeNameTable;
		RFs& iFs;
	};

#endif