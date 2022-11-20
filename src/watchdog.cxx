#include "watchdog.hxx"

#include <esp_task_wdt.h>

#include "constants.hxx"

namespace my {

void init_watchdog()
{
	esp_task_wdt_init(WatchdogPanicTimeout, true);
}

void start_watchdog()
{
	esp_task_wdt_add(nullptr);
}

void reset_watchdog()
{
	esp_task_wdt_reset();
}

}  // namespace my
