#include "lm_access/LumBlkInfo.hpp"
#include "lm_access/LumTickMap.hpp"
#include "lm_access/tickutility.hpp"



#include <list>

using namespace std;

LumBlkInfo::LumBlkInfo() :
  _debug(0),
  _lbn_file(0)
{
  tickmap = tickutility::Instance();
  tickmap->Init();

  for (int i=0;i<37;i++) {
     _lumDelivered[i] = 0;
     _corrNL[i] = 0;
  }
}

LumBlkInfo::LumBlkInfo(const LumBlkInfo& rhs) :
  _debug(0),
  _lbn_file(rhs._lbn_file),
  _triggers(rhs._triggers), 
  _good_releases(rhs._good_releases)
{
  tickmap = tickutility::Instance();
  tickmap->Init();
};

LumBlkInfo::LumBlkInfo(gz::igzstream& s, 
		       const lm_access::TriggerMap& triggers) : 
  _debug(0),
  _lbn_file(1)
{
  tickmap = tickutility::Instance();
  tickmap->Init();
  string mark;

  const string DEADBEEF = "0xDEADBEEF";
  const string B0CABEEF = "0xB0CABEEF";
  const string BADBEEF = "0xBADBEEF";
  long lm_ignoredNumber = 0;
  float lm_old_luminosity = -1;
  double nb_ticks = 0;

  /* read the luminosity information per trigger */
  while (1) {
    s >> mark;
    if (s.fail()) break;
    if (mark == DEADBEEF) break;
    float lm_L1 = -1;
    float lm_Raw = -1;
    int hasL2 = -1;
    long aL1 = 0, aL2 = 0, aL3 = 0;
    s >> lm_L1 >> lm_Raw >> hasL2 >> lm_ignoredNumber >> lm_ignoredNumber >> lm_ignoredNumber >> aL1 >> aL2 >> aL3;
    
    if (s.fail()) break;
    lm_access::TriggerMap::const_iterator it = triggers.find(mark);
    if (it != triggers.end()) {
      lm_L1 *= lm_access::lmCorrection;
      lm_Raw *= lm_access::lmCorrection;
      _triggers[it->second] = LumTrigger(lm_L1, lm_Raw, hasL2, aL1, aL2, aL3);
    }
  }

  /* read the release information */

  while (1) {
    s >> mark;   
    if (s.fail()) break;
    if (mark == B0CABEEF) break;    

    list<string> buffer;
    while (1) {
      if (s.fail()) break;
      if (! mark.size()) break;
      if (mark == "[]") break;
      if (mark[0] == '[') { /* skip everything between '[' and ']' */
	while (1) {
	  s >> mark;
	  if (s.fail()) break;
	  if (! mark.size()) break;
	  if (mark[mark.size() - 1] == ']') break;
	}
	break;
      }  /* skip everything after '[' */
      buffer.push_front(mark);
      s >> mark;
    } /* read line */
    if ( (! s.fail()) && (mark.size()) && 
	 (mark[mark.size() - 1] == ']') && buffer.size() ) {
      list<string>::const_iterator it_s = buffer.begin();
      int keepL2 = atoi(it_s->c_str());
      string release = "";
      while ( ++it_s != buffer.end() ) release = *it_s + " " + release;
      _good_releases[LumFileRelease(release)] = keepL2;
      //cout << "Release: " << release << ", keepL2 = " << keepL2 << endl;
    }
  }

  /* luminosity correction from the file read */

  if (mark == B0CABEEF) {
  if (_debug) cout << "LumBlkInfo: Reading tick information"<<std::endl;
    if (!s.fail()) {

      float lm_L1 = -1;
      float lm_Raw = -1;
      s >> nb_ticks >> lm_old_luminosity;

      // disable the rescaling feature

      lm_old_luminosity = -1;

      std::map<lm_access::TriggerID, LumTrigger>::iterator it;
      for(it = _triggers.begin(); it != _triggers.end(); it++) {
	if ((lm_old_luminosity!=-1) && (lm_access::effXsec>0)) {
	   cout<< " In code that should never run in LumBlkInfo  " << endl;
	  lm_L1 = it->second.luml1()*(lm_old_luminosity/(lm_access::effXsec*1000));
	  lm_Raw = it->second.lumraw()*(lm_old_luminosity/(lm_access::effXsec*1000));
	  it->second.set_luml1(lm_L1);
	}
      }

      /* delivered luminosity calculation */
      if (_debug) cout << "LumBlkInfo: deliverd lum. calculation" << std::endl;
      string tick;
      float pHalo, pbarHalo;
 

      _lumDelivered[0]=0.0;
      float luminosity;
      float corrected = 0.;
      while (1) {
	s >> tick;
	if (s.fail()) break;
	if (tick==BADBEEF) break;
	s >> luminosity >> pHalo >> pbarHalo;

	if (s.fail()) break;
	int index = tickmap->tickindex(tick);
	if(index < 1 || index > 36){
	  cerr << " Invalid tick number in lm_access::LumBlkInfo read !!! " << tick << endl;
	  luminosity = 0.;
	}
	// tranform instantaneous into integrated lum
	_lumDelivered[index] = luminosity*nb_ticks*lm_access::conversion_factor;

      // find  non-linearity correction HMS/BC 9-10-2004
      // but don't apply it now, it is applied in the functions.

	if(_lumDelivered[index] > 0){
	  _corrNL[index] =  (1.+ tickmap->beta(index))/(1.+tickmap->offset(index));
	}
	else{
	  _corrNL[index] = 1.;
	}	
	corrected += _lumDelivered[index]*_corrNL[index];

	if(_debug) cout << index << " corrNL " << _corrNL[index]  << " " << _lumDelivered[index] << endl;
	_lumDelivered[0] += _lumDelivered[index];
      }  // end of read loop?

      // calculate an average correction from the pieces
      
      if(corrected  != -1.0){
	_corrNL[0]=corrected/_lumDelivered[0];
      }
      else{
	_corrNL[0] = 1.;
      }
      
    }
    
  
      if(_debug) cout << _lbn << " corrNL " << _corrNL[0]  << " " << _lumDelivered[0] << endl;
  }

  
 

  return;
}

