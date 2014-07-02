#include <lm_access/string_util.hpp>

#include <ctype.h>
#include <list>

using namespace std;

vector<string> split(const string& s, char space) {
  list<string> words;

  int n = s.size();
  int i = 0;
  while (i < n) {
    int j = s.find(space, i);
    if (j == -1) {
      string what = s.substr(i, n);
      if (what.size()) words.push_back(what);
      break;
    }
    if (j == i) {
      i++;
      continue;
    }  
    string what = s.substr(i, j - i);
    if (what.size()) words.push_back(what);
    i = j;
  }


  vector<string> res(words.size());

  list<string>::const_iterator it = words.begin();
  for(int i = 0; i < res.size(); i++) res[i] = *it++;

  return res;
}

string rstrip(const string& s){
  int index = s.size();
  while (index-- >= 0) if (! isspace(s[index])) break;
  return s.substr(0, ++index);
};
string lstrip(const string& s) {
  int index = 0;
  while (index < s.size()) if (! isspace(s[index++])) break;
  return s.substr(--index, s.size());
}
string strip(const string& s) {
  return rstrip(lstrip(s));
}
