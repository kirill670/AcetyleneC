# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
# Symbian::Logger

package Symbian::Logger;

use Time::localtime;
use IO::File;

# Symbian::Logger new(scalar aLogFile)
# Object constructor
sub new($)
	{
	my $proto = shift;
	my ($aLogFile) = @_;

	my $class = ref($proto) || $proto;

	my $self = {};
	bless($self, $class);

	if (defined $aLogFile)
		{
		$self->SetLog($aLogFile);
		}

	# Support for scanlog and Die() control.
	$self->{iPhaseErrorCount} = 0;
	$self->{iPhase} = undef;

	$self->{iTicking} = 0; # Not currently printing ticks

	return $self;
	}

# boolean SetLog(scalar aFilename)
sub SetLog($)
	{
	my $self = shift;
	my ($aLogFile) = @_;

	if (defined($self->{iLOGFILE}))
		{
		$self->{iLOGFILE}->close();
		# This forces any subsequent error message to go to stdout
		$self->{iLOGFILE} = undef;
		}
	
	if (-e $aLogFile)
		{
		if (-e $aLogFile."~")
			{
			if (!unlink $aLogFile."~")
				{
				$self->Error("Couldn't delete backup log file\n");
				return 0;
				}
			}

		if (system("copy $aLogFile $aLogFile~ > nul 2>&1"))
			{
			$self->Error("Couldn't back-up existing log file\n");
			return 0;
			}
		}
		
	$self->{iLOGFILE}=new IO::File("> $aLogFile");

	if (defined($self->{iLOGFILE}))
		{
		return 1;
		}
	else
		{
		$self->Error("Couldn't open logfile $aLogFile\n");
		return 0;
		}
	}

# void Print(scalar aLogLine)
sub Print($)
	{
	my $self = shift;
	my ($aLogLine) = @_;

	my $logfile = $self->{iLOGFILE};

	if ($aLogLine !~ /\n$/)
		{
		$aLogLine = $aLogLine."\n";
		}

	if (!defined($logfile))
		{
		$self->UnTick();
		print $aLogLine;
		}
	else
		{
		print $logfile $aLogLine;
		}
	}

# void Die(scalar aError)
sub Die($)
	{
	my $self = shift;
	my ($aError) = @_;

	my $logfile = $self->{iLOGFILE};

	if ($aError !~ /\n$/)
		{
		$aError = $aError."\n";
		}

	if (!defined($logfile))
		{
		$self->UnTick();
		die $aError;
		}
	else
		{
		print $logfile $aError;
		die "ERROR: System experienced a fatal error; check the log file.\n";
		}
	}

# void Status(scalar aMessage)
sub Status($)
	{
	my $self = shift;
	my ($aMessage) = @_;

	if (defined($self->{iLOGFILE}))
		{
		print STDOUT $aMessage."\n"; # Only display status (to STDOUT) if everything else is going to the logfile
		}
	}

# void Tick() - print a dot to screen, if not logging
sub Tick()
	{
	my $self = shift;
	
	if (defined($self->{iLOGFILE}))
		{
		print STDOUT ".";
		$self->{iTicking} = 1;
		}
	}

# void UnTick() - if previously printing ticks (see Tick()), output a newline
sub UnTick()
	{
	my $self = shift;

	if ((defined($self->{iLOGFILE})) && ($self->{iTicking}))
		{
		print STDOUT "\n";
		$self->{iTicking} = 0;
		}
	}

# Returns the number of errors encountered in a phase
sub GetErrorCount()
	{
	my $self = shift;
	return $self->{iPhaseErrorCount};
	}
	
###########################################
# Handling Commands, Phases and components.
###########################################

# void Command(scalar aMessage)
# Prints out a command in scanlog format to the log file or stdout
sub Command($)
	{
	my $self = shift;
	my ($aCommand) = @_;
	my $message = "===-------------------------------------------------\n=== $aCommand\n===-------------------------------------------------\n";
	$self->Print($message);
	}

# void PhaseStart(scalar aPhaseName)
# If a current phase is active then this is closed, if when doing so a
# non-zero error count is returned by PhaseEnd() then Die is called. This
# is regarded as a logic error as the stage runner should normally call PhaseEnd()
# itself and decide what to do about any errors that occured in that phase.
sub PhaseStart($)
	{
	my $self = shift;
	my $phase = shift;
	if (defined $self->{iPhase})
		{
		my $numErrs = $self->PhaseEnd();
		# If there are errors returned by PhaseEnd then Die()
		if ($numErrs != 0)
			{
			$self->Die("Fatal logic error detected, CConfig::PhaseStart() called without PhaseEnd() when phase has $numErrs errors.\n");
			}
		}
	$self->Command($phase);
	$self->{iPhase} = $phase;
	my $localTime = ctime();
	my $message = "=== $self->{iPhase} started $localTime\n";
	$self->Print($message);
	$self->{iPhaseErrorCount} = 0;
	}
  
# scalar PhaseEnd(void)
# Closes the current phase and returns a count of the number of errors encountered.
# This will die if a PhaseStart() has not been declared.
sub PhaseEnd()
	{
	my $self = shift;
	my $localTime = ctime();
	if (defined $self->{iPhase})
		{
		my $message = "=== $self->{iPhase} finished $localTime\n";
		$self->Print($message);
		}
	else
		{
		$self->Die("Error: CConfig::PhaseEnd() called without corresponding PhaseStart()\n");
		}
	$self->{iPhase} = undef;
	return $self->{iPhaseErrorCount};
	}

# void Component(scalar aComponent)
# Prints out a component for this phase in scanlog format to the log file or stdout
sub Component($)
	{
	my $self = shift;
	my ($aComponent) = @_;
	if (!defined $self->{iPhase})
		{
		$self->Die("Logger: Undefined phase for component \"$aComponent\"\n");
		}
	else
		{
		my $message = "=== $self->{iPhase} == $aComponent";
		$self->Print($message);
		}
	}

###############################
# Handling errors and warnings.
###############################

# void Error(scalar aMessage)
# Writes an error message to the logfile (if defined) or stdout
# and will increment the error count for this phase.
sub Error($)
	{
	my $self = shift;
	my ($aMessage) = @_;
	$self->{iPhaseErrorCount} += 1;
	my $message = "ERROR: $aMessage";
	$self->Print($message);
	}

# void Warning(scalar aMessage)
# Writes an warning message to the logfile (if defined) or stdout
sub Warning($)
	{
	my $self = shift;
	my ($aMessage) = @_;
	my $message = "WARNING: $aMessage";
	$self->Print($message);
	}

sub DESTROY
	{
	my $self = shift;

	my $localTime = ctime();
	if (defined $self->{iPhase})
		{
		my $message = "=== $self->{iPhase} finished $localTime\n";
		$self->Print($message);
		}
	if (defined($self->{iLOGFILE}))
		{
		$self->{iLOGFILE}->close();
		$self->{iLOGFILE} = undef;
		}
	}

1;
