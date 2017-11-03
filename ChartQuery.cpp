#include "ChartQuery.h"

#include "Constants.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

QVector<QPointF> ChartQuery::GetDataForAvgPulse()
{
	QSqlQuery query;
	query.prepare( "SELECT Date, AvgPulse FROM Training ORDER BY Date" );
	if ( !query.exec() )
	{
		qWarning() << QString( "ChartQuery: select query error: " + query.lastError().text() );
	}

	QVector<QPointF> aData;
	while ( query.next() )
	{
		int iYValue = query.value( "AvgPulse" ).toInt();
		if ( CanTakeToChart( iYValue ) )
		{
			qint64 iDateInMSec = QDateTime::fromString( query.value( "Date" ).toString(), Constants::DATA_FORMAT ).toMSecsSinceEpoch();
			aData.append( QPointF( iDateInMSec, iYValue ) );
		}
	}

	return aData;
}

QVector<QPointF> ChartQuery::GetDataForAvgPace()
{
	QSqlQuery query;
	query.prepare( "SELECT Date, AvgPace FROM Training ORDER BY Date" );
	if ( !query.exec() )
	{
		qWarning() << QString( "ChartQuery: select query error: " + query.lastError().text() );
	}

	QVector<QPointF> aData;
	while ( query.next() )
	{
		int iYValue = query.value( "AvgPace" ).toInt();
		if ( CanTakeToChart( iYValue ) )
		{
			qint64 iDateInMSec = QDateTime::fromString( query.value( "Date" ).toString(), Constants::DATA_FORMAT ).toMSecsSinceEpoch();
			aData.append( QPointF( iDateInMSec, iYValue ) );
		}
	}

	return aData;
}

QVector<QPointF> ChartQuery::GetDataForHrRest()
{
	QSqlQuery query;
	query.prepare( "SELECT Date, HrRest FROM TrainingDay ORDER BY Date" );
	if ( !query.exec() )
	{
		qWarning() << QString( "ChartQuery: select query error: " + query.lastError().text() );
	}

	QVector<QPointF> aData;
	while ( query.next() )
	{
		int iYValue = query.value( "HrRest" ).toInt();
		if ( CanTakeToChart( iYValue ) )
		{
			qint64 iDateInMSec = QDateTime::fromString( query.value( "Date" ).toString(), Constants::DATA_FORMAT ).toMSecsSinceEpoch();
			aData.append( QPointF( iDateInMSec, iYValue ) );
		}
	}

	return aData;
}

bool ChartQuery::CanTakeToChart( const int a_iValueToCheck )
{
	return a_iValueToCheck > 0;
}
