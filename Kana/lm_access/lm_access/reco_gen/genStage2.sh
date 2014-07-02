#!/usr/bin/env bash
#
# genStage2.sh script: produce the information needed for stage2
#                      luminosity files. uses the querySQL.py
#                      Python script and the RecoGen C++ program
#
# syntax: genStage2.sh directory filename 
#                      where directory gives the path to the
#                      querySQL.py Python script and the RecoGen
#                      C++ program and filename is the name of a ROOT tuple
#                      known to SAM (including the full path name)
# 
# This script is usually called from a SAM project once a file
# is delivered in the SAM cache (see the Stage2.py Python script)
#
# Directory in which the scripts and programs reside
#
PROGDir=$1
# 
# Remove the directory path from the filename
#
FULLName=$2
FILEName=`echo $FULLName | awk '{i=index($1,"recoA");print substr($1,i)}'`
#
# Print some welcome message
# 
echo    "genStage2: Processing file $FILEName"
echo -n "           Starting at "; date
#
# Usual D0 setups
#
. /usr/local/etc/setups.sh
setup n32
setup D0RunII p11.05.00 > /dev/null 2>&1
setup python_dcoracle
# 
# Get the relevant informations for this file
# from the SAM and Runs databases
# 
\rm -f info.txt
$PROGDir/querySQL.py -f $FILEName
SQLstatus=$?
echo    "           Return code from querySQL: $SQLstatus"
#
# If the database information was available process
# the ROOT tuple, make consistency checks and count
# the number of minbias and zerobias triggers per
# luminosity block
#
if [ $SQLstatus == 0 ]
then
  $PROGDir/RecoGen $FULLName
  ROOTstatus=$?
  echo    "           Return code from RecoGen: $ROOTstatus"
  if [ $ROOTstatus != 0 ]
  then
    echo    "           File $FILEName processing failed during RecoGen"
    \rm -f core
  fi
else
  echo    "           File $FILEName processing failed during querySQL"
fi
#
# End of the script
#
echo -n "           Ending at "; date
echo    " "
exit 0
