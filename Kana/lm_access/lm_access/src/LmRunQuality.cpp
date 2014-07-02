#include "lm_access/LmRunQuality.hpp"
#include <iostream>

namespace lm_access{

  //  using namespace std;

LmRunQuality::LmRunQuality(){
  _allgood=1;
  _somebad=0;
}



  /*
std::string LmRunQuality::filename_expand(std::string& filename){

    int environstart = filename.find("$");
    int environend = filename.find("/");


    if(environstart == 0){

    // a complex path

      if(environend > 0){
	std::string environ = filename.substr(environstart+1,environend-1);
	std::string restofpath = filename.substr(environend,environ.size()-1);
	const char* env = environ.c_str();
	std::string newenviron = std::getenv(env);
	return newenviron+restofpath;
      }

    // just an environmental

      else {
	std::string environ = filename.substr(1,filename.length());
	return getenv(environ.c_str());
      }
    }

    // no environmental 

    return filename;
}
  */

bool LmRunQuality::loadGoodRuns(std::string filename){
  filename=filename_expand(filename);
  int count = 0;
  ifstream goodfilestream(filename.c_str());
  if(!goodfilestream){
    cerr << "No good runs specified by " << filename << " , assume all are goodor retain previous good list" << endl;
    if(_allgood == 0) _allgood = 1;
    return 0;
  }
  int run;
  while(goodfilestream >> run){
    goodruns.insert(run);
    count++;
  }
  goodfilestream.close();
  _allgood = 0;
  cout << count << " good runs loaded from " << filename << endl;
  return 1;
}

bool LmRunQuality::loadBadRuns(std::string filename){
  filename=filename_expand(filename);
  int count = 0;
  ifstream badfilestream(filename.c_str());
  if(!badfilestream){
    cerr << "No bad runs specified by " << filename << " , don't add any bad runs to existing list" << endl;
    if(_somebad != 1) _somebad = 0;
    return 0;
  }
  int run;
  while(badfilestream >> run){
    badruns.insert(run);
    count++;
  }
  badfilestream.close();
  _somebad=1;
  cout << count << " bad runs loaded from " << filename << endl;
  return 1;
}    

bool LmRunQuality::isGoodRun(int run)const{
  return (_allgood || goodruns.count(run));
} 

bool LmRunQuality::isBadRun(int run)const{
  return (_somebad && badruns.count(run));
}

void LmRunQuality::addGoodRun(int run){
  goodruns.insert(run);
}

void LmRunQuality::addBadRun(int run){
  badruns.insert(run);
}
    
void LmRunQuality::removeGoodRun(int run){
  goodruns.erase(run);
}

void LmRunQuality::removeBadRun(int run){
  badruns.erase(run);
}
}
