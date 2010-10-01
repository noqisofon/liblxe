/**
 * @file iterator_proxy.hpp
 */
#ifndef spaghetti_iterator_proxy_hpp
#define spaghetti_iterator_proxy_hpp


/**
 * @def _SPAG_ARRAY_SIZE
 * _type_ の配列 _value_ の長さを表します。
 */
#define             _SPAG_ARRAY_SIZE(_type_, _value_)       sizeof(_value_) / sizeof(_type_)
/**
 * @def _SPAG_ARRAY_TYPE
 * _type_ の配列 _value_ の型を表します。
 */
#define             _SPAG_ARRAY_TYPE(_type_, _value_)       _type_[_SPAG_ARRAY_SIZE(_type_, _value_)]


template <class _Container>
struct iterator_proxy {
    typedef     typename _Container::iterator       iterator;
};
template <class _Type>
struct iterator_proxy<_Type*> {
    typedef     _Type*      iterator;
};
template <class _Type, std::size_t _N>
struct iterator_proxy<_Type[_N]> {
    typedef     _Type*      iterator;

    static iterator begin(iterator _It) {
        return _It;
    }


    static iterator end(iterator _It) {
        return _It + _N;
    }
};
template <class _Type, std::size_t _N>
struct iterator_proxy<const _Type[_N]> {
    typedef     _Type*      iterator;

    static iterator begin(iterator _It) {
        return _It;
    }


    static iterator end(iterator _It) {
        return _It + _N;
    }
};


#endif  /* spaghetti_iterator_proxy_hpp */
