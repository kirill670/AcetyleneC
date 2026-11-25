# Copyright (c) 2003 Symbian Ltd. All rights reserved  use strict;
package GenXml;
  
  use strict;
  
  use FindBin;
  use lib "$FindBin::Bin/lib";
  use XML::DOM;
  use XML::DOM::ValParser;
  
  # produces the "Use of uninitialized value in concatenation (.) or string" warning
  use XML::XQL;
  use XML::XQL::DOM;
  
  # Used by debug prints
  #my $count;
  
my ($gHiResTimer) = 0; #Flag - true (1) if HiRes Timer module available
my ($gLogFileH); # Log file handle
my ($gValidateFailed) = 0; # Flag true (1) if the XML validation has failed
my ($gValidate) = 0; # Flag true (1) if to do XML validation only

# Check if HiRes Timer is available
if (eval "require Time::HiRes;") {
  $gHiResTimer = 1;
} else {
  print "Cannot load HiResTimer Module, install the Perl module Time-HiRes for more accurate timing data\n";
}

sub Start
{
  my ($iXmlSource, $iDataOutput, $iLogFile, $iSourceDir, $iConfName, $iMergedXml, $iValidate) = @_;
  
  my $configuration;
  my @options;
  my $n; # Used to store number of nodes
  my @units; # List of units in configuration
  my $ID = 1; # Execute Element ID counter
  my $Stage = 1; # Execute Element Stage counter
  
  # Set global validation Flag
  $GenXml::gValidate = $iValidate;

  # Open Log file
  $GenXml::gLogFileH = IO::File->new("> $iLogFile")
    or die "ERROR: RealTimeBuild Couldn't open $iLogFile for writing: $!\n";

  # Logfile headers
  print $GenXml::gLogFileH "===-------------------------------------------------\n";
  print $GenXml::gLogFileH "=== Genxml\n";
  print $GenXml::gLogFileH "===-------------------------------------------------\n";
  print $GenXml::gLogFileH "=== Genxml started ".localtime()."\n";


  # $iSourceDir must end in a \
  # Add a \ if not present
  if ($iSourceDir !~ /\\$/)
  {
    $iSourceDir .= "\\";
  }
  
  # Parse all the files into one DOM doc
  my $doc = &Parse_files($iXmlSource);
  # ... XML::DOM::Document was created sucessfully ...
  
  # Exit here if validating only
  exit if ($GenXml::gValidate);
  
  # Try normalising it
  $doc->normalize;
  
  # Debug dump new doc to file
  $doc->printToFile("$iMergedXml") if ($iMergedXml);

  # Create header for generating the output
  &logfileHeader("Generating output XML ".$iDataOutput);

  # Produce a bare bones output document
  my ($outParser, $outDoc, $docElem, $commands) = &start_output_doc($iConfName);
  
  # Read the global options (savespace and keepgoing)
  my $build = $doc->getElementsByTagName("build");
  # Only one build element allowed  
  my $nodes = $build->item(0)->getElementsByTagName("option");
  $n = $nodes->getLength;
  for (my $i = 0; $i < $n; $i++)
  {
    my $node = $nodes->item($i);
    my $name = $node->getAttributeNode("abldOption");
    my $enable = $node->getAttributeNode("enable")->getValue;
    push @options, $name->getValue if ($enable =~ /Y/i);
  }
 
  # Find named configuration
  $configuration = find_configuration($doc, $iConfName);  
  
  # Read all the children of the configuration (unitListRef or task)
  my $children = $configuration->getChildNodes;
  $n = $children->getLength;
  for (my $i = 0; $i < $n; $i++)
  {
    if (($children->item($i)->getNodeTypeName eq "ELEMENT_NODE") && ($children->item($i)->getTagName eq "unitListRef"))
    {
      #Processes the unitListRefs to build up a complete list of units which are IDREFs
      push @units, &find_unitList_by_ID($doc, $children->item($i)->getAttributeNode("unitList")->getValue, $iSourceDir);
    }
  }

  # Process for tasks this time
  for (my $i = 0; $i < $n; $i++)
  {
    if (($children->item($i)->getNodeTypeName eq "ELEMENT_NODE") && ($children->item($i)->getTagName eq "task"))
    {
      &process_task($children->item($i), $doc, \$outDoc, \$commands, \$ID, \$Stage, \@units, \@options, $iSourceDir);
    }
  }

  
  # Output doc
  $docElem->appendChild($commands);
  $docElem->addText("\n");
  #print $outDoc->toString;
  $outDoc->printToFile($iDataOutput);
  
  $doc->dispose;
  $outDoc->dispose;
  
  # Create footer for generating the output
  &logfileFooter();
  
  # Print Genxml log footer
  print $GenXml::gLogFileH "=== Genxml finished ".localtime()."\n";

  # Close file handles
  close($GenXml::gLogFileH);

}

