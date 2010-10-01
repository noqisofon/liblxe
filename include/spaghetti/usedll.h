/**
 * @file use_dll.h
 */
#ifndef spaghetti_use_dll_h
#define spaghetti_use_dll_h


/**
 * @def _Q_EXTERN_C
 * 関数の修飾子です。関数が C 言語形式であることを表します。
 */
#define     _Q_EXTERN_C                 extern "C"


/**
 * @def _DLL_API
 * DLL 用の呼び出し規約です。
 */
#define     _DLL_API                    __stdcall


/**
 * @def _DECLSPEC_DLL_EXPORT
 * 関数やクラス、構造体用の修飾子です。DLL にエクスポートします。
 */
#define     _DECLSPEC_DLL_EXPORT        __declspec(dllexport)


/**
 * @def _DECLSPEC_DLL_IMPORT
 * 関数やクラス、構造体用の修飾子です。DLL にインポートします。
 */
#define     _DECLSPEC_DLL_IMPORT        __declspec(dllimport)


#endif  /* spaghetti_use_dll_h */
