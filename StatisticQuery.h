#ifndef STATISTICQUERY_H
#define STATISTICQUERY_H

#include "StatisticData.h"

#include <QString>
#include <QSharedPointer>

class StatisticQuery
{
public:
	StatisticQuery();

	QSharedPointer<StatisticData> Load( const QString& a_rDate ) const;

private:
	void LoadTrainingCountInWeek( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const;
	void LoadTrainingCountInMonth( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const;
	void LoadDistanceInWeek( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const;
	void LoadDistanceInMonth( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const;
	void LoadDurationInWeek( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const;
	void LoadDurationInMonth( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const;
	void LoadCaloriesInWeek( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const;
	void LoadCaloriesInMonth( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const;
	void LoadCaloriesInDay( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const;

	void LoadTrainingStressScoreForPulse( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const;
	void LoadTrainingStressScoreForPace( const QString& a_rDate, QSharedPointer<StatisticData> a_pStatisticData ) const;
};

#endif // STATISTICQUERY_H
