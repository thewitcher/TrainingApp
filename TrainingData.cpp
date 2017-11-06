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
