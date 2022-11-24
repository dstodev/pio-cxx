#ifndef PIO_CXX_UDP_HXX
#define PIO_CXX_UDP_HXX

#include <cstdint>

namespace my {

/// Returns true on success, false otherwise.
bool broadcast_udp_message(uint16_t port, uint8_t const* message, std::size_t message_len);

}  // namespace my

#endif  // PIO_CXX_UDP_HXX
