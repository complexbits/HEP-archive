#!/usr/bin/env python
# -----------------------------------------------------------------------------------
# A script to produce a map between L3 trigger names and L1 and L3 trigger bit 
# numbers, reading this information from the runs database.
#
# Syntax:  makeL1L3TrigMap.py [ -run RunNumber | -runlist RunNumberList | 
#                               -runrange RunNumber1,RunNumber2 ]
#                             [ -map L1L3TrigMap ] [ -help ]
#          where 
#               -run        produces the trigger map for a single run number given
#                           by RunNumber 
#                                    
#               -runlist    produces the trigger map for all the runs specified in
#                           the input list RunNumberList (one entry per run)
#                                       
#               -runrange   produces the trigger map for all the runs between
#                           RunNumber1 and RunNumber2 (including the extremes)
#                           (very fast, but no check on the completeness of the
#                           trigger map)
# 
#               -map        save the map in the file specified by L1L3TrigMap
#                           (by default the output is sent to stdout). If the
#                           file specified by L1L3TrigMap is already existing
#                           it is opened in append mode (but duplicate entries
#                           are removed).
#
#               -onlineDB   use the online data base, instead of the offline mirror
#
#               -help       print this help screen
#
# To use this script you need to setup python and oracle:
# $> setup python_dcoracle 
# $> makeL1L3TrigMap.py .......
#
# Provided you have a recent python installation, you should be able 
# to run this script everywhere
#
# Author:  Marco Verzocchi (mverzocc@fnal.gov) x5252
# Created: 10/16/2001 
#
# Changes: 10/17/2001 - Convert to use DCOracle to query the database
#                       (using an example script from Emmanuelle Perez) 
#          10/18/2001 - Use the offline database instead of the online DB
#                       but add an option to revert to the online DB
#                       Check that the dcoracle is available, print
#                       an error message in case of problems
#          10/29/2001 - Replace all print statements with sys.stderr.write
#                       Correct one minor bug (only occurred in case of errors)
#          10/31/2001 - Minor improvements in the printouts
# 
# -----------------------------------------------------------------------------------

import os
import sys
import string
try:
  import dcoracle
except:
  sys.stderr.write('\nmakeL1L3TrigMap: to use this script you need the dcoracle module for Python\n')
  sys.stderr.write('                 type setup python_dcoracle and then rerun the script\n\n') 
  sys.exit(2)
  
#------------------------------------------------------------
# Data base coordinates.
#------------------------------------------------------------
runsOnlineDB='d0onprd'
runsOfflineDB='d0ofprd1'
runsUsername='d0read'
runsPassword='reader'

#------------------------------------------------------------
# Maximum number of run queries for a single SQL query:
# maxListRuns controls the queries of the type .. OR .. OR ..
# maxRangeRuns controls the queries of the type > .. AND <..
#------------------------------------------------------------
maxListRuns=50
maxRangeRuns=200

def usage():
#------------------------------------------------------------
# Print the help screen
#------------------------------------------------------------
  sys.stderr.write('\nSyntax:  makeL1L3TrigMap.py [ -run RunNumber | -runlist RunNumberList |\n')
  sys.stderr.write('                              -runrange RunNumber1,RunNumber2 ]\n')
  sys.stderr.write('                            [ -map L1L3TrigMap ] [ -help ]\n')
  sys.stderr.write('         where\n')
  sys.stderr.write('              -run        produces the trigger map for a single run number given\n')
  sys.stderr.write('                          by RunNumber\n\n')
  sys.stderr.write('              -runlist    produces the trigger map for all the runs specified in\n')
  sys.stderr.write('                          the input list RunNumberList (one entry per run)\n\n')
  sys.stderr.write('              -runrange   produces the trigger map for all the runs between\n')
  sys.stderr.write('                          RunNumber1 and RunNumber2 (including the extremes\n')
  sys.stderr.write('                          (very fast, but no check on the completeness of the\n')
  sys.stderr.write('                          trigger map)\n\n')
  sys.stderr.write('              -map        save the map in the file specified by L1L3TrigMap\n')
  sys.stderr.write('                          (by default the output is sent to stdout). If the\n')
  sys.stderr.write('                          file specified by L1L3TrigMap is already existing\n')
  sys.stderr.write('                          it is opened in append mode (but duplicate entries\n')
  sys.stderr.write('                          are removed).\n\n')
  sys.stderr.write('              -onlineDB   use the online data base, instead of the offline mirror\n\n')
  sys.stderr.write('              -help       prints this help screen\n\n')
  sys.stderr.write('To use this script you need to setup python and oracle:\n')
  sys.stderr.write('$> setup python_dcoracle\n')
  sys.stderr.write('$> makeL1L3TrigMap.py .......\n\n')
  sys.exit(2)

