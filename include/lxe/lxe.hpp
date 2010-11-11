/**
 * @file  lxe.hpp
 * @brief lxe �̂܂Ƃ߁B
 */
#ifndef lxe_lxe_hpp
#define lxe_lxe_hpp

#include <windows.h>

#include <spaghetti/cast.h>
#include <spaghetti/string_util.hpp>

#ifndef LXE_DEFINE_REGISTRY_T
typedef     HKEY            registry_t;
#   define          LXE_DEFINE_REGISTRY_T
#endif  /* ndef LXE_DEFINE_REGISTRY_T */

#ifndef LXE_DEFINE_ACCESS_MASK_T
typedef     ACCESS_MASK     access_mask_t;
#   define          LXE_DEFINE_ACCESS_MASK_T
#endif  /* ndef LXE_DEFINE_ACCESS_MASK_T */

#ifndef LXE_DEFINE_SECURITY_ATTR_T
typedef     SECURITY_ATTRIBUTES     security_attr_t;
#   define          LXE_DEFINE_SECURITY_ATTR_T
#endif  /* ndef LXE_DEFINE_SECURITY_ATTR_T */

#include <lxe/datetime.hpp>
#include <lxe/eventlog.hpp>
#include <lxe/error_handler.hpp>
#include <lxe/handle.hpp>
#include <lxe/inet.hpp>
#include <lxe/ini_file.hpp>
#include <lxe/registry.hpp>
#include <lxe/stream_weaver.hpp>
#include <lxe/vbstring.hpp>
#include <lxe/winio.hpp>


#endif  /* lxe_lxe_hpp */
