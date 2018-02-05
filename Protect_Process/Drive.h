#pragma once
#include <Ntddk.h>


void Jump_Flags(PDRIVER_OBJECT drive_object);
void DriverUnload(PDRIVER_OBJECT drive_object);




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

typedef struct _LDR_DATA_TABLE_ENTRY64
{
	LIST_ENTRY64    InLoadOrderLinks;
	LIST_ENTRY64    InMemoryOrderLinks;
	LIST_ENTRY64    InInitializationOrderLinks;
	PVOID            DllBase;
	PVOID            EntryPoint;
	ULONG            SizeOfImage;
	UNICODE_STRING    FullDllName;
	UNICODE_STRING     BaseDllName;
	ULONG            Flags;
	USHORT            LoadCount;
	USHORT            TlsIndex;
	PVOID            SectionPointer;
	ULONG            CheckSum;
	PVOID            LoadedImports;
	PVOID            EntryPointActivationContext;
	PVOID            PatchInformation;
	LIST_ENTRY64    ForwarderLinks;
	LIST_ENTRY64    ServiceTagLinks;
	LIST_ENTRY64    StaticLinks;
	PVOID            ContextInformation;
	ULONG            OriginalBase;
	LARGE_INTEGER    LoadTime;
} LDR_DATA_TABLE_ENTRY64, *PLDR_DATA_TABLE_ENTRY64;

