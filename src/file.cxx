#include "file.hxx"

#include "ArduinoJson.h"

#include <utilities.hxx>

namespace my {

bool load_wlan_creds_from_json(char const* json, std::string& out_ssid, std::string& out_password)
{
	static StaticJsonDocument<256> wlan_config;
	auto result = deserializeJson(wlan_config, json);

	bool ok = result == DeserializationError::Ok;

	if (ok) {
		out_ssid = wlan_config.getMember("ssid").as<typeof(out_ssid)>();
		out_password = wlan_config.getMember("password").as<typeof(out_password)>();
	}
	else {
		my::printf("Could not deserialize wifi credentials!\n");
	}

	return ok;
}

}  // namespace my
