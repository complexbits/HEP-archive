#!/usr/bin/env python
# 
# Program to get run information from the SAM and Runs databases
#
# Version 2.1  - 09 Jun 2003 - H. Schellman ignore monitor trigger 
#
# Version 1.9  - 01 Jun 2003 - H. Schellman fix filename parsing for new streams
#
# Version 1.8  - 29 Nov 2002 - H. Schellman
#                Update for p13, checks for thumbnails, ignores root and strip
#
# Version 1.7  - 24 May 2002 - Marco Verzocchi
#                Fix a bug (improper handling of other streams while
#                getting the list of runs currently being processed on
#                the farms)
#
# Version 1.6  - 17 May 2002 - Marco Verzocchi
#                HTML directory now passed as a runtime option
#
# Version 1.5  - 05 May 2002 - Marco Verzocchi
#                Corrected a minor bug
# Version 1.4  - 04 May 2002 - Marco Verzocchi
#                Remove some comments
#
# Version 1.3  - 24 April 2002 - Marco Verzocchi
#                Reenable some checks on recoAS files
#                Prevent other users from running the script
#
# Version 1.2  - 23 April 2002 - Marco Verzocchi
#                Disable checkMerge on merged recoS and recoAS files
#                (the name of the file does not correspond to the real
#                range, so it cannot be used; since we don't have the
#                parentage information for recoS and recoAS files, a
#                proper check cannot be performed).
#                Check that the files are actually available in SAM.
#                Handle partitions being processed more than once.
#                Check for any run taken with an official/global trigger.
#                Add check for jobs currently queued on the farms.
#
# Version 1.1  - 08 April 2002 - Marco Verzocchi
#                First version of the code, probably there are still
#                bugs, particularly when dealing with early versions
#                of the D0 software (p10.14.00 and earlier versions)
#                There may still be room for improvement in the speed
#                of the code (either by making a single SQL query for
#                all the files belonging to a run, or by making more
#                complex SQL queries).
#
import dcoracle
import getopt,os,sys,string,time
import re

class Sqlbase:
    def __init__ (self, dbc):
        self.__dbc = dbc
        self.__cursor = dbc.cursor()
        return

    def __del__ (self):
        del self.__dbc
        del self.__cursor
        return

    def dbc (self):
        return self.__dbc

    def sql (self, sqlexpr, args = ()):
        self.__cursor.execute (sqlexpr, args)
        return self.__cursor.fetchall ()

#
# Retrieve a list of the runs which are still being processed 
#
def infoRunsInQueue(sql,version):
    runlist=[]
    runPattern=re.compile('[0-9]{10,10}')
    query="select analysis_projects.proj_snap_id from analysis_projects,working_groups,persons where working_groups.work_grp_name='d0production' and persons.last_name='farm' and analysis_projects.person_id=persons.person_id and working_groups.work_grp_id=analysis_projects.work_grp_id and analysis_projects.project_name like '%%%s%%' and ( analysis_projects.project_status like 'new%%' or analysis_projects.project_status like 'running%%' )"%(version)
    l=sql.sql(query)
    for id in l:
        m=sql.sql("select  data_files.file_name "
                  "from    data_files,project_files,datasets "
                  "where   data_files.file_id=project_files.file_id and project_files.proj_snap_id=datasets.dataset_id and "
                  "        data_files.data_tier='raw' and datasets.dataset_id=:p1",id)
        for file in m:
            file='%s'%file
            matchString=runPattern.search(file)
            runnum=string.atoi(file[matchString.start():matchString.end()])
            if not runnum in runlist:
                runlist.append(runnum)
    return runlist

#
# Retrieve runs data base information by run number (for a single run in the runs database)
#
def infoGetRunsDBbyRun(sql,run):
    l = sql.sql ("select  runs.run_number,run_streams.stream_name,runs.trig_config_name,runs.trig_config_vers,to_char(new_time(runs.start_time,'GMT','CST')) "
                 "from    runs.runs,runs.run_streams "
                 "where   runs.run_number=run_streams.run_number and runs.run_number=:p1"
                 ,(run))
    return l

#
# Retrieve runs data base information by run number and trigger name (for many runs in the runs database)
#
def infoGetRunsDBbyRunTrigger(sql,first,last,trigger):
    l = sql.sql ("select  runs.run_number,run_streams.stream_name,runs.trig_config_name,runs.trig_config_vers,to_char(new_time(runs.start_time,'GMT','CST')) "
                 "from    runs.runs,runs.run_streams "
                 "where   runs.run_number=run_streams.run_number and runs.run_number>=:p1 and runs.run_number<=:p2 and runs.trig_config_name like :p3"
                 ,(first,last,trigger))
    return l

#
# Retrieve SAM information by run number and tier
#
def infoByRun (sql,run,tier='raw'):
    l = sql.sql ("select  data_files.file_name,data_files.file_id,application_families.version,data_files.event_count,data_file_status.file_status "
                 "from    data_files,runs,physical_datastreams,application_families,data_file_status "
                 "where   data_files.run_id=runs.run_id and application_families.appl_family_id=data_files.appl_family_id and "
                 "        data_files.file_status=data_file_status.file_status and "
                 "        data_files.stream_id=physical_datastreams.stream_id and runs.run_number=:p1 and data_files.data_tier=:p2 and "
                 "        data_file_status.file_status='available' "
                 "order by data_files.file_name"
                 ,(run,tier))
    return l


