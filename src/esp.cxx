#include "esp.hxx"

#include "watchdog.hxx"

namespace my {

void init_esp32_peripherals()
{
	init_watchdog();
	start_watchdog();
}

}  // namespace my
