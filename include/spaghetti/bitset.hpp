/**
 * @file bitset.hpp
 */
#ifndef spaghetii_bitset_hpp
#define spaghetii_bitset_hpp


typedef     unsigned int    bitset_t;


/**
 * self �� other_bitset ���܂܂�Ă�����^��Ԃ��܂��B
 */
bool bitset_is_include(bitset_t self, bitset_t other_bitset);


/**
 * �w�肳�ꂽ�r�b�g�Z�b�g�𔽓]�������̂�Ԃ��܂��B
 */
bitset_t bitset_inversion(bitset_t self);



/**
 * self ���� other ����菜�������̂�Ԃ��܂��B
 * @since 2010-09-24T14:13:12+0900
 */
bitset_t bitset_difference(bitset_t self, bitset_t other);


#endif  /* spaghetii_bitset_hpp */
