/**
 * @file use_dll.h
 */
#ifndef spaghetti_use_dll_h
#define spaghetti_use_dll_h


/**
 * @def _Q_EXTERN_C
 * �֐��̏C���q�ł��B�֐��� C ����`���ł��邱�Ƃ�\���܂��B
 */
#define     _Q_EXTERN_C                 extern "C"


/**
 * @def _DLL_API
 * DLL �p�̌Ăяo���K��ł��B
 */
#define     _DLL_API                    __stdcall


/**
 * @def _DECLSPEC_DLL_EXPORT
 * �֐���N���X�A�\���̗p�̏C���q�ł��BDLL �ɃG�N�X�|�[�g���܂��B
 */
#define     _DECLSPEC_DLL_EXPORT        __declspec(dllexport)


/**
 * @def _DECLSPEC_DLL_IMPORT
 * �֐���N���X�A�\���̗p�̏C���q�ł��BDLL �ɃC���|�[�g���܂��B
 */
#define     _DECLSPEC_DLL_IMPORT        __declspec(dllimport)


#endif  /* spaghetti_use_dll_h */