LumBlkInfo& LumBlkInfo::operator=(const LumBlkInfo& rhs) {
  if (this != & rhs) {
    _lbn_file = rhs._lbn_file;
    _triggers = rhs._triggers;
    _good_releases = rhs._good_releases;
    for(int i = 0; i < 37; i++){
      _lumDelivered[i] = rhs._lumDelivered[i];
      _corrNL[i] = rhs._corrNL[i];
    }
  }
  return *this;
}

double LumBlkInfo::luml1(const lm_access::TriggerID& triggerID, const int tick) const {
  std::map<lm_access::TriggerID, LumTrigger>::const_iterator it = 
    _triggers.find(triggerID);
  
  if (it != _triggers.end()){
    if (_lumDelivered[0] == 0) return 0.0;
    
    if(tick == 0){
      return (double) it->second.luml1()*_corrNL[0];
    }
    else{
      int index = tickmap->tickindex(tick);
      if(index < 1){
	cerr << " invalid tick number in lm_access::luml1 " << index << " " << tick << endl;
      }
      return (double) it->second.luml1()*_corrNL[index]*_lumDelivered[index]/_lumDelivered[0];
    }									     
    
  }
  else return -1;
}

double LumBlkInfo::lumraw(const lm_access::TriggerID& triggerID, const int tick) const {
  std::map<lm_access::TriggerID, LumTrigger>::const_iterator it = 
    _triggers.find(triggerID);
  //cout << _lbn << " apply " << _corrNL << " to  lumraw for trigger " << triggerID << endl;
  if (it != _triggers.end()){
    if (_lumDelivered[0] == 0) return 0.0;
    
    if(tick == 0){
      if(_debug)cout << " raw " << it->second.lumraw() << " " << _corrNL[0] << endl;
      return (double) it->second.lumraw()*_corrNL[0];
    }
    else{
      int index = tickmap->tickindex(tick);
      if(index < 1){
	cerr << " invalid tick number in lm_access " << tick << endl;
      }
      return (double) it->second.lumraw()*_corrNL[index]*_lumDelivered[index]/_lumDelivered[0];
            
    }
  }
  else return -1;
  
}

