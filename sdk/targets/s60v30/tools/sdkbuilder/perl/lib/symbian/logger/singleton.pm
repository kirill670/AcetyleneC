# Symbian/Logger/Singleton.pm
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::Logger::Singleton;
use base qw(Symbian::Logger);
use strict;

my $self;

sub new 
{
     my $class = shift;
     if (! $self)
     {
      $self = bless {}, $class;
      $self = bless $self->SUPER::new(@_) , $class;
     }
     return $self;
}

sub Debug
{
  my $self = shift;
  my $newval = shift;
  $self->{debug} = $newval if defined $newval;
  return defined $self->{debug} ? $self->{debug} : 0;
}

1;
