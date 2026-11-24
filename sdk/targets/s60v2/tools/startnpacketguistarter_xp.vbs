dim WshShell
Set WshShell = WScript.CreateObject("WScript.Shell")
Return = WshShell.Run("StartNpacketGUI_XP.bat", 1, true)
Set WshShell = Nothing 