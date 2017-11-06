#include "ChartQuery.h"

#include "StatisticQuery.h"
#include "StatisticData.h"
#include "Constants.h"
#include "CommonQuery.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

QVector<QPointF> ChartQuery::GetDataForAvgPulse()
{
	QSqlQuery query;
	query.prepare( "SELECT Date FROM Training ORDER BY Date" );
	if ( !query.exec() )
	{
		qWarning() << QString( "ChartQuery: select query error: " + query.lastError().text() );
	}

	QVector<QPointF> aData;
	while ( query.next() )
	{
		QString strDate = query.value( "Date" ).toString();

		int iYValue = CommonQuery::LoadAvgPulse( strDate );
		qDebug() << iYValue;
		if ( CanTakeToChart( iYValue ) )
		{
			qint64 iDateInMSec = QDateTime::fromString( strDate, Constants::DATA_FORMAT ).toMSecsSinceEpoch();
			aData.append( QPointF( iDateInMSec, iYValue ) );
		}
	}

	return aData;
}

QVector<QPointF> ChartQuery::GetDataForAvgPace()
{
	QSqlQuery query;
	query.prepare( "SELECT Date FROM Training ORDER BY Date" );
	if ( !query.exec() )
	{
		qWarning() << QString( "ChartQuery: select query error: " + query.lastError().text() );
	}

	QVector<QPointF> aData;
	while ( query.next() )
	{
		QString strDate = query.value( "Date" ).toString();

		int iYValue = CommonQuery::LoadAvgPace( strDate );
		if ( CanTakeToChart( iYValue ) )
		{
			qint64 iDateInMSec = QDateTime::fromString( strDate, Constants::DATA_FORMAT ).toMSecsSinceEpoch();
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

QVector<QPointF> ChartQuery::GetDataForRest()
{
	QSqlQuery query;
	query.prepare( "SELECT Date, Rest FROM Training ORDER BY Date" );
	if ( !query.exec() )
	{
		qWarning() << QString( "ChartQuery: select query error: " + query.lastError().text() );
	}

	QVector<QPointF> aData;
	while ( query.next() )
	{
		int iYValue = query.value( "Rest" ).toInt();
		if ( CanTakeToChart( iYValue ) )
		{
			qint64 iDateInMSec = QDateTime::fromString( query.value( "Date" ).toString(), Constants::DATA_FORMAT ).toMSecsSinceEpoch();
			aData.append( QPointF( iDateInMSec, iYValue ) );
		}
	}

	return aData;
}

QVector<QPointF> ChartQuery::GetDataForDuration()
{
	QSqlQuery query;
	query.prepare( "SELECT Date, SUM(Duration) FROM Interval GROUP BY Date ORDER BY Date" );
	if ( !query.exec() )
	{
		qWarning() << QString( "ChartQuery: select query error: " + query.lastError().text() );
	}

	QVector<QPointF> aData;
	while ( query.next() )
	{
		int iYValue = query.value( "SUM(Duration)" ).toInt();
		if ( CanTakeToChart( iYValue ) )
		{
			qint64 iDateInMSec = QDateTime::fromString( query.value( "Date" ).toString(), Constants::DATA_FORMAT ).toMSecsSinceEpoch();
			aData.append( QPointF( iDateInMSec, iYValue / 60.0 ) );
		}
	}

	return aData;
}

QVector<QPointF> ChartQuery::GetDataForCalories()
{
	QSqlQuery query;
	query.prepare( "SELECT Date, SUM(Calories) FROM Interval GROUP BY Date ORDER BY Date" );
	if ( !query.exec() )
	{
		qWarning() << QString( "ChartQuery: select query error: " + query.lastError().text() );
	}

	QVector<QPointF> aData;
	while ( query.next() )
	{
		int iYValue = query.value( "SUM(Calories)" ).toInt();
		if ( CanTakeToChart( iYValue ) )
		{
			qint64 iDateInMSec = QDateTime::fromString( query.value( "Date" ).toString(), Constants::DATA_FORMAT ).toMSecsSinceEpoch();
			aData.append( QPointF( iDateInMSec, iYValue ) );
		}
	}

	return aData;
}

QVector<QPointF> ChartQuery::GetDataForPaceTSS()
{
	QSqlQuery query;
	query.prepare( "SELECT Date FROM Training ORDER BY Date" );
	if ( !query.exec() )
	{
		qWarning() << QString( "ChartQuery: select query error: " + query.lastError().text() );
	}

	StatisticQuery statQuery;

	QVector<QPointF> aData;
	while ( query.next() )
	{
		QString strDate = query.value( "Date" ).toString();

		QSharedPointer<StatisticData> pStatData = statQuery.Load( strDate );
		int iTSS = pStatData->GetTrainingStressScoreForPace();

		if ( CanTakeToChart( iTSS ) )
		{
			qint64 iDateInMSec = QDateTime::fromString( strDate, Constants::DATA_FORMAT ).toMSecsSinceEpoch();
			aData.append( QPointF( iDateInMSec, iTSS ) );
		}
	}

	return aData;
}

QVector<QPointF> ChartQuery::GetDataForPulseTSS()
{
	QSqlQuery query;
	query.prepare( "SELECT Date FROM Training ORDER BY Date" );
	if ( !query.exec() )
	{
		qWarning() << QString( "ChartQuery: select query error: " + query.lastError().text() );
	}

	StatisticQuery statQuery;

	QVector<QPointF> aData;
	while ( query.next() )
	{
		QString strDate = query.value( "Date" ).toString();

		QSharedPointer<StatisticData> pStatData = statQuery.Load( strDate );
		int iTSS = pStatData->GetTrainingStressScoreForPulse();

		if ( CanTakeToChart( iTSS ) )
		{
			qint64 iDateInMSec = QDateTime::fromString( strDate, Constants::DATA_FORMAT ).toMSecsSinceEpoch();
			aData.append( QPointF( iDateInMSec, iTSS ) );
		}
	}

	return aData;
}

bool ChartQuery::CanTakeToChart( const int a_iValueToCheck )
{
	return a_iValueToCheck > 0;
}