# Error Processing function for the XML Validation
#
# Throws an exception (with die) when an error is encountered, this
# will stop the parsing process.
# Don't die if a warning or info message is encountered, just print a message.
sub my_fail
{
  my $code = shift;
  
  if ($code < 200)
  {
    print $GenXml::gLogFileH "ERROR: ".XML::Checker::error_string ($code, @_);
    # Set Flag so all the errors are reported before dieing
    $GenXml::gValidateFailed = 1;
  }
  
  # Useful debug output
  print $GenXml::gLogFileH XML::Checker::error_string ($code, @_) if ($GenXml::gValidate);
}

sub my_Unparsed_handler
{
  my ($Parser, $Entity, $Base, $Sysid, $Pubid, $Notation) = @_;
  print $GenXml::gLogFileH "$Entity Unparsed";
  die "ERROR: RealTimeBuild Processing error\n";
}

# Parse_files
#
# Inputs
# $iXMLSoure - ref to array of filenames
#
# Outputs
# $doc - XML DOM doc
#
# Description
# This function merges multiple XML files into one document
sub Parse_files
{
  my ($iXmlSource) = @_;
  my (@docs);

  # Load the XML document
  my %expat_options = (KeepCDATA => 1, 
          Handlers => [ Unparsed => \&my_Unparsed_handler ]);
  
  for (my $i = 0; $i < scalar(@$iXmlSource); $i++)
  {
    # Create header for parsing each file
    &logfileHeader(@$iXmlSource[$i]);

    my $parser = new XML::DOM::ValParser (%expat_options);
    XML::DOM::ignoreReadOnly (1);
    local $XML::Checker::FAIL = \&my_fail;
    
    # Useful debug output
    #print "Parsing ".@$iXmlSource[$i]."\n";
    
    $docs[$i] = $parser->parsefile (@$iXmlSource[$i]);
    
    # Create footer for parsing each file
    &logfileFooter();
  }
  
  # Check to see if any of the XML files failed validation and die
  die "ERROR: RealTimeBuild: Validation failed\n" if ($GenXml::gValidateFailed);

  
  #Docs load now merge into $docs[0]
  for (my $i = 1; $i < scalar(@docs); $i++)
  {
    # Create header for merging each file
    &logfileHeader("Merging in XML file ".@$iXmlSource[$i]);
    &process_node(\($docs[0]->getElementsByTagName("SystemDefinition")),\($docs[$i]->getElementsByTagName("SystemDefinition")), \($docs[0]));
    
    # Re-validate merged file
    local $XML::Checker::FAIL = \&my_fail;
    $docs[0]->check();
    
    # Create footer for merging each file
    &logfileFooter();
    # Check to see if any of the XML files failed validation and die
    die "ERROR: RealTimeBuild: Merged Validation failed\n" if ($GenXml::gValidateFailed);
  }
  
  return $docs[0];
}

