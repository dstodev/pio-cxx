#ifndef PIO_CXX_SLEEP_HXX
#define PIO_CXX_SLEEP_HXX

#include <cstdint>

namespace my {

void init_sleep();
void start_sleep();

/// Delay the calling task, giving execution time to other tasks.
void yield_for(uint32_t time_seconds);

}  // namespace my

#endif  // PIO_CXX_SLEEP_HXX
