# GCCE.mk
#
# Copyright (c) 1997-2006 Symbian Software Ltd.  All rights reserved.
#

# This file provides the definition of variables that are used by the component specific makefile
# This is for the BPABI (Base Platform ABI) platform using the GCCE compiler.

#---------------
# Path Settings
#---------------

# Compiler Installation Location
CC_INSTALL_PATH=

#----------------------------------
# Programs used from the ToolChain
#----------------------------------

# C++ Compiler
CC=arm-none-symbianelf-g++

# Linker
LD=arm-none-symbianelf-ld

# Assembler
ASM=arm-none-symbianelf-as

# Archiver
AR=arm-none-symbianelf-ar

# Translator to translate the GCC inline assembler code
TRANASM=

#------------------
# Compiler Options
#------------------

# Flag whether the compiler requires Unix slashes for absolute paths
UNIX_SLASH_FOR_CC_ABS_PATHS=1

#-------------------
# Debug Mode Options
#-------------------

# Optimization Level in DEBUG mode
DEBUG_OPTIMISATION=

# Option to produce debug information
DEBUG_OPTION=-g

# Option to ensure that the debug format is of DWARF3 format
DEBUG_FORMAT=

# Specific compiler options for a UDEB build
SYMBIAN_UDEB_CCFLAGS= $(DEBUG_OPTION) $(DEBUG_FORMAT)

#-------------------------
# Target Processor Options 
#-------------------------

# Option to select the appropriate target processor
TARGET_ARCH_OPTION=-march=armv5t

# Option to generate the approproate ARM instruction set.
ARM_INSTRUCTION_SET=

# Option to generate the approproate thumb instruction set.
THUMB_INSTRUCTION_SET=

# Compiler define for thumb instruction set
COMPILER_THUMB_DEFINES=

# Compiler define for interwork
COMPILER_INTERWORK_DEFINES=

# Option to specify the floating point conformance. 
FPMODE_OPTION=

# Compiler option to select softvfp mode
SOFTVFPMODE_OPTION=-msoft-float

# Compiler option to select hardware floating point unit
VFP2MODE_OPTION=

# Option to force all enumerations to be stored in as integers. 
ENUM_OPTION=

#---------------------------------
# Options controlling C++ Features
#---------------------------------

# Option for handling Virtual functions and Virtual Tables
EXPORT_VTBL_OPTION=

# Disables unused virtual function elimination (VFE) in C++ mode. --vfe is the default
VFE_OPTION= 

# Option to turn on exception handling
EXCEPTIONS=-fexceptions

#-------------------------------------------------------------------------
# Options controlling the ARM Architecture Procedure Call Standard (AAPCS)
#-------------------------------------------------------------------------

# This Option is for ARM Architecture Procedure Call Standard with the 
# qualifier to support calls between the ARM and Thumb instruction sets.
AAPCS_OPTION=-mapcs

#-----------------------------------------------------------
# Options controlling generation of Compiler Warnings/Errors 
#-----------------------------------------------------------

# Option to control the Compiler warnings
CC_WARNINGS_CONTROL_OPTION=-Wall -Wno-ctor-dtor-privacy -Wno-unknown-pragmas

# Option to suppress the Compiler errors
CC_ERRORS_CONTROL_OPTION=

# Option to modify the Compiler warnings and errors for Symbian OS
SYMBIAN_CC_MESSAGE_OPTION=$(CC_WARNINGS_CONTROL_OPTION) $(CC_ERRORS_CONTROL_OPTION)

#-----------------
# Optional Options
#-----------------

# Compiler option to avoid the generation of the intermediate files. (Optional)
TEMP_FILES_OPTION=-pipe

# Library Option
OWN_LIBRARY_OPTION=

# Option to generate the Object File
COMPILE_ONLY_OPTION=-c

# Option to generate the Preprocessed File
PREPROCESSOR_OPTION=-E

# Other additional Options to be passed to the compiler
EXTRA_CC_OPTION=

#---------------------
# Preprocessor Options
#---------------------

# Prefix Header File passed to the preprocessor
PREFIXFILE=$(EPOCROOT)EPOC32\INCLUDE\GCCE\GCCE.h

# For .cpp Source files
CPP_LANG_OPTION=-x c++

# For .c Source files
C_LANG_OPTION=-x c

# For .cia Source files
CIA_LANG_OPTION=-x c++ -S -Wa,-adln

#-------------------
# Assembler Options
#-------------------

# Option to generate the Assembler instructions
ASSEMBLER_LISTING_OPTION=-S

# Output option used to pass the output file name
ASM_OUTPUT_OPTION=-o

#------------------
# Translator Options
#------------------

# Flags to be passed to the translator
TRANASM_FLAGS=-n -s 

# Output option used to pass the output file name
TRANASM_OUTPUT_OPTION=-o=

# Input option used to pass the input file name
TRANASM_INPUT_OPTION=

#---------------------------
# Include Options and Files
#---------------------------

# Option to specify the location of the header files
INCLUDE_OPTION=-I

