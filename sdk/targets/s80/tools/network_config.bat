if not exist JAVA_EXE goto try_with_path

JAVA_EXE -jar npacketgui.jar -wins -checkEmu -name "Network configuration"
goto endi

:try_with_path
java -jar npacketgui.jar -wins -checkEmu -name "Network configuration"
:endi

