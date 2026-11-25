#!perl
#
# EvalidCompare.pm
#
# Copyright (c) 2003 Symbian Ltd. All rights reserved.
#

package EvalidCompare;

use strict;
use IO::Handle;
use IO::File;
use Cwd;


#
# Constants.
#

my %typeLookup = (
		  'ARM PE-COFF executable' => 'ignore',
		  'E32 EXE' => 'e32',
		  'E32 DLL' => 'e32',
		  'Uncompressed E32 EXE' => 'e32',
		  'Uncompressed E32 DLL' => 'e32',
		  'Compressed E32 EXE' => 'e32',
		  'Compressed E32 DLL' => 'e32',
		  'Intel DLL' => 'intel_pe',
		  'Intel EXE' => 'intel_pe',
		  'MSDOS EXE' => 'intel_pe',
		  'Intel object' => 'intel',
		  'Intel library' => 'intel',
		  'ARM object' => 'arm',
		  'ARM library' => 'arm',
		  'unknown format' => 'identical',
		  'Java class' => 'identical',
		  'ZIP file' => 'zip',
		  'Permanent File Store' => 'permanent_file_store',
		  'SIS file' => 'identical',
		  'MSVC database' => 'ignore',
		  'MAP file' => 'map',
		  'SGML file' => 'sgml',
		  'Preprocessed text' => 'preprocessed_text',
		  'ELF file' => 'elf',
		  'Unknown COFF object' => 'identical',
		  'Unknown library' => 'identical',
		 );

my %typeHandler = (
		  e32 => {reader => 'petran', filter => \&PeTranFilter},
		  arm => {reader => 'nm --no-sort', filter => \&NmFilter, retry => 1, relative_paths => 1},
		  elf => {reader => 'elfdump', filter => \&ElfDumpFilter},
		  intel => {reader => 'dumpbin /symbols /exports', filter => \&DumpBinFilter, dos_paths => 1},
		  intel_pe => {reader => 'pe_dump', filter => \&FilterNone},
		  zip => {reader => 'unzip -l -v', filter => \&UnzipFilter, rawretry => 1},
		  map => {filter => \&MapFilter},
		  sgml => {filter => \&SgmlFilter},
		  preprocessed_text => {filter => \&PreprocessedTextFilter},
		  permanent_file_store => {reader => 'pfsdump -c -v', filter => \&PermanentFileStoreFilter, relative_paths => 1},
		  ignore => {filter => \&FilterAll}
		 );


#
# Globals.
#

my $log;
my $verbose;
my $toRoot;


#
# Public.
#

sub CompareFiles {
  my $file1 = shift;
  my $file2 = shift;
  $verbose = defined($_[0]) ? shift : 0;
  $log = defined($_[0]) ? shift : *STDOUT;
  # Try binary compare first (to keep semantics the same as evalid)...
  if (DoCompareFiles($file1, $file2, 'unknown format')) {
    return 1,'identical';
  }
  my $type = IdentifyFileType($file1);
  if ($typeLookup{$type} eq 'identical') {
    return 0,$type; # We already know a binary compare is going to return false.
  }
  return DoCompareFiles($file1, $file2, $type),$type;
}

sub GenerateSignature {
  my $file = shift;
  $verbose = defined($_[0]) ? shift : 0;
  $log = defined($_[0]) ? shift : *STDOUT;
  my $md5;

  if (eval "require Digest::MD5") { # Prefer Digest::MD5, if available.
    $md5 = Digest::MD5->new();
  } elsif (eval "require MD5") { # Try old version of MD5, if available.
    $md5 = new MD5;
  } elsif (eval "require Digest::Perl::MD5") { # Try Perl (Slow) version of MD5, if available.
    $md5 = Digest::Perl::MD5->new();
  } else {
    die "Error: Cannot load any MD5 Modules";
  }

  my $type = IdentifyFileType($file);
  WriteFilteredData($file, $type, $md5);
  return $md5->hexdigest(), $type;
}


#
# Private.
#

