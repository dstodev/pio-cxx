#include "wifi.hxx"

#include <sstream>

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

bool initialize_wifi()
{
	// https://www.arduino.cc/reference/en/libraries/wifi/

	std::string ssid, password;

	bool ok = load_wlan_creds_from_json(wlan_json, ssid, password);

	if (ok) {
		WiFi.mode(WIFI_STA);
		WiFi.begin(ssid.c_str(), password.c_str());
		auto result = WiFi.waitForConnectResult(WaitForWiFiDelay);
		ok = result == WL_CONNECTED;

		if (!ok) {
			my::print("Failed to connect to wireless network!\n");
			my::print("Connect result: %hu\n", result);
		}
	}

	return ok;
}

}  // namespace my
