#include "TrainingGeneralQuery.h"

#include "DateHelper.h"
#include "CommonQuery.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

TrainingGeneralQuery::TrainingGeneralQuery()
{
	// Nothing
}

QSharedPointer<TrainingGeneralData> TrainingGeneralQuery::Load( const QString& a_rDate ) const
{
	auto pTrainingGeneralData = QSharedPointer<TrainingGeneralData>::create( a_rDate );
	LoadDistanceAndDuration( pTrainingGeneralData );
	LoadAvgPace( pTrainingGeneralData );
	LoadAvgPulse( pTrainingGeneralData );
	LoadTrainingName( pTrainingGeneralData );
	LoadTrainingType( pTrainingGeneralData );

	return pTrainingGeneralData;
}

void TrainingGeneralQuery::LoadDistanceAndDuration( QSharedPointer<TrainingGeneralData> a_pTrainingGeneralData ) const
{
	QSqlQuery query;
	query.prepare( "SELECT SUM(Distance), SUM(Duration) FROM Interval WHERE Date = :Date" );
	query.bindValue( ":Date", a_pTrainingGeneralData->GetDate() );
	if ( !query.exec() )
	{
		qWarning() << QString( "TrainingGeneralQuery: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pTrainingGeneralData->SetDistance( query.value( "SUM(Distance)" ).toInt() );
		a_pTrainingGeneralData->SetDuration( query.value( "SUM(Duration)" ).toInt() );
	}
}

void TrainingGeneralQuery::LoadAvgPace( QSharedPointer<TrainingGeneralData> a_pTrainingGeneralData ) const
{
	a_pTrainingGeneralData->SetAvgPace( CommonQuery::LoadAvgPace( a_pTrainingGeneralData->GetDate() ) );
}

void TrainingGeneralQuery::LoadAvgPulse( QSharedPointer<TrainingGeneralData> a_pTrainingGeneralData ) const
{
	a_pTrainingGeneralData->SetAvgPulse( CommonQuery::LoadAvgPulse( a_pTrainingGeneralData->GetDate() ) );
}

void TrainingGeneralQuery::LoadTrainingName( QSharedPointer<TrainingGeneralData> a_pTrainingGeneralData ) const
{
	QSqlQuery query;
	query.prepare( "SELECT Name FROM Training WHERE Date = :Date" );
	query.bindValue( ":Date", a_pTrainingGeneralData->GetDate() );
	if ( !query.exec() )
	{
		qWarning() << QString( "LoadTrainingName: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pTrainingGeneralData->SetName( query.value( "Name" ).toString() );
	}
}

void TrainingGeneralQuery::LoadTrainingType( QSharedPointer<TrainingGeneralData> a_pTrainingGeneralData ) const
{
	QSqlQuery query;
	query.prepare( "SELECT TrainingType FROM Training WHERE Date = :Date" );
	query.bindValue( ":Date", a_pTrainingGeneralData->GetDate() );
	if ( !query.exec() )
	{
		qWarning() << QString( "LoadTrainingType: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		a_pTrainingGeneralData->SetTrainingType( query.value( "TrainingType" ).toInt() );
	}
}

int TrainingGeneralQuery::GetIntervalCount( const int a_iTrainingId ) const
{
	QSqlQuery query;
	query.prepare( "SELECT COUNT(*) FROM Interval WHERE TrainingId = :TrainingId" );
	query.bindValue( ":TrainingId", a_iTrainingId );
	if ( !query.exec() )
	{
		qWarning() << QString( "TrainingGeneralQuery: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		return query.value( "COUNT(*)" ).toInt();
	}
	return 0;
}
