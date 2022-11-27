#include <Arduino.h>

#include "constants.hxx"
#include "esp.hxx"
#include <utilities.hxx>

static bool Running = false;

using namespace my;

void setup()
{
	// Watchdog init/start happens first to avoid permadeath if something in setup fails
	init_watchdog();
	start_watchdog();

	init_sleep();

	Serial.begin(SerialBaudRate);
	Serial.flush();

	reset_watchdog();  // Reset watchdog before waiting for serial connection
	wait_for(Serial, delay, WaitForSerialDelay * 1'000);  // Serial (instance of type HWCDC) implements operator bool()
	set_printer(Serial);

	reset_watchdog();  // init_wifi() waits for connection; reset watchdog first
	bool ok = init_wifi();

	if (ok) {
		my::printf("Setup complete!\n");
		my::printf("Using ESP-IDF version: %s\n", esp_get_idf_version());
		Running = true;
	}
}

void loop()
{
	static uint8_t constexpr message[] = "Hello!";

	if (Running) {
		reset_watchdog();

		my::printf("Broadcasting '%s' on port %hu... ", message, UdpBroadcastPort);

		if (broadcast_udp_message(UdpBroadcastPort, message, sizeof(message))) {
			my::printf("done!\n");
		}
		else {
			Running = false;
			my::printf("failed!\n");
		}

		// Reset watchdog as late as possible before yielding to other tasks, but only if running.
		reset_watchdog();
	}

	// Give execution time to other tasks before turning off some components to save power.
	yield_for(TaskProcessingTime);
	start_sleep();
}
