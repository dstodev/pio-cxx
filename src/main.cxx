#include <sstream>

#include <Arduino.h>
#include <esp_task_wdt.h>  // for esp_task_wdt_reset()

#include "constants.hxx"
#include "esp.hxx"
#include "udp.hxx"
#include "wait_for.hxx"
#include "wifi.hxx"
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
	my::wait_for(Serial, delay, WaitForSerialDelay);  // Serial implements operator bool()
	my::set_printer(ArduinoPrinter);

	bool ok = my::initialize_wifi();

	if (ok) {
		my::print("Setup complete!\n");
		Running = true;
	}
}

void loop()
{
	static uint8_t constexpr message[] = "Hello!";

	if (Running) {
		esp_task_wdt_reset();

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
