# generic.mk
#
# Copyright (c) 2006 Symbian Software Ltd.  All rights reserved.
#
# Definitions common to all shells


# *_PATH variables to support filename policy conformance in makefile templates
# NOTE: These should all be replaced by calls to a function that lower-cases
# the current setting of the original variable

PLATFORM_PATH=$(PLATFORM)
CFG_PATH=$(CFG)

ifeq ($(PLATFORM_PATH),WINS) 
	PLATFORM_PATH=wins
else
ifeq ($(PLATFORM_PATH),WINSCW) 
	PLATFORM_PATH=winscw
else
ifeq ($(PLATFORM_PATH),ARMV5) 
	PLATFORM_PATH=armv5
endif
endif
endif

ifeq ($(CFG_PATH),UREL) 
	CFG_PATH=urel
else
ifeq ($(CFG_PATH),UDEB) 
	CFG_PATH=udeb
endif
endif

define slash2generic
	$(subst /,$/,$1)
endef
