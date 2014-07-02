#!/usr/local/bin/bash
#
# Simple shell script to generate the MINTS web pages
#
# Run by cron for user mverzocc daily at 1:17am (CST)
# Usually installed in the /prj_root/866/lum_1/cronjobs/mints
# directory, requires the checkRunInfo.py and mkWebRunInfo.py
# scripts and the mkWebRunInfo.config configuration file.
# Any editing should be restricted to the configuration file
# and to this script if necessary.
#
# Output: michael.dat     ASCII file for Michael Begel 
#         runMINTS.log    log file for MINTS
# 

cd /prj_root/866/lum_1/cronjobs/mints

. /usr/local/etc/setups.sh
setup n32
setup D0RunII
setup python_dcoracle

WWWdirectory=/www-d0/home/WWW/docs/phys_id/luminosity/data_access/processing_status
export WWWdirectory 

#
# First run checkRunInfo.py. Some lines may be commented below,
# once the processing of a certain version of Reco has been
# completed. Use the -q option to check for queued jobs for a
# certain version of the software.
#
# ./checkRunInfo.py -b 129194 -e 133020 -l all -v t01.56% -w $WWWdirectory
# ./checkRunInfo.py -b 129194 -e 133020 -l all -v p10.07% -w $WWWdirectory
# ./checkRunInfo.py -b 129194 -e 146000 -l all -v p10.11% -w $WWWdirectory
# ./checkRunInfo.py -b 139615 -e 148000 -l all -v p10.14% -w $WWWdirectory
# ./checkRunInfo.py -b 145043 -e 155554 -l all -v p10.15% -q -w $WWWdirectory
# ./checkRunInfo.py -b 139615 -e 199999 -l all -v p11.07% -q -w $WWWdirectory
#  ./checkRunInfo.py -b 145001 -e 158453 -l all -v p11.08% -q -w $WWWdirectory
# ./checkRunInfo.py -b 157527 -e 160558 -l all -v p11.09% -q -w $WWWdirectory
# ./checkRunInfo.py -b 158973 -e 161648 -l all -v p11.10% -q -w $WWWdirectory
# ./checkRunInfo.py -b 161646 -e 163647 -l all -v p11.11% -q -w $WWWdirectory
# ./checkRunInfo.py -b 164039 -e 165775 -l all -v p11.12% -q -w $WWWdirectory
# ./checkRunInfo.py -b 157708 -e 166782 -l all -v p11.13% -q -w $WWWdirectory
# ./checkRunInfo.py -b 166000 -e 199999 -l all -v p13.02% -q -w $WWWdirectory
# ./checkRunInfo.py -b 166000 -e 199999 -l all -v p13.03% -q -w $WWWdirectory
# ./checkRunInfo.py -b 166000 -e 199999 -l all -v p13.04% -q -w $WWWdirectory
# ./checkRunInfo.py -b 164382 -e 170246 -l all -v p13.05% -q -w $WWWdirectory
#./checkRunInfo.py -b 165589 -e 169002 -l all -v r13.06% -q -w $WWWdirectory
#./checkRunInfo.py -b 151817 -e 178310 -l all -v p13.06% -q -w $WWWdirectory
#./checkRunInfo.py -b 165650 -e 180956 -l all -v p14.03% -q -w $WWWdirectory
#./checkRunInfo.py -b 151852 -e 177243 -l all -v p14.05% -q -w $WWWdirectory
#./checkRunInfo.py -b 187169 -e 187170 -l all -v r14.06% -q -w $WWWdirectory
./checkRunInfo.py -b 149000 -e 199999 -l all -v p14.06% -q -w $WWWdirectory
#
# Next run mkWebRunInfo.py. This also produces an ASCII
# file for Michael Begel (michael.dat), updated daily.
#
\rm -f tmp.dat michael.dat
./mkWebRunInfo.py -v -c mkWebRunInfo.config > tmp.dat 2>&1
sort -r tmp.dat > michael.dat
\rm -f tmp.dat

# Make sure that other people can access the files in write mode
cd $WWWdirectory
chmod -R 2775 *
