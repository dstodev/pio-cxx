#include <sstream>

#include <Arduino.h>

#include "constants.hxx"
#include "esp.hxx"
#include <utilities.hxx>

static struct
{
	static void print(char const* message)
	{
		Serial.print(message);
	}

} ArduinoPrinter;

static bool Running = false;

void setup()
{
	my::init_esp32_peripherals();

	Serial.begin(SerialBaudRate);
	Serial.flush();
	my::wait_for(Serial, delay, WaitForSerialDelay);  // Serial implements operator bool()
	my::set_printer(ArduinoPrinter);

	bool ok = my::init_wifi();

	if (ok) {
		my::print("Setup complete!\n");
		Running = true;
	}
}

void loop()
{
	static uint8_t constexpr message[] = "Hello!";

	if (Running) {
		my::reset_watchdog();
		my::print("Broadcasting '%s' on port %hu...", message, UdpBroadcastPort);

		if (my::broadcast_udp_message(UdpBroadcastPort, message, sizeof(message))) {
			my::print(" done!\n");
		}
		else {
			Running = false;
		}
	}

	delay(LoopDelay);
}
