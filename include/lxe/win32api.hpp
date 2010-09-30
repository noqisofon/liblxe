/**
 * @file    win32api.hpp
 * 
 */
#ifndef lxe_win32api_win32api_hpp
#define lxe_win32api_win32api_hpp

#include <config/lxe_prefix.h>

#ifndef LXE_HANDLE_T_DEFINED
typedef     HANDLE                  handle_t;
#   define      LXE_HANDLE_T_DEFINED
#endif  /* ndef LXE_HANDLE_T_DEFINED */
typedef     HKEY                    registry_t;
typedef     SECURITY_ATTRIBUTES     security_attr_t;
typedef     ACCESS_MASK             access_mask_t;

#include "handle.hpp"

#include <spaghetti/cast.h>

#include <spaghetti/string_util.hpp>


#endif  /* lxe_win32api_win32api_hpp */
