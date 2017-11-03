#ifndef TRAININGDAYDATA_H
#define TRAININGDAYDATA_H

#include<QDate>

class TrainingDayData
{
public:
	TrainingDayData( const QString& a_rDate );
	virtual ~TrainingDayData();

	QString GetDate() const;

	int GetHrRest() const;
	void SetHrRest( int a_iHrRest );

	int GetSleepLevel() const;
	void SetSleepLevel( int a_iSleepLevel );

	int GetWeight() const;
	void SetWeight( int a_iWeight );

	int GetTresholdPace() const;
	void SetTresholdPace( int a_iTresholdPace );

	int GetTresholdPulse() const;
	void SetTresholdPulse( int a_iTresholdPulse );

private:
	const QString m_strTrainingDate;
	int m_iHrRest = 0;
	int m_iSleepLevel = 0;
	int m_iWeight = 0;
	int m_iTresholdPace = 0;
	int m_iTresholdPulse = 0;
};

#endif // TRAININGDAYDATA_H
