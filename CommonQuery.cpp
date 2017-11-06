#include "CommonQuery.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "DateHelper.h"

int CommonQuery::LoadAvgPulse( const QString& a_rDate )
{
	QSqlQuery query;
	query.prepare( "SELECT "
					"SUM ( "
						"( CAST( Duration as real ) / CAST( "
							"( SELECT SUM(Duration) FROM Interval WHERE Date = :Date ) as real ) ) "
					"* CAST( AvgPulse as real )"
				   " )"
				   " as AvgPulse "
				   "FROM Interval "
				   "WHERE Date = :Date" );
	query.bindValue( ":Date", a_rDate );
	if ( !query.exec() )
	{
		qWarning() << QString( "LoadAvgIfNeeded: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		return  query.value( "AvgPulse" ).toInt();
	}

	return 0;
}

int CommonQuery::LoadAvgPace( const QString& a_rDate )
{
	QSqlQuery query;
	query.prepare( "SELECT ( CAST ( SUM(Duration) as real ) / CAST( SUM(Distance) as real ) ) * 16.66666667 as DecPace "
				   "FROM Interval "
				   "WHERE Date = :Date GROUP BY Date" );
	query.bindValue( ":Date", a_rDate );
	if ( !query.exec() )
	{
		qWarning() << QString( "LoadAvgIfNeeded: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		double fPaceInDec = query.value( "DecPace" ).toFloat();
		return DateHelper::GetSecondsFromDecimalValue( fPaceInDec );
	}

	return 0;
}
