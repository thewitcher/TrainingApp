#ifndef INTERVALDATA_H
#define INTERVALDATA_H

#include <QString>

#include "Macros.h"

class IntervalData
{
public:
	IntervalData( const QString& a_rData );

	QString GetDate() const;

private:
	const QString m_strData;

	ADD_MEMBER_WITH_GETER_AND_SETTER( Calories, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( Distance, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( AvgPulse, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( MinPulse, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( MaxPulse, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( Duration, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( Cadence, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( StepLength, d, double, 0.0 )

	ADD_MEMBER_WITH_GETER_AND_SETTER( AvgPace, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( TimeInFirstZone, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( TimeInSecondZone, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( TimeInThirdZone, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( TimeInFourthZone, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( TimeInFifthZone, i, int, 0 )
};

#endif // INTERVALDATA_H