# 
# Retrieve SAM information by run number, tier and version
#
def infoByRunV (sql,run,version,tier='raw'):
    l = sql.sql ("select  data_files.file_name,data_files.file_id,application_families.version,data_files.event_count,data_file_status.file_status "
                 "from    data_files,runs,physical_datastreams,application_families,data_file_status "
                 "where   data_files.run_id=runs.run_id and application_families.appl_family_id=data_files.appl_family_id and "
                 "        data_files.file_status=data_file_status.file_status and "
                 "        data_files.stream_id=physical_datastreams.stream_id and runs.run_number=:p1 and data_files.data_tier=:p2 and "
                 "        application_families.version like :p3 and data_file_status.file_status='available'"
                 ,(run,tier,version))
    return l

#
# Retrieve SAM parent information by file id, tier and version
#
def infoByParent (sql,id,version,tier='reconstructed'):
    l = sql.sql ("select  data_files.file_name,data_files.file_id,data_files.event_count,data_file_status.file_status,application_families.version "
                 "from    data_files,file_lineages,application_families,data_file_status "
                 "where   data_files.file_id=file_lineages.file_id_dest and data_files.appl_family_id=application_families.appl_family_id and "
                 "        data_files.file_status=data_file_status.file_status and "
                 "        file_lineages.file_id_source=:p1 and data_files.data_tier=:p2 and application_families.version like :p3 and "
                 "        data_file_status.file_status='available'"
                 , (id,tier,version))
    return l

#
# Retrieve SAM child information by file id and tier
#
def infoByChild (sql,id,tier='reconstructed'):
    l = sql.sql ("select  data_files.file_name,data_files.file_id,data_files.event_count,data_file_status.file_status "
                 "from    data_files,file_lineages,data_file_status "
                 "where   data_files.file_id=file_lineages.file_id_source and file_lineages.file_id_dest=:p1 and data_files.data_tier=:p2 and "
                 "        data_files.file_status=data_file_status.file_status and data_file_status.file_status='available'"
                 , (id,tier))
    return l

#
# Retrieve SAM child information by file, tier and version
#
def infoByChildV (sql,id,version,tier='reconstructed'):
    l = sql.sql ("select  data_files.file_name,data_files.file_id,application_families.version,data_files.event_count,data_file_status.file_status "
                 "from    data_files,file_lineages,application_families,data_file_status "
                 "where   data_files.file_id=file_lineages.file_id_source and data_files.appl_family_id=application_families.appl_family_id and "
                 "        data_files.file_status=data_file_status.file_status and "
                 "        file_lineages.file_id_dest=:p1 and data_files.data_tier=:p2 and application_families.version like :p3 and "
                 "        data_file_status.file_status='available'"
                 , (id,tier,version))
    return l

#
# Trace down inconsistencies between the DST and the raw data
#
def checkDST(userfile,sql,run,version):
    for reco,nid,ver,evt2,stat2 in infoByRunV(sql,run,version,tier='reconstructed'):
	if(string.find(reco,"monitor")> -1):
	    continue
        tot1=0
        for raw,id,evt1,stat1 in infoByChild(sql,nid,tier='raw'):
	    fileinfo=parsefilename(raw)
	    if fileinfo["type"] == "unknown":
		continue
	    if fileinfo["stream"]=="monitor":
		continue
            tot1=tot1+evt1
        if ( tot1!=evt2):
            userfile.write('<FONT COLOR="#AA7700">')
            userfile.write('Inconsistency found between DST and raw data file\n')
            userfile.write('Number of events in the DST file       %10d\n'%(evt2))
            userfile.write('Number of events in the raw data files %10d'%(tot1))
            userfile.write('</FONT>\n')
            userfile.write('Name of the DST file <FONT COLOR="#0000DD">%s</FONT>\n'%(reco))
            userfile.write('List of raw data files\n')
            for raw,id,evt1,stat1 in infoByChild(sql,nid,tier='raw'):
                userfile.write('      <FONT COLOR="#0000FF">%s</FONT> %7d\n'%(raw,evt1))
            userfile.write('------------------------------------------------------------\n')
    return

#
# Trace down inconsistencies between the ROOT tuple, the DST and the raw data
#
def checkROOT(userfile,sql,run,version):
    for root,rid,ver,evt3,stat3 in infoByRunV(sql,run,version,tier='root-tuple'):
        tot2=0
        tot1=0
        for reco,nid,ver,evt2,stat2 in infoByChildV(sql,rid,version,tier='reconstructed'):
	    if(string.find(reco,"monitor")> -1):
		continue
            tot2=tot2+evt2
            for raw,id,evt1,stat1 in infoByChild(sql,nid,tier='raw'):
		if(string.find(raw,"monitor")>-1):
		    continue
                tot1=tot1+evt1
        if ( tot2!=evt3):
            userfile.write('<FONT COLOR="#AA7700">')
            userfile.write('Inconsistency found between ROOT tuple and DST file\n')
            userfile.write('Number of events in the ROOT tuple     %10d\n'%(evt3))
            userfile.write('Number of events in the DST  files     %10d'%(tot2))
            userfile.write('</FONT>\n')
            userfile.write('Name of the ROOT tuple <FONT COLOR="#0000BB">%s</FONT>\n'%(root))
            userfile.write('List of DST files\n')
            for reco,nid,ver,evt2,stat2 in infoByChildV(sql,rid,version,tier='reconstructed'):
		if(string.find(reco,"monitor")>-1):
		    continue
                userfile.write('       <FONT COLOR="#0000DD">%s</FONT> %7d \n'%(reco,evt2))
            userfile.write('------------------------------------------------------------\n')
        if ( tot1!=evt3):
            userfile.write('<FONT COLOR="#AA7700">')
            userfile.write('Inconsistency found between ROOT tuple and raw data file\n')
            userfile.write('Number of events in the ROOT tuple     %10d\n'%(evt3))
            userfile.write('Number of events in the raw data files %10d'%(tot1))
            userfile.write('</FONT>\n')
            userfile.write('Name of the ROOT tuple <FONT COLOR="#0000BB">%s</FONT>\n'%(root))
            userfile.write('List of raw data files\n')
            for reco,nid,ver,evt2,stat2 in infoByChildV(sql,rid,version,tier='reconstructed'):
		if(string.find(reco,"monitor")>-1):
		    continue
                for raw,id,evt1,stat1 in infoByChild(sql,nid,tier='raw'):
                    userfile.write('       <FONT COLOR="#0000FF">%s</FONT> %7d\n'%(raw,evt1))
            userfile.write('------------------------------------------------------------\n')
    return

