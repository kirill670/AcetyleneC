#!\bin\perl -w
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.

=pod
=head1 NAME

Symbian::SDK::FilterTool::FilterFileList - FilterFileList

=head1 SYNOPSIS

 use Symbian::SDK::FilterTool::FilterFileList

 my $filelist = new Symbian::SDK::FilterTool::FilterFileList();

 $filelist->ScanDir('some\\dir\\somewhere');

 $filelist->IncludeFile('some\\dir\\somewhere\\some\\file');
 $filelist->ExcludeFile('some\\dir\\somewhere\\some\\other\\file');

 my @included - $filelist->GetIncludedFiles();

=head1 DESCRIPTION
 
Maintains a list of files, and a record of whether they are to be included in a product or not

=head1 METHODS

=cut

package Symbian::SDK::FilterTool::FilterFileList;

use Symbian::File::List;
use File::Find;

=head2 new()

B<Returns>: C<Symbian::SDK::FilterTool::FilterFileList> - the newly created object

B<Parameters>: None

Simple constructor

=cut

sub new()
{
    my $class = shift;

    my $self = { "unfiltered" => {}, "included" => {}, "excluded" => {}, "reverse" => {} };

    bless $self, $class;

    return $self;
}

=head2 C<ScanDir(String $path)>

B<Returns>: None

B<Parameters>: C<$path> - Path to load list of files from

Must be called prior to IncludeFile() or ExcludeFile().

=cut

sub ScanDir($)
{
    my $self = shift;
    my ($path) = @_;

    # "unfiltered", "included" and "excluded" hash keys are ids into "files"
    $self->{ "unfiltered" } = {};
    $self->{ "included" } = {};
    $self->{ "excluded" } = {};
    $self->{ "reverse" } = {};
    $self->{ "files" } = new Symbian::File::List();

    # Define subroute to do the work
    my $include = sub
    {
        my $name = $File::Find::name;

        if ($name ne "" and -f $name)
        {

            # Ensure the file is in "files", then add the id to "unfiltered"
            my $id = $self->{ "files" }->AddFile($name);
            $self->{ "unfiltered" }->{$id} = "**uncategorised**";
            $self->{ "reverse" }->{$id} = 0; # 0 = unfiltered
        }
      };

    # Run @$include over all files
    find( $include, $path );
}

=head2 C<GetUnfilteredFiles()>

B<Returns>: C<List> - The unfiltered files (so far)

B<Parameters>: None

Reports on the files which have not been included or excluded. Generally useful as a record of things 'still to do'

=cut

sub GetUnfilteredFiles()
{
    my $self = shift;

    # Look up each id in "unfiltered" to get a list of filenames
    return map( $self->{ "files" }->LookupFile($_), keys %{$self->{ "unfiltered" }});
}

=head2 C<GetIncludedFiles()>

B<Returns>: C<List> - The names of files which have been included so far

B<Parameters>: None

Reports on the files which have been included (using IncludeFile)

=cut

sub GetIncludedFiles()
{
    my $self = shift;

    # Look up each id in "included" to get a list of filenames
    return map( $self->{ "files" }->LookupFile($_), keys %{$self->{ "included" }});
}

=head2 C<GetExcludedFiles()>

B<Returns>: C<List> - The names of files which have been excluded so far

B<Parameters>: None

Reports on the files which have been excluded (using ExcludeFile)

=cut

sub GetExcludedFiles()
{
    my $self = shift;

    # Look up each id in "excluded" to get a list of filenames
    return map( $self->{ "files" }->LookupFile($_), keys %{$self->{ "excluded" }});
}

=head2 C<GetCategory(String $file)>

B<Returns>: Any - The 'category' for the file, as previously given by CategoriseFile()

B<Parameters>: C<$file> - The name of the file

=cut

sub GetCategory($)
{
    my $self = shift;
    my ($file) = @_;

    my $id = $self->{ "files" }->GetFileID($file);

    # Hash values are the category
    my $category;
    $category=$self->{"included"}->{$id} if exists $self->{"included"}->{$id};
    $category=$self->{"unfiltered"}->{$id} if exists $self->{"unfiltered"}->{$id};
    $category=$self->{"excluded"}->{$id} if exists $self->{"excluded"}->{$id};
    if (defined $category)
    {
        if ($category eq "**uncategorised**")
        {
            $category = undef;
        }
        return $category;
    }
    else
    {
        die "WARNING: Couldn't provide cateogory for $file; file doesn't exist\n";
    }
}

=head2 C<IsIncluded(String $file)>

B<Returns>: C<Boolean> - True if the file has been included using IncludeFile. False otherwise

B<Parameters>: C<$file> - The file in question

=cut

sub IsIncluded($)
{
    my $self = shift;
    my ($file) = @_;

    my $id = $self->{ "files" }->GetFileID($file);

    return ($self->{"reverse"}->{$id} == 1);
}

