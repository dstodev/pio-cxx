#ifndef PIO_CXX_ARDUINO_HXX
#define PIO_CXX_ARDUINO_HXX

#include <cstdint>

#include <Arduino.h>

namespace my {

/// Wait up to timeout milliseconds for predicate, checking every interval.
/// A predicate is anything testable as a boolean, especially stateful classes which implement operator bool().
template <typename Predicate>
void wait_for_ms(Predicate& predicate, uint32_t timeout, uint32_t interval = 10 /* ms */)
{
	auto iterations = timeout / interval;
	for (auto i {0}; !predicate && i < iterations; ++i) {
		delay(interval);
	}
}

}  // namespace my

#endif  // PIO_CXX_ARDUINO_HXX
