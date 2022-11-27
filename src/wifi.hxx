#ifndef PIO_CXX_WIFI_HXX
#define PIO_CXX_WIFI_HXX

namespace my {
namespace wifi {

/// Returns true on success, false otherwise.
bool init();
bool enable();
bool disable();

}  // namespace wifi
}  // namespace my

#endif  // PIO_CXX_WIFI_HXX