# process_node
#
# Inputs
# $node1 - ref to a node from the master
# $node2 - ref to a node from the slave
# $doc1 - ref to the doc of node1 so we can set the doc owner to the (not DOM spec) to get around WRONG_DOCUMENT_ERR restriction
#
# Outputs
#
# Description
# This function processes a node in two DOM documents, if any children match then it calls itself to process
# the children nodes furthur
sub process_node
{
  my ($node1, $node2, $doc1) = @_;
  
  # Some nodes need special processing e.g. SystemDefinition
  # This is because there can only be a certain number of these nodes
  # child node / element rules outlined below, this rules are applied to the children of the node in question
  # Child Node / element tag        Rule
  # ------------------------        ----
  # SystemDefinition                Merge the name and revision CDATA as there can be only one of this element
  # systemModel                     Always processed furthur as there can only be 1 or 0 of these
  # layer                           Same name process furthur otherwise append child
  # logicalset                      Same name process furthur otherwise append child
  # logicalsubset                   Same name process furthur otherwise append child
  # module                          Same name process furthur otherwise append child
  # component                       Same name process furthur otherwise append child
  # unit                            Same unitID generate ERROR and not replace child, otherwise append child
  # sub elements of unit            No processing needed as these cannot be merged
  # package                         Same name process furthur otherwise append child

  # build                           Always processed furthur as there can only be 1 or 0 of these  
  # unitList                        Same name process furthur otherwise append child
  # unitRef                         Same unit ignore, different unit append child
  # targetList                      Same name generate ERROR and not replace child, otherwise append child
  # target                          Same name generate ERROR and not replace child, otherwise append child
  # option                          Same name generate ERROR and not replace child, otherwise append child
  # configuration                   Same name generate ERROR and not replace child, otherwise append child
  # sub elements of configuration   No processing needed as these cannot be merged
  
  
  # All other nodes                 Append child
  
  # Useful debug stuff
  #$GenXml::count++;
  #print "enter $GenXml::count\n";
  
  # Handle the special case for the first call to this function with the node containing the SystemDefinition
  if (($$node1->getTagName eq "SystemDefinition") && ($$node1->getTagName eq "SystemDefinition"))
  {
    # Get the name attributes
    my ($name1) = $$node1->getAttribute('name');
    my ($name2) = $$node2->getAttribute('name');
    
    # Get the revision attributes
    my ($revision1) = $$node1->getAttribute('revision');
    my ($revision2) = $$node2->getAttribute('revision');
    
    # Combine the two and set the attributes
    $$node1->setAttribute('name',$name1." + ".$name2);
    $$node1->setAttribute('revision',$revision1." + ".$revision2);
  }
  
  # Get the children of the parent nodes

  my $nodelist1 = $$node1->getChildNodes;    
  my $nodelist2 = $$node2->getChildNodes;    

  # Useful debug stuff
  #print "has ".$nodelist2->getLength." children\n";
  
  # Itterate throught the children of node2 check to see if they are present / rule match in node 1
  my $ni = $nodelist2->getLength;
  for (my $i = 0; $i < $ni; $i++)
  {
    # Useful debug stuff
    #print "node $i ".$nodelist2->item($i)->getNodeTypeName."\n";
    
    if ($nodelist2->item($i)->getNodeTypeName eq "ELEMENT_NODE")
    {
      # Handle rule match on ELEMENTS
      my $tagname = $nodelist2->item($i)->getTagName;
      
      # Useful debug stuff
      # print "Tagname = $tagname\n";
      
      if (($tagname eq "systemModel") || ($tagname eq "build") )
      {
        # find the $node1 for this elements
        my $nj = $nodelist1->getLength;
        for (my $j = 0; $j < $nj; $j++)
        {
          if ($nodelist1->item($j)->getNodeTypeName eq "ELEMENT_NODE")
          {
            if ($nodelist1->item($j)->getTagName eq $tagname)
            {
              # process furthur
              
              # Useful debug stuff
              #print "processing $tagname furthur\n";
              &process_node(\($nodelist1->item($j)), \($nodelist2->item($i)), $doc1);
            } else {
              # no systemModel or build element found so append child
              &append_child($node1, \($nodelist2->item($i)), $doc1)
            }
          }
        }
      } elsif (($tagname eq "layer") || ($tagname eq "logicalset") || ($tagname eq "logicalsubset") || ($tagname eq "module") || ($tagname eq "component") || ($tagname eq "package") || ($tagname eq "unitList"))
      {
        # Check the $node1 for elements with the same "name"
        my $match; # Flag for matching element found
        my $nj = $nodelist1->getLength;
        for (my $j = 0; $j < $nj; $j++)
        {
          # Only look at element nodes in node1
          if ($nodelist1->item($j)->getNodeTypeName eq "ELEMENT_NODE")
          {
            if ($nodelist2->item($i)->getAttribute('name') eq $nodelist1->item($j)->getAttribute('name'))
            {
              # Process furthur match found
              $match = 1;
              
              # Useful debug stuff
              #print "processing j=$j $tagname furthur ".$nodelist2->item($i)->getAttribute('name')."\n";
              
              &process_node(\($nodelist1->item($j)), \($nodelist2->item($i)), $doc1);
            }
          }
        }
        # If no match found Append child
        
        # Useful debug stuff
        #print "new $tagname added\n" if (!$match);
        
        &append_child($node1, \($nodelist2->item($i)), $doc1) if (!$match);
        
      } elsif (($tagname eq "unit") || ($tagname eq "targetList") || ($tagname eq "target") || ($tagname eq "option") || ($tagname eq "configuration")) {
        # Check the $node1 for elements with the same ID attribute (Global check for ID clashes)
        my $idAttrib;
        if ($tagname eq "unit")
        {
          # Special case of the unit element as this has uses the attribute of unitID instead of name
          $idAttrib = "unitID";
        } else {
          $idAttrib = "name";
        }
        
        my $ID = $nodelist2->item($i)->getAttribute($idAttrib);
        # Search for the XML ID in $doc1
        if( scalar(XML::XQL::solve ("//*[\@$idAttrib = '$ID']", $$doc1)))
        {
          print $GenXml::gLogFileH "ERROR: $ID already exists, not merging this $tagname element\n";
        } else {
          # unitID not found so append elememnt
          
          # Useful debug stuff
          # print "new $tagname added\n";
          
          &append_child($node1, \($nodelist2->item($i)), $doc1);
        }
      } elsif ($tagname eq "unitRef") {
        # Check the $node1 for elements with the same "name"
        my $match; # Flag for matching element found
        my $nj = $nodelist1->getLength;
        for (my $j = 0; $j < $nj; $j++)
        {
          # Only look at element nodes in node1
          if ($nodelist1->item($j)->getNodeTypeName eq "ELEMENT_NODE")
          {
            if ($nodelist2->item($i)->getAttribute('unit') eq $nodelist1->item($j)->getAttribute('unit'))
            {
              # Ignore the unitRef element as it is a duplicate
              $match = 1;
              print $GenXml::gLogFileH "WARNING: Duplicate unitRef ".$nodelist2->item($i)->getAttribute('unit')." not merging\n";
            }
          }
        }
        # No match found Append Child
        
        # Useful debug stuff
        # print "New unitRef\n" if (!$match);
        
        &append_child($node1, \($nodelist2->item($i)), $doc1) if (!$match);
        
      } else {
        # Element not recognised so append child
        &append_child($node1, \($nodelist2->item($i)), $doc1);
      }
    } else {
      # Handle non element nodes (append child of node2 to node 1)
      # At the moment adding in non element nodes adds a lot of whitespace
      # TODO: correctly handle non element nodes
      # This is not important at the moment as there are no important non element nodes for the merge
      #&append_child($node1, \($nodelist2->item($i)), $doc1);
    }
  }
  
  # Useful debug stuff
  #print "return $GenXml::count\n";
  #$GenXml::count--;
}

