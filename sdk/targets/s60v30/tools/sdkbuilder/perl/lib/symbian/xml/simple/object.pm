# Object.pm
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::XML::Simple::Object;
use strict;

# public.

use constant XMLOBJECT_HASH => 'HASH';
use constant XMLOBJECT_ARRAY => 'ARRAY';

sub xml_object_type {
    return XMLOBJECT_HASH; # default
}

1;

=pod

=head1 NAME

Symbian::XML::Simple::Object - Objects that can be written as XML.

=head1 SYNOPSIS

 package Foo::HashTypeObject;
 use base qw(Symbian::XML::Simple::Object);

 sub new { bless {} }

 # or for array-type objects:

 package Foo::ArrayTypeObject;
 use base qw(Symbian::XML::Simple::Object);

 sub new { bless [] }
 sub xml_object_type { Symbian::XML::Simple::Object::XMLOBJECT_ARRAY }

=head1 DESCRIPTION

XML::Simple can't dump your object as XML because it doesn't know what kind of
reference was blessed to make that object. The solution is to tack on an
interface so the object can be queried and the underlying reference type
determined.

This is the interface. Make your class a subclass of this package and you will
inherit the default xml_object_type method which identifies your object as a
blessed hashref. If your object is really a blessed arrayref then override this
method with your own as in the example above.

That's it - now your method can be written as XML using Symbian::XML::Simple.

=head1 METHODS

=head2 xml_object_type()

This method returns one of two values defined here as constants. They are:
XMLOBJECT_HASH and XMLOBJECT_ARRAY. They are not exported so you must qualify
them fully (as in the examples above) with this package name, e.g.
Symbian::XML::Simple::Object::XMLOBJECT_HASH.

N.B. You need only define your own xml_object_type method if your object is not
a blessed hashref.

=head1 SEE ALSO

L<Symbian::XML::Simple>

L<XML::Simple>

=head1 COPYRIGHT

Copyright (c) 2005 Symbian Software Ltd. All rights reserved.

=cut
