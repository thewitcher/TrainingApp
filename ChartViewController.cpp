#include "ChartViewController.h"

#include "ChartQuery.h"
#include "Constants.h"

#include "Settings.h"

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
	m_pAxisX->setMin( QDateTime::fromString( Settings::GetInstance()->GetSetting( "StartDate" ), Constants::DATA_FORMAT ) );
	m_pAxisX->setMax( QDateTime::fromString( Settings::GetInstance()->GetSetting( "EndDate" ), Constants::DATA_FORMAT ) );
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

void ChartViewController::CreateSeries( ESeriesType a_eSeriesType , const QVector<QPointF>& a_aData , const QString& a_strName )
{
	QtCharts::QLineSeries* pSeries = new QtCharts::QLineSeries;

	for ( auto pPoint : a_aData )
	{
		*pSeries << pPoint;
	}

	pSeries->setName( a_strName );
	m_pChart->addSeries( pSeries );

	QtCharts::QValueAxis* pAxisY = GetYAxis( a_eSeriesType );
	pAxisY->setLinePenColor( pSeries->pen().color() );
	m_pChart->addAxis( pAxisY, GetYAxisAlignment( a_eSeriesType ) );

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
			CreateSeries( a_eSeriesType, ChartQuery::GetDataForAvgPace(), "Średnie tempo" );
			break;
		}
		case ChartViewController::SeriesForAvgPulse:
		{
			CreateSeries( a_eSeriesType, ChartQuery::GetDataForAvgPulse(), "Średnie tętno" );
			break;
		}
		case ChartViewController::SeriesForHrRest:
		{
			CreateSeries( a_eSeriesType, ChartQuery::GetDataForHrRest(), "Tętno spoczynkowe" );
			break;
		}
		case ChartViewController::SeriesForRest:
		{
			CreateSeries( a_eSeriesType, ChartQuery::GetDataForRest(), "Czas odpoczynku" );
			break;
		}
		case ChartViewController::SeriesForDuration:
		{
			CreateSeries( a_eSeriesType, ChartQuery::GetDataForDuration(), "Czas trwania" );
			break;
		}
		case ChartViewController::SeriesForCalories:
		{
			CreateSeries( a_eSeriesType, ChartQuery::GetDataForCalories(), "Kalorie" );
			break;
		}
		case ChartViewController::SeriesForPaceTSS:
		{
			CreateSeries( a_eSeriesType, ChartQuery::GetDataForPaceTSS(), "Training stress score - tempo" );
			break;
		}
		case ChartViewController::SeriesForPulseTSS:
		{
			CreateSeries( a_eSeriesType, ChartQuery::GetDataForPulseTSS(), "Training stress score - tętno" );
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

void ChartViewController::slotOnClearChartTipsClicked()
{
	ClearChartTips();
}

void ChartViewController::ChartCheckBoxToggle( bool a_bChecked, ESeriesType a_eSeriesType )
{
	if ( a_bChecked )
	{
		m_aSeriesToDraw.append( a_eSeriesType );
	}
	else
	{
		m_aSeriesToDraw.removeOne( a_eSeriesType );
	}

	Draw( m_aSeriesToDraw );
}

void ChartViewController::slotOnPaceToggled( bool a_bChecked )
{
	ChartCheckBoxToggle( a_bChecked, SeriesForAvgPace );
}

void ChartViewController::slotOnHrRestToggled( bool a_bChecked )
{
	ChartCheckBoxToggle( a_bChecked, SeriesForHrRest );
}

void ChartViewController::slotOnPulseToggled( bool a_bChecked )
{
	ChartCheckBoxToggle( a_bChecked, SeriesForAvgPulse );
}

void ChartViewController::slotOnDurationToggled( bool a_bChecked )
{
	ChartCheckBoxToggle( a_bChecked, SeriesForDuration );
}

void ChartViewController::slotOnRestToggled( bool a_bChecked )
{
	ChartCheckBoxToggle( a_bChecked, SeriesForRest );
}

void ChartViewController::slotOnCaloriesToggled( bool a_bChecked )
{
	ChartCheckBoxToggle( a_bChecked, SeriesForCalories );
}

void ChartViewController::slotOnPaceTSSToggled( bool a_bChecked )
{
	ChartCheckBoxToggle( a_bChecked, SeriesForPaceTSS );
}

void ChartViewController::slotOnPulseTSSToggled( bool a_bChecked )
{
	ChartCheckBoxToggle( a_bChecked, SeriesForPulseTSS );
}