#------------------------------------------------------------
# The triggermap class. Methods implemented:
# ------------------ "public" -------------------------------
# __init__:       constructor
# addrunlist:     public method to add the entries for a list 
#                 of runs 
# addrunrange:    public method for adding the entries for 
#                 runs in a given run number range 
# numentries:     get the number of entries in the map
# dump:           print the trigger map on the screen
# writetofile:    write the trigger map on a file or merge
#                 it with a preexisting file
# ------------------ "private" ------------------------------
# __del__:        destructor 
# DBquery:        perform the SQL query on the Oracle 
#                 database and parse the output 
# DBconnect:      connect with the Oracle database
# DBclose:        disconnect from the Oracle database
# DBerror:        print error messages whenever a problem
#                 with the database occurs
# addlist:        actual method for adding entries for a list
#                 of runs, used from addrunlist
# addrange:       actual method for adding entries for a run
#                 number range, used from addrunrange
# queryDB:        performs the DB query, used from addlist
#                 and addrange
# addentry:       add a single entry to the map, used by 
#                 DBqueryDB
# mergetofile:    merges the trigger map created in memory
#                 with the one contained in the output file,
#                 used by writetofile 
#------------------------------------------------------------
class trigmap:

#------------------------------------------------------------
# Method to save the trigger map in a file. If the trigger
# map has to be merged with a preexisting one, create a
# list of runs contained in the old map.
#------------------------------------------------------------ 
    def mergetofile(self,filename):
      file=open(filename,"r")
      listoldruns=[]
      for line in file.readlines():    
        listoldruns.append(string.split(line)[0])
      file.close()
      file=open(filename,"a")
      newentries=0
      duplicate=0
      for entry in self.Map:
        run=string.split(entry)[0]
        if not run in listoldruns:
          file.write('%s\n'%entry)
          newentries=newentries+1
        else:
          duplicate=duplicate+1
      file.close()
      sys.stderr.write('\nmakeL1L3TrigMap: added %d new trigger maps to the file %s \n'%(newentries,filename))
      sys.stderr.write('                 out of the %d new maps created in memory'%len(self.Map))
      if duplicate > 0:
        sys.stderr.write(' %d entries were ignored'%duplicate)
      total=newentries+len(listoldruns)
      sys.stderr.write('\n\nmakeL1L3TrigMap: %s now contains the trigger maps for %d runs\n\n'%(filename,total))

#------------------------------------------------------------
# Method to save the trigger map in a file.
#------------------------------------------------------------
    def writetofile(self,filename):
      if os.path.isfile(filename):
        try:
          file=open(filename,"a")
        except:
          sys.stderr.write('\nmakeL1L3TrigMap: you requestesed to merge the trigger map with the one\n')
          sys.stderr.write('                 contained in %s but the file cannot be accessed\n'%filename)
          filename=filename+'.new'
          sys.stderr.write('                 in append mode - writing a new map to %s instead\n\n'%filename)
        else:
          self.mergetofile(filename)
          return      
      try:
        file=open(filename,"w")
      except:
        sys.stderr.write('\nmakeL1L3TrigMap: you cannot create the file %s\n'%filename)
        sys.stderr.write('                 dump the triggermap on the screen\n\n')
        self.dump()
      else:
        for entry in self.Map:
          file.write('%s\n'%entry)
        sys.stderr.write('\nmakeL1L3TrigMap: written %d entries to %s\n\n'%(len(self.Map),filename))

#------------------------------------------------------------
# Method to sys.stderr.write( the trigger map on the screen 
#------------------------------------------------------------
    def dump(self):
      for entry in self.Map:
        sys.stdout.write(entry+'\n')

#------------------------------------------------------------
# Method to get the trigger map for a list of runs: split
# the list in chunks of 50 runs at a time (maxListRuns).
#------------------------------------------------------------
    def addrunlist(self,listofruns):
      bignumofruns=len(listofruns)
      if bignumofruns > maxListRuns:
        nchunks=bignumofruns/maxListRuns
        i=0
        while i < nchunks+1:
          index1=maxListRuns*i
          index2=maxListRuns*(i+1)
          if index2 > bignumofruns:
            index2=bignumofruns
          shortlist=listofruns[index1:index2]
          self.addlist(shortlist)
          i=i+1
      else:
        self.addlist(listofruns)
 