# Preinclude file for that compiler that contains all the compiler specific definitions
# required by the Symbian OS source code.
PREINCLUDE_OPTION=-include $(EPOCROOT)EPOC32/INCLUDE/GCCE/GCCE.h

# Option to control the search for the header files. For example, if we do not want to do a search in the
# standard include directory of C++, then can restrict it by providing the appropriate option.
HEADER_FILES_CONTROL_OPTION=-nostdinc

# Path to pick the header files from the Compiler installation directory
COMPILER_INCLUDE_PATH=

#---------------------
# Release Mode Options
#---------------------

# Optimization Level in RELEASE mode
REL_OPTIMISATION=-O2 -fno-unit-at-a-time

# Specific compiler options for a UREL build
SYMBIAN_UREL_CCFLAGS=

#---------------------------------
# Symbol Attribute Setting Options
#---------------------------------

# Option to set the visibility of runtime symbols as DEFAULT (instead of HIDDEN)
RUNTIME_SYMBOL_VISIBILITY_OPTION=

# Option to specify the output of the toolchain
OUTPUT_OPTION=-o

# Common compiler options for compiling programs targeted at Symbian OS
CCFLAGS=$(SYMBIAN_CC_MESSAGE_OPTION) $(EXCEPTIONS) $(TARGET_ARCH_OPTION) $(ENUM_OPTION) $(OWN_LIBRARY_OPTION) $(FPMODE_OPTION) $(EXPORT_VTBL_OPTION) $(VFE_OPTION) $(AAPCS_OPTION) $(TEMP_FILES_OPTION) $(HEADER_FILES_CONTROL_OPTION) $(COMPILE_ONLY_OPTION) $(EXTRA_CC_OPTION)

#------------------
# Linker Options
#------------------

# Output option used to pass the output file name
LINKER_OUTPUT_OPTION=-o

# Option to generate debug information
LINKER_DEBUG_OPTION=

#--------------------------------------------------------------
# Options to generate executables conforming to BPABI standards
#--------------------------------------------------------------

# Option to generate an executable conforming to the Base Platform ABI for the ARM Architecture
BPABI_OPTION=

# The `R_ARM_TARGET1' relocation is typically used for entries in the `.init_array' section. It is
# interpreted as either `R_ARM_REL32' or `R_ARM_ABS32', depending on the target. The following option
# override the default export relocations.
TARGET_RELOCATION_OPTION=--target1-abs

#-------------------------------------
# Options to specify the output format
#-------------------------------------

# Option to create a relocatable ELF image. A relocatable image has a dynamic segment that contains 
# relocations that can be used to relocate the image post link-time.
RELOCATABLE_IMAGE_OPTION=

# Option to create an ELF shared object.
SHARED_OBJECT_OPTION=-shared

#-------------------------------------------
# Options to set the Start of RO/RW sections
#-------------------------------------------

# Option to set the start of the code section (RO Region)
CODE_SEGMENT_START=-Ttext

# Option to split object into RO and RW sections
SPLIT_OPTION=

# Option to set the start of the Data section (RW region)
RW_BASE_OPTION=-Tdata

# Option to be passed to the linker to set the start of the data section (RW region)
DATA_SEGMENT_START=$(SPLIT_OPTION) $(RW_BASE_OPTION)

#---------------------------------------------------------
# Options controlling generation of Linker Warnings/Errors 
#---------------------------------------------------------

# Option to control the Linker warnings
LD_WARNINGS_CONTROL_OPTION=

# Option to suppress the Linker errors
LD_ERRORS_CONTROL_OPTION=

# Option to modify the Linker warnings and errors for Symbian OS
SYMBIAN_LD_MESSAGE_OPTION=$(LD_WARNINGS_CONTROL_OPTION) $(LD_ERRORS_CONTROL_OPTION)

# Option to specify whether unresolved symbol references from regular object files can be allowed or not.
UNRESOLVED_SYMBOL_REF_OPTION=--no-undefined

# Option to specify the undefined reference
UNDEFINED_SYMBOL_REF_OPTION=-u

# Other additional Options to be passed to the Linker
EXTRA_LD_OPTION=

#-------------------
#Entry Point Options
#-------------------

# Option to pass the explicit symbol for beginning execution of the program
LINKER_ENTRY_OPTION=--entry

# Symbol used to denote the Start of the gouped archives.
START_GROUP_SYMBOL=

# Symbol used to denote the End of the gouped archives.
END_GROUP_SYMBOL=

#-------------------------	
# Library Specific Options
#-------------------------

# Option to control the search in the standard libraries
STDLIB_OPTION=-nostdlib

# Additional static libraries that should be supplied to the linker to be linked with
STATIC_LIBS_LIST=-lsupc++ -lgcc

# Option to pass the path from where the runtime libraries should be picked up
STATIC_LIBS_PATH=-L

# Additional runtime libraries that should be supplied to the linker to be linked with
# Provide the libraries separated by space, scppnwdl.dso should come before drtrvct2_2.dso
RUNTIME_LIBS_LIST=dfpaeabi.dso dfprvct2_2.dso drtaeabi.dso scppnwdl.dso drtrvct2_2.dso

