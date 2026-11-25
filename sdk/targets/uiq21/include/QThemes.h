// QThmUtils.h
//
// Copyright (c) 2000-2003 Symbian Ltd.  All rights reserved.
// Created for UIQ 2.1
#ifndef __QTHMUTILS_H__
#define __QTHMUTILS_H__

#include <e32std.h>

class CEikonEnv;
class TBaSystemSoundInfo;
class RFs;

class QThemes
	{
public:
	/**
	 * Launches the Themes dialog
	 */
	IMPORT_C static void RunThemeManagerDlgLD();

	/**
	 * Launches the Appearance dialog
	 *
	 * @param aLinkToThemes Decides if you can open the Themes dialog from this dialog
	 */
	IMPORT_C static void RunAppearanceDlgLD(TBool aLinkToThemes);
	
	/**
	 * Launches the Sound and Alerts dialog
	 */
	IMPORT_C static void RunSystemSoundsDlgLD();	

	/**
	 * Asynchronous method to sets the launcher wallpaper
	 *
	 * @param aFileName Points at an image
	 * @param aEikEnv CEikonEnv reference
	 * @param aCallBack A static callback method to be called on completion
	 */
	IMPORT_C static void SetLauncherWallpaperL(const TFileName& aFileName, const CEikonEnv& aEikEnv, const TCallBack& aCallBack);

	/**
	 * Synchronous method to sets the launcher wallpaper
	 *
	 * @param aFileName Points at an image
	 * @param aEikEnv CEikonEnv reference
	 */
	IMPORT_C static void SetLauncherWallpaperL(const TFileName& aFileName, const CEikonEnv& aEikEnv);

	/**
	 * Sets the system sound
	 *
	 * @param aSoundInfo The sound to add to the array of system sounds
	 * @param aFs The file server session.
	 */
	IMPORT_C static void SetSystemSoundL(const TBaSystemSoundInfo& aSoundInfo, RFs& aFs);
private:
	QThemes();
	};

#endif // __QTHMUTILS_H__