#!/usr/bin/env python
# 
# Program to get run information from the SAM and Runs databases
#
# TODO: add a summary view based on streams, but checkRunInfo.py
#       does not deal properly with streaming yet
#
# Version 2.0  - 30 Nov 2002 - H. Schellman
#                Make thumbnail info show up in root column
#                not pretty but works.
#
# Version 1.9  - 17 May 2002 - Marco Verzocchi
#                Uses configuration file. Correct two bugs.
#
# Version 1.8  -  9 May 2002 - Marco Verzocchi
#                Add trigger version 7.00
# 
# Version 1.7  -  5 May 2002 - Marco Verzocchi
#                Correct a small bug introduced yesterday
# 
# Version 1.6  -  4 May 2002 - Marco Verzocchi
#                Remove the GIF files
#                Add version 5.1 of the globalCalMuon trigger
#
# Version 1.5  - 24 April 2002 - Marco Verzocchi
#                Move around a couple of things on the web page
#
# Version 1.4  - 24 April 2002 - Marco Verzocchi
#                Reenable recoAS checks on p10.15
#
# Version 1.3  - 24 April 2002 - Marco Verzocchi
#                Add a summary view based on trigger type
#
# Version 1.2  - 23 April 2002 - Marco Verzocchi
#                Add a summary view of all runs and summaries for each
#                month of data taking.
#
# Version 1.1  - 08 April 2002 - Marco Verzocchi
#                First version of the code, probably there are still
#                bugs, particularly when dealing with early versions
#                of the D0 software (p10.14.00 and earlier versions).
#          
import getopt,os,sys,string,time

#
# Define some operators on version numbers
#
def versionGreater(version1,version2):
    v1=string.atof(version1[1:6])
    v2=string.atof(version2[1:6])
    return v1>v2
    
#
# Compare two dates
# 
def earlierDate(date1,date2):
    da1='%7s20%2s'%(date1[0:7],date1[7:9])
    da2='%7s20%2s'%(date2[0:7],date2[7:9])
    d1=time.strptime(da1,'%d-%b-%Y')
    d2=time.strptime(da2,'%d-%b-%Y')
    date=date2
    if ( d1<d2 ):
        date=date1
    return date

def laterDate(date1,date2):
    da1='%7s20%2s'%(date1[0:7],date1[7:9])
    da2='%7s20%2s'%(date2[0:7],date2[7:9])
#    print da1,da2
    d1=time.strptime(da1,'%d-%b-%Y')
    d2=time.strptime(da2,'%d-%b-%Y')
    date=date2
    if ( d1>d2 ):
        date=date1
    return date
    
#
# Class for creating an index.html file with pointers to all the different summary pages
#
class HTMLindex:

    def __init__(self,htmldir):
	print "HTMLindex dir ", htmldir
        self.__htmlfile='%s/index.html'%(htmldir)
        self.__htmlfilenew='%s/index.html.new'%(htmldir)
        if self.__htmlfilenew in os.listdir(htmldir):
            os.remove(self.__htmfilenew)
        self.__htmlindex=open(self.__htmlfilenew,"w")
        return

    def __del__(self):
        del self.__htmlfile
        del self.__htmlfilenew
        del self.__htmlindex
        return

    def HTMLheader(self):
        self.__htmlindex.write('<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">\n')
        self.__htmlindex.write('<HTML>\n')
        self.__htmlindex.write('<HEAD>\n')
        self.__htmlindex.write('   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">\n')
        self.__htmlindex.write('   <META NAME="GENERATOR"  CONTENT="MINTS: version 1.00 - Data processing checks">\n')
        self.__htmlindex.write('<TITLE>Offline data processing status</TITLE>\n')
        self.__htmlindex.write('</HEAD>\n')
        self.__htmlindex.write('<BODY TEXT="#000000" BGCOLOR="#FFFFFF" LINK="#0000EE" VLINK="#551A8B" ALINK="#FF0000">\n')
        self.__htmlindex.write('<CENTER><H1>Offline data processing status</H1></CENTER>\n')
        self.__htmlindex.write('<HR>\n')
        return

    def HTMLbeginByVersion(self):
        self.__htmlindex.write('<CENTER><B><H2><FONT COLOR="#FF0000">Summaries by D0 software version</FONT></H2></B></CENTER>\n')
        self.__htmlindex.write('<TABLE BORDER=2 CELLSPACING=2 CELLPADDING=2 WIDTH="100%">\n')
        self.__htmlindex.write('<TR BGCOLOR="#99FFFF">\n')
        self.__htmlindex.write('   <TH><B>Version</B></TH>\n')
        self.__htmlindex.write('   <TH><B>First run</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Date</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Last run</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Date</B></TH>\n')
        self.__htmlindex.write('   <TH><B>RAW data events</B></TH>\n')
        self.__htmlindex.write('   <TH><B>DST events</B></TH>\n')
        self.__htmlindex.write('   <TH><B>thumbnails or ROOT tuples</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Filtered events</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Filtered ROOT</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Last update</B></TH>\n')
        self.__htmlindex.write('</TR>\n')
        return

    def HTMLaddByVersion(self,sumvers):
        self.__htmlindex.write('<TR BGCOLOR="#FFFFFF">\n')
        if ( sumvers[0]!='All' ):
            self.__htmlindex.write('   <TD ALIGN=CENTER><A HREF="summary_%6s.html"><B>%6s</B></A>\n'%(sumvers[0],sumvers[0]))
        else:
            self.__htmlindex.write('   <TD ALIGN=CENTER><A HREF="summary_%6s.html"><B>%6s</B></A>\n'%('runnum',sumvers[0]))
        self.__htmlindex.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(sumvers[1]))
        self.__htmlindex.write('   <TD ALIGN=CENTER>%s</TD>\n'%(sumvers[2]))
        self.__htmlindex.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(sumvers[3]))
        self.__htmlindex.write('   <TD ALIGN=CENTER>%s</TD>\n'%(sumvers[4]))
        self.__htmlindex.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(sumvers[5]))
        self.__htmlindex.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(sumvers[6]))
        self.__htmlindex.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(sumvers[7]))
        if ( sumvers[0]=='p10.15'):
            self.__htmlindex.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(sumvers[8]))
            self.__htmlindex.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(sumvers[9]))
        else: 
            self.__htmlindex.write('   <TD ALIGN=RIGHT>&nbsp;</TD>\n')
            self.__htmlindex.write('   <TD ALIGN=RIGHT>&nbsp;</TD>\n')
        self.__htmlindex.write('   <TD ALIGN=CENTER>%s</TD>\n'%(sumvers[10]))
        self.__htmlindex.write('</TR>\n')
        return

    def HTMLendByVersion(self):
        self.__htmlindex.write('</TABLE>\n')
        self.__htmlindex.write('<HR>\n')
        return

    def HTMLbeginByDate(self):
        self.__htmlindex.write('<CENTER><B><H2><FONT COLOR="#FF0000">Summaries by calendar date</FONT></H2></B></CENTER>\n')
        self.__htmlindex.write('<TABLE BORDER=2 CELLSPACING=2 CELLPADDING=2 WIDTH="100%">\n')
        self.__htmlindex.write('<TR BGCOLOR="#99FFFF">\n')
        self.__htmlindex.write('   <TH><B>Month</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Number of runs</B></TH>\n')
        self.__htmlindex.write('   <TH><B>First run</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Last run</B></TH>\n')
        self.__htmlindex.write('   <TH><B>RAW data events</B></TH>\n')
        self.__htmlindex.write('   <TH><B>DST events</B></TH>\n')
        self.__htmlindex.write('   <TH><B>thumbnails or ROOT tuples</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Last update</B></TH>\n')
        self.__htmlindex.write('</TR>\n')
        return
 
    def HTMLaddByDate(self,summonth):
        self.__htmlindex.write('<TR BGCOLOR="#FFFFFF">\n')
        self.__htmlindex.write('   <TD ALIGN=CENTER><A HREF="summary_%6s.html"><B>%6s</B></A>\n'%(summonth[0],summonth[0]))
        self.__htmlindex.write('   <TD ALIGN=CENTER>%s</TD>\n'%(summonth[1]))
        self.__htmlindex.write('   <TD ALIGN=CENTER>%s</TD>\n'%(summonth[2]))
        self.__htmlindex.write('   <TD ALIGN=CENTER>%s</TD>\n'%(summonth[3]))
        self.__htmlindex.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(summonth[4]))
        self.__htmlindex.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(summonth[5]))
        self.__htmlindex.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(summonth[6]))
        self.__htmlindex.write('   <TD ALIGN=CENTER>%s</TD>\n'%(summonth[7]))
        self.__htmlindex.write('</TR>\n')
        return
    
    def HTMLendByDate(self):
        self.__htmlindex.write('</TABLE>\n')
        self.__htmlindex.write('<HR>\n')
        return

    def HTMLbeginByTrigger(self):
        self.__htmlindex.write('<CENTER><B><H2><FONT COLOR="#FF0000">Summaries by trigger type</FONT></H2></B></CENTER>\n')
        self.__htmlindex.write('<TABLE BORDER=2 CELLSPACING=2 CELLPADDING=2 WIDTH="100%">\n')
        self.__htmlindex.write('<TR BGCOLOR="#99FFFF">\n')
        self.__htmlindex.write('   <TH><B>Trigger</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Number of runs</B></TH>\n')
        self.__htmlindex.write('   <TH><B>First run</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Date</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Last run</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Date</B></TH>\n')
        self.__htmlindex.write('   <TH><B>RAW data events</B></TH>\n')
        self.__htmlindex.write('   <TH><B>DST events</B></TH>\n')
        self.__htmlindex.write('   <TH><B>thumbnails or ROOT tuples</B></TH>\n')
        self.__htmlindex.write('   <TH><B>Last update</B></TH>\n')
        self.__htmlindex.write('</TR>\n')
        return

    def HTMLaddByTrigger(self,sumtrig):
        trigname=sumtrig[0]
        if ( sumtrig[0]=='min' ):
            trigname='minimum_bias'
        elif ( sumtrig[0]=='zero' ):
            trigname='zero_bias'
        self.__htmlindex.write('<TR BGCOLOR="#FFFFFF">\n')
        self.__htmlindex.write('   <TD ALIGN=CENTER><A HREF="summary_%s.html"><B>%s</B></A>\n'%(sumtrig[0],trigname))
        self.__htmlindex.write('   <TD ALIGN=CENTER>%s</TD>\n'%(sumtrig[1]))
        self.__htmlindex.write('   <TD ALIGN=CENTER>%s</TD>\n'%(sumtrig[2]))
        self.__htmlindex.write('   <TD ALIGN=CENTER>%s</TD>\n'%(sumtrig[3]))
        self.__htmlindex.write('   <TD ALIGN=CENTER>%s</TD>\n'%(sumtrig[4]))
        self.__htmlindex.write('   <TD ALIGN=CENTER>%s</TD>\n'%(sumtrig[5]))
        self.__htmlindex.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(sumtrig[6]))
        self.__htmlindex.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(sumtrig[7]))
        self.__htmlindex.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(sumtrig[8]))
        self.__htmlindex.write('   <TD ALIGN=CENTER>%s</TD>\n'%(sumtrig[9]))
        self.__htmlindex.write('</TR>\n')
        return

    def HTMLendByTrigger(self):
        self.__htmlindex.write('</TABLE>\n')
        self.__htmlindex.write('<HR>\n')
        return


    def HTMLfooter(self):
        self.__htmlindex.write('<B><FONT COLOR="#FF0000">Other summaries could be prepared.... ask the luminosity ID working group</FONT></B>\n')
        self.__htmlindex.write('<HR>\n')
        self.__htmlindex.write('<B>These WWW pages are generated nightly by a cron job using the information available in the SAM and Runs databases</B>\n')
        self.__htmlindex.write('<BR>\n')
        self.__htmlindex.write('<B>The two following Python scripts are used:</B>\n')
        self.__htmlindex.write('<BR>\n')
        self.__htmlindex.write('<LI><A HREF="http://www-d0.fnal.gov/cgi-bin/viewcvs.cgi/lm_access/scripts/checkRunInfo.py">checkRunInfo.py</A> (version 1.8 of 12/05/2002)</LI> <FONT COLOR="#FF0000">(PLEASE, DO NOT TRY TO RUN THIS SCRIPT)</FONT>\n')
        self.__htmlindex.write('<LI><A HREF="http://www-d0.fnal.gov/cgi-bin/viewcvs.cgi/lm_access/scripts/mkWebRunInfo.py">mkWebRunInfo.py</A> (version 2.0 of 12/05/2002)</LI>\n')
        self.__htmlindex.write('<HR>\n')
        self.__htmlindex.write('<I>This page was created by MINTS using the information in the SAM and Runs databases</I>\n')
        self.__htmlindex.write('<BR>\n')
        currentdate=time.strftime('%a %b %d %Y at %H:%M:%S',time.localtime(time.time()))
        self.__htmlindex.write('<I>MINTS updated this page on %s</I>\n'%(currentdate))
        return
 
    def HTMLupdatepage(self):
        self.__htmlindex.close()
        os.remove(self.__htmlfile)
        os.system('mv %s %s'%(self.__htmlfilenew,self.__htmlfile))
        return
    
