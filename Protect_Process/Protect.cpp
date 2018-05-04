#include "Protect.h"


CG::Link_List<PROCESS_LIST> *Protect::_List;

void Protect::Protect_Start()
{
	NTSTATUS status = 0;

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

	status = ObRegisterCallbacks(&ob, &_Handle);
	if (!NT_SUCCESS(status))
	{
		DbgBreakPoint();
	}
}

void Protect::Protect_Stop()
{
	ObUnRegisterCallbacks(_Handle);
}

OB_PREOP_CALLBACK_STATUS Protect::Protect_Process
(
__in PVOID  RegistrationContext,
__in POB_PRE_OPERATION_INFORMATION  OperationInformation
)
{
	if (_List->Get_Size() < 1)
	{
		return OB_PREOP_SUCCESS;
	}

	HANDLE pid = PsGetProcessId((PEPROCESS)OperationInformation->Object);

	if (_List->Search((ULONG)pid, 0))
	{
		//if ((OperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_TERMINATE) == PROCESS_TERMINATE)
		//{
		//	//Terminate the process, such as by calling the user-mode TerminateProcess routine..  
		//	OperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_TERMINATE;
		//}
		//if ((OperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_OPERATION) == PROCESS_VM_OPERATION)
		//{
		//	//Modify the address space of the process, such as by calling the user-mode WriteProcessMemory and VirtualProtectEx routines.  
		//	OperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_OPERATION;
		//}
		//if ((OperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_READ) == PROCESS_VM_READ)
		//{
		//	//Read to the address space of the process, such as by calling the user-mode ReadProcessMemory routine.  
		//	OperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_READ;
		//}
		//if ((OperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_WRITE) == PROCESS_VM_WRITE)
		//{
		//	//Write to the address space of the process, such as by calling the user-mode WriteProcessMemory routine.  
		//	OperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_WRITE;
		//}
		OperationInformation->Parameters->CreateHandleInformation.DesiredAccess = 0;
	}

	return OB_PREOP_SUCCESS;
}


