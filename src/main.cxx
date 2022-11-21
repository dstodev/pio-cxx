#include <sstream>

#include <Arduino.h>

#include "constants.hxx"
#include "esp.hxx"
#include <utilities.hxx>

static bool Running = false;

void setup()
{
	my::init_watchdog();
	my::init_sleep();

	Serial.begin(SerialBaudRate);
	Serial.flush();
	my::wait_for(Serial, delay, WaitForSerialDelay);  // Serial implements operator bool()
	my::set_printer(Serial);

	bool ok = my::init_wifi();

	my::start_watchdog();

	if (ok) {
		my::printf("Setup complete!\n");
		Running = true;
	}
}

void loop()
{
	static uint8_t constexpr message[] = "Hello!";

	if (Running) {
		my::reset_watchdog();
		my::printf("Broadcasting '%s' on port %hu...", message, UdpBroadcastPort);

		if (my::broadcast_udp_message(UdpBroadcastPort, message, sizeof(message))) {
			my::printf(" done!\n");
		}
		else {
			Running = false;
		}
	}

	my::start_sleep();
}
