#include "TrainingGeneralData.h"

TrainingGeneralData::TrainingGeneralData( const QString& a_rDate )
	: m_strDate( a_rDate )
{
	// Nothing
}

QString TrainingGeneralData::GetDate() const
{
	return m_strDate;
}

int TrainingGeneralData::GetDistance() const
{
	return m_iDistance;
}

void TrainingGeneralData::SetDistance( const int a_iDistance )
{
	m_iDistance = a_iDistance;
}

int TrainingGeneralData::GetDuration() const
{
	return m_iDuration;
}

void TrainingGeneralData::SetDuration( const int a_iDuration )
{
	m_iDuration = a_iDuration;
}

int TrainingGeneralData::GetAvgPulse() const
{
	return m_iAvgPulse;
}

void TrainingGeneralData::SetAvgPulse( const int a_iAvgPulse )
{
	m_iAvgPulse = a_iAvgPulse;
}

int TrainingGeneralData::GetAvgPace() const
{
	return m_iAvgPace;
}

void TrainingGeneralData::SetAvgPace( const int a_iAvgPace )
{
	m_iAvgPace = a_iAvgPace;
}

QString TrainingGeneralData::GetName() const
{
	return m_strName;
}

void TrainingGeneralData::SetName( const QString& a_strName )
{
	m_strName = a_strName;
}
