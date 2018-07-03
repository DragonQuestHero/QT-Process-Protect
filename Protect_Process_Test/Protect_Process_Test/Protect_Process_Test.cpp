// Protect_Process_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <windows.h>

#define PROTECT_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,0x7100,METHOD_BUFFERED ,FILE_ANY_ACCESS)
#define RE_PROTECT_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,0x7101,METHOD_BUFFERED ,FILE_ANY_ACCESS)


extern "C" __declspec(dllexport) int Protect(int pid)
{
	HANDLE m_hDevice = CreateFileA("\\\\.\\Protect_Process", GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == m_hDevice)
	{
		return 0;
	}
	DWORD dwRet = NULL;
	WCHAR p[1024] = { 0 };
	memcpy(p, std::to_wstring(pid).data(), std::to_wstring(pid).length() * 2);
	DeviceIoControl(m_hDevice, PROTECT_PROCESS, p, sizeof(p), p, sizeof(p), &dwRet, NULL); //hook it.
	CloseHandle(m_hDevice);
	return 1;
}

extern "C" __declspec(dllexport) int RE_Protect()
{
	HANDLE m_hDevice = CreateFileA("\\\\.\\Protect_Process", GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == m_hDevice)
	{
		return 0;
	}
	DWORD dwRet = NULL;
	WCHAR p[1024] = { 0 };
	DeviceIoControl(m_hDevice, RE_PROTECT_PROCESS, p, sizeof(p), p, sizeof(p), &dwRet, NULL); //hook it.
	CloseHandle(m_hDevice);
	return 1;
}

int main(int argc, char *argv[])
{
	Protect(std::stoi(argv[1]));

    return 0;
}

