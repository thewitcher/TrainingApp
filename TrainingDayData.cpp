#include "TrainingDayData.h"
#include <QDebug>

TrainingDayData::TrainingDayData( const QString &a_rDate )
	: m_strTrainingDate( a_rDate )
{
	// Nothing
}

TrainingDayData::~TrainingDayData()
{
	// Nothing
}
QString TrainingDayData::GetDate() const
{
	return m_strTrainingDate;
}

int TrainingDayData::GetHrRest() const
{
	return m_iHrRest;
}

void TrainingDayData::SetHrRest( int a_iHrRest )
{
	m_iHrRest = a_iHrRest;
}

int TrainingDayData::GetSleepLevel() const
{
	return m_iSleepLevel;
}

void TrainingDayData::SetSleepLevel( int a_iSleepLevel )
{
	m_iSleepLevel = a_iSleepLevel;
}

int TrainingDayData::GetWeight() const
{
	return m_iWeight;
}

void TrainingDayData::SetWeight( int a_iWeight )
{
	m_iWeight = a_iWeight;
}

int TrainingDayData::GetTresholdPace() const
{
	return m_iTresholdPace;
}

void TrainingDayData::SetTresholdPace( int a_iTresholdPace )
{
	m_iTresholdPace = a_iTresholdPace;
}

int TrainingDayData::GetTresholdPulse() const
{
	return m_iTresholdPulse;
}

void TrainingDayData::SetTresholdPulse( int a_iTresholdPulse )
{
	m_iTresholdPulse = a_iTresholdPulse;
}
