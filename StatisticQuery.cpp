#include "StatisticQuery.h"
#include "DateHelper.h"
#include "Constants.h"

#include "CommonQuery.h"

#include <QDebug>
#include "QSqlQuery"
#include "QSqlError"

StatisticQuery::StatisticQuery()
{
	// Nothing
}

QSharedPointer<StatisticData> StatisticQuery::Load( const QString& a_rDate ) const
{
	QSharedPointer<StatisticData> pStatisticData = QSharedPointer<StatisticData>::create( a_rDate );

	LoadTrainingCountInWeek( a_rDate, pStatisticData );
	LoadTrainingCountInMonth( a_rDate, pStatisticData );
	LoadDistanceInWeek( a_rDate, pStatisticData );
	LoadDistanceInMonth( a_rDate, pStatisticData );
	LoadDurationInWeek( a_rDate, pStatisticData );
	LoadDurationInMonth( a_rDate, pStatisticData );
	LoadCaloriesInWeek( a_rDate, pStatisticData );
	LoadCaloriesInMonth( a_rDate, pStatisticData );
	LoadCaloriesInDay( a_rDate, pStatisticData );

	LoadTrainingStressScoreForPace( a_rDate, pStatisticData );
	LoadTrainingStressScoreForPulse( a_rDate, pStatisticData );

	return pStatisticData;
}

