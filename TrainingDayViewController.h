#ifndef TRAININGDAYVIEWCONTROLLER_H
#define TRAININGDAYVIEWCONTROLLER_H

#include <QWidget>

#include "TrainingDayData.h"
#include "TrainingData.h"
#include "IntervalSqlModel.h"
#include "IntervalData.h"

namespace Ui
{
	class TrainingDayView;
}

class QSqlRelationalTableModel;

class TrainingDayViewController : public QWidget
{
	Q_OBJECT

public:
	explicit TrainingDayViewController( QWidget* a_pParent = nullptr );
	~TrainingDayViewController();

	void SetTrainingDayData( QSharedPointer<TrainingDayData> a_pTrainingDayData );
	void SetTrainingData( QSharedPointer<TrainingData> a_pTrainingData );

	void Refresh();

signals:
	void signalClosed();

protected slots:
	void slotOnSaveClicked( bool a_bChecked );
	void slotOnAddClicked( bool a_bChecked );
	void slotOnQuitClicked( bool a_bChecked );

private:
	void LoadIntervals();
	void PopulateView();
	void SetModel();
	QSharedPointer<IntervalData> ReadIntervalDataFromUI() const;

	Ui::TrainingDayView *m_pTrainingDayUI;
	IntervalSqlModel* m_pIntervalModel = nullptr;
	QSharedPointer<TrainingDayData> m_pTrainingDayData;
	QSharedPointer<TrainingData> m_pTrainingData;
};

#endif // TRAININGDAYVIEWCONTROLLER_H