sub IdentifyFileType {
  my $file = shift;
  open (FILE, $file) or die "Error: Couldn't open \"$file\" for reading: $!\n";
  binmode (FILE);
  my $typeBuf;
  read (FILE, $typeBuf, 512);
  close (FILE);
  my ($uid1, $uid2, $uid3, $checksum) = unpack "V4", $typeBuf;

  # NB. Need to use the s modifier so that '.' will match \x0A

  if ($typeBuf =~ /^.\x00\x00\x10.{12}EPOC.{8}(....).{12}(.)\x00\x00(.)/s) {
    # E32 Image file with a 0x100000?? UID1
    # $2 is the flag field indicating an EXE or a DLL
    # $3 is the flag byte indicating compressable executables
    # $1 is the format field indicating compression type
    # See e32tools\inc\e32image.h
    #
    my $typename = "E32 EXE";
    if ((ord $2) & 0x1) {
      $typename = "E32 DLL";
    }
    if ((ord $3) & 0x1) {
	  if ((ord $1) != 0) {
        $typename = "Compressed $typename";
	  }
	  else {
        $typename = "Uncompressed $typename";
	  }
    }
    return $typename;
  }

  if ($typeBuf =~ /^\x4D\x5A.{38}\x00{20}(....)/s) {
    # A standard 64-byte MS-DOS header with e_magic == IMAGE_DOS_SIGNATURE
    # $1 is e_lfanew, which we expect to point to a COFF header

    my $offset = unpack "V",$1;
    if ($offset + 24 <= length $typeBuf) {
      $typeBuf = substr $typeBuf, $offset;
    }
    else {
      open FILE, $file or die "Error: Couldn't open \"$file\" for reading: $!\n";
      binmode FILE;
      seek FILE, $offset, 0;
      read FILE, $typeBuf, 512;
      close FILE;
    }

    if ($typeBuf =~ /^PE\0\0\x4c\x01.{16}(..)/s) {
      # A PE signature "PE\0\0" followed by a COFF header with
      # machine type IMAGE_FILE_MACHINE_I386
      # $1 is the characteristics field
      #
      if ((unpack "v",$1) & 0x2000) {
		return "Intel DLL";
      }
      else {
		return "Intel EXE";
      }
    }
	elsif($typeBuf =~ /^PE\0\0\0\x0a/) {
	# A PE signature "PE\0\0" followed by ARM COFF file magic value 0xA00
		return "ARM PE-COFF executable";
	}
    else {
      return "MSDOS EXE";
    }
  }

  if ($typeBuf =~ /^(\x4c\x01|\x00\x0A).(\x00|\x01).{4}...\x00/s) {
    # COFF header with less than 512 sections and a symbol table
    # at an offset no greater than 0x00ffffff

    if ($1 eq "\x4c\x01") {
      return "Intel object";
    }
    elsif ($1 eq "\x00\x0A") {
      return "ARM object";
    }
    else {
      return "Unknown COFF object";
    }
  }

  if ($typeBuf =~ /^!<arch>\x0A(.{48}([0-9 ]{10})\x60\x0A(..))/s) {
    # library - could be MARM or WINS

    $typeBuf = $1;
    my $member_start = 8;

    open (FILE, $file) or die "Error: Couldn't open \"$file\" for reading: $!\n";
    binmode (FILE);

    while ($typeBuf =~ /^.{48}([0-9 ]{10})\x60\x0A(..)/s) {
      # $1 is the size of the archive member, $2 is first 2 bytes of the file
      # There may be several different sorts of file in the archive, and we
      # need to scan through until we find a type we recognize:
      # $2 == 0x0A00 would be ARM COFF, 0x014C would be Intel COFF
      if ($2 =~ /\x00\x0A/) {
	close FILE;
	return "ARM library";
      }
      if ($2 =~ /\x4C\x01/) {
	close FILE;
	return "Intel library";
      }

      $member_start += 60 + $1;
      if ($member_start & 0x1) {
        $member_start += 1;	# align to multiple of 2 bytes
      }
      seek FILE, $member_start, 0;
      read FILE, $typeBuf, 512;
    }
    close FILE;
    return "Unknown library";
  }

  if ($typeBuf =~ /^\xCA\xFE\xBA\xBE/) {
    # Java class file - should have match as a straight binary comparison
    return "Java class";
  }

  if ($typeBuf =~ /^PK\x03\x04/) {
    # ZIP file
    return "ZIP file";
  }

  if ($uid1 && $uid1==0x10000050) {
    # Permanent File Store
    return "Permanent File Store";
  }

  if ($uid1 && $uid2 && $uid3 && $checksum && $uid3==0x10000419) {
    if (($uid1==0x100002c3 && $uid2==0x1000006d && $checksum==0x128ca96f)  # narrow
	||  ($uid1==0x10003b0b && $uid2==0x1000006d && $checksum==0x75e21a1d)  # unicode
	||  ($uid1==0x10009205 && $uid2==0x10003a12 && $checksum==0x986a0c25)) # new format
      {
      # SIS file
      return "SIS file";
      }
  }

  if ($typeBuf =~ /^Microsoft [^\x0A]+ [Dd]atabase/s) {
    return "MSVC database";
  }

  if ($typeBuf =~ /^\S.+ needed due to / || $typeBuf =~ /^Archive member included.*because of file/) {
    # GCC MAP file
    return "MAP file";
  }

  if ($typeBuf =~ /Preferred load address is/) {
    # Developer Studio MAP file
    return "MAP file";
  }

  if ($typeBuf =~ /^Address   Size      Name    Subname  Module/) {
    # CodeWarrior MAP file
    return "MAP file";
  }

  if ($typeBuf =~ /<!DOCTYPE/i) {
    # XML or HTML file - need to ignore javadoc generation dates
    return "SGML file";
  }

  if ($typeBuf =~ /^# 1 ".*"(\x0D|\x0A)/s) {
    # Output of CPP
    return "Preprocessed text";
  }

  if ($typeBuf =~/^\x7F\x45\x4C\x46/) {
    # ELF file
    return "ELF file";
  }

  return 'unknown format';
}