double LumBlkInfo::lumDelivered(const int tick) const {
  
  if(tick == 0) {
    return _lumDelivered[0]*_corrNL[0];
  }
  else{      
    int index = tickmap->tickindex(tick);
    if(index < 1){
      cerr << " invalid tick number in lm_access " << tick << endl;
    }
    return (double) _lumDelivered[index]*_corrNL[index];
  }
  
}

double LumBlkInfo::luminosity(const lm_access::TriggerID& triggerID,
			      const lm_access::LmType& type, const int tick) const {
  switch (type) {
  case lm_access::Triggered : return luml1(triggerID,tick);
  case lm_access::Recorded :
  case lm_access::Reconstructed :
  case lm_access::ReconstructedDontCheckL3 : return lumraw(triggerID, tick);
  case lm_access::Delivered : return lumDelivered(tick);
  default: 
    std::cerr << "LumBlkInfo::luminosity LmType unknown " << std::endl; 
    return -1;
  
  };
  return -1;
}

long LumBlkInfo::acceptsL1(const lm_access::TriggerID& triggerID) const {
    std::map<lm_access::TriggerID, LumTrigger>::const_iterator it = 
	_triggers.find(triggerID);
    if (it != _triggers.end()) return (int) it->second.acceptsL1();
    else return -1;
}

long LumBlkInfo::acceptsL2(const lm_access::TriggerID& triggerID) const {
    std::map<lm_access::TriggerID, LumTrigger>::const_iterator it = 
	_triggers.find(triggerID);
    if (it != _triggers.end()) return (int) it->second.acceptsL2();
    else return -1;
}

long LumBlkInfo::acceptsL3(const lm_access::TriggerID& triggerID) const {
    std::map<lm_access::TriggerID, LumTrigger>::const_iterator it = 
	_triggers.find(triggerID);
    if (it != _triggers.end()) return (int) it->second.acceptsL3();
    else return -1;
}

int LumBlkInfo::lbn_file_status() const {
  if (_debug){
    std::cout << "LumBlkInfo::lbn_file_status " << _lbn_file << std::endl;
}
  return _lbn_file;
};

int LumBlkInfo::trigger_status(const lm_access::TriggerID triggerID,
			       const lm_access::LmType& type, int keepL2) const {
  if (type == lm_access::Delivered) return (_lumDelivered >= 0);
  std::map<lm_access::TriggerID, LumTrigger>::const_iterator it_trig = 
    _triggers.find(triggerID);
  if (it_trig == _triggers.end()) return 0;
  const LumTrigger& lm_trigger = it_trig->second;
  int isLuminosityKnown;
  switch (type) {

  case lm_access::Triggered : return (lm_trigger.luml1() >= 0);
  case lm_access::Recorded :
    if(_debug){
      cout << "LumBlkInfo::trigger_status Recorded " << lm_trigger.lumraw() << endl;
    }
  case lm_access::ReconstructedDontCheckL3 :
    if(_debug){
      cout << "LumBlkInfo::trigger_status ReconstructedDontCheckL3 " << lm_trigger.lumraw() << endl;
    }
    return (lm_trigger.lumraw() >= 0);
  case lm_access::Reconstructed :
    isLuminosityKnown = (lm_trigger.lumraw() >= 0);
    return ( (keepL2) ? isLuminosityKnown : 
	     ( (isLuminosityKnown) && (lm_trigger.hasL2() == 0) ) );
  default: return 0;
  };
}

