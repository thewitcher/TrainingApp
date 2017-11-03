#include "IntervalQuery.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "IntervalData.h"

void IntervalQuery::Insert( const QSharedPointer<IntervalData> a_pDataObject )
{
	QSqlQuery query;
	query.prepare(	"INSERT INTO Interval (Date, Calories, Distance, AvgPace, AvgPulse, MinPulse, MaxPulse, Duration, Cadence, StepLength, TimeInFirstZone, TimeInSecondZone, TimeInThirdZone, TimeInFourthZone, TimeInFifthZone) "
					"VALUES (:Date, :Calories, :Distance, :AvgPace, :AvgPulse, :MinPulse, :MaxPulse, :Duration, :Cadence, :StepLength , :TimeInFirstZone, :TimeInSecondZone, :TimeInThirdZone, :TimeInFourthZone, :TimeInFifthZone)" );

	query.bindValue( ":Date", a_pDataObject->GetDate() );
	query.bindValue( ":Calories", a_pDataObject->GetCalories() );
	query.bindValue( ":Distance", a_pDataObject->GetDistance() );
	query.bindValue( ":AvgPace", a_pDataObject->GetAvgPace() );
	query.bindValue( ":AvgPulse", a_pDataObject->GetAvgPulse() );
	query.bindValue( ":MinPulse", a_pDataObject->GetMinPulse() );
	query.bindValue( ":MaxPulse", a_pDataObject->GetMaxPulse() );
	query.bindValue( ":Duration", a_pDataObject->GetDuration() );
	query.bindValue( ":Cadence", a_pDataObject->GetCadence() );
	query.bindValue( ":StepLength", a_pDataObject->GetStepLength() );
	query.bindValue( ":TimeInFirstZone", a_pDataObject->GetTimeInFirstZone() );
	query.bindValue( ":TimeInSecondZone", a_pDataObject->GetTimeInSecondZone() );
	query.bindValue( ":TimeInThirdZone", a_pDataObject->GetTimeInThirdZone() );
	query.bindValue( ":TimeInFourthZone", a_pDataObject->GetTimeInFourthZone() );
	query.bindValue( ":TimeInFifthZone", a_pDataObject->GetTimeInFifthZone() );

	if ( !query.exec() )
	{
		qWarning() << QString( "IntervalQuery: insert query error: " + query.lastError().text() );
	}
}
