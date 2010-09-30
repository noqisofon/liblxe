/**
 * @file vbstring.cpp
 */
#include <stdafx.h>
//#include <spaghetti/debugger.h>
#include <lxe/vbstring.hpp>
using namespace std;



/**
 * 指定された文字列から同じ内容の BSTR を作成して返します。
 */
inline BSTR _sys_bstring_allocate(const _TCHAR* s)
{
#ifdef LXE_USE_ASSERT
    assert( s != NULL );
#endif  /* def LXE_USE_ASSERT */
    return SysAllocString( __REINTERPRET_CAST(const OLECHAR *, s) );
}
#ifdef LXE_USE_STDSTRING
/**
 * 指定された文字列から同じ内容の BSTR を作成して返します。
 */
inline BSTR _sys_bstring_allocate(const tstring& s)
{
    return SysAllocString( __REINTERPRET_CAST( const OLECHAR *, s.c_str() ) );
}
#endif  /* ndef LXE_USE_STDSTRING */
/**
 * 指定された文字列から n 文字目までの BSTR を作成して返します。
 */
inline BSTR _sys_bstring_allocate(const _TCHAR* s, size_t n)
{
#ifdef LXE_USE_ASSERT
    assert( s != NULL );
#endif  /* def LXE_USE_ASSERT */
    return SysAllocStringLen( __REINTERPRET_CAST(const OLECHAR *, s),
                              __STATIC_CAST(UINT, n)
                              );
}
#ifdef LXE_USE_STDSTRING
/**
 * 指定された文字列から n 文字目までの BSTR を作成して返します。
 */
inline BSTR _sys_bstring_allocate(const tstring& s, size_t n)
{
    return SysAllocStringLen( __REINTERPRET_CAST( const OLECHAR *, s.c_str() ),
                              __STATIC_CAST(UINT, n)
                              );
}
#endif  /* ndef LXE_USE_STDSTRING */


inline size_t _sys_bstring_length(BSTR bs) {
    return SysStringLen( bs );
}


/**
 * BSTR を開放します。
 */
inline void _sys_bstring_deallocate(BSTR bs)
{
#ifdef LXE_USE_ASSERT
    assert( is_dealloced( bs ) );
#endif  /* def LXE_USE_ASSERT */
    if ( bs ) {
#if defined(LXE_USE_LOGGING) && defined(LXE_USE_FSTREAM)
        {
            ofstream    output( "terminate.log" );

            output << "removing 0x" << hex << __REINTERPRET_CAST(INT_PTR, bs)
                << "   " << bs << endl;

            output.close();
        }
#endif  /* LXE_USE_LOGGING */

#ifdef LXE_USE_POINTER_TRAITS
        /*
         * 何故か bs の値が 0x00000002 になっていることがあり、
         * この場合、SysFreeString() は SEH 例外を投げる。
         *
         */
        if ( pointer_traits<BSTR>::ne_intptr( bs, 0x00000002 ) ||
             pointer_traits<BSTR>::ne_intptr( bs, 0xcccccccc ) )
            SysFreeString( bs );
#else
        SysFreeString( bs );
#endif  /* def LXE_USE_POINTER_TRAITS */

    }
}


BSTR bstrdup(const _TCHAR*  s)
{
    return _sys_bstring_allocate( s );
}
#ifdef LXE_USE_STDSTRING
BSTR bstrdup(const tstring& s)
{
    return _sys_bstring_allocate( s );
}
#endif  /* def LXE_USE_STDSTRING */


BSTR bstrndup(const _TCHAR*  s, size_t n)
{
    return _sys_bstring_allocate( s, n );
}
#ifdef LXE_USE_STDSTRING
BSTR bstrndup(const tstring& s, size_t n)
{
    return _sys_bstring_allocate( s, n );
}
#endif  /* def LXE_USE_STDSTRING */


size_t bstrlen(BSTR bs)
{
    return _sys_bstring_length( bs );
}


void bstr_free(BSTR bs)
{
    _sys_bstring_deallocate( bs );
}
