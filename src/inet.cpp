/**
 * @file inet.cpp
 */
#include <stdafx.h>
#include <lxe/inet.hpp>
using namespace std;


#pragma comment(lib, "ws2_32.lib")


bool check_host(const tstring& hostname) {
    WSADATA     wsa_data;
    hostent*    ent;
    DWORD       err;

    if ( ( err = WSAStartup( MAKEWORD(2, 1), &wsa_data ) ) != 0 ) {

        return false;
    }

    if ( ( ent = gethostbyname( hostname.c_str() ) ) == NULL ) {
        WSACleanup();

        return false;
    }

    WSACleanup();

    return true;
}
