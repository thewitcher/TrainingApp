#ifndef TRAININGQUERY_H
#define TRAININGQUERY_H

#include <QSharedPointer>
#include <QString>

#include "TrainingData.h"

class TrainingQuery
{
public:
	QSharedPointer<TrainingData> Load( const QString& a_rDate ) const;

	void InsertOrUpdate( const QSharedPointer<TrainingData> a_pDataObject );

protected:
	bool CheckIfExist( const QSharedPointer<TrainingData> a_pDataObject );
	void Insert( const QSharedPointer<TrainingData> a_pDataObject );
	void Update( const QSharedPointer<TrainingData> a_pDataObject );
};

#endif // TRAININGQUERY_H
