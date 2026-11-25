// COESNDPY.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COESNDPY_H__)
#define __COESNDPY_H__

#include <e32std.h>

class TBaSystemSoundType;
class CCoeSoundPlayerManager;

/** 
 * The <code>CoeSoundPlayer</code> class is a utility class for simple sound 
 * playing. This class must be used in the same thread as an active UI Control 
 * Framework environment (<code>CCoeEnv</code>). The class plays the sound 
 * specified by a <code>TBaSystemSoundType</code> object. The caller can 
 * request the sound to be repeated and the time between repeats. If the exact 
 * sound cannot be found on a particular device, a match by category only is 
 * used (first UID). No sound will play if a match is not found.
 * 
 * @lib [what]
 * @publishedAll
 * @released 
 */
class CoeSoundPlayer

	{
public:
    /** [what] */
	enum 
        { 
        /** [what] */
        ENoRepeat=1, 
        /** [what] */
        ERepeatForever=KMaxTInt
        };
public:
    /** 
    * Plays the specified sound. This method only interrupts another sound that 
    * is currently playing if the new sound has a higher priority than the 
    * current one. To interrupt any currently playing sound and play a new one,
    * use <code>PlaySoundNow()</code> instead of <code>PlaySound()</code>.
    * 
    * @param aType The sound to play
    * @remarks
    * @see
    */
	inline static void PlaySound(const TBaSystemSoundType& aType);
	
    /** 
    * Plays the specified sound. This method only interrupts another sound that 
    * is currently playing if the new sound has a higher priority than the 
    * current one. To interrupt any currently playing sound and play a new one,
    * use <code>PlaySoundNow()</code> instead of <code>PlaySound()</code>.
    * 
    * @param aType The sound to play
    * @param aPlayCount The number of times the sound is played
    * @param aGap The interval in microseconds between each time the sound is 
    *             played
    * @remarks
    * @see
    */
    inline static void PlaySound(const TBaSystemSoundType& aType,TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap);
	
    /** 
    * Plays the specified sound, interrupting any other sound that is currently 
    * playing. 
    * 
    * @param aType The sound to play
    * @remarks
    * @see
    */
    inline static void PlaySoundNow(const TBaSystemSoundType& aType);
	
    /** 
    * Plays the specified sound the specifed number of times with the specified 
    * interval, interrupting any other sound that is currently playing. 
    * 
    * @param aType The sound to play
    * @param aPlayCount The number of times the sound is played
    * @param aGap The interval in microseconds between each time the sound is 
    *             played
    * @remarks
    * @see
    */
    inline static void PlaySoundNow(const TBaSystemSoundType& aType,TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap);
	
    /** 
    * [what]
    *
    * @param aType [what]
    * @remarks
    * @see
    */
    IMPORT_C static void CancelSound(const TBaSystemSoundType& aType);

private:
	IMPORT_C static void PlaySound(const TBaSystemSoundType& aType,TInt aPlayCount,
											TTimeIntervalMicroSeconds32 aGap,TBool aInterrupt);
	static CCoeSoundPlayerManager* ManagerL();
	};

inline void CoeSoundPlayer::PlaySound(const TBaSystemSoundType& aType)
/** Plays the specified sound. 

This function only interrupts another, currently playing, sound if the new 
sound has a higher priority than the currently playing sound. If you wish 
to interrupt any currently playing sound and play a new one, use PlaySoundNow() 
instead of PlaySound().

@param aType The sound to play.*/
	{CoeSoundPlayer::PlaySound(aType,ENoRepeat,TTimeIntervalMicroSeconds32(0),EFalse);}

inline void CoeSoundPlayer::PlaySound(const TBaSystemSoundType& aType,TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap)
/** Plays the specified sound for the specifed number of times with the specified 
interval. 

This function only interrupts another, currently playing, sound if the new sound 
has a higher priority than the current one. If you wish to interrupt 
any currently playing sound and play a new one, use PlaySoundNow() instead of PlaySound().

@param aType The sound to play. 
@param aPlayCount The number of times the sound is played.
@param aGap The interval in microseconds between each time the sound is played. */
	{CoeSoundPlayer::PlaySound(aType,aPlayCount,aGap,EFalse);}

inline void CoeSoundPlayer::PlaySoundNow(const TBaSystemSoundType& aType)
/** Plays the specified sound, interrupting any other sound that is currently playing.

@param aType The sound to play. */
	{CoeSoundPlayer::PlaySound(aType,ENoRepeat,TTimeIntervalMicroSeconds32(0),ETrue);}

inline void CoeSoundPlayer::PlaySoundNow(const TBaSystemSoundType& aType,TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap)
/** Plays the specified sound the specifed number of times with the 
specified interval, interrupting any other sound that is currently playing.

@param aType The sound to play.
@param aPlayCount The number of times the sound is played.
@param aGap The interval in microseconds between each time the sound is played. */
	{CoeSoundPlayer::PlaySound(aType,aPlayCount,aGap,ETrue);}

#endif
