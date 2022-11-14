#include <Arduino.h>
#include <ArduinoJson.h>

#include <string>

#include "../wlan.cfg.hxx"

using namespace project;
using namespace ArduinoJson6194_F1;

static struct
{
	std::string ssid;
	std::string password;
} WLAN;

void load_wlan_from_json(char const* json)
{
	static StaticJsonDocument<256> wlan_config;
	auto error = deserializeJson(wlan_config, json);

	if (error) {
		Serial.println("Could not deserialize wifi credentials!");
	}

	WLAN.ssid = wlan_config.getMember("ssid").as<std::string>();
	WLAN.password = wlan_config.getMember("password").as<std::string>();
}

void setup()
{
	Serial.begin(115200);

	while (!Serial) {
		// Wait for serial start
		delay(10);
	}

	load_wlan_from_json(wlan_json);

	// https://www.arduino.cc/reference/en/libraries/wifi/

	Serial.println("Setup complete!");
}

void loop()
{
	delay(10000);
	Serial.print("ssid: ");
	Serial.println(WLAN.ssid.c_str());
	Serial.print("password: ");
	Serial.println(WLAN.password.c_str());
}
