#include "Settings.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

Settings* Settings::m_pSettings = nullptr;

Settings* Settings::GetInstance()
{
	if ( !m_pSettings )
	{
		m_pSettings = new Settings;
	}
	return m_pSettings;
}

void Settings::Load()
{
	QFile settings( "./settings.txt" );
	if ( settings.open( QFile::ReadOnly ) )
	{
		QTextStream out( &settings );

		QString strKey;
		QString strValue;

		while ( !out.atEnd() )
		{
			out >> strKey;
			out >> strValue;

			if ( !strKey.isEmpty() && !strValue.isEmpty() )
			{
				m_aSettings.insert( strKey, strValue );
			}
		}
	}
}

QString Settings::GetSetting( const QString& a_rSettingName ) const
{
	if ( !m_aSettings.contains( a_rSettingName ) )
	{
		qWarning() << "No such setting: " << a_rSettingName;
		throw 1;
	}
	return m_aSettings.value( a_rSettingName );
}

Settings::Settings()
{
	// Nothinf
}
