#ifndef SETTINGS_H
#define SETTINGS_H

#include <QHash>

class Settings
{
public:
	static Settings* GetInstance();

	void Load();
	QString GetSetting( const QString& a_rSettingName ) const;

private:
	Settings();

	QHash<QString, QString> m_aSettings;
	static Settings* m_pSettings;
};

#endif // SETTINGS_H
