#include "udp.hxx"

#include <Arduino.h>
#include <WiFiUdp.h>

/// returns true on success, false otherwise
bool broadcast_udp_message(std::uint16_t port, std::uint8_t const* message, std::size_t message_len)
{
	static WiFiUDP udp;

	bool ok = udp.beginPacket("255.255.255.255", port);
	if (!ok) {
		Serial.println("Could not resolve hostname or port!");
	}

	if (ok) {
		udp.write(message, message_len);
		ok = udp.endPacket() == 1;
		if (!ok) {
			Serial.println("Failed to send message!");
		}
	}

	return ok;
}
