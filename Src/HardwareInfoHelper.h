#pragma once
#include <string>

class HardwareInfoHelper
{
private:
	HardwareInfoHelper(void);
	~HardwareInfoHelper(void);
public:
	static std::string GetMotherBoardID();
	static std::string GetCPUID();
	static std::string GetStorageID();
	static std::string GetNetMacID();
};

