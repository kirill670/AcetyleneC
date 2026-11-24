#!perl -w
#
# M a n u a l D i a l o g
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

# Very simple Tk interaction class. Creates a window containing a number
# of buttons with a return value (which is some kind of scalar). When one
# of the buttons is hit the associated scalar is returned.
use strict;
package ManualDialog;
use Tk;

sub new
{
    my $arg = shift;
    my $class = ref($arg) || $arg;
    my $title = shift;
    my $instrc = shift;
    my $ques = shift;
    my $resp = shift;
    return undef unless(ref($resp));

    my $self = {
                title => $title,
               instrc => $instrc,
                 ques => $ques,
                 resp => $resp, # An array of arrays.
            
           background => "LightBlue1", 
                   rc => undef,
           };
    bless $self, $class;
    return $self;
}

#
# Display the window and wait for the user to hit one of the buttons based
# on the prompts displayed (instructions and a question). Return the scalar
# associated with the button pressed.
# Note that it is possible to call this method more than once, but there's
# probably no point (in other words this method does not trigger destruction
# of the object).
#
sub Display
{
    my $self = shift;
    return undef unless(ref($self));
    # Create the main window, give it a minimum size.
    my $mw = MainWindow->new(-background => $self->Background());
    
    # We create three or four frames running horizontally..
    if(defined($self->{title}))
    {
        $mw->title($self->{title});
        my $frm0 = $mw->Frame( -background => $self->Background());
        $frm0->pack(-side=>'top', -fill => 'x', pady=>5, padx=>5);
        my $lbl0 = $frm0->Label(-background => $self->Background(),
                                -text => $self->{title})->pack(-anchor => 'w');
    }

    # Three more..
    my $frm1 = $mw->Frame(-relief => 'raised',
                     -borderwidth => 1,
                      -background => $self->Background());
    $frm1->pack(-side=>'top', -fill => 'x', pady=>5, padx=>5);
    my $frm2 = $mw->Frame(-relief => 'raised',
                     -borderwidth => 1,
                      -background => $self->Background());
    $frm2->pack( -fill => 'x', pady=>5, padx=>5);
    my $frm3 = $mw->Frame(-relief => 'raised',
                     -borderwidth => 1,
                      -background => $self->Background());
    $frm3->pack( -fill => 'x', -side=>'bottom', pady=>5, padx=>5);

    # The text is static, so we'll just use labels.
    for my $instrc (@{$self->{instrc}})
    {
        my $lbl1 = $frm1->Label(-background => $self->Background(),
                                -text => $instrc)->pack(-anchor => 'w');
    }
    for my $ques (@{$self->{ques}})
    {
        my $lbl2 = $frm2->Label(-background => $self->Background(),
                                -text => $ques)->pack(-anchor => 'w');
    }

    # In this frame we have an unknown number of buttons.
    for my $rsp (@{$self->{resp}})
    {
        # rsp is an array of two elements. The first is the name of the
        # button, the second the value the return for this response.
        my $bn = $rsp->[0];
        my $rc = $rsp->[1];

        my $button = $frm3->Button(-text => $bn, 
                             -background => $self->Background,
                        -command => sub { $self->{rc} = $rc; $mw->DESTROY; });
        $button->pack(-fill => 'x' );
    }
    MainLoop();
    return $self->{rc};
}

# Change the background colour for the displayed window before displaying it.
sub Background
{
    my $self = shift;
    return undef unless(ref($self));
    my $back = shift;
    $self->{background} = $back if(defined($back));
    return($self->{background});
}

1;