#------------------------------------------------------------
# Method to get the trigger map for a list of runs: build 
# the lynx command which is used to query the database
#------------------------------------------------------------
    def addlist(self,shortlist):
      numofruns=len(shortlist)
      self.SQLquery="select run_number,bit_name,depend_bit,bit_num from runs.run_trigs where ( ( run_number = "
      i=0
      while i < numofruns-1:
        self.SQLquery=self.SQLquery+"'%d' or run_number = "%(string.atoi(shortlist[i]))
        i=i+1
      self.SQLquery=self.SQLquery+"'%d' ) and trg_type = 'L3bit' ) order by run_number ASC"%(string.atoi(shortlist[i]))
      self.DBquery('check',numofruns)

#------------------------------------------------------------
# Method to get the trigger map for a range of runs: split
# the list in chunks of 200 runs at a time (maxRangeRuns).
#------------------------------------------------------------
    def addrunrange(self,runrange):
      firstrun=string.atoi(runrange[0])
      lastrun=string.atoi(runrange[1])
      nentries=lastrun-firstrun+1
      nchunks=nentries/maxRangeRuns
      i=0 
      while i < nchunks+1:
        index1=firstrun+maxRangeRuns*i
        index2=index1+maxRangeRuns-1
        if index2 > lastrun:
          index2=lastrun
        self.addrange(index1,index2)
        i=i+1

#------------------------------------------------------------
# Method to get the trigger map for a range of runs: build
# the lynx command which is used to query the database
#------------------------------------------------------------
    def addrange(self,firstrun,lastrun):
      nentries=lastrun-firstrun+1
      self.SQLquery="select run_number,bit_name,depend_bit,bit_num from runs.run_trigs where ( run_number >= '%d' and run_number <= '%d' and trg_type = 'L3bit' ) order by run_number ASC"%(firstrun,lastrun)
      self.DBquery('no_check',nentries)

#------------------------------------------------------------
# Parse the output of the database query
#------------------------------------------------------------
    def DBquery(self,check,expected):
      try:
        self.cursor.execute(self.SQLquery)
      except:
        self.DBerror('query_failed')
      try:
        DBQueryResult=self.cursor.fetchall()
      except:
        self.DBerror('no_result') 
      entry=''
      numrows=len(DBQueryResult)
      runnum=-1
      foundentries=0
      for i in range(numrows):
        if entry == '':
          runnum=DBQueryResult[i][0]
          entry="%s"%runnum+" "
          for j in range(3):
            entry=entry+"%s"%DBQueryResult[i][j+1]+" "
        else:
          if DBQueryResult[i][0]==runnum:
            for j in range(3):
              entry=entry+"%s"%DBQueryResult[i][j+1]+" "
          else:
            entry=entry+"#"
            self.addentry(entry)
            foundentries=foundentries+1
            runnum=DBQueryResult[i][0]
            entry="%s"%runnum+" "
            for j in range(3):
              entry=entry+"%s"%DBQueryResult[i][j+1]+" "
      if not runnum == -1:
        entry=entry+"#"
        self.addentry(entry) 
        foundentries=foundentries+1
      if check == 'check' and foundentries != expected :
        sys.stderr.write('\nmakeL1L3TrigMap: MISWEB query returns an incomplete trigger map\n')
        sys.stderr.write('                 found only %d runs out of the %d expected\n'%(foundentries,expected))
        sys.stderr.write('                 not updating the trigger map - abort execution\n\n')
        sys.exit(1)


#------------------------------------------------------------
# Connect to the database
#------------------------------------------------------------
    def DBconnect(self,connection):
      try: 
        self.dbconn=dcoracle.Connect(connection) 
      except:
        self.DBerror('no_connection')
      try: 
        self.cursor=self.dbconn.cursor()
      except:
        self.DBerror('no_cursor')

#------------------------------------------------------------
# Close the database connection
#------------------------------------------------------------     
    def DBclose(self):
      try:
        self.cursor.close()
      except:
        self.DBerror('closing')
        
#------------------------------------------------------------
# Database errors
#------------------------------------------------------------      
    def DBerror(self,type):
      if type == 'no_connection':
        sys.stderr.write('\nmakeL1L3TrigMap: failed to connect to the Oracle database using:\n')
        sys.stderr.write('                 database %s\n'%runsDBServer)
        sys.stderr.write('                 username %s\n'%runsUsername)
        sys.stderr.write('                 password %s\n'%runsPassword)
      elif type == 'no_cursor':
        sys.stderr.write('\nmakeL1L3TrigMap: failed to get the cursor from Oracle\n')
      elif type == 'query_failed':
        sys.stderr.write('\nmakeL1L3TrigMap: database query failed\n')
        sys.stderr.write('                 did you type setup python_dcoracle ?\n')
      elif type == 'no_result':
        sys.stderr.write('\nmakeL1L3TrigMap: the database query returned an empty result\n')
      elif type == 'closing':
        sys.stderr.write('\nmakeL1L3TrigMap: error while closing the connection to Oracle\n')
      else:
        sys.stderr.write('\nmakeL1L3TrigMap: unknown error in using the database\n')
      sys.stderr.write('\nmakeL1L3TrigMap: error message from Oracle:\n\n')
      sys.stderr.write(sys.exc_value)
      sys.stderr.write('\nmakeL1L3TrigMap: abort execution\n\n')
      sys.exit(2)

