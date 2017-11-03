#include "DateHelper.h"
#include "Constants.h"

#include <QDebug>

bool DateHelper::IsBefore( const QDate& a_rStartDate, const QDate& a_rEndDate )
{
	return ( a_rStartDate.daysTo( a_rEndDate ) < 0 );
}

QDate DateHelper::GetDateForFirstDayInWeekForDate( const QDate& a_rDate )
{
	return a_rDate.addDays( 1 - a_rDate.dayOfWeek() );
}

QDate DateHelper::GetDateForLastDayInWeekForDate( const QDate &a_rDate )
{
	return a_rDate.addDays( Constants::DAYS_IN_WEEK - a_rDate.dayOfWeek() );
}

QDate DateHelper::GetDateForFirstDayInMonthForDate( const QDate& a_rDate )
{
	return QDate( a_rDate.year(), a_rDate.month(), 1 );
}

QDate DateHelper::GetDateForLastDayInMonthForDate( const QDate& a_rDate )
{
	return QDate( a_rDate.year(), a_rDate.month(), a_rDate.daysInMonth() );
}

QString DateHelper::GetDateForFirstDayInWeekForDate( const QString& a_rDate )
{
	return DateHelper::GetDateForFirstDayInWeekForDate( QDate::fromString( a_rDate, Constants::DATA_FORMAT ) ).toString( Constants::DATA_FORMAT );
}

QString DateHelper::GetDateForLastDayInWeekForDate( const QString& a_rDate )
{
	return DateHelper::GetDateForLastDayInWeekForDate( QDate::fromString( a_rDate, Constants::DATA_FORMAT ) ).toString( Constants::DATA_FORMAT );
}

QString DateHelper::GetDateForFirstDayInMonthForDate( const QString& a_rDate )
{
	return DateHelper::GetDateForFirstDayInMonthForDate( QDate::fromString( a_rDate, Constants::DATA_FORMAT ) ).toString( Constants::DATA_FORMAT );
}

QString DateHelper::GetDateForLastDayInMonthForDate( const QString& a_rDate )
{
	return DateHelper::GetDateForLastDayInMonthForDate( QDate::fromString( a_rDate, Constants::DATA_FORMAT ) ).toString( Constants::DATA_FORMAT );
}

int DateHelper::GetSecondsForMM_SS( const QTime& a_rTime )
{
	return ( a_rTime.minute() * 60 + a_rTime.second() );
}

int DateHelper::GetSecondsForHH_MM_SS( const QTime& a_rTime )
{
	return ( a_rTime.hour() * 3600 + GetSecondsForMM_SS( a_rTime ) );
}

QString DateHelper::GetTranslatedMonth( const QDate& a_rDate )
{
	switch ( a_rDate.month() )
	{
		case 1:
		{
			return "Styczeń";
		}
		case 2:
		{
			return "Luty";
		}
		case 3:
		{
			return "Marzec";
		}
		case 4:
		{
			return "Kwiecień";
		}
		case 5:
		{
			return "Maj";
		}
		case 6:
		{
			return "Czerwiec";
		}
		case 7:
		{
			return "Lipiec";
		}
		case 8:
		{
			return "Sierpień";
		}
		case 9:
		{
			return "Wrzesień";
		}
		case 10:
		{
			return "Październik";
		}
		case 11:
		{
			return "Listopad";
		}
		case 12:
		{
			return "Grudzień";
		}
	}

	qWarning() << "Invalid month";
	throw 1;
}

QString DateHelper::GetStringFromSeconds( const int a_iSeconds, const QString& a_rFormat )
{
	return QTime( 0, 0, 0, 0 ).addSecs( a_iSeconds ).toString( a_rFormat );
}

QTime DateHelper::GetTimeFromSeconds( const int a_iSeconds )
{
	return QTime( 0, 0, 0, 0 ).addSecs( a_iSeconds );
}
