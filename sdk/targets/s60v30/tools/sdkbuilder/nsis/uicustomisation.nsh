;================================================================
; NsisCustomisation.nsh
; nsis header file to customize the installer
; only lines in the format !define NAME [value] should be edited
; the other lines are explanation or examples.
; note: none of these defines is compulsory.
;================================================================

!define INSTALLER_FILENAME "SymbianSDKInstaller.exe"

!define UNINSTALLER_FILENAME "SymbianSDKUNInstaller.exe"

!define INSTALLER_BUILD_VERSION "1.1.1.1"
;if defined, the installer will have a version tab in properties
!define TRADEMARK "Symbian"
;if defined, will add a trademark key to version tab properties



;Interface Settings
; General Interface Settings
!define MUI_ICON "${SDKTOOLS_PATH}\nsis\symbian.ico"
;The icon for the installer.
;Default: ${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico
!define MUI_UNICON "${SDKTOOLS_PATH}\nsis\symbian.ico"
;The icon for the uninstaller.
;Default: ${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico
!define MUI_HEADERIMAGE
;Display an image on the header of the page.
!define MUI_HEADERIMAGE_BITMAP "${SDKTOOLS_PATH}\nsis\symbian_for_all_pages.bmp"
;Bitmap image to display on the header of installers pages (recommended size: 150x57 pixels).
;Default: ${NSISDIR}\Contrib\Graphics\Header\nsis.bmp
!define MUI_HEADERIMAGE_BITMAP_NOSTRETCH
;Do not stretch the installer header bitmap to fit the size of the field. Use this option only if you have an image that does not use the whole space. If you have a full size bitmap that fits exactly, you should not use this option because the size of the field will be different if the user has a custom DPI setting.

;!define MUI_HEADERIMAGE_BITMAP_RTL bmp_file
;Bitmap image to display on the header of installers pages when using a RTL language (recommended size: 150x57 pixels).
;Default: Non-RTL bitmap

;!define MUI_HEADERIMAGE_BITMAP_RTL_NOSTRETCH
;Do not stretch the installer header bitmap when using a RTL language to fit the size of the field. Use this option only if you have an image that does not use the whole space. If you have a full size bitmap that fits exactly, you should not use this option because the size of the field will be different if the user has a custom DPI setting.
!define MUI_HEADERIMAGE_UNBITMAP "${SDKTOOLS_PATH}\nsis\symbian_for_all_pages.bmp"
;Bitmap image to display on the header of uninstaller pages (recommended size: 150x57 pixels).
;Default: Installer header bitmap
!define MUI_HEADERIMAGE_UNBITMAP_NOSTRETCH
;Do not stretch the uninstaller header bitmap to fit the size of the field. Use this option only if you have an image that does not use the whole space. If you have a full size bitmap that fits exactly, you should not use this option because the size of the field will be different if the user has a custom DPI setting.

;!define MUI_HEADERIMAGE_UNBITMAP_RTL bmp_file
;Bitmap image to display on the header of uninstallers pages when using a RTL language (recommended size: 150x57 pixels).
;Default: Installer RTL header bitmap

;!define MUI_HEADERIMAGE_UNBITMAP_RTL_NOSTRETCH
;Do not stretch the uninstaller header bitmap when using a RTL language to fit the size of the field. Use this option only if you have an image that does not use the whole space. If you have a full size bitmap that fits exactly, you should not use this option because the size of the field will be different if the user has a custom DPI setting.
!define MUI_HEADERIMAGE_RIGHT
;Display the header image on the right side instead of the left side (when using a RTL language it will be displayed on the left side instead of the right side).

;!define MUI_BGCOLOR (color: RRGGBBR hexadecimal)
;Background color for the header, the Welcome page and the Finish page.
;Default: FFFFFF

; Interface Resource Settings
;!define MUI_UI ui_file
;The interface file with the dialog resources. Change this if you have made your own customized UI.
;Default: ${NSISDIR}\Contrib\UIs\modern.exe

;!define MUI_UI_HEADERIMAGE ui_file
;The interface files with the dialog resource IDD_INST that contains a bitmap control and space for the header bitmap.
;Default: ${NSISDIR}\Contrib\UIs\modern_headerbmp.exe

;!define MUI_UI_HEADERIMAGE_RIGHT ui_file
;The interface files with the dialog resource IDD_INST that contains a bitmap control and space for the header bitmap on the right side.
;Default: ${NSISDIR}\Contrib\UIs\modern_headerbmpr.exe

;!define MUI_UI_COMPONENTSPAGE_SMALLDESC ui_file
;The interface files with a customized dialog resource IDD_SELCOM with a small description area.
;Default: {NSISDIR}\Contrib\UIs\modern_smalldesc.exe

;!define MUI_UI_COMPONENTSPAGE_NODESC ui_file
;The interface files with a customized dialog resource IDD_SELCOM without a description area.
;Default: {NSISDIR}\Contrib\UIs\modern_nodesc.exe

; Welcome/Finish Page Interface Settings
!define MUI_WELCOMEFINISHPAGE_BITMAP "${SDKTOOLS_PATH}\nsis\symbian.bmp"
;Bitmap for the Welcome page and the Finish page (recommended size: 164x314 pixels).
;Default: ${NSISDIR}\Contrib\Graphics\Wizard\win.bmp
!define MUI_WELCOMEFINISHPAGE_BITMAP_NOSTRETCH
;Do not stretch the bitmap for the Welcome and Finish page to fit the size of the field. Use this option only if you have an image that does not use the whole space. If you have a full size bitmap that fits exactly, you should not use this option because the size of the field will be different if the user has a custom DPI setting.

; Welcome/Finish Page InstallOptions INI Settings
;!define MUI_WELCOMEFINISHPAGE_INI ini_file
;InstallOptions INI file for the Welcome page and the Finish page.
;Default: ${NSISDIR}\Contrib\Modern UI\ioSpecial.ini

; Uninstaller Welcome/Finish Page Settings
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "${SDKTOOLS_PATH}\nsis\symbian.bmp"
;Bitmap for the Welcome page and the Finish page (recommended size: 164x314 pixels).
;Default: ${NSISDIR}\Contrib\Graphics\Wizard\win.bmp
!define MUI_UNWELCOMEFINISHPAGE_BITMAP_NOSTRETCH
;Do not stretch the bitmap for the Welcome and Finish page to fit the size of the field. Use this option only if you have an image that does not use the whole space. If you have a full size bitmap that fits exactly, you should not use this option because the size of the field will be different if the user has a custom DPI setting.

; Uninstaller Welcome/Finish Page Interface INI Settings
;!define MUI_UNWELCOMEFINISHPAGE_INI ini_file
;InstallOptions INI file for the uninstaller Welcome page and the Finish page.
;Default: ${NSISDIR}\Contrib\Modern UI\ioSpecial.ini

; License Page Interface Settings
;!define MUI_LICENSEPAGE_BGCOLOR (/windows | /grey | (color: RRGGBB hexadecimal))
;The background color for the license textbox. Use /windows for the Windows text background color (usually white). Use the /grey for the window background color (usually grey).
;Default: /windows

; Components Page Interface Settings
;!define MUI_COMPONENTSPAGE_CHECKBITMAP bitmap_file
;The bitmap with images for the checks of the component select treeview.
;Default: ${NSISDIR}\Contrib\Graphics\Checks\modern.bmp

;!define MUI_COMPONENTSPAGE_SMALLDESC
;A small description area on the bottom of the page. Use this layout if you have a lot of sections and don't need large descriptions.

;!define MUI_COMPONENTSPAGE_NODESC
;No description area.

; Installation Page Interface Settings
;!define MUI_INSTFILESPAGE_COLORS (/windows | (foreground color: RRGGBB hexadecimal) (background color: RRGGBB hexadecimal))
;The colors of the details screen. Use /windows for the default Windows colors.
;Default: /windows

;!define MUI_INSTFILESPAGE_PROGRESSBAR ("" | colored | smooth)
;The style of the progress bar. Colored makes it use the MUI_INSTALLCOLORS.
;Default: smooth

; Installer Finish Page Interface Settings
;!define MUI_FINISHPAGE_NOAUTOCLOSE
;Do not automatically jump to the finish page, to allow the user to check the install log.

; Uninstaller Finish Page Interface Settings
;!define MUI_UNFINISHPAGE_NOAUTOCLOSE
;Do not automatically jump to the finish page, to allow the user to check the uninstall log.

; Abort Warning Settings
!define MUI_ABORTWARNING
;Show a message box with a warning when the user wants to close the installer.

;!define MUI_ABORTWARNING_TEXT text
;Text to display on the abort warning messagebox.

; Uninstaller Abort Warning Settings
;!define MUI_UNABORTWARNING
;Show a message box with a warning when the user wants to close the uninstaller.

;!define MUI_UNABORTWARNING_TEXT text
;Text to display on the abort warning messagebox.



; General Page Settings
;!define MUI_PAGE_HEADER_TEXT text
;Text to display on the header of the page.

;!define MUI_PAGE_HEADER_SUBTEXT text
;Subtext to display on the header of the page.

; Welcome Page Settings
;!define MUI_WELCOMEPAGE_TITLE title
;Title to display on the top of the page.

!define MUI_WELCOMEPAGE_TITLE_3LINES

;Extra space for the title area.

;!define MUI_WELCOMEPAGE_TEXT text
;Text to display on the page. Use \r\n for a newline.

; License Page Settings
;!define MUI_LICENSEPAGE_TEXT_TOP text
;Text to display on the top of the page.

;!define MUI_LICENSEPAGE_TEXT_BOTTOM text
;Text to display on the bottom of the page.

;!define MUI_LICENSEPAGE_BUTTON button_text
;Text to display on the 'I Agree' button.

;!define MUI_LICENSEPAGE_CHECKBOX
;Display a checkbox the user has to check to agree with the license terms.

;!define MUI_LICENSEPAGE_CHECKBOX_TEXT text
;Text to display next to the checkbox to agree with the license terms.

;!define MUI_LICENSEPAGE_RADIOBUTTONS
;Display two radio buttons to allow the user to choose between accepting the license terms or not.

;!define MUI_LICENSEPAGE_RADIOBUTTONS_TEXT_ACCEPT text
;Text to display next to the checkbox to accept the license terms.

;!define MUI_LICENSEPAGE_RADIOBUTTONS_TEXT_DECLINE text
;Text to display next to the checkbox to decline the license terms.

; Components Page Settings
;!define MUI_COMPONENTSPAGE_TEXT_TOP text
;Text to display on the top of the page.

;!define MUI_COMPONENTSPAGE_TEXT_COMPLIST text
;Text to display on next to the components list.

;!define MUI_COMPONENTSPAGE_TEXT_INSTTYPE text
;Text to display on next to the installation type combo box.

;!define MUI_COMPONENTSPAGE_TEXT_DESCRIPTION_TITLE text
;Text to display on the of the top of the description box.

;!define MUI_COMPONENTSPAGE_TEXT_DESCRIPTION_INFO text
;Text to display inside the description box when no section is selected.

; Directory Page Settings
;!define MUI_DIRECTORYPAGE_TEXT_TOP text
;Text to display on top of the page.

;!define MUI_DIRECTORYPAGE_TEXT_DESTINATION text
;Text to display on the destination folder frame.

;!define MUI_DIRECTORYPAGE_VARIABLE variable
;Variable in which to store the selected folder.
;Default: $INSTDIR

;!define MUI_DIRECTORYPAGE_VERIFYONLEAVE
;Does not disable the Next button when a folder is invalid but allows you to use GetInstDirError in the leave function to handle an invalid folder.

; Start Menu Folder Page Settings
;!define MUI_STARTMENUPAGE_TEXT_TOP text
;Text to display on the top of the page.

;!define MUI_STARTMENUPAGE_TEXT_CHECKBOX text
;Text to display next to the checkbox to disable the Start Menu folder creation.

;!define MUI_STARTMENUPAGE_DEFAULTFOLDER folder
;The default Start Menu Folder.

!define MUI_STARTMENUPAGE_NODISABLE
;Do not display the checkbox to disable the creation of Start Menu shortcuts.

;!define MUI_STARTMENUPAGE_REGISTRY_ROOT root
;!define MUI_STARTMENUPAGE_REGISTRY_KEY key
;!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME value_name
;The registry key to store the Start Menu folder. The page will use it to remember the users preference. You should also use for the uninstaller to remove the Start Menu folders. Don't forget to remove this key during uninstallation.


; Installation Page Settings
;!define MUI_INSTFILESPAGE_FINISHHEADER_TEXT text
;Text to display on the header of the installation page when the installation has been completed (won't be displayed when using a Finish page without MUI_(UN)FINISHPAGE_NOAUTOCLOSE).

;!define MUI_INSTFILESPAGE_FINISHHEADER_SUBTEXT text
;Subext to display on the header of the installation page when the installation has been completed (won't be displayed when using a Finish page without MUI_(UN)FINISHPAGE_NOAUTOCLOSE).

;!define MUI_INSTFILESPAGE_ABORTHEADER_TEXT text
;Text to display on the header of the installation page when the installation has been aborted.

;!define MUI_INSTFILESPAGE_ABORTHEADER_SUBTEXT text
;Subext to display on the header of the installation page when the installation has been aborted.

; Finish Page Settings
;!define MUI_FINISHPAGE_TITLE title
;Title to display on the top of the page.

!define MUI_FINISHPAGE_TITLE_3LINES
;Extra space for the title area.

;!define MUI_FINISHPAGE_TEXT text
;Text to display on the page. Use \r\n for a newline.

;!define MUI_FINISHPAGE_TEXT_LARGE
;Extra space for the text area (if using checkboxes).

;!define MUI_FINISHPAGE_BUTTON text
;Text to display on the Finish button.

;!define MUI_FINISHPAGE_TEXT_REBOOT text
;Text to display on the finish page when asking for a system reboot. Use \r\n for a newline.

;!define MUI_FINISHPAGE_TEXT_REBOOTNOW text
;Text to display next to the 'Reboot now' option button.

;!define MUI_FINISHPAGE_TEXT_REBOOTLATER text
;Text to display next to the 'Reboot later' option button.

;!define MUI_FINISHPAGE_RUN exe_file
;Application which the user can select to run using a checkbox. You don't need to put quotes around the filename when it contains spaces.

;!define MUI_FINISHPAGE_RUN_TEXT text
;Texts to display next to the 'Run program' checkbox.

;!define MUI_FINISHPAGE_RUN_PARAMETERS parameters
;Parameters for the application to run. Don't forget to escape double quotes in the value (use $\").

;!define MUI_FINISHPAGE_RUN_NOTCHECKED
;Do not check the 'Run program' checkbox by default

;!define MUI_FINISHPAGE_RUN_FUNCTION function_name
;Call a function instead of executing an application (define MUI_FINISHPAGE_RUN without parameters). You can use the function to exectute multiple applications or you can change the checkbox name and use it for other things.

;!define MUI_FINISHPAGE_SHOWREADME file/url
;File or website which the user can select to view using a checkbox. You don't need to put quotes around the filename when it contains spaces.

;!define MUI_FINISHPAGE_SHOWREADME_TEXT text
;Texts to display next to the 'Show Readme' checkbox.

;!define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED
;Do not check the 'Show Readme' checkbox by default

;!define MUI_FINISHPAGE_SHOWREADME_FUNCTION function_name
;Call a function instead of showing a file (define MUI_FINISHPAGE_SHOWREADME without parameters). You can use the function to show multiple files or you can change the checkbox name and use it for other things.

;!define MUI_FINISHPAGE_LINK link_text
;Text for a link on the which the user can click to view a website or file.

;!define MUI_FINISHPAGE_LINK_LOCATION file/url
;Website or file which the user can select to view using the link. You don't need to put quotes around the filename when it contains spaces.

;!define MUI_FINISHPAGE_LINK_COLOR (color: RRGGBB hexadecimal)
;Text color for the link on the Finish page.
;Default: 000080

;!define MUI_FINISHPAGE_NOREBOOTSUPPORT
;Disables support for the page that allows the user to reboot the system. Define this option to save some space if you are not using the /REBOOTOK flag or SetRebootFlag.

; Uninstall Confirm Page Settings
;!define MUI_UNCONFIRMPAGE_TEXT_TOP text
;Text to display on the top of the page.

;!define MUI_UNCONFIRMPAGE_TEXT_LOCATION text
;Text to display next to the uninstall location text box.


