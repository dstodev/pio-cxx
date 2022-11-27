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
namespace wifi {

bool init()
{
	// https://www.arduino.cc/reference/en/libraries/wifi/

	std::string ssid, password;

	bool ok = load_wlan_creds_from_json(wlan_json, ssid, password);
	assert_ok(ok, "Could not load WLAN credentials!\n");

	WiFi.begin(ssid.c_str(), password.c_str());
	auto result = WiFi.waitForConnectResult(WaitForWiFiDelay * 1'000);
	ok = result == WL_CONNECTED;
	assert_ok(ok, "Failed to connect to wireless network with result: %hhu\n", result);

	return ok;
}

bool enable()
{
	WiFi.begin();
	auto result = WiFi.waitForConnectResult(WaitForWiFiDelay * 1'000);
	bool ok = result == WL_CONNECTED;
	assert_ok(ok, "WiFi.waitForConnectResult() failed with result: %hhu\n", result);

	return ok;
}

bool disable()
{
	bool ok = WiFi.disconnect(true);
	assert_ok(ok, "WiFi.disconnect() failed!\n");

	ok = WiFi.mode(WIFI_OFF);
	assert_ok(ok, "WiFi.mode() failed!\n");

	return ok;
}

}  // namespace wifi
}  // namespace my
