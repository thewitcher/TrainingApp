#ifndef TRAININGGENERALDATA_H
#define TRAININGGENERALDATA_H

#include <QDate>

#include "Macros.h"

class TrainingGeneralData
{
public:
	TrainingGeneralData( const QString& a_rDate );

	QString GetDate() const;

	int GetDistance() const;
	void SetDistance( const int a_iDistance );

	int GetDuration() const;
	void SetDuration( const int a_iDuration );

	int GetAvgPulse() const;
	void SetAvgPulse( const int a_iAvgPulse );

	int GetAvgPace() const;
	void SetAvgPace( const int a_iAvgPace );

	QString GetName() const;
	void SetName( const QString& a_strName );

	ADD_MEMBER_WITH_GETER_AND_SETTER( TrainingType, i, int, 0 )

private:
	const QString m_strDate;
	int m_iDistance = 0;
	int m_iDuration = 0;
	int m_iAvgPulse = 0;
	int m_iAvgPace = 0;
	QString m_strName = "";
};

#endif // TRAININGGENERALDATA_H
