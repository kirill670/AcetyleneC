# Symbian/SDK/FilterTool/ConfigValidator.pm
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::SDK::FilterTool::ConfigValidator;
use strict;

use Carp;
use File::Spec;

sub new {
    my $class = shift;
    my $self = bless {}, $class;
    return $self;
}

# for readability reasons we are delegating validation of directives
# to individual methods. since we will dynamically generate the name
# of the method to call in each case, an AUTOLOAD method is provided
# to catch any calls which go astray (_should_ never happen!).
#
# validation methods are named according to the convention validate_
# followed by the lower-case directive name with underscores instead
# of spaces, e.g. validate_work_area, validate_epoc_root etc.

sub AUTOLOAD {
    my $self = shift;
    no strict qw(vars);
    if ($AUTOLOAD =~ /^.*::validate_([^:]+)$/) { # validation attempt?
        my $directive = $1;
        $directive =~ s/_/ /g;
        warn "WARNING: Can't validate configuration directive: $directive\n";
        return 1; # i.e. not a failure
    }
    carp "$AUTOLOAD not implemented";
    return undef;
}

sub DESTROY {}

# public.

sub Error {
    my $self = shift;
    return $self->{error};
}

sub ValidateConfig {

    my $self = shift;
    my $config = shift;

    if (!UNIVERSAL::isa($config, 'Symbian::Config::Basic')) {
        $self->{error} = 'not a Symbian::Config::Basic object';
        return 0;
    }

    $self->{config} = $config; # cached so interdependencies can be checked

    my @directives = (
        { optional => 0, name => 'input area' },
        { optional => 0, name => 'work area' },
        { optional => 0, name => 'sdk name' },
        { optional => 0, name => 'sdk id' },
        { optional => 0, name => 'publisher name' },
        { optional => 0, name => 'doxygen output area' },
        { optional => 0, name => 'config names' },
        { optional => 1, name => 'documentation root' },
        { optional => 1, name => 'examples root' },
        { optional => 0, name => 'filter log' },
        { optional => 1, name => 'epoc root' },
        { optional => 1, name => 'tools root' },
        { optional => 0, name => 'source root' },
        { optional => 1, name => 'include root' },
        { optional => 1, name => 'sdk description' },
        { optional => 1, name => 'sdk license' },
        { optional => 1, name => 'publisher logo' },
        { optional => 1, name => 'publisher web site' },
        { optional => 1, name => 'build number' },
        { optional => 1, name => 'cpp flags' },
        { optional => 1, name => 'cpp include' },
        { optional => 1, name => 'manifest file' },
        { optional => 1, name => 'readme file' },
        { optional => 1, name => 'cpp macros' },
        { optional => 1, name => 'user rules file' },
	{ optional => 0, name => 'ui source path' },
	{ optional => 1, name => 'ipr filter ui code' },
	{ optional => 1, name => 'ui source root' },
	{ optional => 1, name => 'ui configs' },
	{ optional => 0, name => 'ui components' },
    );

    my @unknown = ();

    # find unknown directives in the config file
    for my $directive ($config->GetNames()) {
        if (!grep lc($_->{name}) eq lc($directive), @directives) {
            push @unknown, $directive;
        }
    }

    if (@unknown) {
        local $" = ', ';
        $self->{error} = "unknown directive(s) found: @unknown";
        return 0;
    }

    # find and validate known directives
    for my $directive (@directives) {

        # get the value from the config file
        my $value = $config->Get($directive->{name});

        # no value - skip validation if optional, fail if required
        if (!defined $value) {
            next if $directive->{optional};
            $self->{error} = "required directive not set: $directive->{name}";
            return 0;
        }

        # dynamically generate validation method name
        my $method = join('_', 'validate', split(' ', lc($directive->{name})));

        # return a failure if validation fails
        return 0 if !$self->$method($value);
    }

    return 1; # all configuration directives validated
}

# private.

sub is_absolute_or_input_area_subdir {

    my $self = shift;
    my $name = shift;
    my $value = shift;

    if (!$self->is_absolute_path($value)) { # must be relative to input area

        # path must be inside the input area (so no .. dirs)
        if ($value =~ m!\\\.\.\\!) {
            $self->{error} = "$name may not contain .. directories";
            return 0;
        }

        # validate input area so we can access the cached absolute path
        my $input = $self->{config}->Get('input area');
        return 0 if !$self->validate_input_area($input);

        # $self->{productroot} contains the absolute product root
        $value = File::Spec->catdir($self->{cache}{inputarea}, $value);
    }

    # must be an existing directory
    if (!-d $value) {
        $self->{error} = "$name directory does not exist: $value";
        return 0;
    }

    # store for possible later cross-ref
    $self->{cache}{$name} = $value;

    return 1;
}

