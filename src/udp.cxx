#include "udp.hxx"

#include <WiFiUdp.h>

#include <utilities.hxx>

namespace my {

/// returns true on success, false otherwise
bool broadcast_udp_message(std::uint16_t port, std::uint8_t const* message, std::size_t message_len)
{
	static WiFiUDP udp;

	bool ok = udp.beginPacket("255.255.255.255", port);
	if (!ok) {
		my::print("Could not resolve hostname or port!\n");
	}

	if (ok) {
		udp.write(message, message_len);
		ok = udp.endPacket() == 1;
		if (!ok) {
			my::print("Failed to send message!\n");
		}
	}

	return ok;
}

}  // namespace my