#
# Class containing the information for a single run. The information
# is read from the HTML file and can be later printed in a compact form.
#
class RunInfo:

    def __init__ (self,runnumber,version):
        self.__runnum=runnumber
        self.__date=''
        self.__version=version
        self.__skiprun=0
        self.__trigconf=''
        self.__stream=''
        self.__rawdata=0
        self.__dst=[0,0.,0,0]
        self.__root=[0,0.,0,0]
        self.__recoS=[0,0.,0,0]
        self.__recoAS=[0,0.,0,0] 
        self.__status=[0,0,0,0]
        self.__htmlfile=''
        self.__htmlcreated=''
        self.__message=''
        self.__htmlcolor=''
        self.__queued=0
        return

    def __del__(self):
        del self.__runnum
        del self.__date
        del self.__version
        del self.__skiprun
        del self.__trigconf
        del self.__stream
        del self.__rawdata
        del self.__dst
        del self.__root
        del self.__recoS
        del self.__recoAS
        del self.__status
        del self.__htmlfile
        del self.__htmlcreated
        del self.__message
        del self.__htmlcolor
        del self.__queued
        return

    def getInfoHTML(self,htmldir):
        self.__htmlfile='%3.3d/run%10.10d.%6s.html'%(self.__runnum/1000,self.__runnum,self.__version[0:6])
        runsum=open('%s/%s'%(htmldir,self.__htmlfile),"r")
        decode=0
        for line in runsum.readlines():
            if ( line=='<!-- BEGIN SUMMARY\n'):
                decode=1
            if ( decode==1 and line=='END SUMMARY -->\n'):
                decode=0
            if ( decode==1 ):
                tokens=string.split(line)
                if ( tokens[0]=='Run' ):
                    if ( len(tokens)>2 and tokens[2]=='ignored' ):
                        self.__skiprun=1
                    runnum=string.atoi(tokens[1])
                if ( tokens[0]=='Date'):
                    self.__date=tokens[1]
                if ( tokens[0]=='Trigger' ):
                    self.__trigconf=tokens[2]
                if ( tokens[0]=='Data' ):
                    self.__stream=tokens[2]
                if ( tokens[0]=='Raw' ):
                    self.__rawdata=string.atoi(tokens[3])
                if ( tokens[0]=='DST' ):
                    self.__dst[0]=string.atoi(tokens[2])
                    self.__dst[1]=string.atof(tokens[4])
                    if ( self.__dst[1]<100.0 ):
                        self.__dst[2]=1
                    if ( len(tokens)>=11 and tokens[10]=='Inconsistent' ):
                        self.__dst[3]=1
                if ( tokens[0]=='ROOT' or tokens[0]=='thumbnail' ):
                    self.__root[0]=string.atoi(tokens[2])
                    self.__root[1]=string.atof(tokens[4])
                    if ( self.__root[1]<100.0 ):
                        self.__root[2]=1
                    if ( len(tokens)>=11 and tokens[10]=='Inconsistent' ):
                        self.__root[3]=1
                if ( tokens[0]=='RecoS' ):
                    self.__recoS[0]=string.atoi(tokens[2])
                    self.__recoS[1]=string.atof(tokens[4])
                    if ( self.__recoS[1]<100.0 ):
                        self.__recoS[2]=1
                    if ( len(tokens)>=11 and tokens[10]=='Inconsistent' ):
                        self.__recoS[3]=1
                if ( tokens[0]=='RecoAS' ):
                    self.__recoAS[0]=string.atoi(tokens[2])
                    self.__recoAS[1]=string.atof(tokens[4])
                    if ( self.__recoAS[1]<100.0 ):
                        self.__recoAS[2]=1
                    if ( len(tokens)>=11 and tokens[10]=='Inconsistent' and self.__version=='p10.15' ):
                        self.__recoAS[3]=1
                if ( tokens[0]=='Problems' ):
                    self.__status[0]=1
                if ( self.__status[0]==1 and tokens[0]=='not' ):
                    self.__status[1]=1
                if ( self.__status[0]==1 and tokens[0]=='inconsistent' ):
                    self.__status[2]=1
                if ( self.__status[0]==1 and tokens[0]=='merging' ):
                    self.__status[3]=1
                if ( tokens[0]=='Farm' ):
                    if ( tokens[2]=='queued' ): 
                        self.__queued=1
            if ( line[9:26]=='updated this page' ):
                self.__htmlcreated='%2s-%3s-%2s'%(line[38:40],string.upper(line[34:37]),line[43:45])
        runsum.close()
        if (self.__skiprun==0 ):
            self.__htmlcolor='#FFFFFF'
            self.__message=''
            if ( self.__status[0]==0 ):
                self.__htmlcolor="#00FF00"
                self.__message='DONE'
            if ( self.__dst[2]+self.__root[2]+self.__recoS[2]>0 ):
                self.__htmlcolor="#FFCC33"
                self.__message='Not completed'
                if ( self.__queued==1 ):
                    self.__htmlcolor="#C0C0C0"
                    self.__message='Jobs submitted'
                elif ( self.__dst[0]==0 ):
                    self.__htmlcolor="#FFFF00"
                    self.__message='Not processed'
            elif ( self.__dst[3]+self.__root[3]+self.__recoS[3]>0 ):
                self.__htmlcolor="#FF9900"
                self.__message='Completed with errors'
            else:
                if ( self.__recoAS[2]>0 or self.__recoAS[3]>0 ):
                    self.__htmlcolor="#33BB33"
                    self.__message='DONE'
                if ( self.__status[0]==1 and self.__version=='p10.14' ):
                    self.__htmlcolor="#33BB33"
                    self.__message='DONE'
        return

    def getNumEvt(self):
        evts=[0,0,0,0,0]
        evts[0]=self.__rawdata 
        evts[1]=self.__dst[0]
        evts[2]=self.__root[0]
        evts[3]=self.__recoS[0]
        evts[4]=self.__recoAS[0]
        return evts

    def getFracProcessed(self):
        percent=[0,0,0,0]
        percent[0]=self.__dst[1]
        percent[1]=self.__root[1]
        percent[2]=self.__recoS[1]
        percent[3]=self.__recoAS[1]
        return percent

    def getRawEvt(self):
        return self.__rawdata

    def getRun(self):
        return self.__runnum

    def getDate(self):
        return self.__date

    def getCreationDate(self):
        return self.__htmlcreated

    def getTrigger(self):
        return self.__trigconf

    def getStream(self):
        return self.__stream

    def wasProcessed(self):
        return self.__dst[0]

    def getMessage(self):
        return self.__message
 
    def getHTMLcolor(self):
        return self.__htmlcolor

    def printInfoHTMLVersion(self,output):
        if (self.__skiprun==0 ):
            message=self.__message
            color=self.__htmlcolor
            output.write('<TR BGCOLOR="#FFFF00">\n')
            output.write('   <TD ALIGN=RIGHT BGCOLOR="%s"><A HREF="%s">%7d</A></TD>\n'%(color,self.__htmlfile,self.__runnum))
            output.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">%s</TD>\n'%(self.__date))
            output.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">%s</TD>\n'%(self.__trigconf))
            output.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">%s</TD>\n'%(self.__stream))
            output.write('   <TD ALIGN=RIGHT BGCOLOR="#FFFFFF">%d</TD>\n'%(self.__rawdata))
            output.write('   <TD ALIGN=CENTER BGCOLOR="%s">%s</TD>\n'%(color,message))
            color0="#00FF00"
            if ( self.__dst[1]<100.0):
                color0="#FFCC33"
            if ( self.__dst[0]==0):
                if ( self.__queued==1 ):
                    color0="#C0C0C0" 
                else:
                    color0="#FFFF00"
            if ( self.__dst[1]==100.0 and self.__dst[3]>0):
                color0="#FF9900"
            output.write('   <TD ALIGN=CENTER BGCOLOR="%s">%6.2f%%</TD>\n'%(color0,self.__dst[1]))
            color0="#00FF00"
            if ( self.__root[1]<100.0):
                color0="#FFCC33"
            if ( self.__root[1]==0.0):
                color0="#FF0000"
            if ( self.__dst[0]==0):
                if ( self.__queued==1 ):
                    color0="#C0C0C0" 
                else:
                    color0="#FFFF00"
            if ( self.__root[1]==100.0 and self.__root[3]>0):
                color0="#FF9900"
            output.write('   <TD ALIGN=CENTER BGCOLOR="%s">%6.2f%%</TD>\n'%(color0,self.__root[1]))
            if ( versionGreater(self.__version,'p10.11') ) :
                color0="#00FF00"
                if ( self.__recoS[1]<100.0):
                    color0="#FFCC33"
                if ( self.__recoS[1]==0.0):
                    color0="#FF0000"
                if ( self.__dst[0]==0 ):
                    if ( self.__queued==1 ):
                        color0="#C0C0C0" 
                    else:
                        color0="#FFFF00"
                if ( self.__recoS[1]==100.0 and self.__recoS[3]>0):
                    color0="#FF9900"
                output.write('   <TD ALIGN=CENTER BGCOLOR="%s">%6.2f%%</TD>\n'%(color0,self.__recoS[1]))
            else:
                output.write('   <TD BGCOLOR="#FFFFFF">&nbsp;</TD>\n')
            color0="#00FF00"
            color1="#000000"
            message='PASS'
            if ( self.__status[1]>0 or self.__status[2]>0 ):
                if ( self.__status[1]>0 ):
                    color0="#FFCC33"
                if ( self.__status[2]>0 ):
                    message='FAIL:'
                    if ( self.__status[1]==0 ):
                        color0="#FF9900"
                    color1="#FF0000"
                    if ( self.__dst[3]>0 ): 
                        message='%s %s'%(message,'DST')
                    if ( self.__root[3]>0 ): 
                        if ( versionGreater(self.__version,'p13.01') ) :
                            message='%s %s'%(message,'thumbnail')
                        else:
                            message='%s %s'%(message,'ROOT')
                    if ( self.__recoS[3]>0 ): 
                        message='%s %s'%(message,'recoS')
                    # if ( self.__recoAS[3]>0 ): 
                    if ( self.__recoAS[0]!=self.__recoS[0] and self.__recoAS[0]>0 ) :
                        message='%s %s'%(message,'recoAS')
                else:
                    if ( self.__dst[2]==0 and self.__root[2]==0 and self.__recoS[2]==0 and self.__status[3]==0 ):
                        if (self.__recoAS[2]>0 or self.__recoAS[3]>0 ):
                            color0="#33BB33"
                if ( self.__dst[0]==0 ):
                    if ( self.__queued==1 ):
                        color0="#C0C0C0" 
                    else:
                        color0="#FFFF00"
                    message='&nbsp;'
            output.write('   <TD ALIGN=CENTER BGCOLOR="%s"><FONT COLOR="%s"><B>%s</B></TD>\n'%(color0,color1,message))
            message='<B>NONE</B>'
            if ( self.__dst[0]==0 ):
                message='&nbsp;'
            if ( self.__status[2]==1 or self.__status[3]==1 ):
                color="#FF0000"
                message='<A HREF="%s"><B>YES</B></A>'%(self.__htmlfile)
            output.write('   <TD ALIGN=CENTER BGCOLOR="%s">%s</TD>\n'%(color,message))
            output.write('</TR>\n')
        return
