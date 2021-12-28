#ifndef TYPE_EXISTS_HPP_INCLUDED
#define TYPE_EXISTS_HPP_INCLUDED

// thanks, https://devblogs.microsoft.com/oldnewthing/20190710-00/?p=102678

#include <type_traits>

template < class, class = void > struct TypeExists : std::false_type {
};

template< class T >
struct TypeExists<T, std::void_t<decltype(sizeof(T))>> : std::true_type{};



#endif