#------------------------------------------------------------
# Add the entry to the map
#------------------------------------------------------------
    def addentry(self,entry):
      newmapentry=('%s')%entry
      self.Map.append(newmapentry)
 
#------------------------------------------------------------
# Get the number of entries in the map
#------------------------------------------------------------
    def numentries(self):
      return len(self.Map)

#------------------------------------------------------------
# Class destructor
#------------------------------------------------------------
    def __del__(self):
      self.DBclose()

#------------------------------------------------------------
# Construct a new empty map
#------------------------------------------------------------
    def __init__(self):
      self.Map=[]
      self.dbconn=''
      self.cursor=''
      self.SQLquery=''

#------------------------------------------------------------
# The start of the script 
#------------------------------------------------------------
if __name__ == '__main__':
    
#------------------------------------------------------------
# Parse the command line
#------------------------------------------------------------
  args=sys.argv[1:]

#------------------------------------------------------------
# Print the help message
#------------------------------------------------------------
  if "-help" in args:
    sys.stderr.write('\nmakeL1L3TrigMap.py: a tool to build the L1/L3 trigger map for use in the LM_ACCESS package\n')
    usage()

#------------------------------------------------------------
# Ccheck whether the offline (default) or online DB should
# be used for the run queries 
#------------------------------------------------------------
  runsDBServer=runsOfflineDB
  if "-onlineDB" in args:
    runsDBServer=runsOnlineDB
  DBconnection=runsUsername+'/'+runsPassword+'@'+runsDBServer

#------------------------------------------------------------
# Create a trigger map in memory
#------------------------------------------------------------
  L1L3TriggerMap=trigmap()
  L1L3TriggerMap.DBconnect(DBconnection)
  RequestNewRuns=0

#------------------------------------------------------------
# Fill the trigger map either with a single run or with a
# list of runs read from a file. The same method is applied
# in both cases (an SQL request which contains the or of
# all the run numbers)
#------------------------------------------------------------
  ListOfRuns=[]
  if "-run" in args:
    ListOfRuns.append(args[args.index("-run")+1]),
    del args[args.index("-run"):args.index("-run")+2]
  if "-runlist" in args:
    runlist=args[args.index("-runlist")+1]
    del args[args.index("-runlist"):args.index("-runlist")+2]
    file=open(runlist,"r")
    for line in file.readlines():
      ListOfRuns.append(line), 
    file.close
  if not ListOfRuns == []:
    RequestNewRuns=1
    L1L3TriggerMap.addrunlist(ListOfRuns)

#------------------------------------------------------------
# Fill the trigger map using a run range. This is not the
# recommended option because it does not allow any check
# on the integrity of the map returned by MISWEB. On the
# other hand it allows a very fast access to the database 
#------------------------------------------------------------
  if "-runrange" in args:
    RunRange = string.split(args[ args.index("-runrange")+1 ], ',')
    del args[ args.index("-runrange"):args.index("-runrange")+2 ] 
    RequestNewRuns=1
    if len(RunRange) != 2:
      sys.stderr.write('\nmakeL1L3TrigMap: syntax error - you must specify two run numbers withe the -runrange\n')
      sys.stderr.write('                 option, separated by a comma, like -runrange 129194,132026\n')
      usage()
    L1L3TriggerMap.addrunrange(RunRange)
 
#------------------------------------------------------------ 
# Check that the map has been filled, otherwise stop
#------------------------------------------------------------ 
  if L1L3TriggerMap.numentries() == 0:
    sys.stderr.write('\nmakeL1L3TrigMap: no entries in the trigger map\n')
    if RequestNewRuns == 0:
      sys.stderr.write( '                 use the -run, -runlist or -runrange options to specify a set of runs\n')
      sys.stderr.write( '                 for which the trigger map should be downloaded from the database\n\n')
      usage()
    else:
      sys.stderr.write( '                 failed to find the trigger maps for the specified input runs\n\n')
      sys.exit(1)

#------------------------------------------------------------ 
# Write or append the map to a file or dump it on the screen
#------------------------------------------------------------ 
  if "-map" in args:
    FileMap=args[args.index("-map")+1] 
    del args[args.index("-map"):args.index("-map")+2]
    L1L3TriggerMap.writetofile(FileMap)
  else:
    L1L3TriggerMap.dump()

#------------------------------------------------------------ 
# End of the script
#------------------------------------------------------------ 
  sys.exit(0)