#
# Trace down inconsistencies between the ROOT tuple, the DST and the raw data
#
def checkTMB(userfile,sql,run,version):
    for tmb,tid,ver,evt3,stat3 in infoByRunV(sql,run,version,tier='thumbnail'):
        tot1=0
	if(string.find(tmb,"monitor")>-1):
	    continue
        for raw,id,evt1,stat1 in infoByChild(sql,tid,tier='raw'):
	    if(string.find(raw,"monitor")>-1):
		continue
            tot1=tot1+evt1
        if ( tot1!=evt3):
            userfile.write('<FONT COLOR="#AA7700">')
            userfile.write('Inconsistency found between thumbnail and raw data file\n')
            userfile.write('Number of events in the thumbnail      %10d\n'%(evt3))
            userfile.write('Number of events in the raw data files %10d'%(tot1))
            userfile.write('</FONT>\n')
            userfile.write('Name of the thumbnail <FONT COLOR="#0000BB">%s</FONT>\n'%(tmb))
            userfile.write('List of raw data files\n')
            for raw,id,evt1,stat1 in infoByChild(sql,rid,tier='raw'):
		if(string.find(raw,"monitor")>-1):
		    continue
                userfile.write('       <FONT COLOR="#0000FF">%s</FONT> %7d\n'%(raw,evt1))
            userfile.write('------------------------------------------------------------\n')
    return

#
# Trace down inconsistencies between recoS file and its ROOT tuple
#
def checkFROOT(userfile,sql,run,version):
    for root,rid,ver,evt3,stat3 in infoByRunV(sql,run,version,tier='filtered-root'):
        tot2=0
        for recoS,sid,ver,evt2,stat2 in infoByChildV(sql,rid,version,tier='raw'):
            tot2=tot2+evt2
        if ( tot2!=evt3):
            userfile.write('<FONT COLOR="#AA7700">')
            userfile.write('Inconsistency found between recoS file and its ROOT tuple\n')
            userfile.write('Number of events in the recoS file     %10d\n'%(tot2))
            userfile.write('Number of events in the ROOT tuple     %10d'%(evt3))
            userfile.write('</FONT>\n')
            userfile.write('Name of the ROOT tuple <FONT COLOR="#000077">%s</FONT>\n'%(root))
            userfile.write('List of recoS files\n')
            for reco,nid,ver,evt2,stat2 in infoByChildV(sql,rid,version,tier='filtered-reco'):
                userfile.write('       <FONT COLOR="#000099">%s</FONT> %7d\n'%(reco,evt2))
            userfile.write('------------------------------------------------------------\n')
    return

#
# Look for gaps in merged files
#
def checkMerge(userfile,sql,run,stream,lowestpart,version,partition,tier='root-tuple'):
    errsum=0
    npart=len(partition)
    nstre=len(stream)
    for file,id,ver,evt,stat in infoByRunV(sql,run,version,tier):
        skip=0
        color='#000000'
        if ( tier=='root-tuple'): 
            if ( file[0:11+nstre]=='recoA_reco_%s'%(stream) ):
                color="#0000BB"
                pos=string.find(file,'mrg')
                if ( pos>=0 ):
                    first=string.atoi(file[27+nstre:30+nstre])
                    last=string.atoi(file[31+nstre:34+nstre])
                else:
                    first=string.atoi(file[23+nstre:26+nstre])
                    last=first
            else:
                skip=1
        if ( tier=='filtered-reco'):
            color="#000099"
            if ( file[0:6+nstre]=='recoS_%s'%(stream) ): 
                pos=string.find(file,'mrg')
                if ( pos>=0 ):
                    first=string.atoi(file[22+nstre:25+nstre])
                    last=string.atoi(file[26+nstre:29+nstre])
                else:
                    first=string.atoi(file[18+nstre:21+nstre])
                    last=first
            else:
                skip=1
        if ( tier=='filtered-root'):
            color="#000077"
            if ( file[0:12+nstre]=='recoA_recoS_%s'%(stream) ): 
                pos=string.find(file,'mrg')
                if ( pos>=0 ):
                    first=string.atoi(file[28+nstre:31+nstre])
                    last=string.atoi(file[43+nstre:46+nstre])
                    frun=string.atoi(file[17+nstre:27+nstre])
                    if ( frun<string.atoi(run) ):
                        first=1
                    lrun=string.atoi(file[32+nstre:42+nstre])
                    if ( lrun>string.atoi(run) ):
                        last=npart
                else:
                    first=string.atoi(file[24+nstre:27+nstre])
                    last=first
            else:
                skip=1
        if ( tier=='thumbnail'):
            color="#000055"
            if ( file[0:6+nstre]=='recoT_%s'%(stream) ):
                pos=string.find(file,'mrg')
                if ( pos>=0 ):
                    first=string.atoi(file[22+nstre:25+nstre])
                    last=string.atoi(file[26+nstre:29+nstre])
                else:
                    first=string.atoi(file[18+nstre:21+nstre])
                    last=first
            else:
                skip=1
        if ( skip==0 ):
            if (lowestpart==1 ):
                first=first-1
                last=last-1
            for i in range (first,last+1):
		if(i >= len(partition)):
		   print " partition out of range ",i,">",len(partition)
		   break
                if ( partition[i]==0 ):
                    userfile.write('<FONT COLOR="#FF0000">Error merged non processed partition</FONT> %3d in file <FONT COLOR="%7s">%s</FONT>\n'%(i+1,color,file))
                    errsum=1
                else: 
                    partition[i]=-1
    if ( errsum>0 ):
        userfile.write('------------------------------------------------------------\n')
    return errsum

