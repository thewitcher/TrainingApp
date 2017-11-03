#include "ChartViewController.h"

#include "ChartQuery.h"
#include "Constants.h"

#include <QtCharts/QBarSet>
#include <QDebug>
#include <QDate>

ChartViewController::ChartViewController()
{
	// Nothing
}

void ChartViewController::ConfigureXAxis()
{
	m_pAxisX->setFormat( Constants::DATA_FORMAT );
	m_pChart->addAxis( m_pAxisX, Qt::AlignBottom );
}

void ChartViewController::Draw( const QVector<ChartViewController::ESeriesType>& a_rSeriesToDraw )
{
	ClearChart();
	ConfigureXAxis();

	bool bChangeAxisSizes = false;
	for ( ChartViewController::ESeriesType eSeriesType : a_rSeriesToDraw )
	{
		// Series
		CreateAndAddSeries( eSeriesType );
		bChangeAxisSizes = !bChangeAxisSizes;
	}
}

Qt::AlignmentFlag ChartViewController::GetYAxisAlignment( ESeriesType a_eSeriesType ) const
{
	return ( a_eSeriesType % 2 == 0 ? Qt::AlignLeft : Qt::AlignRight );
}

void ChartViewController::CreateSeriesForAvgPulse()
{
	QtCharts::QLineSeries* pSeries = new QtCharts::QLineSeries;

	QVector<QPointF> aData = ChartQuery::GetDataForAvgPulse();
	for ( auto pPoint : aData )
	{
		*pSeries << pPoint;
	}

	pSeries->setName( "Średnie tętno" );
	m_pChart->addSeries( pSeries );

	QtCharts::QValueAxis* pAxisY = GetYAxis( SeriesForAvgPulse );
	pAxisY->setLinePenColor( pSeries->pen().color() );
	m_pChart->addAxis( pAxisY, GetYAxisAlignment( SeriesForAvgPulse ) );

	pSeries->attachAxis( m_pAxisX );
	pSeries->attachAxis( pAxisY );

	connect( pSeries, &QtCharts::QLineSeries::hovered, this, &ChartViewController::slotToolTip, Qt::UniqueConnection );
	connect( pSeries, &QtCharts::QLineSeries::clicked, this, &ChartViewController::slotKeepChartTip, Qt::UniqueConnection );
}

void ChartViewController::CreateSeriesForAvgPace()
{
	QtCharts::QLineSeries* pSeries = new QtCharts::QLineSeries;

	QVector<QPointF> aData = ChartQuery::GetDataForAvgPace();
	for ( auto pPoint : aData )
	{
		*pSeries << pPoint;
	}

	pSeries->setName( "Średnie tempo" );
	m_pChart->addSeries( pSeries );

	QtCharts::QValueAxis* pAxisY = GetYAxis( SeriesForAvgPace );
	pAxisY->setLinePenColor( pSeries->pen().color() );
	m_pChart->addAxis( pAxisY, GetYAxisAlignment( SeriesForAvgPace ) );

	pSeries->attachAxis( m_pAxisX );
	pSeries->attachAxis( pAxisY );

	connect( pSeries, &QtCharts::QLineSeries::hovered, this, &ChartViewController::slotToolTip, Qt::UniqueConnection );
	connect( pSeries, &QtCharts::QLineSeries::clicked, this, &ChartViewController::slotKeepChartTip, Qt::UniqueConnection );
}

void ChartViewController::CreateSeriesForHrRest()
{
	QtCharts::QLineSeries* pSeries = new QtCharts::QLineSeries;

	QVector<QPointF> aData = ChartQuery::GetDataForHrRest();
	for ( auto pPoint : aData )
	{
		*pSeries << pPoint;
	}

	pSeries->setName( "Tętno spoczynkowe" );
	m_pChart->addSeries( pSeries );

	QtCharts::QValueAxis* pAxisY = GetYAxis( SeriesForHrRest );
	pAxisY->setLinePenColor( pSeries->pen().color() );
	m_pChart->addAxis( pAxisY, GetYAxisAlignment( SeriesForHrRest ) );

	pSeries->attachAxis( m_pAxisX );
	pSeries->attachAxis( pAxisY );

	connect( pSeries, &QtCharts::QLineSeries::hovered, this, &ChartViewController::slotToolTip, Qt::UniqueConnection );
	connect( pSeries, &QtCharts::QLineSeries::clicked, this, &ChartViewController::slotKeepChartTip, Qt::UniqueConnection );
}

