#include "IntervalSqlModel.h"
#include "DateHelper.h"

#include <QDebug>

IntervalSqlModel::IntervalSqlModel( QObject* a_pParent )
	: QSqlRelationalTableModel( a_pParent )
{
	CreateTranslations();
	CreateFilters();
}

QVariant IntervalSqlModel::data( const QModelIndex& a_rIndex, int a_iRole ) const
{
	QString strColumnType = headerData( a_rIndex.column(), Qt::Horizontal, OriginalHeaders ).toString();

	if ( a_iRole == Qt::DisplayRole )
	{
		if ( m_aFilters.contains( strColumnType ) )
		{
			return m_aFilters.value( strColumnType )( QSqlRelationalTableModel::data( a_rIndex, a_iRole ).toString() );
		}
		else
		{
			qWarning() << "No filter for: " << strColumnType;
			throw 1;
		}
	}

	return QSqlRelationalTableModel::data( a_rIndex, a_iRole );
}

void IntervalSqlModel::CreateFilters()
{
	m_aFilters[ "Id" ] = []( const QString& a_rData )->QString
	{
		return a_rData;
	};

	m_aFilters[ "Date" ] = []( const QString& a_rData )->QString
	{
		return a_rData;
	};

	m_aFilters[ "Calories" ] = []( const QString& a_rData )->QString
	{
		return a_rData;
	};

	m_aFilters[ "Distance" ] = []( const QString& a_rData )->QString
	{
		float fDistanceKm = a_rData.toFloat();
		return QString::number( fDistanceKm / 1000.0 );
	};

	m_aFilters[ "AvgPace" ] = []( const QString& a_rData )->QString
	{
		float fPaceInSec = a_rData.toFloat();
		return DateHelper::GetStringFromSeconds( fPaceInSec, "mm:ss" );
	};

	m_aFilters[ "AvgPulse" ] = []( const QString& a_rData )->QString
	{
		return a_rData;
	};

	m_aFilters[ "MinPulse" ] = []( const QString& a_rData )->QString
	{
		return a_rData;
	};

	m_aFilters[ "MaxPulse" ] = []( const QString& a_rData )->QString
	{
		return a_rData;
	};

	m_aFilters[ "Duration" ] = []( const QString& a_rData )->QString
	{
		float fDurationInSec = a_rData.toFloat();
		return DateHelper::GetStringFromSeconds( fDurationInSec, "HH:mm:ss" );
	};
	m_aFilters[ "Cadence" ] = []( const QString& a_rData )->QString
	{
		return a_rData;
	};
	m_aFilters[ "StepLength" ] = []( const QString& a_rData )->QString
	{
		return a_rData;
	};
	m_aFilters[ "TimeInFirstZone" ] = []( const QString& a_rData )->QString
	{
		float fTimeInSec = a_rData.toFloat();
		return DateHelper::GetStringFromSeconds( fTimeInSec, "HH:mm" );
	};
	m_aFilters[ "TimeInSecondZone" ] = []( const QString& a_rData )->QString
	{
		float fTimeInSec = a_rData.toFloat();
		return DateHelper::GetStringFromSeconds( fTimeInSec, "HH:mm" );
	};
	m_aFilters[ "TimeInThirdZone" ] = []( const QString& a_rData )->QString
	{
		float fTimeInSec = a_rData.toFloat();
		return DateHelper::GetStringFromSeconds( fTimeInSec, "HH:mm" );
	};
	m_aFilters[ "TimeInFourthZone" ] = []( const QString& a_rData )->QString
	{
		float fTimeInSec = a_rData.toFloat();
		return DateHelper::GetStringFromSeconds( fTimeInSec, "HH:mm" );
	};
	m_aFilters[ "TimeInFifthZone" ] = []( const QString& a_rData )->QString
	{
		float fTimeInSec = a_rData.toFloat();
		return DateHelper::GetStringFromSeconds( fTimeInSec, "HH:mm" );
	};
}

void IntervalSqlModel::CreateTranslations()
{
	m_aDatabaseTranslation[ "Id" ] = "Id";
	m_aDatabaseTranslation[ "Date" ] = "Data";
	m_aDatabaseTranslation[ "Calories" ] = "Kalorie [kcal]";
	m_aDatabaseTranslation[ "Distance" ] = "Dystans [km]";
	m_aDatabaseTranslation[ "AvgPace" ] = "Średnie tempo [mm:ss]";
	m_aDatabaseTranslation[ "AvgPulse" ] = "Średnie tętno [bpm]";
	m_aDatabaseTranslation[ "MinPulse" ] = "Minimalne tętno [bpm]";
	m_aDatabaseTranslation[ "MaxPulse" ] = "Maksymalne tętno [bpm]";
	m_aDatabaseTranslation[ "Duration" ] = "Czas trwania [hh:mm:ss]";
	m_aDatabaseTranslation[ "Cadence" ] = "Kadencja";
	m_aDatabaseTranslation[ "StepLength" ] = "Długość kroku [m]";
	m_aDatabaseTranslation[ "TimeInFirstZone" ] = "Czas w I strefie [hh:mm]";
	m_aDatabaseTranslation[ "TimeInSecondZone" ] = "Czas w II strefie[hh:mm]";
	m_aDatabaseTranslation[ "TimeInThirdZone" ] = "Czas w III strefie[hh:mm]";
	m_aDatabaseTranslation[ "TimeInFourthZone" ] = "Czas w IV strefie[hh:mm]";
	m_aDatabaseTranslation[ "TimeInFifthZone" ] = "Czas w V strefie[hh:mm]";
}

void IntervalSqlModel::TranslateHeaders()
{
	QVariant varHeaderData;

	for ( int iSection = 0 ; iSection < columnCount() ; ++iSection )
	{
		varHeaderData = headerData( iSection, Qt::Horizontal, Qt::DisplayRole );
		if ( m_aDatabaseTranslation.contains( varHeaderData.toString() ) )
		{
			setHeaderData( iSection, Qt::Horizontal, m_aDatabaseTranslation[ varHeaderData.toString() ] );
			setHeaderData( iSection, Qt::Horizontal, varHeaderData, OriginalHeaders );
		}
		else
		{
			qWarning() << "Missing translation: " + varHeaderData.toString();
			throw 1;
		}
	}
}
