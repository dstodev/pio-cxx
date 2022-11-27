#include "watchdog.hxx"

#include <Arduino.h>
#include <esp_task_wdt.h>

#include "constants.hxx"

namespace my {
namespace watchdog {

void init()
{
	esp_task_wdt_init(WatchdogPanicTimeout, true);
}

void start()
{
	esp_task_wdt_add(nullptr);
}

void reset()
{
	esp_task_wdt_reset();
}

void wait_for_panic()
{
	delay(-1);  // signed-to-unsigned conversion means this waits for max-int milliseconds
}

}  // namespace watchdog
}  // namespace my
