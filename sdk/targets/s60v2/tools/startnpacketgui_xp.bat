echo off
rem This is start script file ONLY for installer program in Windows XP.
rem This script is launched by StartNPacketGUIStarter_XP.vbs during intallation
rem in Windows XP. It is NOT possible to launch .bat files directly from
rem installer when running Windows XP.

rem Use network_config.bat to launch Network Configuration, also in Windows XP  

echo on
JAVA_EXE -jar npacketgui.jar -winscw -name "Network Configuration" -useProxy FALSE - useDHCP TRUE -useAutoDNS TRUE
echo off