def colorCodes(htmlsum,version):
# Write a table explaining the color coding and the various error conditions.
    htmlsum.write('<CENTER><B>The following color codes and messages are used in the run summaries:</B></CENTER>\n')
    htmlsum.write('<TABLE BORDER=2 CELLSPACING=2 CELLPADDING=2 WIDTH="100%">\n')
    htmlsum.write('<TR BGCOLOR="#FFFFFF">\n')
    htmlsum.write('   <TD BGCOLOR="#00FF00">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</TD>\n')
    htmlsum.write('   <TD>All partitions corresponding to this run have been processed completely, without any error. DST, ROOT tuples, filtered DST and the corresponding ROOT tuples have been generated and no inconsistency was found in the number of events. There was no error in the process or merging files</TD>\n')
    htmlsum.write('</TR>\n')
    htmlsum.write('<TR BGCOLOR="#FFFFFF">\n')
    htmlsum.write('   <TD BGCOLOR="#33BB33">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</TD>\n')
    message=''
    if ( version[0]=='p10.14'):
        message=' <B><FONT COLOR="#FF0000">This check makes no sense for most p10.14 filtered ROOT tuples.</FONT></B>'
    if ( version[0]=='p10.15'):
        message=' <B><FONT COLOR="#FF0000">This is a known problem with p10.15.</FONT></B>'
    htmlsum.write('   <TD>All partitions corresponding to this run have been processed completely, but there are some problems with the ROOT tuples corresponding to the filtered DST sample (either they haven\'t been generated or there are inconsistencies in the number of events or errors in the process of merging ROOT files.%s. The DST, ROOT tuples and the filtered DST are fine and no inconsistency was found in the number of events.</TD>\n'%(message))
    htmlsum.write('</TR>\n')
    htmlsum.write('<TR BGCOLOR="#FFFFFF">\n')
    htmlsum.write('   <TD BGCOLOR="#FFFF00">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</TD>\n')
    htmlsum.write('   <TD>This run hasn\'t been processed with the current version of the D0 software and there is no job in the D0 farm queue.</TD>\n')
    htmlsum.write('</TR>\n')
    htmlsum.write('<TR BGCOLOR="#FFFFFF">\n')
    htmlsum.write('   <TD BGCOLOR="#C0C0C0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</TD>\n')
    htmlsum.write('   <TD>Jobs for this run have been submitted to the D0 farm.</TD>\n')
    htmlsum.write('</TR>\n')
    htmlsum.write('<TR BGCOLOR="#FFFFFF">\n')
    htmlsum.write('   <TD BGCOLOR="#FFCC33">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</TD>\n')
    htmlsum.write('   <TD>This run was processed only partially. The fraction of events processed at each step (DST: D0reco, ROOT: RecoAnalyze, recoS: filtered DST) is indicated in the respective column of the table.</TD>\n')
    htmlsum.write('</TR>\n')
    htmlsum.write('<TR BGCOLOR="#FFFFFF">\n')
    htmlsum.write('   <TD BGCOLOR="#FF9900">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</TD>\n')
    htmlsum.write('   <TD>The run appears to have been processed completely. However there are some inconsistencies in the number of events. Check the <B>Consistency check</B> column.</TD>\n')
    htmlsum.write('</TR>\n')
    htmlsum.write('<TR BGCOLOR="#FFFFFF">\n')
    htmlsum.write('   <TD BGCOLOR="#FF0000">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</TD>\n')
    htmlsum.write('   <TD>Used to signal a processing error. Click on the run number to see more details.</TD>\n')
    htmlsum.write('</TR>\n')
    htmlsum.write('<TR BGCOLOR="#FFFFFF">\n')
    htmlsum.write('   <TD BGCOLOR="#99FFFF"><B>Consistency check</B></TD>\n')
    htmlsum.write('   <TD><B>PASS:&nbsp;</B>The number of events in the output of each program of the reconstruction chain is consistent with the number of input events. <FONT COLOR="#FF0000"><B>FAIL:&nbsp;</B></FONT>An inconsistency has been found between the number of input and output events (generally this indicates that one partition hasn\'t been completely processed).</TD>\n')
    htmlsum.write('</TR>\n')
    htmlsum.write('<TR BGCOLOR="#FFFFFF">\n')
    htmlsum.write('   <TD BGCOLOR="#99FFFF"><B>Merging errors</B></TD>\n')
    htmlsum.write('   <TD><B>NONE:&nbsp;</B>No errors found while merging ROOT tuples or filtered DST. <B>YES:&nbsp;</B>Errors founds in the merging of ROOT tuples or filtered DST. Usually this involves merging the ROOT tuple for an incomplete partition or assigning a file name which spans a non-processed partition. Click on the run number or on <B>YES:&nbsp;</B> to see more details.</TD>\n')
    htmlsum.write('</TR>\n')
    htmlsum.write('</TABLE>\n')
    htmlsum.write('<HR>\n')
    return

