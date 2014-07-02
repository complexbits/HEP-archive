#!/usr/bin/env python
import os,time,sys,string
import file_client
import SAMDbServer
from getFileParentsRecursive import getFileParentsRecursive

# trace files back to raw data and find the luminosity related info.

from posixpath import exists

def getCacheFileInfo(filename,cachename):
    #    cachefile = os.environ['LUM_CACHE_FILE']
    if(len(cachename) <1 ):
	cachefile = "/prj_root/829/c/com/begel/stage1a/SAM_cache"
    else:
	cachefile=cachename
    if(not exists(cachefile)):
	return ["NO CACHE"]
    command = "grep %s %s" %(filename,cachefile)
    result = os.popen(command).readlines()
    if(len(result) == 0):
       return ["NOT IN CACHE FILE"]
    if(len(result) == 1):
	return ["OK",string.strip(result[0])]
    else:
	return ["DUPLICATE RECORD"]

def getFileRawInfo(filename):
    filename = os.path.split(filename)[1]
    run = -1
    try:
	    fileinfo = file_client.APIGetFileInfo(filename)
    except SAMDbServer.DBError, oerr:
	    print "**** Terminating execution due to database error"
	    return ["DBError"]
    except SAMDbServer.DataFileNotFound:
	    print "File not found"
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


def getLumInfo(filename):

	try:
	    fileinfo = file_client.APIGetFileInfo(filename)
	except SAMDbServer.DBError, oerr:
	    print "**** Terminating execution due to database error"
	    return ["DBError"]
	except SAMDbServer.DataFileNotFound:
	    print "File not found"
	    return ["NoSuchFile"]
	run = fileinfo.runNumber
	min = fileinfo.lumMin
	max = fileinfo.lumMax
	event = fileinfo.eventCount

	    
        return ["OK",[run,min,max,event]]



def getFileParents(filename):


	try:
	    fileinfo = file_client.APIGetFileInfo(filename)
	except SAMDbServer.DBError, oerr:
	    print "**** Terminating execution due to database error"
	    return ["DBError"]
	except SAMDbServer.DataFileNotFound:
	    print "File not found"
	    return ["NoSuchFile"]
	

	    
        return ["OK",fileinfo.parentList,fileinfo.eventCount]

def getFileEvents(filename):

	try:
	    fileinfo = file_client.APIGetFileInfo(filename)
	except SAMDbServer.DBError, oerr:
	    print "**** Terminating execution due to database error"
	    return -1
	except SAMDbServer.DataFileNotFound:
	    print "File not found"
	    return -1
	return fileinfo.eventCount





def parse_raw(filename):
    a = string.split(filename,".raw")
    if(len(a) < 1):
	return "bad"
    b = string.split(string.join(a),"_")
    return b[-2]+" : "+b[-1]+" - " + b[-1]

def formatOutput(filename,result):

     if(result[0] != "OK"):
#        print result
	output = filename + " DB Failure on info generation "
	return output

     output = "%s %s %d %d %d < " %(filename,result[1],result[2],result[3],result[4])
    
     for luminfo in result[5]:
#        print result[5],luminfo
	output = output +"%d : %d - %d " % (luminfo[0],luminfo[1],luminfo[2])

     return output[0:-1]+" >"
 
  

if __name__ == '__main__':

    if(len(sys.argv)<2):
	print "getFileInfoCache <filename> <optional-cache> returns status word, and list of lum block ranges"
	print "run = -1, means multiple runs"
	sys.exit(1)
    filename = sys.argv[1]
# get from the cache
    if(len(sys.argv)> 2):
	cache = sys.argv[2]
    else:
	cache = ""

    result = getCacheFileInfo(filename,cache)
    if(result[0] == "OK"):
	print result[1]
	sys.exit(0)


    result = getFileRawInfo(filename)
    if(result[0] != "OK"):
	print " could not get info"
	sys.exit(1)
    
    print formatOutput(filename,result)
    
