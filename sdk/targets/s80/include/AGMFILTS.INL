// AGMFILTS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// ---------------------------- TAgnFilter -------------------------------------
inline TBool TAgnFilter::AreTimedApptsIncluded() const
/** Tests whether the filter includes or excludes timed appointments.

@return True=included, False=excluded. */
	{ return (iFilter & EIncludeTimedAppts); }

inline TBool TAgnFilter::AreUnTimedApptsIncluded() const
/** Tests whether the filter includes or excludes untimed appointments, i.e. day 
notes.

@return True=included, False=excluded. */
	{ return (iFilter & EIncludeUnTimedAppts); }

inline TBool TAgnFilter::AreEventsIncluded() const
/** Tests whether the filter includes or excludes events.

@return True=included, False=excluded. */
	{ return (iFilter & EIncludeEvents); }

inline TBool TAgnFilter::AreAnnivsIncluded() const
/** Tests whether the filter includes or excludes anniversaries.

@return True=included, False=excluded. */
	{ return (iFilter & EIncludeAnnivs); }

inline TBool TAgnFilter::AreTodosIncluded() const
/** Tests whether the filter includes or excludes to-do entries.

@return True=included, False=excluded. */
	{ return (iFilter & EIncludeTodos); }

inline TBool TAgnFilter::AreRptsIncluded() const
/** Tests whether the filter includes or excludes repeating entries.

@return True=included, False=excluded. */
	{ return (iFilter & EIncludeRpts); }

inline TBool TAgnFilter::AreNonRptsIncluded() const
/** Tests whether the filter includes or excludes non-repeating entries.

@return True=included, False=excluded. */
	{ return (iFilter & EIncludeNonRpts); }

inline TBool TAgnFilter::RptNextInstanceOnly() const
/** Tests whether the filter only includes the next instance of a repeating entry.

@return True=only include the next instance of a repeating entry, False=include 
all instances. */
	{ return (iFilter & EIncludeRptsNextInstanceOnly); }

inline TBool TAgnFilter::AreAlarmedOnlyIncluded() const
/** Tests whether the filter only includes alarmed entries.

@return True=Only include alarmed entries, False=include all 
entries. */
	{ return (iFilter & EIncludeAlarmedOnly); }

inline TBool TAgnFilter::AreCrossedOutIncluded() const
/** Tests whether the filter includes or excludes crossed-out entries.

@return True=included, False=excluded. */
	{ return (iFilter & EIncludeCrossedOut); }

inline TBool TAgnFilter::AreCrossedOutOnlyIncluded() const
/** Tests whether the filter only includes crossed-out entries.

@return True=only include crossed-out entries, false=include 
all entries. */
	{ return (iFilter & EIncludeCrossedOutOnly); }

/*
 * Tests whether to match folded character only when searching for the entry's text.
 *
 * @since     7.0
 * @returns   "TBool"
 *            True=Match folded character only
 */
inline TBool TAgnFilter::IsFoldedOnlySearch() const
	{ return (iFilter & EFoldedSearch); }

/*
 * Tests whether to match exact text only when searching for the entry's text.
 *
 * @since     7.0
 * @returns   "TBool"
 *            True=Match exact text only
 */
inline TBool TAgnFilter::IsExactTextOnlySearch() const
	{ return (iFilter & EExactTextSearch); }

// ---------------------------- TAgnSymbolFilter -------------------------------
inline TBool TAgnSymbolFilter::HasEntrySymbol() const
/** Tests whether the filter has an entry symbol.

@return True if the filter has an entry symbol, false if not. */
	{ return(iHasEntrySymbol);}

inline void TAgnSymbolFilter::SetHasEntrySymbol(TBool aHasEntrySymbol)
/** Sets the 'has entry symbol' flag.

@param aHasEntrySymbol True to set the flag, False to clear the flag. */
	{ iHasEntrySymbol = (TInt16)aHasEntrySymbol; }

inline TText16 TAgnSymbolFilter::EntrySymbol() const
/** Gets the entry symbol, as set by SetEntrySymbol().

@return The entry symbol. */
	{ return (iEntrySymbol); }

inline void TAgnSymbolFilter::SetEntrySymbol(TText aEntrySymbol)
/** Sets the entry symbol and sets the 'has entry symbol' flag.

@param aEntrySymbol The entry symbol. */
	{ 
	iEntrySymbol = aEntrySymbol;
	SetHasEntrySymbol(ETrue);
	}

