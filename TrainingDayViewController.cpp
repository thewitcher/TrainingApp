#include "TrainingDayViewController.h"
#include "ui_TrainingDayView.h"

#include "DateHelper.h"
#include "TrainingDayQuery.h"
#include "TrainingQuery.h"
#include "IntervalQuery.h"

#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QSqlQuery>

TrainingDayViewController::TrainingDayViewController( QWidget* a_pParent )
	: QWidget( a_pParent ),
	m_pTrainingDayUI( new Ui::TrainingDayView )
{
	m_pTrainingDayUI->setupUi( this );

	connect( m_pTrainingDayUI->m_pSaveTrainingButton, &QPushButton::clicked, this, &TrainingDayViewController::slotOnSaveAndQuitClicked, Qt::UniqueConnection );
	connect( m_pTrainingDayUI->m_pAddIntervalButton, &QPushButton::clicked, this, &TrainingDayViewController::slotOnAddClicked, Qt::UniqueConnection );
	connect( m_pTrainingDayUI->m_pQuitButton, &QPushButton::clicked, this, &TrainingDayViewController::slotOnQuitClicked, Qt::UniqueConnection );
}

TrainingDayViewController::~TrainingDayViewController()
{
	delete m_pTrainingDayUI;
}

void TrainingDayViewController::SetTrainingDayData( QSharedPointer<TrainingDayData> a_pTrainingDayData )
{
	m_pTrainingDayData = a_pTrainingDayData;
}

void TrainingDayViewController::SetTrainingData( QSharedPointer<TrainingData> a_pTrainingData )
{
	m_pTrainingData = a_pTrainingData;
}

void TrainingDayViewController::Refresh()
{
	PopulateView();
	LoadIntervals();
}

void TrainingDayViewController::LoadIntervals()
{
	if ( m_pIntervalModel )
	{
		delete m_pIntervalModel;
	}

	if ( m_pTrainingDayData )
	{
		SetModel();
	}
}

void TrainingDayViewController::SetModel()
{
	m_pIntervalModel = new IntervalSqlModel;
	m_pIntervalModel->setTable( "Interval" );

	QString strWhereStatement( "Date = '%1'" );
	strWhereStatement = strWhereStatement.arg( m_pTrainingDayData->GetDate() );

	m_pIntervalModel->setFilter( strWhereStatement );
	m_pIntervalModel->setEditStrategy( QSqlTableModel::OnFieldChange );

	m_pTrainingDayUI->m_pIntervalView->setModel( m_pIntervalModel );
	m_pTrainingDayUI->m_pIntervalView->resizeColumnsToContents();
	m_pTrainingDayUI->m_pIntervalView->hideColumn( 0 ); // primary key
	m_pTrainingDayUI->m_pIntervalView->hideColumn( 1 ); // foreign key

	m_pIntervalModel->TranslateHeaders();

	m_pTrainingDayUI->m_pIntervalView->resizeColumnsToContents();

	m_pIntervalModel->select();
}

