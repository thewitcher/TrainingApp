#include "TrainingData.h"

TrainingData::TrainingData( const QString& a_rData )
	: m_strData( a_rData )
{
	// Nothing
}

QString TrainingData::GetDate() const
{
	return m_strData;
}

QString TrainingData::GetName() const
{
	return m_strName;
}

int TrainingData::GetTime() const
{
	return m_iTime;
}

int TrainingData::GetMood() const
{
	return m_iMood;
}

int TrainingData::GetAvgPace() const
{
	return m_iAvgPace;
}

int TrainingData::GetAvgPulse() const
{
	return m_iAvgPulse;
}

void TrainingData::SetName( const QString& a_rName )
{
	m_strName = a_rName;
}

void TrainingData::SetTime( const int a_iTime )
{
	m_iTime = a_iTime;
}

void TrainingData::SetMood( const int a_iMood )
{
	m_iMood = a_iMood;
}

void TrainingData::SetAvgPace( const int a_iAvgPace )
{
	m_iAvgPace = a_iAvgPace;
}

void TrainingData::SetAvgPulse( const int a_iAvgPulse )
{
	m_iAvgPulse = a_iAvgPulse;
}
