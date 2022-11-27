#include "udp.hxx"

#include <WiFiUdp.h>

#include <utilities.hxx>

namespace my {
namespace udp {

bool broadcast_message(uint16_t port, uint8_t const* message, std::size_t message_len)
{
	static WiFiUDP udp;

	bool ok = udp.beginPacket("255.255.255.255", port);
	assert_ok(ok, "Could not resolve hostname or port!\n");

	udp.write(message, message_len);
	ok = udp.endPacket() == 1;
	assert_ok(ok, "Failed to send message!\n");

	return ok;
}

}  // namespace udp
}  // namespace my
