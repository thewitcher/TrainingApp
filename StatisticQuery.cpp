#include "StatisticQuery.h"
#include "DateHelper.h"
#include "Constants.h"

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
		qWarning() << QString( "StatisticQuery: select query error: " + query.lastError().text() );
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
		qWarning() << QString( "StatisticQuery: select query error: " + query.lastError().text() );
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
		qWarning() << QString( "StatisticQuery: select query error: " + query.lastError().text() );
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
		qWarning() << QString( "StatisticQuery: select query error: " + query.lastError().text() );
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
		qWarning() << QString( "StatisticQuery: select query error: " + query.lastError().text() );
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
		qWarning() << QString( "StatisticQuery: select query error: " + query.lastError().text() );
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
		qWarning() << QString( "StatisticQuery: select query error: " + query.lastError().text() );
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
		qWarning() << QString( "StatisticQuery: select query error: " + query.lastError().text() );
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
		qWarning() << QString( "StatisticQuery: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pStatisticData->SetCaloriesInDay( query.value( "SUM(Calories)" ).toInt() );
	}
}

void StatisticQuery::LoadTrainingStressScoreForPulse( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const
{
	QString strQueryString = QString
	(
	"SELECT" \
	" TrainingDay.Date, " \
	" ifnull( ( SELECT SUM(Duration) FROM Interval WHERE Date = TrainingDay.Date ) / 3600.0, 0 ) as Time, " \
	" ifnull( ( CAST( TrainingDay.TresholdPulse as float ) / CAST( Training.AvgPulse as float ) ) * ( CAST( TrainingDay.TresholdPulse as float ) / CAST( Training.AvgPulse as float ) ), 0 )  as IF " \
	" FROM Training, TrainingDay " \
	" WHERE TrainingDay.Date BETWEEN '%1' AND '%1' AND TrainingDay.Date = Training.Date;"
	).arg( a_rDate );

	QSqlQuery query;
	query.prepare( strQueryString );
	if ( !query.exec() )
	{
		qWarning() << QString( "StatisticQuery: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pStatisticData->SetTrainingStressScoreForPulse( query.value( "Time" ).toFloat() * query.value( "IF" ).toFloat() * 100.0 );
	}
}

void StatisticQuery::LoadTrainingStressScoreForPace( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const
{
	QString strQueryString = QString
	(
	"SELECT" \
	" TrainingDay.Date, " \
	" ifnull( ( SELECT SUM(Duration) FROM Interval WHERE Date = TrainingDay.Date ) / 3600.0, 0 ) as Time, " \
	" ifnull( ( CAST( TrainingDay.TresholdPace as float ) / CAST( Training.AvgPace as float ) ) * ( CAST( TrainingDay.TresholdPace as float ) / CAST( Training.AvgPace as float ) ), 0 )  as IF " \
	" FROM Training, TrainingDay " \
	" WHERE TrainingDay.Date BETWEEN '%1' AND '%1' AND TrainingDay.Date = Training.Date;"
	).arg( a_rDate );

	QSqlQuery query;
	query.prepare( strQueryString );
	if ( !query.exec() )
	{
		qWarning() << QString( "StatisticQuery: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pStatisticData->SetTrainingStressScoreForPace( query.value( "Time" ).toFloat() * query.value( "IF" ).toFloat() * 100.0 );
	}
}
