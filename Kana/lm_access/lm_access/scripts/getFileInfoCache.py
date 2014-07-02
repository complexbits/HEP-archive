#!/usr/bin/env python
import os,time,sys,string
import file_client
import SAMDbServer

# trace files back to raw data and find the luminosity related info.

from posixpath import exists

def getFileRawInfo(filename):
#    filename = os.path.split(filename)[1]
    run = -1
    type = datatier(filename)


# raw data, just get and return

    if(type == "raw"):
    
	try:
	    fileinfo = file_client.APIGetFileInfo(filename)
	except SAMDbServer.DBError, oerr:
	    print "**** Terminating execution due to database error"
	    return ["DBError"]
	except SAMDbServer.DataFileNotFound:
	    print "File not found"
	    return ["NoSuchFile"]
	raw_events = fileinfo.eventCount
	run = fileinfo.runNumber
	lumMin = fileinfo.lumMin
	lumMax = fileinfo.lumMax
        return ["OK","raw",raw_events,-1,-1,[[run,lumMin,lumMax,raw_events]]]

# reco data, find parent raw files, return info for them

    if(type == "reco"):
	
	result = getFileParents(filename)
	if(result[0] != "OK"):
	    return [result[0]]

	sortunique(result[1])
	reco_events = result[2]
	raw_events = 0
	lumInfo = []
	for file in result[1]:
#	    raw_events = raw_events + getFileEvents(file)
	    test = getLumInfo(file)
	    if(test[0] != "OK"):
		return [result[0]]
	    else:
		raw_events = raw_events + test[1][3]
		lstuff = test[1]
		if len(lumInfo) > 0:
		    estuff = lumInfo[-1]
#		    print lstuff, estuff
		    if estuff[2] == lstuff[1]-1 and estuff[0] == lstuff[0]:
#			print lstuff
#			print estuff
			lumInfo[-1][2] = lstuff[2]
			lumInfo[-1][3] = lumInfo[-1][3]+lstuff[3]
#			print "extend lum block", lumInfo[-1]
		    else:
			lumInfo = lumInfo+[lstuff]
		else:
		    lumInfo = [lstuff]

	return [result[0],"reco",raw_events,reco_events,-1,lumInfo]

# root data, trace back 2 layers, then return

    if(type == "root"):
	list =[]
	result = getFileParents(filename)
	if(result[0] != "OK"):
	    return [result[0]]
	else:
	    root_events = result[2]
	    sortunique(result[1])
#	    print "parents: ", result[1]
	    reco_events = 0
	    for parent in result[1]:
		answer = getFileParents(parent)
		if answer[0] != "OK":
		    return answer		
		reco_events = reco_events + answer[2]
		list.extend(answer[1])
#	print list
	sortunique(list)
	raw_events = 0
	lumInfo=[]
	
	index = 0
	for raw in list:
#	    raw_events = raw_events +getFileEvents(raw)
	    test=getLumInfo(raw)
	    if(test[0] != "OK"):
		return [result[0]]
	    else:

# fancy stuff to merge lum blocks if sequential
	    
		lstuff = test[1]
#		print "blocks",lstuff
		if(len(lumInfo)> 0):
		    estuff = lumInfo[-1]
#		    print lstuff,estuff
		    if estuff[2] == lstuff[1]-1 and estuff[0] == lstuff[0]:
#			print lstuff
#			print estuff
			lumInfo[-1][2] = lstuff[2]
			lumInfo[-1][3] = lumInfo[-1][3]+lstuff[3]
#			print "extend lum block",lumInfo[-1]
		    else:
			lumInfo = lumInfo+[lstuff]
		else:
		    lumInfo = [lstuff]
		raw_events = raw_events + test[1][3]
#		lumInfo = lumInfo+[test[1]]
#		print " new data ",lumInfo,test[1]
#	print list
	return ["OK","root",raw_events,reco_events,root_events,lumInfo]
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



def datatier(filename):
    if(filename[0:5]== "recoA"):
	return "root"
    if(filename[0:5]== "reco_"):
	return "reco"
    if(filename[-3:] == "raw"):
	return "raw"
    else:
	return "unknown"

def parse_raw(filename):
    a = string.split(filename,".raw")
    if(len(a) < 1):
	return "bad"
    b = string.split(string.join(a),"_")
    return b[-2]+" : "+b[-1]+" - " + b[-1]

def formatOutput(filename,result):

     if(result[0] != "OK"):
	output = filename + " invalid "
	return output

     output = "%s %s %d %d %d < " %(filename,result[1],result[2],result[3],result[4])
    
     for luminfo in result[5]:
#        print result[5],luminfo
	output = output +"%d : %d - %d " % (luminfo[0],luminfo[1],luminfo[2])

     return output[0:-1]+" >"
   


def getCacheFileInfo(filename):
    #    cachefile = os.environ['LUM_CACHE_FILE']
    cachefile = "/prj_root/829/c/com/begel/stage1a/SAM_cache"
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

if __name__ == '__main__':
    if(len(sys.argv)<2):
	print "getFileInfoCache <filename> returns status word, and list of lum block ranges"
	print "run = -1, means multiple runs"
	sys.exit(1)
    filename = sys.argv[1]
# get from the cache

    result = getCacheFileInfo(filename)
    if(result[0] == "OK"):
	print result[1]
	sys.exit(0)


    result = getFileRawInfo(filename)
#    if(result[0] != "OK"):
#	print " could not get info"
#	sys.exit(1)

    
    print formatOutput(filename,result)
    
