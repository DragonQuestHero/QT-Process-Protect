#include "IO_Control.h"

#define DEVICE_NAME L"\\Device\\Protect_Process"
#define LINK_NAME L"\\??\\Protect_Process"

#define PROTECT_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,0x7100,METHOD_BUFFERED ,FILE_ANY_ACCESS)
#define RE_PROTECT_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,0x7101,METHOD_BUFFERED ,FILE_ANY_ACCESS)


NTSTATUS IO_Control::Create_IO_Control(PDRIVER_OBJECT drive_object)
{
	NTSTATUS status = 0;
	//创建设备对象
	RtlInitUnicodeString(&DeviceName, DEVICE_NAME);
	status = IoCreateDevice(drive_object, 0, &DeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &DeviceObject);
	if (!NT_SUCCESS(status))
	{
		DbgPrint("Create Device error!\n");
		return status;
	}

	DeviceObject->Flags |= DO_BUFFERED_IO;
	//创建符号连接
	RtlInitUnicodeString(&LinkName, LINK_NAME);
	status = IoCreateSymbolicLink(&LinkName, &DeviceName);
	if (!NT_SUCCESS(status))
	{
		DbgPrint("Create Link error!\n");
		return status;
	}

	DbgPrint("Create Device and Link SUCCESS!\n");

	drive_object->MajorFunction[IRP_MJ_CREATE] = IO_Control::Io_DispatchCommon;
	drive_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IO_Control::IO_Control_Center;

	return STATUS_SUCCESS;
}

NTSTATUS IO_Control::Io_DispatchCommon(PDEVICE_OBJECT  DeviceObject, PIRP  pIrp)
{
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS IO_Control::Delete_IO_Control(PDRIVER_OBJECT drive_object)
{
	RtlInitUnicodeString(&LinkName, LINK_NAME);
	IoDeleteSymbolicLink(&LinkName);
	IoDeleteDevice(DeviceObject);
	DbgPrint("Link_Unload\n");
	return STATUS_SUCCESS;
}

NTSTATUS IO_Control::IO_Control_Center(PDEVICE_OBJECT  DeviceObject, PIRP  pIrp)
{
	PIO_STACK_LOCATION irp = IoGetCurrentIrpStackLocation(pIrp);
	ULONG Io_Control_Code = irp->Parameters.DeviceIoControl.IoControlCode;
	ULONG Input_Lenght = irp->Parameters.DeviceIoControl.InputBufferLength;
	ULONG Output_Lenght = irp->Parameters.DeviceIoControl.OutputBufferLength;
	WCHAR *Input_Buffer = new WCHAR[Input_Lenght];
	RtlCopyMemory(Input_Buffer, pIrp->AssociatedIrp.SystemBuffer, Input_Lenght);

	ULONG ulcode = irp->Parameters.DeviceIoControl.IoControlCode;
	if (ulcode == PROTECT_PROCESS && Input_Lenght > 0)
	{
		UNICODE_STRING temp_str;
		RtlInitUnicodeString(&temp_str, Input_Buffer);
		ULONG temp_pid;
		RtlUnicodeStringToInteger(&temp_str, 10, &temp_pid);
		PROCESS_LIST temp_list;
		temp_list.PID = temp_pid;
		Protect::_List->Push(temp_list);
	}
	if (ulcode == RE_PROTECT_PROCESS)
	{
	}
	
	


	UNICODE_STRING return_str;
	RtlInitUnicodeString(&return_str, L"SUCCESS");
	RtlCopyMemory(pIrp->AssociatedIrp.SystemBuffer, return_str.Buffer, return_str.MaximumLength);

	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = return_str.MaximumLength;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}