def makeSummaryByTrigger(listhtml,trigger,listoftriggers,htmldir):
    trigname=trigger
    if ( trigger=='min' ):
        trigname='minimum_bias'
    elif ( trigger=='zero' ):
        trigname='zero_bias'
    htmlfile='%s/summary_%s.html'%(htmldir,trigger)
    lentrig=len(trigger)
    lentrall=[]
    for i in listoftriggers:
        lentrall.append(len(i))
# Internal buffers for the various runs and for the event counters
# sumtrig: 0 trigger name
#          1 number of runs
#          2 first run
#          3 date
#          4 last run
#          5 date
#          6 raw
#          7 dst
#          8 root
#          9 last update
#          A status word 0 if fine
    sumtrig=['trigger',0,0,'01-JAN-00',999999,'31-DEC-19',0,0,0,'01-JAN-00',1]
    totevt=[0,0,0]
    lastrun=0
    firstrun=99999999
    firstdate='31-DEC-19'
    lastdate='01-JAN-00'
    datecreate='01-JAN-00'
    maxvers=0
    numruns=0
# Parse the HTML files corresponding to each individual run
    for htmlentry in listhtml:
        runtrigger=htmlentry[2]
        trigtokens=string.split(runtrigger,'/')
        ntokens=len(trigtokens)-1
        runtrigger=trigtokens[ntokens]
        runselect=0
        if ( runtrigger[0:lentrig]==trigger ):
             runselect=1
        elif ( trigger=='others' ):
            triginthelist=0
            i=0
            for i in range(len(listoftriggers)):
                if ( runtrigger[0:lentrall[i]]==listoftriggers[i]):
                    triginthelist=1
            if ( triginthelist==0 ):
                runselect=1
        if ( runselect==1 ):
            numentries=htmlentry[6]
            maxvers=max(htmlentry[6],maxvers)
            maxDST=0
            maxROOT=0
            numruns=numruns+1
            totevt[0]=totevt[0]+htmlentry[4]
            for i in range(numentries):
                evDST=htmlentry[7*i+11]
                maxDST=max(maxDST,evDST)
                evROOT=htmlentry[7*i+12]
                maxROOT=max(maxROOT,evROOT)
            totevt[1]=totevt[1]+maxDST
            totevt[2]=totevt[2]+maxROOT
            lastrun=max(lastrun,htmlentry[0])
            firstrun=min(firstrun,htmlentry[0])
            firstrun=htmlentry[0]
            firstdate=earlierDate(firstdate,htmlentry[1])
            lastdate=laterDate(lastdate,htmlentry[1])
            datecreate=laterDate(datecreate,htmlentry[5])
# Summary of all the runs
    sumtrig[0]=trigger
    sumtrig[1]=numruns
    sumtrig[2]=firstrun
    sumtrig[3]=firstdate
    sumtrig[4]=lastrun
    sumtrig[5]=lastdate
    sumtrig[6]=totevt[0]
    sumtrig[7]=totevt[1]
    sumtrig[8]=totevt[2]
    sumtrig[9]=datecreate
    sumtrig[10]=0