# append_child
#
# Inputs
# $node1 - is already a ref of the node to append to
# $node2 - ref of node from nodelist2 to append to $node1
# $doc1 - ref to document to merge the node into (need for non DOM operation of changing owner of node)
#
# Outputs
# $outParser - Parser
# $outDoc - document
# $docElem - root element
# $commands - command node
#
# Description
# This function produces the static parts of the output XML file
sub append_child
{
  my ($node1, $node2, $doc1) = @_;
  
  # Clone the node
  my $clone = $$node2->cloneNode(1); 
  # Fix the owner of node
  $clone->setOwnerDocument($$doc1);
  # Append a line return for more tidy xml
  $$node1->addText("\n");
  # Append the node
  $$node1->appendChild($clone);
}

# start_output_doc
#
# Inputs
# $iConfName - Configuration name used
#
# Outputs
# $outParser - Parser
# $outDoc - document
# $docElem - root element
# $commands - command node
#
# Description
# This function produces the static parts of the output XML file
sub start_output_doc
{
  my ($iConfName) = @_;
  
  my ($outParser, $outDoc, $docElem, $commands);

  $outParser = new XML::DOM::Parser;

  my $str = <<END;
<?xml version="1.0"?>
<!DOCTYPE Build  [
  <!ELEMENT Product (Commands)>
  <!ATTLIST Product name CDATA #REQUIRED>
  <!ELEMENT Commands (Execute+ | SetEnv*)>
  <!ELEMENT Execute EMPTY>
  <!ATTLIST Execute
  ID CDATA #REQUIRED
  Stage CDATA #REQUIRED
  Component CDATA #REQUIRED
  Cwd CDATA #REQUIRED
  CommandLine CDATA #REQUIRED>
  <!ELEMENT SetEnv EMPTY>
  <!ATTLIST SetEnv
  Order ID #REQUIRED
  Name CDATA #REQUIRED
  Value CDATA #REQUIRED>
]>
<Product>
</Product>
END

  $outDoc = $outParser->parse($str);
  
  # get the document element
  $docElem = $outDoc->getDocumentElement;
  $docElem->setAttribute('name', $iConfName);
  # Add the Commands Node
  $commands = $outDoc->createElement('Commands');
  $commands->addText("\n");
  # create the default SetEnv elements
  my $SetEnv1 = $outDoc->createElement('SetEnv');
  $SetEnv1->setAttribute('Order', '1');
  $SetEnv1->setAttribute('Name', 'EPOCROOT');
  $SetEnv1->setAttribute('Value', '\\');
  $commands->appendChild($SetEnv1);
  $commands->addText("\n");
  my $SetEnv2 = $outDoc->createElement('SetEnv');
  $SetEnv2->setAttribute('Order', '2');
  $SetEnv2->setAttribute('Name', 'PATH');
  $SetEnv2->setAttribute('Value', '\\epoc32\\gcc\\bin;\\epoc32\\tools;%PATH%');
  $commands->appendChild($SetEnv2);
  $commands->addText("\n");
  
  return ($outParser, $outDoc, $docElem, $commands);
}

