#pragma once
#include "CRTCPP.hpp"
#include "Protect.h"
#include "Struct.h"


class IO_Control
{
public:
	IO_Control()
	{
	}
	~IO_Control()
	{
	}
public:
	NTSTATUS Create_IO_Control(PDRIVER_OBJECT drive_object);
	NTSTATUS Delete_IO_Control(PDRIVER_OBJECT drive_object);
	static NTSTATUS Io_DispatchCommon(PDEVICE_OBJECT  DeviceObject, PIRP  pIrp);
	static NTSTATUS IO_Control_Center(PDEVICE_OBJECT  DeviceObject, PIRP  pIrp);
private:
	PDEVICE_OBJECT DeviceObject = nullptr;
	UNICODE_STRING DeviceName;
	UNICODE_STRING LinkName;
};

