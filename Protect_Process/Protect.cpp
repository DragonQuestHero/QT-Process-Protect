#include "Protect.h"

LIST_ENTRY Protect::_List;
KSPIN_LOCK Protect::_Lock;

void Protect::Hook_Start()
{
	OB_OPERATION_REGISTRATION oor;
	OB_CALLBACK_REGISTRATION ob;

	ob.Version = ObGetFilterVersion();
	ob.OperationRegistrationCount = 1;
	ob.OperationRegistration = &oor;
	RtlInitUnicodeString(&ob.Altitude, L"321000");
	ob.RegistrationContext = NULL;


	oor.ObjectType = PsProcessType;
	oor.Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;

	oor.PreOperation = (POB_PRE_OPERATION_CALLBACK)Protect::Protect_Process;

	oor.PostOperation = NULL;

	ObRegisterCallbacks(&ob, &_Handle);
}

void Protect::Re_Hook()
{
	ObUnRegisterCallbacks(_Handle);
}

OB_PREOP_CALLBACK_STATUS Protect::Protect_Process
(
__in PVOID  RegistrationContext,
__in POB_PRE_OPERATION_INFORMATION  OperationInformation
)
{
	HANDLE pid = PsGetProcessId((PEPROCESS)OperationInformation->Object);
	ULONG upid = (ULONG)pid;

	if (IsListEmpty(&_List))
	{
		return OB_PREOP_SUCCESS;
	}
	for (auto p = _List.Flink; p != &_List; p = p->Flink)
	{
		PID_LIST *p2 = CONTAINING_RECORD(p, PID_LIST, List);

		if (upid == p2->PID)//_PID
		{
			if ((OperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_TERMINATE) == PROCESS_TERMINATE)
			{
				//Terminate the process, such as by calling the user-mode TerminateProcess routine..  
				OperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_TERMINATE;
			}
			if ((OperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_OPERATION) == PROCESS_VM_OPERATION)
			{
				//Modify the address space of the process, such as by calling the user-mode WriteProcessMemory and VirtualProtectEx routines.  
				OperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_OPERATION;
			}
			if ((OperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_READ) == PROCESS_VM_READ)
			{
				//Read to the address space of the process, such as by calling the user-mode ReadProcessMemory routine.  
				OperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_READ;
			}
			if ((OperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_WRITE) == PROCESS_VM_WRITE)
			{
				//Write to the address space of the process, such as by calling the user-mode WriteProcessMemory routine.  
				OperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_WRITE;
			}
			//OperationInformation->Parameters->CreateHandleInformation.DesiredAccess = 0;
		}
	}
	return OB_PREOP_SUCCESS;
}