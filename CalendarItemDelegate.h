#ifndef CALENDARITEMDELEGATE_H
#define CALENDARITEMDELEGATE_H

#include "ItemDelegate.h"
#include "CalendarItem.h"

class CalendarItemDelegate : public ItemDelegate<CalendarItem>
{
public:
	CalendarItemDelegate( QObject* a_pParent = nullptr );

protected:
	void setEditorData( QWidget* a_pEditor, const QModelIndex& a_rIndex ) const override;
	void setModelData( QWidget* a_pEditor, QAbstractItemModel* a_pModel, const QModelIndex& a_rIndex ) const override;
	void updateEditorGeometry( QWidget* a_pEditor, const QStyleOptionViewItem& a_rOption, const QModelIndex& a_rIndex ) const override;
	QWidget* createEditor( QWidget* a_pParent, const QStyleOptionViewItem& a_rOption, const QModelIndex& a_rIndex ) const;
};

#endif // CALENDARITEMDELEGATE_H
