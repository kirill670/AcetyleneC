@echo off

rem pjava Launcher
rem Copyright (c) 1999-2003 Symbian Ltd.  All rights reserved.

if "%_epoc_drive_j%"=="" if exist "%epocroot%epoc32\java" set _epoc_drive_j=%epocroot%epoc32\java
if "%_epoc_drive_t%"=="" if exist "%epocroot%erj" set _epoc_drive_t=%epocroot%erj
if not "%_epoc_drive_j%"=="" echo _epoc_drive_j=%_epoc_drive_j%
if not "%_epoc_drive_t%"=="" echo _epoc_drive_t=%_epoc_drive_t%
perl -S pjava.pl %1 %2 %3 %4 %5 %6 %7 %8 %9
:END