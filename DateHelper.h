#ifndef DATEHELPER_H
#define DATEHELPER_H

#include <QDate>

class DateHelper
{
public:
	static bool IsBefore( const QDate& a_rStartDate, const QDate& a_rEndDate );
	static QDate GetDateForFirstDayInWeekForDate( const QDate& a_rDate );
	static QDate GetDateForLastDayInWeekForDate( const QDate& a_rDate );
	static QDate GetDateForFirstDayInMonthForDate( const QDate& a_rDate );
	static QDate GetDateForLastDayInMonthForDate( const QDate& a_rDate );

	static QString GetDateForFirstDayInWeekForDate( const QString& a_rDate );
	static QString GetDateForLastDayInWeekForDate( const QString& a_rDate );
	static QString GetDateForFirstDayInMonthForDate( const QString& a_rDate );
	static QString GetDateForLastDayInMonthForDate( const QString& a_rDate );


	static int GetSecondsForMM_SS( const QTime& a_rTime );
	static int GetSecondsForHH_MM_SS( const QTime& a_rTime );
	static QString GetTranslatedMonth( const QDate& a_rDate );

	static QString GetStringFromSeconds( const int a_iSeconds, const QString& a_rFormat );
	static QTime GetTimeFromSeconds( const int a_iSeconds );
};

#endif // DATEHELPER_H
