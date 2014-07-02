#!/usr/bin/env python
import os,time,sys,string
import file_client
import SAMDbServer
import getopt
from getFileLBNList import getFileLBNList


from posixpath import exists



# here to do files from a sam project

def getDimensionLBNList(dimname):
    command = "sam translate constraints -a --dim='%s' | grep raw  " %(dimname) 

    result = os.popen(command).readlines()
    result.sort()
    n = 0
    l = 0
    s = 0
    for file in result:
	  filename = string.strip(file)
	  if(len(filename)<2):
	      continue
	  if(string.find(filename,':') >= 0):
	      continue
	  
	  if(exists(filename+".lbn")):
	      s = s+1
	      continue
	  result=getFileLBNList(filename)
	  if result[0] == "OK":
	      n = n + 1
	      if(len(result[1]) < 1):
		  print " strange problem, no lbns"
		  continue
	      f = open(filename+".lbn","w")
	      i = 0
	      while i < len(result[1]):
		  f.write("%d\n"%result[1][i])
		  i = i + 1
		  l = l + 1
	      f.close
	  else:
	      sys.stderr.write( result[0])
    
    return [n,l,s]



  

if __name__ == '__main__':

    if(len(sys.argv)!=2):
	print "getDimensionLBNList.py defname makes a file filename.lbn for each file in dataset defined by dimension which contains the lbn numbers for that file"
	sys.exit(1)
    result = getDimensionLBNList(sys.argv[1])
    n = result[0]
    l = result[1]
    s = result[2]
    print "getDimensionLBNList.py has produced ",n," files with ",l," lbns" 
    print s,"prexisting .lbn files were reused"
