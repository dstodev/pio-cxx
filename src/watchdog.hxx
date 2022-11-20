#ifndef PIO_CXX_WATCHDOG_HXX
#define PIO_CXX_WATCHDOG_HXX

namespace my {

void init_watchdog();

/// When watchdog is not reset in time, it panics, ultimately calling Arduino setup() again.
/// Reset the watchdog by calling reset_watchdog().
void start_watchdog();

/// Resets the watchdog.
void reset_watchdog();

}  // namespace my

#endif  // PIO_CXX_WATCHDOG_HXX
