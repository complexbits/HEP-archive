#ifndef LIBBASIC_STRING_UTIL_H
#define LIBBASIC_STRING_UTIL_H

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& s, char space = ' ');

std::string rstrip(const std::string& s);
std::string lstrip(const std::string& s);
std::string strip(const std::string& s);

#endif /* LIBBASIC_STRING_UTIL_H */
