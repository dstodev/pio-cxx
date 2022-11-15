#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#include <string>

#include "../wlan.cfg.hxx"
#include "utilities.hxx"

using namespace project;
using namespace ArduinoJson6194_F1;


/// returns true on success, false otherwise
bool load_wlan_from_json(char const* json, std::string& out_ssid, std::string& out_password)
{
	static StaticJsonDocument<256> wlan_config;
	auto result = deserializeJson(wlan_config, json);

	bool ok = result == DeserializationError::Ok;

	if (ok) {
#define type(o) my::remove_reference_t<decltype(o)>
		out_ssid = wlan_config.getMember("ssid").as<type(out_ssid)>();
		out_password = wlan_config.getMember("password").as<type(out_password)>();
#undef type
	}
	else {
		Serial.println("Could not deserialize wifi credentials!");
	}

	return ok;
}

/// returns true on success, false otherwise
bool initialize_wifi()
{
	// https://www.arduino.cc/reference/en/libraries/wifi/

	std::string ssid, password;

	bool ok = load_wlan_from_json(wlan_json, ssid, password);

	if (ok) {
		WiFi.mode(WIFI_STA);
		WiFi.begin(ssid.c_str(), password.c_str());
		auto result = WiFi.waitForConnectResult(5000 /* ms */);  // wait to connect
		ok = result == WL_CONNECTED;

		if (!ok) {
			Serial.println("Failed to connect to wireless network!");
			Serial.print("Connect result: ");
			Serial.println(result);
		}
	}

	return ok;
}

void setup()
{
	Serial.begin(115200);

	// Wait up to 1 second for serial start, checking every 10ms
	for (auto i {0}; !Serial && i < 100; ++i) {
		delay(10 /* ms */);
	}

	bool ok = initialize_wifi();

	if (ok) {
		Serial.println("Setup complete!");
	}
}

void loop()
{
	static uint8_t const message[] = "hello!";
	static WiFiUDP udp;

	// If this boolean becomes false, it will remain false on the next loop cycle (it is static).
	// This means all following if (ok) { ... } blocks no longer execute if a problem occurs.
	static bool ok = true;

	bool stop_udp = false;

	if (ok) {
		ok = udp.beginPacket("255.255.255.255", 58400);
		if (!ok) {
			Serial.println("Could not resolve hostname or port!");
			stop_udp = true;
		}
	}

	if (ok) {
		udp.write(message, sizeof(message));
		ok = udp.endPacket() == 1;
		if (!ok) {
			Serial.println("Failed to send message!");
			stop_udp = true;
		}
	}

	if (stop_udp) {
		// A problem occurred this loop cycle
		udp.stop();
	}

	delay(1000 /* ms */);
}
