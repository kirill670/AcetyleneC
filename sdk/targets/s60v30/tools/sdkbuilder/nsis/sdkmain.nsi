; Main SDK Installer script


!include "MUI.nsh"
!include "StrFunc.nsh"
!include "sdk_param.nsh"
!include "Sections.nsh"




!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME} : ${PRODUCT_VERSION}"
!define PRODUCT_DIR_REGKEY "Software\${PRODUCT_NAME}\${PRODUCT_VERSION}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_REGVAL "${PRODUCT_NAME} : ${PRODUCT_VERSION}"
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "${PRODUCT_NAME}"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_DIR_REGKEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"


!ifdef CUSTOM_INSTALLER
!include ${CUSTOM_INSTALLER}
!else
!include "${SDKTOOLS_PATH}\nsis\UICustomisation.nsh"
!endif

!ifndef INSTALLER_FILENAME
!define INSTALLER_FILENAME "sdkinstaller.exe"
!endif
!ifndef UNINSTALLER_FILENAME
!define UNINSTALLER_FILENAME "sdkuninstaller.exe"
!endif


  
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
Var SectionFlags
var sectName
Var OverWrite
Var numberOfSection
Var selAll
Var curInstType
Var prevInstType
Var newInstallation
Var InstalledComponents
var ICONS_GROUP
var iniFile
var day
var month
var year
var dayofweek
var hour
var minute
var second


${StrTok}

InstType "Full"
InstType /COMPONENTSONLYONCUSTOM
OutFile ${INSTALLER_FILENAME}
InstallDir "$PROGRAMFILES\${PRODUCT_NAME}"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
XPStyle on
ShowInstDetails show
ShowUnInstDetails show

;!ifdef USER_FUNCTIONS
;!include ${USER_FUNCTIONS}
;!endif



Function .onInit
System::Call 'kernel32::CreateMutexA(i 0, i 0, t "$(^Name)") i .r1 ?e'

  Pop $R0

  StrCmp $R0 0 +3

    MessageBox MB_OK|MB_ICONEXCLAMATION "The installer is already running." /SD IDOK

    Abort

Call GetParameters
  Pop $2
  # search for quoted /INIFILE
  StrCpy $1 '"'
  Push $2
  Push '"/INIFILE='
  Call StrStr
  Pop $0
  StrCpy $0 $0 "" 1 # skip quote
  StrCmp $0 "" "" next
  # search for non quoted /INIFILE
  StrCpy $1 ' '
  Push $2
  Push '/INIFILE='
  Call StrStr
  Pop $0
next:

  StrCmp $0 "" done
  # copy the value after /INIFILE=
  StrCpy $0 $0 "" 9
  # search for the next parameter
  Push $0
  Push $1
  Call StrStr
  Pop $1
  StrCmp $1 "" done
  StrLen $1 $1
  StrCpy $0 $0 -$1
done:
  StrCpy $iniFile $0

;if there was anything as inifile, set silent
StrCmp $iniFile "" end
SetSilent silent

;if not absolute path, add $exedir at the beggining
Push $iniFile
Push ":"
Call StrStr
Pop $R0
StrCmp $R0 "" 0 +4
StrCpy $iniFile $EXEDIR\$iniFile"
;MessageBox MB_OK "$EXEDIR"
;MessageBox MB_OK "$iniFile"
call silentUninstall
call silentSelection
end:

FunctionEnd

;==========================================================================
; Welcome page
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE "welcomeLeave"
!insertmacro MUI_PAGE_WELCOME

Function welcomeLeave
  strCpy $newInstallation "1"
  strCpy $OverWrite "0"
  intOp $numberOfSection 1 + 0
; check if this version of the sdk is installed
  ReadRegStr $R0 ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName"
  strCmp $R0 "$(^Name)" 0 NotInstalled
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "$R0 Already installed, do you want to uninstall it first?" IDYES 0 IDNO DoNotUninstall
; execute the uninstaller
  ReadRegStr $R1 ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString"
  ifFileExists $R1 0 UninstallerNotFound
  ReadRegStr $R2 ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_DIR_REGKEY}" "InstallationPath"
  HideWindow
  ClearErrors
