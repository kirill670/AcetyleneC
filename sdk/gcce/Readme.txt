########################################################################
#
# File:   README
# Author: CodeSourcery, LLC
# Date:   2005-05-19
#
# Contents:
#   GNU Toolchain README
#
########################################################################

========
Contents
========

1. Introduction
2. License
3. Manifest
4. Support
5. Installing the Binary Packages
6. Validation
7. Source Packages

===============
1. Introduction
===============

This directory contains source code and binary packages for the Q1B 2005
GNU Toolchain release.

The GNU Toolchain consists of the GNU Binary Utilities (the assembler,
linker, and related programs), the GNU C and C++ compilers, C and
C++ runtime libraries, and the GNU debugger/simulator (GDB).

The GNU Toolchain supports both ARM and Thumb compilation and supports
multiple variants of the ARM architecture, including Version 6.  

Three different toolchains are provided:

1) An ARM GNU/Linux toolchain.  This includes the GNU C Library (glibc).
This toolchain is based on the arm EABI, and includes NPTL support.  As such
it may not be backwards compaitble with existing arm-linux toolchains or
systems.

2) A bare metal EABI based toolchain.  This includes a C library designed to
work in semihosted emvironments (eg. the GNU Simulator, or with the ARM
Armulator.  The same library can be used unchanged on many embedded systems,
if you provide the semihosting system calls.

3) A SymbianOS toolchain.  This does not include C or C++ runtime libraries.
These are supplied separately by Symbian.

==========
2. License
==========

These packages contain only free software.  

Most of the source code used to build these packages is licensed under
the GNU Public License (GPL).  The full text of the GNU Public License
is available online at:

  http://www.gnu.org/licenses/gpl.html

This software is provided with NO WARRANTY, to the extent permitted by
applicable law.  The software is provided "as is" without warranty of
any kind, either expressed or implied, including, but not limited to,
the implied warranties of merchantability and fitness for a particular
purpose.  See the GPL for additional information about the lack of any
warranty for this software.

All trademarks appearing in this document are the property of their
respective owners.

===========
3. Manifest
===========

The following table lists the files in this directory and their MD5
checksums:

 MD5 Checksum                     File
 ------------                     ----


==========
4. Support
==========

CodeSourcery does not provide free support for these packages.

CodeSourcery does provide paid support (including installation
assistance, defect correction, etc.) for these packages and for the
GNU Toolchain in general.  Please send mail to info@codesourcery.com
if you are interested in purchasing support for the GNU Toolchain.

=================================
5. Installing the Binary Packages
=================================

Nine binary packages are provided.  

The systems for which binary packages are available are:

1. Red Hat Linux 8.0 (and higher)

2. Solaris 2.8 (and higher)

3. Windows NT/2000/XP (and higher)

The GNU host triplets for these systems are given by the following table:

  Operating System        Host Triplet
  ----------------        --------------
  Red Hat Linux 8.0       i686-pc-linux-gnu
  Solaris 2.8             sparc-sun-solaris2.8
  Windows NT/2000/XP      i686-mingw32

For each system compilers are available for the following target triplets:

1. arm-none-linux-gnueabi - Compiler for EABI based linux/glibc targets.

2. arm-none-eabi - Compiler for EABI based embedded/newlib targets.

3. arm-none-symbianelf - Arm EABI based compiler for SymbianOS.

The binary package for the system whose host triplet is "y" for target
triplet "x" is "gnu-csl-arm-2005Q1C-y-x.tar.bz2".

To unpack the package, use the following commands:

  bunzip2 gnu-csl-arm-2005Q1C-y-x.tar.bz2
  tar xf gnu-csl-arm-2005Q1C-y-x.tar

NOTE: Problems have been experienced when using WinZip to unpack tar.bz2
packages.  The Windows package is also available as a installer
package.

These commands will create several subdirectories of the current
directory including "bin", "lib", and several others.

To use the binary packages, place the "bin" directory in your PATH.

The C compiler is "arm-none-eabi-gcc".  The C++ compiler is
"arm-none-eabi-g++".  

To compile a C program "test.c" and produce an executable "test.exe"
use the following command:

  arm-none-eabi-gcc test.c -o test.exe

To compile a C++ program "test.cc" and produce an executable
"test.exe" use the following command:

  arm-none-eabi-g++ test.cc -o test.exe

Additional documentation is available in the GNU "info" format in the
"info" subdirectory after installation.  For example, if you have the
GNU info reader installed, you can use:

  info -f ./info/gcc.info

to read the manual for the GNU C and C++ compilers.

=============
6. Validation
=============

The Red Hat Linux binary packages have been validated by running the
DejaGNU regression test suites for the GNU Binary Utilities, GNU C
Compiler, GNU C++ Compiler, and GNU C++ Runtime Library.  These
testsuites have been run in both ARM and Thumb mode, using the default
compilation options for the various tools.  These tests exercise the C
and C++ compiler with various levels of optimization including "-g",
"-O1", and "-O2".  All execution tests were performed by using the GNU
Simulator.

