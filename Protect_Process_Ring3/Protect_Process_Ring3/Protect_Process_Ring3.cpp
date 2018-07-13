#include "Protect_Process_Ring3.h"

#define PROTECT_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,0x7100,METHOD_BUFFERED ,FILE_ANY_ACCESS)
#define RE_PROTECT_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,0x7101,METHOD_BUFFERED ,FILE_ANY_ACCESS)

Protect_Process_Ring3::Protect_Process_Ring3(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	_Model = new QStandardItemModel();
	ui.tableView->setModel(_Model);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableView->horizontalHeader()->setSectionsClickable(false);
	ui.tableView->verticalHeader()->setDefaultSectionSize(25);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	_Model->setColumnCount(2);
	_Model->setHeaderData(0, Qt::Horizontal, u8"PID");
	_Model->setHeaderData(1, Qt::Horizontal, u8"Name");
	ui.tableView->setColumnWidth(1, 100);
	ui.tableView->setColumnWidth(1, 180);
	ui.tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	for (int i = 0; i < 2; i++)
	{
		ui.tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
	}


	Set_SLOTS();

	Get_Process_List();
}

void Protect_Process_Ring3::Set_SLOTS()
{
	connect(ui._Protect_pushButton, SIGNAL(clicked()), this, SLOT(SLOT_Protect()));
	connect(ui._Clear_pushButton, SIGNAL(clicked()), this, SLOT(SLOT_Clear()));
}

void Protect_Process_Ring3::Get_Process_List()
{
	int temp_index = 0;
	BOOL working = 0;
	PROCESSENTRY32 lppe = { 0 };
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot)
	{
		lppe.dwSize = sizeof(lppe);
		working = Process32First(hSnapshot, &lppe);
		while (working)
		{
			_Model->setVerticalHeaderItem(temp_index, new QStandardItem);
			_Model->setData(_Model->index(temp_index, 0), (long)lppe.th32ProcessID);
			_Model->setData(_Model->index(temp_index, 1), lppe.szExeFile);
			working = Process32Next(hSnapshot, &lppe);
			temp_index++;
		}
	}
}

void Protect_Process_Ring3::SLOT_Protect()
{
	HANDLE m_hDevice = CreateFileA("\\\\.\\Protect_Process", GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == m_hDevice)
	{
		QMessageBox::information(NULL, "ERROR", "CreateFileA");
	}
	DWORD dwRet = NULL;
	WCHAR p[1024] = { 0 };
	int pid = _Model->index(ui.tableView->currentIndex().row(), 0).data().toInt();
	memcpy(p, std::to_wstring(pid).data(), std::to_wstring(pid).length() * 2);
	DeviceIoControl(m_hDevice, PROTECT_PROCESS, p, sizeof(p), p, sizeof(p), &dwRet, NULL); //hook it.
	CloseHandle(m_hDevice);
	QMessageBox::information(NULL, "", "I think successful");
	/*qDebug() << _Model->index(ui.tableView->currentIndex().row(), 0).data();
	qDebug() << _Model->index(ui.tableView->currentIndex().row(), 1).data();*/
}

void Protect_Process_Ring3::SLOT_Clear()
{
	HANDLE m_hDevice = CreateFileA("\\\\.\\Protect_Process", GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == m_hDevice)
	{
		QMessageBox::information(NULL, "ERROR", "CreateFileA");
	}
	DWORD dwRet = NULL;
	WCHAR p[1024] = { 0 };
	DeviceIoControl(m_hDevice, RE_PROTECT_PROCESS, p, sizeof(p), p, sizeof(p), &dwRet, NULL); //hook it.
	CloseHandle(m_hDevice);
	QMessageBox::information(NULL, "", "I think successful");
}