#
# Do all the checks for a single run
# 
def doOneRun(debug,htmldir,sql,run,trigger,stream,version,startdate,queued):
   
    # Reset all buffers
    tot1=0
    tot2=0
    tot3=0
    tot4=0
    tot5=0
    totT=0
    mis2=0
    mis3=0
    mis4=0
    mis5=0
    misT=0
    DSTcheck=0
    ROOTcheck=0
    FROOTcheck=0
    TMBcheck=0
    otp=[] 
    ost=[]
    osr=[]
    DSTflag=[]
    ROOTflag=[]
    recoSflag=[]
    recoASflag=[]
    TMBflag=[]
    multiDST=0
    processingSTARTED=1
    erro=0
    # Get the number of raw data files for this run
    l0=infoByRun(sql,run,tier='raw')
    numrows0=len(l0)
    if debug:
        sys.stderr.write('Found %d raw data files for run %s\n'%(numrows0,run))
    htmlsubdir='%3.3d'%(string.atoi(run)/1000)
    if not htmlsubdir in os.listdir(htmldir):
        os.system('mkdir %s/%s'%(htmldir,htmlsubdir))
    htmlfile='%s/%s/run%10.10d.%6s.html'%(htmldir,htmlsubdir,string.atoi(run),version[0:6])
    if htmlfile in os.listdir(htmldir):
        os.remove(htmlfile)
    htmlrun=open(htmlfile,"w")
    # HTML header
    htmlrun.write('<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">\n')
    htmlrun.write('<HTML>\n')
    htmlrun.write('<HEAD>\n')
    htmlrun.write('   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">\n')
    htmlrun.write('   <META NAME="GENERATOR"  CONTENT="MINTS: version 1.00 - Data processing checks">\n')
    htmlrun.write('<TITLE>Data processing checks for run number %7d - D0 version %6s</TITLE>\n'%(string.atoi(run),version[0:6]))
    htmlrun.write('</HEAD>\n')
    htmlrun.write('<BODY TEXT="#000000" BGCOLOR="#FFFFFF" LINK="#0000EE" VLINK="#551A8B" ALINK="#FF0000">\n')
    htmlrun.write('<H3>Data processing checks for run number %7d - D0 version %6s </H3>\n'%(string.atoi(run),version[0:6]))
    htmlrun.write('<HR>\n')
    htmlrun.write('<PRE>\n')
    htmlrun.write('------------------------------------------------------------\n')
    htmlrun.write('checkRunInfo.py running for run number %7d - %3d partitions\n'%(string.atoi(run),numrows0))
    htmlrun.write('------------------------------------------------------------\n')
    # Create a buffer to flag processed partitions
    for i in range(numrows0):
        DSTflag.append(0)
        ROOTflag.append(0)
        recoSflag.append(0)
        recoASflag.append(0)
        TMBflag.append(0)
    index=-1
    lowestpart=999
    # Loop on the raw data files and look for DSTs
    nstre=len(stream)
    for raw,id,ver,evt1,stat1 in l0:
	
# fix by hms 6-1-03
#        part=string.atoi(raw[12+nstre:15+nstre])
	fileinfo = parsefilename(raw)
	if fileinfo["type"] == "unknown":
	   continue
        part=fileinfo["partition"]
	s = fileinfo["stream"]
