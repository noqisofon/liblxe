/**
 * @file vbstring.hpp
 * 
 */
#ifndef lxe_vbstring_hpp
#define lxe_vbstring_hpp

#include <lxe/win32api.hpp>


/**
 * �v���~�e�B�u C �����񂩂瓯�����e�̐V���� VB ��������쐬���ĕԂ��܂��B
 */
BSTR bstrdup(const _TCHAR*  s);
#ifdef LXE_USE_STDSTRING
BSTR bstrdup(const tstring& s);
#endif  /* def LXE_USE_STDSTRING */


/**
 * �v���~�e�B�u C �����񂩂� n �����ڂ܂œ������e�̐V���� VB ��������쐬���ĕԂ��܂��B
 */
BSTR bstrndup(const _TCHAR*  s, size_t n);
#ifdef LXE_USE_STDSTRING
BSTR bstrndup(const tstring& s, size_t n);
#endif  /* def LXE_USE_STDSTRING */


/**
 * �w�肳�ꂽ VB ������̒�����Ԃ��܂��B
 */
size_t bstrlen(BSTR bs);


/**
 * BSTR ���J�����܂��B
 */
void bstr_free(BSTR bs);


#endif  /* lxe_vbstring_hpp */
