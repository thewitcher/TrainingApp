#ifndef STATISTICDATA_H
#define STATISTICDATA_H

#include <QString>

#include "Macros.h"

class StatisticData
{
public:
	StatisticData( const QString& a_rData );

	ADD_MEMBER_WITH_GETER_AND_SETTER( TrainingCountInWeek, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( DistanceInWeek, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( WholeDurationInWeek, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( CaloriesInWeek, i, int, 0 )

	ADD_MEMBER_WITH_GETER_AND_SETTER( TrainingCountInMonth, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( DistanceInMonth, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( WholeDurationInMonth, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( CaloriesInMonth, i, int, 0 )

	ADD_MEMBER_WITH_GETER_AND_SETTER( CaloriesInDay, i, int, 0 )

	ADD_MEMBER_WITH_GETER_AND_SETTER( TrainingStressScoreForPace, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( TrainingStressScoreForPulse, i, int, 0 )

private:
	const QString m_strDate;
};

#endif // STATISTICDATA_H
