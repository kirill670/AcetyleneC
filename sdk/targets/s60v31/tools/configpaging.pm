#
# configpaging.pm
#
#
# Copyright (c) 2006 Symbian Software Ltd.  All rights reserved.
#

# changes the paging/unpaged configuration of binaries a generated
# OBY file according to the list in configpaging.lst
#

# use
#	externaltool=configpaging.pm
# in oby file to enable
#
# use
#	tool=configpaging \epoc32\rom\myconfigpaging.lst
# to change the default configpaging.lst
#

package configpaging;

use strict;

our @EXPORT=qw(
        configpaging_info
        configpaging_single
        configpaging_multiple
);
use Exporter;
our @ISA=qw(Exporter);

# routine to provide information about the tool
sub configpaging_info ()
{
    my %toolinfo;
    $toolinfo{'name'} = "configpaging";
    $toolinfo{'invocation'} = "InvocationPoint2";
    $toolinfo{'multiple'} = \&configpaging_multiple;
    $toolinfo{'single'} = \&configpaging_single;
    return \%toolinfo;
}


my $configlist="\\epoc32\\rom\\configpaging.cfg";

# routine to handle multiple invocation
sub configpaging_multiple
{
    my ($line) = @_;
	my @args=split /[=\s]/, $line;
	$configlist=$args[2];
    return "REM configpaging.pm: Using $configlist";
}

#
# Set the default
#
my $defaultunpaged=0;

#
# paged list
#
my @pagedlist = (
);

#
# unpaged list
#
my @unpagedlist = (
);



sub isobystatement
{
	my ($li) = @_;
	if ($li =~ /\s*data\s*=/) { return 1;}
	if ($li =~ /\s*file\s*=/) { return 1;}
	if ($li =~ /\s*dll\s*=/) { return 1;}
	if ($li =~ /\s*secondary\s*=/) { return 1;}

	return 0;
}

# routine to handle single invocation
sub configpaging_single
{
    my ($oby) = @_;
	print "configpaging.pm: Modifying demand paging configuration using $configlist\n";
	if(!open FILE, $configlist)
		{
		print ("Can't open $configlist\n");
		return;
		}

	# parse the configlist
	# insert the files listed in the paged or unpaged list as appropriate
	my $default=\@unpagedlist;
	my $line;
	while ($line=<FILE>)
		{
		if ($line !~ /\S/ ) { next; }
		if ($line =~ /^\s*#/ ) { next; }

		if ($line =~ /^\s*defaultunpaged/)
			{ $defaultunpaged=1; }
		elsif ($line =~ /^\s*defaultpaged/)
			{ $defaultunpaged=0; }
		elsif ($line =~ /^\s*unpaged\:\s*/ )
			{ $default = \@unpagedlist; }
		elsif ($line =~ /^\s*paged\:\s*/ )
			{ $default= \@pagedlist; }

		elsif ($line =~ /\s*(\S+)\s*unpaged/)
			{ #print "unpaged...$line";
			 push @unpagedlist, $1; }
		elsif ($line =~ /\s*(\S+)\s*paged/)
			{ #print "paged...$line";
			push @pagedlist, $1; }
		elsif ( $line =~ /\s*(\S+)/ )
			{ #print "default...$line";
			push @$default, $1; }
		}
	close FILE;


#	foreach my $i (@pagedlist)
#		{ print "  paged $i\n"; }
#	foreach my $i (@unpagedlist)
#		{ print "  unpaged $i\n"; }


	# read the oby file that was handed to us
	# find matches between each oby line and any files  in the paged or unpaged list
	# modify the attributes of the oby line as appropriate
	my @newlines;
	foreach $line (@$oby)
		{
		my $add="";
		chomp $line;
		if (isobystatement($line))
			{
			if ($defaultunpaged) { $add=" unpaged"; }
			else { $add=" paged"; }
			my $lcline=lc($line);
			foreach my $match (@pagedlist) {
				if ($lcline =~ $match) { $add=" paged"; }
			}
			foreach my $match (@unpagedlist) {
				if ($lcline =~ $match) { $add=" unpaged"; }
			}
			if ($add)
				{
				$line =~ s/\bunpaged\b/ /ig;
				$line =~ s/\bpaged\b/ /ig;
				}
			}
		push @newlines, "$line$add\n";
		}
	@$oby = @newlines;
}

1;
