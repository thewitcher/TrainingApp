#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Settings.h"

MainWindow::MainWindow( QWidget* a_pParent )
	: QMainWindow( a_pParent )
	, m_pMainWindowUI( new Ui::MainWindow )
{
	m_pMainWindowUI->setupUi( this );

	Init();

	m_pMainWindowUI->m_pModeWidget->setCurrentIndex( 0 );
	connect( m_pMainWindowUI->m_pModeWidget, &QTabWidget::currentChanged, this, &MainWindow::slotOnCurrentTabChanged, Qt::UniqueConnection );

	m_calendarViewController.SetTableView( m_pMainWindowUI->m_pCalendar );
	m_calendarViewController.SetTrainingDetailsLabel( m_pMainWindowUI->m_pTrainingDetailsLabel );
	m_calendarViewController.CreateCalendar();

	m_chartViewController.SetChartView( m_pMainWindowUI->m_pChartView );
	connect( m_pMainWindowUI->m_pHrRestChart, &QCheckBox::toggled, &m_chartViewController, &ChartViewController::slotOnHrRestToggled, Qt::UniqueConnection );
	connect( m_pMainWindowUI->m_pAvgPaceChart, &QCheckBox::toggled, &m_chartViewController, &ChartViewController::slotOnPaceToggled, Qt::UniqueConnection );
	connect( m_pMainWindowUI->m_pAvgPulseChart, &QCheckBox::toggled, &m_chartViewController, &ChartViewController::slotOnPulseToggled, Qt::UniqueConnection );
	connect( m_pMainWindowUI->m_pClearChartTips, &QCheckBox::clicked, &m_chartViewController, &ChartViewController::slotOnClearChartTipsClicked, Qt::UniqueConnection );

	connect( m_pMainWindowUI->m_pActionQuit, &QAction::triggered, this, &MainWindow::slotOnQuit, Qt::UniqueConnection );
}

MainWindow::~MainWindow()
{
	delete m_pMainWindowUI;
}

void MainWindow::slotOnQuit( bool /*a_bChecked*/ )
{
	qApp->quit();
}

void MainWindow::slotOnCurrentTabChanged( int a_iTabIndex )
{
	if ( m_pMainWindowUI->m_pModeWidget->widget( a_iTabIndex )->objectName() == "Charts" )
	{
		m_chartViewController.OnOpen();
	}
}

void MainWindow::Init()
{
	Settings::GetInstance()->Load();
}
