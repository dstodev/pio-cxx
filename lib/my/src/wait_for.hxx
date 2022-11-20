#ifndef PIO_CXX_WAIT_FOR_HXX
#define PIO_CXX_WAIT_FOR_HXX

#include <cstdint>

namespace my {

/// Wait up to timeout_ms for predicate, checking every interval_ms.
/// A predicate is anything testable as a boolean, especially stateful classes which implement operator bool().
/// Requires a WaitFn(/* uint32_t ms */) to call, which is expected to wait for the given time in milliseconds.
template <typename Predicate, typename WaitFn>
void wait_for(Predicate& predicate, WaitFn& wait_fn, uint32_t timeout_ms, uint32_t interval_ms = 10 /*ms*/)
{
	auto iterations = timeout_ms / interval_ms;
	for (auto i {0}; !predicate && i < iterations; ++i) {
		wait_fn(interval_ms);
	}
}

}  // namespace my

#endif  // PIO_CXX_WAIT_FOR_HXX
