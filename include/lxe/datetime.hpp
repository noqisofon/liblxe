/**
 * @file datetime.hpp
 */
#ifndef lxe_datetime_hpp
#define lxe_datetime_hpp


#include <lxe/win32api.hpp>


/**
 * 32 bit �^ time_t ����AISO 8601 �����̕�����ɕϊ����ĕԂ��܂��B
 * @since 2010-09-14T09:31:21+0900
 */
tstring toLongTime32String(__time32_t t);


/**
 * 64 bit �^ time_t ����AISO 8601 �����̕�����ɕϊ����ĕԂ��܂��B
 * @since 2010-09-14T09:31:21+0900
 */
tstring toLongTime64String(__time64_t t);


/**
 * time_t ����AISO 8601 �����̕�����ɕϊ����ĕԂ��܂��B
 * @since 2010-09-14T09:31:21+0900
 */
inline tstring toLongTimeString(time_t t) {
#ifdef _USE_32BIT_TIME_T
    return toLongTime32String( t );
#else
    return toLongTime64String( t );
#endif  /* def _USE_32BIT_TIME_T */
}


#endif  /* lxe_datetime_hpp */