#	print raw,s
	if(s == "monitor"):
	    continue
        tot1=tot1+evt1

        if ( part<lowestpart ):
            lowestpart=part
        l1=infoByParent(sql,id,version,tier='reconstructed')
        numrows1=len(l1)
        index=index+1
        if ( versionGreater(version,'p13.01') ):
            lT=infoByParent(sql,id,version,tier='thumbnail')
            numrowsT=len(lT)
            if ( numrowsT==0 ):
                htmlrun.write('No <FONT COLOR="#000055">thumbnail</FONT> available for   <FONT COLOR="#0000FF">%s</FONT>  %7d\n'%(raw,evt1))
                misT=misT+evt1
                erro=erro+1
            else:
                totT=totT+evt1
                TMBflag[index]=TMBflag[index]+1
        if ( numrows1==0 ):
            htmlrun.write('No <FONT COLOR="#0000DD">DST</FONT> available for         <FONT COLOR="#0000FF">%s</FONT>  %7d\n'%(raw,evt1))
            mis2=mis2+evt1
            mis3=mis3+evt1
            mis4=mis4+evt1
            mis5=mis5+evt1
            erro=erro+1
        else:
            # DST found, now look for ROOT tuples
            if ( debug and numrows1>0 ):
                sys.stderr.write('Number of DST found for file %s: %d\n'%(raw,numrows1))
            recolist=[]
            rootgenerated=0
            for reco,nid,evt2,stat2,vers2 in l1:
                reconovers=reco.replace(vers2,'VERSION')
                if ( reco[0:5+nstre]=='reco_%s'%(stream) ):
                    DSTflag[index]=DSTflag[index]+1
                    l2=infoByParent(sql,nid,version,tier='root-tuple')
                    numrows2=len(l2)
                    if not reconovers in recolist: 
                        recolist.append(reconovers)
                        tot2=tot2+evt2
                        for root,rid,evt3,stat3,vers3 in l2:
                            if ( root[0:11+nstre]=='recoA_reco_%s'%(stream) ):
                                rootgenerated=1
                                ROOTflag[index]=ROOTflag[index]+1
                                rootnovers=root.replace(vers3,'VERSION')
                                if not rootnovers in otp:
                                    tot3=tot3+evt3
                                    otp.append(rootnovers)
                    else:
                        multiDST=1
                        if ( debug ):
                            sys.stderr.write('DST file %s has %d daughters \n'%(reco,numrows2))
                        for root,rid,evt3,stat3,vers3 in l2:
                            if ( root[0:11+nstre]=='recoA_reco_%s'%(stream) ):
                                rootnovers=root.replace(vers3,'VERSION')
                                if ( rootgenerated==0 ):
                                    rootgenerated=1
                                    ROOTflag[index]=ROOTflag[index]+1
                                    if not rootnovers in otp:
                                        tot3=tot3+evt3
                                        otp.append(rootnovers)
            if ( rootgenerated==0 and not versionGreater(version,'p13.01') ): 
                for reco,nid,evt2,stat2,vers2 in l1:
                    htmlrun.write('No <FONT COLOR="#0000BB">ROOT</FONT> tuple available for  <FONT COLOR="#0000DD">%s</FONT>  %7d\n'%(reco,evt2))
                    mis3=mis3+evt2
                    erro=erro+1
            # DST found now look for recoS files
            if ( versionGreater(version,'p10.11') and not versionGreater(version,'p13.01') ):
                l3=infoByParent(sql,id,version,tier='filtered-reco')
                numrows3=len(l3)
                if ( numrows3==0 ):
                    htmlrun.write('No <FONT COLOR="#000099">recoS</FONT> available for       <FONT COLOR="#0000FF">%s</FONT>  %7d\n'%(raw,evt1))
                    mis4=mis4+evt1
                    erro=erro+1
                else:
                    for frec,nid,evt4,stat4,vers4 in l3:
                        if ( frec[0:6+nstre]=='recoS_%s'%(stream) ):
                            recoSflag[index]=recoSflag[index]+1
                            if not frec in ost:
                                tot4=tot4+evt4
                                ost.append(frec)
            # DST found now look for ROOT tuples corresponding to the recoS files
            if ( versionGreater(version,'p10.11') and not versionGreater(version,'p13.01') ):
                l4=infoByParent(sql,id,version,tier='filtered-root')
                numrows4=len(l4)
                if ( numrows4==0):
                    htmlrun.write('No <FONT COLOR="#000077">recoA_recoS</FONT> available for <FONT COLOR="#0000FF">%s</FONT>  %7d\n'%(raw,evt1))
                    mis5=mis5+evt1
                    erro=erro+1
                else:
                    for frot,rid,evt5,stat5,vers5 in l4:
                        if ( frot[0:12+nstre]=='recoA_recoS_%s'%(stream) ): 
                            recoASflag[index]=recoASflag[index]+1
                            if not frot in osr:
                                tot5=tot5+evt5
                                osr.append(frot)
    # Check whether the processing really started 
    if ( tot2==0 ):
        if (len(queued)>0 ):
            if not string.atoi(run) in queued:
                processingSTARTED=0
    # Summary of the processing
    # if ( erro!=0 ):
    htmlrun.write('------------------------------------------------------------\n')
    htmlrun.write('Partitions processing status for run number %7d\n'%(string.atoi(run)))
    htmlrun.write('------------------------------------------------------------\n')
    if ( lowestpart==1 ):
        htmlrun.write('                                                                                                                1\n')
        htmlrun.write('                      1111111111222222222233333333334444444444555555555566666666667777777777888888888899999999990\n')
        htmlrun.write('             1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\n')
    elif ( lowestpart==0 ):
        htmlrun.write('                       111111111122222222223333333333444444444455555555556666666666777777777788888888889999999999\n')
        htmlrun.write('             0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n')
    htmlrun.write('             ----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+\n')
    htmlrun.write('DST          ')
    for i in range(numrows0):
        if ( i>0 and i%100==0 ):
            htmlrun.write('\n             ')
        if ( DSTflag[i]==1 ): 
            htmlrun.write('1')
        else:
            htmlrun.write('<FONT COLOR="#FF0000">%1d</FONT>'%(DSTflag[i]))
    if ( not versionGreater(version,'p13.01') ):
        htmlrun.write('\nROOT         ')
        for i in range(numrows0):
            if ( i>0 and i%100==0 ):
                htmlrun.write('\n             ')
            if ( ROOTflag[i]==1 ): 
                htmlrun.write('1')
            else:
                htmlrun.write('<FONT COLOR="#FF0000">%1d</FONT>'%(ROOTflag[i]))
    if ( versionGreater(version,'p10.11') and not versionGreater(version,'p13.01') ):
        htmlrun.write('\nrecoS        ')
        for i in range(numrows0):
            if ( i>0 and i%100==0 ):
                htmlrun.write('\n             ')
            if ( recoSflag[i]==1 ): 
                htmlrun.write('1')
            else:
                htmlrun.write('<FONT COLOR="#FF0000">%1d</FONT>'%(recoSflag[i]))
    if ( versionGreater(version,'p10.11') and not versionGreater(version,'p13.01') ):
        htmlrun.write('\nrecoAS       ')
        for i in range(numrows0):
            if ( i>0 and i%100==0 ):
                htmlrun.write('\n             ')
            if ( recoASflag[i]==1 ): 
                htmlrun.write('1')
            else:
                htmlrun.write('<FONT COLOR="#FF0000">%1d</FONT>'%(recoASflag[i]))
    if ( versionGreater(version,'p13.01') ):
        htmlrun.write('\nrecoT        ')
        for i in range(numrows0):
            if ( i>0 and i%100==0 ):
                htmlrun.write('\n             ')
            if ( TMBflag[i]==1 ):
                htmlrun.write('1')
            else:
                htmlrun.write('<FONT COLOR="#FF0000">%1d</FONT>'%(TMBflag[i]))
    htmlrun.write('\n')
    htmlrun.write('             ----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+\n')
    htmlrun.write('------------------------------------------------------------\n')
    htmlrun.write('SAM summary for run %7d\n'%(string.atoi(run)))
    htmlrun.write('------------------------------------------------------------\n')
    htmlrun.write('Total number of events (raw data)                    %7d\n'%(tot1))
    htmlrun.write('Total number of events (DST)                         %7d\n'%(tot2))
    if ( not versionGreater(version,'p13.01') ):
        htmlrun.write('Total number of events (ROOT tuple)                  %7d\n'%(tot3))
    if ( versionGreater(version,'p10.11') and not versionGreater(version,'p13.01') ):
        htmlrun.write('Total number of events (recoS stream)                %7d\n'%(tot4))
    if ( versionGreater(version,'p10.11') and not versionGreater(version,'p13.01') ):
        htmlrun.write('Total number of events (recoS stream, ROOT tuple)    %7d\n'%(tot5))
    if ( versionGreater(version,'p13.01') ):
        htmlrun.write('Total number of events (thumbnail)                   %7d\n'%(totT))
    htmlrun.write('------------------------------------------------------------\n')
    if ( mis2>0 ):
        htmlrun.write('<FONT COLOR="#FF0000">')
        htmlrun.write('Non D0recoed events (DST not generated)              %7d'%(mis2))
        htmlrun.write('</FONT>\n')
    if ( mis2+tot2!=tot1):
        htmlrun.write('<FONT COLOR="#AA7700">')
        htmlrun.write('===> Inconsistency in the number of events in the DST')
        htmlrun.write('</FONT>\n')
        DSTcheck=1
    if ( not versionGreater(version,'p13.01') ):
        if ( mis3>0 ):
            htmlrun.write('<FONT COLOR="#FF0000">')
            htmlrun.write('Non RecoAnalyzed events (ROOT tuple not generated)   %7d'%(mis3))
            htmlrun.write('</FONT>\n')
        if ( mis3+tot3!=tot1):
            htmlrun.write('<FONT COLOR="#AA7700">')
            htmlrun.write('===> Inconsistency in the number of events in the ROOT tuple')
            htmlrun.write('</FONT>\n')
            ROOTcheck=1
        if ( versionGreater(version,'p10.11') ):
            if ( mis4>0 ):
                htmlrun.write('<FONT COLOR="#FF0000">')
                htmlrun.write('Non filtered events (recoS not generated)            %7d'%(mis4))
                htmlrun.write('</FONT>\n')
        if ( versionGreater(version,'p10.11') ):
            if ( mis5>0 ):
                htmlrun.write('<FONT COLOR="#FF0000">')
                htmlrun.write('Non filtered events (recoA_recoS not generated)      %7d'%(mis5))
                htmlrun.write('</FONT>\n')
            if ( tot4!=tot5 and tot5>0 ):
                htmlrun.write('<FONT COLOR="#AA7700">')
                htmlrun.write('===> Inconsistency in the number of events in the filtered ROOT tuple')
                htmlrun.write('</FONT>\n')
                FROOTcheck=1
    else: 
        if ( misT>0 ):
            htmlrun.write('<FONT COLOR="#FF0000">')
            htmlrun.write('Non D0recoed (thumbnail not generated)               %7d'%(misT))
            htmlrun.write('</FONT>\n')
        if ( misT+totT!=tot1):
            htmlrun.write('<FONT COLOR="#AA7700">')
            htmlrun.write('===> Inconsistency in the number of events in the thumbnail')
            htmlrun.write('</FONT>\n')
            TMBcheck=1
    if ( mis2+mis3+mis4+mis5+(tot4-tot5)+misT==0 and DSTcheck==0 and ROOTcheck==0 and TMBcheck==0 ):
        htmlrun.write('<FONT COLOR="#009900">')
        htmlrun.write('Run %7d was completely processed'%(string.atoi(run)))
        htmlrun.write('</FONT>\n')
    htmlrun.write('------------------------------------------------------------\n')
    # Event checksum fail, look for inconsistencies
    raw2DST='No inconsistencies'
    if ( DSTcheck==1 ):                        
        checkDST(htmlrun,sql,run,version)
        raw2DST='Inconsistent number of events in D0reco output (DST format)'
    DST2ROOT='No inconsistencies'
    if ( ROOTcheck==1 and not versionGreater(version,'p13.01') ):
        checkROOT(htmlrun,sql,run,version)
        DST2ROOT='Inconsistent number of events in RecoAnalyze output'
    recoS2ROOT='No inconsistencies'
    if ( FROOTcheck==1 and versionGreater(version,'p10.14') and not versionGreater(version,'p13.01') ):
        # checkFROOT(htmlrun,sql,run,version)
        recoS2ROOT='Inconsistent number of events in RecoAnalyze output of filtered events'
    raw2TMB='No inconsistencies'
    if ( TMBcheck==1 ):                        
        checkTMB(htmlrun,sql,run,version)
        raw2TMB='Inconsistent number of events in D0reco output (thumbnail format)'
    # Check that no file was skipped in the merging process
    mergeROOT=checkMerge(htmlrun,sql,run,stream,lowestpart,version,ROOTflag,tier='root-tuple')
    mergerecoS=0
    mergerecoAS=0
    mergeTMB=0 
    #if ( versionGreater(version,'p10.11') ):
    #    mergerecoS=checkMerge(htmlrun,sql,run,stream,lowestpart,version,recoSflag,tier='filtered-reco')
    #if ( versionGreater(version,'p10.11') ):
    #    mergerecoAS=checkMerge(htmlrun,sql,run,stream,lowestpart,version,recoASflag,tier='filtered-root')
    if ( versionGreater(version,'p13.01') ):
        mergeTMB=checkMerge(htmlrun,sql,run,stream,lowestpart,version,TMBflag,tier='thumbnail')
    htmlrun.write('</PRE>\n')
    # Write a compressed summary
    htmlrun.write('<!-- BEGIN SUMMARY\n')
    fmis2=0.
    fmis3=0.
    fmis4=0.
    fmis5=0.
    fmisT=0.
    if ( tot1>0 ):
        fmis2=100.*(1-float(mis2)/float(tot1))
        fmisT=100.*(1-float(misT)/float(tot1))
        if ( not versionGreater(version,'p13.01') ):
            fmis3=100.*(1-float(mis3)/float(tot1))
            fmis4=100.*(1-float(mis4)/float(tot1))
            fmis5=100.*(1-float(mis5)/float(tot1))
    htmlrun.write('Run                    %7d\n'%(string.atoi(run)))
    htmlrun.write('Date                   %s\n'%(startdate))
    htmlrun.write('Trigger configuration  %s\n'%(trigger))
    htmlrun.write('Data stream            %s\n'%(stream))
    htmlrun.write('Raw data events        %7d\n'%(tot1))
    htmlrun.write('DST events             %7d    ( %6.2f %% of the total )   %s\n'%(tot2,fmis2,raw2DST))
    if ( not versionGreater(version,'p13.01') ):
        htmlrun.write('ROOT events            %7d    ( %6.2f %% of the total )   %s\n'%(tot3,fmis3,DST2ROOT))
        htmlrun.write('RecoS events           %7d    ( %6.2f %% of the total )     \n'%(tot4,fmis4))
        htmlrun.write('RecoAS events          %7d    ( %6.2f %% of the total )   %s\n'%(tot5,fmis5,recoS2ROOT))
    else: 
        htmlrun.write('thumbnail events       %7d    ( %6.2f %% of the total )   %s\n'%(totT,fmisT,raw2TMB))
    if ( tot1>1 ):
        incomplete=mis2+mis3+mis4+mis5
        inconsistent=DSTcheck+ROOTcheck+FROOTcheck+TMBcheck
        mergeprob=mergeROOT+mergerecoS+mergerecoAS+mergeTMB
        problems=incomplete+inconsistent+mergeprob
        if ( problems ):
            htmlrun.write('Problems found in the processing:\n')
        else:
            htmlrun.write('No problem found - Processing of run %7d completed\n'%(string.atoi(run)))
        if ( incomplete ): 
            htmlrun.write('    not all events have been processed\n')
        if ( inconsistent ):
            htmlrun.write('    inconsistent number of events at different steps of the processing\n')
        if ( mergeprob ):
            if ( not versionGreater(version,'p13.01') ):
                htmlrun.write('    merging errors (ROOT tuples or filtered events)\n')
            else:
                htmlrun.write('    merging errors (thumbnail)\n')
        if ( len(queued)>0 ):
            if ( tot2==0 and processingSTARTED==0 ):
                htmlrun.write('Farm jobs not queued\n')
            else:
                if ( tot2>0 ):
                    htmlrun.write('Farm jobs finished or running\n')
                else:
                    htmlrun.write('Farm jobs queued\n')
        else:
            htmlrun.write('Farm jobs not queued\n')
    else:
        htmlrun.write('Run %7d ignored - too few events %7d\n'%(string.atoi(run),tot1))
    htmlrun.write('END SUMMARY -->\n')
    htmlrun.write('<HR>\n')
    htmlrun.write('<I>This page was created by MINTS using the information in the SAM and Runs databases</I>\n')
    htmlrun.write('<BR>\n')
    currentdate=time.strftime('%a %b %d %Y at %H:%M:%S',time.localtime(time.time()))
    htmlrun.write('<I>MINTS updated this page on %s</I>\n'%(currentdate))
    htmlrun.close()
    sys.stdout.write('Created the web page for run %7d processing version %6s\n'%(string.atoi(run),version[0:6]))
    sys.stdout.write('------> %s\n'%(htmlfile))
    if multiDST:
        sys.stdout.write('------> some partitions have been processed more than once !!!! \n')

    return