;    MessageBox MB_OK "Uninstalling $R1 $R2!"
  ExecWait '"$R1" _?=$R2\'
  IfErrors UninstallerFailed
;  IfFileExists "$INSTDIR\uninstall.exe" DoNotUninstall
  RMDir /r "$R2"
  goto NotInstalled
  UninstallerNotFound:
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Uninstaller not found, do you want to continue?" IDNO 0 IDYES DoNotUninstall
  quit
  UninstallerFailed:
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Uninstaller failed, do you want to continue?" IDNO 0 IDYES DoNotUninstall
  quit
  DoNotUninstall:
  strCpy $newInstallation "0"
  strCpy $OverWrite "1"
  NotInstalled:
  BringToFront
  intOp $selAll 1 + 0
  intOp $prevInstType 0 + 0
FunctionEnd


;==========================================================================
; License page
!ifdef LICENSEDATA
!define MUI_PAGE_CUSTOMFUNCTION_PRE "skipPage"
!insertmacro MUI_PAGE_LICENSE ${LICENSEDATA}
!endif

;==========================================================================
; Components page
!insertmacro MUI_PAGE_COMPONENTS

Function .onSelChange
;reset the selection only in case the user change the selection from insttype full to customised
GetCurInstType $curInstType
	
intCmp $curInstType $prevInstType noSelChange 0 0
intCmp $curInstType ${NSIS_MAX_INST_TYPES} 0 setSelAll setSelAll
;	MessageBox MB_OK "Customized: selected!"
intOp $selAll 0 + 0
;	MessageBox MB_OK "call setselection: selAll = $selAll cur = $curInstType prev = $prevInstType!"
intOp $prevInstType $curInstType + 0
call setSelection
goto noSelChange
setSelAll:
intOp $selAll 1 + 0
;	MessageBox MB_OK "call setselection: selAll = $selAll cur = $curInstType prev = $prevInstType!"
intOp $prevInstType $curInstType + 0
call setSelection
noSelChange:
FunctionEnd


;==========================================================================
; Directory page
!define MUI_PAGE_CUSTOMFUNCTION_PRE "skipPage"
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE "dirLeave"
!define MUI_PAGE_CUSTOMFUNCTION_SHOW "dirShow"
!insertmacro MUI_PAGE_DIRECTORY

Function dirShow
; if re-installation, redisplay directory of previous installation
strCmp $newInstallation "0" 0 nodirsetting
ReadRegStr $R0 ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_DIR_REGKEY}" "InstallationPath"
strCmp $R0 "" nodirsetting 0
!insertmacro MUI_INNERDIALOG_TEXT 1019 "$R0"
nodirsetting:
FunctionEnd


Function dirLeave
  IfFileExists $INSTDIR PathGood
  ;MessageBox MB_OK "Invalid installation directory!"
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Installation folder $INSTDIR does not exist; do you want to create it now?" /SD IDYES IDNO 0 IDYES createInstallionFolder
  Abort
  createInstallionFolder:
  clearErrors
  createDirectory $INSTDIR
  ifErrors 0 NewInstallDir
  MessageBox MB_OK "Could not create $INSTDIR!"
  Abort
  PathGood:
  IfFileExists "$INSTDIR" 0 NewInstallDir
  strCmp $OverWrite "0" 0 NewInstallDir
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "$INSTDIR exists; do you want to delete first?" /SD IDYES IDYES DeleteInstallDir
  strCpy $OverWrite "1"
  goto NewInstallDir
  DeleteInstallDir:
  clearErrors
  RMDir /r "$INSTDIR"
  ifErrors 0 NewInstallDir
  MessageBox MB_OK "Could not delete $INSTDIR!" /SD IDOK
  Abort
  strCpy $OverWrite "0"
  NewInstallDir:
