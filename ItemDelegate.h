#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QEvent>

template <class ItemType>
class ItemDelegate : public QStyledItemDelegate
{
public:
	ItemDelegate( QObject* a_pParent = nullptr );

protected:
	inline void paint( QPainter* a_pPainter, const QStyleOptionViewItem& a_rOption, const QModelIndex& a_rIndex ) const;
	inline QSize sizeHint( const QStyleOptionViewItem& a_rOption, const QModelIndex& a_rIndex ) const;
};

template <class ItemType>
ItemDelegate<ItemType>::ItemDelegate( QObject* a_pParent )
	: QStyledItemDelegate( a_pParent )
{
	// Nothing
}

template <class ItemType>
void ItemDelegate<ItemType>::paint( QPainter* a_pPainter, const QStyleOptionViewItem& a_rOption, const QModelIndex& a_rIndex ) const
{
	if ( a_rIndex.data().canConvert<ItemType>() )
	{
		ItemType item = qvariant_cast<ItemType>( a_rIndex.data() );

		if ( a_rOption.state & QStyle::State_Selected )
		{
			a_pPainter->fillRect( a_rOption.rect, a_rOption.palette.highlight() );
		}
		else
		{
			a_pPainter->fillRect( a_rOption.rect, item.GetColor() );
		}

		item.Paint( a_pPainter, a_rOption.rect, a_rOption.palette );
	}
	else
	{
		QStyledItemDelegate::paint( a_pPainter, a_rOption, a_rIndex );
	}
}

template <class ItemType>
QSize ItemDelegate<ItemType>::sizeHint( const QStyleOptionViewItem& a_rOption, const QModelIndex& a_rIndex ) const
{
	if ( a_rIndex.data().canConvert<ItemType>() )
	{
		ItemType item = qvariant_cast<ItemType>( a_rIndex.data() );
		return item.sizeHint();
	}
	else
	{
		return QStyledItemDelegate::sizeHint( a_rOption, a_rIndex );
	}
}

#endif // ITEMDELEGATE_H
