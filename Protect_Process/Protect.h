#pragma once
#include "Drive.h"
#include "Struct.h"

class Protect
{
public:
	Protect()
	{
		InitializeListHead(&_List);
		KeInitializeSpinLock(&_Lock);
	}
	~Protect()
	{
	}
public:
	void Hook_Start();
	void Re_Hook();
	static LIST_ENTRY _List;
	static KSPIN_LOCK _Lock;
private:
	HANDLE _Handle;
private:
	static OB_PREOP_CALLBACK_STATUS Protect_Process
		(
		__in PVOID  RegistrationContext,
		__in POB_PRE_OPERATION_INFORMATION  OperationInformation
		);
};