# Option to pass the path from where the runtime libraries should be picked up
RUNTIME_LIBS_PATH=

# Option to turn on implicit symbol versioning
SYMVER_OPTION=--default-symver

# Option to specify the shared object name that is stored in the executable
SO_NAME_OPTION=-soname

# Option to generate the map file that provides information about the linking
LINKER_SYMBOLS_OPTION=-Map

# Option to specify the Symbols file
LINKER_SYMBOLS_FILE_OPTION=

# Option to produce the Map file that provides information about linking
LINKER_SYMBOLS_MAP_OPTION=$(LINKER_SYMBOLS_OPTION) $(LINKER_SYMBOLS_FILE_OPTION)

# Option to specify the linker script file
LINKER_SCRIPT_FILE_OPTION=-T

# option to take object file names from other file
COMMANDFILE_OPTION=

# Linker option common to all link commands for UREL build
SYMBIAN_UREL_LINK_FLAGS=$(SYMBIAN_LD_MESSAGE_OPTION) $(BPABI_OPTION) $(RELOCATABLE_IMAGE_OPTION) $(TARGET_RELOCATION_OPTION) $(UNRESOLVED_SYMBOL_REF_OPTION) $(STDLIB_OPTION) $(EXTRA_LD_OPTION)

# Linker option common to all link commands for UDEB build
SYMBIAN_UDEB_LINK_FLAGS=$(SYMBIAN_LD_MESSAGE_OPTION) $(BPABI_OPTION) $(RELOCATABLE_IMAGE_OPTION) $(TARGET_RELOCATION_OPTION) $(UNRESOLVED_SYMBOL_REF_OPTION) $(STDLIB_OPTION) $(EXTRA_LD_OPTION)

#-----------------
# Archiver Options
#-----------------

# ARCHIVER variable should be set since there is a dependency for this variable in e32test.
ARCHIVER= $(AR)

ARCHIVER_CREATE_OPTION=cr

#--------------------------------------
# Compiler and Platform specific macros
#--------------------------------------

# Macro definitions required to identify the compiler. Allows for conditional compilation based on compiler
PLATFORM_DEFINES=-D__MARM_ARMV5__

COMPILER_DEFINES=-D__GCCE__


#-----------------------------------------------------------------------------------------------------
#This section defines the interface with Symbian tools 
#This SHOULD NOT be changed as any changes in this section will not be picked up by the tools back end
#-----------------------------------------------------------------------------------------------------

# Programs used from the ToolChain
export  CC
export  LD
export  ASM
export  AR
export  TRANASM

# Preprocessor Options
export  PREFIXFILE
export  CPP_LANG_OPTION
export  C_LANG_OPTION
export  CIA_LANG_OPTION

# Compiler Options
export	PREPROCESSOR_OPTION
export  ASSEMBLER_LISTING_OPTION
export  ASM_OUTPUT_OPTION
export  INCLUDE_OPTION
export  PREINCLUDE_OPTION
export  HEADER_FILES_CONTROL_OPTION
export  COMPILER_INCLUDE_PATH
export  SYMBIAN_UREL_CCFLAGS
export  SYMBIAN_UDEB_CCFLAGS
export  REL_OPTIMISATION
export  DEBUG_OPTIMISATION
export  ARM_INSTRUCTION_SET
export  THUMB_INSTRUCTION_SET
export  COMPILER_THUMB_DEFINES
export  COMPILER_INTERWORK_DEFINES
export  SOFTVFPMODE_OPTION
export  VFP2MODE_OPTION
export  RUNTIME_SYMBOL_VISIBILITY_OPTION
export  OUTPUT_OPTION
export  CCFLAGS
export  UNIX_SLASH_FOR_CC_ABS_PATHS

# Linker Options
export  LINKER_OUTPUT_OPTION
export  LINKER_DEBUG_OPTION
export  CODE_SEGMENT_START
export  DATA_SEGMENT_START
export  UNDEFINED_SYMBOL_REF_OPTION
export  LINKER_ENTRY_OPTION
export  START_GROUP_SYMBOL
export  END_GROUP_SYMBOL
export  SHARED_OBJECT_OPTION
export  STDLIB_OPTION
export  STATIC_LIBS_LIST
export  STATIC_LIBS_PATH
export  RUNTIME_LIBS_LIST
export  RUNTIME_LIBS_PATH
export  SYMVER_OPTION
export  SO_NAME_OPTION
export  LINKER_SYMBOLS_MAP_OPTION
export  COMMANDFILE_OPTION
export  SYMBIAN_UREL_LINK_FLAGS
export  SYMBIAN_UDEB_LINK_FLAGS

# Archiver Options
export  ARCHIVER
export  ARCHIVER_CREATE_OPTION

# Compiler Specific Defines
export  COMPILER_DEFINES

# Platform Specific Defines
export  PLATFORM_DEFINES

# Translator Options
export  TRANASM_FLAGS
export  TRANASM_OUTPUT_OPTION
export  TRANASM_INPUT_OPTION
#-----------------------------------------------------------------------------------------------------

