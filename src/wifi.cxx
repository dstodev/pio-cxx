#include "wifi.hxx"

#include <WiFi.h>

#if __has_include("../wlan.cfg.hxx")
#include "../wlan.cfg.hxx"
#else
#error "Missing required file wlan.cfg.hxx in project directory! Follow the directions in wlan.cfg.template.hxx"
#endif

#include "constants.hxx"
#include "file.hxx"
#include <utilities.hxx>

namespace my {

bool init_wifi()
{
	// https://www.arduino.cc/reference/en/libraries/wifi/

	std::string ssid, password;

	bool ok = load_wlan_creds_from_json(wlan_json, ssid, password);

	if (ok) {
		WiFi.begin(ssid.c_str(), password.c_str());
		auto result = WiFi.waitForConnectResult(WaitForWiFiDelay * 1'000);
		ok = result == WL_CONNECTED;

		if (!ok) {
			my::printf("Failed to connect to wireless network!\n");
			my::printf("Connect result: %hhu\n", result);
		}
	}

	return ok;
}

}  // namespace my
