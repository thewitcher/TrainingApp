#ifndef DATABASEVIEW_H
#define DATABASEVIEW_H

#include <QSqlRelationalTableModel>

#include <functional>

class IntervalSqlModel : public QSqlRelationalTableModel
{
public:
	enum EUserRole
	{ OriginalHeaders = Qt::UserRole + 1
	};

	IntervalSqlModel( QObject* a_pParent = nullptr );

	void TranslateHeaders();

protected:
	QVariant data( const QModelIndex& a_rIndex, int a_iRole ) const;
	void CreateFilters();
	void CreateTranslations();

private:
	QHash<QString, std::function<QString( const QString& )>> m_aFilters; // translation -> filter
	QHash<QString, QString> m_aDatabaseTranslation; // Original -> translation
};

#endif // DATABASEVIEW_H
