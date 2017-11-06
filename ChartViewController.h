#ifndef CHARTVIEWCONTROLLER_H
#define CHARTVIEWCONTROLLER_H

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

#include <QObject>

#include "ChartTip.h"

class ChartViewController : public QObject
{

	Q_OBJECT

public:
	enum ESeriesType
	{ SeriesForAvgPace
	, SeriesForAvgPulse
	, SeriesForHrRest
	, SeriesForRest
	, SeriesForDuration
	, SeriesForPaceTSS
	, SeriesForPulseTSS
	, SeriesForCalories
	};

	ChartViewController();

	void Draw( const QVector<ESeriesType>& a_rSeriesToDraw );
	void CreateAndAddSeries( ESeriesType a_eSeriesType );
	void SetChartView( QtCharts::QChartView* a_pChartView );

	void OnOpen();


public slots:
	void slotOnHrRestToggled( bool a_bChecked );
	void slotOnPaceToggled( bool a_bChecked );
	void slotOnPulseToggled( bool a_bChecked );
	void slotOnDurationToggled( bool a_bChecked );
	void slotOnRestToggled( bool a_bChecked );
	void slotOnCaloriesToggled( bool a_bChecked );
	void slotOnPaceTSSToggled( bool a_bChecked );
	void slotOnPulseTSSToggled( bool a_bChecked );

	void slotOnClearChartTipsClicked();

protected slots:
	void slotToolTip( const QPointF& a_rPoint, bool a_bState );
	void slotKeepChartTip();

private:
	void CreateSeries( ESeriesType a_eSeriesType, const QVector<QPointF>& a_aData, const QString& a_strName );

	QtCharts::QValueAxis* GetYAxis( ESeriesType a_eSeriesType );

	void ChartCheckBoxToggle( bool a_bChecked, ESeriesType a_eSeriesType );

	void ClearChart();
	void ClearChartTips();

	void ConfigureXAxis();
	void ConfigureView();

	Qt::AlignmentFlag GetYAxisAlignment( ESeriesType a_eSeriesType ) const;

	QtCharts::QChartView* m_pChartView = nullptr;
	QtCharts::QChart* m_pChart = new QtCharts::QChart;

	QtCharts::QDateTimeAxis* m_pAxisX = new QtCharts::QDateTimeAxis;
	QHash<ESeriesType, QtCharts::QValueAxis*> m_aYAxises;

	QVector<ESeriesType> m_aSeriesToDraw;

	QSharedPointer<ChartTip> m_pChartTip;
	QList<QSharedPointer<ChartTip>> m_aChartTips;
};

#endif // CHARTVIEWCONTROLLER_H
