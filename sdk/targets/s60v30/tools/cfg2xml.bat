@echo off

rem cfg2xml.bat
rem
rem This batch file should be used only when installed on
rem \epoc32\tools directory in order to convert one
rem or more CFG files to XML using the XML Schema files
rem in \epoc32\tools\commdb-schema directory
rem
rem Copyright (C) Symbian Ltd., 2003.  All Rights Reserved
rem

java -jar \epoc32\tools\cfg2xml.jar %1 \epoc32\tools\commdb-schema\ %2 %3
