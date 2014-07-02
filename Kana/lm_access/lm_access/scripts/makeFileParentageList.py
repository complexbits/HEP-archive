#!/usr/bin/env python
import os,time,sys,string
import file_client
import SAMDbServer


# trace files back to raw and return list of lbns

from posixpath import exists

dst = 0

# Unique sort

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


# find the parents of a file

def getFileParentsIterative(filelist,rawlist,versionlist):
#    print "iterative step",len(filelist),len(rawlist),versionlist
    if(len(filelist)==0):
	return "DONE"
    temp = []
    for file in filelist:
	
	test=getFileParents(file,versionlist)
	
	if(test[0]=="DONE"):
	    rawlist.append(file)
	elif(test[0]=="OK"):
	    temp = temp + test[1]
	else:
	    return test[0]
    
#    print temp
    filelist=temp
    test = getFileParentsIterative(filelist,rawlist,versionlist)

    
    return "OK"



def getFileParents(filename,versionlist):



        version = versionlist[0]
            
	parent_version = versionlist[1]

	try:
#	    print "begin", filename
	    fileinfo = file_client.APIGetFileInfo(filename)
	    
	except SAMDbServer.DBError, oerr:
	    
	    sys.stderr.write('**** Terminating execution due to database error\n')
	    return ["DBError"]
	except SAMDbServer.DataFileNotFound:
	
	    sys.stderr.write('File not found %s\n'%filename)
	    return ["NoSuchFile"]

# non- dst use  latest version

	if((version == "unknown" or dst) and fileinfo.applName == "dstreco"):
#	    print "set version"
	    versionlist[0] = fileinfo.version
	    versionlist[1] = versionlist[0]
	if((version == "unknown" or dst) and fileinfo.applName == "recon_root"):
#	    print "set version"
	    versionlist[0] = fileinfo.version
	    versionlist[1] = versionlist[0]
#	if(version != "unknown" and version != fileinfo.version):
#	    versionlist[0] = "multiple"
#	    versionlist[1] = "multiple"
        version = versionlist[0]
        parent_version = versionlist[1]
            
#	print "parents ",fileinfo.applName,filename,version,parent_version,fileinfo.parentList
	if(len(fileinfo.parentList)<1):
	    return ["DONE",filename]
	else:
	    returnlist = fileinfo.parentList
	    
        return ["OK",returnlist]

# find the ultimate parents of a list of files

def getFileParentsRecursive(list):
   

   count = 0

   sortunique(list)
   status = "OK"

   for file in list:
       get = getFileParents(file)
       if get[0] == "DONE":
           continue
       if get[0] != "OK":
           status = "FAILURE"
           return status
       else:
           newstuff = get[1]
           list.remove(file)
           list[:-1] = list[:-1]+newstuff
           count = count + 1
#   print count, list
   if(count > 0):
       status = getFileParentsRecursive(list)              
   
   return status

# find the lbns associated with a file

def makeFileParentageList(filename):
    list = [filename]
    raw = []
    version = "unknown"
    parent_version = "unknown"
    versionlist = [version,parent_version]
    try:
#	    print "begin", filename
        fileinfo = file_client.APIGetFileInfo(filename)
	    
    except SAMDbServer.DBError, oerr:
	    
        sys.stderr.write('**** Terminating execution due to database error\n')
        return ["DBError"]
    except SAMDbServer.DataFileNotFound:
	
        sys.stderr.write('File not found %s\n'%filename)
        return ["NoSuchFile"]

    tier = fileinfo.dataTier
    dst = string.find(tier,"reconstructed")>-1    

    result = getFileParentsIterative(list,raw,versionlist)
    version = versionlist[0]
    parent_version = versionlist[1]
    list=raw
#    print result,list
    if(result != "OK"):
	print result
	return ["ERROR"]
    rawlist = list
    lbnlist = []
    nevents = 0
    for file in rawlist:
	fileinfo=""
	try:
	    fileinfo = file_client.APIGetFileInfo(file)
	    
	except SAMDbServer.DBError, oerr:
	    
	    sys.stderr.write('**** Terminating execution due to database error\n')
	    return ["DBError"]
	except SAMDbServer.DataFileNotFound:
	
	    sys.stderr.write('File not found %s\n'%file)
	    return ["NoSuchFile"]
	
	runnum = fileinfo.runNumber
	lbnmin = fileinfo.lumMin
	lbnmax = fileinfo.lumMax
	stream = fileinfo.physicalDatastreamName
#	i = lbnmin
#	print "raw",file,lbnmin,lbnmax
#	while (i <= lbnmax):
        lbnlist.append([lbnmin,lbnmax,runnum,stream,version,parent_version])
#	    i=i+1
#    sortunique(lbnlist)
    return ["OK",lbnlist]


if __name__ == '__main__':
    if(len(sys.argv)<2):
	sys.stderr.write('makeFileParentageList.py <filename> returns list of lbns to file <filename>.lbn\n\n')
	sys.stderr.write('if imported into python makeFileParentageList(filename) returns\n a list of form ["OK",lbnlist] where "OK" is the status flag and lbnlist is a list of integers\n')
	sys.exit(1)
    filename = sys.argv[1]
    result = makeFileParentageList(filename)
#    print result
    if result[0] == "OK":
	f = open(filename+".parentage","w")
	i = 0
	while i < len(result[1]):
	    f.write("%d %d %s %s %s %s\n"%(result[1][i][0],result[1][i][1],result[1][i][2],result[1][i][3],result[1][i][4],result[1][i][5]))
	    i = i + 1
	f.close
    else:
	sys.stderr.write( result[0])

#    if(result[0] != "OK"):
#	print " could not get info"
#	sys.exit(1)

    
      
    
