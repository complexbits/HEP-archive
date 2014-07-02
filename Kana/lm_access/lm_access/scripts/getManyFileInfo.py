#!/usr/bin/env python
import os,time,sys,string
import getFileInfo

if __name__ == '__main__':
    if(len(sys.argv)<2):
	print "geManyFileInfo <filename> <cache-location> gets info about files in list"+ filename

	sys.exit(1)
    if(len(sys.argv)>2):
	cache = sys.argv[2]
    else:
        cache = ""
    filename = sys.argv[1]
    f = open(filename)
    files = f.readlines()
    for file in files:
	  file = string.strip(file)
          result = getFileInfo.getCacheFileInfo(file,cache)
	  print result
          if(result[0] == "OK"):
              print result[1]
              continue

          result = getFileInfo.getFileRawInfo(file)
          if(result[0] != "OK"):
	      continue
	  print getFileInfo.formatOutput(file,result)
