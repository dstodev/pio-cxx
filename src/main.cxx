#include <sstream>

#include <Arduino.h>

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

void setup()
{
	Serial.begin(115'200);
	my::wait_for(Serial, 10'000 /* ms */);  // Serial implements operator bool()
	my::set_printer(ArduinoPrinter);

	bool ok = my::initialize_wifi();

	if (ok) {
		my::print("Setup complete!\n");
	}
}

void loop()
{
	static uint8_t constexpr message[] = "Hello!";
	static uint16_t constexpr port = 58'400;

	// TODO: Make message constexpr
	std::ostringstream echo {};
	echo << "Broadcasting '" << message << "' on port " << port << "...";
	auto echo_str = echo.str();
	my::print(echo_str.c_str());

	if (my::broadcast_udp_message(58'400, message, sizeof(message))) {
		my::print(" done!\n");
	}

	delay(5'000 /* ms */);
}
