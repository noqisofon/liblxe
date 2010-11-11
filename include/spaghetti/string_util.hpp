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
 * s �� separator �ŋ�؂�ꂽ����������� container �Ɋi�[���܂��B
 *    @param that       ��������镶����B
 *    @param container  ������������i�[����R���e�i�B
 *    @param separator  ��؂蕶����B
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
 * that ���� sub_string �� new_sub_string �ɒu�������܂��B
 *    @param   that            �u�������镶����B
 *    @param   sub_string      �������镔��������B
 *    @param   new_sub_string  �������������ɒu�������镔��������B
 *
 *    @return  �u��������������B
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
 * �w�肳�ꂽ������̐擪�Ɩ����̋󔒕���(\s)���폜�����������Ԃ��܂��B
 *    @param  that  �󔒕������폜���镶����B
 *
 *    @return that ����擪�Ɩ����̋󔒕�������폜����������B
 */
template <class _String> inline
_String trim(_String that) {
    typedef   typename _String::const_iterator           const_iterator;
    typedef   typename _String::const_reverse_iterator   const_reverse_iterator;

    // ���[�̌��o
    const_iterator
        left
            =
                std::find_if( that.begin(),
                              that.end(),
                              std::not1( std::ptr_fun( _istspace ) )
                              );

    // �E�[�̌��o
    const_reverse_iterator
        right
            =
                std::find_if( that.rbegin(),
                              that.rend(),
                              std::not1( std::ptr_fun( _istspace ) )
                              );

    // ���[�ƉE�[�̊Ԃ̕������Ԃ�
    return _String( left, right.base() );
}
template <class _String> inline
_String trim(typename _String::const_pointer* that) {
    return trim( _String( that ) );
}


/**
 * �w�肳�ꂽ������̖����̋󔒕���(\s)���폜�����������Ԃ��܂��B
 *    @param  that  �󔒕������폜���镶����B
 *
 *    @return that ���疖���̋󔒕�������폜����������B
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
