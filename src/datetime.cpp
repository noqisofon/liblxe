/**
 * @file datetime.cpp
 */
#include <stdafx.h>

#include <lxe/datetime.hpp>
using namespace std;

#define     DISPLAYED_BUFFER_SIZE        26


tstring toLongTime32String(__time32_t t)
{
    struct tm   timestamp;
    _TCHAR      displayed_buffer[DISPLAYED_BUFFER_SIZE];
    tstring     longtime;

    errno_t     err;

    err = _localtime32_s( &timestamp, &t );
    if ( err > 0 )
        return longtime;

    _tcsftime( displayed_buffer, DISPLAYED_BUFFER_SIZE, _T("%Y-%m-%dT%H:%M:%S"), &timestamp );
    longtime    = displayed_buffer;

    return longtime;
}


tstring toLongTime64String(__time64_t t)
{
    struct tm   timestamp;
    _TCHAR      displayed_buffer[DISPLAYED_BUFFER_SIZE];
    tstring     longtime;

    errno_t     err;

    err = _localtime64_s( &timestamp, &t );
    if ( err > 0 )
        return longtime;

    _tcsftime( displayed_buffer, DISPLAYED_BUFFER_SIZE, _T("%Y-%m-%dT%H:%M:%S"), &timestamp );
    longtime    = displayed_buffer;

    return longtime;
}
