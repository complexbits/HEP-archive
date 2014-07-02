#!/usr/bin/env python
import os,time,sys,string
import getFileInfo

if __name__ == '__main__':
    if(len(sys.argv)<2):
	print "geManyFileInfoSAM <defname> gets info about files in dataset definition <defname>"

	sys.exit(1)
    if(len(sys.argv)> 2):
        cache = sys.argv[2]
    else:
        cache = ""

    defname = sys.argv[1]
    command = "sam translate constraints --dim='__set__ %s' | grep raw  " %(defname) 
#    print command
    result = os.popen(command).readlines()
    result.sort()
#    print result
#    f = open(filename)
#    files = f.readlines()
    for file in result:

	  file = string.strip(file)


	  result = getFileInfo.getCacheFileInfo(file,cache)
	  if(result[0] == "OK"):
	      print result[1]
	      continue

          result = getFileInfo.getFileRawInfo(file)
          if(result[0] != "OK"):
#	      print file+" could not get info"
	      continue
	  print getFileInfo.formatOutput(file,result)
