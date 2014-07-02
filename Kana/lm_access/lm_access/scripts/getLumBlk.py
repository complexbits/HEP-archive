#!/usr/bin/env python
import os,time,sys,string
import file_client
import SAMDbServer
import getopt
from getFileParentsRecursive import getFileParentsRecursive


# trace files back to raw data and find the luminosity related info.

from posixpath import exists


# try to find a file in cache then db

def getLumBlk(file,cache):


    result1 = getCacheFileInfo(file,cache)
    if (result1[0] != "OK"):
       result2 = getFileRawInfo(file)
       if ( result2[0] != "OK"):
          sys.stderr.write('No information available in SAM for file %s - reason %s\n'%(file,result2[0]))
       else:
          print formatOutput(file,result2)	    
    else:
       print result1[1]



# here is the cache code

def getCacheFileInfo(filename,cachefile):
#    print "using the cache"
    command = "grep %s %s" %(filename,cachefile)
    result = os.popen(command).readlines()
    if(len(result) == 0):
       return ["NOT IN CACHE FILE"]
    if(len(result) >= 1):
	return ["OK",string.strip(result[0])]

# here is the db code, traces back through parentage

def getFileRawInfo(filename):

    sys.stderr.write('Information on %s not available in cache - access SAM database\n'%filename)
    filename = os.path.split(filename)[1]
    run = -1
    try:
	    fileinfo = file_client.APIGetFileInfo(filename)
    except SAMDbServer.DBError, oerr:
	    sys.stderr.write('**** Terminating execution due to database error\n')
	    return ["DBError"]
    except SAMDbServer.DataFileNotFound:
	    # sys.stderr.write('File not found %s\n'%filename)
	    return ["NoSuchFile"]
    event_count = fileinfo.eventCount
    data_tier = fileinfo.dataTier

# raw data, just get and return

    if(type == "raw"):
    
	run = fileinfo.runNumber
	lumMin = fileinfo.lumMin
	lumMax = fileinfo.lumMax
        return ["OK","raw",raw_count,0,-1,[[run,lumMin,lumMax,raw_count]]]

# other data, find parent raw files, return info for them

    if(type != "raw"):
	result = [filename]
	status = getFileParentsRecursive(result)
#	print " result of getFileParents" ,status
	if(status  != "OK"):
	    return [status]

	sortunique(result)
	reco_events = event_count
	raw_events = 0
	lumInfo = []
	for file in result:
#	    print file
#	    raw_events = raw_events + getFileEvents(file)
	    test = getLumInfo(file)
	    if(test[0] != "OK"):
		return 
	    else:
		raw_events = raw_events + test[1][3]
		lstuff = test[1]
		if len(lumInfo) > 0:
		    estuff = lumInfo[-1]
		    if estuff[2] == lstuff[1]-1 and estuff[0] == lstuff[0]:
			lumInfo[-1][2] = lstuff[2]
			lumInfo[-1][3] = lumInfo[-1][3]+lstuff[3]
		    else:
			lumInfo = lumInfo+[lstuff]
		else:
		    lumInfo = [lstuff]

	return [status, data_tier,raw_events,0,reco_events,lumInfo]

    else:
	return ["Bad file type"]

# utility

def sortunique(list):
    list.sort()
    n = len(list)
    if(n < 2):
	return
    i = n-1
    while i > 0:
	if(list[i] == list[i-1]):
#	    print "same entry ",list[i]
	    list.pop(i)
	    n = n -1
	i = i - 1


# get the info for a file

def getLumInfo(filename):

	try:
	    fileinfo = file_client.APIGetFileInfo(filename)
	except SAMDbServer.DBError, oerr:
	    sys.stderr.write('**** Terminating execution due to database error\n')
	    return ["DBError"]
	except SAMDbServer.DataFileNotFound:
	    # sys.stderr.write('File not found %s\n'%filename)
	    return ["NoSuchFile"]
	run = fileinfo.runNumber
	min = fileinfo.lumMin
	max = fileinfo.lumMax
	event = fileinfo.eventCount

	    
        return ["OK",[run,min,max,event]]


# trace the parents

def getFileParents(filename):


	try:
	    fileinfo = file_client.APIGetFileInfo(filename)
	except SAMDbServer.DBError, oerr:
	    sys.stderr.write('**** Terminating execution due to database error\n')
	    return ["DBError"]
	except SAMDbServer.DataFileNotFound:
	    # sys.stderr.write('File not found %s\n'%filename)
	    return ["NoSuchFile"]
	

	    
        return ["OK",fileinfo.parentList,fileinfo.eventCount]