int LumBlkInfo::release_status(const LumFileRelease& lm_release, int& keepL2) const
{
  keepL2 = 0;   /* set as the default the worst scenario */
  /* raw file is always good, anyway, if somebody asks for Recorded luminosity,
     lm_access package does not checking at all the release informtion
   */
  if ( lm_release.type() == lm_access::raw ) {
    keepL2 = 1;
    return 1;
  }
  /* if the release is exactly listed in the list of good releases */
  map<LumFileRelease, int>::const_iterator it = _good_releases.find(lm_release);
  if (it != _good_releases.end()) {
    keepL2 = it->second;
    return 1;
  }

  /* for reco files : if the release was not found check whether there is some 
     "daugther" (recoA or tmb) good release (*/
  if ( lm_release.type() == lm_access::reconstructed ) {
    int isGood = 0;
    it = _good_releases.begin();
    while ( (it != _good_releases.end()) && (! isGood) ) {
      const LumFileRelease& currRelease = it->first;
      if ( (currRelease.type() == lm_access::roottuple) ||
	   (currRelease.type() == lm_access::thumbnail) ) {

	if ( currRelease.parent_release() == lm_release.release() ) {
	  isGood = 1;
	  keepL2 = it->second;
	}
      }
      ++it;
    }
    return isGood;
  }
  /* logic for tmb 
   *    if release version is marked as *, only the parent version is checked
   */
  if ( ( lm_release.type() == lm_access::thumbnail ) && 
       ( lm_release.release() == "*" ) ){
    int isGood = 0;
    std::map<LumFileRelease, int>::const_iterator it;
    for ( it = _good_releases.begin(); 
	  ( (it != _good_releases.end()) && (! isGood) ); it++ ) {
      const LumFileRelease& currRelease = it->first;
      if ( currRelease.type() != lm_access::thumbnail ) continue;
      isGood = ( currRelease.parent_release() == lm_release.parent_release() );
      if (isGood) keepL2 = it->second;
    }
    return isGood;
  }

  /* everything else is unknown, and so the release is bad */
  return 0;
}
int LumBlkInfo::status(const lm_access::TriggerID triggerID,
		       const lm_access::LmType& type,
		       const LumFileRelease& lm_release) const {
  if (! lbn_file_status()) return 0;
  int keepL2;
  switch (type) {
  case lm_access::Delivered : return 1;
  case lm_access::Triggered : if(_debug){
    std::cout << "LumBlkInfo::status Triggered" << trigger_status(triggerID,type,1) << std::endl;
  }

  case lm_access::Recorded :
    if(_debug){
      std::cout << "LumBlkInfo::status Recorded" << trigger_status(triggerID,type,1) << std::endl;
    }
    return trigger_status(triggerID, type, 1);
  case lm_access::ReconstructedDontCheckL3 :
    return (release_status(lm_release, keepL2) && trigger_status(triggerID, type, 1));
  case lm_access::Reconstructed :
    if (! release_status(lm_release, keepL2)) return 0;
    else return trigger_status(triggerID, type, keepL2);
  default:
    if(_debug){
      std::cout << "LumBlkInfo::status Default" << trigger_status(triggerID,type,1) << std::endl;
    }
    return 0;
  };

  return 0;
}

