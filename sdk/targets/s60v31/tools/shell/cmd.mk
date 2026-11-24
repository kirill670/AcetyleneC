# cmd.mk
# Copyright (c) 2005 Symbian Software Ltd.  All rights reserved.
#

include $(EPOCROOT)epoc32/tools/shell/generic.mk

# Host platform dependant variables
/:=$(shell echo \)
;:=;
CP=copy
RM=del
RMDIR=rmdir
MKDIR=mkdir
ERASE=@erase 2>>nul
