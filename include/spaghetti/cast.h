/**
 * @file    cast.h
 * @breif   C++ 風のキャストを C 風のキャストとスイッチできるエクステンション
 */
#if !defined(__CSTYLE_CAST)
////////////////////////////////////////////////////////////////////////////////
// 
// C スタイルのキャストを行う関数型プリプロセッサ。
// 
#   define     __CSTYLE_CAST(_type_, _expression_)      ((_type_)_expression_)


#   ifdef __cplusplus
/* 
 * _SPAG_NON_STANDALONE_MODULE が定義されていなかったら、デフォルトとして
 * _SPAG_USE_CPPSTYLE_CAST を定義します。
 */
#       if !defined(_SPAG_NON_STANDALONE_MODULE)
#           define          _SPAG_USE_CPPSTYLE_CAST
#       else
/* 
 * 定義されており、_USE_CPPSTYLE_CAST が定義されていたら
 * _SPAG_USE_CPPSTYLE_CAST を定義します。
 */
#           if defined(_USE_CPPSTYLE_CAST)
#               define      _SPAG_USE_CPPSTYLE_CAST
#           endif  /* defined(_USE_CPPSTYLE_CAST) */

#       endif  /* !defined(_SPAG_NON_STANDALONE_MODULE) */
#   endif  /* def __cplusplus */


////////////////////////////////////////////////////////////////////////////////
// 
// C++ スタイルのキャストを行う関数型プリプロセッサ。
// 
#   if defined(_SPAG_USE_CPPSTYLE_CAST)
#       define      __DYNAMIC_CAST(_type_, _expression_)                  dynamic_cast<_type_>(_expression_)
#       define      __STATIC_CAST(_type_, _expression_)                    static_cast<_type_>(_expression_)
#       define      __REINTERPRET_CAST(_type_, _expression_)          reinterpret_cast<_type_>(_expression_)
#       define      __CONST_CAST(_type_, _expression_)                      const_cast<_type_>(_expression_)
#   else
#       define      __DYNAMIC_CAST(_type_, _expression_)                 __CSTYLE_CAST(_type_, _expression_)
#       define      __STATIC_CAST(_type_, _expression_)                  __CSTYLE_CAST(_type_, _expression_)
#       define      __REINTERPRET_CAST(_type_, _expression_)             __CSTYLE_CAST(_type_, _expression_)
#       define      __CONST_CAST(_type_, _expression_)                   __CSTYLE_CAST(_type_, _expression_)
#   endif  /* defined(_SPAG_USE_CPPSTYLE_CAST) */


#endif  /* !defined(__CSTYLE_CAST) */
