#include <lm_access/LumFileMap.hpp>
#include <lm_access/filename_util.hpp>
#include <lm_access/LmFileParentage.hpp>
#include <cassert>
#include <iostream>
#include <unistd.h>

using namespace std;

// -----------------------------------------------------------------


void LumFileMap::_check_lbn_dir() const {


  if(lm_access::lbn_dir.find("stage3",0) == std::string::npos){
    std::cerr << "Don't seem to be using stage3 files, either update to stage3 or use v00-03-10 of lm_access and set rcp to stage2 in lm_access_pkg ";
    std::cerr << std::endl;
    exit(1);
  }

  if (access(lm_access::lbn_dir.c_str(), R_OK)) {
    std::cerr << "Cannot read from stage3 LBN directory "
              << lm_access::lbn_dir 
              << " if you only have access to stage2 files, use lm_access v00-03-10 and lm_access_pkg v00-01-00 "
              << std::endl;
    exit(1);
  } else return;
}

bool LumFileMap::check_lbn_dir() const {
  if(lm_access::lbn_dir.find("stage3",0) == std::string::npos){
    std::cerr << "Don't seem to be using stage3 files, either update to stage3 or use v00-03-10 of lm_access and set rcp to stage2 in lm_access_pkg ";
    std::cerr << std::endl;
    return 0;
  }
  if (access(lm_access::lbn_dir.c_str(), R_OK)) {
    std::cerr << "Cannot read from stage3 LBN directory "
              << lm_access::lbn_dir 
              << " if you only have access to stage2 files, use lm_access v00-03-10 and lm_access_pkg v00-01-00 "
              << std::endl;
    return 0;
  } else return 1;
}
// -----------------------------------------------------------------

void LumFileMap::set_lbn_dir(const std::string input_lbn_dir) const {
  LmAccessInterface *interface = LmAccessInterface::get_Instance(_debug);
  interface->set_lbn_dir(input_lbn_dir);  
/*
  std::string full_path = lm_access::filename_expand(input_lbn_dir);
  if(full_path == ""){ 
    lm_access::lbn_dir = lm_access::default_lbn_dir;
  }
  else{
    lm_access::lbn_dir = full_path;
    std::cerr << "lm_access::lbn_dir set to " << lm_access::lbn_dir << std::endl;
  }
*/
}

// -----------------------------------------------------------------


LumFileMap::LumFileMap(int ntriggers, const char* trigger_names[], 
                       const lm_access::LmType& type) : 
  _lm_map(), _lm_type(type), _triggers(), _debug(0), _hasrunquality(0), _hasbadlbnlist(0), _hasparentagepath(0) {
  //std::cout << " make new filemap char* " << std::endl;
  // _check_lbn_dir();

  for(lm_access::TriggerID id = 0; id < ntriggers; id++) {
    _triggers[trigger_names[id]] = id + 1;
  }
};

// -----------------------------------------------------------------

LumFileMap::LumFileMap(const std::list<std::string>& trigger_list,
                       const lm_access::LmType& type) :
  _lm_map(), _lm_type(type), _triggers(), _debug(0), _hasrunquality(0), _hasbadlbnlist(0), _hasparentagepath(0) {
  //cout << " make new filemap string " << endl;
  //_check_lbn_dir();
  int id = 1;
  std::list<std::string>::const_iterator it;
  for(it = trigger_list.begin(); it != trigger_list.end(); it++) {
    _triggers[*it] = id++;
  }
}

// -----------------------------------------------------------------

LumFileMap::LumFileMap(const LumFileMap& rhs) : 
  _lm_map(rhs._lm_map), _lm_type(rhs._lm_type), _triggers(rhs._triggers),
_debug(rhs._debug) {
  //cout << " make new filemap copy constructor " << endl;

  //_check_lbn_dir();
    _hasrunquality = rhs._hasrunquality;
    _hasbadlbnlist = rhs._hasbadlbnlist;
    _hasparentagepath = rhs._hasparentagepath;
    myrunquality =rhs.myrunquality;
    mybadlbnlist =rhs.mybadlbnlist;
    myparentagepath = rhs.myparentagepath;
    myparentagetag = rhs.myparentagetag;
};


