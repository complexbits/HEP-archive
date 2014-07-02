#!/usr/bin/env python
#
# Main Python script for generating the Stage 2 files for the 
# luminosity group.
#
# To run it: 1) edit the script and change the project name
#            2) setup n32
#               setup D0RunII ......
#               setup SAM
#               \rm -f Stage2.logfile
#               touch Stage2.logfile
#               sam run project Stage2.py
#
# Uses:      1) genStage2.sh
#            2) querySQL.py
#            3) RecoGen (RecoGen.cpp, ReadSAMInfo.cpp, ReadSAMInfo.hpp, Makefile)
#
# Make sure that the version of the D0 software used in genStage2.sh
# is the same one used to compile the RecoGen executable.
#

import os, sys, string, time, signal
from re import *
from globals import *
import run_project

#
# Directory in which the program is run
#
RunDirectory='/prj_root/866/lum_1/prolay/p1015_test2'

#
# Directory in which the executables and the scripts reside
#
ExeDirectory='/prj_root/866/lum_1/prolay/scripts'

#
# SAM dataset definition
#
project_definition ="pkm_p1015until140402"

############################################################################
#
# DO NOT CHANGE ANYTHING BELOW THIS LINE
#
############################################################################
#
# SAM options: sam_station 
#              snapshot_version
#              appname
#              version
#              group
#              max_file_amt
#              verbosity
#              give_up
#
sam_station        = "central-analysis"
snapshot_version   = 'new'
appname            = "test"
version            = "1"
group              = "dzero"
max_file_amt       = 30000
verbosity          = ""
give_up            = 1

def file_ready(filename):
    #
    # Call the genStage2.sh script: the path of the script is specified by the
    # ExeDirectory variable (and it is passed to the script). Pass also the name
    # of the file returned by SAM and the directory in which the script is run.
    #
    os.system('%s/genStage2.sh %s %s >> %s/Stage2.logfile 2>&1'%(ExeDirectory,ExeDirectory,filename,RunDirectory))

    return




