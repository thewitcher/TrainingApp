#ifndef CALENDARITEM_H
#define CALENDARITEM_H

#include "TrainingGeneralData.h"

#include <QStandardItem>
#include <QPalette>

class CalendarItem : public QStandardItem
{
public:
	CalendarItem( QSharedPointer<TrainingGeneralData> a_pTrainingGeneralData = nullptr );

	QVariant data( int a_iRole ) const;
	void Paint( QPainter* a_pPainter, const QRect& a_rRect, const QPalette& a_pPalette ) const;
	QSize sizeHint() const;
	QSharedPointer<TrainingGeneralData> GetTrainingGeneralData() const;
	QColor GetColor();

protected:
	QSharedPointer<TrainingGeneralData> m_pTrainingGeneralData;
};

Q_DECLARE_METATYPE( CalendarItem )

#endif // CALENDARITEM_H