void LumBlkInfo::print(std::ostream& s) const {
  std::map<lm_access::TriggerID, LumTrigger>::const_iterator it_trig;
 
  
  for(it_trig = _triggers.begin(); it_trig != _triggers.end(); it_trig++) {
    const LumTrigger& lm_trig = it_trig->second;
    lm_access::LmType t;
    t = lm_access::Delivered;
    s << "Delivered Trigger Status:" << trigger_status(it_trig->first,t,lm_trig.hasL2()) << "\t";
    s << "Delivered Luminosity:" << luminosity(it_trig->first,t) << " mb-1\n"; 
    t = lm_access::Triggered;
    s << "Triggered Trigger Status:" << trigger_status(it_trig->first,t,lm_trig.hasL2()) << "\t";
    s << "Triggered Luminosity:" << luminosity(it_trig->first,t) << " mb-1\n"; 
    t = lm_access::Recorded;
    s << "Recorded Trigger Status:" << trigger_status(it_trig->first,t,lm_trig.hasL2()) << "\t";

    s << "Recorded Luminosity:"  <<  luminosity(it_trig->first,t) << " mb-1\n"; 
    

    s << "Trigger has L2?: " <<lm_trig.hasL2() << "\n "
     << "L1 Accepts: "<< lm_trig.acceptsL1() << "\t "
     << "L2 Accepts: "<< lm_trig.acceptsL2() << "\t "
     << "L3 Accepts: "<< lm_trig.acceptsL3() << "\t "
     << std::endl;
  }

  //  s << "DEADBEEF" << std::endl;
  s << "Reconstructed  information " << std::endl;

  std::map<LumFileRelease, int>::const_iterator it_r;
  for(it_r = _good_releases.begin(); it_r != _good_releases.end(); it_r++) {
    int keep = it_r->second;
    s << it_r->first.str() << ", keepL2 = " << it_r->second << ", status = "<<
      release_status(it_r->first,keep) <<  std::endl;
    
  }

  // by tick integrated
  for(int i = 1; i < 37; i++){
    int tick = tickmap->ticklist(i);
    s << "Delivered Luminosity by tick:\t" << tick << "\t" <<  luminosity(it_trig->first,lm_access::Delivered, tick) << " mb-1\n"; 
  }
}