FunctionEnd


;==========================================================================
;StartMenu page
!define MUI_PAGE_CUSTOMFUNCTION_PRE "skipPage"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP

;==========================================================================
; main section
Section "" ; Main section (hidden)
  SectionIn 1 2 3
  ;set $INSTDIR to $INSTDIR\${PRODUCT_VERSION}
  ;strCpy $INSTDIR "$INSTDIR\${PRODUCT_VERSION}"
  SetOutPath "$INSTDIR"
  strCmp $OverWrite "1" 0 +2
  SetOverwrite off
  strCmp $newInstallation "1" done
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
;lc  SetOutPath "$INSTDIR"
  !ifdef LICENSEDATA
         File "${LICENSEDATA}"
  !endif
  !ifdef READMEDATA
         File "${READMEDATA}"
  !endif
  SetOutPath "$INSTDIR\${MANIFEST_DESTINATION}"
  File /a "${MANIFEST_FILE}"
  SetOutPath "$INSTDIR"
  !ifndef NO_DEVICES_UPDATE
  File "${SDKTOOLS_PATH}\updateDevices.pl"
  !endif
  File "${SDKTOOLS_PATH}\updateManifest.pl"
  !insertmacro MUI_STARTMENU_WRITE_END
done:
SectionEnd


;==========================================================================
;components groups
SubSection /e "Components" SEC1
!include CreateComponents.nsh
!include DeleteComponents.nsh
SubSectionEnd


;==========================================================================
; Instfiles page
!define MUI_PAGE_CUSTOMFUNCTION_SHOW "instShow"
!insertmacro MUI_PAGE_INSTFILES

Function instShow
; if re-installation, fetch directory of previous installation
strCmp $newInstallation "0" 0 done
ReadRegStr $INSTDIR ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_DIR_REGKEY}" "InstallationPath"
strCmp $INSTDIR "" 0 PathFound
Abort "Could not find the previous Installation directory"
PathFound:
ifFileExists $INSTDIR done 0
Abort "Installtion directory $INSTDIR does not exist"
done:
FunctionEnd

;==========================================================================
; Finish page
!ifdef READMEDATA
!define MUI_FINISHPAGE_SHOWREADME "${READMEDATA}"
!endif
!define MUI_PAGE_CUSTOMFUNCTION_PRE "skipPage"
!insertmacro MUI_PAGE_FINISH


;==========================================================================
; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES


;==========================================================================
; Language files
!insertmacro MUI_LANGUAGE "English"
!ifdef INSTALLER_BUILD_VERSION
  VIProductVersion "${INSTALLER_BUILD_VERSION}"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "${PRODUCT_NAME}"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "${PRODUCT_PUBLISHER}"
!ifdef TRADEMARK
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "${TRADEMARK} is a trademark of ${PRODUCT_PUBLISHER}"
!endif
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "© ${PRODUCT_PUBLISHER}"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "${PRODUCT_NAME} Installer"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" ""
  VIAddVersionKey /LANG=${LANG_ENGLISH} "InternalName" "${INSTALLER_FILENAME}"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "OriginalFilename" "${INSTALLER_FILENAME}"
!endif
; MUI end ------




;==========================================================================
;post installation section
Section -Post
; additional icons
; start menu
  
  strCmp $newInstallation "1" 0 done

  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  CreateDirectory "$SMPROGRAMS\$ICONS_GROUP\${PRODUCT_VERSION}"
  !ifdef $PRODUCT_WEB_SITE
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\${PRODUCT_VERSION}\${PRODUCT_PUBLISHER} website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$DESKTOP\${PRODUCT_NAME}-${PRODUCT_VERSION}.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  !endif
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\${PRODUCT_VERSION}\Uninstall SDK.lnk" "$INSTDIR\${UNINSTALLER_FILENAME}"
  
  !insertmacro MUI_STARTMENU_WRITE_END

