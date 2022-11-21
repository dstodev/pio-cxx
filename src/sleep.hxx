#ifndef PIO_CXX_SLEEP_HXX
#define PIO_CXX_SLEEP_HXX

#include <cstdint>

namespace my {

void wake_up_from_sleep_after(uint32_t time_seconds);
void start_sleep();

}  // namespace my

#endif  // PIO_CXX_SLEEP_HXX
