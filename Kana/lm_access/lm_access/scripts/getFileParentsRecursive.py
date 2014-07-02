#!/usr/bin/env python
import os,time,sys,string
import file_client
import SAMDbServer

# trace files back to raw data and find the luminosity related info.

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

if __name__ == '__main__':
    if(len(sys.argv)<2):
	sys.stderr.write('getFileParentsRecursive <filename> returns list of top parents\n')
	sys.exit(1)
    filename = sys.argv[1]
    result = getFileParentsRecursive([filename])
#    if(result[0] != "OK"):
#	print " could not get info"
#	sys.exit(1)

    
      
    