# process_task
#
# Inputs
# $task - task node
# $doc - Reference to input document
# $outDoc - Reference to output document
# $commands - Reference to the command node
# $ID - Reference to theExecute ID counter
# $Stage - Reference to the Execute Stage counter
# $units - Reference to the unit array
# $options - Reference to the options array
#
# Outputs
#
# Description
# This function processes the task nodes
sub process_task
{
  my ($task, $doc, $outDoc, $commands, $ID, $Stage, $units, $options, $iSourceDir) = @_;
  
  my $n; # Number of Nodes
  my @targets;
  my @localUnits; # Used for task specific unit list overrides
  
  # Read all the task 
  my $children = $task->getChildNodes;
  $n = $children->getLength;
  for (my $i = 0; $i < $n; $i++)
  {
    if ($children->item($i)->getNodeTypeName eq "ELEMENT_NODE")
    {
      # Check for unitListRef for task unit list override
      if ($children->item($i)->getTagName eq "unitListRef")
      {
        #Processes the unitListRefs to build up a complete list of units which are IDREFs
        push @localUnits, &find_unitList_by_ID($doc, $children->item($i)->getAttributeNode("unitList")->getValue, $iSourceDir);
        # Overwrite Ref $units with new Ref to @localUnits
        $units = \@localUnits;
      }
      
      if ($children->item($i)->getTagName eq "specialInstructions")
      {
        #Processes the unitListRefs to build up a complete list of units which are IDREFs
        my $task_elem = $$outDoc->createElement('Execute');
        $task_elem->setAttribute('ID', $$ID);
        $$ID++; # The ID must always be incremented
        $task_elem->setAttribute('Stage', $$Stage);
        $$Stage++; # All specialInstructions are done sequentially
        $task_elem->setAttribute('Component', $children->item($i)->getAttributeNode("name")->getValue);
        my ($cwd) = $children->item($i)->getAttributeNode("cwd")->getValue;
        # Replace any Environment variables
        my ($cwdtemp) = $cwd;
        $cwdtemp =~ s/%(\w+)%/$ENV{$1}/g;
        # If $cwd does not starts with a drive letter or absolute path then add the source Directory on the front
        if (!(($cwdtemp =~ /^\w:[\\]/) || ($cwdtemp =~ /^\\/)))
        {
          $cwd = $iSourceDir . $cwd;
        }
        $task_elem->setAttribute('Cwd', $cwd);
        $task_elem->setAttribute('CommandLine', $children->item($i)->getAttributeNode("command")->getValue);
        $$commands->appendChild($task_elem);
        $$commands->addText("\n");
      } elsif ($children->item($i)->getTagName eq "buildLayer") {
        # targetParallel ais optional so check that they exist before trying to get the value.
        my $unitP = $children->item($i)->getAttributeNode("unitParallel")->getValue;
        my $targetP = $children->item($i)->getAttributeNode("targetParallel")->getValue if ($children->item($i)->getAttributeNode("targetParallel"));
        my $abldCommand = $children->item($i)->getAttributeNode("command")->getValue;
        
        # Build the list of targets, targets are optional
        if ($children->item($i)->getAttributeNode("targetList"))
        {
          @targets = &find_targetList_by_ID($doc, $children->item($i)->getAttributeNode("targetList")->getValue);
        } else {
          # There are no targets associated with this buildlayer
          $targetP = "NA"; # Not applicable
        }
        
        # Build the correct option string
        my ($optionStr);
        foreach my $option (@$options)
        {
          # only add -savespace if the command abld target or abld build take this option
          # don't add -keepgoing if -what or -check are part of the command
          if ((($option =~ /\s*-savespace\s*/i) || ($option =~ /\s*-s\s*/i) ) && (($abldCommand =~ /^\s*abld\s+target/i) || ($abldCommand =~ /^\s*abld\s+build/i)))
          {
            $optionStr .= " $option" ;
          }
          if (($option =~ /\s*-keepgoing\s*/i) || ($option =~ /\s*-k\s*/i) )
          {
            if (!(($abldCommand =~ /^\s*abld\s+\w*-check\s+/i) || ($abldCommand =~ /^\s*abld\s+\w*-c\s+/i) || ($abldCommand =~ /^\s*abld\s+\w*-what\s+/i) || ($abldCommand =~ /^\s*abld\s+\w*-w\s+/i)))
            {
              $optionStr .= " $option" ;
            }
          }
        }
        
        
        # Cover all the combinations of units and targets
        my ($Ref1, $Ref2, $loop1, $loop2);
        
        if ($targetP eq "N")
        {
          # Got to switch order of looping
          $Ref2 = $units;
          $Ref1 = \@targets;
          $loop2 = $unitP;
          $loop1 = $targetP;
        } else {
          $Ref1 = $units;
          $Ref2 = \@targets;
          $loop1 = $unitP;
          $loop2 = $targetP;
        }
        
        for (my $i = 0; $i < scalar(@$Ref1); $i++)
        {
          if ($targetP ne "NA")
          {
            for (my $j = 0; $j < scalar(@$Ref2); $j++)
            {
              # Create the element
              my $task_elem = $$outDoc->createElement('Execute');
              $task_elem->setAttribute('ID', $$ID);
              $$ID++; # The ID must always be incremented
              $task_elem->setAttribute('Stage', $$Stage);
              
              if ($targetP eq "N") {
                # loops swapped but the order of unitP and targetP need to be swapped back
                # unit (Component) name is the 0 element of the sub array, source location in element 1
                $task_elem->setAttribute('Component',$$Ref2[$j][0]);
                # Find the bldFile directory and set as Cwd
                $task_elem->setAttribute('Cwd',$$Ref2[$j][1]);
                
                $task_elem->setAttribute('CommandLine',$abldCommand.$optionStr." ".$$Ref1[$i]);
                $$commands->appendChild($task_elem);
                $$commands->addText("\n");
              } else {
                # unit (Component) name is the 0 element of the sub array, source location in element 1
                $task_elem->setAttribute('Component',$$Ref1[$i][0]);
                # Find the bldFile directory and set as Cwd
                $task_elem->setAttribute('Cwd',$$Ref1[$i][1]);
                
                $task_elem->setAttribute('CommandLine',$abldCommand.$optionStr." ".$$Ref2[$j]);
                $$commands->appendChild($task_elem);
                $$commands->addText("\n");
              }
              $$Stage++ if (($loop1 eq "N") && ($loop2 eq "N"));
            }
            $$Stage++ if (($loop1 eq "N") && ($loop2 eq "Y"));
          } else {
            # Create the element
            my $task_elem = $$outDoc->createElement('Execute');
            $task_elem->setAttribute('ID', $$ID);
            $$ID++; # The ID must always be incremented
            $task_elem->setAttribute('Stage', $$Stage);

            # unit (Component) name is the 0 element of the sub array, source location in element 1
            $task_elem->setAttribute('Component',$$Ref1[$i][0]);
            # Find the bldFile directory and set as Cwd
            $task_elem->setAttribute('Cwd',$$Ref1[$i][1]);
            
            $task_elem->setAttribute('CommandLine',$abldCommand.$optionStr);
            $$commands->appendChild($task_elem);
            $$commands->addText("\n");

            $$Stage++ if ($loop1 ne "Y");
          }
        }
        # Add the * (stage++) for the combinations that don't get this done by the loops
        $$Stage++ if ($loop1 eq "Y");
      }
    }
  }
}