; write the uninstaller
  WriteUninstaller "$INSTDIR\${UNINSTALLER_FILENAME}"
; update registry for the sdk
; for use with control pannel add/remove programs
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\${UNINSTALLER_FILENAME}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  
; for use with start menu uninstall
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_DIR_REGKEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_DIR_REGKEY}" "UninstallString" "$INSTDIR\${UNINSTALLER_FILENAME}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_DIR_REGKEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_DIR_REGKEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_DIR_REGKEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_DIR_REGKEY}" "Manifest" "$INSTDIR\${MANIFEST_DESTINATION}\${MANIFEST_FILENAME}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_DIR_REGKEY}" "InstallationPath" "$INSTDIR"
  !ifndef NO_DEVICES_UPDATE
  call addDevice
  !endif
done:

  call updateCompReg
  
  call updateManifest
  
  !ifndef NO_INSTALLER_LOG
  
  Call GetLocalTime
  Pop "$day" ;Variable (for day)
  Pop "$month" ;Variable (for month)
  Pop "$year" ;Variable (for year)
  Pop "$dayofweek" ;Variable (for day of week name)
  Pop "$hour" ;Variable (for hour)
  Pop "$minute" ;Variable (for minute)
  Pop "$second" ;Variable (for second)
  
  Push "$INSTDIR\installerLog_$day-$month-$year--$hour-$minute-$second.txt"
  Call DumpLog
  !endif
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer." /SD IDOK
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" /SD IDYES IDYES +2
  abort
FunctionEnd


;==========================================================================
;uninstall section
Section Uninstall

  !insertmacro MUI_STARTMENU_GETFOLDER "Application" $ICONS_GROUP
  !ifndef NO_DEVICES_UPDATE
  call un.removeDevice
  !endif
  Delete "$DESKTOP\${PRODUCT_NAME}-${PRODUCT_VERSION}.lnk"
  RMDir /r "$SMPROGRAMS\$ICONS_GROUP\${PRODUCT_VERSION}"
  RMDir /r "$INSTDIR"
  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd


;==========================================================================
;dump the installation log to log file
!define LVM_GETITEMCOUNT 0x1004
!define LVM_GETITEMTEXT 0x102D

Function DumpLog
  MessageBox MB_YESNO "Do you want to save the installation log? " /SD IDYES IDYES 0 IDNO End
  Exch $5
  Push $0
  Push $1
  Push $2
  Push $3
  Push $4
  Push $6

  FindWindow $0 "#32770" "" $HWNDPARENT
  GetDlgItem $0 $0 1016
  StrCmp $0 0 error
  FileOpen $5 $5 "w"
  StrCmp $5 0 error
    SendMessage $0 ${LVM_GETITEMCOUNT} 0 0 $6
    System::Alloc ${NSIS_MAX_STRLEN}
    Pop $3
    StrCpy $2 0
    System::Call "*(i, i, i, i, i, i, i, i, i) i \
      (0, 0, 0, 0, 0, r3, ${NSIS_MAX_STRLEN}) .r1"
    loop: StrCmp $2 $6 done
      System::Call "User32::SendMessageA(i, i, i, i) i \
        ($0, ${LVM_GETITEMTEXT}, $2, r1)"
      System::Call "*$3(&t${NSIS_MAX_STRLEN} .r4)"
      FileWrite $5 "$4$\r$\n"
      IntOp $2 $2 + 1
      Goto loop
    done:
      FileClose $5
      System::Free $1
      System::Free $3
      Goto exit
  error:
    MessageBox MB_OK error /SD IDOK
  exit:
    Pop $6
    Pop $4
    Pop $3
    Pop $2
    Pop $1
    Pop $0
    Exch $5
    End:
FunctionEnd

