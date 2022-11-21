#include "sleep.hxx"

#include <Arduino.h>
#include <esp_sleep.h>

#include "constants.hxx"
#include <utilities.hxx>

namespace my {

void init_sleep()
{
	// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html
	// https://github.com/espressif/esp-idf/tree/master/examples/system/

	auto time_to_sleep_usec = SleepWakeupDelay * 1'000'000ULL;
	esp_sleep_enable_timer_wakeup(time_to_sleep_usec);
}

void start_sleep()
{
	my::printf("Entering sleep...\n");

	// Give extra time for background tasks to process before sleeping
	auto extra_task_processing_time_ms = WakeupExtraProcessingTime * 1'000;
	delay(extra_task_processing_time_ms);

	auto result = esp_light_sleep_start();

	bool ok = result == ESP_OK;

	if (ok) {
		my::printf("Woke from sleep!\n");
	}
	else {
		my::printf("Failed to sleep!\n");
		my::printf("Sleep result: %d\n", result);
	}
}

}  // namespace my
