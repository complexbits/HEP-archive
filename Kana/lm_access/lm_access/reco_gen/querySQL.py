#!/usr/bin/env python
#
# Program to report on luminosity in LBN files
#
import dcoracle
import getopt,sys, pprint

class Sqlbase:
    def __init__ (self, dbc):
        self.__dbc = dbc
        self.__cursor = dbc.cursor()
        return
    
    def __del__ (self):
        del self.__dbc
        del self.__cursor
        return
    
    def dbc (self):
        return self.__dbc
    
    def sql (self, sqlexpr, args = ()):
        self.__cursor.execute (sqlexpr, args)
        return self.__cursor.fetchall ()
# 
# Retrieve SAM information by run number and tier
#
# Making query to runs database:
def infoByRun(sql,run, triggername='zero_bias'):
    m = sql.sql ("select "
                 #"run_number, "
                 #"bit_name, "
                 "bit_num, "
                 "depend_bit "
                 "from "
                 "runs.run_trigs "
                 "where "
                 "run_number=:p1 and "
                 "trg_type='L3bit' and "
                 "bit_name=:p2 "
                 ,(run, triggername))
    return m
#Getting information for Root-Tuple
def infoByFile (sql,filename):
    l = sql.sql ("select "
                 #"df.file_id, "
                 "df.file_name, "
                 "af.version, "
                 "r.run_number, "
                 "pd.physical_datastream_name, "
                 #"fl1.file_id_dest, "
                 #"fl1.file_id_source, "
                 #"df2.file_id, "
                 "df2.file_name "
                 #"df2.data_tier "
                 "from "
                 "data_files df, "
                 "data_files df2, "
                 "file_lineages fl1, "
                 "file_lineages fl2, "
                 "runs r, "
                 "physical_datastreams pd, "
                 "application_families af "
                 "where "
                 "df.file_name=:p1 and "
                 "r.run_id=df.run_id and "
                 "af.appl_family_id=df.appl_family_id and "
                 "pd.stream_id=df.stream_id and "
                 "fl1.file_id_dest=df.file_id and "
                 "fl2.file_id_dest=fl1.file_id_source and "
                 "df2.file_id=fl2.file_id_source "
                 , filename)
    return l

#Getting info for raw files:
def infoByRaw (sql,rawfile):
    l = sql.sql ("select "
                 "df.file_name, "
                 "df.event_count, "
                 "df.lum_min, "
                 "df.lum_max "
                 #"df.file_id "
                 "from "
                 "data_files df "
                 "where "
                 "df.file_name=:p1 "
                 , rawfile)
    return l

# Writting the output file
def datawrite(info):
    file='info.txt'
    FILE=open(file,'w',1)
    #print '-->',file
    #print info['TupleName'], info['Version'],\
          #info['Run'],  info['Stream'],\
          #info['L1minbit'],  info['L3minbit'],\
          #info['L1zerbit'],  info['L3zerbit'],\
          #info['Nofrawfile']
    foo1='%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n' % \
          (info['TupleName'], \
           info['Version'],\
           info['Run'],\
           info['Stream'],\
           info['L1minbit'],\
           info['L3minbit'],\
           info['L1zerbit'],\
           info['L3zerbit'],\
           info['Nofrawfile'])
    FILE.write(foo1)
    for o in info['Rawfile'].keys():
        #print o, info['Rawfile'][o]['Evnt'],\
              #info['Rawfile'][o]['BLBN'],\
              #info['Rawfile'][o]['ELBN']
        foo2='%s\t%i\t%d\t%d\n' % \
              (o, info['Rawfile'][o]['Evnt'],\
               info['Rawfile'][o]['BLBN'],\
               info['Rawfile'][o]['ELBN'])
        FILE.write(foo2)
    
    FILE.close()
    return


def usage():
    print 'Python script for direct SQL query to SAM and Run databases'
    print '\n'
    print 'Retrieves information from the SAM database'
    print 'Options:'
    print '\t-h,--help\t\tThis information'
    print '\t-r,--run\t\tThe run number of interest'
    print '\t-f,--from\t\tDirection of tree lookup'
    print '\t\t\traw\tfrom raw files to root files'
    print '\t\t\troot\tfrom root files to raw files'
    return


def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "hr:f:",
                                   ["help",
                                    "from="])
    except getopt.GetoptError:
        usage()
        sys.exit(2)
        
    samdbc = dcoracle.Connect ("samread/reader@d0ofprd1")
    sql=Sqlbase (samdbc)
    for o,a in opts:
        if o in ("-h", "--help"):
            usage()
            sys.exit()
        if o in ("-f","--from"):
            filename=a
            k=infoByFile(sql,filename)
            if len(k)==0:
                sys.stderr.write('Did not find information for the file %s in the SAM database\n'%(filename))
                sys.exit(3)
            diction={}
            diction['TupleName']=k[0][0]
            diction['Version']=k[0][1]
            diction['Run']=k[0][2]
            diction['Stream']=k[0][3]
            foo=k[0][2]
            barm=infoByRun(sql,foo, triggername='min_bias')
            if ( len(barm)>0 ):
                diction['L3minbit']=barm[0][0]
                diction['L1minbit']=barm[0][1]
            else:
                diction['L3minbit']=-1
                diction['L1minbit']=-1
            barz=infoByRun(sql,foo, triggername='zero_bias')
            if ( len(barz)>0 ):
                diction['L3zerbit']=barz[0][0]
                diction['L1zerbit']=barz[0][1]
            else:
                diction['L3zerbit']=-1
                diction['L1zerbit']=-1
            if ( len(barm)==0 and len(barz)==0 ):
                sys.stderr.write('Problems with the Runs database for run number %s \n'%(foo))
                sys.stderr.write('Cannot use mininum bias or zero bias triggers for the stage2 step \n')
                sys.stderr.write('Please investigate whether this is a real problem !!!!! \n')
                sys.exit(4)
            diction['Nofrawfile']=len(k)
            diction['Rawfile']={}
            n=0
            while n <len(k):
                foobar=k[n][4]
                cfoo=infoByRaw(sql, foobar)
                n=n+1
                if ( len(cfoo)>0 ):
                    diction['Rawfile'][foobar]={}
                    diction['Rawfile'][foobar]['Evnt']=cfoo[0][1]
                    diction['Rawfile'][foobar]['BLBN']=cfoo[0][2]
                    diction['Rawfile'][foobar]['ELBN']=cfoo[0][3]
                else:
                    sys.stderr.write('Cannot find raw data file %s in the SAM database \n'%(foobar))
                    sys.stderr.write('No way of finding the expected LBN range \n')
                    sys.exit(5)
            #print diction
            datawrite(diction)
            #pprint.pprint(k)
        else:
            usage()
            sys.exit(2)
            
    del sql
    samdbc.close()
    return

main()
