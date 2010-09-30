/**
 * @file    handle.hpp
 * @since   2010-08-27T11:55:52
 */
#ifndef lxe_win32api_handle_hpp
#define lxe_win32api_handle_hpp

#include <windows.h>

#ifndef LXE_HANDLE_T_DEFINED
typedef     HANDLE                  handle_t;
#   define      LXE_HANDLE_T_DEFINED
#endif  /* ndef LXE_HANDLE_T_DEFINED */


/**
 * 指定されたハンドルが無効かどうかを判別します。
 * @since 2010-08-27
 */
bool handle_is_invalid(handle_t handle);


/**
 * ハンドルを閉じます。
 * @since 2010-08-27
 */
void handle_close(handle_t handle);


#endif  /* lxe_win32api_handle_hpp */