The complete set of test log and summary files can be found in the
various ".log" and ".sum" files in the "tests/" subdirectory.

The Solaris and Windows binary packages have been tested by compiling
a variety of sample programs and running them in the GNU Simulator.
The binary packages for Solaris and Windows are built from precisely
the same source code used to build the Red Hat Linux packages.

ARM-specific failures were observed in the following components:

  GNU Linker
  GNU C Compiler (Thumb Mode)
  GNU C Compiler (ARM Mode)
  GNU C++ Compiler (ARM Mode)
  GNU C++ Compiler (Thumb Mode)
  GNU IOC C++ Library

The following tables describe the specific failures observed.

GNU Linker
----------

  selective1
  selective2
  selective3

    These tests check a feature called "selective linking".  This
    feature works correctly in the linker provided in these packages,
    but the test scripts do not operate correctly in CodeSourcery's test
    environment.

GNU C Compiler (Thumb Mode)
---------------------------

  gcc.c-torture/compile/20020129-1.c

    This test attempts to cast the address of a structure to a
    function pointer type and then makes a call through the function
    pointer.  The GNU assembler refuses to assemble the code generated
    by the compiler.

    This test is not valid ANSI/ISO C.

  gcc.c-torture/execute/nest-stdar-1.c
  gcc.c-torture/execute/nestfunc-2.c

    This test uses the GNU "nested functions" extension to C.  That
    feature does not currently work correctly in all cases on ARM
    processors.

    This test is not valid ANSI/ISO C.

  gcc.c-torture/execute/builtin-types-compatible-p.c

    This test uses GCC extensions to verify that enum types have "int" type.
    The ARM EABI specifies that enum types use the shortest available
    type capable of holding the enumerated values.

    This test is not valid ANSI/ISO C.

  gcc.dg/compare1.c

    This test checks that correct compiler warnings are generated for
    signed/unsigned conversion enum types to integer types.  The ARM
    EABI specifies slightly different rules for the signedness of small
    integer types.
  
  [gcc.dg/c99-intcost-1.c]

    This test contains a very large number of integer constants and
    checks to see that the constants have the types required by C99.
    The compiler takes more than five minutes to compile this test
    case, which the testsuite considers to be a failure.

GNU C++ Compiler (ARM Mode)
-----------------------------

  g++.dg/eh/forced1.C
  g++.dg/eh/forced2.C
  g++.dg/eh/forced3.C
  g++.dg/eh/forced4.C

    These tests require functionality not provided byt the ARM EABI Exception
    Handling specification.

    This test is not valid ANSI/ISO C++.

  [g++.dg/eh/cleanup1.C]

    This test creates a very large function with a lot of C++
    exception-handling regions.  The compiler takes more than five
    minutes to compile this test case, which the testsuite considers
    to be a failure.

GNU C++ Compiler (Thumb Mode)
-----------------------------

  g++.dg/eh/forced1.C
  g++.dg/eh/forced2.C
  g++.dg/eh/forced3.C
  g++.dg/eh/forced4.C

    These tests require functionality not provided byt the ARM EABI Exception
    Handling specification.

    This test is not valid ANSI/ISO C++.

  [g++.dg/eh/cleanup1.C]

    This test creates a very large function with a lot of C++
    exception-handling regions.  The compiler takes more than five
    minutes to compile this test case, which the testsuite considers
    to be a failure.

  g++.gd/other/profile1.C

    This test involves the compiler inserting additional profiling
    which then causes a failure during register allocation.
    This situation should never occur except when -fprofile-arcs is used.

GNU ISO C++ Library
-------------------

  21_strings/basic_string/cons/char/6.cc
  21_strings/basic_string/inserters_extractors/char/10.cc
  21_strings/basic_string/inserters_extractors/char/11.cc
  27_io/basic_istream/getline/char/5.cc
  27_io/basic_istream/ignore/char/2.cc
  27_io/basic_stringbuf/overflow/char/1.cc
  27_io/ios_base/sync_with_stdio/1.cc
  27_io/objects/char/10.cc

    These tests allocate a large quantity of memory.  The simulator test
    environment used by CodeSourcery is unable to provide this.

  27_io/basic_filebuf/imbue/char/13582-2.cc

    This test uses the fork() and sleep() library functions.  The simulator
    test environment used by Codesourcery does not support these. 

==================
7. Source Packages
==================

The following source packages are available:

1. binutils-csl-arm-2005Q1C.tar.bz2

   This package contains the source code for the GNU Binary Utilities.

2. gcc-csl-arm-2005Q1C.tar.bz2

   This package contains the source code for GNU C and C++ compilers
   as well as the GNU C++ Runtime Library.

3. newlib-csl-arm-2005Q1C.tar.bz2

   This package contains the source code for the Newlib C library.

4. glibc-csl-arm-2005Q1C.tar.bz2

   This package contains the source code for the glibc C library.

To unpack package "x" use the following commands:

   bunzip2 x.tar.bz2
   tar xf x.tar
