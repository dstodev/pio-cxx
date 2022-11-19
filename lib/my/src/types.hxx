#ifndef PIO_CXX_TYPES_HXX
#define PIO_CXX_TYPES_HXX

// macro helpers

#define typeof(o) std::remove_reference_t<decltype(o)>

// (macros are unaffected by namespaces)

namespace my {

// TODO

}  // namespace my

#endif  // PIO_CXX_TYPES_HXX
