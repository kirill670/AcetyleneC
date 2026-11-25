#
# Copyright (c) 2001 Symbian Ltd.  All rights reserved.
#
# This script is only meant to be used to launch buildpkg
# from the console.
#

use FindBin;
use lib $FindBin::Bin."/perllib","$FindBin::Bin";
use Cwd;
use findjava;

#put the location of the java.exe into the path
$ENV{PATH} = getJavaBin() . ";" . $ENV{PATH}; 

$command = "java -jar \"".$FindBin::Bin."/pkgmgr/buildpkg.jar\" ";

foreach my $arg (@ARGV)
{
    	#check if the arg ends with a "\" if so quote it so that it becomes "\\"
	$arg =~ s/\\$/\\\\/;

	$command.="\"".$arg."\" ";		
}

my $exitValue = system ($command);

#covert the java error code
$exitValue = $exitValue / 256;

exit($exitValue);