void TrainingDayViewController::PopulateView()
{
	if ( m_pTrainingDayData )
	{
		m_pTrainingDayUI->m_pWeight->setValue( m_pTrainingDayData->GetWeight() );
		m_pTrainingDayUI->m_pHrRest->setValue( m_pTrainingDayData->GetHrRest() );
		m_pTrainingDayUI->m_pSleepLevel->setCurrentIndex( m_pTrainingDayData->GetSleepLevel() );
		m_pTrainingDayUI->m_pTresholdPulse->setValue( m_pTrainingDayData->GetTresholdPulse() );

		m_pTrainingDayUI->m_pTresholdPace->setTime( DateHelper::GetTimeFromSeconds( m_pTrainingDayData->GetTresholdPace() ) );
	}

	if ( m_pTrainingData )
	{
		m_pTrainingDayUI->m_pMood->setCurrentIndex( m_pTrainingData->GetMood() );
		m_pTrainingDayUI->m_pTrainingName->setText( m_pTrainingData->GetName() );

		m_pTrainingDayUI->m_pRealisationTextEdit->setPlainText( m_pTrainingData->GetRealistaion() );
		m_pTrainingDayUI->m_pPlanTextEdit->setPlainText( m_pTrainingData->GetPlan() );
		m_pTrainingDayUI->m_pRestTime->setValue( m_pTrainingData->GetRest() );

		m_pTrainingDayUI->m_pTrainingEffect->setValue( m_pTrainingData->GetTrainingEffect() );
		m_pTrainingDayUI->m_pTrainingType->setCurrentIndex( m_pTrainingData->GetTrainingType() );
		m_pTrainingDayUI->m_pEnduranceLevel->setValue( m_pTrainingData->GetEnduranceLevel() );

		m_pTrainingDayUI->m_pTrainingTime->setTime( DateHelper::GetTimeFromSeconds( m_pTrainingData->GetTime() ) );
	}
}

void TrainingDayViewController::ClearIntervalData()
{
	m_pTrainingDayUI->m_pAvgPulse->setValue( 0 );
	m_pTrainingDayUI->m_pCadence->setValue( 0 );
	m_pTrainingDayUI->m_pCalories->setValue( 0 );
	m_pTrainingDayUI->m_pDistance->setValue( 0 );
	m_pTrainingDayUI->m_pDuration->setTime( QTime( 0, 0, 0 ) );
	m_pTrainingDayUI->m_pMaxPulse->setValue( 0 );
	m_pTrainingDayUI->m_pMinPulse->setValue( 0 );

	m_pTrainingDayUI->m_pStepLength->setValue( 0.0 );
	m_pTrainingDayUI->m_pAvgPace->setTime( QTime( 0, 0, 0 ) );
	m_pTrainingDayUI->m_pFirstZoneTIme->setTime( QTime( 0, 0, 0 ) );
	m_pTrainingDayUI->m_pSecondZoneTIme->setTime( QTime( 0, 0, 0 ) );
	m_pTrainingDayUI->m_pThirdZoneTIme->setTime( QTime( 0, 0, 0 ) );
	m_pTrainingDayUI->m_pFourthZoneTIme->setTime( QTime( 0, 0, 0 ) );
	m_pTrainingDayUI->m_pFifthZoneTIme->setTime( QTime( 0, 0, 0 ) );
}

void TrainingDayViewController::slotOnSaveAndQuitClicked( bool /*a_bChecked*/ )
{
	if ( m_pTrainingDayData )
	{
		TrainingDayQuery trainingDayQuery;
		m_pTrainingDayData->SetHrRest( m_pTrainingDayUI->m_pHrRest->value() );
		m_pTrainingDayData->SetSleepLevel( m_pTrainingDayUI->m_pSleepLevel->currentIndex() );
		m_pTrainingDayData->SetTresholdPace( DateHelper::GetSecondsForMM_SS( m_pTrainingDayUI->m_pTresholdPace->time() ) );
		m_pTrainingDayData->SetTresholdPulse( m_pTrainingDayUI->m_pTresholdPulse->value() );
		m_pTrainingDayData->SetWeight( m_pTrainingDayUI->m_pWeight->value() );

		if ( m_pTrainingDayData->GetTresholdPace() > 0 && m_pTrainingDayData->GetTresholdPulse() > 0 )
		{
			trainingDayQuery.InsertOrUpdate( m_pTrainingDayData );
		}
		else
		{
			QMessageBox msgBox;
			msgBox.setText( "Tętno i tempo progowe nie zostało wprowadzone. Czy mimo to chcesz zapisać?" );
			msgBox.setStandardButtons( QMessageBox::No | QMessageBox::Yes );
			if ( msgBox.exec() == QMessageBox::Yes )
			{
				trainingDayQuery.InsertOrUpdate( m_pTrainingDayData );
			}
			else
			{
				return;
			}
		}

	}

	if ( m_pTrainingData )
	{
		TrainingQuery trainingQuery;
		m_pTrainingData->SetMood( m_pTrainingDayUI->m_pMood->currentIndex() );
		m_pTrainingData->SetName( m_pTrainingDayUI->m_pTrainingName->text() );
		m_pTrainingData->SetRealistaion( m_pTrainingDayUI->m_pRealisationTextEdit->toPlainText() );
		m_pTrainingData->SetPlan( m_pTrainingDayUI->m_pPlanTextEdit->toPlainText() );
		m_pTrainingData->SetRest( m_pTrainingDayUI->m_pRestTime->value() );

		m_pTrainingData->SetTrainingEffect( m_pTrainingDayUI->m_pTrainingEffect->value() );
		m_pTrainingData->SetTrainingType( m_pTrainingDayUI->m_pTrainingType->currentIndex() );
		m_pTrainingData->SetEnduranceLevel( m_pTrainingDayUI->m_pEnduranceLevel->value() );

		m_pTrainingData->SetTime( DateHelper::GetSecondsForHH_MM_SS( m_pTrainingDayUI->m_pTrainingTime->time() ) );

		trainingQuery.InsertOrUpdate( m_pTrainingData );
	}

	slotOnQuitClicked( true );
}