sub WriteFilteredData {
  my $file = shift;
  my $type = shift;
  my $md5 = shift;

  unless (exists $typeLookup{$type}) {
    die "Invalid file type \"$type\"";
  }
  $type = $typeLookup{$type};

 if ($type ne 'identical') {
    unless (exists $typeHandler{$type}) {
      die "Invalid comparison type \"$type\"";
    }
    my $reader = $typeHandler{$type}->{reader};
    my $filter = $typeHandler{$type}->{filter};
    my $retry = $typeHandler{$type}->{retry} || 0;
    my $rawretry = $typeHandler{$type}->{rawretry} || 0;
    my $relativePaths = $typeHandler{$type}->{relative_paths} || 0;
	my $dosPaths = $typeHandler{$type}->{dos_paths} || 0;
	
    if ($relativePaths) {
      $file = RelativePath($file);
    }
    if ($dosPaths) {
      $file =~ s/\//\\/g;       # convert to DOS-style backslash separators
    }
    
    my $raw;
    if ($reader) {
      $raw = IO::File->new("$reader \"$file\" 2>&1 |") or die "Error: Couldn't run \"$reader $file\": $!\n";
    }
    else {
      $raw = IO::File->new("$file") or die "Error: Couldn't open \"$file\": $!\n";
    }
    while (my $line = <$raw>) {
      &$filter(\$line);
      $md5->add($line);
    }
    Drain($raw);
    $raw->close();

    # Retry once if reader failed and reader has retry specified
    if ((($?>>8) != 0) && ($retry == 1))
    {
      print "Warning: $reader failed (" .($?>>8). ") on $file - retrying\n";
      # Reset MD5
      $md5->reset;
      $raw = IO::File->new("$reader \"$file\" 2>&1 |") or die "Error: Couldn't run \"$reader $file\": $!\n";
      while (my $line = <$raw>)
      {
        &$filter(\$line);
        $md5->add($line);
      }
      Drain($raw);
      $raw->close();
      if (($?>>8) != 0)
      {
        print "Error: $reader failed again (" .($?>>8) .") on $file - reporting failure\n";
      }
    }

    # Retry as raw if specified
    if (($?>>8) != 0) {
      if ($rawretry)
      {
        print "Warning: $reader failed (". ($?>>8) .") on file $file - retrying as raw binary\n";
        # Set type to be identical so it will try it as a raw binary stream
        $type = 'identical';
      } else {
        print "Error: $reader failed (". ($?>>8) .") on file $file - not retrying as raw binary\n";
      }
    }
  }
  if ($type eq 'identical') {
    # Reset md5 as it might have been used in reader section
    $md5->reset;
    # Treat 'identical' as a special case - no filtering, just write raw binary stream.
    my $raw = IO::File->new($file) or die "Error: Couldn't open \"$file\" for reading: $!\n";
    binmode($raw);
    my $buf;
    while ($raw->read($buf, 4096)) {
      $md5->add($buf);
    }
    $raw->close();
  }

}