// -----------------------------------------------------------------

LumFileMap& LumFileMap::operator=(const LumFileMap& rhs) {
  //cout << " make new filemap copy = " << endl;
  if (this != &rhs) {
    _lm_map = rhs._lm_map;
    _lm_type = rhs._lm_type;
    _triggers = rhs._triggers;
    _debug = rhs._debug;
    _hasrunquality = rhs._hasrunquality;
    _hasbadlbnlist = rhs._hasbadlbnlist;
    _hasparentagepath = rhs._hasparentagepath;
    myrunquality =rhs.myrunquality;
    mybadlbnlist =rhs.mybadlbnlist;
    myparentagepath = rhs.myparentagepath;
    myparentagetag = rhs.myparentagetag;
  }
  return *this;
}


// -----------------------------------------------------------------

LumFile& LumFileMap::add(const std::string& fileID, const LumFile& f) {

  // first make certain you have information you need

  //_check_lbn_dir();

   if(_debug){
    std::cout << "LumFileMap::add " << fileID << std::endl;
  }
  if (_lm_map.find(fileID) != _lm_map.end()) {
    std::cerr << "ERROR: " 
              << "LumFile& LumFileMap::add(string&, LumFile& f) - "
              << " Entry with key " << fileID << " already exists!"
              << std::endl;
    exit(1);
  }

 _lm_map[fileID] = f;
  _lm_map[fileID].setdebug(_debug);
  return (_lm_map[fileID]);
}

// do it all for a single file

bool LumFileMap::addAndLoad(const std::string& fileID, const lm_access::FileType ft, lm_access::LmRunQuality* prunquality, const std::string& parentage_path, const std::string& parentage_tag) {

  int istart = 0;
  std::list<int> lbnlist; 

  // get parentage information
  std::string filepath;

  if(parentage_path == ""){
    filepath = "./"+fileID;
  }
  else{
    filepath = parentage_path+"/"+fileID;
  }
  lm_access::LmFileParentage p(filepath,parentage_tag);
  lm_access::LmFileParentage_const_iterator it;

  // loop over lbns in parentage

  for (it = p.begin(); it!= p.end(); it++){
    int lbn = it->first;
    cout << "Testing Lbn = " << lbn << std::endl;
    const lm_access::LBNParentage lbnp = it->second;
    int run = lbnp.getRun(0);
    std::string stream = lbnp.getStream(0);
  
    if(stream == string("000")){
      cout << " this is probably stream 000, skip " << lbn << endl;
      continue;
    }
    std::string version = lbnp.getVersion(0);
    std::string parentversion = lbnp.getParentVersion(0);
    if(istart == 0){
      add(fileID,LumFile(ft,version,parentversion));
      istart ++;
    }
 
    // cut out bad runs
    int numrange = _runrangelo.size();
    bool okrange = 0;
    if (numrange == 0) okrange = 1;
    else{
      for (int k = 0; k < numrange; k++){
        if(run >= _runrangelo[k] && run <= _runrangehi[k]){
          okrange = 1;
          break;
        }
      }
    }
    if (!okrange){ 
      if(_debug) std::cout << "LumFileMap reject lbn, run " << lbn <<"," << run << " as not in run range" << std::endl;
      continue;
    }

    if(!prunquality->isGoodRun(run) || prunquality->isBadRun(run)){
      if(_debug) std::cout << "LumFileMap reject run " << run << std::endl;
      continue;
    }
   lbnlist.push_back(lbn);
//   _lm_map[fileID].downloadLBN(lbn,_triggers);
//   _lbncounter.insert(lbn);
  }
  if (lbnlist.size()>0) _lm_map[fileID].downloadLBN(lbnlist,_triggers);
  for (std::list<int>::const_iterator it=lbnlist.begin();it!=lbnlist.end();it++) {
    _lbncounter.insert(*it);
  }
  return istart;
}
    
