/********************************************************************************
** Form generated from reading UI file 'Protect_Process_Ring3.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROTECT_PROCESS_RING3_H
#define UI_PROTECT_PROCESS_RING3_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Protect_Process_Ring3Class
{
public:
    QWidget *centralWidget;
    QPushButton *_Protect_pushButton;
    QPushButton *_Clear_pushButton;
    QTableView *tableView;

    void setupUi(QMainWindow *Protect_Process_Ring3Class)
    {
        if (Protect_Process_Ring3Class->objectName().isEmpty())
            Protect_Process_Ring3Class->setObjectName(QStringLiteral("Protect_Process_Ring3Class"));
        Protect_Process_Ring3Class->resize(332, 501);
        centralWidget = new QWidget(Protect_Process_Ring3Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        _Protect_pushButton = new QPushButton(centralWidget);
        _Protect_pushButton->setObjectName(QStringLiteral("_Protect_pushButton"));
        _Protect_pushButton->setGeometry(QRect(20, 460, 131, 31));
        _Clear_pushButton = new QPushButton(centralWidget);
        _Clear_pushButton->setObjectName(QStringLiteral("_Clear_pushButton"));
        _Clear_pushButton->setGeometry(QRect(180, 460, 131, 31));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 10, 311, 441));
        Protect_Process_Ring3Class->setCentralWidget(centralWidget);

        retranslateUi(Protect_Process_Ring3Class);

        QMetaObject::connectSlotsByName(Protect_Process_Ring3Class);
    } // setupUi

    void retranslateUi(QMainWindow *Protect_Process_Ring3Class)
    {
        Protect_Process_Ring3Class->setWindowTitle(QApplication::translate("Protect_Process_Ring3Class", "Protect_Process_Ring3", Q_NULLPTR));
        _Protect_pushButton->setText(QApplication::translate("Protect_Process_Ring3Class", "Protect", Q_NULLPTR));
        _Clear_pushButton->setText(QApplication::translate("Protect_Process_Ring3Class", "Clear", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Protect_Process_Ring3Class: public Ui_Protect_Process_Ring3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROTECT_PROCESS_RING3_H