QtCharts::QValueAxis* ChartViewController::GetYAxis( ChartViewController::ESeriesType a_eSeriesType )
{
	if ( !m_aYAxises.contains( a_eSeriesType ) )
	{
		m_aYAxises.insert( a_eSeriesType, new QtCharts::QValueAxis );
	}

	return m_aYAxises.value( a_eSeriesType );
}

void ChartViewController::CreateAndAddSeries( ESeriesType a_eSeriesType )
{
	switch ( a_eSeriesType )
	{
		case ChartViewController::SeriesForAvgPace:
		{
			CreateSeriesForAvgPace();
			break;
		}
		case ChartViewController::SeriesForAvgPulse:
		{
			CreateSeriesForAvgPulse();
			break;
		}
		case ChartViewController::SeriesForHrRest:
		{
			CreateSeriesForHrRest();
			break;
		}
	}
}

void ChartViewController::SetChartView( QtCharts::QChartView* a_pChartView )
{
	m_pChartView = a_pChartView;
	ConfigureView();
}

void ChartViewController::OnOpen()
{
	ClearChart();
}

void ChartViewController::slotToolTip( const QPointF& a_rPoint, bool a_bState )
{
	if ( m_pChartTip == nullptr )
	{
		m_pChartTip = QSharedPointer<ChartTip>::create( m_pChart );
	}

	if ( a_bState )
	{
		m_pChartTip->SetText( QString("X: %1 \nY: %2 ").arg( QDateTime::fromMSecsSinceEpoch( a_rPoint.x() ).toString( Constants::DATA_FORMAT ) ).arg( a_rPoint.y() ) );
		m_pChartTip->SetAnchor( a_rPoint );
		m_pChartTip->setZValue( 11 );
		m_pChartTip->UpdateGeometry();
		m_pChartTip->show();
	}
	else
	{
		m_pChartTip->hide();
	}
}

void ChartViewController::slotKeepChartTip()
{
	m_aChartTips.append( m_pChartTip );
	m_pChartTip = QSharedPointer<ChartTip>::create( m_pChart );
}

void ChartViewController::ClearChartTips()
{
	m_pChartTip.clear();
	m_aChartTips.clear();
}

void ChartViewController::ClearChart()
{
	m_pChart->removeAxis( m_pAxisX );

	for ( auto pXAxis : m_aYAxises )
	{
		m_pChart->removeAxis( pXAxis );
	}

	m_pChart->removeAllSeries();

	ClearChartTips();
}

void ChartViewController::ConfigureView()
{
	m_pChartView->setRenderHint( QPainter::Antialiasing );
	m_pChartView->setChart( m_pChart );
	m_pChart->legend()->setAlignment( Qt::AlignBottom );
	m_pChart->setTitle( "Analiza treningów" );
}

void ChartViewController::slotOnHrRestToggled( bool a_bChecked )
{
	if ( a_bChecked )
	{
		m_aSeriesToDraw.append( SeriesForHrRest );
	}
	else
	{
		m_aSeriesToDraw.removeOne( SeriesForHrRest );
	}

	Draw( m_aSeriesToDraw );
}

void ChartViewController::slotOnPaceToggled( bool a_bChecked )
{
	if ( a_bChecked )
	{
		m_aSeriesToDraw.append( SeriesForAvgPace );
	}
	else
	{
		m_aSeriesToDraw.removeOne( SeriesForAvgPace );
	}

	Draw( m_aSeriesToDraw );
}

void ChartViewController::slotOnPulseToggled( bool a_bChecked )
{
	if ( a_bChecked )
	{
		m_aSeriesToDraw.append( SeriesForAvgPulse );
	}
	else
	{
		m_aSeriesToDraw.removeOne( SeriesForAvgPulse );
	}

	Draw( m_aSeriesToDraw );
}

void ChartViewController::slotOnClearChartTipsClicked()
{
	ClearChartTips();
}
