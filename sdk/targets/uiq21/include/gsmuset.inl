inline TSmsDataCodingScheme::TSmsAlphabet TSmsUserDataSettings::Alphabet() const
/**
 *
 * @return The Alphabet for the User Data
 */
	{
	return iAlphabet;
	}

inline void TSmsUserDataSettings::SetAlphabet(TSmsDataCodingScheme::TSmsAlphabet aAlphabet)
/**
 *
 * @param aAlphabet To set the Alphabet for the User Data
 */
	{
	iAlphabet=aAlphabet;
	}

inline TBool TSmsUserDataSettings::TextCompressed() const
/**
 *
 * @return True if the message text is compressed
 */
	{
	return iFlags&ESmsFlagCompressed;
	}

inline void TSmsUserDataSettings::SetTextCompressed(TBool aCompressed)
/**
 *
 * @param aCompressed To set/reset message text compressed/uncompressed
 */
	{
	iFlags=aCompressed? iFlags|ESmsFlagCompressed: iFlags&(~ESmsFlagCompressed);
	}

