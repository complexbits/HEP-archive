#include "lm_access/tickutility.hpp"

tickutility* tickutility::Instance(){

  static tickutility me;

  return &me;
}

tickutility::tickutility(){;}

void tickutility::Init(const bool fixNL){

 
  // create list and inverse

  
  static const int mylist[37]={ 0,7,10,13,16,19,22,25,28,31,34,37,40,60,63,66,69,72,75,78,81,84,87,90,93,113,116,119,122,125,128,131,134,137,140,143,146};
  
  static const int inverse[160] ={0,-1,-1,-1,-1,-1,-1, 1,-1,-1, 2,-1,-1, 3,-1,-1, 4,-1,-1, 5,-1,-1, 6,-1,-1, 7,-1,-1, 8,-1,-1, 9,-1,-1, 10,-1,-1, 11,-1,-1, 12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 13,-1,-1, 14,-1,-1, 15,-1,-1, 16,-1,-1, 17,-1,-1, 18,-1,-1, 19,-1,-1, 20,-1,-1, 21,-1,-1, 22,-1,-1, 23,-1,-1, 24,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 25,-1,-1, 26,-1,-1, 27,-1,-1, 28,-1,-1, 29,-1,-1, 30,-1,-1, 31,-1,-1, 32,-1,-1, 33,-1,-1, 34,-1,-1, 35,-1,-1, 36,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1};

  // future corrections

  static const float beta_val[12]= {0,0,0,0,0,0,0,0,0,0,0,0};

  static const float offset_val[12]={0,0,0,0,0,0,0,0,0,0,0,0};

  /*  static const float beta_val[12]={0, 
				   0.00297446,
				   0.0199349,
				   0.035516,
				   0.04446,
				   0.0366521,
				   0.0341626,
				   0.0499875,
				   0.0702892,
				   0.0567248,
				   0.0551246,
				   0.0463146};
  
    static const float offset_val[12] = { 0,
					  0.002111504,
					  0.013541383,
					  0.021346926,
					  0.025946791,
					  0.025269363,
					  0.023508072,
					  0.031497819,
					  0.027883506,
					  0.027479091,
					  0.026706147,
					  0.021764717};
  */

  for (int i = 0; i < 37; i++){
    int k = mylist[i];
    _list[i]=k;
  }  
  for (int i = 0; i < 160; i++){
    _inverse[i]=inverse[i];
  }
  
  for (int i = 0; i < 12; i++){
 
      _beta[i]=beta_val[i];
      _offset[i] = offset_val[i];
    
  }
}

int tickutility::tickindex(const std::string& tick)const{
  return tickindex(atoi(tick.c_str()));
}

  // convert from tick number to index

int tickutility::tickindex( const int tick)const{
  if(tick>=0 && tick<=159) return _inverse[tick];
  return -1;
}
  // convert from index to tick number int
  
int tickutility::ticklist(const int index)const{
  if(index >= 0 && index <= 36)   return _list[index];
  return -1;
}

float tickutility::beta(const int tick) const{
  int ref = (tick-1)%12;
  return _beta[ref];
}
float tickutility::offset(const int tick) const{
  int ref = (tick-1)%12;
  return _offset[ref];
}

