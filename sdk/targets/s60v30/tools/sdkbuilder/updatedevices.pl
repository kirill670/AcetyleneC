#!perl
use strict;
use File::Basename;
use Getopt::Long;
use XML::Simple;
use File::Spec;
use File::Path;

my ($file,$name,$id,$kitroot,$epocroot,$toolsroot,$add,$remove);

eval {GetOptions ('add', \$add, 'remove', \$remove, 'device=s', \$file, 'name=s', \$name, 'id=s', \$id, 'kitroot=s', \$kitroot, 'epocroot=s', \$epocroot, 'toolsroot=s', \$toolsroot)};

die "Error: Device must have a name" if (!$name);
die "Error: Device must have an id" if (!$id);
die "Error: Device must have a 'kitroot'" if (!$kitroot && $add);
die "Error: Device must have a EPOCROOT" if (!$epocroot && $add);

prependRoots();

my $xml = readDevices();

my $default;

if ($add)
{
    if(exists $xml->{devices}->{device})
    {
        $default = 'no';
    }else
    {
        $default = 'yes';
    }
    addDevice($xml,$default);
} elsif($remove)
{
    if (defined $file && -f $file)
    {
        removeDevice($xml);
    }elsif (!defined $file)
    {
        print "Devices file not specified.\n";
    }else
    {
        print "Devices file $file does not exist.\n";
    }
}else
{
    print "No device operation specified!\n";
}

sub readDevices
{
    my $xml;
    if (defined $file && -f $file)
    {
        $xml = XMLin(
            $file,
            forcearray => [ qw(device epocroot toolsroot) ],
            keeproot   => 1,
            keyattr    => []);

    } else
    {
        $xml->{devices} = {version => '1.0'};
    }
    return $xml;
}

sub addDevice
{
    $epocroot =~ s/\.\\?$//; # clean end of epoc root if ending with . or .\
    $epocroot =~ s/(.*)([^\\])$/$1$2\\/; # epocroot must end with \
    my $xml = shift;
    my $default = shift;
    my $exists = 0;

    foreach my $device (@{$xml->{devices}->{device}})
    {
        if ($device->{name} eq $name && $device->{id} eq $id)
        {
            print "Can not add device. Device already exist.\n";
            $exists =1;
            last;
        }
    }
    if (!$exists)
    {
        my $newdevice = {
            name          => "$name",
            id            => "$id",
            default       => "$default",
            epocroot      => [ $epocroot ],
            userdeletable => "yes",
          };
        $newdevice->{toolsroot} = [ $toolsroot ] if ($toolsroot);
        push @{$xml->{devices}{device}}, $newdevice;
        writeDevices($xml);
    }
    return;
}

sub removeDevice
{
    my $xml = shift;
    my $exists = 0;

    my $newdevices = [];
    foreach my $device (@{$xml->{devices}->{device}})
    {
        if ($device->{name} eq $name && $device->{id})
        {
            $exists =1;
        } else
        {
            push @$newdevices, $device;
        }
    }
    if ($exists)
    {
        $xml->{devices}{device} = $newdevices;
        writeDevices($xml);
    }else
    {
        print "Can not remove device. Device does not exist."
    }
    return;
}

sub writeDevices
{
    my $xml = shift;
    print XMLout($xml, keeproot => 1, outputfile => $file, xmldecl => '<?xml version="1.0"?>');
}

sub prependRoots
{
    die "Error: Kit root must not contain '..' directories\n" if $kitroot =~ /(^|\\\/)\.\.($|\\\/)/;
    die "Error: EPOCROOT must not contain '..' directories\n" if $epocroot =~ /(^|\\\/)\.\.($|\\\/)/;
    $epocroot = File::Spec->catdir($kitroot, $epocroot);
    $epocroot = File::Spec->canonpath($epocroot);
    if (defined $toolsroot)
    {
    	die "Error: Tools root must not contain '..' directories\n" if $toolsroot =~ /(^|\\\/)\.\.($|\\\/)/;
        $toolsroot = File::Spec->catdir($kitroot, $toolsroot);
        $toolsroot = File::Spec->canonpath($toolsroot);
    }    
}