sub is_absolute_file_or_input_area_subfile {

    my $self = shift;
    my $name = shift;
    my $value = shift;

    if (!$self->is_absolute_path($value)) { # must be relative to input area

        # path must be inside the input area (so no .. dirs)
        if ($value =~ m!\\\.\.\\!) {
            $self->{error} = "$name may not contain .. directories";
            return 0;
        }

        # validate input area so we can access the cached absolute path
        my $input = $self->{config}->Get('input area');
        return 0 if !$self->validate_input_area($input);

        # $self->{productroot} contains the absolute product root
        $value = File::Spec->catfile($self->{cache}{inputarea}, $value);
    }

    # must be an existing file
    if (!-f $value) {
        $self->{error} = "$name does not exist: $value";
        return 0;
    }

    # store for possible later cross-ref
    $self->{cache}{$name} = $value;

    return 1;
}

sub is_absolute_path {
    my $self = shift;
    my $path = shift;
    return $path =~ m!^[a-z]:[\\/]!i;
}

sub is_subdirectory_of {
    my $self = shift;
    my $test = shift;
    my $path = shift;
    return $path =~ /^\Q$test\E/i;
}

sub is_valid_filename {
    my $self = shift;
    my $name = shift;
    return $name !~ m![\\/:*?"<>|]!;
}

# validation routines

# sub validate_example {
#
#     my $self = shift;
#     my $value = shift;
#
#     # ok represents some test
#     if (!ok($value)) {
#         $self->{error} = 'Example is not OK';
#         return 0;
#     }
#
#     # ...any other tests required
#
#     return 1; # valid
# }

sub validate_input_area {

    my $self = shift;
    my $value = shift;

    return 1 if defined $self->{cache}{inputarea}; # already checked

    # must be an absolute path
    if (!$self->is_absolute_path($value)) {
        $self->{error} = 'Input Area must be an absolute path';
        return 0;
    }

    # must be an existing directory
    if (!-d $value) {
        $self->{error} = "Input Area directory does not exist: $value";
        return 0;
    }

    $self->{cache}{inputarea} = $value; # cached so interdependencies can be checked

    return 1; # valid
}

sub validate_work_area {

    my $self = shift;
    my $value = shift;

    # must be absolute - others depend on it
    if (!$self->is_absolute_path($value)) {
        $self->{error} = 'Work Area must be an absolute path';
        return 0;
    }

    # must be an existing directory
    if (!-d $value) {
        $self->{error} = 'Work Area directory does not exist';
        return 0;
    }

    return 1; # valid
}

sub validate_sdk_name {

    my $self = shift;
    my $value = shift;

    # this is going to be used as a directory name
    if (!$self->is_valid_filename($value)) {
        $self->{error} = 'SDK Name contains invalid characters \\/:*?"<>|]';
        return 0;
    }

    return 1; # valid
}

sub validate_sdk_id {

    my $self = shift;
    my $value = shift;

    # this is going to be used as a directory name
    if (!$self->is_valid_filename($value)) {
        $self->{error} = 'SDK ID contains invalid characters \\/:*?"<>|]';
        return 0;
    }

    return 1; # valid
}

sub validate_publisher_name {

    my $self = shift;
    my $value = shift;

    # must be a string of length > 0
    if (!length($value)) {
        $self->{error} = 'Publisher Name must be specified';
        return 0;
    }

    return 1; # valid
}

sub validate_doxygen_output_area {

    my $self = shift;
    my $value = shift;

    # must be an existing directory
    if (!-d $value) {
        $self->{error} = 'Doxygen Output Area directory must exist';
        return 0;
    }

    return 1; # valid
}

sub validate_config_names {

    my $self = shift;
    my $value = shift;

    # config names are dirs under the doxygen output area
    my $dox = $self->{config}->Get('doxygen output area');
    return 0 if !$self->validate_doxygen_output_area($dox);

    # convert value to a list of values
    my @values = ref($value) ? @$value : ($value);

    # iterate through values
    for my $value (@values) {

        for (qw(doxygen stats)) { # make expected paths

            my $path = File::Spec->catdir($dox, $_, $value);

            if (!-d $path) {
                $self->{error} = "Config Names entry '$value' directory not found: $path";
                return 0;
            }
        }
    }

    return 1; # valid
}

sub validate_filter_log {

    my $self = shift;
    my $value = shift;

    # must be an absolute path
    if (!$self->is_absolute_path($value)) {
        $self->{error} = 'Filter Log must be an absolute path';
        return 0;
    }

    # This class is for validation _only_!
    # If the requirement arises to move an existing log aside the
    # renaming code must be put _elsewhere_ and this method modified
    # so that it does not throw the following error (that the log
    # file already exists).
    # Again, this class is for validation _only_!

    # file cannot already exist
    if (-f $value) {
        $self->{error} = 'Filter Log file already exists';
        return 0;
    }

    # the directory must be writable, permissions ok etc.
    if (!open(LOG, ">$value")) {
        $self->{error} = "Filter Log file could not be created: $!";
        return 0;
    }

    # tidy up - we didn't really want to create the log here
    # it will be created at the proper time if execution gets
    # that far - only created here to check for errors.
    close(LOG);
    unlink($value);

    return 1; # valid
}

sub validate_epoc_root {

    my $self = shift;
    my $value = shift;

    return 0 if !$self->is_absolute_or_input_area_subdir('Epoc Root' => $value);

    my $release = File::Spec->catdir($self->{cache}{'Epoc Root'}, 'epoc32', 'release');

    if (!-d $release) {
        $self->{error} = "Can't find release directory under Epoc Root at $release";
        return 0;
    }

    return 1;
}

sub validate_tools_root {

    my $self = shift;
    my $value = shift;

    return $self->is_absolute_or_input_area_subdir('Tools Root' => $value);
}

sub validate_source_root {

    my $self = shift;
    my $value = shift;

    return $self->is_absolute_or_input_area_subdir('Source Root' => $value);
}

sub validate_include_root {

    my $self = shift;
    my $value = shift;

    return $self->is_absolute_or_input_area_subdir('Include Root' => $value);
}

sub validate_examples_root {

    my $self = shift;
    my $value = shift;

    return $self->is_absolute_or_input_area_subdir('Examples Root' => $value);
}

sub validate_documentation_root {

    my $self = shift;
    my $value = shift;

    return $self->is_absolute_or_input_area_subdir('Documentation Root' => $value);
}

sub validate_sdk_description {

    my $self = shift;
    my $value = shift;

    # must be a string of length > 0
    if (!length($value)) {
        $self->{error} = 'SDK Description must be specified';
        return 0;
    }

    return 1; # valid
}

sub validate_sdk_license {

    my $self = shift;
    my $value = shift;

    # must be an existing file
    return $self->is_absolute_file_or_input_area_subfile('SDK License', $value);
}

sub validate_user_rules_file {

    my $self = shift;
    my $value = shift;

    # must be an existing file
    return $self->is_absolute_file_or_input_area_subfile('User rules file', $value);
}

sub validate_publisher_logo {

    my $self = shift;
    my $value = shift;

    # must be an existing file
    return $self->is_absolute_file_or_input_area_subfile('Publisher logo', $value);
}

sub validate_publisher_website {

    my $self = shift;
    my $value = shift;

    # make sure this looks like a valid url - regex courtesy of URI.pm perldoc
    if ($value !~ m|^(?:([^:/?#]+):)?(?://([^/?#]*))?([^?#]*)(?:\?([^#]*))?(?:#(.*))?|) {
        $self->{error} = 'Publisher Website must be a valid URL';
        return 0;
    }

    return 1; # valid
}

sub validate_build_number {

    my $self = shift;
    my $value = shift;

    # must be a string of length > 0
    if (!length($value)) {
        $self->{error} = 'Build Number must be specified';
        return 0;
    }

    return 1; # valid
}

sub validate_cpp_flags {

    my $self = shift;
    my $value = shift;

    # no sensible checks - any value (even no value) is ok

    return 1; # valid
}

sub validate_cpp_include {

    my $self = shift;
    my $value = shift;

    # convert value to a list of values
    my @values = ref($value) ? @$value : ($value);

    for my $value (@values) {

        # if it's absolute check it exists
        if ($self->is_absolute_path($value) and !-d $value) {
            $self->{error} = "CPP Include path does not exist: $value";
            return 0;
        }

        # otherwise it's relative to the file to be processed so we can't check
    }

    return 1; # valid
}

sub validate_manifest_file {

    my $self = shift;
    my $value = shift;

    # this is going to be used as a file name
    if (!$self->is_valid_filename($value)) {
        $self->{error} = 'Manifest filename contains invalid characters \\/:*?"<>|]';
        return 0;
    }

    return 1; # valid
}

sub validate_readme_file {

    my $self = shift;
    my $value = shift;

    # must be an existing file
    return is_absolute_file_or_input_area_subfile("Readme file", $value);
}

sub validate_ui_source_path {
    my $self = shift;
    my $value = shift;

    return $self->is_absolute_or_input_area_subdir('UI Source Path' => $value);
}

sub validate_ipr_filter_ui_code {
    my $self = shift;
    my $value = shift;

    if ($value =~ /\(true|yes\)/i) {
        if ( (!defined($self->{config}->Get('ui source root')))
          && (!defined($self->{config}->Get('ui configs')))
        ) {
            $self->{error} = "If setting 'IPR Filter UI Code', both 'UI Source Root' and 'UI Configs' must also be set";
            return 0;
        }
    }
    return 1;
}

sub validate_ui_source_root {
    my $self = shift;
    my $value = shift;

    return $self->is_absolute_or_input_area_subdir('UI Source Root' => $value);
}

sub validate_ui_configs {
    my $self = shift;
    my $value = shift;

    # config names are dirs under the doxygen output area
    my $dox = $self->{config}->Get('doxygen output area');
    return 0 if !$self->validate_doxygen_output_area($dox);

    # convert value to a list of values
    my @values = ref($value) ? @$value : ($value);

    # iterate through values
    for my $value (@values) {

        for (qw(doxygen stats)) { # make expected paths

            my $path = File::Spec->catdir($dox, $_, $value);

            if (!-d $path) {
                $self->{error} = "Config Names entry '$value' directory not found: $path";
                return 0;
            }
        }
    }

    return 1; # valid
}

sub validate_ui_components {
    my $self = shift;
    my $value = shift;

    foreach my $match (ref($value) ? @$value : ($value)) {
        if ($match eq "") {
            $self->{error} = "A UI Components entry may not be blank";
            return 0;
            }
        }
    return 1; # Valid
}

sub validate_cpp_macros {
    my $self = shift;
    my $value = shift;

    foreach my $match (ref($value) ? @$value : ($value)) {
        if ($match eq "") {
            $self->{error} = "A CPP Macros entry may not be blank";
            return 0;
            }
        }
    return 1; # Valid
}

1;

__END__

=pod

=head1 NAME

Symbian::SDK::FilterTool::ConfigValidator - Early checking of config settings

=head1 SYNOPSIS

  use Symbian::Config::Basic;
  use Symbian::SDK::FilterTool::ConfigValidator;

  my $config = new Symbian::Config::Basic('/path/to/config.file');
  my $validator = new Symbian::SDK::FilterTool::ConfigValidator();

  if (!$validator->ValidateConfig($config)) {
      die $validator->Error();
  }

=head1 DESCRIPTION

This class is designed to be called early in the running of the filter tool in order to detect user mistakes in their config file before too much processing had occurred. It collates various tests in one place.

In order to extend this class, more private methods may be added named validate_config_name, where 'config_name' is replaced by the name of the configuration directive to be tested, with spaced replaced by underscores. The directive name must also be added to the hash in the ValidateConfig method.

Should an entry made in the ValidateConfig hash not match with a method implemented, a warning will be generated.

=head1 METHODS

=head2 new()

B<Returns>: C<Symbian::SDK::FilterTool::ConfigValidator> - the created object

B<Parameters>: None

Simple constructor.

=cut

=head2 Error()

B<Returns>: String - The last error generated by a validate step

B<Parameters>: None

=head2 ValidateConfig(Symbian::Config::Basic $config)

B<Returns>: C<Undef> if validation fails, true otherwise

B<Parameters> C<$config> - the Symbian::Config::Basic object to validate

If undef is returned, use C<Error()> to return the actual error

=head1 SEE ALSO

L<Symbian::Config::Basic>

=head1 COPYRIGHT

Copyright (c) 2005 Symbian Software Ltd. All rights reserved.

=cut
