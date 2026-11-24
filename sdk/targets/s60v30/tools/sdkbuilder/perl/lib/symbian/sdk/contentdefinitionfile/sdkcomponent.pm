#!perl
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
# SdkComponent - Module to create/update SdkComponent object that correspond to a group xml element
#

package Symbian::SDK::ContentDefinitionFile::SdkComponent;
use strict;
use Symbian::Logger::Singleton;
use Cwd;
use File::Spec::Functions;
use Cwd 'abs_path';

# New() : create a new SdkComponent object
#
# Parameters:
#   - order
#   - description
#   - hidden
#   - required
#   - default
#   - rootpath
# Returns:
#   - the newly created SdkComponent object reference
sub New
{
    my $pkg = shift;
    my ($order,$description,$hidden,$required,$default,$rootpath) = @_;

    my $self = {};
    $self->{logger} = Symbian::Logger::Singleton->new();
    $self->{order} = $order if defined $order;
    $self->{description} = $description if defined $description;
    $self->{hidden} = $hidden if defined $hidden;
    $self->{required} = $required if defined $required;
    $self->{default} = $default if defined $default;
    $self->{rootpath} = $rootpath if defined $rootpath;

    bless $self, $pkg;
    return $self;
}

# RootPath() : set/get rootpath
#
# Parameters:
#   - rootpath
# Returns:
#   - rootpath
sub RootPath
{
    my $self = shift;
    my $newval = shift;
    $self->{rootpath}->{path} = lc(canonpath($newval)) if defined $newval;
    return $self->{rootpath}->{path};
}

# validateComponent() : validates the content of the current object
#
# Parameters:
#   - force : force re-validation
# Returns:
#   - valid: 1 valid - 0 invalid
sub ValidateComponent
{
    my $self = shift;
    my $force = shift;
    if (!exists $self->{valid} || $force)
    {

        # component not validated yet or forced to validate again
        $self->{valid} = 1;
        my $rootPath = canonpath($self->RootPath());
        if (!$rootPath || ! -d $rootPath)
        {

            # rootpath invalid
            $self->{valid} = 0;
            $self->{logger}->Error($self->SdkComponentName() ." : invalid rootpath $rootPath");
        } else
        {
            foreach my $file (values %{$self->GetComponentFiles()})
            {

                # good place to validate all file elements
                if (!$file->ValidateFile($self->RootPath()))
                {
                    my $source = $file->SdkFileSource();
                    my $destination = $file->SdkFileDestination();
                    my $message = $self->SdkComponentName();
                    $message .= " : <source=" . $source if defined $source;
                    $message .= " destination=".$destination if defined $destination;
                    $message .= " recursive=".$file->SdkFileRecursive().
                      "> invalid, therefore file tag ignored\n\n";
                    $self->{logger}->Error($message);
                }
            }
            my $metadata = $self->SdkComponentMetaData();
            $metadata->Validate($rootPath) if $metadata;
        }
    }
    return $self->{valid};
}

# addComponentFile() : add a SdkFile object to the existing list
#
# Parameters:
#   - a SdkFile object
# Returns:
#   - 1 success - 0 fail
sub AddComponentFile
{
    my $self = shift;
    my $file = shift;
    if (exists $self->{files}->{$file->SdkFileOrder()})
    {
        $self->{logger}->Error("Another file element exists with order ". $file->SdkFileOrder(). ".");
        return 0;
    }
    $self->{files}->{$file->SdkFileOrder()} = $file;
    return 1;
}

# getComponentFiles() : get the existing SdkFile objects
#
# Parameters:
#   - none
# Returns:
#   - hash containing the existing SdkFile objects keyed on their orders
sub GetComponentFiles
{
    my $self = shift;
    return exists $self->{files} ? $self->{files} : {};
}

# getComponentSources() : expands and resolve all SdkFile objects and build a hash of destination -> source
#
# Parameters:
#   - componentsources : a reference to an empty hash
#   - sdksource : a refrence to a sdksources hash
# Returns:
#   - none
sub GetComponentSources
{
    my $self = shift;
    my $componentSources = shift;
    my $sdksources = shift;
    my $sourcefiles = $self->GetComponentFiles();
    my $sources;
    foreach my $fkey (sort {$a <=> $b} keys %{$sourcefiles})
    {

        # SdkFile object
        if (! $sourcefiles->{$fkey}->ValidateFile($self->RootPath()))
        {
            next;
        }

        #get the list of source files
        $sourcefiles->{$fkey}->GetSdkFileSources($self->RootPath()
            ,$self->SdkComponentName()
            ,\$componentSources
            ,\$sdksources);
    } #end of SdkFile
}

# SdkComponentOrder() : set/get order
#
# Parameters:
#   - order
# Returns:
#   - order
sub SdkComponentOrder
{
    my $self = shift;
    my $newval = shift;
    $self->{order} = $newval if defined $newval;
    return $self->{order};
}

# SdkComponentDescription() : set/get description
#
# Parameters:
#   - description
# Returns:
#   - description
sub SdkComponentDescription
{
    my $self = shift;
    my $newval = shift;
    $self->{description} = $newval if defined $newval;
    return $self->{description};
}

# SdkComponentName() : set/get name
#
# Parameters:
#   - name
# Returns:
#   - name
sub SdkComponentName
{
    my $self = shift;
    my $newval = shift;
    $self->{name} = $newval if defined $newval;
    return $self->{name};
}

# SdkComponentRequired() : set/get required
#
# Parameters:
#   - required : true/false
# Returns:
#   - required : 1/0
sub SdkComponentRequired
{
    my $self = shift;
    my $newval = shift;
    $self->{required} = $newval if defined $newval;
    if (exists ($self->{required}) && $self->{required} =~ /true/i)
    {
        return 1;
    } else
    {
        return 0;
    }
}

# SdkComponentHidden() : set/get hidden
#
# Parameters:
#   - hidden : true/false
# Returns:
#   - hidden : 1/0
sub SdkComponentHidden
{
    my $self = shift;
    my $newval = shift;
    $self->{hidden} = $newval if defined $newval;
    if (exists ($self->{hidden}) && $self->{hidden} =~ /true/i)
    {
        return 1;
    } else
    {
        return 0;
    }
}

# SdkComponentDefault() : set/get default
#
# Parameters:
#   - default : true/false
# Returns:
#   - default 1/0
sub SdkComponentDefault
{
    my $self = shift;
    my $newval = shift;
    $self->{default} = $newval if defined $newval;
    if (exists ($self->{default}) && $self->{default} =~ /true/i)
    {
        return 1;
    } else
    {
        return 0;
    }
}

# SdkComponentMetaData() : set/get SdkMetaData object
#
# Parameters:
#   - a SdkMetaData object
# Returns:
#   - SdkMetaData object reference
sub SdkComponentMetaData
{
    my $self = shift;
    my $newval = shift;
    $self->{metadata} = $newval if defined $newval;
    return $self->{metadata};
}

1;

__END__

sub New
sub ValidateComponent
sub RootPath
sub AddComponentFile
sub GetComponentFiles
sub GetComponentSources
sub SdkComponentDescription
sub SdkComponentOrder
sub SdkComponentName
sub SdkComponentRequired
sub SdkComponentHidden
sub SdkComponentDefault
sub SdkComponentMetaData
