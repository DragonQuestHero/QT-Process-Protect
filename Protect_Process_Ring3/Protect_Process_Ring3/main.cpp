#include "Protect_Process_Ring3.h"
#include <QtWidgets/QApplication>

#ifdef NDEBUG
#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif // DEBUG

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Protect_Process_Ring3 w;
	w.show();
	return a.exec();
}