# Start writing the summary WEB page
    if htmlfile in os.listdir(htmldir):
        os.remove(htmlfile)
    htmlsum=open(htmlfile,"w")
    htmlsum.write('<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">\n')
    htmlsum.write('<HTML>\n')
    htmlsum.write('<HEAD>\n')
    htmlsum.write('   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">\n')
    htmlsum.write('   <META NAME="GENERATOR"  CONTENT="MINTS: version 1.00 - Data processing checks">\n')
    htmlsum.write('<TITLE>Data processing checks D0 runs with trigger type %s</TITLE>\n'%(trigname))
    htmlsum.write('</HEAD>\n')
    htmlsum.write('<BODY TEXT="#000000" BGCOLOR="#FFFFFF" LINK="#0000EE" VLINK="#551A8B" ALINK="#FF0000">\n')
    htmlsum.write('<CENTER><H2>Data processing checks for D0 runs with trigger type %s</H2></CENTER>\n'%(trigname))
    htmlsum.write('<HR>\n')
# Write a first table containing the total number of events
    if ( numruns>0 ):
        htmlsum.write('<TABLE BORDER=2 CELLSPACING=2 CELLPADDING=2 WIDTH="100%">\n')
        htmlsum.write('<TR BGCOLOR="#99FFFF">\n')
        htmlsum.write('   <TH><B>Number of runs</B></TH>\n')
        htmlsum.write('   <TH><B>Starting from </B></TH>\n')
        htmlsum.write('   <TH><B>Ending on</B></TH>\n')
        htmlsum.write('   <TH><B>RAW data events</B></TH>\n')
        htmlsum.write('   <TH><B>DST events</B></TH>\n')
        htmlsum.write('   <TH><B>ROOT tuples</B></TH>\n')
        htmlsum.write('</TR>\n')
        htmlsum.write('<TR BGCOLOR="#FFFF00">\n')
        htmlsum.write('   <TD ALIGN=CENTER>%d</TD>\n'%(len(listhtml)))
        htmlsum.write('   <TD ALIGN=CENTER>%s</TD>\n'%(firstdate))
        htmlsum.write('   <TD ALIGN=CENTER>%s</TD>\n'%(lastdate))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[0]))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[1]))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[2]))
        htmlsum.write('</TR>\n')
        htmlsum.write('</TABLE>\n')
        htmlsum.write('<HR>\n')
# Write a second table explaining the color coding and the various error conditions.
        colorCodes(htmlsum,'All')
# Now the third table with the details of each run 
        htmlsum.write('<TABLE BORDER=2 CELLSPACING=2 CELLPADDING=2 WIDTH="100%">\n')
        htmlsum.write('<TR BGCOLOR="#99FFFF">\n')
        htmlsum.write('   <TH><B>Run number</B></TH>\n')
        htmlsum.write('   <TH><B>Date</B></TH>\n')
        htmlsum.write('   <TH><B>Trigger configuration file</B></TH>\n')
        htmlsum.write('   <TH><B>Data stream</B></TH>\n')
        htmlsum.write('   <TH><B>Number of events</B></TH>\n')
        htmlsum.write('   <TH COLSPAN="%d"><B>Processing status for different reco versions</B></TH>\n'%(maxvers))
        htmlsum.write('</TR>\n')
        for htmlentry in listhtml:
            runtrigger=htmlentry[2]
            trigtokens=string.split(runtrigger,'/')
            ntokens=len(trigtokens)-1
            runtrigger=trigtokens[ntokens]
            runselect=0
            if ( runtrigger[0:lentrig]==trigger ):
                 runselect=1
            elif ( trigger=='others' ):
                triginthelist=0
                i=0
                for i in range(len(listoftriggers)):
                    if ( runtrigger[0:lentrall[i]]==listoftriggers[i]):
                        triginthelist=1
                if ( triginthelist==0 ):
                    runselect=1
            if ( runselect==1 ):
                numvers=htmlentry[6]
# Decide which is the best version for this run
                color=htmlentry[9]
                bestvers=0
                if ( numvers>1 ):
                    maxproc=0.
                    for i in range(numvers):
                        fracproc=htmlentry[7*i+10]
                        if ( fracproc>maxproc ):
                            bestvers=i 
                            maxproc=fracproc
                        elif ( fracproc==maxproc ):
                            if ( htmlentry[7*i+8]=='DONE' ):
                                bestvers=i
                    if ( maxproc==0. ):
                        bestvers=i
                        numvers=1
                    color=htmlentry[7*bestvers+9]
                htmlsum.write('<TR BGCOLOR="#FFFF00">\n')
                htmlsum.write('   <TD ALIGN=RIGHT BGCOLOR="%s">%7d</TD>\n'%(color,htmlentry[0]))
                htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">%s</TD>\n'%(htmlentry[1]))
                htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">%s</TD>\n'%(htmlentry[2]))
                htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">%s</TD>\n'%(htmlentry[3]))
                htmlsum.write('   <TD ALIGN=RIGHT BGCOLOR="#FFFFFF">%d</TD>\n'%(htmlentry[4]))
                if ( numvers==1 ):
                    i=bestvers
                    htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="%s"><A HREF="%s">%s</A>: %s</TD>\n'%(htmlentry[7*i+9],htmlentry[7*i+13],htmlentry[7*i+7],htmlentry[7*i+8]))
                else:
                    for i in range(numvers):
                        htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="%s"><A HREF="%s">%s</A>: %s</TD>\n'%(htmlentry[7*i+9],htmlentry[7*i+13],htmlentry[7*i+7],htmlentry[7*i+8]))
                emptycol=maxvers-numvers
                if ( emptycol>0):
                    for i in range(emptycol):
                        htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">&nbsp;</TD>\n')
                htmlsum.write('</TR>\n')
        htmlsum.write('</TABLE>\n')
# No runs found for this trigger
    else:
        htmlsum.write('<CENTER><B><H2><FONT COLOR="#FF0000">No runs found for the %s trigger</FONT></H2></B></CENTER>\n'%(trigname))
        sumtrig[10]=1
    htmlsum.write('<HR>')
    htmlsum.write('<I>This page was created by MINTS using the information in the SAM and Runs databases</I>\n')
    htmlsum.write('<BR>\n')
    currentdate=time.strftime('%a %b %d %Y at %H:%M:%S',time.localtime(time.time()))
    htmlsum.write('<I>MINTS updated this page on %s</I>\n'%(currentdate))
    htmlsum.close()
    return sumtrig

def makeSummaryByMonth(listhtml,month,htmldir):
    htmlfile='%s/summary_%s.html'%(htmldir,month)
# Internal buffers for the various runs and for the event counters
    summonth=['JAN-00',0,0,999999,0,0,0,'01-JAN-00',1]
    totevt=[0,0,0]
    lastrun=0
    firstrun=0
    datecreate='01-JAN-00'
    maxvers=0
    numruns=0
# Parse the HTML files corresponding to each individual run
    for htmlentry in listhtml:
        runmonth=htmlentry[1]
        runmonth=runmonth[3:]
        if ( runmonth==month ):
            numentries=htmlentry[6]
            maxvers=max(htmlentry[6],maxvers)
            maxDST=0
            maxROOT=0
            numruns=numruns+1
            totevt[0]=totevt[0]+htmlentry[4]
            for i in range(numentries):
                evDST=htmlentry[7*i+11]
                maxDST=max(maxDST,evDST)
                evROOT=htmlentry[7*i+12]
                maxROOT=max(maxROOT,evROOT)
            totevt[1]=totevt[1]+maxDST
            totevt[2]=totevt[2]+maxROOT
            if ( lastrun==0 ):
                lastrun=htmlentry[0]
            firstrun=htmlentry[0]
            datecreate=laterDate(datecreate,htmlentry[5])
# Summary of all the runs
    summonth[0]=month
    summonth[1]=numruns
    summonth[2]=firstrun
    summonth[3]=lastrun
    summonth[4]=totevt[0]
    summonth[5]=totevt[1]
    summonth[6]=totevt[2]
    summonth[7]=datecreate
    summonth[8]=0
# Start writing the summary WEB page
    if htmlfile in os.listdir(htmldir):
        os.remove(htmlfile)
    htmlsum=open(htmlfile,"w")
    htmlsum.write('<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">\n')
    htmlsum.write('<HTML>\n')
    htmlsum.write('<HEAD>\n')
    htmlsum.write('   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">\n')
    htmlsum.write('   <META NAME="GENERATOR"  CONTENT="MINTS: version 1.00 - Data processing checks">\n')
    htmlsum.write('<TITLE>Data processing checks D0 runs of %s</TITLE>\n'%(month))
    htmlsum.write('</HEAD>\n')
    htmlsum.write('<BODY TEXT="#000000" BGCOLOR="#FFFFFF" LINK="#0000EE" VLINK="#551A8B" ALINK="#FF0000">\n')
    htmlsum.write('<CENTER><H2>Data processing checks for D0 runs of %s</H2></CENTER>\n'%(month))
    htmlsum.write('<HR>\n')
