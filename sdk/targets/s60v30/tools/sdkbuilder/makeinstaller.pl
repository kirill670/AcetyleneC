#!perl
use strict;
use FindBin;
use lib "$FindBin::Bin\\perl\\lib\\";
use Symbian::SDK::makeNsis;
use Symbian::Logger::Singleton;
use Cwd 'abs_path';
use Cwd;
use File::Path;
use File::Basename;
use File::Spec::Functions;
use Getopt::Long;

my ($manifest,$logfile,$nsis_param,$user_code,
    $outputdir,$debug,$no_installer_log, $productarea, $custom, $help, $no_devices);
eval {GetOptions ('manifest=s', \$manifest, 'product=s', \$productarea, 'outputdir=s', \$outputdir,
        'log=s', \$logfile, 'nsis_parameters=s', \$nsis_param, 'custom_installer=s', \$custom,
        'debug', \$debug, 'no_installer_log', \$no_installer_log, 'not_device', \$no_devices, 'help', \$help)};
my $logger = Symbian::Logger::Singleton->new();
$logger->SetLog($logfile) if $logfile;
$logger->Debug(1) if $debug;

my $message = "Usage: makeInstaller\n";
$message .= "\t\[-product=path\]\t\t\t: path to the product area\n";
$message .= "\t-manifest=manifest file \t: path and name of the manifest file\n";
$message .= "\t-outputdir=path\t\t\t: path to a directory where the installer is genrated (created if new)\n";
$message .= "\t\[-log=logfile\]\t\t\t: name of the log file\n";
$message .= "\t\[-nsis_parameters=\"Nsis parameters\"\]\t: nsis parameters passed to the compiler e.g. \"/XSetCompressor lzma\"\n";
$message .= "\t\[-custom_installer=\"nsis installer customisation headerfile\"\]\t: Installer customisation file\n";
$message .= "\t\[-debug\]\t\t\t: debug flag\n";
$message .= "\t\[-no_installer_log\]\t\t: installer will not prompt the user for saving the installation log\n";
$message .= "\t\[-not_device\]\t\t\t: don't add this installation to devices\n";
$message .= "\t\[-help]\t\t\t\t: display this output\n";
$logger->Die($message) if (!$manifest || !$outputdir || $help);

#check various paths are valid
# if log file name is not absolute then it's relative to outputdir
if (!-e $outputdir || !-d $outputdir)
{
    mkpath($outputdir);
}
$outputdir= abs_path($outputdir);
$logfile = Symbian::SDK::Utils::GetFullPath($outputdir,$logfile) if ($logfile);

#$manifest = catdir(abs_path(dirname($manifest)),basename($manifest));
#if productarea dir defined and manifest path is not absolute then it's relative to productarea
if ($productarea)
{
    $manifest = Symbian::SDK::Utils::GetFullPath($productarea,$manifest);
}

$logger->Die("Manifest file $manifest does not exist.") if ! -f $manifest;

$message = "Running makeNsis with arguments \n";
$message .= "\t\tProduct area: $productarea\n" if $productarea;
$message .= "\t\tmanifest: $manifest\n";
$message .= "\t\toutputdir: $outputdir\n";
$message .= "\t\tnsis param: $nsis_param\n" if $nsis_param;
$message .= "\t\tno_installer: $no_installer_log\n" if $no_installer_log;
$message .= "\t\tcustom code: $custom\n" if $custom;
$message .= "\t\tdebug: $debug\n" if $debug;
$message .= "\t\tdevices: $no_devices\n" if $no_devices;

$logger->Print($message) if $logger->Debug;

Symbian::SDK::makeNsis->Run($productarea,$manifest,$outputdir,$nsis_param,$no_installer_log,$custom, $no_devices);
