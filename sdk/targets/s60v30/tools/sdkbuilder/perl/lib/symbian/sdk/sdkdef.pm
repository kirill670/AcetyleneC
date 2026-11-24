#!perl
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
# SdkDef - Module to read/write SDK Manifest files
#
package Symbian::SDK::SdkDef;
use strict;
use Symbian::SDK::SdkContent;
use Symbian::SDK::Utils;
use Cwd 'abs_path';
use XML::Simple;
use File::Basename;
use File::Spec::Functions;
use Symbian::Logger::Singleton;
use File::Path;

sub New
{
    my $pkg = shift;
    my $self = {};
    my $sdk_def_file = shift;
    my $productarea = shift;
    $self->{logger} = Symbian::Logger::Singleton->new();
    bless $self, $pkg;
    if (!defined $sdk_def_file)
    {
        return $self;
    }
    $self->{logger}->Die("Manifest file $sdk_def_file does not exist") if (! -e $sdk_def_file);

    $self->{SdkDefFile} = $sdk_def_file;
    
    $self->{logger}->Print("Reading manifest file $sdk_def_file\n") if $self->{logger}->Debug();
    #create an sdk object from the provided XML file
    my $xs1 = XML::Simple->new();
    $self->{xml} = eval{ $xs1->XMLin($sdk_def_file , forcecontent => 1, suppressempty => 1, keyattr => [], forcearray => ["contentDefinition", "section", "group"]) };
    if( $@ )
    {
        $@ =~ s/at (.:|)\/.*?$//s;               # remove module line number
        $self->{logger}->Error("ERROR in '$sdk_def_file':\n$@");
    }

    # Extract the root paths information
    if (! ref $self->{xml}->{paths}->{root})
    {
        $self->{rootpath} = $self->{xml}->{paths}->{root};
    } else
    {
        foreach my $root (@{$self->{xml}->{paths}->{root}})
        {
            if (ref $root)
            {
                if (exists $self->{roots}->{lc($root->{id})})
                {
                    $self->{logger}->Error("\nERROR in '$sdk_def_file': root with id of '".$root->{id}."' is duplicated in 'paths' element");
                }
                else
                {
                    $self->{roots}->{lc($root->{id})} = $root->{path};
                }
            }
            else
            {
                if (exists $self->{rootpath})
                {
                    $self->{logger}->Error("Internal error: 'paths' element appears to have two 'root' attributes");
                }
                else
                {
                    $self->{rootpath} = $root;
                }
            }
        }
    }
    if ( defined $productarea )
    {
        $self->{rootpath} = $productarea;
    }    
    $self->Validate(1);
    return $self;
}

sub Validate
{
    my $self = shift;
    my $force = shift;
    if (!exists $self->{valid} || $force)
    {
        $self->{logger}->Print("Validating manifest content\n") if $self->{logger}->Debug();
        $self->{valid} = 0;
        $self->{logger}->Die("SDK Id not defined.") if(! $self->SDKId());
        $self->{logger}->Die("SDK Name not defined.") if(! $self->SDKName());
        my $productarea = $self->{rootpath};
        $self->{logger}->Die("Product Area not defined.") if(!$productarea );
        if (!file_name_is_absolute(canonpath($productarea)))
        {
             $productarea = catdir(dirname($self->{SdkDefFile}),$productarea);
        }
        $self->{logger}->Die("Product Area $productarea does not exists.") if (!-d $productarea);
        $self->{logger}->Die("Publisher Name not defined.") if(! $self->SDKPublisherName());
        my $file = $self->SDKLicenseName();
        $file = Symbian::SDK::Utils::GetFullPath($self->SDKRootPath(),$file) if $file;
        if ($file && ! -f Symbian::SDK::Utils::GetFullPath($self->SDKRootPath(),$file))
        {
            $self->{logger}->Die("License file $file does not exist.");
        }
        $file = $self->SDKReadmeName();
        $file = Symbian::SDK::Utils::GetFullPath($self->SDKRootPath(),$file) if $file;
        if ($file && ! -f Symbian::SDK::Utils::GetFullPath($self->SDKRootPath(),$file))
        {
            $self->{logger}->Die("Readme file $file does not exist.");
        }        
        $self->{logger}->Die("EPOCROOT not defined.") if !$self->SDKEpocRoot();
        Symbian::SDK::Utils::ValidateRoot("EPOCROOT",
            $self->SDKEpocRoot(),
            $self->SDKRootPath());
        $self->{logger}->Die("TOOLSROOT not defined.") if !$self->SDKToolsRoot();
        Symbian::SDK::Utils::ValidateRoot("TOOLSROOT",
            $self->SDKToolsRoot(),
            $self->SDKRootPath());
        $self->{logger}->Die("SOURCEROOT not defined.") if !$self->SDKSourceRoot();
        Symbian::SDK::Utils::ValidateRoot("SOURCEROOT",
            $self->SDKSourceRoot(),
            $self->SDKRootPath());
        $self->{logger}->Die("INCLUDEROOT not defined.") if !$self->SDKIncludeRoot();
        Symbian::SDK::Utils::ValidateRoot("INCLUDEROOT",
            $self->SDKIncludeRoot(),
            $self->SDKRootPath());
        $self->{valid} = 1;
    }
    return $self->{valid};
}

