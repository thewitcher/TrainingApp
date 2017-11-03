#ifndef CALENDARVIEWCONTROLLER_H
#define CALENDARVIEWCONTROLLER_H

#include <QTableView>
#include <QLabel>
#include <QObject>

#include "TrainingDayViewController.h"
#include "CalendarItem.h"

class QStandardItemModel;

class CalendarViewController : public QObject
{

	Q_OBJECT

public:
	CalendarViewController();
	~CalendarViewController();

	void SetTrainingDetailsLabel( QLabel* a_pTrainingDetailsLabel );
	void SetTableView( QTableView* a_pCalendar );

	void CreateCalendar();
	void CreateModel();

protected slots:
	void slotOnDoubleClicked( const QModelIndex& a_rIndex );
	void slotUpdateSelected();
	void slotUpdateRightPanel(  const QModelIndex& a_rIndex );

private:
	void CreateAndSetDelegate();
	void CreateAndSetModel();
	void CustomizeView();
	void PopulateDataBaseWithEmptyTrainingDays( const QPair<QDate, QDate>& a_rEdgeDate );
	QPair<QDate, QDate> GetEdgeDates() const;
	void CreateHeaders();


	QTableView* m_pCalendar;
	QLabel* m_pTrainingDetailsLabel;
	QStandardItemModel* m_pCalendarModel = nullptr;
	QSharedPointer<TrainingDayViewController> m_pTrainingDayView = QSharedPointer<TrainingDayViewController>::create();
	QList<QDate> m_aAllDates;
};

#endif // CALENDARVIEWCONTROLLER_H
