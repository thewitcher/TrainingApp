#ifndef TRAININGDATA_H
#define TRAININGDATA_H

#include <QString>

#include "Macros.h"

class TrainingData
{
public:
	TrainingData( const QString& a_rData );

	QString GetDate() const;
	QString GetName() const;
	int GetTime() const;
	int GetMood() const;
	int GetAvgPace() const;
	int GetAvgPulse() const;

	void SetName( const QString& a_rName );
	void SetTime( const int a_iTime );
	void SetMood( const int a_iMood );
	void SetAvgPace( const int a_iAvgPace );
	void SetAvgPulse( const int a_iAvgPulse );

	ADD_MEMBER_WITH_GETER_AND_SETTER( Plan, str, QString, "" )
	ADD_MEMBER_WITH_GETER_AND_SETTER( Realistaion, str, QString, "" )
	ADD_MEMBER_WITH_GETER_AND_SETTER( Rest, i, int, 0 )

	ADD_MEMBER_WITH_GETER_AND_SETTER( TrainingEffect, f, float, 0.0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( EnduranceLevel, i, int, 0 )
	ADD_MEMBER_WITH_GETER_AND_SETTER( TrainingType, i, int, 0 )

private:
	const QString m_strData;
	QString m_strName;
	int m_iTime;
	int m_iMood = 0;
	int m_iAvgPace = 0;
	int m_iAvgPulse = 0;
};

#endif // TRAININGDATA_H
