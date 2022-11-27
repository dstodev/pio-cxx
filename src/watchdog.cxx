#include "watchdog.hxx"

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

}  // namespace watchdog
}  // namespace my