sub DoCompareFiles {
  my $file1 = shift;
  my $file2 = shift;
  my $type = shift;
  my $same = 0;
  unless (exists $typeLookup{$type}) {
    die "Invalid file type \"$type\"";
  }
  $type = $typeLookup{$type};
  if ($type ne 'identical')
  {
    unless (exists $typeHandler{$type}) {
      die "Invalid comparison type \"$type\"";
    }
    my $reader = $typeHandler{$type}->{reader};
    my $filter = $typeHandler{$type}->{filter};
    my $retry = $typeHandler{$type}->{retry} || 0;
    my $rawretry = $typeHandler{$type}->{rawretry} || 0;
    my $relativePaths = $typeHandler{$type}->{relative_paths} || 0;
    if ($relativePaths) {
      $file1 = RelativePath($file1);
      $file2 = RelativePath($file2);
    }
    my $fileHandle1;
    my $fileHandle2;
    if ($reader) {
      $fileHandle1 = IO::File->new("$reader \"$file1\" 2>&1 |") or die "Error: Couldn't run \"$reader $file1\": $!\n";
      $fileHandle2 = IO::File->new("$reader \"$file2\" 2>&1 |") or die "Error: Couldn't run \"$reader $file2\": $!\n";
    }
    else {
      $fileHandle1 = IO::File->new("$file1") or die "Error: Couldn't open \"$file1\": $!\n";
      $fileHandle2 = IO::File->new("$file2") or die "Error: Couldn't open \"$file2\": $!\n";
    }
    $same = CompareTexts($fileHandle1, $fileHandle2, $filter, $file1);
    Drain($fileHandle1, $fileHandle2);

    $fileHandle1->close();
    my $status1 = $?>>8;
    $fileHandle2->close();
    my $status2 = $?>>8;
    if (($retry) && ($status1 != 0 or $status2 != 0))
    {
      print ($log "Warning: $reader failed ($status1, $status2) - retrying\n");

      # Repeat previous code by hand, rather than calling DoCompareFiles
      # again: if it's a systematic failure that would be a never ending loop...

      $fileHandle1 = IO::File->new("$reader \"$file1\" 2>&1 |") or die "Error: Couldn't run \"$reader $file1\": $!\n";
      $fileHandle2 = IO::File->new("$reader \"$file2\" 2>&1 |") or die "Error: Couldn't run \"$reader $file2\": $!\n";
      $same = CompareTexts($fileHandle1, $fileHandle2, $filter, $file1);
      Drain($fileHandle1, $fileHandle2);
      $fileHandle1->close();
      $status1 = $?>>8;
      $fileHandle2->close();
      $status2 = $?>>8;
      if ($status1 != 0 or $status2 != 0)
      {
        print ($log "Warning: $reader failed again ($status1, $status2) - reporting failure\n");
        $same = 0;
      }
    }

    # Retry as raw if specified
    if (($rawretry)&& ($status1 != 0 or $status2 != 0))
    {
      if ($rawretry)
      {
        print ($log "Warning: $reader failed (" .$?>>8 .") on a file retrying as raw binary\n");
        # Set type to be identical so it will try it as a raw binary stream
        $type = 'identical';
      } else {
        print ($log "Error: $reader failed (". $?>>8 .") on a file not retrying as raw binary\n");
      }
    }

  }

  if ($type eq 'identical') {
    # Treat 'identical' as a special case - no filtering, just do raw binary stream comparison.
    my $fileHandle1 = IO::File->new($file1) or die "Error: Couldn't open \"$file1\" for reading: $!\n";
    my $fileHandle2 = IO::File->new($file2) or die "Error: Couldn't open \"$file2\" for reading: $!\n";
    binmode($fileHandle1);
    binmode($fileHandle2);
    $same = CompareStreams($fileHandle1, $fileHandle2, $file1);
  }

  return $same;
}