# Write a first table containing the total number of events
    if ( numruns>0 ):
        htmlsum.write('<TABLE BORDER=2 CELLSPACING=2 CELLPADDING=2 WIDTH="100%">\n')
        htmlsum.write('<TR BGCOLOR="#99FFFF">\n')
        htmlsum.write('   <TH><B>Number of runs</B></TH>\n')
        htmlsum.write('   <TH><B>RAW data events</B></TH>\n')
        htmlsum.write('   <TH><B>DST events</B></TH>\n')
        htmlsum.write('   <TH><B>ROOT tuples</B></TH>\n')
        htmlsum.write('</TR>\n')
        htmlsum.write('<TR BGCOLOR="#FFFF00">\n')
        htmlsum.write('   <TD ALIGN=CENTER>%d</TD>\n'%(numruns))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[0]))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[1]))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[2]))
        htmlsum.write('</TR>\n')
        htmlsum.write('</TABLE>\n')
        htmlsum.write('<HR>\n')
# Write a second table explaining the color coding and the various error conditions.
        colorCodes(htmlsum,'All')
# Now the third table with the details of each run 
        htmlsum.write('<TABLE BORDER=2 CELLSPACING=2 CELLPADDING=2 WIDTH="100%">\n')
        htmlsum.write('<TR BGCOLOR="#99FFFF">\n')
        htmlsum.write('   <TH><B>Run number</B></TH>\n')
        htmlsum.write('   <TH><B>Date</B></TH>\n')
        htmlsum.write('   <TH><B>Trigger configuration file</B></TH>\n')
        htmlsum.write('   <TH><B>Data stream</B></TH>\n')
        htmlsum.write('   <TH><B>Number of events</B></TH>\n')
        htmlsum.write('   <TH COLSPAN="%d"><B>Processing status for different reco versions</B></TH>\n'%(maxvers))
        htmlsum.write('</TR>\n')
        for htmlentry in listhtml:
            runmonth=htmlentry[1]
            runmonth=runmonth[3:]
            if ( runmonth==month ):
                numvers=htmlentry[6]
# Decide which is the best version for this run
                color=htmlentry[9]
                bestvers=0
                if ( numvers>1 ):
                    maxproc=0.
                    for i in range(numvers):
                        fracproc=htmlentry[7*i+10]
                        if ( fracproc>maxproc ):
                            bestvers=i 
                            maxproc=fracproc
                        elif ( fracproc==maxproc ):
                            if ( htmlentry[7*i+8]=='DONE' ):
                                bestvers=i
                    if ( maxproc==0. ):
                        bestvers=i
                        numvers=1
                    color=htmlentry[7*bestvers+9]
                htmlsum.write('<TR BGCOLOR="#FFFF00">\n')
                htmlsum.write('   <TD ALIGN=RIGHT BGCOLOR="%s">%7d</TD>\n'%(color,htmlentry[0]))
                htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">%s</TD>\n'%(htmlentry[1]))
                htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">%s</TD>\n'%(htmlentry[2]))
                htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">%s</TD>\n'%(htmlentry[3]))
                htmlsum.write('   <TD ALIGN=RIGHT BGCOLOR="#FFFFFF">%d</TD>\n'%(htmlentry[4]))
                if ( numvers==1 ):
                    i=bestvers
                    htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="%s"><A HREF="%s">%s</A>: %s</TD>\n'%(htmlentry[7*i+9],htmlentry[7*i+13],htmlentry[7*i+7],htmlentry[7*i+8]))
                else:
                    for i in range(numvers):
                        htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="%s"><A HREF="%s">%s</A>: %s</TD>\n'%(htmlentry[7*i+9],htmlentry[7*i+13],htmlentry[7*i+7],htmlentry[7*i+8]))
                emptycol=maxvers-numvers
                if ( emptycol>0):
                    for i in range(emptycol):
                        htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">&nbsp;</TD>\n')
                htmlsum.write('</TR>\n')
        htmlsum.write('</TABLE>\n')
# No runs found for this month
    else:
        htmsum.write('<CENTER><B><H2><FONT COLOR="#FF0000">No runs found for the %s month</FONT></H2></B></CENTER>\n'%(month))
        summonth[8]=1
    htmlsum.write('<HR>')
    htmlsum.write('<I>This page was created by MINTS using the information in the SAM and Runs databases</I>\n')
    htmlsum.write('<BR>\n')
    currentdate=time.strftime('%a %b %d %Y at %H:%M:%S',time.localtime(time.time()))
    htmlsum.write('<I>MINTS updated this page on %s</I>\n'%(currentdate))
    htmlsum.close()
    return summonth

def makeSummaryByRunnum(verbose,listofversions,htmldir):
    htmlfile='%s/summary_runnum.html'%(htmldir)
# Internal buffers for the various runs and for the event counters
    listhtml=[]
    monthlist=[]
    sumrun=['All',0,'01-JAN-00',999999,'01-JAN-00',0,0,0,0,0,'01-JAN-00',1]
    totevt=[0,0,0,0,0]
    datelast=''
    dateupdate='01-JAN-00'
    lastrun=999999
    maxvers=0
# Parse the HTML files corresponding to each individual run
    for i in range(129,999):
        directory='%3.3d'%(i)
        if directory in os.listdir(htmldir):
            localdir='%s/%s'%(htmldir,directory)
            listfiles=os.listdir(localdir)
            listfiles.sort()
            for j in range (0,999): 
                runnum=1000*i+j
                numentry=0
                maxDST=0
                maxROOT=0
                for version in listofversions:
                    localfile='run%10.10d.%6s.html'%(runnum,version[0])
                    if localfile in listfiles:
                        info=RunInfo(runnum,version[0])
                        info.getInfoHTML(htmldir)
                        if ( numentry==0 ):
                            htmlentry=[]
                            htmlentry.append(info.getRun())
                            htmlentry.append(info.getDate())
                            htmlentry.append(info.getTrigger()) 
                            htmlentry.append(info.getStream())
                            htmlentry.append(info.getRawEvt()) 
                            datecreate=info.getCreationDate()
			    if(len(datecreate)<1):
				print "creation date is strange for ",runnum
				continue
                            htmlentry.append(datecreate)
                            dateupdate=laterDate(dateupdate,datecreate)
                            htmlentry.append(0)
                            lastrun=runnum
                            totevt[0]=totevt[0]+info.getRawEvt()
                            datelast=info.getDate()
                            month=datelast[3:]
                            if not month in monthlist:
                                monthlist.append(month)
                        htmlentry.append(version[0])
                        htmlentry.append(info.getMessage())
                        htmlentry.append(info.getHTMLcolor())
                        percent=info.getFracProcessed()
                        htmlentry.append(min(percent[0],percent[1]))
                        events=info.getNumEvt()
                        if (events[1]>events[0] and percent[0]==100.0 ):
                            events[1]=events[0]
                        if (events[2]>events[0] and percent[1]==100.0 ):
                            events[2]=events[0]
                        htmlentry.append(events[1])
                        htmlentry.append(events[2])
                        htmlentry.append('%s/%s'%(directory,localfile))
                        numentry=numentry+1
                        htmlentry[6]=numentry
                        maxvers=max(numentry,maxvers)
                        maxDST=max(maxDST,events[1])
                        maxROOT=max(maxROOT,events[2])
                if ( numentry>0 ):
                    if ( listhtml==[] ):
                        datefirst=datelast
                        firstrun=runnum
                    totevt[1]=totevt[1]+maxDST
                    totevt[2]=totevt[2]+maxROOT
                    listhtml.append(htmlentry)
# Summary of all the runs
    sumrun[0]='All'
    sumrun[1]=firstrun
    sumrun[2]=datefirst
    sumrun[3]=lastrun
    sumrun[4]=datelast
    sumrun[5]=totevt[0]
    sumrun[6]=totevt[1]
    sumrun[7]=totevt[2]
    sumrun[8]=totevt[3]
    sumrun[9]=totevt[4]
    sumrun[10]=dateupdate
    sumrun[11]=0
