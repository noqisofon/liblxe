/**
 * @file stream_weaver.hpp
 * 
 */
#ifndef lxe_stream_weaver_hpp
#define lxe_stream_weaver_hpp

#include <iostream>
#include <sstream>


inline std::ostream& operator << (std::ostream& out, std::stringstream& ss) {
    return out << ss.str();
}


inline std::ostream& operator<< (std::ostream& out, const BSTR& bs) {
    if ( bs == NULL )
        out << _T("null");
    else
        out << _T("\"") << __REINTERPRET_CAST(_TCHAR *, bs) << _T("\"");

    return out;
}


#endif  /* lxe_stream_weaver_hpp */