# Write() : Write out the manifest file
#
# Parameters:
#   $sdk_def_file - the filename to use
# Returns:
sub Write($)
{
    my $self = shift;
    my ($sdk_def_file) = @_;
    $self->{logger}->Print("writing manifest file $sdk_def_file\n") if $self->{logger}->Debug();
    my $manifest_location = dirname($sdk_def_file);
    mkpath($manifest_location) if !-d $manifest_location;
    open(FILE, ">$sdk_def_file") or $self->{logger}->Die("Couldn't write to $sdk_def_file: $!");
    print FILE "<?xml version=\"1.0\" encoding=\"windows-1250\"?>\n";
    print FILE "<sdk id=\"".$self->SDKId()."\" name=\"".$self->SDKName()."\">\n";
    print FILE "  <description>".$self->SDKDescription()."</description>\n" if $self->SDKDescription();

    print FILE "  <publisher ";
    print FILE "link=\"".$self->SDKPublisherWebSite()."\" " if $self->SDKPublisherWebSite();
    print FILE ">".$self->SDKPublisherName()."</publisher>\n";

    if (! scalar $self->SDKCreationDetails())
    {
        my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday) =gmtime();
        $year += 1900;
        $mon++;
        my $login = getlogin;
        $self->SDKCreationDetails("$year-$mon-$mday", "$hour:$min:$sec", $login);
    }

    my ($date,$time,$user) = $self->SDKCreationDetails();
    print FILE "  <created date=\"".$date."\" time=\"".$time."\" user=\"".$user."\"/>\n";
    print FILE "  <paths root=\"".$self->{rootpath}. "\">\n";
    foreach my $root (keys %{$self->{roots}})
    {
        print FILE "	   <root id=\"$root\" path=\"".$self->{roots}->{$root}."\"/>\n";
    }
    print FILE "   <license file=\"". $self->SDKLicenseName() . "\"/>\n" if $self->SDKLicenseName();
    print FILE "   <readme file=\"". $self->SDKReadmeName() . "\"/>\n" if $self->SDKReadmeName();
    my @cdfs = $self->GetContentDefinitionFiles();
    foreach my $cdf (@cdfs)
    {
        print FILE "   <contentDefinition file=\"" . $cdf . "\"/>\n";
    }
    print FILE "  </paths>\n";
    my $sections =  $self->GetSections();
    foreach my $section (@$sections)
    {
        print FILE "   <section name=\"" . $section->{name} . "\">\n";
        print FILE "     <build>" . $section->{build} . "</build>\n";
        print FILE "     <cppflags>" . $section->{cppflags} . "</cppflags>\n";
        print FILE "   </section>\n";
    }
    my $insts = $self->SDKInstalled();

    if (scalar @$insts)
    {
        print FILE " <installed>\n";

        foreach my $installed (@$insts)
        {
            print FILE "   <group>".$installed."</group>\n";
        }
        print FILE " </installed>\n";
    }
    print FILE "</sdk>\n";
    close FILE;
    return 1;
}

# SDKRoot() : Generic root getter/setter
#
# Parameters:
#   $rootid - name of root to get/set
#   $newval - optional new value, if setting (not including the SDK root path)
# Returns:
#   The (new) value of the specified root
sub SDKRoot()
{
    my $self = shift;
    my ($rootid, $newval) = @_;
    $self->{roots}->{lc($rootid)} = lc(canonpath($newval)) if defined $newval;
    my $retval = $self->{roots}->{lc($rootid)};
    $retval =~ /^\s*(.*?)([\\\/]?)\s*$/;
    return lc(canonpath($1).$2);
}

