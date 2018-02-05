#pragma once
#include "Drive.h"

class Protect
{
public:
	Protect()
	{
	}
	~Protect()
	{
	}
public:
	void Hook_Start(ULONG);
	void Re_Hook();
private:
	HANDLE _Handle;
	static ULONG _PID;
	static OB_PREOP_CALLBACK_STATUS Protect_Process
		(
		__in PVOID  RegistrationContext,
		__in POB_PRE_OPERATION_INFORMATION  OperationInformation
		);
public:
	void * __cdecl operator new(size_t size, POOL_TYPE PoolType = PagedPool)
	{
		return ExAllocatePool(PagedPool, size);
	}

		void __cdecl operator delete(void* pointer)
	{
		ExFreePool(pointer);
	}
};


