#pragma once
#include <fstream>
#include <nlohmann/json.hpp>

class ISerialazable
{
public:
	virtual void serializeBin(std::ofstream& out) = 0;
	virtual void serializeJson(nlohmann::json& j) = 0;
};

