@echo off
Echo Switching emulator to normal start
attrib -r \EPOC32\INCLUDE\STARTER.RSG
attrib -r \EPOC32\RELEASE\WINSCW\UDEB\Z\resource\STARTER.RSC
attrib -r \EPOC32\RELEASE\WINSCW\UREL\Z\resource\STARTER.RSC
copy \epoc32\data\z\resource\STARTER.RSC \EPOC32\RELEASE\WINSCW\UDEB\Z\resource\STARTER.RSC
copy \epoc32\data\z\resource\STARTER.RSC \EPOC32\RELEASE\WINSCW\UREL\Z\resource\STARTER.RSC 
copy \epoc32\tools\STARTER.RSG \EPOC32\INCLUDE\STARTER.RSG