# find_configuration
#
# Inputs
# $doc - DOM document model
# $name - configuration name
#
# Outputs
# $config - the node of the named configuration
#
# Description
# This function locates and return the named configuration node
sub find_configuration
{
  my ($doc, $iConfName) = @_;
  
  # Find the named configuration 
  my $nodes = $doc->getElementsByTagName ("configuration");
  my ($configuration, $match);
  my $n = $nodes->getLength;
  for (my $i = 0; $i < $n; $i++)
  {
      my $node = $nodes->item ($i);
      my $name = $node->getAttributeNode ("name");
      if ( $name->getValue eq $iConfName)
      {
        $match = 1;
        $configuration = $node;
      }
  }
  
  # If no configuration has been found the produce ERROR message
  die "ERROR: RealTimeBuild: Named configuration $iConfName not found\n" if (!$match);
  
  return $configuration;
}

# Find_bldFile_by_ID
#
# Inputs
# $doc - DOM document model
# $id - value of the IDREF to find
#
# Outputs
# $bldFile - the value of the bldFile attribute of the unit referenced
#
# Description
# This function finds the location of the bld.inf in the system model
sub find_bldFile_by_ID
{
  my ($doc, $id) = @_;
  
  #print "finding bldFile $id\n";
  my (@element) = XML::XQL::solve ("//unit[\@unitID = '$id']", $doc);
  # Should only return one element because the Validating Parser will not allow multiple DTD ID's
  if ($element[0])
  {
    return $element[0]->getAttributeNode("bldFile")->getValue;
  } else {
    return undef;
  }
}