# Convenience root getter
#
# Parameters:
#   root id string: epocroot,srcroot,toolsroot,includeroot
#   keepdrive: 1 : keepdrive letter is exists in the path, 0: don't
# Returns:
#   epocroot if absolute or rootpath.epocroot if not without drive letter
sub SDKEnvRoot
{
    my $self = shift;
    my $rootid = shift;
    my $keepdrive = shift;
    my $aRoot = "";
    $aRoot = canonpath($self->{roots}->{lc($rootid)}) if exists $self->{roots}->{lc($rootid)};
    $aRoot =~ s/^[\\\/]//;
    if (file_name_is_absolute($aRoot))
    {
        $aRoot =~ s/[a-zA-Z]:// if (!$keepdrive);
        return $aRoot;
    } else
    {
        my $root = $self->SDKRootPath();
        $root =~ s/^[a-zA-Z]:// if (!$keepdrive);
        return lc(canonpath(catfile($root,$aRoot)));
    }
}

# SDKRootPath() : SDK root path getter/setter
#
# Parameters:
#   $newval - optional new value, if setting
# Returns:
#   The (new) value
sub SDKRootPath
{
    my $self = shift;
    my $newval = shift;
    $self->{rootpath} = lc(canonpath($newval)) if defined $newval;
    my $productarea = $self->{rootpath};
    if (!file_name_is_absolute(canonpath($productarea)))
    {
        $productarea = catdir(dirname($self->{SdkDefFile}),$productarea);
    }
    return Win32::GetShortPathName(lc(canonpath($productarea)));
}

# Specific root getter/setters
#
# Parameters:
#   $newval - optional new value, if setting (not including the SDK root path)
# Returns:
#   The (new) value, including the SDK root path
sub SDKEpocRoot
{
    my $self = shift;
    my $newval = shift;
    return $self->SDKRoot('epocroot', $newval);
}

sub SDKToolsRoot
{
    my $self = shift;
    my $newval = shift;
    return $self->SDKRoot('toolsroot', $newval);
}

sub SDKSourceRoot
{
    my $self = shift;
    my $newval = shift;
    return $self->SDKRoot('srcroot', $newval);
}

sub SDKIncludeRoot
{
    my $self = shift;
    my $newval = shift;
    return $self->SDKRoot('includeroot', $newval);
}

sub SDKDocumentationRoot
{
    my $self = shift;
    my $newval = shift;
    return $self->SDKRoot('documentationroot', $newval);
}

sub SDKExamplesRoot
{
    my $self = shift;
    my $newval = shift;
    return $self->SDKRoot('examplesroot', $newval);
}

# Direct XML getter/setters
#
# Parameters:
#   $newval - optional new value, if setting
# Returns:
#   The (new) value
sub SDKId
{
    my $self = shift;
    my $newval = shift;
    $self->{xml}->{id} = $newval if defined $newval;
    return $self->{xml}->{id};
}

sub SDKDescription
{
    my $self = shift;
    my $newval = shift;
    $self->{xml}->{description} = $newval if defined $newval;
    return $self->{xml}->{description};
}

sub SDKName
{
    my $self = shift;
    my $newval = shift;
    $self->{xml}->{name} = $newval if defined $newval;
    return $self->{xml}->{name};
}

sub SDKPublisherName
{
    my $self = shift;
    my $newval = shift;
    $self->{xml}->{publisher}->{content} = $newval if defined $newval;
    return $self->{xml}->{publisher}->{content};
}

sub SDKPublisherWebSite
{
    my $self = shift;
    my $newval = shift;
    $self->{xml}->{publisher}->{link} = $newval if defined $newval;
    return $self->{xml}->{publisher}->{link};
}

sub SDKPublisherLogo
{
    my $self = shift;
    my $newval = shift;
    $self->{xml}->{publisher}->{logo} = $newval if defined $newval;
    return $self->{xml}->{publisher}->{logo};
}

sub SDKInstallerLogo
{
    my $self = shift;
    my $newval = shift;
    $self->{xml}->{publisher}->{installerlogo} = $newval if defined $newval;
    return $self->{xml}->{publisher}->{installerlogo};
}

