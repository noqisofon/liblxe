#ifndef spaghetti_algo_hpp
#define spaghetti_algo_hpp


/**
 * first ���� last �܂ł̗v�f�� container �ɃR�s�[���܂��B
 *     @param first     �R�s�[����擪�̔����q�B
 *     @param last      �R�s�[���閖���̔����q�B
 *     @param container �R�s�[��̃R���e�i�B
 */
template <class _OutputIterator,class _Container>
inline void copy_array(_OutputIterator first, _OutputIterator last, _Container& container) {
    for ( ; first != last; ++ first ) {
        container.push_back( *first );
    }
}


#endif  /* spaghetti_algo_hpp */
