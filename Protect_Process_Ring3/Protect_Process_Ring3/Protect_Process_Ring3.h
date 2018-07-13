#pragma once

#include <QtWidgets/QMainWindow>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QScrollBar>
#include <QModelIndex>
#include <QDebug>
#include "ui_Protect_Process_Ring3.h"

#include <string>

#include <windows.h>
#include <Tlhelp32.h>

class Protect_Process_Ring3 : public QMainWindow
{
	Q_OBJECT

public:
	Protect_Process_Ring3(QWidget *parent = Q_NULLPTR);
public slots:
	void SLOT_Protect();
	void SLOT_Clear();
private:
	void Set_SLOTS();
	void Get_Process_List();
private:
	QStandardItemModel *_Model;
private:
	Ui::Protect_Process_Ring3Class ui;
};
