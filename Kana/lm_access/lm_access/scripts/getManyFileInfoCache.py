#!/usr/bin/env python
import os,time,sys,string
import getFileInfoCache

if __name__ == '__main__':
    if(len(sys.argv)<2):
	print "geManyFileInfo <filename> gets info about files in list"+ filename

	sys.exit(1)
    filename = sys.argv[1]
    f = open(filename)
    files = f.readlines()
    for file in files:
	  file = string.strip(file)
          result = getFileInfoCache.getCacheFileInfo(file)
#	  print result
          if(result[0] == "OK"):
              print result[1]
              continue

          result = getFileInfoCache.getFileRawInfo(file)
          if(result[0] != "OK"):
	      continue
	  print getFileInfoCache.formatOutput(file,result)
