/**
 * @file string_util.hpp
 */
#ifndef spaghetti_string_util_hpp
#define spaghetti_string_util_hpp

#include <cstring>
#include <string>
#include <algorithm>


#if defined(_UNICODE) || defined(UNICODE)
#   define           tstring           std::wstring
#else
#   define           tstring           std::string
#endif  /* defined(_UNICODE) || defined(UNICODE) */

#if defined(_UNICODE) || defined(UNICODE)
#   define      tstringstream       std::wstringstream
#else
#   define      tstringstream       std::stringstream
#endif  /* defined(_UNICODE) || defined(UNICODE) */


template <class _Char> inline
size_t length(const _Char* s) {
    size_t  i   = 0;

    while ( *s ++ )
        ++ i;

    return i;
}


template <class _Container, class _String> inline
_Container split(_String s, _String t) {
    typedef     typename _String::size_type      size_type;

    _Container  v;
    size_type   p   = s.find( t );

    if ( p != _String::npos ) {
        v.push_back( s.substr( 0, p ) );
        s = s.substr( p + t.size() );
    }
    v.push_back( s );

    return v;
}


/**
 * s の separator で区切られた部分文字列を container に格納します。
 *    @param that       分割される文字列。
 *    @param container  部分文字列を格納するコンテナ。
 *    @param separator  区切り文字列。
 */
template <class _Container, class _String> inline
void split_all(_String that, _Container& container, const _String separator) {
    typedef     typename _String::size_type      size_type;

    size_type   separator_length = separator.length();

    for ( size_type p = 0; ( p = that.find( separator ) ) != _String::npos; ) {
        container.push_back( that.substr( 0, p ) );
        that = that.substr( p + separator_length );
    }
    container.push_back( that );
}
template <class _Container, class _String> inline
void split_all(_String that, _Container& container, const typename _String::const_pointer separator) {
    typedef     typename _String::size_type      size_type;

    size_type   separator_length = length( separator );

    for ( size_type p = 0; ( p = that.find( separator ) ) != _String::npos; ) {
        container.push_back( that.substr( 0, p ) );
        that = that.substr( p + separator_length );
    }
    container.push_back( that );
}


template <class _String> inline
_String replace(_String s, _String f, _String t) {
    typedef     typename _String::size_type      size_type;

    _String      r;
    size_type   p = s.find( f );
    if ( p != _String::npos ) {
        r += s.substr( 0, p ) + t;
        s  = s.substr( p + f.size() );
    }
    return r + s;
}
template <class _String> inline
_String replace(_String s, _String f, typename _String::const_pointer t) {
    typedef     typename _String::size_type      size_type;

    _String      r;
    size_type   p = s.find( f );
    if ( p != _String::npos ) {
        r += s.substr( 0, p ) + t;
        s  = s.substr( p + f.size() );
    }
    return r + s;
}
template <class _String> inline
_String replace(_String s, typename _String::const_pointer f, typename _String::const_pointer t) {
    typedef     typename _String::size_type      size_type;

    _String      r;
    size_type   p = s.find( f );
    if ( p != _String::npos ) {
        r += s.substr( 0, p ) + t;
        s  = s.substr( p + length( f ) );
    }
    return r + s;
}
template <class _String> inline
_String replace(_String s, typename _String::const_pointer f, _String t) {
    typedef     typename _String::size_type      size_type;

    _String      r;
    size_type   p = s.find( f );
    if ( p != _String::npos ) {
        r += s.substr( 0, p ) + t;
        s  = s.substr( p + length( f ) );
    }
    return r + s;
}


/**
 * that 内の sub_string を new_sub_string に置き換えます。
 *    @param   that            置き換える文字列。
 *    @param   sub_string      検索する部分文字列。
 *    @param   new_sub_string  検索した部分に置き換える部分文字列。
 *
 *    @return  置き換えた文字列。
 */
template <class _String> inline
_String replace_all(_String that, _String sub_string, _String new_sub_string) {
    typedef     typename _String::size_type      size_type;

    _String    replace_allment;
    for ( size_type p = 0; ( p = that.find( sub_string ) ) != _String::npos; ) {
        replace_allment += that.substr( 0, p ) + new_sub_string;
        that             = that.substr( p + sub_string.size() );
    }
    return replace_allment + that;
}
template <class _String> inline
_String replace_all(_String that, typename _String::const_pointer sub_string, typename _String::const_pointer new_sub_string) {
    return replace_all( that, _String( sub_string ), _String( new_sub_string ) );
}


/**
 * 指定された文字列の先頭と末尾の空白文字(\s)を削除した文字列を返します。
 *    @param  that  空白文字を削除する文字列。
 *
 *    @return that から先頭と末尾の空白文字列を削除した文字列。
 */
template <class _String> inline
_String trim(_String that) {
    typedef   typename _String::const_iterator           const_iterator;
    typedef   typename _String::const_reverse_iterator   const_reverse_iterator;

    // 左端の検出
    const_iterator
        left
            =
                std::find_if( that.begin(),
                              that.end(),
                              std::not1( std::ptr_fun( _istspace ) )
                              );

    // 右端の検出
    const_reverse_iterator
        right
            =
                std::find_if( that.rbegin(),
                              that.rend(),
                              std::not1( std::ptr_fun( _istspace ) )
                              );

    // 左端と右端の間の文字列を返す
    return _String( left, right.base() );
}
template <class _String> inline
_String trim(typename _String::const_pointer* that) {
    return trim( _String( that ) );
}


/**
 * 指定された文字列の末尾の空白文字(\s)を削除した文字列を返します。
 *    @param  that  空白文字を削除する文字列。
 *
 *    @return that から末尾の空白文字列を削除した文字列。
 */
template <class _String> inline
_String trim_right(_String that) {
    typedef        typename _String::const_reverse_iterator       const_reverse_iterator;

    const_reverse_iterator
        right
            =
                std::find_if( that.rbegin(),
                              that.rend(),
                              std::not1( std::ptr_fun( _istspace ) )
                              );

    return _String( that.begin(), right.base() );
}
template <class _String> inline
_String trim_right(typename _String::const_pointer* that) {
    return trim_right( _String( that ) );
}


#endif  /* spaghetti_string_util_hpp */
