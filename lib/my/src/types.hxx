#ifndef PIO_CXX_TYPES_HXX
#define PIO_CXX_TYPES_HXX

#include <type_traits>

// Using reference implementation from: https://en.cppreference.com/w/cpp/types/remove_reference
// because it isn't in the current standard library.
template <typename T>
using remove_reference_t = typename std::remove_reference<T>::type;

#endif  // PIO_CXX_TYPES_HXX
