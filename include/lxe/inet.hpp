/**
 * @file inet.hpp
 */
#ifndef lxe_inet_hpp
#define lxe_inet_hpp

#include <winsock2.h>
#include <spaghetti/string_util.hpp>


bool check_host(const tstring& hostname);
inline bool check_host(const _TCHAR* hostname) {
    return check_host( tstring( hostname ) );
}


#endif  /* lxe_inet_hpp */
