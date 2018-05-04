#pragma once
#include "CRTCPP.hpp"
#include "Link_List.hpp"
#include "NtSysAPI_Func.hpp"
#include "Process.hpp"

#include "Struct.h"


class Protect
{
public:
	Protect()
	{
		_List = new CG::Link_List<PROCESS_LIST>();
	}
	~Protect()
	{
	}
public:
	void Protect_Start();
	void Protect_Stop();
	static CG::Link_List<PROCESS_LIST> *_List;
private:
	HANDLE _Handle;
private:
	static OB_PREOP_CALLBACK_STATUS Protect_Process
		(
		__in PVOID  RegistrationContext,
		__in POB_PRE_OPERATION_INFORMATION  OperationInformation
		);
};