bool LumFileMap::addAndLoad(const std::string& fileID, const lm_access::FileType ft) {

  std::list<int> lbnlist; 
  if(!_hasparentagepath){
    std::cout << " can only use addAndLoad after attachParentage " << std::endl;
    assert(_hasparentagepath);
  }
  int istart = 0;
  
  // get parentage information
  std::string filepath;
  
  if(myparentagepath == ""){
    filepath = "./"+fileID;
  }
  else{
    filepath = myparentagepath+"/"+fileID;
  }
  lm_access::LmFileParentage p(filepath,myparentagetag);
  lm_access::LmFileParentage_const_iterator it;
  
  // loop over lbns in parentage
  
  for (it = p.begin(); it!= p.end(); it++){
    int lbn = it->first;
    const lm_access::LBNParentage lbnp = it->second;
    int run = lbnp.getRun(0);
    int numrange = _runrangelo.size();
    std::string stream = lbnp.getStream(0);
    if(stream == string("000")){
      cout << " this is from partition 000, skip " << lbn << endl;
      continue;
    }
    bool okrange = 0;

    if (numrange == 0) okrange = 1;
    else{
      for (int k = 0; k < numrange; k++){
        if(run >= _runrangelo[k] && run <= _runrangehi[k]){
          okrange = 1;
          break;
        }
      }
    }

    if (!okrange){ 
      if(_debug) std::cout << "LumFileMap reject lbn, run " << lbn << "," << run << " as not in run range" << std::endl;
      continue;
    }   
    std::string version = lbnp.getVersion(0);
    std::string parentversion = lbnp.getParentVersion(0);
    if(istart == 0){
      add(fileID,LumFile(ft,version,parentversion));
      istart ++;
    }
    
    // cut out bad runs
    
    if(_hasrunquality && (!myrunquality->isGoodRun(run) || myrunquality->isBadRun(run))){
      if(_debug) std::cout << "LumFileMap reject run " << run << std::endl;
      continue;
    }
    
    
    // cut out bad lbns
    
    if(_hasbadlbnlist && mybadlbnlist->isBadLBN(lbn)){
      if(_debug) std::cout << "LumFileMap reject LBN " << lbn << std::endl;
      continue;
    }
    lbnlist.push_back(lbn);
//   _lm_map[fileID].downloadLBN(lbn,_triggers);
//   _lbncounter.insert(lbn);
  }
  if (lbnlist.size()>0) _lm_map[fileID].downloadLBN(lbnlist,_triggers);
  for (std::list<int>::const_iterator it=lbnlist.begin();it!=lbnlist.end();it++) {
    _lbncounter.insert(*it);
  }
  return istart;
}
    


// -----------------------------------------------------------------

  int LumFileMap::downloadLBN(const std::string& fileID, int lbn) {
  std::map<std::string, LumFile>::iterator it;
  it = _lm_map.find(fileID);
  if (it == _lm_map.end()) {
     std::cerr << "ERROR: "
               << "int LumFileMap::downloadLBN(string&, int) - "
               << "Key " << fileID << " does not exists!"
               << std::endl;
     exit(1);
  } 
  if(_debug){
    std::cout << "LumFileMap::downloadLBN " << fileID << " " << lbn << std::endl;
  }
  bool status = it->second.downloadLBN(lbn, _triggers);
  _lbncounter.insert(lbn);
  return status;
}

// -----------------------------------------------------------------

int LumFileMap::isGoodLBN(const std::string& fileID, int lbn, 
                          const std::string& trigger) const {
  lm_access::TriggerMap::const_iterator it_trig = _triggers.find(trigger);
  if (it_trig == _triggers.end()) return 0;
  std::map<std::string, LumFile>::const_iterator it;
  if(_debug){ 
    std::cout << "LumFileMap::isGoodLBN start" << fileID << " " << lbn << " " << trigger << std::endl; 
  }
  it = _lm_map.find(fileID);
  if (it == _lm_map.end()) {
     std::cerr << "ERROR: "
               << "int LumFileMap::isGoodLBN(string&, int, string&) - "
               << "Key " << fileID << " does not exists!"
               << " Must return bad status "
               << std::endl;
     return 0;
  } 
  int result = it->second.isGoodLBN(lbn, it_trig->second, _lm_type);
  if(_debug){
    std::cout << "LumFileMap::isGoodLBN results " << it_trig->second << " " << result << " LBN = " << lbn << std::endl;
  }
  return result;
}

