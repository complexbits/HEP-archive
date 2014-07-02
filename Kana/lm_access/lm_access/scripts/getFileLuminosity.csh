#!/bin/csh 

setenv filename $1
setenv trigger $2

setup sam

makeFileParentageList.py $filename 
file_luminosity $filename $trigger

exit(0)

