#include "esp.hxx"

#include <esp_sleep.h>
#include <esp_task_wdt.h>

#include "constants.hxx"

namespace my {

void init_esp32_peripherals()
{
	// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html
	// https://github.com/espressif/esp-idf/blob/master/components/esp_hw_support/include/esp_sleep.h
	// https://github.com/espressif/esp-idf/tree/master/examples/system/deep_sleep
	esp_sleep_enable_timer_wakeup(SleepWakeupDelay);

	// If program does not call esp_task_wdt_reset() in time, panic. (calls setup() again)
	esp_task_wdt_init(WatchdogPanicTimeout, true);
	esp_task_wdt_add(nullptr);
}

void start_sleep()
{
	// TODO
}

}  // namespace my