# get the events

def getFileEvents(filename):

	try:
	    fileinfo = file_client.APIGetFileInfo(filename)
	except SAMDbServer.DBError, oerr:
	    sys.stderr.write('**** Terminating execution due to database error\n')
	    return -1
	except SAMDbServer.DataFileNotFound:
	    # sys.stderr.write('File not found %s\n'%filename)
	    return -1
	return fileinfo.eventCount





def parse_raw(filename):
    a = string.split(filename,".raw")
    if(len(a) < 1):
	return "bad"
    b = string.split(string.join(a),"_")
    return b[-2]+" : "+b[-1]+" - " + b[-1]


# define output format

def formatOutput(filename,result):

     if(result[0] != "OK"):
#        print result
	output = result
	return output

     output = "%s %s %d %d %d < " %(filename,result[1],result[2],result[3],result[4])
    
     for luminfo in result[5]:
	output = output +"%d : %d - %d " % (luminfo[0],luminfo[1],luminfo[2])

     return output[0:-1]+" >"


# here to do many files

def getManyFileInfo(list,cache):
    if(not exists(list)):
	sys.stderr.write('invalid input list file %s\n'%list)
	sys.exit(1)
    f = open(list)
    files = f.readlines()
#    print files
    for file in files:
	  file = string.strip(file)
#	  print file
          getLumBlk(file,cache)

# here to do files from a sam project

def getManyFileInfoSAM(defname,cache):
    command = "sam translate constraints -a --dim='__set__ %s' | grep raw  " %(defname) 

    result = os.popen(command).readlines()
    result.sort()
    for file in result:
	  file = string.strip(file)
	  if(string.find(file,'raw') >= 0):
	      getLumBlk(file,cache)

def getManyFileInfoSAMCon(defname,cache):
    command = "sam translate constraints -a --dim='%s' | grep raw  " %(defname) 
#    print command
    result = os.popen(command).readlines()
    result.sort()
    for file in result:
	  file = string.strip(file)
	  if(string.find(file,'raw') >= 0):
	      getLumBlk(file,cache)



def help():
	sys.stderr.write('getLumBlk.py <file options> [--cache=<cache-location>]\n')
	sys.stderr.write('returns status word, and list of lum block ranges\n\n')
	sys.stderr.write('file options are: --file=<singlefile>\n')
	sys.stderr.write('                  --list=<file containing list>\n')
	sys.stderr.write('                  --defname=< sam dataset definition >\n')
	sys.stderr.write('                  --dim=< sam dimensions > \n\n')
	sys.stderr.write('optional <cache-location> is location of a cache file\n')



  

if __name__ == '__main__':

    if(len(sys.argv)<2):
	help()
	sys.exit(1)
    args = sys.argv
    try:
	optlist,args = getopt.getopt(sys.argv[1:],'',['file=','list=' , 'defname=','cache=','dim=','help'])
    except getopt.GetoptError:
	help()
	sys.exit(2)

#    print optlist,args

# cache handling

    defaultcache = "/prj_root/846/cd_1/lm_access_cache/cache_v2"
    cache = defaultcache
    for options in optlist:

#	print options
	if options[0] == '--help':
	    help()
	    sys.exit(0)
	if options[0] == '--cache':
		cache = options[1]
		if(len(cache) <1 ):
		    cache = defaultcache
		
		if(not exists(cache)):
		    sys.stderr.write('invalid cache file %s \n'%cache)
		    sys.exit(1)

# file options handling

    for options in optlist:
	if options[0] == '--file':
	    file = options[1]
#	    print " call getLumBlk"
	    result = getLumBlk(file,cache)
	    sys.exit(0)
	elif options[0] == '--list':
#	    print "list", options[1]
	    list = options[1]
	    getManyFileInfo(list,cache)
	    sys.exit(0)
	elif options[0] == '--dim':
#	    print "list", options[1]
	    list = options[1]
	    getManyFileInfoSAMCon(list,cache)
	    sys.exit(0)
	elif options[0] == '--defname':
		defname= options[1]
		result = getManyFileInfoSAM(defname,cache)
		sys.exit(0)
	
    sys.stderr.write('did not get a correct options list\n')
    help()
    sys.exit(1)
    
    