// -----------------------------------------------------------------



lm_access::LmType LumFileMap::lm_type() const {return _lm_type;;}

// -----------------------------------------------------------------


double LumFileMap::luminosity(const std::string& trigger, const int tick) const { 
  lm_access::TriggerMap::const_iterator it_trig = _triggers.find(trigger);
  if (it_trig == _triggers.end()) return 0;
  std::map<std::string, LumFile>::const_iterator it;
  double result = 0;
  for(it = _lm_map.begin(); it != _lm_map.end(); it++) {
    result += it->second.luminosity(it_trig->second, _lm_type, tick);
  }
  return result;
}

// -----------------------------------------------------------------

long LumFileMap::acceptsL1(const std::string& trigger) const { 
  lm_access::TriggerMap::const_iterator it_trig = _triggers.find(trigger);
  if (it_trig == _triggers.end()) return 0;
  std::map<std::string, LumFile>::const_iterator it;
  long result = 0;
  for(it = _lm_map.begin(); it != _lm_map.end(); it++) {
    result += it->second.acceptsL1(it_trig->second,_lm_type);
  }
  return result;
}

// -----------------------------------------------------------------

long LumFileMap::acceptsL2(const std::string& trigger) const { 
  lm_access::TriggerMap::const_iterator it_trig = _triggers.find(trigger);
  if (it_trig == _triggers.end()) return 0;
  std::map<std::string, LumFile>::const_iterator it;
  long result = 0;
  for(it = _lm_map.begin(); it != _lm_map.end(); it++) {
    result += it->second.acceptsL2(it_trig->second,_lm_type);
  }
  return result;
}

// -----------------------------------------------------------------

long LumFileMap::acceptsL3(const std::string& trigger) const { 
  lm_access::TriggerMap::const_iterator it_trig = _triggers.find(trigger);
  if (it_trig == _triggers.end()) return 0;
  std::map<std::string, LumFile>::const_iterator it;
  long result = 0;
  for(it = _lm_map.begin(); it != _lm_map.end(); it++) {
    result += it->second.acceptsL3(it_trig->second,_lm_type);
  }
  return result;
}

// -----------------------------------------------------------------

int LumFileMap::disableLBN(const std::string& fileID, int lbn) {
  std::map<std::string, LumFile>::iterator it;
  it = _lm_map.find(fileID);
  if (it == _lm_map.end()) {
     std::cerr << "ERROR: "
               << "int LumFileMap::disableLBN(string&, int) - "
               << "Key " << fileID << " does not exists!"
               << std::endl;
     exit(1);
  } 
  if(_debug){
    std::cout << "LumFileMap::disableLBN " << fileID << " " << lbn << std::endl;
  }
  return it->second.disableLBN(lbn);
}

// -----------------------------------------------------------------


std::list<int> LumFileMap::getLBNList(const std::string& fileID)const{
  map<std::string, LumFile>::const_iterator it;
  it = _lm_map.find(fileID);
  if(it != _lm_map.end())  return it->second.getLBNList();
  if(_debug) std::cout << " Could not find any lbns for fileID " << fileID << " in LumFileMap " << std::endl;
  return std::list<int>();
}

bool LumFileMap::attachBadRunList(const lm_access::LmRunQuality* pRunQuality){
  myrunquality = pRunQuality;
  _hasrunquality = true;
  return pRunQuality?1:0;
}

bool LumFileMap::attachRunRange(const int runlo, const int runhi){
  _runrangelo.push_back(runlo);
  _runrangehi.push_back(runhi);
  return (_runrangelo.size() == _runrangehi.size());
}
bool LumFileMap::attachBadLBNList(const lm_access::BadLBNList* pBadLBNList){
  mybadlbnlist = pBadLBNList;
  _hasbadlbnlist = true;
  return pBadLBNList?1:0;
}

bool LumFileMap::attachParentage(const std::string& parentage_path, const std::string& parentage_tag ){
  myparentagepath = parentage_path;
  myparentagetag = parentage_tag;
  _hasparentagepath = true;
  return true;
}

















