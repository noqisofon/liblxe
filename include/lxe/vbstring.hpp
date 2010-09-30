/**
 * @file vbstring.hpp
 * 
 */
#ifndef lxe_vbstring_hpp
#define lxe_vbstring_hpp

#include <lxe/win32api.hpp>


/**
 * プリミティブ C 文字列から同じ内容の新しい VB 文字列を作成して返します。
 */
BSTR bstrdup(const _TCHAR*  s);
#ifdef LXE_USE_STDSTRING
BSTR bstrdup(const tstring& s);
#endif  /* def LXE_USE_STDSTRING */


/**
 * プリミティブ C 文字列から n 文字目まで同じ内容の新しい VB 文字列を作成して返します。
 */
BSTR bstrndup(const _TCHAR*  s, size_t n);
#ifdef LXE_USE_STDSTRING
BSTR bstrndup(const tstring& s, size_t n);
#endif  /* def LXE_USE_STDSTRING */


/**
 * 指定された VB 文字列の長さを返します。
 */
size_t bstrlen(BSTR bs);


/**
 * BSTR を開放します。
 */
void bstr_free(BSTR bs);


#endif  /* lxe_vbstring_hpp */
