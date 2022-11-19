#ifndef PIO_CXX_WAIT_FOR_HXX
#define PIO_CXX_WAIT_FOR_HXX

#include <cstdint>

#include <Arduino.h>  // for delay()

namespace my {

/// Wait up to timeout_ms for predicate, checking every interval_ms.
/// A predicate is anything testable as a boolean, especially stateful classes which implement operator bool().
template <typename Predicate>
void wait_for(Predicate& predicate, uint32_t timeout_ms, uint32_t interval_ms = 10 /* ms */)
{
	auto iterations = timeout_ms / interval_ms;
	for (auto i {0}; !predicate && i < iterations; ++i) {
		delay(interval_ms);
	}
}

}  // namespace my

#endif  // PIO_CXX_WAIT_FOR_HXX