#
# Define some operators on version numbers
#
def versionGreater(version1,version2):
    v1=string.atof(version1[1:6])
    v2=string.atof(version2[1:6])
    return v1>v2
    
#
# Print an help screen
# 
def usage():
    sys.stderr.write('checkRunInfo.py\n\n')
    sys.stderr.write('check the consistency of the information for runs in the SAM database\n')
    sys.stderr.write('Options:\n')
    sys.stderr.write('\t-h,--help\t\tThis information\n')
    sys.stderr.write('\t-r,--run\t\tThe run number of interest\n')
    sys.stderr.write('\t-b,--beginrun\t\tThe first run number of interest\n')
    sys.stderr.write('\t-e,--endrun\t\tThe last run number of interest\n')
    sys.stderr.write('\t-l,--list\t\tThe list of run numbers of interest (use all to process all runs between the two extremes given by the -b and -e options) \n')
    sys.stderr.write('\t-v,--version\t\tThe version of the D0 software used for processing (use % for accessing multiple versions)\n')
    sys.stderr.write('\t-d,--debug\t\tPrint some debug information\n')
    sys.stderr.write('\t-q,--queuecheck\t\tCheck jobs currently running on the farms\n')
    sys.stderr.write('\t-w,--wwwdirectory\t\tDirectory in which the HTML files are stored\n')
    return
    