# Start writing the summary WEB page
    if htmlfile in os.listdir(htmldir):
        os.remove(htmlfile)
    htmlsum=open(htmlfile,"w")
    htmlsum.write('<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">\n')
    htmlsum.write('<HTML>\n')
    htmlsum.write('<HEAD>\n')
    htmlsum.write('   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">\n')
    htmlsum.write('   <META NAME="GENERATOR"  CONTENT="MINTS: version 1.00 - Data processing checks">\n')
    htmlsum.write('<TITLE>Data processing checks D0 runs %d - %d</TITLE>\n'%(firstrun,lastrun))
    htmlsum.write('</HEAD>\n')
    htmlsum.write('<BODY TEXT="#000000" BGCOLOR="#FFFFFF" LINK="#0000EE" VLINK="#551A8B" ALINK="#FF0000">\n')
    htmlsum.write('<CENTER><H2>Data processing checks for D0 runs %d - %d</H2></CENTER>\n'%(firstrun,lastrun))
    htmlsum.write('<HR>\n')
# Write a first table containing the total number of events
    if ( len(listhtml)>0 ):
        htmlsum.write('<TABLE BORDER=2 CELLSPACING=2 CELLPADDING=2 WIDTH="100%">\n')
        htmlsum.write('<TR BGCOLOR="#99FFFF">\n')
        htmlsum.write('   <TH><B>Number of runs</B></TH>\n')
        htmlsum.write('   <TH><B>Starting from </B></TH>\n')
        htmlsum.write('   <TH><B>Ending on</B></TH>\n')
        htmlsum.write('   <TH><B>RAW data events</B></TH>\n')
        htmlsum.write('   <TH><B>DST events</B></TH>\n')
        htmlsum.write('   <TH><B>thumbnails or ROOT tuples</B></TH>\n')
        htmlsum.write('</TR>\n')
        htmlsum.write('<TR BGCOLOR="#FFFF00">\n')
        htmlsum.write('   <TD ALIGN=CENTER>%d</TD>\n'%(len(listhtml)))
        htmlsum.write('   <TD ALIGN=CENTER>%s</TD>\n'%(datefirst))
        htmlsum.write('   <TD ALIGN=CENTER>%s</TD>\n'%(datelast))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[0]))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[1]))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[2]))
        htmlsum.write('</TR>\n')
        htmlsum.write('</TABLE>\n')
        htmlsum.write('<HR>\n')
# Write a second table explaining the color coding and the various error conditions.
    colorCodes(htmlsum,'All')
# Now the third table with the details of each run 
    htmlsum.write('<TABLE BORDER=2 CELLSPACING=2 CELLPADDING=2 WIDTH="100%">\n')
    htmlsum.write('<TR BGCOLOR="#99FFFF">\n')
    htmlsum.write('   <TH><B>Run number</B></TH>\n')
    htmlsum.write('   <TH><B>Date</B></TH>\n')
    htmlsum.write('   <TH><B>Trigger configuration file</B></TH>\n')
    htmlsum.write('   <TH><B>Data stream</B></TH>\n')
    htmlsum.write('   <TH><B>Number of events</B></TH>\n')
    htmlsum.write('   <TH COLSPAN="%d"><B>Processing status for different reco versions</B></TH>\n'%(maxvers))
    htmlsum.write('</TR>\n')
    listhtml.reverse()
    for htmlentry in listhtml:
        numvers=htmlentry[6]
# Decide which is the best version for this run
        color=htmlentry[9]
        bestvers=0
        if ( numvers>1 ):
            maxproc=0.
            for i in range(numvers):
                fracproc=htmlentry[7*i+10]
                if ( fracproc>maxproc ):
                    bestvers=i 
                    maxproc=fracproc
                elif ( fracproc==maxproc ):
                    if ( htmlentry[7*i+8]=='DONE' ):
                        bestvers=i
            if ( maxproc==0. ):
                bestvers=i
                numvers=1
            color=htmlentry[7*bestvers+9]
        htmlsum.write('<TR BGCOLOR="#FFFF00">\n')
        htmlsum.write('   <TD ALIGN=RIGHT BGCOLOR="%s">%7d</TD>\n'%(color,htmlentry[0]))
        htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">%s</TD>\n'%(htmlentry[1]))
        htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">%s</TD>\n'%(htmlentry[2]))
        htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">%s</TD>\n'%(htmlentry[3]))
        htmlsum.write('   <TD ALIGN=RIGHT BGCOLOR="#FFFFFF">%d</TD>\n'%(htmlentry[4]))
        if ( numvers==1 ):
            i=bestvers
            htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="%s"><A HREF="%s">%s</A>: %s</TD>\n'%(htmlentry[7*i+9],htmlentry[7*i+13],htmlentry[7*i+7],htmlentry[7*i+8]))
        else:
            for i in range(numvers):
                htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="%s"><A HREF="%s">%s</A>: %s</TD>\n'%(htmlentry[7*i+9],htmlentry[7*i+13],htmlentry[7*i+7],htmlentry[7*i+8]))
        emptycol=maxvers-numvers
        if ( emptycol>0):
            for i in range(emptycol):
                htmlsum.write('   <TD ALIGN=LEFT  BGCOLOR="#FFFFFF">&nbsp;</TD>\n')
        i=bestvers
        if ( verbose==1 ):
            sys.stderr.write('%7d %9s %7d %7d %7d\n'%(htmlentry[0],htmlentry[1],htmlentry[4],htmlentry[7*i+11],htmlentry[7*i+12]))
        htmlsum.write('</TR>\n')
    htmlsum.write('</TABLE>\n')
    htmlsum.write('<HR>')
    htmlsum.write('<I>This page was created by MINTS using the information in the SAM and Runs databases</I>\n')
    htmlsum.write('<BR>\n')
    currentdate=time.strftime('%a %b %d %Y at %H:%M:%S',time.localtime(time.time()))
    htmlsum.write('<I>MINTS updated this page on %s</I>\n'%(currentdate))
    htmlsum.close()
    return sumrun,monthlist,listhtml

def makeSummaryByVersion(version,htmldir):
    htmlfile='%s/summary_%6s.html'%(htmldir,version[0])
# Start writing the summary WEB page
    if htmlfile in os.listdir(htmldir):
        os.remove(htmlfile)
    htmlsum=open(htmlfile,"w")
    htmlsum.write('<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">\n')
    htmlsum.write('<HTML>\n')
    htmlsum.write('<HEAD>\n')
    htmlsum.write('   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">\n')
    htmlsum.write('   <META NAME="GENERATOR"  CONTENT="MINTS: version 1.00 - Data processing checks">\n')
    htmlsum.write('<TITLE>Data processing checks D0 version %6s</TITLE>\n'%(version[0]))
    htmlsum.write('</HEAD>\n')
    htmlsum.write('<BODY TEXT="#000000" BGCOLOR="#FFFFFF" LINK="#0000EE" VLINK="#551A8B" ALINK="#FF0000">\n')
    htmlsum.write('<CENTER><H2>Data processing checks for D0 version %6s</H2></CENTER>\n'%(version[0]))
    htmlsum.write('<HR>\n')
    if ( version[0]=='t01.56' or version[0]=='p10.07'):
        htmlsum.write('<CENTER><B><FONT COLOR="#FF0000">Filtered DST are not produced for %s</FONT></B></CENTER>\n'%(version[0]))
        htmlsum.write('<HR>\n')
    if ( version[0]=='p10.11'):
        htmlsum.write('<CENTER><B><FONT COLOR="#FF0000">No checks are performed on the filtered DST in p10.11</FONT></B></CENTER>\n')
        htmlsum.write('<HR>\n')
# Internal buffers for the various runs and for the event counters
    listhtml=[]
    sumvers=['t01.56',0,'01-JAN-00',999999,'01-JAN-00',0,0,0,0,0,'01-JAN-00',1]
    totevt=[0,0,0,0,0]
    datelast=''
    runlast=999999
