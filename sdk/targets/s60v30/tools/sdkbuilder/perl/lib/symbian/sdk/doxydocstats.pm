# DoxyDocStats.pm
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::SDK::DoxyDocStats;
use strict;

use Carp;
use XML::Parser;
use Symbian::Logger::Singleton;

sub new {
    my $class = shift;
    my $self = bless {
        depth  => 0,
        file   => undef,
        files  => {},
        last   => [],
        parser => undef,
    }, $class;
    return $self;
}

sub parse {
    my $self = shift;
    my $file = shift;
    $self->{depth} = 0;
    $self->{file} = $file;
    $self->{parser} = XML::Parser->new();
    $self->{parser}->setHandlers(
        Start => sub { $self->start_element(@_) },
        End   => sub { $self->end_element(@_) });
    return $self->{parser}->parsefile($file);
}

sub ignore {
    my $self = shift;
    my $element = shift;
    my @ignore = qw(
        Argument
        CapabilityConditional
        CapabilityUnconditional
        DocStats
	Namespace
    );
    return grep $element eq $_, @ignore;
}

sub start_element {
    my $self = shift;
    my $parser = shift;
    my $element = shift;
    my %attrib = @_;

    return if $self->ignore($element);

    my $logger = new Symbian::Logger::Singleton();
    
    $self->{depth}++;
    my $file = $attrib{file}; # current element file name

    if (!defined $file) { # inherited

        # check this isn't a top level element (root has no file to inherit)
        if ($self->{depth} == 1) {
            $logger->Warning("Element $element ".$attrib{name}." cannot inherit filename at ".$self->{file}." line ".$parser->current_line());
            return;
        }

        $file = $self->{last}[$self->{depth} - 1];
    }

    # check the im-access attribute is present and correct
    if (!defined $attrib{'im-access'}) {
        $logger->Warning("Element $element ".$attrib{name}." missing im-access level at ".$self->{file}." line ".$parser->current_line());
        return;
    }

    # check the line [number] attribute is present and correct (except Files)
    if (!defined $attrib{line} and $element ne 'File') {
        $logger->Warning("Element $element ".$attrib{name}." missing line number at ".$self->{file}." line ".$parser->current_line());
        return;
    }

    $file =~ s!\\!/!g; # Normalise slashes
    $file = lc($file); # Lower-case filename (FS is case insensitive)

    my $item = {
        line => $attrib{line},
        name => $attrib{name},
        type => $element};

    # index item by file and im category
    push @{$self->{files}{$file}{$attrib{'im-access'}}}, $item;

    # index by definition file also, where available
    if (defined $attrib{definitionFile}) {

        my $defnfile = $attrib{definitionFile};

        $defnfile =~ s!\\!/!g;     # Normalise slashes
        $defnfile = lc($defnfile); # Lower-case filename (FS is case insensitive)

        push @{$self->{files}{$defnfile}{$attrib{'im-access'}}}, $item;
    }

    # remember last for file "inheritance"
    $self->{last}[$self->{depth}] = $file;
}

sub end_element {
    my $self = shift;
    my $parser = shift;
    my $element = shift;
    return if $self->ignore($element);
    $self->{depth}--;
}

sub GetFileAccess {
    my $self = shift;
    my $file = shift;
    $file =~ s!\\!/!g; # Normalise slashes
    $file = lc($file); # Lower-case filename (FS is case insensitive)
    return unless exists $self->{files}{$file};
    return keys %{$self->{files}{$file}};
}

sub GetApiItems {
    my $self = shift;
    my $file = shift;
    my $access = shift;
    $file =~ s!\\!/!g; # Normalise slashes
    $file = lc($file); # Lower-case filename (FS is case insensitive)
    return unless exists $self->{files}{$file};
    return $self->{files}{$file}{$access};
}

1;

=pod

=head1 NAME

Symbian::SDK::DoxyDocStats - Parse DocStats XML files for IM information.

=head1 SYNOPSIS

 use Symbian::SDK::DoxyDocStats;

 my $dds = Symbian::SDK::DoxyDocStats->new();
 $dds->parse('c:/path/to/file.xml');

 my $file = '/path/to/file.h';
 my @im = $dds->GetFileAccess($file);

 for my $access (@im) {
     my @items = $dds->GetApiItems($file, $access);
     for my $item (@items) {
         # do something
     }
 }

=head1 DESCRIPTION

This module will parse DocStats XML file(s) and extract the IM information for
later use. Methods are provided (see below) to query the object for this info.

=head1 METHODS

=head2 new()

Takes no arguments and returns a new DoxyDocStats object.

=head2 parse('c:/path/to/file.xml')

Pass in the path to the file you are interested in parsing.

N.B. This method may be called more than once to parse many files into the same
object.

=head2 GetFileAccess('/path/to/file.h')

Returns a list of unique IM access levels seen for API items belonging to the
header file specified. If the file specified was not seen it returns undef.

=head2 GetApiItems('/path/to/file.h', 'accessLevel')

Pass in header file path and IM access level and all matching API entries will
be returned as a list. Each entry will consist of a hashref like this:

=begin text

    $item = {
        line =>  999,
        name => 'DummyApiItem',
        type => 'Function' };

=end

$item->{line} is the line number in the source file where the API item appears.
$item->{name} is the name of the API item.
$item->{type} is the type (or kind) of the item, e.g. Function, Enum etc.

=head1 COPYRIGHT

Copyright (c) 2005 Symbian Software Ltd. All rights reserved.

=cut