def main():

    if ( os.environ['USER']!='mverzocc' and os.environ["USER"]!='schellma' ):
        sys.stderr.write('The checkRunInfo.py script should not be run by a generic user\n')
        sys.stderr.write('since it uses a Oracle licence. If you really need to run this\n')
        sys.stderr.write('script, please contact mverzocc@fnal.gov\n')
        sys.stderr.write('The checkRunInfo.py script is run automatically once a night\n')
        sys.stderr.write('and there should be no need to run it more frequently than that\n')
        usage()
        sys.exit(2)

    try:
        opts, args = getopt.getopt(sys.argv[1:], "hr:v:l:e:b:dqw:",
                                   ["help",
                                    "run="])
    except getopt.GetoptError:
        usage()
        sys.exit(2)

    samdbc = dcoracle.Connect ("samread/reader@d0ofprd1")
    sql=Sqlbase (samdbc)
    
    htmldir=os.getcwd()
    listofruns=[]
    listofversions=[]
    listofstreams=[]
    listoftriggers=[]
    listofdates=[]
    firstrun=0
    lastrun=99999999
    debug=0
    checkqueue=0

    for o,a in opts:
        if o in ("-h", "--help"):
            usage()
            sys.exit()

        if o in ("-r","--run"):
            listofruns.append(a)

        if o in ("-e","--endrun"):
            lastrun=a

        if o in ("-b","--beginrun"):
            firstrun=a

        if o in ("-l","--list"):
            if ( a!='all' ):
                file=open(a,"r")
                for line in file.readlines():
                    listofruns.append(string.strip(line))
                file.close
            else:
                listofruns.append('all')

        if o in ("-v","--version"):
            listofversions.append(a)

        if o in ("-d","--debug"):
            debug=1
 
        if o in ("-q","--queuecheck"):
            checkqueue=1

        if o in ("-w","--wwwdirectory"):
            htmldir=a

    if ( listofruns[0]=='all' ):
        listofruns=[]
