// AGMFILTS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// ---------------------------- TAgnFilter -------------------------------------
/**
 * Returns whether the filter includes / excludes timed appointments.
 *
 * @returns   "TBool"
 *            True=Included, False=Excluded.
 */
inline TBool TAgnFilter::AreTimedApptsIncluded() const
	{ return (iFilter & EIncludeTimedAppts); }

/**
 * Returns whether the filter includes / excludes untimed appointments,
 * i.e. day notes.
 *
 * @returns   "TBool"
 *            True=Included, False=Excluded.
 */
inline TBool TAgnFilter::AreUnTimedApptsIncluded() const
	{ return (iFilter & EIncludeUnTimedAppts); }

/**
 * Returns whether the filter includes / excludes events.
 *
 * @returns   "TBool"
 *            True=Included, False=Excluded.
 */
inline TBool TAgnFilter::AreEventsIncluded() const
	{ return (iFilter & EIncludeEvents); }

/**
 * Returns whether the filter includes / excludes anniversaries.
 *
 * @returns   "TBool"
 *            True=Included, False=Excluded.
 */
inline TBool TAgnFilter::AreAnnivsIncluded() const
	{ return (iFilter & EIncludeAnnivs); }

/**
 * Returns whether the filter includes / excludes to-do entries.
 *
 * @returns   "TBool"
 *            True=Included, False=Excluded.
 */
inline TBool TAgnFilter::AreTodosIncluded() const
	{ return (iFilter & EIncludeTodos); }

/**
 * Returns whether the filter includes / excludes repeating entries.
 *
 * @returns   "TBool"
 *            True=Included, False=Excluded.
 */
inline TBool TAgnFilter::AreRptsIncluded() const
	{ return (iFilter & EIncludeRpts); }

/**
 * Returns whether the filter includes / excludes non-repeating entries.
 *
 * @returns   "TBool"
 *            True=Included, False=Excluded.
 */	
inline TBool TAgnFilter::AreNonRptsIncluded() const
	{ return (iFilter & EIncludeNonRpts); }

/**
 * Returns whether the filter only includes the next instance of a
 * repeating entry.
 *
 * @returns   "TBool"
 *            True=Only includes the next instance of a repeating
 *            entry, False=Does not only include the next instance
 *            of a repeating entry.
 */
inline TBool TAgnFilter::RptNextInstanceOnly() const
	{ return (iFilter & EIncludeRptsNextInstanceOnly); }

/**
 * Returns whether the filter only includes alarmed entries.
 *
 * @returns   "TBool"
 *            True=Only alarmed entries included, False=Does not
 *            only include alarmed entries.
 */
inline TBool TAgnFilter::AreAlarmedOnlyIncluded() const
	{ return (iFilter & EIncludeAlarmedOnly); }

/**
 * Returns whether the filter includes / excludes crossed-out entries.
 *
 * @returns   "TBool"
 *            True=Included, False=Excluded.
 */
inline TBool TAgnFilter::AreCrossedOutIncluded() const
	{ return (iFilter & EIncludeCrossedOut); }

/**
 * Returns whether the filter only includes crossed-out entries.
 *
 * @since     5.2
 * @returns   "TBool"
 *            True=Only crossed-out entries included, False=Does not
 *            only include crossed-out entries.
 */
inline TBool TAgnFilter::AreCrossedOutOnlyIncluded() const
	{ return (iFilter & EIncludeCrossedOutOnly); }

// ---------------------------- TAgnSymbolFilter -------------------------------
/**
 * Tests whether the filter has an entry symbol.
 *
 * @returns   "TBool"
 *            True if the filter has an entry symbol, otherwise
 *            False.
 */
inline TBool TAgnSymbolFilter::HasEntrySymbol() const
	{ return(iHasEntrySymbol);}

/**
 * Sets the has entry symbol flag.
 *
 * @param     "TBool aHasEntrySymbol"
 *            True to set the flag, False to clear the flag.
 */
inline void TAgnSymbolFilter::SetHasEntrySymbol(TBool aHasEntrySymbol)
	{ iHasEntrySymbol = (TInt16)aHasEntrySymbol; }

/**
 * Gets the entry symbol, as set by <code>SetEntrySymbol()</code>.
 *
 * @returns   "TText16"
 *            The entry symbol.
 */
inline TText16 TAgnSymbolFilter::EntrySymbol() const
	{ return (iEntrySymbol); }

/**
 * Sets the entry symbol and sets the has entry symbol flag to True.
 *
 * @param     "TText aEntrySymbol"
 *            The entry symbol.
 */
inline void TAgnSymbolFilter::SetEntrySymbol(TText aEntrySymbol)
	{ 
	iEntrySymbol = aEntrySymbol;
	SetHasEntrySymbol(ETrue);
	}

