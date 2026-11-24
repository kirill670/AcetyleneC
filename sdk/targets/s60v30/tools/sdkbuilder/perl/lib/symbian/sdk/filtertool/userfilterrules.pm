#!perl
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
#  Symbian::SDK::FilterTool::UserFilterRules - Module to create/update UserFilterRules objects
#

package Symbian::SDK::FilterTool::UserFilterRules;
use Symbian::SDK::FilterTool::UserRule;
use strict;
use XML::Simple;
use Symbian::Logger::Singleton;


# new() : creates a new Symbian::SDK::FilterTool::UserFilterRules object
#
# Parameters:
#   none
# Returns:
#   A reference to the new object (empty)
sub new
{
    my $pkg = shift;
    my $self = {};
    $self->{logger} = Symbian::Logger::Singleton->new();
    bless $self, $pkg;
    return $self;
}

# ReadUserRules() : read the user rules from an xml file and fills the current object
#
# Parameters:
#   $user_rules_file - (String) path and name of the user rules xml file
# Returns:
#   none
sub ReadUserRules
{
    my $self = shift;
    my $user_rules_file = shift;
    my $definedGroups = shift;
    if (!defined $user_rules_file)
    {
        $self->{logger}->Error("User rules file not defined");
    } elsif( !-e $user_rules_file)
    {
        $self->{logger}->Error("User rules file $user_rules_file does not exist");
    }

    my $xs1 = XML::Simple->new();
    $self->{xml} = eval{ $xs1->XMLin($user_rules_file , suppressempty => 1, keyattr => [], forcearray => ["filter"]) };
    if( $@ )
    {
        $@ =~ s/at (.:|)\/.*?$//s;               # remove module line number
        $self->{logger}->Die("ERROR: In '$user_rules_file':\n$@");
    }
    my $xmlrules = exists $self->{xml}->{filter} ? $self->{xml}->{filter} : [];

    foreach my $xmlrule (@$xmlrules)
    {
        my $rule = Symbian::SDK::FilterTool::UserRule->new(
            $xmlrule->{operation},
            $xmlrule->{location},
            $xmlrule->{groups},
            $xmlrule->{recursive},
            $xmlrule->{content});
        if ($rule->Validate($definedGroups))
        {
            $self->AddRule($rule);
        }
    }
    delete $self->{xml};
}

# AddRule() : Adds a rule the current object
#
# Parameters:
#   a user rule - Symbian::SDK::FilterTool::UserRule object
# Returns:
#   none
sub AddRule
{
    my $self = shift;
    push @{$self->{rules}},shift;
}

# GetRules() : get all rules in the object
#
# Parameters:
#   none
# Returns:
#   Array of Symbian::SDK::FilterTool::UserRule objects
sub GetRules
{
    my $self = shift;
    return exists $self->{rules} ? $self->{rules} : [];
}

# GetGroupRules() : get all rules in the object for a specific group
#
# Parameters:
#   $group - (String) group name
# Returns:
#   Array of Symbian::SDK::FilterTool::UserRule objects
sub GetGroupRules
{
    my $self = shift;
    my $group = shift;
    my @rules = ();
    foreach my $rule (@{$self->GetRules()})
    {
        my $userGroups = $rule->Groups();
        if (scalar @{$userGroups} == 0)
        {
            push @rules,$rule;
        } else {
            foreach my $userGroup (@{$userGroups})
            {
                if (lc($userGroup) eq lc($group))
                {
                    push @rules,$rule;
                    next;
                }
            }
        }
    }
    return \@rules;
}

# GetGroupFilters() : Convenience api: get group rules as regexps
#
# Parameters:
#   $group - (String) group name
# Returns:
#   Array of strings
# example turn rule /epoc32/release  *.doc to
# 1- [\\\/]epoc32[\\\/]release[\\\/].*[^\\\/]*\.doc$ if recursive
# 2- [\\\/]epoc32[\\\/]release[\\\/][^\\\/]*\.doc$ if not recursive
sub GetGroupFilters
{
    my $self = shift;
    my $group = shift;
    my $rules = $self->GetGroupRules($group);
    my @filters = ();
    foreach my $rule (@{$rules})
    {
        my $location = $rule->FilesLocation();
        my $slash = '[\\\\\\/]';
        my $notslash = '[^\\\\\\/]';
        $location = $location."\\" if ($location !~ /[\/\\]$/); # add \ if not present
        $location =~ s![\\\/]!$slash!g; # turn / or \ into [\\\/]
        $location =~ s!\*!$notslash\*!g; # turn * into [^\\\/]*
        my $extension = $rule->FilesExtension();
        $extension =~ s!\*!$notslash\*!g; # turn * into [^\\\/]*
        $extension =~ s!([\|\(\)\$\.\+\?])!\\$1!g; # esacpe |()$.+?
        my $file_regexp;
        if ($rule->Recursive())
        {
            $file_regexp = $location . "($notslash*$slash)*" . $extension . "\$"; # find
        } else
        {
            $file_regexp = $location . $extension . "\$"; # glob
        }
        if (lc($rule->Operation()) eq 'include')
        {
            push @filters,{$file_regexp=>'include'};
        } else
        {
            push @filters,{$file_regexp=>'exclude'};
        }
    }
    return \@filters;
}

1;
