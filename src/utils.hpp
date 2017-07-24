#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#ifndef UTILS_HPP
#define UTILS_HPP

class utils {
public:
    //safe getline utility function, 
    //src: https://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
    //for cross platform file support
    std::istream& safeGetline(std::istream& is, std::string& t);

    //remove trailing zero function for data with trailing zeros
    //src: http://www.geeksforgeeks.org/remove-trailing-zeros-string-c/
    std::string removeTrailingZeros(std::string s);
};
#endif
