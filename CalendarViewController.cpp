#include "CalendarItemDelegate.h"
#include "TrainingGeneralQuery.h"
#include "TrainingGeneralData.h"
#include "TrainingDayQuery.h"
#include "TrainingDayViewController.h"
#include "StatisticQuery.h"
#include "TrainingQuery.h"
#include "StatisticData.h"
#include "TrainingData.h"
#include "ItemDelegate.h"
#include "CalendarViewController.h"
#include "DateHelper.h"
#include "Constants.h"
#include "Settings.h"

#include <QStandardItemModel>
#include <QHeaderView>
#include <QScrollBar>
#include <QDebug>

CalendarViewController::CalendarViewController()
{
	// Nothing
}

CalendarViewController::~CalendarViewController()
{
	delete m_pCalendarModel;
}

void CalendarViewController::CreateAndSetDelegate()
{
	auto pItemDelegate = new CalendarItemDelegate();
	m_pCalendar->setItemDelegate( pItemDelegate );
}

void CalendarViewController::PopulateDataBaseWithEmptyTrainingDays( const QPair<QDate, QDate>& a_rEdgeDate )
{
	m_aAllDates.clear();

	QDate nextDate = a_rEdgeDate.first;
	TrainingDayQuery query;
	while ( !DateHelper::IsBefore( nextDate, a_rEdgeDate.second ) )
	{
		query.AddEmptyTrainigDay( nextDate.toString( Constants::DATA_FORMAT ) );
		m_aAllDates.append( nextDate );
		nextDate = nextDate.addDays( 1 );
	}
}

void CalendarViewController::CreateHeaders()
{
	m_pCalendarModel->setHeaderData( 0, Qt::Horizontal, "Poniedziałek" );
	m_pCalendarModel->setHeaderData( 1, Qt::Horizontal, "Wtorek" );
	m_pCalendarModel->setHeaderData( 2, Qt::Horizontal, "Środa" );
	m_pCalendarModel->setHeaderData( 3, Qt::Horizontal, "Czwartek" );
	m_pCalendarModel->setHeaderData( 4, Qt::Horizontal, "Piątek" );
	m_pCalendarModel->setHeaderData( 5, Qt::Horizontal, "Sobota" );
	m_pCalendarModel->setHeaderData( 6, Qt::Horizontal, "Niedziela" );
}

void CalendarViewController::SetTrainingDetailsLabel( QLabel* a_pTrainingDetailsLabel )
{
	m_pTrainingDetailsLabel = a_pTrainingDetailsLabel;
}

void CalendarViewController::CreateModel()
{
	if ( m_pCalendarModel )
	{
		delete m_pCalendarModel;
	}

	const int iRowCount = ( m_aAllDates.size() / Constants::DAYS_IN_WEEK );
	m_pCalendarModel = new QStandardItemModel( iRowCount, Constants::DAYS_IN_WEEK );

	for ( int iIndex = 0; iIndex < m_aAllDates.size() ; ++iIndex )
	{
		int iRow = iIndex / Constants::DAYS_IN_WEEK;
		int iColumn = iIndex % Constants::DAYS_IN_WEEK;
		QModelIndex index = m_pCalendarModel->index( iRow, iColumn );

		TrainingGeneralQuery query;
		auto pTrainingGeneralData = query.Load( m_aAllDates.at( iIndex ).toString( Constants::DATA_FORMAT ) );
		m_pCalendarModel->setData( index, QVariant::fromValue( CalendarItem( pTrainingGeneralData ) ) );
	}
}

void CalendarViewController::CreateAndSetModel()
{
	PopulateDataBaseWithEmptyTrainingDays( GetEdgeDates() );
	CreateModel();

	m_pCalendar->setModel( m_pCalendarModel );

	CreateHeaders();
}

void CalendarViewController::CustomizeView()
{
	m_pCalendar->setEditTriggers( QAbstractItemView::NoEditTriggers );
	m_pCalendar->setSelectionBehavior( QAbstractItemView::SelectItems );
	m_pCalendar->setVerticalScrollMode( QAbstractItemView::ScrollPerPixel );
	m_pCalendar->resizeColumnsToContents();
	m_pCalendar->resizeRowsToContents();
	m_pCalendar->verticalHeader()->hide();
	m_pCalendar->verticalScrollBar()->setVisible( false );

	m_pCalendar->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );

	connect( m_pCalendar, &QTableView::doubleClicked, this, &CalendarViewController::slotOnDoubleClicked );
	connect( m_pCalendar, &QTableView::clicked, this, &CalendarViewController::slotUpdateRightPanel );
	connect( m_pTrainingDayView.data(), &TrainingDayViewController::signalClosed, this, &CalendarViewController::slotUpdateSelected, Qt::UniqueConnection );
}

QPair<QDate, QDate> CalendarViewController::GetEdgeDates() const
{
	QDate startDate = QDate::fromString( Settings::GetInstance()->GetSetting( "StartDate" ), Constants::DATA_FORMAT );
	QDate endDate = QDate::fromString( Settings::GetInstance()->GetSetting( "EndDate" ), Constants::DATA_FORMAT );

	if ( DateHelper::IsBefore( startDate, endDate ) )
	{
		qWarning() << "Invalid dates";
		return QPair<QDate, QDate>();
	}

	QDate firstDayInStartWeek = DateHelper::GetDateForFirstDayInWeekForDate( startDate );
	QDate firstDayInEndWeek = DateHelper::GetDateForLastDayInWeekForDate( endDate );

	return qMakePair( firstDayInStartWeek, firstDayInEndWeek );
}

