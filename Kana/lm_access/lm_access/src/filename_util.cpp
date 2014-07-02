#include "lm_access/filename_util.hpp"
#include <cassert>
#include <cstdlib>
#include <iostream>

std::string lm_access::filename_expand(const std::string& filename){

    int environstart = filename.find("$");
    int environend = filename.find("/");


    if(environstart == 0){

    // a complex path

      if(environend > 0){
	std::string environ = filename.substr(environstart+1,environend-1);
	std::string restofpath = filename.substr(environend,environ.size()-1);
	const char* env = environ.c_str();
	const char* expanded_env = std::getenv(env);
	if(expanded_env <= 0){
	  std::cerr << "Invalid environmental in filename "<< env << " set to null string " << std::endl;
	  expanded_env = "";
	}
	std::string newenviron(expanded_env);
	return newenviron+restofpath;
      }

    // just an environmental

      else {
	std::string environ = filename.substr(1,filename.length());
	const char* expanded_env = getenv(environ.c_str());
	if(expanded_env <= 0){
	  std::cerr << "Invalid environmental in filename " << environ << " set to null string " <<  std::endl;
	  expanded_env = "";
	}
	return std::string(expanded_env);
      }
    }

    // no environmental 

    return filename;
}

std::string lm_access::filename_only(const std::string& filename){
    int begin_name=filename.find_last_of(std::string("/"),9999);
    std::string short_name;
    if(begin_name >= 0){
      short_name = filename.substr(begin_name+1,filename.size());
    }
    else{
      short_name = filename;
    }
    return short_name;
}
