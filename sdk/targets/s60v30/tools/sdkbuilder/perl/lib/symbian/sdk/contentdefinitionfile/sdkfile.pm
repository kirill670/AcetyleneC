#!perl
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
# SdkFile - Module to create/update SdkFile object that corresponds to a file xml element
#

package Symbian::SDK::ContentDefinitionFile::SdkFile;

use strict;
use File::Basename;
use File::Spec::Functions;
use Symbian::SDK::Utils;
use Symbian::Logger::Singleton;

# New() : create a new SdkFile
#
# Parameters:
#   - source : source file(s)
#   - destination: destination file/path
#   - recursive :  true/false
# Returns:
#   the newly created SdkFile object reference
sub New
{
    my $pkg = shift;
    my $self = {};
    bless $self, $pkg;
    $self->{logger} = Symbian::Logger::Singleton->new();
    my ($order,$source,$destination,$recursive,@excludes) = @_;
    $self->{order} = $order if defined $order;
    $self->{source} = $source if defined $source;
    $self->{destination} = $destination if defined $destination;
    $self->{recursive} = $recursive if defined $recursive;
    $self->SdkFileExcludes(@excludes);
    return $self;
}

# SdkFileOrder() : set/get order
#
# Parameters:
#   - order
# Returns:
#   - order
sub SdkFileOrder
{
    my $self = shift;
    my $newval = shift;
    $self->{order} = $newval if defined $newval;
    return $self->{order};
}

# SdkFileSource() : set/get source
#
# Parameters:
#   - source
# Returns:
#   - source
sub SdkFileSource
{
    my $self = shift;
    my $newval = shift;
    $self->{source} = lc(canonpath($newval)) if defined $newval;
    return $self->{source};
}

# SdkFileDestination() : get/set destination
#
# Parameters:
#   - destination
# Returns:
#   - destination
sub SdkFileDestination
{
    my $self = shift;
    my $newval = shift;
    $self->{destination} = lc(canonpath($newval)) if defined $newval;
    return $self->{destination};
}

# SdkFileRecursive() : set/get recursive
#
# Parameters:
#   - recursive true/false
# Returns:
#    - recursive 1/0
sub SdkFileRecursive
{
    my $self = shift;
    my $newval = shift;
    $self->{recursive} = lc($newval) if defined $newval;
    if (exists ($self->{recursive}) && $self->{recursive} =~ /true/i)
    {
        return 1;
    } else
    {
        return 0;
    }
}

# SdkFileExcludes() : set/get excludes
#
# Parameters:
#    - exclude array
# Returns:
#    - exclude array
sub SdkFileExcludes
{
    my $self = shift;
    my (@newval) = @_;
    foreach my $exclude (@newval)
    {
        push @{$self->{exclude}},{path=>$exclude};
    }
    my @excludes = ();
    @excludes = map($_->{path},@{$self->{exclude}});
    return \@excludes;
}

# validateFile() : validates the content of the current object
#
# Parameters:
#   - rootpath : path to the source location
# Returns:
#   - valid : 1 valid - 0 invalid
sub ValidateFile
{
    my $self = shift;
    my $rootPath = shift;
    $rootPath = canonpath($rootPath);

    if (! exists ($self->{valid}))
    {
        my $source = $self->SdkFileSource();
        my $destination = $self->SdkFileDestination();
        my $recursive = $self->SdkFileRecursive();
        my $message = "";
        $message  .= "<source=$source " if $source;
        $message .= "destination=$destination " if $destination;
        $message .= "recursive=$recursive>\n";
        my $error = 0;
        if ( !defined $source )
        {

            # source not defined
            $message .= "Source not defined\n";
            $self->{logger}->Error($message);
            $self->{valid} = 0;
            return $self->{valid};
        }
        if ( defined $destination && Symbian::SDK::Utils::HasWildCards($destination))
        {

            # destination has wcards
            $message .= "Destination can not have wildcards\n";
            $self->{logger}->Error($message);
            $self->{valid} = 0;
            return $self->{valid};
        }
        my $fullsource = Symbian::SDK::Utils::GetFullPath($rootPath,$source);

        my $destinationName = undef;
        my $destinationPath = undef;

        if (defined $destination)
        {
            if ( $destination =~ /[\\\/]$/)
            {

                # destination ending with \ or / so assume it's a directory
                $destinationPath = canonpath($destination);
            } else
            {

                # split it into directory name and file name
                $destinationPath = dirname(canonpath($destination));
                $destinationName = basename(canonpath($destination));
            }
        }

        if ( !Symbian::SDK::Utils::HasWildCards($source) && ! -e $fullsource )
        {

            # source does not have wcards but it does not exist
            $message .= "Source <$fullsource> does not exist\n";
            $self->{logger}->Error($message);
            $self->{valid} = 0;
            return $self->{valid};
        }

        if ( -e $fullsource && $recursive )
        {

            # source exists but recursive is on
            $message .= "Recursive not allowed with single files or folders\n";
            $self->{logger}->Error($message);
            $self->{valid} = 0;
            return $self->{valid};
        }

        #check the not allowed expressions between source and destination
        if ( $destinationName && ! -f $fullsource )
        {

            # source is not a single file and destination suggest a rename case
            $message .= "Rename not allowed src=" . catfile($rootPath,$source) . "     dest=$destination destname=$destinationName\n";
            $self->{logger}->Error($message);
            $self->{valid} = 0;
            return $self->{valid};
        }
        $self->{valid} = 1;
    }
    return $self->{valid};

}

