# Copyright (c) 2003 Symbian Ltd. All rights reserved

# summarise an automated build log
#
# documentation available in generic\tools\e32toolp\docs\scanlog.txt
# please update the documentation when modifying this file

package Scanlog;

use strict;
use Carp;

# CheckForErrors
#
# Inputs
# $line - Line of text to check
#
# Outputs
# Return true for presence of error in the line
# Return false for no error found
#
# Description
# This function matches the input against a known set of Error Strings
sub CheckForErrors
{
  my ($line) = @_;

	# BLDMAKE ERROR: Can't find "\INTERNET\GROUP\BLD.INF"
	# ABLD ERROR: Project Bldmake directory "\EPOC32\BUILD\APP-FRAMEWORK\UIKLAF\GROUP\" does not exist

	if ($line =~ /(ABLD|BLDMAKE) ERROR:/)
	{
		return 1;
	}

	# "\WAPENG\GROUP\BLD.INF" FATAL ERROR(S):

	if ($line =~ /FATAL ERROR\(S\):/)
	{
		return 1;
	}


	# NMAKE : fatal error U1077: 'C:\apps\DevStudio\VC\BIN\NMAKE.EXE' : return code '0x2'

	if ($line =~ /fatal error U1077/)
	{
		return 1;
	}

	# NMAKE : warning U4010: 'FINALCOPYFXCM' : build failed; /K specified, continuing ...

	if ($line =~ /warning U4010/)
	{
		return 1;
	}

	# make: *** [SAVESPACECONVTOOL] Error 2

	if ($line =~ /make(\[\d+\])?: \*\*\* /)
	{
		return 1;
	}

	# make: Target `SAVESPACE' not remade because of errors.

	if ($line =~ /make(\[\d+\])?: .* not remade /)
	{
		return 1;
	}

	# "..\UCRT\Ecrt0.cpp", line 24: Error:  #390: function "main" may not be called or have its address taken
	# "EUSER\\epoc\\arm\\Uc_i64.cia", line 16: Error: A1356W: Instruction not supported on targeted CPU

	if ($line =~ /"(.*)", line (\d+): (Error: +(.\d+.*?):.*)$/)
	{
		return 1;
	}

	# Fatal error: Internal fault: 0x5c6e (200322) in _ZN17CContactLocalView20HandleDatabaseEventLE23TContactDbObserverEvent

	if ($line =~ /error: ((Internal fault):.*)$/)
	{
		return 1;
	}
	
	# Exception: STATUS_ACCESS_VIOLATION
	# networkPrim.c
  #    0 [main] make 2020 handle_exceptions: Exception: STATUS_ACCESS_VIOLATION
  #  265 [main] make 2020 open_stackdumpfile: Dumping stack trace to make.exe.stackdump
	if ($line =~ /Exception: STATUS_ACCESS_VIOLATION/)
	{
		return 1;
	}

	# MSGBROWSER.WINSCW:3233: target `\EPOC32\RELEASE\WINSCW\UDEB\Z\System\Data' given more than once in the same rule.
	if ($line =~ /target .* given more than once in the same rule/)
	{
		return 1;
	}
	
	# ERROR: <anything>
	if ($line =~ /^ERROR: /)
	{
		return 1;
	}
	
	# Not already returned so return false
	return 0;
}

