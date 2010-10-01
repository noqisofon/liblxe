#ifndef lxe_lxe_prefix_hpp
#define lxe_lxe_prefix_hpp

#include "config.h"

#include <tchar.h>
#include <windows.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cctype>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <stdexcept>


#if defined(_UNICODE) || defined(UNICODE)
#   define      tstringstream       std::wstringstream
#else
#   define      tstringstream       std::stringstream
#endif  /* defined(_UNICODE) || defined(UNICODE) */

#include <spaghetti/cast.h>


#endif  /* lxe_lxe_prefix_hpp */
