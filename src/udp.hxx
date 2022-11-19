#ifndef PIO_CXX_UDP_HXX
#define PIO_CXX_UDP_HXX

#include <cstdint>

namespace my {

bool broadcast_udp_message(std::uint16_t port, std::uint8_t const* message, std::size_t message_len);

}

#endif  // PIO_CXX_UDP_HXX
