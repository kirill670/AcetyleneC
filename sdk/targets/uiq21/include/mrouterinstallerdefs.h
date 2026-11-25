
#ifndef __MROUTERINSTALLERDEFS__
#define __MROUTERINSTALLERDEFS__

// These defines need to be constructed during installation at some point (rather than
// using the fixed strings here)

#define INSTALL_KEY           "SOFTWARE\\Intuwave Ltd\\mRouterRunTime"      // Needs to be dynamic (company name)?
#define INSTALL_USAGE_COUNT   "UsageCount"
#define INSTALL_TYPE_KEY      "InstallType"
#define INSTALL_STAND_ALONE   "StandAloneInstalled"
#define INSTALL_TYPE_FRESH    "Fresh"
#define INSTALL_TYPE_UPDATE   "Update"
#define MROUTER_VERSION_NUMBER "2.1.0.359"



#define INSTALLER_CMD         "Installer"


// ==============================================================
// Defines used to copy and remove entries from the Control Panel
// Uninstall thing

// Source
#define CTRLPNL_KEY      "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\mRouterRunTime"  // Dynamic (the appname, at least)?


// Registry keys where we can control what is visible in the control panel
#define CUST_UNINST_DLL  "\\mRouterUninst.dll"             // The uninstaller application
#define MY_UNINSTALLER   "mRouterUninstall.exe"     // This is the file that determines whether we should uninstall
#define MROUTER_DISPNAME "DisplayName"              // This is the visible portion of the uninstall program display
#define MROUTER_UNINST   "UninstallString"          // This is where the uninstall application is obtained
	
// ==============================================================


// Deletion Keys
#define CUSUNINST_CMDARG      " -a -c"                                                      // Used to identify the custom uninstaller key (and run in silent mode)
#define WINDOWS_RUN_ONCE      "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"       // Fixed
#define WINDOWS_RUN           "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"
#define RUN_ONCE_DELETE_KEY   "mRouterRunTimeUninstall"
#define UNINSTALLER_KEY       "Uninstaller"                                                 // Differentiate between uninstalling via the control panel and
#define DELETE_ON_REBOOT      "DeleteOnReboot"                                              //    uninstalling from an xxConnect uninstallation.
#define CMDLINE_TOKENDELIMIT  " "

#define SMALL_BUFF_SIZE       256
#define LARGE_BUFF_SIZE       1024
#endif
