#pragma once
#include <string>

class HardwareInfoHelper
{
private:
	HardwareInfoHelper(void);
	~HardwareInfoHelper(void);
protected:
	static std::string SystemCmdPipeFunc(CString strCMD, std::string cstrEnSearch);
public:
	static std::string GetMotherBoardID();
	static std::string GetCPUID();
	static std::string GetHarddiskID();
	static std::string GetNetMacID();
};

