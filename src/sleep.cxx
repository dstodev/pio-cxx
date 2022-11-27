#include "sleep.hxx"

#include <esp_sleep.h>

#include "constants.hxx"
#include "wifi.hxx"
#include <utilities.hxx>

namespace my {
namespace sleep {

void init()
{
	// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html
	// https://github.com/espressif/esp-idf/tree/master/examples/system/

	auto time_to_sleep_usec = SleepWakeupDelay * 1'000'000ULL;
	esp_sleep_enable_timer_wakeup(time_to_sleep_usec);
}

bool start()
{
	my::printf("Disabling peripherals... ");
	bool ok = wifi::disable();
	assert_ok(ok, "Failed to disable wifi!\n");
	my::printf("done!\n");

	my::printf("Entering sleep... ");
	auto result = esp_light_sleep_start();
	ok = result == ESP_OK;
	assert_ok(ok, "Failed with result: %d\n", result);
	my::printf("done!\n");

	my::printf("Re-enabling peripherals... ");
	ok = wifi::enable();
	assert_ok(ok, "Failed to enable wifi!\n");
	my::printf("done!\n");

	return ok;
}

}  // namespace sleep
}  // namespace my