QSharedPointer<IntervalData> TrainingDayViewController::ReadIntervalDataFromUI() const
{
	QSharedPointer<IntervalData> pIntervalData = QSharedPointer<IntervalData>::create( m_pTrainingDayData->GetDate() );
	pIntervalData->SetAvgPulse( m_pTrainingDayUI->m_pAvgPulse->value() );
	pIntervalData->SetCadence( m_pTrainingDayUI->m_pCadence->value() );
	pIntervalData->SetCalories( m_pTrainingDayUI->m_pCalories->value() );
	pIntervalData->SetDistance( m_pTrainingDayUI->m_pDistance->value() );
	pIntervalData->SetDuration( DateHelper::GetSecondsForHH_MM_SS( m_pTrainingDayUI->m_pDuration->time() ) );
	pIntervalData->SetMaxPulse( m_pTrainingDayUI->m_pMaxPulse->value() );
	pIntervalData->SetMinPulse( m_pTrainingDayUI->m_pMinPulse->value() );

	pIntervalData->SetStepLength( m_pTrainingDayUI->m_pStepLength->value() );
	pIntervalData->SetAvgPace( DateHelper::GetSecondsForMM_SS( m_pTrainingDayUI->m_pAvgPace->time() ) );
	pIntervalData->SetTimeInFirstZone( DateHelper::GetSecondsForHH_MM_SS( m_pTrainingDayUI->m_pFirstZoneTIme->time() ) );
	pIntervalData->SetTimeInSecondZone( DateHelper::GetSecondsForHH_MM_SS( m_pTrainingDayUI->m_pSecondZoneTIme->time() ) );
	pIntervalData->SetTimeInThirdZone( DateHelper::GetSecondsForHH_MM_SS( m_pTrainingDayUI->m_pThirdZoneTIme->time() ) );
	pIntervalData->SetTimeInFourthZone( DateHelper::GetSecondsForHH_MM_SS( m_pTrainingDayUI->m_pFourthZoneTIme->time() ) );
	pIntervalData->SetTimeInFifthZone( DateHelper::GetSecondsForHH_MM_SS( m_pTrainingDayUI->m_pFifthZoneTIme->time() ) );

	return pIntervalData;
}

void TrainingDayViewController::slotOnAddClicked( bool /*a_bChecked*/ )
{
	IntervalQuery query;
	query.Insert( ReadIntervalDataFromUI() );
	m_pIntervalModel->select();
}

void TrainingDayViewController::slotOnQuitClicked( bool /*a_bChecked*/ )
{
	ClearIntervalData();

	emit signalClosed();
	hide();
}
