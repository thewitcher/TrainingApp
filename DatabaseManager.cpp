#include "DatabaseManager.h"

#include <QSqlDatabase>
#include <QDebug>
void DatabaseManager::CreateConnection()
{
	QSqlDatabase database = QSqlDatabase::addDatabase( "QSQLITE" );
	database.setDatabaseName( "./trainings.sqlite" );
	if ( !database.open() )
	{
		qWarning() << "Database cannot be opened";
	}
}
