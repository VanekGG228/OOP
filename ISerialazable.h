#pragma once
#include <fstream>
class ISerialazable
{
public:
	virtual void serializeBin(std::ofstream& out) = 0;
	virtual void serializeJson(std::ofstream& out) = 0;
};

