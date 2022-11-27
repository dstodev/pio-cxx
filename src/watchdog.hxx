#ifndef PIO_CXX_WATCHDOG_HXX
#define PIO_CXX_WATCHDOG_HXX

namespace my {
namespace watchdog {

void init();

/// When watchdog is not reset in time, it panics, ultimately calling Arduino setup() again.
/// Reset the watchdog by calling reset_watchdog().
void start();

/// Resets the watchdog.
void reset();

}  // namespace watchdog
}  // namespace my

#endif  // PIO_CXX_WATCHDOG_HXX