Function updateManifest
  ReadRegStr $R0 ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_DIR_REGKEY}" "Manifest"
  strCmp $R0 "" 0 +2
  MessageBox MB_OK "Manifest file not registered!" /SD IDOK
  ifFileExists $R0 +3 0
  MessageBox MB_OK "Manifest file $R0 does not exists!" /SD IDOK
  goto manifestEnd
  StrCpy $0 0
  loop:
  EnumRegKey $1 ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_DIR_REGKEY}" $0
  StrCmp $1 "" done
  IntOp $0 $0 + 1
  StrCpy $1 "$\"$1$\""
  StrCpy $InstalledComponents "$InstalledComponents $1"
  goto loop
  done:
  ExecWait 'perl "$INSTDIR\updateManifest.pl"  "$R0" "$INSTDIR" $InstalledComponents'
  manifestEnd:
FunctionEnd

Function silentUninstall

  push $R0
  push $R1
  push $R2

  ReadRegStr $R0 ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName"
  strCmp $R0 "$(^Name)" 0 NotInstalled
;  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "$R0 Already installed, do you want to uninstall it first?" /SD IDYES IDYES 0 IDNO DoNotUninstall
; execute the uninstaller
  ReadRegStr $R1 ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString"
  ifFileExists $R1 0 UninstallerNotFound
  ReadRegStr $R2 ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_DIR_REGKEY}" "InstallationPath"
  HideWindow
  ClearErrors
;    MessageBox MB_OK "Uninstalling $R1 $R2!"
;  strCpy $newInstallation "0"
;  strCpy $OverWrite "1"
  ExecWait '"$R1" /S _?=$R2\'
;  IfErrors UninstallerFailed
;  IfFileExists "$INSTDIR\uninstall.exe" DoNotUninstall
  RMDir /r "$R2"
  NotInstalled:
  UninstallerNotFound:

  pop $R2
  pop $R1
  pop $R0

FunctionEnd



Function silentSelection

         push $R0
         push $R2
         push $R3
         push $R4
         push $R5

         ; $R0 String from INI file
         ; $R1 not used as recommended
         ; $R2 token
         ; $R3 token counter
         ; $R4 Section name
         ; $R5 Section counter

         ;unselect everything

         IntOp $R5 $R5 * 0
         IntOp $R5 $R5 + 1
         loop0:
         SectionGetText $R5 $R4
         ;MessageBox MB_OK "Unselecting $R4"
         !insertmacro UnselectSection $R5
         IntOp $R5 $R5 + 1
         SectionGetText $R5 $R4
         StrCmp $R4 "-" 0 loop0

         ;pick up information from file passed through $iniFile

         ;MessageBox MB_OK "$iniFile"

         IntOp $R3 $R3 * 0
         ReadINIStr $R0 $iniFile sections install
         ;MessageBox MB_OK "$R0"

         loop:
         ${StrTok} $R2 $R0 "," $R3 "1"
         StrCmp $R2 "" end
         ;MessageBox MB_OK "$R3 >> $R2"
         IntOp $R5 $R5 * 0
         IntOp $R5 $R5 + 1
         loop2:
         SectionGetText $R5 $R4
         ;MessageBox MB_OK "Section $R5 -> $R4"
         StrCmp $R2 $R4 0 continue2
         ;MessageBox MB_OK "Selecting $R4 ($R5)"
         !insertmacro SelectSection $R5
         Goto end2
         continue2:
         IntOp $R5 $R5 + 1
         SectionGetText $R5 $R4
         StrCmp $R4 "-" end2 loop2
         end2:

         IntOp $R3 $R3 + 1
         Goto loop
         ;StrCmp $R2 "" 0 loop

         pop $R5
         pop $R4
         pop $R3
         pop $R2
         pop $R0



end:

FunctionEnd

