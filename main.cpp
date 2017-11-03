#include "MainWindow.h"
#include "DatabaseManager.h"

#include <QApplication>

int main( int a_iArgc, char* a_pArgv[] )
{
	QApplication a( a_iArgc, a_pArgv );

	DatabaseManager::CreateConnection();

	MainWindow w;
	w.showMaximized();

	return a.exec();
}
