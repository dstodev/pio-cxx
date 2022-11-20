#ifndef PIO_CXX_ESP_HXX
#define PIO_CXX_ESP_HXX

#include "sleep.hxx"
#include "udp.hxx"
#include "watchdog.hxx"
#include "wifi.hxx"

namespace my {

void init_esp32_peripherals();

}  // namespace my

#endif  // PIO_CXX_ESP_HXX
