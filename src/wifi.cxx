#include "wifi.hxx"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>

#include "../wlan.cfg.hxx"
#include "file.hxx"

bool initialize_wifi()
{
	// https://www.arduino.cc/reference/en/libraries/wifi/

	std::string ssid, password;

	bool ok = load_wlan_creds_from_json(wlan_json, ssid, password);

	if (ok) {
		WiFi.mode(WIFI_STA);
		WiFi.begin(ssid.c_str(), password.c_str());
		auto result = WiFi.waitForConnectResult(5000 /* ms */);
		ok = result == WL_CONNECTED;

		if (!ok) {
			Serial.println("Failed to connect to wireless network!");
			Serial.print("Connect result: ");
			Serial.println(result);
		}
	}

	return ok;
}
