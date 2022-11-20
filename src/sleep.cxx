#include "sleep.hxx"

#include <esp_sleep.h>

namespace my {

void wake_up_from_sleep_after(uint32_t time_in_seconds)
{
	auto time_in_usec = time_in_seconds * 1'000'000;

	// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html
	// https://github.com/espressif/esp-idf/blob/master/components/esp_hw_support/include/esp_sleep.h
	// https://github.com/espressif/esp-idf/tree/master/examples/system/deep_sleep
	esp_sleep_enable_timer_wakeup(time_in_usec);
}

void start_sleep()
{
	// TODO
}

}  // namespace my