sub SDKLicenseName
{
    my $self = shift;
    my $newval = shift;
    $self->{xml}->{paths}->{license}->{file} = $newval if defined $newval;
    return $self->{xml}->{paths}->{license}->{file};
}

sub SDKReadmeName
{
    my $self = shift;
    my $newval = shift;
    $self->{xml}->{paths}->{readme}->{file} = $newval if defined $newval;
    return $self->{xml}->{paths}->{readme}->{file};
}

sub SDKReadme
{
    my $self = shift;
    my $newval = shift;
    $self->{xml}->{readme}->{file} = $newval if defined $newval;
    return $self->{xml}->{readme}->{file};
}

sub SDKWebLocation
{
    my $self = shift;
    my $newval = shift;
    $self->{xml}->{publisher}->{link} = $newval if defined $newval;
    return $self->{xml}->{publisher}->{link};
}

sub SDKCppFlags
{
    my $self = shift;
    my $newval = shift;

    # TODO: What if there are multiple sections? Need to select the right one
    $self->{xml}->{section}->{cppflags} = $newval if defined $newval;
    return $self->{xml}->{section}->{cppflags};
}

sub SDKBuild
{
    my $self = shift;
    my $newval = shift;
    $self->{xml}->{section}->{build} = $newval if defined $newval;
    return $self->{xml}->{section}->{build};
}

# GetSDKSections : Lists the available sections by name
#
# Parameters:
#   None
# Returns:
#   The list of section names
sub GetSDKSections
{
    my $self = shift;

    return $self->{xml}->{section};
}

# AddSDKSection : Adds a section
#
# Parameters:
#   $name - Name of section to add
#   \%args - Arguments of specified section
# Returns:
#   1 if successfully added, 0 otherwise (section with that name already exists)
sub AddSDKSection($$)
{
    my $self = shift;
    my ($name, $args) = @_;

    my $section = $self->GetSection($name);
    if (defined $section)
    {
        return 0; # Name already exists
    }
    else
    {
        my $hash = {%$args}; # Copy the hash
        $hash->{name} = $name;

        push @{$self->{xml}->{section}}, $hash;
        return 1;
    }
}

# RemoveSDKSection : Removes a named section
#
# Parameters:
#   $name - Name of section to delete
# Returns:
#   1 if a section was deleted, 0 otherwise
sub RemoveSDKSection
{
    my $self = shift;
    my ($name) = @_;

    my $deleted = 0;

# Note if there are more than one index of the specified name, both will be deleted
    for (my $index = 0; $index < scalar(@{$self->{xml}->{section}}); $index++)
    {
        if (lc($self->{xml}->{section}->[$index]->{name}) eq lc($name))
        {
            delete $self->{xml}->{section}->[$index]->{name};
            $deleted = 1;
        }
    }

    return $deleted;
}

# private GetSection : Returns a reference to the named section hash from the XML
#
# Parameters:
#   $name - Section name
# Returns
#   $hashref - Section hash. Undef if section not found
sub GetSection
{
    my $self = shift;
    my ($name) = @_;

# Note if there are more than one index of the specified name, only the first will be returned.
    foreach my $section (@{$self->{xml}->{section}})
    {
        if (lc($section->{name}) eq lc($name))
        {
            return $section;
        }
    }

    return undef;
}

sub GetSections
{
    my $self = shift;
    return exists $self->{xml}->{section}
      ? $self->{xml}->{section}
      : [];
}

# SDKContentDefinition() : Get/set the SDKContent object
#
# Parameters:
#   $newval - optional new value, if setting
# Returns:
#   The (new) SDKContent object
sub SDKContentDefinition
{
    my $self = shift;
    my $newval = shift;

    if (defined $newval)
    {

        # Set
        $self->{sourceDefinition} = $newval;

        # Update the xml
        $self->SetContentDefinitionFiles($newval->GetContentDefinitionFiles())
    }
    elsif (!defined $self->{sourceDefinition})
    {

        # If it was a get and the SDKContent object hasn't been generated
        $self->UpdateSourceDef();
    }

    return $self->{sourceDefinition};
}

