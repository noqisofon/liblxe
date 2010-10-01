/**
 * @file bitset.hpp
 */
#ifndef spaghetii_bitset_hpp
#define spaghetii_bitset_hpp


typedef     unsigned int    bitset_t;


/**
 * self に other_bitset が含まれていたら真を返します。
 */
bool bitset_is_include(bitset_t self, bitset_t other_bitset);


/**
 * 指定されたビットセットを反転したものを返します。
 */
bitset_t bitset_inversion(bitset_t self);



/**
 * self から other を取り除いたものを返します。
 * @since 2010-09-24T14:13:12+0900
 */
bitset_t bitset_difference(bitset_t self, bitset_t other);


#endif  /* spaghetii_bitset_hpp */
