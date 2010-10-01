/**
 * @file types.h
 */
#ifndef standard_types_h
#define standard_types_h

#define    _AMOUNTS(_type_)           sizeof(_type_) / sizeof(char)


typedef     unsigned char           ubyte;
typedef     signed char             sbyte;

#if !defined(_HAVE_STDINT_H)
typedef     signed char             int8_t;
typedef     unsigned char           uint8_t;
typedef     short                   int16_t;
typedef     unsigned short          uint16_t;
typedef     int                     int32_t;
typedef     unsigned                uint32_t;
typedef     long long               int64_t;
typedef     unsigned long long      uint64_t;
#else
#   include <stdint.h>
#endif  /* !defined(_HAVE_STDINT_H) */


typedef     bool                _boolean;


#endif  /* standard_types_h */