# SDKContentDefinitionFiles() : Get/set the list of Content Definition files
#
# Parameters:
#   \@newval - optional list of files, if setting. Causes regeneration of the SDKContent object
# Returns:
#   The (new) list of Content Definition files
sub GetContentDefinitionFiles
{
    my $self = shift;
    my @newvals = @_;
    if (scalar @newvals)
    {
        $self->SetContentDefinitionFiles(@newvals);
        $self->UpdateSourceDef();
    }
    return map($_->{file},@{$self->{xml}->{paths}->{contentDefinition}});
}

# private SetContentDefinitionFiles
#
# Parameters:
#   \@newval - list of files. Does not cause regeneration of the SDKContent obejct
# Returns:
#   None
sub SetContentDefinitionFiles
{
    my $self = shift;
    my @newvals = @_;

    $self->{xml}->{paths}->{contentDefinition} = [];
    foreach my $newval (@newvals)
    {
        push @{$self->{xml}->{paths}->{contentDefinition}}, {file=>lc(canonpath($newval))};
    }
}

# private UpdateSourceDef() - Regenerate the SDKContent object, based on the list of Content Definition files
#
# Parameters:
#   None
# Returns:
#   None
sub UpdateSourceDef
{
    my $self = shift;

    my $cidx = -1;
    my $cdf;
    my $cdo;
    $cdo = Symbian::SDK::SdkContent->New();
    my $cdpath;
    my $gorder = 0;
    while (defined ($self->{xml}->{paths}->{contentDefinition}->[++$cidx]))
    {
        $cdpath = canonpath($self->{xml}->{paths}->{contentDefinition}->[$cidx]->{file});
        $cdpath = Symbian::SDK::Utils::GetFullPath($self->SDKRootPath(),$cdpath);
        $cdf = Symbian::SDK::SdkContent->New($cdpath, $self->SDKRootPath(), ++$gorder); # get sdk content
        $cdf->ValidateContent();
        foreach my $gkey (sort {$a <=> $b} keys (%{$cdf->{group}}))
        {
            $cdo->AddSDKComponent($cdf->{group}->{$gkey});
            $gorder = $gkey;
        }
    }
    $self->{sourceDefinition} = $cdo;
}

# SDKInstalled() : Get/set the list of Installed Components
#
# Parameters:
#   \@newval - optional list of components, if setting.
# Returns:
#   The (new) list of Installed Components
sub SDKInstalled
{
    my $self = shift;
    my @newvals = @_;
    $self->{xml}->{installed}->{group} = [] if scalar @newvals;
    my $idx =0;
    foreach my $newval (@newvals)
    {

        #push @{$self->{xml}->{installed}->{group}}, $newval;
        $self->{xml}->{installed}->{group}->[$idx++] = $newval;
    }
    return exists $self->{xml}->{installed}->{group}
      ? $self->{xml}->{installed}->{group}
      : [];
}

# SDKCreationDetails() : Get/set the creation date, time and user
#
# Parameters:
#   $date
#   $time
#   $user
# Returns:
#   (date,time,user)
sub SDKCreationDetails
{
    my $self = shift;
    my ($date,$time, $user) = @_;
    $self->{xml}->{created}->{date} = $date if defined $date;
    $self->{xml}->{created}->{time} = $time if defined $time;
    $self->{xml}->{created}->{user} = $user if defined $user;
    return ($self->{xml}->{created}->{date},$self->{xml}->{created}->{time},$self->{xml}->{created}->{user});
}

# SDKManifest() getter/setters
#
# Parameters:
#   $newval - optional new value, if setting
# Returns:
#   The (new) value
sub SDKManifest
{
    my $self = shift;
    my $newval = shift;
    $self->{SdkDefFile} = $newval if defined $newval;
    return $self->{SdkDefFile};
}

1;

__END__

sub new 
convert a manifest file into a SdkDef object.
excpects a manifest xml file.



=============

getters/setters

sub SDKId
sub SDKEpocRoot
sub SDKRootPath
sub SDKToolsRoot
sub SDKSourceRoot
sub SDKIncludeRoot
sub SDKExamplesRoot
sub SDKDocumentationRoot
sub SDKDescription
sub SDKContentDefinition
sub SDKName
sub SDKPublisherName
sub SDKPublisherWebSite
sub SDKPublisherLogo
sub SDKLicenseName
sub SDKReadmeName
sub SDKReadme? not needed
sub SDKWebLocation
sub SDKCppFlags
sub SDKSectionBuild
sub SDKSectionName
