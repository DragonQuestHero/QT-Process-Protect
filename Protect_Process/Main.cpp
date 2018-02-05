#include "Drive.h"
#include "IO_Control.h"
#include "Protect.h"

IO_Control *io_control = nullptr;

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT drive_object, PUNICODE_STRING path)
{
	DbgPrint("Start\n");
	drive_object->DriverUnload = DriverUnload;
	Jump_Flags(drive_object);

	Protect *protect = new Protect();
	io_control = new IO_Control(protect);
	io_control->Create_IO_Control(drive_object);


	return STATUS_SUCCESS;
}

void DriverUnload(PDRIVER_OBJECT drive_object)
{
	UNREFERENCED_PARAMETER(drive_object);

	io_control->Delete_IO_Control(drive_object);

	//Link_Unload(drive_object);




	DbgPrint("Unload Over!\n");
}

void Jump_Flags(PDRIVER_OBJECT drive_object)
{
	PLDR_DATA_TABLE_ENTRY64 ldr;
	ldr = (PLDR_DATA_TABLE_ENTRY64)drive_object->DriverSection;
	ldr->Flags |= 0x20;
}