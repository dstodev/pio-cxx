#include "watchdog.hxx"

#include <Arduino.h>
#include <esp_task_wdt.h>

#include "constants.hxx"
#include <utilities.hxx>

namespace my {
namespace watchdog {

bool init()
{
	auto result = esp_task_wdt_init(WatchdogPanicTimeout, true);
	bool ok = result == ESP_OK;
	assert_ok(ok, "Failed to init watchdog with result: %d\n", result);
	return ok;
}

bool start()
{
	auto result = esp_task_wdt_add(nullptr);
	bool ok = result == ESP_OK;
	assert_ok(ok, "Failed to start watchdog with result: %d\n", result);
	return ok;
}

bool stop()
{
	auto result = esp_task_wdt_delete(nullptr);
	bool ok = result == ESP_OK;
	assert_ok(ok, "Failed to stop watchdog with result: %d\n", result);
	return ok;
}

bool reset()
{
	auto result = esp_task_wdt_reset();
	bool ok = result == ESP_OK;
	assert_ok(ok, "Failed to reset watchdog with result: %d\n", result);
	return ok;
}

void wait_for_panic()
{
	delay(-1);  // signed-to-unsigned conversion means this waits for max-int milliseconds
}

}  // namespace watchdog
}  // namespace my
