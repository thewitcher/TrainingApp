#include "TrainingQuery.h"

#include "TrainingData.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

QSharedPointer<TrainingData> TrainingQuery::Load( const QString& a_rDate ) const
{
	QSharedPointer<TrainingData> pTrainingData = QSharedPointer<TrainingData>::create( a_rDate );

	QSqlQuery query;
	query.prepare( "SELECT * FROM Training WHERE Date = :Date" );
	query.bindValue( ":Date", a_rDate );
	if ( !query.exec() )
	{
		qWarning() << QString( "TrainingQuery: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		pTrainingData->SetAvgPace( query.value( "AvgPace" ).toInt() );
		pTrainingData->SetAvgPulse( query.value( "AvgPulse" ).toInt() );
		pTrainingData->SetMood( query.value( "Mood" ).toInt() );
		pTrainingData->SetName( query.value( "Name" ).toString() );
		pTrainingData->SetTime( query.value( "Time" ).toInt() );
		pTrainingData->SetRealistaion( query.value( "Realisation" ).toString() );
		pTrainingData->SetPlan( query.value( "Plan" ).toString() );
		pTrainingData->SetRest( query.value( "Rest" ).toInt() );
		pTrainingData->SetTrainingEffect( query.value( "TrainingEffect" ).toFloat() );
		pTrainingData->SetEnduranceLevel( query.value( "EnduranceLevel" ).toInt() );
		pTrainingData->SetTrainingType( query.value( "TrainingType" ).toInt() );
	}

	return pTrainingData;
}

bool TrainingQuery::CheckIfExist( const QSharedPointer<TrainingData> a_pDataObject )
{
	QSqlQuery query;
	query.prepare( "SELECT COUNT(*) FROM Training WHERE Date = :Date" );
	query.bindValue( ":Date", a_pDataObject->GetDate() );
	if ( !query.exec() )
	{
		qWarning() << QString( "TrainingQuery: select query error: " + query.lastError().text() );
	}

	if ( query.next() )
	{
		return ( query.value( "COUNT(*)" ).toInt() > 0 );
	}

	return false;
}

void TrainingQuery::Insert( const QSharedPointer<TrainingData> a_pDataObject )
{
	QSqlQuery query;
	query.prepare(	"INSERT INTO Training (Date, Name, Mood, Time, AvgPace, AvgPulse, Realisation, Plan, Rest, "
					"TrainingEffect, EnduranceLevel, TrainingType) "
					"VALUES (:Date, :Name, :Mood, :Time, :AvgPace, :AvgPulse, :Realisation, :Plan, :Rest, "
					":TrainingEffect, :EnduranceLevel, :TrainingType)" );
	query.bindValue( ":Date", a_pDataObject->GetDate() );
	query.bindValue( ":Name", a_pDataObject->GetName() );
	query.bindValue( ":Mood", a_pDataObject->GetMood() );
	query.bindValue( ":Time", a_pDataObject->GetTime() );
	query.bindValue( ":AvgPace", a_pDataObject->GetAvgPace() );
	query.bindValue( ":AvgPulse", a_pDataObject->GetAvgPulse() );
	query.bindValue( ":Realisation", a_pDataObject->GetRealistaion() );
	query.bindValue( ":Plan", a_pDataObject->GetPlan() );
	query.bindValue( ":Rest", a_pDataObject->GetRest() );
	query.bindValue( ":TrainingEffect", a_pDataObject->GetTrainingEffect() );
	query.bindValue( ":EnduranceLevel", a_pDataObject->GetEnduranceLevel() );
	query.bindValue( ":TrainingType", a_pDataObject->GetTrainingType() );

	if ( !query.exec() )
	{
		qWarning() << QString( "TrainingQuery: insert query error: " + query.lastError().text() );
	}
}

void TrainingQuery::Update( const QSharedPointer<TrainingData> a_pDataObject )
{
	QSqlQuery query;
	query.prepare(	"UPDATE Training "
					"SET Name = :Name, Mood = :Mood, TrainingEffect = :TrainingEffect, EnduranceLevel = :EnduranceLevel, "
					"TrainingType = :TrainingType, Time = :Time, AvgPace = :AvgPace, AvgPulse = :AvgPulse, "
					"Realisation = :Realisation, Plan = :Plan, Rest = :Rest "
					"WHERE Date = :Date" );
	query.bindValue( ":Date", a_pDataObject->GetDate() );
	query.bindValue( ":Name", a_pDataObject->GetName() );
	query.bindValue( ":Mood", a_pDataObject->GetMood() );
	query.bindValue( ":Time", a_pDataObject->GetTime() );
	query.bindValue( ":AvgPace", a_pDataObject->GetAvgPace() );
	query.bindValue( ":AvgPulse", a_pDataObject->GetAvgPulse() );
	query.bindValue( ":Realisation", a_pDataObject->GetRealistaion() );
	query.bindValue( ":Plan", a_pDataObject->GetPlan() );
	query.bindValue( ":Rest", a_pDataObject->GetRest() );
	query.bindValue( ":TrainingEffect", a_pDataObject->GetTrainingEffect() );
	query.bindValue( ":EnduranceLevel", a_pDataObject->GetEnduranceLevel() );
	query.bindValue( ":TrainingType", a_pDataObject->GetTrainingType() );

	if ( !query.exec() )
	{
		qWarning() << QString( "update query error: " + query.lastError().text() );
	}
}

void TrainingQuery::InsertOrUpdate( const QSharedPointer<TrainingData> a_pDataObject )
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