=head2 C<IsExcluded(String $file)>

B<Returns>: C<Boolean> - True if the file has been excluded using ExcludeFile. False otherwise

B<Parameters>: C<$file> - The file in question

=cut

sub IsExcluded($)
{
    my $self = shift;
    my ($file) = @_;

    my $id = $self->{ "files" }->GetFileID($file);

    return ($self->{"reverse"}->{$id} == 2);
}

=head2 C<IncludeFile(String $file)>

B<Returns>: C<Boolean> - True if it was possible to set the file to included, False if not (due to it being already included, excluded or not actually existing)

B<Parameters>: C<$file> - the name of the file to include

In the case of non-existent or excluded files, a warning will be logged. In the case of an already included file, no message will be logged (but a value of False will still be returned).

=cut

sub IncludeFile($)
{
    my $self = shift;
    my ($file) = @_;

    my $id = $self->{ "files" }->GetFileID($file);

    my $state = $self->{"reverse"}->{$id};

    if (!defined $state)
    {
        print "WARNING: Couldn't include $file; file doesn't exist\n";
        return 0;
    }
    elsif ($state == 0)
    {
        $self->{"included"}->{$id} = $self->{"unfiltered"}->{$id};
        delete $self->{"unfiltered"}->{$id} or print "ERROR: Internal error: FilterFileList reverse lookup out of sync when including\n";
        $self->{"reverse"}->{$id} = 1; # 1 = include
        return 1;
    }
    elsif ($state == 2)
    {
        print "WARNING: Couldn't include $file; already excluded\n";
        return 0;
    }
    elsif ($state == 1)
    {

        # Do nothing: File already included
        return 0;
    }
    else
    {
        print "ERROR: Internal error: FilterFileList reverse lookup value invalid for including $file\: Value is $state\n";
        return 0;
    }
}

=head2 C<ExcludeFile(String $file)>

B<Returns>: C<Boolean> - True if it was possible to set the file to excluded, False if not (due to it being already excluded, included or not actually existing)

B<Parameters>: C<$file> - the name of the file to exclude

In the case of non-existent or included files, a warning will be logged. In the case of an already excluded file, no message will be logged (but a value of False will still be returned).

=cut

sub ExcludeFile($)
{
    my $self = shift;
    my ($file) = @_;

    my $id = $self->{ "files" }->GetFileID($file);

    my $state = $self->{"reverse"}->{$id};

    if (!defined $state)
    {
        print "WARNING: Couldn't exclude $file; file doesn't exist\n";
        return 0;
    }
    elsif ($state == 0)
    {
        $self->{"excluded"}->{$id} = $self->{"unfiltered"}->{$id};
        delete $self->{"unfiltered"}->{$id} or print "ERROR: Internal error: FilterFileList reverse lookup out of sync when excluding\n";
        $self->{"reverse"}->{$id} = 2; # 2 = exclude
        return 1;
    }
    elsif ($state == 1)
    {
        # Tolerate exclusion after inclusion. This is to support user defined filter rules
        $self->{"excluded"}->{$id} = $self->{"included"}->{$id};
        delete $self->{"included"}->{$id} or print "ERROR: Internal error: FilterFileList reverse lookup out of sync when excluding after include\n";
        $self->{"reverse"}->{$id} = 2; # 2 = exclude
        return 1;
    }
    elsif ($state == 2)
    {

        # Do nothing: File already excluded
        return 0;
    }
    else
    {
        print "ERROR: Internal error: FilterFileList reverse lookup value invalid for excluding $file\: Value is $state\n";
        return 0;
    }
}

=head2 C<CategoriseFile(String $file, Scalar $category)>

B<Returns>: C<boolean> - False if the file does not exist, true otherwise

=over 4

=item B<Parameters>:

=item $file - The name of the file to categorise

=item $category - Any value to assign as the category

=back

Assigns a category tag to a file

=cut

sub CategoriseFile($$)
{
    my $self = shift;
    my ($file, $category) = @_;

    my $id = $self->{ "files" }->GetFileID($file);

    # Hash values are the category
    if (exists $self->{"unfiltered"}->{$id})
    {
        $self->{"unfiltered"}->{$id} = $category;
    }
    elsif (exists $self->{"included"}->{$id})
    {
        $self->{"included"}->{$id} = $category;
    }
    elsif (exists $self->{"excluded"}->{$id})
    {
        $self->{"excluded"}->{$id} = $category;
    }
    else
    {
        print "WARNING: Couldn't categoriese $file; file doesn't exist\n";
        return 0;
    }

    return 1;
}

=head2 C<GetFileList()>

B<Returns>: C<Symbian::File::List> - An alternate representation of the total list of files

B<Parameters>: None

An accessor method for the total list of files in the form of a Symbian::File::List object

=cut

sub GetFileList()
{
    my $self = shift;

    return $self->{"files"};
}
1;
