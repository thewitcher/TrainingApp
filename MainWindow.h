#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "CalendarViewController.h"
#include "ChartViewController.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow( QWidget *a_pParent = 0 );
	~MainWindow();

private slots:
	void slotOnQuit( bool a_bChecked );

	void slotOnCurrentTabChanged( int a_iTabIndex );

private:
	void Init();

	Ui::MainWindow* m_pMainWindowUI;
	CalendarViewController m_calendarViewController;
	ChartViewController m_chartViewController;
};

#endif // MAINWINDOW_H