LumBlkInfo::LumBlkInfo(int lbn, const lm_access::TriggerMap& triggers):
  _debug(0),
  _lbn_file(0),
  _lbn(lbn)
{

    tickmap = tickutility::Instance();
    tickmap->Init();

    for (int i=0;i<37;i++) {_lumDelivered[i]= 0;_corrNL[i] = 0;}

    list<string> _listtriggers;
    for (lm_access::TriggerMap::const_iterator it=triggers.begin();it!=triggers.end();it++)
        _listtriggers.push_back(it->first);

    if (_debug) cout << "LumBlkInfo: Creating interface to the data." << std::endl;

    LmAccessInterface* lbninfo = LmAccessInterface::get_Instance(_debug);
//    lbninfo->set_debug(_debug);
    if (_debug) cout << "LumBlkInfo: Loading info for LBN = " << lbn << std::endl;
//    lbninfo->Load(lbn,0);

    _lbn_file = (int)lbninfo->get_status(lbn);
    if (!_lbn_file) {
       if (_debug) cout << "LumBlkInfo: Bad Lbn status" <<  std::endl;
       return;
    }

    if (_debug) cout <<"LmBlkInfo: Calling get_Trigger_info"<< std::endl;
    LmTriggerList triggerlist=lbninfo->get_Trigger_info(lbn,_listtriggers);
    if (!lbninfo->get_trigger_status(lbn)) {
       if (_debug) cout << "LumBlkInfo: BAD Trigger block status." << std::endl;
//       return;
    } 
    if (_debug) {
       cout << "LumBlkInfo: Trigger map size = " << triggerlist.size() << std::endl;
       for (LmTriggerList::const_iterator it=(triggerlist).begin();it!=(triggerlist).end();it++) {
          cout << "Trigger info for LBN = " << lbn << std::endl;
             it->print();
       }
    }

//  By now, it handles only one trigger at a time, but in the
//  future, this part should be reviewed.

    if (_debug)
       cout << "LumBlkInfo: get_Trigger_info returned a list with size = "<< triggerlist.size() << std::endl;

    for (LmTriggerList::const_iterator it = (triggerlist).begin(); it!= (triggerlist).end();it++) {
       //if (_debug) (it)->print();
       float lm_L1   = ((float) it->LumL1L2())*lm_access::lmCorrection;
       float lm_Raw  = (float) (it)->LumL3()*lm_access::lmCorrection;
       int    hasL2   = (it)->hasL2();
       long   aL1     = (it)->L1Accepts();
       long   aL2     = (it)->L2Accepts();
       long   aL3     = (it)->L3Accepts();
       lm_access::TriggerMap::const_iterator itt = triggers.find((it)->Trigger());
       if (itt!=triggers.end())_triggers[itt->second] = LumTrigger(lm_L1, lm_Raw, hasL2, aL1, aL2, aL3);
    }

  /* read the release information */
 
    if (_debug) cout << "LumBlkInfo: Calling get_Release_info." << std::endl;
    LmReleaseList Releases=lbninfo->get_Release_info(lbn);
    if (!lbninfo->get_release_status(lbn)) {
       if (_debug) cout << "LumBlkIo: BAD Release block status." << std::endl;
 //      return;
    }
    if (_debug) cout << "LmBlkInfo: Release list size = " << Releases.size() << std::endl;

    for (LmReleaseList::const_iterator it = (Releases).begin();it != (Releases).end(); it++) {
      //if (_debug) (it)->print();
      int keepL2 = (it)->get_keepL2();
      string release = (it)->get_DataType()+' '+(it)->get_RecoVersion()+' '+(it)->get_TMBVersion();
      _good_releases[LumFileRelease(release)] = keepL2;
    }

    double beamx = lbninfo->get_BeamX(lbn);
    float  lumconst = lbninfo->get_LumConstant(lbn);

    for (std::map<lm_access::TriggerID, LumTrigger>::iterator it=_triggers.begin();it!=_triggers.end();it++) {
        if ((lumconst!=-1) && (lm_access::effXsec>0)) {
           cout << " In code that should never run in LumBlkInfo  " << endl;
           cout << " LumConstant = " << lumconst << std::endl;  
           float lm_L1  = it->second.luml1()*(lumconst/(lm_access::effXsec*1000));
           float lm_Raw = it->second.lumraw()*(lumconst/(lm_access::effXsec*1000));
           it->second.set_luml1(lm_L1);
        }
    }

   /* read the tick information */

    if (_debug) cout << "LumBlkInfo: Calling get_Tick_info." << std::endl;
    LmTickList ticklist = lbninfo->get_Tick_info(lbn); 
    if (!lbninfo->get_tick_status(lbn)) {
       if (_debug) cout << "LumBlkInfo: BAD Tick block status." << std::endl;
//       return;
    }
    if (_debug) 
       cout << "LumBlkInfo: get_Tick_info returned a list with size = " << ticklist.size() << std::endl;

    /* delivered luminosity calculation */
    _lumDelivered[0]=0.0;
    float luminosity;
    float corrected = 0;

    for (LmTickList::const_iterator it=(ticklist).begin();it!=(ticklist).end();it++) {
        //if (_debug) (it)->print();
        int tick = (it)->get_Tick();
        luminosity = (it)->get_InstLuminosity();
        if (tick<1||tick>159) {
           cout << "LumBlkInfo: ERROR: invalid tick number = " << tick << std::endl;
           return;
        }
        int index = tickmap->tickindex(tick);
        if(index < 1 || index > 36){
          cerr << " Invalid tick number in lm_access::LumBlkInfo read !!! " << tick << endl;
          luminosity = 0.;
        }
        // tranform instantaneous into integrated lum
        _lumDelivered[index] = luminosity*beamx*lm_access::conversion_factor;
                                                                                                                            
      // find  non-linearity correction HMS/BC 9-10-2004
      // but don't apply it now, it is applied in the functions.
                                                                                                                            
        if(_lumDelivered[index] > 0){
          _corrNL[index] =  (1.+ tickmap->beta(index))/(1.+tickmap->offset(index));
        }
        else{
          _corrNL[index] = 1.;
        }
        corrected += _lumDelivered[index]*_corrNL[index];
                                                                                                                            
        if(_debug) cout << index << " corrNL " << _corrNL[index]  << " " << _lumDelivered[index] << endl;
        _lumDelivered[0] += _lumDelivered[index];
    }
                                                                                                                            
    // calculate an average correction from the pieces
                                                                                                                            
    if(corrected  != -1.0){
      _corrNL[0]=corrected/_lumDelivered[0];
    }
    else{
      _corrNL[0] = 1.;
    }  

    if(_debug) cout << _lbn << " corrNL " << _corrNL[0]  << " " << _lumDelivered[0] << endl;

    return;
};

