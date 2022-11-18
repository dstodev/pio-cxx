#include "file.hxx"

#include "ArduinoJson.h"

#include <types.hxx>

bool load_wlan_creds_from_json(char const* json, std::string& out_ssid, std::string& out_password)
{
	static StaticJsonDocument<256> wlan_config;
	auto result = deserializeJson(wlan_config, json);

	bool ok = result == DeserializationError::Ok;

	if (ok) {
#define typeof(o) remove_reference_t<decltype(o)>
		out_ssid = wlan_config.getMember("ssid").as<typeof(out_ssid)>();
		out_password = wlan_config.getMember("password").as<typeof(out_password)>();
#undef typeof
	}
	else {
		Serial.println("Could not deserialize wifi credentials!");
	}

	return ok;
}