# CheckForWarnings
#
# Inputs
# $iLine - Line of text to check
#
# Outputs
# Return true for presence of Warning in the line
# Return false for no Warning found
#
# Description
# This function matches the input against a known set of Warning Strings
sub CheckForWarnings
{
  my ($line) = @_;

	# RCOMP Warning: Unmatched enum name used as simple initialiser

	if ($line =~ /Warning: Unmatched/i)
	{
		return 1;
	}


	# BLDMAKE WARNING: read-only ABLD.BAT will be overwritten

	if ($line =~ /^BLDMAKE WARNING:/)
	{
		return 1;
	}


	# \FORM\GROUP\BLD.INF WARNING(S):
	# \FORM\GROUP\BLD.INF(28) : Exported source file \form\group\tagma.rtf not found

	if ($line =~ /WARNING\(S\)/)
	{
		return 1;
	}

	# WARNING: Can't find following headers in User or System Include Paths
	# WARNING: Frozen .DEF file \CSTUBSHELL\BMARM\STUBRUNU.DEF not found - project not frozen
	# WARNING: Not attempting to create any import libraries.
	# WARNING: rls_string STRING_r_ssl_error_ssl_AlertNoRenegotiation; either has incorrect syntax or no value

	if ($line =~ /^WARNING: /)
	{
		return 1;
	}

	# \BIOMSG\BITSINC\BioTestUtils.inl(4) : warning C4100: 'iOperation' : unreferenced formal parameter

	if ($line =~ /\(\d+\) : warning C/)
	{
		return 1;
	}

	# LINK : warning LNK4005: no objects used from library \EPOC32\RELEASE\WINS\UDEB\ESTOR.LIB

	if ($line =~ /LINK : warning/)
	{
		return 1;
	}

	# ..\\..\\BAFL\\SRC\\Bacline.cpp:68: warning: value computed is not used

	if ($line =~ /:\d+: warning:/)
	{
		return 1;
	}

	# "..\UCRT\Ecrt0.cpp", line 12: Warning:  #335-D: linkage specification is not allowed
	# "s16c.o(.directive)", line 70: Warning: L6331W: s16c.o(.directive)(line 70, col 14) No eligible global symbol matches pattern _fsqrt.

	if ($line =~ /"(.*)", line (\d+): (Warning: +(.\d+.*?):.*)$/)
	{
		return 1;
	}
		
	# /../../kvm/VmEPOC/src/emuNetDebuggerTransport.c
	# ### mwccsym2 Usage Warning:
	# #   Specified directory 'Z:/epoc32/include/libcnot' not found
	# ... t_winscw_udeb_cw_obj_g/serialDebuggerTransport.o
	# Linking lib ... winscw_udeb_cw_bin/tkmidp20_kvm.lib 

	if ($line =~ /Usage Warning:/)
	{
		return 1;
	}
	# mwld.exe: No symbols were exported

	if ($line =~ /mwld.exe:/)
	{
		return 1;
	}

	# === target == tools\e32tools
  #	make -r  -k -f "\EPOC32\BUILD\TOOLS\E32TOOLS\GROUP\TOOLS.make" SAVESPACE CFG=REL VERBOSE=-s KEEPGOING=-k
	#		nmake -nologo -x - -s -k -f "\EPOC32\BUILD\TOOLS\E32TOOLS\GROUP\ERUNTEST\TOOLS\ERUNTEST.TOOLS" REL CLEANBUILDREL
	# Command line warning D4002 : ignoring unknown option '/Op'
	
	if ($line =~ /^Command line warning/)
	{
		return 1;
	}
		
	# MAKEDEF WARNING: 1 export(s) not yet Frozen:

	if ($line =~ /^MAKEDEF WARNING:/)
	{
		return 1;
	}

	# Comment from PETRAN which is actually a warning rather than an error
	# ERROR: bad relocation:  [00004f60] = 00000f68

	if ($line =~ /ERROR: bad relocation:/)
	{
		return 1;
	}

	# 1 warning

	if ($line =~ /^(\d+) warning/)
	{
		return 1;
	}

	# Not already returned so return false
	return 0;
}

# CheckForNotBuilt
#
# Inputs
# $iLine - Line of text to check
#
# Outputs
# Return true for presence of Warning in the line
# Return false for no Warning found
# $iNotBuilt - Name of thing not built
#
# Description
# This function matches the input against a known set of Strings for things not built
sub CheckForNotBuilt
{
  my ($line) = @_;
  
  # MISSING COMPONENT alp2csh: can't find tools\sdk_eng\alp2csh\group\bld.inf

	if ($line =~ /^MISSING COMPONENT (.*):.* find (.*)$/)
	{
		return (1,$2);
	}

	# MISSING: \EPOC32\RELEASE\WINS\UDEB\OPLR.DLL

	if ($line =~ /^MISSING: (\S+)/)
	{
		return (1,$1);
	}
	
	# Not already returned so return false
	return 0;
}

# CheckForMissing
#
# Inputs
# $iLine - Line of text to check
#
# Outputs
# Return true for presence of Warning in the line
# Return false for no Warning found
# $iNotBuilt - Name of thing not built
#
# Description
# This function matches the input against a known set of Strings for things not built
sub CheckForMissing
{
  my ($line) = @_;
  
	if ($line =~ /fatal error U1073: .* make '(.*)'/)
	{
		return (1,$1);
	}
	
	# Not already returned so return false
	return 0;
}

# CheckForRealTimeErrors
#
# Inputs
# $iLine - Line of text to check
#
# Outputs
# Return true for presence of a Real Time Error in the line
#        plus string detailing error (if available)
# Return false for no Real Time Error found
#
# Description
# This function matches the input against a known set of Error Strings
# At the time of adding this subroutine, such error strings were only reported by P4GetSource.pm
# Scripts calling this subroutine should note that, for example, lines beginning with "ERROR:" will
# also be considered to be errors by subroutine CheckForErrors, above. 
sub CheckForRealTimeErrors
{
  my ($line) = @_;

	if ($line =~ /^Error:\s*RealTimeBuild:\s*(.*)/mi)
	{
		return (1,$1);  # Return True plus any other text on line
	}
	
	# Not already returned so return False
	return 0;
}
1;
