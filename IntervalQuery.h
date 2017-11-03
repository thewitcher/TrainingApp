#ifndef INTERVALQUERY_H
#define INTERVALQUERY_H

#include <QSharedPointer>
#include "IntervalData.h"

class IntervalQuery
{
public:
	void Insert( const QSharedPointer<IntervalData> a_pDataObject );
};

#endif // INTERVALQUERY_H
