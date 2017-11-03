#ifndef TRAININGGENERALQUERY_H
#define TRAININGGENERALQUERY_H

#include "TrainingGeneralData.h"

#include <QSharedPointer>

class TrainingGeneralQuery
{
public:
	TrainingGeneralQuery();

	QSharedPointer<TrainingGeneralData> Load( const QString& a_rDate ) const;

protected:
	void LoadDistanceAndDuration( QSharedPointer<TrainingGeneralData> a_pTrainingGeneralData ) const;
	void LoadAvgPulseAndPace( QSharedPointer<TrainingGeneralData> a_pTrainingGeneralData ) const;
	void LoadTrainingName( QSharedPointer<TrainingGeneralData> a_pTrainingGeneralData ) const;
	void LoadTrainingType( QSharedPointer<TrainingGeneralData> a_pTrainingGeneralData ) const;
	int GetIntervalCount( const int a_iTrainingId ) const;
};

#endif // TRAININGGENERALQUERY_H