# getSdkFileSources() : expands and resolve source and destination + recursive to build the list (hash)
#                       destination file - source file
#
# Parameters:
#   - rootpath: path to the source location
#   - component name
#   - componentsources : a refrence to the full component list (hash)
#   - sdksource : a reference to the full sdk list (hash)
# Returns:
#   var -desc
sub GetSdkFileSources
{
    my $self = shift;
    my $rootPath = canonpath(shift);
    my $componentName = shift;
    my $componentsources = shift;
    my $sdksources = shift;
    my $source;
    my $sourceName;
    my $sourcePath;
    my $destination;
    my $destinationName;
    my $destinationPath;
    my $recursive=0;
    my $searchPattern;
    our @sources = ();
    my $moves;

    my $resolved_destination;

    if ( ! $self->ValidateFile($rootPath) )
    {
        return $moves; # empty
    }

    # get source
    $source = $self->SdkFileSource();
    $source =~ s/^[\\\/]//;
    my $fullsource = Symbian::SDK::Utils::GetFullPath($rootPath,$source);

    # get recursive
    $recursive = $self->SdkFileRecursive();

    # get destination
    $destination = $self->SdkFileDestination();
    if (defined $destination)
    {
        $destination = canonpath($destination);
        if ( $destination =~ /[\\\/]\s*$/)
        {

            # directory
            $destinationPath = $destination;
        } else
        {

            # split into directory and file name
            $destinationPath = dirname($destination);
            $destinationName = basename($destination);
        }
    }
    if (-f $fullsource || -d $fullsource)
    {

        #single file
        @sources = ($source);
    } else
    {
        @sources = ResolveSource($rootPath, $source, $recursive);
    }
    my $message = $componentName .
      " : <source=".$self->SdkFileSource();
    $message .= " destination=". $destination if defined $destination;
    $message .= " recursive=".$self->SdkFileRecursive().">";
    if (! scalar @sources )
    {
        $self->{logger}->Warning($message . " does not match any file");
    }

    my @compoverrides=();
    my @sdkoverrides=();
    my $excludes = ConvertFileSpecToRegExp($self->SdkFileExcludes());
    foreach my $srcPath (@sources)
    {
        $srcPath = lc(canonpath($srcPath));
        if(!MatchRegExp($srcPath,$excludes))
        {
            if ($recursive or !defined $destination)
            {

                # preserve path
                $resolved_destination = defined($destination) && ! file_name_is_absolute($srcPath)
                  ? catfile($destinationPath,$srcPath)
                  : defined ($destination)
                  ? catfile($destination,basename($srcPath))
                  : undef;
            } else
            {

                # do not preserve path
                if ( -d $source )
                {
                    $resolved_destination = defined ($destination) && ! file_name_is_absolute($srcPath)
                      ? catfile($destination, $source)
                      : $source;
                } else {
                    $resolved_destination = defined($destinationName)
                      ? $destination
                      : catfile($destinationPath,basename($srcPath));
                }
            }
            $resolved_destination = lc(canonpath($resolved_destination)) if $resolved_destination;
            if (!$resolved_destination)
            {
                $resolved_destination = $srcPath;
                $srcPath = undef;
            }
            if ( exists $$componentsources->{$resolved_destination})
            {
                if (defined $$componentsources->{$resolved_destination} && ($$componentsources->{$resolved_destination} ne $srcPath))
                {

#print "$componentName : override destination = $resolved_destination source = ".$$componentsources->{$resolved_destination} . "\n";
                    push @compoverrides, $resolved_destination;
                }
                next;
            } elsif (exists $$sdksources->{$resolved_destination})
            {
                if (defined $$sdksources->{$resolved_destination} && ($$sdksources->{$resolved_destination} ne $srcPath))
                {
                    push @sdkoverrides, $resolved_destination;
                }
                next;
            }

            $$componentsources->{$resolved_destination} = $srcPath;
            $$sdksources->{$resolved_destination} = $srcPath;
        }
    }
    if ($#compoverrides >= 0 )
    {
        $self->{logger}->Error("In Component: $componentName\n" .
              $message .
              "\nattempts to override the following files previously created".
              " by the same component\n");
        foreach my $override (@compoverrides)
        {
            $self->{logger}->Print(">> $override\n");
        }
    }
    if ($#sdkoverrides >= 0)
    {
        $self->{logger}->Error("In Component: $componentName\n" .
              $message .
              "\nattempts to override the following files previously created".
              "$message by another component");
        foreach my $override (@sdkoverrides)
        {
            $self->{logger}->Print(">> $override\n");
        }
    }
    return;

    # ResolveSource() : inner sub
    sub ResolveSource
    {
        my $rootPath = shift;
        my $source = shift;
        my $recursive = shift;
        if ( !$recursive )
        {

            # golb the files
            use File::DosGlob 'glob';
            if ( ! file_name_is_absolute($source))
            {
                chdir $rootPath;
            }
            @sources = glob $source;
        } else
        {

            # search deep in the tree, use find
            @sources = FindSource( $rootPath, $source);
        }
        return @sources;

        # FindSource() : inner sub
        sub FindSource
        {
            our $searchPath = shift; # component rootpath
            $searchPath =~ s/\\/\//g;
            our $searchPattern = shift; # source attribute, could be abs or rel to rootpath
            our $searchPatternAbsolute = file_name_is_absolute($searchPattern)
              ? 1
              : 0;
            our $fullstring = $searchPatternAbsolute
              ? $searchPattern
              : catfile($searchPath,$searchPattern);
            $fullstring =~ /([^\*\?]*[\\\/])(.*$)/;
            our $tmpsearchPath = $1;
            our $tmpsearchPattern = $2;
            $tmpsearchPattern =~ s/\*/\.\*/g;  # escape *
            $fullstring =~ s/\*/\.\*/g; # escape *
            $fullstring =~ s/\\/\//g;
            our @list= ();
            return @list if (!-d $tmpsearchPath);

            # here is the way the search is done
            # having component root = d:\foo\bar\
            # source to look for is src\*.c
            # we call find as find(\&filter,"d:\foo\bar\src\")
            # we need to push src\ to the list if there was any match
            my $index = $#list;
            use File::Find;
            find(\&Filter, $tmpsearchPath);
            if ($#list != $index)
            {
                $searchPattern =~ /([^\*\?]*[\\\/])(.*$)/;
                my @dirs = $1 ? split /[\\\/]/,$1 : ();
                my $diridx = scalar @dirs;
                while ($diridx > 0)
                {
                    push @list, join('\\',@dirs[0..--$diridx]);
                }
            }
            return @list;

            # Filter() : the File::Find wanted sub
            sub Filter
            {
                my $file = canonpath($File::Find::name);
                $file =~ s/\\/\//g;
                return unless $file =~ /^$fullstring$/i;
                if ($searchPatternAbsolute)
                {
                    push @list, $file;
                } else
                {
                    $file =~ s/^\Q$searchPath\E[\\\/]*//i;
                    push @list, $file;
                }
            } # end of sub d
        } # end of sub findSource
    }
}

#private
sub ConvertFileSpecToRegExp
{
    my $excludes = shift;
    my @regexp = ();
    foreach my $exclude (@{$excludes})
    {
        my $slash = '[\\\\\\/]';
        my $notslash = '[^\\\\\\/]';
        $exclude =~ s![\\\/]!$slash!g; # turn / or \ into [\\\/]
        $exclude =~ s!\*!$notslash\*!g; # turn * into [^\\\/]*
        $exclude =~ s!([\|\(\)\$\.\+\?])!\\$1!g;  # esacpe |()$.+?
        push @regexp,$exclude;
    }
    return \@regexp;
}

#private
sub MatchRegExp()
{
    my $file = shift;
    my $excludes = shift;
    foreach my $exclude (@{$excludes})
    {
        if($file =~ $exclude)
        {
            return 1;
        }
    }
    return 0;
}
1;

__END__


sub new create an SdkFile object
sub SdkFileOrder
sub ValidateFile
sub SdkFileSource
sub SdkFileDestination
sub SdkFileRecursive
sub GetSdkFileSources
