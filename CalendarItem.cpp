#include "CalendarItem.h"
#include "DateHelper.h"

#include <QPainter>

CalendarItem::CalendarItem( QSharedPointer<TrainingGeneralData> a_pTrainingGeneralData )
	: m_pTrainingGeneralData( a_pTrainingGeneralData )
{
	// Nothing
}

QVariant CalendarItem::data( int /*a_iRole*/ ) const
{
	return QVariant::fromValue( *this );
}

void CalendarItem::Paint( QPainter* a_pPainter, const QRect& a_rRect, const QPalette& a_pPalette ) const
{
	a_pPainter->save();

	QFontMetrics fm( a_pPainter->font() );
	int iPixelsHight = fm.height();

	a_pPainter->setRenderHint( QPainter::Antialiasing, true );
	a_pPainter->setBrush( a_pPalette.foreground() );

	QFont oldFont = a_pPainter->font();
	QFont boldFont = a_pPainter->font();
	boldFont.setBold( true );
	a_pPainter->setFont( boldFont );

	a_pPainter->translate( 5, 5 );
	a_pPainter->drawText( a_rRect, QString( m_pTrainingGeneralData->GetDate() ) );

	if ( !m_pTrainingGeneralData->GetName().isEmpty() )
	{
		a_pPainter->translate( 0, iPixelsHight );
		a_pPainter->drawText( a_rRect, m_pTrainingGeneralData->GetName() );
	}

	a_pPainter->setFont( oldFont );

	a_pPainter->translate( 0, iPixelsHight );
	a_pPainter->drawText( a_rRect, QString( "Dystans: " + QString::number( m_pTrainingGeneralData->GetDistance() / 1000.0 ) + " km" ) );

	a_pPainter->translate( 0, iPixelsHight );
	a_pPainter->drawText( a_rRect, QString( "Czas: " + DateHelper::GetStringFromSeconds( m_pTrainingGeneralData->GetDuration(), "HH:mm:ss" ) ) );

	a_pPainter->translate( 0, iPixelsHight );
	a_pPainter->drawText( a_rRect, QString( "Śr. tętno: " + QString::number( m_pTrainingGeneralData->GetAvgPulse() ) ) );

	a_pPainter->translate( 0, iPixelsHight );
	QTime pace( 0, m_pTrainingGeneralData->GetAvgPace() / 60, m_pTrainingGeneralData->GetAvgPace() % 60 );
	a_pPainter->drawText( a_rRect, QString( "Śr. tempo: " + pace.toString( "mm:ss" ) ) );

	a_pPainter->restore();
}

QSize CalendarItem::sizeHint() const
{
	return QSize( 150, 120 );
}

QSharedPointer<TrainingGeneralData> CalendarItem::GetTrainingGeneralData() const
{
	return m_pTrainingGeneralData;
}

QColor CalendarItem::GetColor()
{
	if ( m_pTrainingGeneralData )
	{
		switch ( m_pTrainingGeneralData->GetTrainingType() )
		{
			case 0:
			{
				return QColor( "white" );
			}
			case 1:
			{
				return QColor( "orange" );
			}
			case 2:
			{
				return QColor( "green" );
			}
			case 3:
			{
				return QColor( "grey" );
			}
			case 4:
			{
				return QColor( "pink" );
			}
			case 5:
			{
				return QColor( "brown" );
			}
			case 6:
			{
				return QColor( "dark blue" );
			}
			case 7:
			{
				return QColor( "cyan" );
			}
			case 8:
			{
				return QColor( "light orange" );
			}
			case 9:
			{
				return QColor( "yellow" );
			}
			case 10:
			{
				return QColor( "dark yellow" );
			}
			case 11:
			{
				return QColor( "light grey" );
			}
			case 12:
			{
				return QColor( "purpure" );
			}
			case 13:
			{
				return QColor( "dark orange" );
			}
		}
	}
	return QColor( "white" );
}
