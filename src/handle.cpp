/**
 * @file handle.cpp
 */
#include <stdafx.h>

#include <lxe/handle.hpp>


bool handle_is_invalid(handle_t handle)
{
    return handle == NULL ||
           handle == INVALID_HANDLE_VALUE;
}


void handle_close(handle_t handle)
{
    if ( handle_is_invalid( handle ) )
        return ;

    CloseHandle( handle );
}