# Find_unitList_by_ID
#
# Inputs
# $doc - DOM document model
# $id - value of the IDREF to find
# $iSourceDir - root of source
#
# Outputs
# @units - a list of arrays [units,source location] referenced in the specified unit list
#
# Description
# This function finds a list of units and full source location
sub find_unitList_by_ID
{
  my ($doc, $id, $iSourceDir) = @_;
  
  my $n; # Number of Nodes
  my @units; # List of units in unitList
  my $unitLoc; #Unit location 
  
  #print "finding unitList $id\n";
  my (@element) = XML::XQL::solve("//unitList[\@name = '$id']", $doc);
  # Should only return one element because the Validating Parser will not allow multiple DTD ID's
  if (!($element[0]))
  {
    print $GenXml::gLogFileH "ERROR: Cannot find unitList $id\n";
    die "ERROR: RealTimeBuild: Cannot find unitList $id\n";
  }  
  my $children = $element[0]->getChildNodes;
  $n = $children->getLength;
  for (my $i = 0; $i < $n; $i++)
  {
    if ( ($children->item($i)->getNodeTypeName eq "ELEMENT_NODE") && ($children->item($i)->getTagName eq "unitRef"))
    {
      # build up the list of units to return
      my $unitID = $children->item($i)->getAttributeNode("unit")->getValue;
      my $bldFile = &find_bldFile_by_ID($doc, $unitID);
      if (!defined $bldFile)
      {
        print $GenXml::gLogFileH "ERROR: unit $unitID not found, not building\n";
      } else {
        $unitLoc = $iSourceDir.&find_bldFile_by_ID($doc, $unitID);
        # Check that unit was found skip existance check
        if (defined $unitLoc)
        {
          # Check that the bld.inf exists before pushing on to the list
          if (-e $unitLoc."\\bld.inf")
          {
            push @units, [$unitID, $unitLoc];
          } else {
            print $GenXml::gLogFileH "MISSING: $unitLoc file could not be found, not building $unitID\n";
          }
        }
      }
    }
  }
  
  return @units;
}

