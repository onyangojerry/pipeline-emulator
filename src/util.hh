#include <iostream>
#include <string>

#ifndef __UTIL_HH__
#define __UTIL_HH__

void panic(std::string s)
{
    std::cerr << s << std::endl;
    exit(1);
}

#endif // __UTIL_HH__
