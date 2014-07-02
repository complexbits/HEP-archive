#!/usr/bin/env python
import os,time,sys,string
import getFileInfoCache

if __name__ == '__main__':
    if(len(sys.argv)<2):
	print "geManyFileInfoSAM <defname> gets info about files in dataset definition <defname>"

	sys.exit(1)
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


	  result = getFileInfoCache.getCacheFileInfo(file)
	  if(result[0] == "OK"):
	      print result[1]
	      continue

          result = getFileInfoCache.getFileRawInfo(file)
          if(result[0] != "OK"):
#	      print file+" could not get info"
	      continue
	  print getFileInfoCache.formatOutput(file,result)