void CalendarViewController::CreateCalendar()
{
	CreateAndSetModel();
	CreateAndSetDelegate();
	CustomizeView();
}

void CalendarViewController::SetTableView( QTableView* a_pCalendar )
{
	m_pCalendar = a_pCalendar;
}

void CalendarViewController::slotOnDoubleClicked( const QModelIndex& a_rIndex )
{
	if ( a_rIndex.data().canConvert<CalendarItem>() )
	{
		CalendarItem item = qvariant_cast<CalendarItem>( a_rIndex.data() );
		auto pTrainingGeneralData = item.GetTrainingGeneralData();

		TrainingDayQuery trainingDayQuery;
		m_pTrainingDayView->SetTrainingDayData( trainingDayQuery.Load( pTrainingGeneralData->GetDate() ) );

		TrainingQuery trainingQuery;
		m_pTrainingDayView->SetTrainingData( trainingQuery.Load( pTrainingGeneralData->GetDate() ) );

		m_pTrainingDayView->Refresh();

		m_pTrainingDayView->showMaximized();
	}
}

void CalendarViewController::slotUpdateSelected()
{
	QModelIndex index = m_pCalendar->selectionModel()->selection().indexes().first();

	if ( index.data().canConvert<CalendarItem>() )
	{
		CalendarItem item = qvariant_cast<CalendarItem>( index.data() );
		TrainingGeneralQuery query;
		auto pTrainingGeneralData = query.Load( item.GetTrainingGeneralData()->GetDate() );
		m_pCalendarModel->setData( index, QVariant::fromValue( CalendarItem( pTrainingGeneralData ) ) );

		slotUpdateRightPanel( index );
	}
}

void CalendarViewController::slotUpdateRightPanel( const QModelIndex& a_rIndex )
{
	if ( a_rIndex.data().canConvert<CalendarItem>() )
	{
		CalendarItem item = qvariant_cast<CalendarItem>( a_rIndex.data() );
		auto pTrainingGeneralData = item.GetTrainingGeneralData();

		const QString strDate = pTrainingGeneralData->GetDate();

		QDate date = QDate::fromString( strDate, Constants::DATA_FORMAT );

		QDate firstDayInWeek = DateHelper::GetDateForFirstDayInWeekForDate( date );
		QDate lastDayInWeek = DateHelper::GetDateForLastDayInWeekForDate( date );

		TrainingQuery trainigQuery;
		QSharedPointer<TrainingData> pTrainingData = trainigQuery.Load( strDate );

		StatisticQuery statisticQuery;
		QSharedPointer<StatisticData> pStatisticData = statisticQuery.Load( strDate );

		QString strTemplate = QString(
		"<b>Dzień:</b> %1<br>" \
		"<b>Plan:</b><br>" \
		"%2<br>" \
		"<b>Realizacja:</b><br>" \
		"%3<br>" \
		"<b>Kalorie:</b> %4<br>" \
		"--------------<br>"
		"<b>Tydzień:</b> %5<br>" \
		"<b>Liczba treningów:</b> %6<br>" \
		"<b>Kilometraż:</b> %7 km<br>" \
		"<b>Łączny czas:</b> %8<br>" \
		"<b>Kalorie:</b> %9<br>" \
		"--------------<br>"
		"<b>Miesiąc:</b> %10<br>" \
		"<b>Liczba treningów:</b> %11<br>" \
		"<b>Kilometraż:</b> %12 km<br>" \
		"<b>Łączny czas:</b> %13<br>" \
		"<b>Kalorie:</b> %14<br>" \
		"--------------<br>" \
		"<b>Training Stress Score (Pace):</b> %15<br>"
		"<b>Training Stress Score (Pulse):</b> %16"
		).arg( strDate )
		.arg( pTrainingData->GetPlan().isEmpty() ? "Brak planu" : pTrainingData->GetPlan().replace( "\n", "<br>" ) )
		.arg( pTrainingData->GetRealistaion().isEmpty() ? "Brak opisu" : pTrainingData->GetRealistaion().replace( "\n", "<br>" ) )
		.arg( pStatisticData->GetCaloriesInDay() )
		.arg( firstDayInWeek.toString( Constants::DATA_FORMAT ) + " - " + lastDayInWeek.toString( Constants::DATA_FORMAT ) )
		.arg( pStatisticData->GetTrainingCountInWeek() )
		.arg( pStatisticData->GetDistanceInWeek() / 1000.0 )
		.arg( DateHelper::GetStringFromSeconds( pStatisticData->GetWholeDurationInWeek(), "HH:mm:ss" ) )
		.arg( pStatisticData->GetCaloriesInWeek() )
		.arg( DateHelper::GetTranslatedMonth( date ) )
		.arg( pStatisticData->GetTrainingCountInMonth() )
		.arg( pStatisticData->GetDistanceInMonth() / 1000.0 )
		.arg( DateHelper::GetStringFromSeconds( pStatisticData->GetWholeDurationInMonth(), "HH:mm:ss" ) )
		.arg( pStatisticData->GetCaloriesInMonth() )
		.arg( pStatisticData->GetTrainingStressScoreForPace() )
		.arg( pStatisticData->GetTrainingStressScoreForPulse() );

		m_pTrainingDetailsLabel->setText( strTemplate );
	}
}
