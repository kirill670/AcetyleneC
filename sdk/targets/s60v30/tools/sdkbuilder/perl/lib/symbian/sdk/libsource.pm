# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.

=pod

=head1 NAME

Symbian::SDK::LibSource - Identifies source for import libraries and other build files

=head1 SYNOPSIS

  use Symbian::SDK::LibSource;

  my $sourcefinder = new Symbian::SDK::LibSource();

  $sourcefinder->LoadTargetData("\\doxygen_area\\doxygen\\GT_9.0");

  my @sources = @{$sourcefinder->GetLibSource("epoc32\\release\\winscw\\udeb\\fred.lib")};

=head1 DESCRIPTION

This class uses doxygen stats to identify firstly the import libraries, then the source files for them and .pdb files. Firstly, 

=cut

package Symbian::SDK::LibSource;
use strict;

use File::Basename;
use File::Find;
use Symbian::SDK::DoxyBldInf;

# known prefixes used with the VariantTarget(name,ext) macros
my @variant_prefixes = qw(
    _assabet_
    _Sassabet_
    _h2_
    _SH2_
    _integrator_cm1136_
    _integrator_cm920_
    _Sintegrator_
    _lubbock_
    _Slubbock_
    _template_
);

# make regular expression for later substitution
my $variant_prefixes = '(?:'.join('|', @variant_prefixes).'|)?';

sub new {
    my $class = shift;
    my $self = bless {
        dox => Symbian::SDK::DoxyBldInf->new()
    }, $class;
    return $self;
}

sub LoadTargetData {

    my $self = shift;
    my $dir = shift;

    my $parsed = 0;

    my $wanted = sub {
        return if $File::Find::name !~ /doxyBuildInf\.xml$/i;
	$parsed = 1;
        $self->{dox}->parse($File::Find::name);
    };

    find($wanted, $dir);

    return $parsed;
}

sub GetLibSource {

    my $self = shift;
    my $lib = shift;

    my $target = $self->FindTarget($lib);

    return unless defined $target;

    return $self->{dox}->GetTargetSource($target);
}

sub FindTarget {

    my $self = shift;
    my $lib = shift;

    my $targets = $self->{dox}->GetTargets();

    # try exact match - we live in hope :)

    my $filename = basename($lib);

    (my $base = $filename) =~ s/\.(?:lib|pdb)$//i; # use this if exact match fails

    my @matches = grep $targets->{$_}{name} =~ /^\Q$filename\E$/i, keys %$targets;

    while (!@matches) {

        # search for corresponding dll/exe/whatever

        last if @matches = grep $targets->{$_}{name} =~ /^\Q$base\E(\.\w+)?$/i, keys %$targets;

        # check variant targets

        (my $varbase = $base) =~ s/^$variant_prefixes/VariantTarget(/;

        last if @matches = grep $targets->{$_}{name} =~ /^\Q$varbase\E,/i, keys %$targets;

        # swap rvct version number (2_1 to 2_2 and vice versa)

        (my $otherrvct = $base) =~ s/(?<=2_)([12])/$1 == 1 ? 2 : 1/e;

        last if @matches = grep $targets->{$_}{name} =~ /^\Q$otherrvct\E(\.\w+)$/, keys %$targets;

        # try all matches again less the {000a0000} (?, if any)

        next if $base =~ s/\{[0-9a-f]{8}\}//;

        # try all matches again less the 2_x (RVCT version, if any)

        next if $base =~ s/2_[12]//;

        last; # if no matches
    }

    return $matches[0];
}

1;
