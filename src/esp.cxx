#include "esp.hxx"

#include "constants.hxx"
#include "watchdog.hxx"

namespace my {

void init_esp32_peripherals()
{
	init_watchdog();
	start_watchdog();

	my::wake_up_from_sleep_after(SleepWakeupDelay);
}

}  // namespace my
