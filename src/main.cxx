#include <Arduino.h>

#include <utilities.hxx>

#include "udp.hxx"
#include "wait_for.hxx"
#include "wifi.hxx"

void setup()
{
	Serial.begin(115200);
	wait_for(Serial, 5000 /* ms */);  // Serial implements operator bool()

	bool ok = initialize_wifi();

	if (ok) {
		Serial.println("Setup complete!");
	}
}

void loop()
{
	static uint8_t const message[] = "Hello!";

	broadcast_udp_message(58400, message, sizeof(message));

	delay(5000 /* ms */);
}
