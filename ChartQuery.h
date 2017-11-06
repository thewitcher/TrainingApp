#ifndef CHARTQUERY_H
#define CHARTQUERY_H

#include <QVector>
#include <QPointF>

class ChartQuery
{
public:
	static QVector<QPointF> GetDataForAvgPulse();
	static QVector<QPointF> GetDataForAvgPace();
	static QVector<QPointF> GetDataForHrRest();

	static QVector<QPointF> GetDataForRest();
	static QVector<QPointF> GetDataForDuration();
	static QVector<QPointF> GetDataForCalories();
	static QVector<QPointF> GetDataForPaceTSS();
	static QVector<QPointF> GetDataForPulseTSS();

	static bool CanTakeToChart( const int a_iValueToCheck );
};

#endif // CHARTQUERY_H
