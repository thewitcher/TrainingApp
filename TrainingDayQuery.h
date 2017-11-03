#ifndef TRAININGDAYQUERY_H
#define TRAININGDAYQUERY_H

#include <QString>
#include <QSharedPointer>

#include "TrainingDayData.h"

class TrainingDayQuery
{
public:
	TrainingDayQuery();

	void AddEmptyTrainigDay( const QString& a_rDate );
	QSharedPointer<TrainingDayData> Load( const QString& a_rDate ) const;
	void Save( QSharedPointer<TrainingDayData> a_pTrainingDayData );

	void InsertWithCheck( const QSharedPointer<TrainingDayData> a_pDataObject );
	void InsertOrUpdate( const QSharedPointer<TrainingDayData> a_pDataObject );

protected:
	void Insert( const QSharedPointer<TrainingDayData> a_pDataObject );
	void Update( const QSharedPointer<TrainingDayData> a_pDataObject );
	bool CheckIfExist( const QSharedPointer<TrainingDayData> a_pDataObject );
};

#endif // TRAININGDAYQUERY_H
