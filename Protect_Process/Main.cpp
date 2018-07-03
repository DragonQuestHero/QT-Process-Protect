#include "CRTCPP.hpp"
#include "IO_Control.h"
#include "Protect.h"

IO_Control *io_control = nullptr;
Protect *protect = nullptr;

void DriverUnload(PDRIVER_OBJECT drive_object)
{
	protect->Protect_Stop();
	io_control->Delete_IO_Control(drive_object);

	DbgPrint("Unload Over!\n");
}

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT drive_object, PUNICODE_STRING path)
{
	DbgPrint("Start\n");
	drive_object->DriverUnload = DriverUnload;

	io_control = new IO_Control();
	io_control->Create_IO_Control(drive_object);

	protect = new Protect();
	protect->Protect_Start();

	return STATUS_SUCCESS;
}



