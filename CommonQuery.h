#ifndef COMMONQUERY_H
#define COMMONQUERY_H

#include <QString>

class CommonQuery
{
public:
	static int LoadAvgPulse( const QString& a_rDate );
	static int LoadAvgPace( const QString& a_rDate );
};

#endif // COMMONQUERY_H
