#ifndef PIO_CXX_FILE_HXX
#define PIO_CXX_FILE_HXX

#include <string>

namespace my {

/// returns true on success, false otherwise
bool load_wlan_creds_from_json(char const* json, std::string& out_ssid, std::string& out_password);

}  // namespace my

#endif  // PIO_CXX_FILE_HXX
