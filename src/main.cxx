#include <Arduino.h>

#include "constants.hxx"
#include "sleep.hxx"
#include "udp.hxx"
#include "watchdog.hxx"
#include "wifi.hxx"
#include <utilities.hxx>

using namespace my;

void setup()
{
	// Watchdog init/start happens first to avoid permadeath if something in setup fails
	watchdog::init();
	watchdog::start();

	sleep::init();

	Serial.begin(SerialBaudRate);
	Serial.flush();

	watchdog::reset();  // before waiting for serial connection
	wait_for(Serial, delay, WaitForSerialDelay * 1'000);  // Serial (instance of type HWCDC) implements operator bool()
	set_printer(Serial);

	watchdog::reset();  // before init_wifi() waits for Wi-Fi connection
	bool ok = wifi::init();

	if (ok) {
		my::printf("Setup complete!\n");
		my::printf("Using ESP-IDF version: %s\n", esp_get_idf_version());
	}
	else {
		delay(-1);
	}
}

void loop()
{
	static uint8_t constexpr message[] = "Hello!";

	watchdog::reset();
	my::printf("Broadcasting '%s' on port %hu... ", message, UdpBroadcastPort);

	if (udp::broadcast_message(UdpBroadcastPort, message, sizeof(message))) {
		my::printf("done!\n");
	}
	else {
		delay(-1);
	}

	sleep::start();
}
