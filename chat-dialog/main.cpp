#include "chatdialog.h"
#include <QApplication>

#include <QSettings>
#include <QNetworkConfigurationManager>
#include <QNetworkSession>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QNetworkConfigurationManager manager;
    if(manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired){
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered){
            config = manager.defaultConfiguration();
        }

        QNetworkSession* networkSession = new QNetworkSession(config, &a);
        networkSession->open();
        networkSession->waitForOpened();

        if(networkSession->isOpen()){
            QNetworkConfiguration config = networkSession->configuration();
            QString id;
            if(config.type() == QNetworkConfiguration::UserChoice){ id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString(); }
            else{ id = config.identifier(); }

            QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
            settings.beginGroup(QLatin1String("QtNetwork"));
            settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
            settings.endGroup();
        }
    }

    ChatDialog w;
    w.show();

    return a.exec();
}
