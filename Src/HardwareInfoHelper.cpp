#include "StdAfx.h"
#include "HardwareInfoHelper.h"

HardwareInfoHelper::HardwareInfoHelper(void)
{
}


HardwareInfoHelper::~HardwareInfoHelper(void)
{
}

std::string HardwareInfoHelper::SystemCmdPipeFunc( CString strCMD, std::string cstrEnSearch )
{
	std::string strRet;
	strRet.clear();
	const long MAX_COMMAND_SIZE = 10000; // 命令行输出缓冲大小     

	HANDLE hReadPipe  = NULL; //读取管道  
	HANDLE hWritePipe = NULL; //写入管道      
	PROCESS_INFORMATION pi;   //进程信息      
	STARTUPINFO         si;   //控制命令行窗口信息  
	SECURITY_ATTRIBUTES sa;   //安全属性  

	char            szBuffer[MAX_COMMAND_SIZE+1] = {0}; // 放置命令行结果的输出缓冲区  
	std::string          strBuffer;  
	unsigned long   count = 0;  
	long            ipos  = 0;  

	memset(&pi, 0, sizeof(pi));  
	memset(&si, 0, sizeof(si));  
	memset(&sa, 0, sizeof(sa));  

	pi.hProcess = NULL;  
	pi.hThread  = NULL;  
	si.cb       = sizeof(STARTUPINFO);  
	sa.nLength  = sizeof(SECURITY_ATTRIBUTES);  
	sa.lpSecurityDescriptor = NULL;  
	sa.bInheritHandle       = TRUE;  

	do 
	{
		//1.0 创建管道  
		BOOL bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);  
		if(!bret)  
		{  
			break;  
		}  

		//2.0 设置命令行窗口的信息为指定的读写管道  
		GetStartupInfo(&si);  
		si.hStdError    = hWritePipe;  
		si.hStdOutput   = hWritePipe;  
		si.wShowWindow  = SW_HIDE; //隐藏命令行窗口  
		si.dwFlags      = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;  

		//3.0 创建获取命令行的进程  
		bret = CreateProcess(NULL, strCMD.GetBuffer(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi );  
		if(!bret)  
		{  
			break;
		}     

		//4.0 读取返回的数据  
		WaitForSingleObject (pi.hProcess, 500/*INFINITE*/);  
		bret  =  ReadFile(hReadPipe,  szBuffer,  MAX_COMMAND_SIZE,  &count,  0);  
		if(!bret)  
		{  
			break;
		}  

		//5.0 查找主板序列号  
		bret = FALSE;  
		strBuffer = szBuffer;  
		ipos = strBuffer.find(cstrEnSearch);  

		if (ipos < 0) // 没有找到  
		{         
			break;
		}  
		else  
		{  
			strBuffer = strBuffer.substr(ipos+cstrEnSearch.length());  
		}

		memset(szBuffer, 0x00, sizeof(szBuffer));  
		strcpy_s(szBuffer, strBuffer.c_str());  

		//去掉中间的空格 \r \n  
		int j = 0;  
		for (size_t i = 0; i < strlen(szBuffer); i++)  
		{  
			if (szBuffer[i] != ' ' && szBuffer[i] != '\n' && szBuffer[i] != '\r')  
			{  
				strRet.push_back(szBuffer[i]);
				j++;  
			}  
		}  
	} while (0);

	//关闭所有的句柄  
	CloseHandle(hWritePipe);  
	CloseHandle(hReadPipe);  
	CloseHandle(pi.hProcess);  
	CloseHandle(pi.hThread);  

	return strRet;  
}

std::string HardwareInfoHelper::GetMotherBoardID()
{
	return SystemCmdPipeFunc(_T("wmic BaseBoard get SerialNumber"), "SerialNumber");
}

std::string HardwareInfoHelper::GetCPUID()
{
	return SystemCmdPipeFunc(_T("wmic cpu get processorid"), "ProcessorId");
}

std::string HardwareInfoHelper::GetHarddiskID()
{
	return SystemCmdPipeFunc(_T("wmic diskdrive get SerialNumber"), "SerialNumber");
}

std::string HardwareInfoHelper::GetNetMacID()
{
	return SystemCmdPipeFunc(_T("wmic nicconfig get macaddress"), "MACAddress");
}