#	print infoGetRunsDBbyRunTrigger(sql,firstrun,lastrun,trigger='official%')
        for run,stream,trigname,trigvers,startdate in infoGetRunsDBbyRunTrigger(sql,firstrun,lastrun,trigger='official/global%'):
	    if(stream == "monitor"):
		continue
            listofruns.append('%s'%(run))
            listofstreams.append(stream)
            trigger='%s_%s'%(trigname,trigvers)
            listoftriggers.append(trigger)
            listofdates.append(startdate)
    else:
        for run in listofruns:
            for run1,stream,trigname,trigvers,startdate in infoGetRunsDBbyRun(sql,run):
		if(stream == "monitor"):
		    continue
                listofstreams.append(stream)
                trigger='%s_%s'%(trigname,trigvers)
                listoftriggers.append(trigger)
                listofdates.append(startdate)

    if ( listofversions[0]=='all'):
        listofversions=[]

    for version in listofversions:
        queued=[]
        if checkqueue:
            queued=infoRunsInQueue(sql,version)
        i=-1
        for run in listofruns:
            i=i+1
            trigger=listoftriggers[i]
            stream=listofstreams[i]
            startdate=listofdates[i]
            doOneRun(debug,htmldir,sql,run,trigger,stream,version,startdate,queued)

    del sql
    samdbc.close()

def parsefilename(filename):
    list = string.split(filename,".")
    if len(list) < 1:
	return {"type":"unknown"}
    if list[len(list)-1] == "raw":
# this is probably a raw file with format stream_run_part
         newlist = string.split(list[0],"_")
	 n = len(newlist)
	 if(n<2):
	     print "bad file name ", filename
	     return {"type":"unknown"}
	 istream = newlist[0]
	 i = 1
	 while i < n -2:
	     istream = istream + "_" + newlist[i]
	     i = i + 1

	 return {"type":"raw","stream":istream,"run":string.atoi(newlist[n-2]),"partition":string.atoi(newlist[n-1])}

    return {"type":"new"}

main()
