#ifndef PIO_CXX_MACROS_HXX
#define PIO_CXX_MACROS_HXX

#include <type_traits>

#define typeof(o) std::remove_reference_t<decltype(o)>

#include <printer.hxx>

#define assert_ok(expr, ...) \
	do { \
		if (!(expr)) { \
			my::printf(__VA_ARGS__); \
			return false; \
		} \
	} while (0)

#endif  // PIO_CXX_MACROS_HXX