# find_targetList_by_ID
#
# Inputs
# $doc - reference to DOM document model
# $id - value of the IDREFS to find (multiple whitespace ID's)
#
# Outputs
# @targets - a list of targets referenced in the specified targetList
#
# Description
# This function finds a list of units and full source location
sub find_targetList_by_ID
{
  my ($doc, $idrefs) = @_;
  
  my $n; # Number of Nodes
  my @targets; # List of units in targetList
  
  # Split on whitespace to get ID's from IDREFS
  my @ids = split(/\s+/, $idrefs);
  
  for (my $i = 0; $i < scalar(@ids); $i++)
  {
    my ($id) = $ids[$i];
    my (@element) = XML::XQL::solve("//targetList[\@name = '$id']", $doc);
    # Should only return one element because the Validating Parser will not allow multiple DTD ID's
    # target attrib is another IDREFS list of target
    if (!($element[0]))
    {
      print $GenXml::gLogFileH "ERROR: Cannot find targetList $id\n";
      die "ERROR: RealTimeBuild: Cannot find targetList $id\n";
    }
    my $targetIDREFS;
    if ($element[0])
    {
      $targetIDREFS = $element[0]->getAttributeNode("target")->getValue;
    } else {
      print $GenXml::gLogFileH "ERROR: Cannot find targetList of $id\n";
      die "ERROR: RealTimeBuild Processing error\n";
    }
    
    # Split on whitespace to get ID's from IDREFS
    my @targetsID = split(/\s+/, $targetIDREFS);
    for (my $j = 0; $j < scalar(@targetsID); $j++)
    {
      my ($target) = $targetsID[$j];
      my (@target_element) = XML::XQL::solve("//target[\@name = '$target']", $doc);
      # Should only return one element because the Validating Parser will not allow multiple DTD ID's
      if ($target_element[0])
      {
        push @targets, $target_element[0]->getAttributeNode("abldTarget")->getValue;
      } else {
        print $GenXml::gLogFileH "ERROR: Cannot find target of $target\n";
        die "ERROR: RealTimeBuild Processing error\n";
      }
    }
  }
  
  return @targets;
}

# logfileHeader
#
# Inputs
# $comp - string to place in the "component" section of the header
#
# Outputs
#
# Description
# This function print the log file header to te global logfile handle
sub logfileHeader
{
  my ($comp) = @_;
  
  # Log file headers for each log file loading
  print $GenXml::gLogFileH "=== Genxml == $comp\n";

  print $GenXml::gLogFileH "-- Genxml\n";
  # Add the per command start timestamp
  print $GenXml::gLogFileH "++ Started at ".localtime()."\n";
  # Add the per command start HiRes timestamp if available
  if ($gHiResTimer == 1)
  {
    print $GenXml::gLogFileH "+++ HiRes Start ".Time::HiRes::time()."\n";
  } else {
    # Add the HiRes timer missing statement
    print $GenXml::gLogFileH "+++ HiRes Time Unavailable\n";
  }
  $GenXml::gLogFileH->flush;
}

# logfileFooter
#
# Inputs
#
# Outputs
#
# Description
# This function print the log file footer to te global logfile handle
sub logfileFooter
{
  # Add the per command end HiRes timestamp if available
  print $GenXml::gLogFileH "+++ HiRes End ".Time::HiRes::time()."\n" if ($gHiResTimer == 1);
  # Add the per command end timestamp
  print $GenXml::gLogFileH "++ Finished at ".localtime()."\n";
  $GenXml::gLogFileH->flush;
}

1;