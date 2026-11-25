// BANAMEDPLUGINS.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__BANAMEDPLUGINS_H__)
#define __BANAMEDPLUGINS_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

#if !defined(__E32BASE_H__)
#include <E32BASE.H>
#endif

#if !defined(__BAMDESCA_H__)
#include <BAMDESCA.H>
#endif

class RFs;

/**
 *
 * A localised list of the names of the plug-ins available on the device
 * for a particular plug-in framework.
 *
 * This class should be used by applications that display lists of
 * plug-ins. It is provided so that the plug-in names displayed to users:
 * are not filenamesare localisable, i.e. for a multi-language ROM
 * device, plug-in names must be translated into the correct language and
 * sorted according to the locale's collation rulescan be filtered
 * depending on the current locale, i.e. the user will not necessarily
 * see the names of all plug-ins for a given framework for every language
 * of a multi-language ROM.Note that the class <code>MDesC16Array</code>
 * is shown in the derivation tree. The class definition for
 * <code>CBaNamedPlugins</code>, however, uses the typedef
 * <code>MDesCArray</code>. In 6.1 builds, the symbol
 * <code>MDesCArray</code> always resolves to <code>MDesC16Array</code>.
 *
 * @since 6.1
 * @lib "bafl.lib"
 */
class CBaNamedPlugins : public CBase, public MDesCArray
	{
public:
	/**
	 *
	 * The prototype for a function that compares two plug-in names,
	 * <code>aName1</code> and <code>aName2</code> for sorting.
	 *
	 * The plug-in names list is sorted using this algorithm after it has
	 * been populated. Implementing this function is optional. If
	 * implemented, it is passed as a parameter to
	 * <code>CParameters::SetCompareNames()</code>. If not implemented, a
	 * default algorithm is used.The function should return a positive value
	 * if <code>aName1</code> is to occur after <code>aName2</code> or
	 * negative if <code>aName1</code> is to occur before
	 * <code>aName2</code>. Zero should be returned if both descriptors are
	 * equivalent.
	 *
	 * @lib "bafl.lib"
	 */
	typedef TInt (*TCompareNames)(const TDesC& aName1, const TDesC& aName2);

	/**
	 *
	 * The prototype for a function that compares two plug-in identifiers,
	 * <code>aIdentifier1</code> and <code>aIdentifier2</code> to find out if
	 * they are the same.
	 *
	 * Implementing this function is optional. If implemented, it is passed
	 * to <code>CBaNamedPlugins::IndexOfIdentifier()</code>, which uses the
	 * function to compare a specified plug-in identifier with each
	 * identifier in turn in the list of named plug-ins. The function should
	 * return true if they are the same, false if not.
	 * <code>TDesC::CompareC()</code> could be used to do the comparison.
	 *
	 * @lib "bafl.lib"
	 */
	typedef TBool (*TEquivalentIdentifiers)(const TDesC& aIdentifier1, const TDesC& aIdentifier2);

	/**
	 *
	 * The position in the list of plug-in names for the text string which
	 * represents the choice of no plug-in.
 
	 *
	 * Passed as an argument to <code>SetTextForNoneL()</code> and
	 * <code>SetTextForNone()</code>.
	 *  */
	enum TArrayPosition
		{
		/** The string is inserted at the start of the list (array position zero).
		 */
		EArrayPositionFirst,

		/** The string is appended to the list.
		 */
		EArrayPositionLast
		};

	/**
	 *
	 * Information about a resource file containing the names of one or more
	 * named plug-ins.
	 *
	 * The information is the full filename of the resource file (the
	 * language-specific version of this file provides the localised names,
	 * for display to users), the format for the contents of the resource
	 * file and a unique identifier for the plug-in, which is either a UID or
	 * an arbitrary textual identifier (this is not for display).An array of
	 * <code>TResourceFile</code> objects is passed to
	 * <code>CParameters::NewL()</code> and <code>NewLC()</code>.
	 *
	 * @lib "bafl.lib"
	 */
	class TResourceFile
		{
	public:
		/**
		 *
		 * The format of the contents of a resource file.
 
		 *
		 * The <code>EFormatArrayOfUidNamePairs</code> format enables the names
		 * of multiple plug-ins to be held in a single resource file. This could
		 * be used in situations where a fixed set of plug-ins are provided in a
		 * single package, e.g. the plug-ins provided in a ROM (helping to reduce
		 * ROM space). In other cases, the <code>EFormatTbuf</code> format should
		 * be used (here a single resource file provides the name of a single
		 * plug-in).
		 *  */
		enum TFormat
			{
			/** The resource file contains a single <code>TBUF</code> (text string)
			resource, to hold the plug-in name.
			 */
			EFormatTbuf, // the resource is a TBUF

			/** The resource file contains an <code>ARRAY</code> resource, whose items
			are <code>UID_NAME_PAIR</code> structs. These contain plug-in UID and
			name pairs.
			 */
			EFormatArrayOfUidNamePairs // the resource is an ARRAY of UID_NAME_PAIR
			};
	public:
		HBufC* iFullFileName;
		HBufC* iIdentifier; // this may be NULL
		TUid iUid; // this may be KNullUid
		TFormat iFormat;
		};

	/**
	 *
	 * Interface class with a single pure virtual function that generates a
	 * fallback name for plug-ins.
	 *
	 * The <code>FallBackNameL()</code> function is called during
	 * construction of the <code>CBaNamedPlugins</code> object for any
	 * plug-ins for which no resource file could be found with the correct
	 * language extension.Use of this interface is optional. To use it, pass
	 * an instance of a class which implements the interface to
	 * <code>CParameters::SetFallBackName()</code>. If this is not done, then
	 * by default the fallback name used for plug-ins is simply the filename
	 * of the resource file without the drive, directory path or extension.
	 *
	 * @lib "bafl.lib"
	 */
	class MFallBackName
		{
	public:
		/**
		 *
		 * Generates and returns a fallback name for plug-ins for which no
		 * resource is available.
		 *
		 * The fallback name can be generated using the filename of the plug-in's
		 * resource file, which is passed as an argument.
		 *
		 * @param     "const TDesC& aFullResourceFileName"
		 *            The full filename of the resource file. This is the
		 *            same as <code>TResourceFile::iFullFileName</code>.
		 * @returns   "HBufC*"
		 *            The fallback name for a plug-in.
		 */
		virtual HBufC* FallBackNameL(const TDesC& aFullResourceFileName) const=0;
	private:
		IMPORT_C virtual void MFallBackName_Reserved_1();
		IMPORT_C virtual void MFallBackName_Reserved_2();
		};

	/**
	 *
	 * The parameters for a localised list of plug-in names.
	 *
	 * An object of this class is passed to
	 * <code>CBaNamedPlugins::NewL()</code> and <code>NewLC()</code>. The
	 * parameters are as follows — minimally, the first two must be
	 * provided:An array of <code>TResourceFile</code> objects. Each object
	 * contains information about a single plug-in, or multiple plug-ins,
	 * including the filename of the corresponding resource file. Versions of
	 * these resource files with the correct filename extensions for the
	 * required languages provide the name of one or more plug-in, translated
	 * appropriately.A connected session with the file server. This is
	 * required to search the file sytem for the localised resource files,
	 * then to open them for reading.An optional object that generates a
	 * fallback name for plug-ins, if no resource file could be found. If no
	 * such function is provided, then the fallback name used for plug-ins is
	 * simply the filename of the resource file without the drive, directory
	 * path or extension.An optional function that compares two plug-in names
	 * for sorting. The list is sorted after it has been fully populated,
	 * using this algorithm. If not specified, sorting is done by using the
	 * system-wide (locale-dependent) collation rules.An optional descriptor
	 * which, if provided, adds an additional item whose meaning is "none"
	 * (i.e. "no plug-in") to the <code>MDesCArray</code>, and the array
	 * position (either the start or the end of the array) at which to insert
	 * it.
	 *
	 * @lib "bafl.lib"
	 */
	class CParameters : public CBase
		{
	public:
		IMPORT_C static CParameters* NewL(RFs& aFileServerSession, const TArray<TResourceFile>& aArrayOfResourceFiles);
		IMPORT_C static CParameters* NewLC(RFs& aFileServerSession, const TArray<TResourceFile>& aArrayOfResourceFiles);
		IMPORT_C virtual ~CParameters();
		IMPORT_C void SetFallBackName(const MFallBackName& aFallBackName); // fall-back name is used if the resource file does not exist - by default the name of the file without drive, directories or extension is used
		IMPORT_C void SetCompareNames(TCompareNames aCompareNames);
		// SetTextForNoneL and SetTextForNone both add an extra item to the array (i.e. to the MDesCArray interface)
		IMPORT_C void SetTextForNoneL(const TDesC& aTextForNone, TArrayPosition aArrayPositionOfTextForNone);
		IMPORT_C void SetTextForNone(HBufC* aTextForNone, TArrayPosition aArrayPositionOfTextForNone); // passes ownership of aTextForNone in to the CParameters object
	private:
		CParameters(RFs& aFileServerSession);
		void ConstructL(const TArray<TResourceFile>& aArrayOfResourceFiles);
	private:
		RFs& iFileServerSession;
		TArray<TResourceFile>* iArrayOfResourceFiles; // a shallow copy
		const MFallBackName* iFallBackName;
		TCompareNames iCompareNames;
		HBufC* iTextForNone;
		TArrayPosition iArrayPositionOfTextForNone; // this is undefined if iTextForNone is NULL
	private:
		friend class CBaNamedPlugins;
		};
public:
	IMPORT_C static CBaNamedPlugins* NewL(const CParameters& aParameters);
	IMPORT_C static CBaNamedPlugins* NewLC(const CParameters& aParameters);
	IMPORT_C virtual ~CBaNamedPlugins();
	IMPORT_C TInt IndexOfUid(TUid aUid) const;
	IMPORT_C TInt IndexOfIdentifier(const TDesC& aIdentifier, TEquivalentIdentifiers aEquivalentIdentifiers) const;
	IMPORT_C TUid UidAtIndex(TInt aIndex) const;
	IMPORT_C const TDesC* IdentifierAtIndex(TInt aIndex) const;
	// from MDesCArray
	IMPORT_C virtual TInt MdcaCount() const;
	IMPORT_C virtual TPtrC MdcaPoint(TInt aIndex) const;
private:
	class TNamedPlugIn
		{
	public:
		HBufC* iName;
		HBufC* iIdentifier; // this may be NULL
		TUid iUid;
		TCompareNames iCompareNames; // unfortunately the only decent way of passing this function pointer to CompareNamedPlugIns is by storing it in each TNamedPlugIn (an alternative would be to use Dll::Tls but that would be a lot more clumsy)
		};
private:
	CBaNamedPlugins(TInt aGranularity);
	void ConstructL(const CParameters& aParameters);
	static TInt CompareNamedPlugIns(const TNamedPlugIn& aNamedPlugIn1, const TNamedPlugIn& aNamedPlugIn2);
	static TInt DefaultAlgorithmToCompareNames(const TDesC& aName1, const TDesC& aName2);
private:
	RArray<TNamedPlugIn> iArrayOfNamedPlugIns;
	};

#endif

