#include "CalendarItemDelegate.h"
#include "TrainingDayViewController.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

CalendarItemDelegate::CalendarItemDelegate( QObject* a_pParent )
	: ItemDelegate<CalendarItem>( a_pParent )
{
	// Nothing
}

void CalendarItemDelegate::setEditorData( QWidget* /*a_pEditor*/, const QModelIndex& /*a_rIndex*/ ) const
{
	// Nothing
}

void CalendarItemDelegate::setModelData( QWidget* /*a_pEditor*/, QAbstractItemModel* /*a_pModel*/, const QModelIndex& /*a_rIndex*/ ) const
{
	// Nothing
}

void CalendarItemDelegate::updateEditorGeometry( QWidget* /*a_pEditor*/, const QStyleOptionViewItem& /*a_rOption*/, const QModelIndex& /*a_rIndex*/ ) const
{
	// Nothing
}
QWidget *CalendarItemDelegate::createEditor( QWidget* /*a_pParent*/, const QStyleOptionViewItem& /*a_rOption*/, const QModelIndex& /*a_rIndex*/ ) const
{
	return nullptr;
}
