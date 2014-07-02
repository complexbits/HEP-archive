#!/usr/bin/env python
import os,time,sys,string
import file_client
import SAMDbServer

# trace files back up one level

from posixpath import exists

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



def getFileParents(filename):


	try:
	    print "begin", filename
	    fileinfo = file_client.APIGetFileInfo(filename)
	    
	except SAMDbServer.DBError, oerr:
	    
	    sys.stderr.write('**** Terminating execution due to database error\n')
	    return ["DBError"]
	except SAMDbServer.DataFileNotFound:
	
	    sys.stderr.write('File not found %s\n'%filename)
	    return ["NoSuchFile"]

	if(len(fileinfo.parentList)<1):
	    return ["DONE",filename]
	else:
	    returnlist = fileinfo.parentList
	    
        return ["OK",returnlist]


if __name__ == '__main__':
    if(len(sys.argv)<2):
	sys.stderr.write('getFileParents <filename> returns list of parents to file <filename>.parents\n')
	sys.exit(1)
    filename = sys.argv[1]
    result = getFileParents(filename)
    if result[0] == "OK":
	f = open(filename+".parents","w")
	i = 0
	while i < len(result[1]):
	    f.write(result[1][i])
	    i = i + 1
	f.close

#    if(result[0] != "OK"):
#	print " could not get info"
#	sys.exit(1)

    
      
    