; GetParameters
 ; input, none
 ; output, top of stack (replaces, with e.g. whatever)
 ; modifies no other variables.

 Function GetParameters

   Push $R0
   Push $R1
   Push $R2
   Push $R3

   StrCpy $R2 1
   StrLen $R3 $CMDLINE

   ;Check for quote or space
   StrCpy $R0 $CMDLINE $R2
   StrCmp $R0 '"' 0 +3
     StrCpy $R1 '"'
     Goto loop
   StrCpy $R1 " "

   loop:
     IntOp $R2 $R2 + 1
     StrCpy $R0 $CMDLINE 1 $R2
     StrCmp $R0 $R1 get
     StrCmp $R2 $R3 get
     Goto loop

   get:
     IntOp $R2 $R2 + 1
     StrCpy $R0 $CMDLINE 1 $R2
     StrCmp $R0 " " get
     StrCpy $R0 $CMDLINE "" $R2

   Pop $R3
   Pop $R2
   Pop $R1
   Exch $R0

 FunctionEnd

 ; StrStr
 ; input, top of stack = string to search for
 ;        top of stack-1 = string to search in
 ; output, top of stack (replaces with the portion of the string remaining)
 ; modifies no other variables.
 ;
 ; Usage:
 ;   Push "this is a long ass string"
 ;   Push "ass"
 ;   Call StrStr
 ;   Pop $R0
 ;  ($R0 at this point is "ass string")

 Function StrStr
   Exch $R1 ; st=haystack,old$R1, $R1=needle
   Exch    ; st=old$R1,haystack
   Exch $R2 ; st=old$R1,old$R2, $R2=haystack
   Push $R3
   Push $R4
   Push $R5
   StrLen $R3 $R1
   StrCpy $R4 0
   ; $R1=needle
   ; $R2=haystack
   ; $R3=len(needle)
   ; $R4=cnt
   ; $R5=tmp
   loop:
     StrCpy $R5 $R2 $R3 $R4
     StrCmp $R5 $R1 done
     StrCmp $R5 "" done
     IntOp $R4 $R4 + 1
     Goto loop
 done:
   StrCpy $R1 $R2 "" $R4
   Pop $R5
   Pop $R4
   Pop $R3
   Pop $R2
   Exch $R1
 FunctionEnd
 
Function skipPage
  strCmp $newInstallation "1" done
  Abort
  done:
FunctionEnd


Function GetLocalTime

  # Prepare variables
  Push $0
  Push $1
  Push $2
  Push $3
  Push $4
  Push $5
  Push $6

  # Call GetLocalTime API from Kernel32.dll
  System::Call '*(&i2, &i2, &i2, &i2, &i2, &i2, &i2, &i2) i .r0'
  System::Call 'kernel32::GetLocalTime(i) i(r0)'
  System::Call '*$0(&i2, &i2, &i2, &i2, &i2, &i2, &i2, &i2)i \
  (.r4, .r5, .r3, .r6, .r2, .r1, .r0,)'

  # Day of week: convert to name
  StrCmp $3 0 0 +3
    StrCpy $3 Sunday
      Goto WeekNameEnd
  StrCmp $3 1 0 +3
    StrCpy $3 Monday
      Goto WeekNameEnd
  StrCmp $3 2 0 +3
    StrCpy $3 Tuesday
      Goto WeekNameEnd
  StrCmp $3 3 0 +3
    StrCpy $3 Wednesday
      Goto WeekNameEnd
  StrCmp $3 4 0 +3
    StrCpy $3 Thursday
      Goto WeekNameEnd
  StrCmp $3 5 0 +3
    StrCpy $3 Friday
      Goto WeekNameEnd
  StrCmp $3 6 0 +2
    StrCpy $3 Saturday
  WeekNameEnd:

  # Minute: convert to 2 digits format
	IntCmp $1 9 0 0 +2
	  StrCpy $1 '0$1'

  # Second: convert to 2 digits format
	IntCmp $0 9 0 0 +2
	  StrCpy $0 '0$0'

  # Return to user
  Exch $6
  Exch
  Exch $5
  Exch
  Exch 2
  Exch $4
  Exch 2
  Exch 3
  Exch $3
  Exch 3
  Exch 4
  Exch $2
  Exch 4
  Exch 5
  Exch $1
  Exch 5
  Exch 6
  Exch $0
  Exch 6

FunctionEnd
