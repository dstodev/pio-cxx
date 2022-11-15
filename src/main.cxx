#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#include <string>

#include "../wlan.cfg.hxx"

using namespace project;
using namespace ArduinoJson6194_F1;

static struct
{
	std::string ssid;
	std::string password;
} WLAN;

/// returns true on success, false otherwise
bool load_wlan_from_json(char const* json)
{
	static StaticJsonDocument<256> wlan_config;
	auto result = deserializeJson(wlan_config, json);

	bool ok = result == DeserializationError::Ok;

	if (ok) {
		WLAN.ssid = wlan_config.getMember("ssid").as<std::string>();
		WLAN.password = wlan_config.getMember("password").as<std::string>();
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

	bool ok = load_wlan_from_json(wlan_json);

	if (ok) {
		WiFi.mode(WIFI_STA);
		WiFi.begin(WLAN.ssid.c_str(), WLAN.password.c_str());
		auto result = WiFi.waitForConnectResult(5000 /* ms */);  // wait to connect
		ok = result == WL_CONNECTED;
		Serial.print("wifi connect result: ");
		Serial.println(result);
	}

	if (!ok) {
		Serial.println("Failed to connect to wireless network!");
	}

	return ok;
}

void setup()
{
	Serial.begin(115200);

	while (!Serial) {
		// Wait for serial start
		delay(10 /* ms */);
	}

	bool ok = initialize_wifi();

	if (ok) {
		Serial.println("Setup complete!");
	}
}

void loop()
{
	static uint8_t const message[] = "Hello!";
	static WiFiUDP udp;

	bool ok = udp.beginPacket("255.255.255.255", 58400);

	if (ok) {
		udp.write(message, sizeof(message));
		ok = udp.endPacket() == 1;
	}
	else {
		Serial.println("Could not resolve hostname or port!");
	}

	if (!ok) {
		Serial.println("Failed to send message!");
	}

	delay(1000 /* ms */);
}