sub CompareStreams {
  my $fileHandle1 = shift;
  my $fileHandle2 = shift;
  my $filename = shift;
  my $same = 1;
  my $offset = -4096;
  my $buf1;
  my $buf2;
  while ($same) {
    my $len1 = $fileHandle1->read($buf1, 4096);
    my $len2 = $fileHandle2->read($buf2, 4096);
    if ($len1 == 0 and $len2 == 0) {
      return 1;
    }
    $same = $buf1 eq $buf2;
    $offset += 4096;
  }
  if ($verbose) {
    my @bytes1 = unpack "C*", $buf1;
    my @bytes2 = unpack "C*", $buf2;
    foreach my $thisByte (@bytes1) {
      if ($thisByte != $bytes2[0]) {
	printf $log "Binary comparison: %s failed at byte %d: %02x != %02x\n", $filename, $offset, $thisByte, $bytes2[0];
	last;
      }
      shift @bytes2;
      $offset+=1;
    }
  }
  return 0;
}

sub CompareTexts {
  my $fileHandle1 = shift;
  my $fileHandle2 = shift;
  my $cleaner = shift;
  my $filename = shift;
  my $same = 1;
  my $lineNum = 0;
  my $line1 = '';
  my $line2 = '';
  while ($same) {
    $line1 = <$fileHandle1>;
    $line2 = <$fileHandle2>;
    if (not defined ($line1) and not defined ($line2)) {
      return 1;
    }
    elsif (not defined ($line1) or not defined ($line2)) {
      return 0;
    }
    &$cleaner(\$line1);
    &$cleaner(\$line2);
    $same = $line1 eq $line2;
    $lineNum += 1;
  }
  printf ($log "Text comparison: %s failed at line %d\n< %s> %s\n", $filename, $lineNum, $line1, $line2) if ($verbose);
  return 0;
}

sub Drain {
  foreach my $handle (@_) {
    while (my $line = <$handle>) {
    }
  }
}