# Parse the HTML files corresponding to each individual run
    for i in range(129,1000):
        directory='%3.3d'%(i)
        if directory in os.listdir(htmldir):
            localdir='%s/%s'%(htmldir,directory)
            listfiles=[]
            listfiles=os.listdir(localdir)
            listfiles.sort()
            for file in listfiles:
		if file[0:2]!="run":
		    continue
                runnum=string.atoi(file[3:13])
                runver=file[14:20]
                if ( runver==version[0] ):
                    info=RunInfo(runnum,version[0])
                    info.getInfoHTML(htmldir)
                    process=info.wasProcessed()
                    events=info.getNumEvt()   
                    datelast=info.getDate()
                    datecreate=info.getCreationDate()
                    if ( process or ( not process and runnum>=string.atoi(version[1]) and runnum<=string.atoi(version[2]) ) ):
                        listhtml.append(info)
                        runlast=runnum
                        for i in range(len(events)):
                            totevt[i]=totevt[i]+events[i]
                    if ( ( not process and ( runnum<string.atoi(version[1]) or runnum>string.atoi(version[2]) ) ) or events[0]<2 ):
                        os.remove('%s/%s'%(localdir,file))
# Write a first table containing the total number of events
    if ( len(listhtml)>0 ):
        datefirst=listhtml[0].getDate()
        htmlsum.write('<TABLE BORDER=2 CELLSPACING=2 CELLPADDING=2 WIDTH="100%">\n')
        htmlsum.write('<TR BGCOLOR="#99FFFF">\n')
        htmlsum.write('   <TH><B>Number of runs</B></TH>\n')
        htmlsum.write('   <TH><B>Starting from </B></TH>\n')
        htmlsum.write('   <TH><B>Ending on</B></TH>\n')
        htmlsum.write('   <TH><B>RAW data events</B></TH>\n')
        htmlsum.write('   <TH><B>DST events</B></TH>\n')
        htmlsum.write('   <TH><B>thumbnails or ROOT tuples</B></TH>\n')
        htmlsum.write('   <TH><B>Filtered events</B></TH>\n')
        htmlsum.write('   <TH><B>Filtered ROOT</B></TH>\n')
        htmlsum.write('</TR>\n')
        htmlsum.write('<TR BGCOLOR="#FFFF00">\n')
        htmlsum.write('   <TD ALIGN=CENTER>%d</TD>\n'%(len(listhtml)))
        htmlsum.write('   <TD ALIGN=CENTER>%s</TD>\n'%(datefirst))
        htmlsum.write('   <TD ALIGN=CENTER>%s</TD>\n'%(datelast))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[0]))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[1]))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[2]))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[3]))
        htmlsum.write('   <TD ALIGN=RIGHT>%s</TD>\n'%(totevt[4]))
        htmlsum.write('</TR>\n')
        htmlsum.write('</TABLE>\n')
        htmlsum.write('<HR>\n')
        sumvers[0]=version[0]
        sumvers[1]=listhtml[0].getRun()
        sumvers[2]=datefirst
        sumvers[3]=runlast
        sumvers[4]=datelast
        sumvers[5]=totevt[0]
        sumvers[6]=totevt[1]
        sumvers[7]=totevt[2]
        sumvers[8]=totevt[3]
        sumvers[9]=totevt[4]
        sumvers[10]=datecreate
        sumvers[11]=0
# Write a second table explaining the color coding and the various error conditions.
    colorCodes(htmlsum,version)
# Now the third table with the details of each run 
    htmlsum.write('<TABLE BORDER=2 CELLSPACING=2 CELLPADDING=2 WIDTH="100%">\n')
    htmlsum.write('<TR BGCOLOR="#99FFFF">\n')
    htmlsum.write('   <TH><B>Run number</B></TH>\n')
    htmlsum.write('   <TH><B>Date</B></TH>\n')
    htmlsum.write('   <TH><B>Trigger configuration file</B></TH>\n')
    htmlsum.write('   <TH><B>Data stream</B></TH>\n')
    htmlsum.write('   <TH><B>Number of events</B></TH>\n')
    htmlsum.write('   <TH><B>Processing status</B></TH>\n')
    htmlsum.write('   <TH><B>DST fraction</B></TH>\n')
    htmlsum.write('   <TH><B>thumbnails or ROOT fraction</B></TH>\n')
    htmlsum.write('   <TH><B>recoS fraction</B></TH>\n')
    htmlsum.write('   <TH><B>Consistency check</B></TH>\n')
    htmlsum.write('   <TH><B>Merging errors</B></TH>\n')
    htmlsum.write('</TR>\n')
    for run in listhtml:
        run.printInfoHTMLVersion(htmlsum)
    htmlsum.write('</TABLE>\n')
    htmlsum.write('<HR>')
    htmlsum.write('<I>This page was created by MINTS using the information in the SAM and Runs databases</I>\n')
    htmlsum.write('<BR>\n')
    currentdate=time.strftime('%a %b %d %Y at %H:%M:%S',time.localtime(time.time()))
    htmlsum.write('<I>MINTS updated this page on %s</I>\n'%(currentdate))
    htmlsum.close()
    return sumvers

def readConfig(configFile):
# Read in the configuration file for MINTS
    try:
        configuration=open('%s'%(configFile),"r")
    except:
        sys.stderr.write('\nmkWebRunInfo.py: could not open configuration file %s\n'%(configFile))
        sys.stderr.write('                 abort execution\n\n')
        usage()
        sys.exit(2)
    htmldir=''
    listofversions=[]
    listoftriggers=[]
    for line in configuration.readlines():
        if ( line[0:1]!='#' ):
            tokens=string.split(line)
	    if len(tokens) == 0:
		continue
            if ( tokens[0]=='htmldir'):
                htmldir=tokens[1]
            elif ( tokens[0]=='recoversion'):
                recoversion=[tokens[1],tokens[2],tokens[3]]
                listofversions.append(recoversion)
            elif ( tokens[0]=='trigger'):
                listoftriggers.append(tokens[1])
    configured=0
    if ( htmldir!='' and len(listofversions)>0 and len(listoftriggers)>0 ):
        configured=1
    return configured,htmldir,listofversions,listoftriggers           

def usage():
    sys.stderr.write('mkWebRunInfo.py -c mkWebRunInfo.config\n\n')
    sys.stderr.write('display in WWW format the information produced by the checkRunInfo.py script\n')
    sys.stderr.write('\t-c,--config-file\t\tConfiguration file\n')
    sys.stderr.write('Options:\n')
    sys.stderr.write('\t-h,--help\t\tThis information\n')
    sys.stderr.write('\t-v,--verbose\t\tPrint a simple ascii table of events processed in each run\n')
    return

def main():
    
    verbose=0 
    configured=0
    htmldir=''
    listofversions=[]
    listoftriggers=[]

    try:
        opts, args = getopt.getopt(sys.argv[1:], "hvc:")
    except getopt.GetoptError:
        usage()
        sys.exit(2)

    for o,a in opts:
        if o in ("-h", "--help"):
            usage()
            sys.exit()

        if o in ("-v","--verbose"):
            verbose=1

        if o in ("-c","--config-file"):
            configured,htmldir,listofversions,listoftriggers=readConfig(a)

    if ( configured==0 ):
        sys.stderr.write('\nmkWebRunInfo.py: you did not specify a configuration file \n\n')
        usage()
        sys.exit(2)
        
    index=HTMLindex(htmldir)
    index.HTMLheader()

    index.HTMLbeginByVersion()
    for version in listofversions:
        sumvers=makeSummaryByVersion(version,htmldir)
        if ( sumvers[11]==0 ):
            index.HTMLaddByVersion(sumvers)

    listofversions.reverse()
    sumrun,monthlist,listhtml=makeSummaryByRunnum(verbose,listofversions,htmldir)
    index.HTMLaddByVersion(sumrun)
    index.HTMLendByVersion()

    index.HTMLbeginByDate()
    monthlist.reverse()
    for month in monthlist:
        summonth=makeSummaryByMonth(listhtml,month,htmldir)
        if ( summonth[8]==0 ):
            index.HTMLaddByDate(summonth)
    index.HTMLendByDate()

    index.HTMLbeginByTrigger()
    for trigger in listoftriggers:
        sumtrig=makeSummaryByTrigger(listhtml,trigger,listoftriggers,htmldir)
        if ( sumtrig[10]==0 ):
            index.HTMLaddByTrigger(sumtrig)
    index.HTMLendByTrigger()

    index.HTMLfooter()
    index.HTMLupdatepage()

    
main()
