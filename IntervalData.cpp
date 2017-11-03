#include "IntervalData.h"

IntervalData::IntervalData( const QString& a_rData )
	: m_strData( a_rData )
{
	// Nothing
}

QString IntervalData::GetDate() const
{
	return m_strData;
}
