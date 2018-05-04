#pragma once
#include "Ntddk.hpp"

struct PROCESS_LIST
{
	PROCESS_LIST()
	{
		RtlZeroMemory(Process_Path, 1024);
	}
	ULONG PID;
	WCHAR Process_Path[1024];
};

#define PROCESS_TERMINATE         0x0001    
#define PROCESS_VM_OPERATION      0x0008    
#define PROCESS_VM_READ           0x0010    
#define PROCESS_VM_WRITE          0x0020  

#define PROCESS_CREATE_THREAD  0x0002
#define PROCESS_CREATE_PROCESS 0x0080
#define PROCESS_TERMINATE      0x0001
#define PROCESS_VM_WRITE       0x0020
#define PROCESS_VM_READ        0x0010
#define PROCESS_VM_OPERATION   0x0008
#define PROCESS_SUSPEND_RESUME 0x0800


