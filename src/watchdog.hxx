#ifndef PIO_CXX_WATCHDOG_HXX
#define PIO_CXX_WATCHDOG_HXX

namespace my {
namespace watchdog {

/// Initialize the watchdog.
bool init();

/// Start the watchdog by subscribing the calling task.
/// When watchdog is not reset in time, it panics, ultimately calling Arduino setup() again.
/// Reset the watchdog by calling reset_watchdog().
bool start();

/// Stop the watchdog by unsubscribing the calling task.
bool stop();

/// Resets the watchdog.
bool reset();

/// Waits for the watchdog to panic. Useful for fail conditions.
void wait_for_panic();

}  // namespace watchdog
}  // namespace my

#endif  // PIO_CXX_WATCHDOG_HXX