sub RelativePath {
  my $name = shift;
  if (($name =~ /^\\[^\\]/) || ($name =~ /^\//)) {	# abs path (unix or windows), not UNC
    unless ($toRoot) {
      $toRoot = getcwd();
      $toRoot =~ s/\//\\/g;
      $toRoot =~ s/^[a-zA-Z]:\\(.*)$/$1/;
      $toRoot =~ s/[^\\]+/../g;
      if ($toRoot =~ /^$/) {
	$toRoot = '.';		# because we are starting in the root
      }
    }
    return $toRoot.$name;
  }
  return $name;
}

#
# Filters.
#

sub PeTranFilter {
  my $line = shift;
  if ($$line =~ /Time Stamp:|E32ImageFile|Header CRC:/) { # Ignore time stamps, petran version info and file names, Header CRC which uses the timestamp.
    $$line = '';
  }
}

sub ElfDumpFilter {
  my $line = shift;
  $$line  =~ s/^	Program header offset.*$/Program header offset/;
  $$line  =~ s/^	Section header offset.*$/Section header offset/;
}

sub NmFilter {
  my $line = shift;
  $$line =~ s/^.*:$//;								# ignore the filenames
  $$line =~ s/\.\.\\[^(]*\\//g;
  $$line =~ s/\.\.\/[^(]*\///g;	# ignore pathnames of object files
  if ($$line =~ /^(.+ (_head|_))\w+_(EPOC32_\w+(_LIB|_iname))$/i) {
    # dlltool uses the "-o" argument string as the basis for a "unique symbol", but
    # doesn't turn the name into a canonical form first.
    # dh.o:
    #          U ________EPOC32_RELEASE_ARM4_UREL_EIKCOCTL_LIB_iname
    # 00000000 ? _head_______EPOC32_RELEASE_ARM4_UREL_EIKCOCTL_LIB
    $$line = uc "$1_..._$3\n";
  }
}

sub DumpBinFilter {
  my $line = shift;
  $$line =~ s/^Dump of file.*$/Dump of file/;     # ignore the file names
  $$line =~ s/line# .*[0-9A-Fa-f]{4}/line#/;      # ignore source line numbers
  $$line =~ s/^.*\| \.file$//;                    # ignore description of .file symbol table entries
  $$line =~ s/^    ([A-Z]:)?\\.*\\//;             # ignore value of Filename .file things
  $$line =~ s/^000.* \@comp\.id$//;               # ignore lib.exe version number
  $$line =~ s/^[0-9A-Fa-f]{3} /999 /;             # ignore COFF section number
  $$line =~ s/^\s+tag index.*$//;                 # chat including COFF section number
  $$line =~ s/(\s+Section length) [0-9A-Fa-f]{4}/$1/;# size (of debug section in particular)
  $$line =~ s/^\s+[0-9A-Fa-f]+ \.debug.*$//;      # summary of debug section size
}

sub MapFilter {
  my $line = shift;
  $$line =~ s/([d-z])\d*s_?\d+\.o/$1s999.o/;                     # ignore the names of intermediate files in .LIB
  $$line =~ s/([d-z])\d*([ht])\.o/$1$2.o/;                       # ignore the names of intermediate files in .LIB
  $$line =~ s-/-\\-go;                                           # convert / into \
  $$line =~ s/(\.\.\\|.:\\)[^(]*\\//g;                           # ignore pathnames of object files
  $$line =~ s/\.stab.*$//;                                       # ignore .stab and .stabstr lines
  $$line =~ s/0x.*size before relaxing//;                        # ignore additional comments about .stab and .stabstr
  $$line =~ s/(_head|_)\w+_(EPOC32_\w+(_LIB|_iname))/$1_,,,_$3/; # dlltool-generated unique symbols
  $$line =~ s/Timestamp is .*$//;                                # ignore timestamps in DevStudio map files
}

sub UnzipFilter {
  my $line = shift;
  $$line =~ s/^Archive:.*$/Archive/;                 # ignore the archive names
  # Line format of unzip -l -v
  # Length   Method    Size  Ratio   Date   Time   CRC-32    Name
  $$line =~ s/ (\d+).*? ..-..-..\s+..:.. / ($1) 99-99-99 99:99 /;  # ignore (Method Size Ratio Date Time) on contained files
}

sub SgmlFilter {
  my $line = shift;
  $$line =~ s/<!--.*-->//;  # ignore comments such as "generated by javadoc"
}

sub PreprocessedTextFilter {
  my $line = shift;
  $$line =~ s/^# \d+ ".*"( \d)?$//;  # ignore #include history
}

sub PermanentFileStoreFilter {
  my $line = shift;
  $$line =~ s/^Dumping .*$/Dumping (file)/;  # ignore the source file names
}

sub FilterAll {
  my $line = shift;
  $$line = '';
}

sub FilterNone {
}

1;

__END__

=head1 NAME

EvalidCompare.pm - Utilities for comparing the contents of files.

=head1 DESCRIPTION

This package has been largely factored out of the C<e32toolp> tool C<evalid>. The main pieces of borrowed functionality are the ability to identify file types by examining their content, and the ability to filter irrelevant data out of files to allow comparisons to be performed. This refactoring was done in order to allow both direct and indirect comparisons of files to be supported. Direct comparisions are done by reading a pair of files (in the same way the C<evalid> does). Indirect comparisons are done by generating MD5 signatures of the files to be compared. The later method allows comparisons to be performed much more efficiently, because only one file need be present provided the signature of the other is known.

=head1 INTERFACE

=head2 CompareFiles

Expects to be passed a pair of file names. May optionally also be passed a verbosity level (defaults to 0) and a file handle for logging purposes (defaults to *STDIN). Returns 1 if the files match, 0 if not. Firstly does a raw binary compare of the two files. If they match, no further processing is done and 1 is returned. If not, the type of the first file is found and the files are re-compared, this time ignoring data known to be irrelevant for the file type. The result of this compare is then returned.

=head2 GenerateSignature

Expects to be passed a file name. May optionally also be passed a verbosity level (defaults to 0) and a file handle for logging purposes (defaults to *STDIN). Returns an MD5 signature of the specified file contents, having ignored irrelevant data associted with its type. This signature may subsequently be used to verify that the contents of the file has not been altered in a significant way.

=head1 KNOWN BUGS

None.

=head1 COPYRIGHT

Copyright (c) 2003 Symbian Ltd. All rights reserved.

=cut

__END__
