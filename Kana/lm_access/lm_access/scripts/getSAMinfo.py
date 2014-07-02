#!/usr/bin/env python
#
# Program to report on luminosity in LBN files
#
import dcoracle
import getopt,sys

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
def infoByRun (sql,run,tier='raw'):
    l = sql.sql ("select "
                        "data_files.file_name, "
                        "data_files.file_id, "
                        #"data_files.lum_min, "
                        #"data_files.lum_max, "
                        "application_families.version "
                 "from data_files,runs,physical_datastreams, "
                      "application_families "
                 "where "
                 # Table constraints
                        "data_files.run_id=runs.run_id and "
                        "application_families.appl_family_id=data_files.appl_family_id and "
                        "data_files.stream_id=physical_datastreams.stream_id and "
                 # Data constraints
                        "runs.run_number=:p1 and "
                        "data_files.data_tier=:p2"
                 ,(run,tier))
    return l
#
# Retrieve SAM parent information by file id and tier
#
def infoByParent (sql,id,tier='reconstructed'):
    l = sql.sql ("select "
                        "data_files.file_name, "
                        "data_files.file_id "
                 "from "
                      "data_files, "
                      "file_lineages "
                 "where "
                 # Table constraints
                        "data_files.file_id=file_lineages.file_id_dest and "
                 # Data constraints
                        "file_lineages.file_id_source=:p1 and "
                        "data_files.data_tier=:p2"
                 , (id,tier))
    return l

#
# Retrieve SAM child information by file id and tier
#
def infoByChild (sql,id,tier='reconstructed'):
    l = sql.sql ("select "
                        "data_files.file_name, "
                        "data_files.file_id "
                 "from "
                      "data_files, "
                      "file_lineages "
                 "where "
                 # Table constraints
                        "data_files.file_id=file_lineages.file_id_source and "
                 # Data constraints
                        "file_lineages.file_id_dest=:p1 and "
                        "data_files.data_tier=:p2"
                 , (id,tier))
    return l


def usage():
    print 'getSAMinfo.py'
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
                                    "run="])
    except getopt.GetoptError:
        usage()
        sys.exit(2)

    samdbc = dcoracle.Connect ("samread/reader@d0ofprd1")
    sql=Sqlbase (samdbc)
    for o,a in opts:
        if o in ("-h", "--help"):
            usage()
            sys.exit()

        if o in ("-r","--run"):
            run=a

        if o in ("-f","--from"):
            if a=='raw':
                for raw,id,ver in infoByRun(sql,run,tier='raw'):
                    print '%s' % (raw)
                    for reco,nid in infoByParent(sql,id,tier='reconstructed'):
                        print '\t--> %s' % (reco)
                        for root,rid in infoByParent(sql,nid,tier='root-tuple'):
                            print '\t\t--> %s' % (root)
            elif a=='root':
                for root,rid,ver in infoByRun(sql,run,tier='root-tuple'):
                    print '%s' % (root)
                    for reco,nid in infoByChild(sql,rid,tier='reconstructed'):
                        print '\t<-- %s' % (reco)
                        for raw,id in infoByChild(sql,nid,tier='raw'):
                            print '\t\t<-- %s' % (raw)

            else:
                usage()
                sys.exit(2)
            
    del sql
    samdbc.close()

main()