void StatisticQuery::LoadTrainingCountInWeek( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const
{
	QString strQueryString = QString( "SELECT COUNT(*) FROM Training WHERE Date BETWEEN '%1' AND '%2'" )
	.arg( DateHelper::GetDateForFirstDayInWeekForDate( a_rDate ) )
	.arg( DateHelper::GetDateForLastDayInWeekForDate( a_rDate ) );

	QSqlQuery query;
	query.prepare( strQueryString );
	if ( !query.exec() )
	{
		qWarning() << QString( "StatisticQuery::LoadTrainingCountInWeek: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pStatisticData->SetTrainingCountInWeek( query.value( "COUNT(*)" ).toInt() );
	}
}

void StatisticQuery::LoadTrainingCountInMonth( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const
{
	QString strQueryString = QString( "SELECT COUNT(*) FROM Training WHERE Date BETWEEN '%1' AND '%2'" )
	.arg( DateHelper::GetDateForFirstDayInMonthForDate( a_rDate ) )
	.arg( DateHelper::GetDateForLastDayInMonthForDate( a_rDate ) );

	QSqlQuery query;
	query.prepare( strQueryString );
	if ( !query.exec() )
	{
		qWarning() << QString( "StatisticQuery::LoadTrainingCountInMonth: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pStatisticData->SetTrainingCountInMonth( query.value( "COUNT(*)" ).toInt() );
	}
}

void StatisticQuery::LoadDistanceInWeek( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const
{
	QString strQueryString = QString( "SELECT SUM(Distance) FROM Interval WHERE Date BETWEEN '%1' AND '%2'" )
	.arg( DateHelper::GetDateForFirstDayInWeekForDate( a_rDate ) )
	.arg( DateHelper::GetDateForLastDayInWeekForDate( a_rDate ) );

	QSqlQuery query;
	query.prepare( strQueryString );
	if ( !query.exec() )
	{
		qWarning() << QString( "StatisticQuery::LoadDistanceInWeek: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pStatisticData->SetDistanceInWeek( query.value( "SUM(Distance)" ).toInt() );
	}
}

void StatisticQuery::LoadDistanceInMonth( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const
{
	QString strQueryString = QString( "SELECT SUM(Distance) FROM Interval WHERE Date BETWEEN '%1' AND '%2'" )
	.arg( DateHelper::GetDateForFirstDayInMonthForDate( a_rDate ) )
	.arg( DateHelper::GetDateForLastDayInMonthForDate( a_rDate ) );

	QSqlQuery query;
	query.prepare( strQueryString );
	if ( !query.exec() )
	{
		qWarning() << QString( "StatisticQuery::LoadDistanceInMonth: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pStatisticData->SetDistanceInMonth( query.value( "SUM(Distance)" ).toInt() );
	}
}

void StatisticQuery::LoadDurationInWeek( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const
{
	QString strQueryString = QString( "SELECT SUM(Duration) FROM Interval WHERE Date BETWEEN '%1' AND '%2'" )
	.arg( DateHelper::GetDateForFirstDayInWeekForDate( a_rDate ) )
	.arg( DateHelper::GetDateForLastDayInWeekForDate( a_rDate ) );

	QSqlQuery query;
	query.prepare( strQueryString );
	if ( !query.exec() )
	{
		qWarning() << QString( "StatisticQuery::LoadDurationInWeek: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pStatisticData->SetWholeDurationInWeek( query.value( "SUM(Duration)" ).toInt() );
	}
}

void StatisticQuery::LoadDurationInMonth( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const
{
	QString strQueryString = QString( "SELECT SUM(Duration) FROM Interval WHERE Date BETWEEN '%1' AND '%2'" )
	.arg( DateHelper::GetDateForFirstDayInMonthForDate( a_rDate ) )
	.arg( DateHelper::GetDateForLastDayInMonthForDate( a_rDate ) );

	QSqlQuery query;
	query.prepare( strQueryString );
	if ( !query.exec() )
	{
		qWarning() << QString( "StatisticQuery::LoadDurationInMonth: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pStatisticData->SetWholeDurationInMonth( query.value( "SUM(Duration)" ).toInt() );
	}
}

void StatisticQuery::LoadCaloriesInWeek( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const
{
	QString strQueryString = QString( "SELECT SUM(Calories) FROM Interval WHERE Date BETWEEN '%1' AND '%2'" )
	.arg( DateHelper::GetDateForFirstDayInWeekForDate( a_rDate ) )
	.arg( DateHelper::GetDateForLastDayInWeekForDate( a_rDate ) );

	QSqlQuery query;
	query.prepare( strQueryString );
	if ( !query.exec() )
	{
		qWarning() << QString( "StatisticQuery::LoadCaloriesInWeek: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pStatisticData->SetCaloriesInWeek( query.value( "SUM(Calories)" ).toInt() );
	}
}

void StatisticQuery::LoadCaloriesInMonth( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const
{
	QString strQueryString = QString( "SELECT SUM(Calories) FROM Interval WHERE Date BETWEEN '%1' AND '%2'" )
	.arg( DateHelper::GetDateForFirstDayInMonthForDate( a_rDate ) )
	.arg( DateHelper::GetDateForLastDayInMonthForDate( a_rDate ) );

	QSqlQuery query;
	query.prepare( strQueryString );
	if ( !query.exec() )
	{
		qWarning() << QString( "StatisticQuery::LoadCaloriesInMonth: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pStatisticData->SetCaloriesInMonth( query.value( "SUM(Calories)" ).toInt() );
	}
}

void StatisticQuery::LoadCaloriesInDay( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const
{
	QSqlQuery query;
	query.prepare( "SELECT SUM(Calories) FROM Interval WHERE Date = :Date" );
	query.bindValue( ":Date", a_rDate );
	if ( !query.exec() )
	{
		qWarning() << QString( "StatisticQuery::LoadCaloriesInDay: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pStatisticData->SetCaloriesInDay( query.value( "SUM(Calories)" ).toInt() );
	}
}

void StatisticQuery::LoadTrainingStressScoreForPulse( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const
{
	int iAvgPulse = CommonQuery::LoadAvgPulse( a_rDate );

	QSqlQuery query;
	query.prepare
	(
		"SELECT TrainingDay.Date, "
		"( SELECT SUM(Duration) FROM Interval WHERE Date = TrainingDay.Date ) / 3600.0 as Time, "
		" TrainingDay.TresholdPulse as TP"
		" FROM Training, TrainingDay "
		" WHERE TrainingDay.Date = :Date AND TrainingDay.Date = Training.Date;"
	);
	query.bindValue( ":Date", a_rDate );

	if ( !query.exec() )
	{
		qWarning() << QString( "StatisticQuery::LoadTrainingStressScoreForPulse: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		int iTresholdPulse = query.value( "TP" ).toFloat();

		double IF = 0.0;

		if ( iAvgPulse != 0 )
		{
			IF = double( iTresholdPulse ) / double( iAvgPulse );
		}
		a_pStatisticData->SetTrainingStressScoreForPulse( query.value( "Time" ).toFloat() * IF * IF * 100.0 );
	}
}

void StatisticQuery::LoadTrainingStressScoreForPace( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const
{
	int iAvgPace = CommonQuery::LoadAvgPace( a_rDate );

	QSqlQuery query;
	query.prepare
	(
		"SELECT TrainingDay.Date, "
		"( SELECT SUM(Duration) FROM Interval WHERE Date = TrainingDay.Date ) / 3600.0 as Time, "
		" TrainingDay.TresholdPace as TP"
		" FROM Training, TrainingDay "
		" WHERE TrainingDay.Date = :Date AND TrainingDay.Date = Training.Date;"
	);
	query.bindValue( ":Date", a_rDate );

	if ( !query.exec() )
	{
		qWarning() << QString( "StatisticQuery::LoadTrainingStressScoreForPace: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		int iTresholdPace = query.value( "TP" ).toFloat();

		double IF = 0.0;
		if ( iAvgPace != 0 )
		{
			IF = double( iTresholdPace ) / double( iAvgPace );
		}

		a_pStatisticData->SetTrainingStressScoreForPulse( query.value( "Time" ).toFloat() * IF * IF * 100.0 );
	}
}
