#include "TrainingDayQuery.h"

#include "TrainingDayData.h"

#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

TrainingDayQuery::TrainingDayQuery()
{
	// Nothing
}

void TrainingDayQuery::AddEmptyTrainigDay( const QString& a_rDate )
{
	QSharedPointer<TrainingDayData> pTrainingDayData = QSharedPointer<TrainingDayData>::create( a_rDate );
	InsertWithCheck( pTrainingDayData );
}

void TrainingDayQuery::InsertWithCheck( const QSharedPointer<TrainingDayData> a_pDataObject )
{
	if ( !CheckIfExist( a_pDataObject ) )
	{
		Insert( a_pDataObject );
	}
}

void TrainingDayQuery::InsertOrUpdate( const QSharedPointer<TrainingDayData> a_pDataObject )
{
	if ( CheckIfExist( a_pDataObject ) )
	{
		Update( a_pDataObject );
	}
	else
	{
		Insert( a_pDataObject );
	}
}

QSharedPointer<TrainingDayData> TrainingDayQuery::Load( const QString& a_rDate ) const
{
	QSharedPointer<TrainingDayData> pTrainingDayData = QSharedPointer<TrainingDayData>::create( a_rDate );

	QSqlQuery query;
	query.prepare( "SELECT * FROM TrainingDay WHERE Date = :Date" );
	query.bindValue( ":Date", a_rDate );
	if ( !query.exec() )
	{
		qWarning() << QString( "TrainingDayQuery: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		pTrainingDayData->SetHrRest( query.value( "HrRest" ).toInt() );
		pTrainingDayData->SetSleepLevel( query.value( "SleepLevel" ).toInt() );
		pTrainingDayData->SetTresholdPace( query.value( "TresholdPace" ).toInt() );
		pTrainingDayData->SetTresholdPulse( query.value( "TresholdPulse" ).toInt() );
		pTrainingDayData->SetWeight( query.value( "Weight" ).toInt() );
	}

	return pTrainingDayData;
}

bool TrainingDayQuery::CheckIfExist( const QSharedPointer<TrainingDayData> a_pDataObject )
{
	QSqlQuery query;
	query.prepare( "SELECT COUNT(*) FROM TrainingDay WHERE Date = :Date" );
	query.bindValue( ":Date", a_pDataObject->GetDate() );
	if ( !query.exec() )
	{
		qWarning() << QString( "TrainingDayQuery: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		return ( query.value( "COUNT(*)" ).toInt() > 0 );
	}

	return false;
}

void TrainingDayQuery::Insert( const QSharedPointer<TrainingDayData> a_pDataObject )
{
	QSqlQuery query;
	query.prepare(	"INSERT INTO TrainingDay (Date, HrRest, SleepLevel, Weight, TresholdPace, TresholdPulse) "
					"VALUES (:Date, :HrRest, :SleepLevel, :Weight, :TresholdPace, :TresholdPulse)" );
	query.bindValue( ":Date", a_pDataObject->GetDate() );
	query.bindValue( ":HrRest", a_pDataObject->GetHrRest() );
	query.bindValue( ":SleepLevel", a_pDataObject->GetSleepLevel() );
	query.bindValue( ":Weight", a_pDataObject->GetWeight() );
	query.bindValue( ":TresholdPace", a_pDataObject->GetTresholdPace() );
	query.bindValue( ":TresholdPulse", a_pDataObject->GetTresholdPulse() );

	if ( !query.exec() )
	{
		qWarning() << QString( "insert query error: " + query.lastError().text() );
	}
}

void TrainingDayQuery::Update( const QSharedPointer<TrainingDayData> a_pDataObject )
{
	QSqlQuery query;
	query.prepare(	"UPDATE TrainingDay "
					"SET HrRest = :HrRest, SleepLevel = :SleepLevel, "
					"Weight = :Weight, TresholdPace = :TresholdPace, TresholdPulse = :TresholdPulse "
					"WHERE Date = :Date" );
	query.bindValue( ":Date", a_pDataObject->GetDate() );
	query.bindValue( ":HrRest", a_pDataObject->GetHrRest() );
	query.bindValue( ":SleepLevel", a_pDataObject->GetSleepLevel() );
	query.bindValue( ":Weight", a_pDataObject->GetWeight() );
	query.bindValue( ":TresholdPace", a_pDataObject->GetTresholdPace() );
	query.bindValue( ":TresholdPulse", a_pDataObject->GetTresholdPulse() );

	if ( !query.exec() )
	{
		qWarning() << QString( "update query error: " + query.lastError().text() );
	}
}
