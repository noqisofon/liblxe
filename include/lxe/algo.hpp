#ifndef spaghetti_algo_hpp
#define spaghetti_algo_hpp


/**
 * first から last までの要素を container にコピーします。
 *     @param first     コピーする先頭の反復子。
 *     @param last      コピーする末尾の反復子。
 *     @param container コピー先のコンテナ。
 */
template <class _OutputIterator,class _Container>
inline void copy_array(_OutputIterator first, _OutputIterator last, _Container& container) {
    for ( ; first != last; ++ first ) {
        container.push_back( *first );
    }
}


#endif  /* spaghetti_algo_hpp */
