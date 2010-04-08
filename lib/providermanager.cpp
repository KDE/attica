/*
    This file is part of KDE.
    
    Copyright (c) 2009 Eckhart Wörner <ewoerner@kde.org>
    Copyright (c) 2009 Frederik Gladhorn <gladhorn@kde.org>
    
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "providermanager.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QPluginLoader>
#include <QtCore/QSet>
#include <QtCore/QSignalMapper>
#include <QtCore/QSharedPointer>
#include <QtCore/QTimer>
#include <QtCore/QProcess>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkReply>
#include <QtXml/QXmlStreamReader>

#include "platformdependent.h"
#include "qtplatformdependent.h"


using namespace Attica;

#if QT_VERSION < 0x040700
uint qHash(const QUrl& key) {
    return qHash(key.toString());
}
#endif

class ProviderManager::Private {
public:
    PlatformDependent* m_internals;
    QHash<QUrl, Provider> m_providers;
    QHash<QUrl, QList<QString> > m_providerFiles;
    QSignalMapper m_downloadMapping;
    QHash<QString, QNetworkReply*> m_downloads;
    QPluginLoader m_pluginLoader;
    bool m_authenticationSuppressed;

    Private()
        : m_internals(0)
        , m_authenticationSuppressed(false)
    {
    }
    ~Private()
    {
        // do not delete m_internals: it is the root component of a plugin!
    }
};


PlatformDependent* ProviderManager::loadPlatformDependent() {

    QString program("kde4-config");
    QStringList arguments;
    arguments << "--path" << "lib";
    
    QProcess process;
    process.start(program, arguments);
    process.waitForFinished();

    /* Try to find the KDE plugin. This can be extended to include other platform specific plugins. */

    QStringList paths = QString(process.readAllStandardOutput()).trimmed().split(':');
    qDebug() << "Pfade: " << paths;

    QString pluginName("attica_kde.so");
    
    foreach(const QString& path, paths) {
        QString libraryPath(path + '/' + pluginName);
        qDebug() << "Trying to load " << libraryPath;
        if (QFile::exists(libraryPath)) {
            d->m_pluginLoader.setFileName(libraryPath);
            QObject* plugin = d->m_pluginLoader.instance();
            if (plugin) {
                PlatformDependent* platformDependent = qobject_cast<PlatformDependent*>(plugin);
                if (platformDependent) {
                    qDebug() << "Using Attica with KDE support";
                    return platformDependent;
                }
            }
        }
    }
    qDebug() << "Using Attica without KDE support";
    return new QtPlatformDependent;
}


ProviderManager::ProviderManager()
    : d(new Private)
{
    d->m_internals = loadPlatformDependent();
    connect(d->m_internals->nam(), SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), SLOT(authenticate(QNetworkReply*,QAuthenticator*)));
    connect(&d->m_downloadMapping, SIGNAL(mapped(QString)), SLOT(fileFinished(QString)));
}

void ProviderManager::loadDefaultProviders()
{
    QTimer::singleShot(0, this, SLOT(slotLoadDefaultProvidersInternal()));
}

void ProviderManager::setAuthenticationSuppressed(bool suppressed)
{
    d->m_authenticationSuppressed = suppressed;
}

void ProviderManager::clear()
{
    d->m_providerFiles.clear();
    d->m_providers.clear();
}

void ProviderManager::slotLoadDefaultProvidersInternal()
{
    foreach (const QUrl& url, d->m_internals->getDefaultProviderFiles()) {
        addProviderFile(url);
    }
    if (d->m_downloads.isEmpty()) {
        emit defaultProvidersLoaded();
    }
}

QList<QUrl> ProviderManager::defaultProviderFiles()
{
    return d->m_internals->getDefaultProviderFiles();
}

ProviderManager::~ProviderManager()
{
    delete d;
}

void ProviderManager::addProviderFileToDefaultProviders(const QUrl& url)
{
    d->m_internals->addDefaultProviderFile(url);
    addProviderFile(url);
}

void ProviderManager::removeProviderFileFromDefaultProviders(const QUrl& url)
{
    d->m_internals->removeDefaultProviderFile(url);
}

void ProviderManager::addProviderFile(const QUrl& url)
{
    QString localFile = url.toLocalFile();
    if (!localFile.isEmpty()) {
        QFile file(localFile);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "ProviderManager::addProviderFile: could not open provider file: " << url.toString();
            return;
        }
        addProviderFromXml(file.readAll());
    } else {
        if (!d->m_downloads.contains(url.toString())) {
            QNetworkReply* reply = d->m_internals->get(QNetworkRequest(url));
            connect(reply, SIGNAL(finished()), &d->m_downloadMapping, SLOT(map()));
            d->m_downloadMapping.setMapping(reply, url.toString());
            d->m_downloads.insert(url.toString(), reply);
        }
    }
}

void ProviderManager::fileFinished(const QString& url)
{
    QNetworkReply* reply = d->m_downloads.take(url);
    parseProviderFile(reply->readAll(), url);
    reply->deleteLater();
}

void ProviderManager::addProviderFromXml(const QString& providerXml)
{
    parseProviderFile(providerXml, QString());
}

void ProviderManager::parseProviderFile(const QString& xmlString, const QString& url)
{
    QXmlStreamReader xml(xmlString);
    while (!xml.atEnd() && xml.readNext()) {
        if (xml.isStartElement() && xml.name() == "provider") {
            QString baseUrl;
            QString name;
            QUrl icon;
            while (!xml.atEnd() && xml.readNext()) {
                if (xml.isStartElement())
                {
                    if (xml.name() == "location") {
                        baseUrl = xml.readElementText();
                    }
                    if (xml.name() == "name") {
                        name = xml.readElementText();
                    }
                    if (xml.name() == "icon") {
                        icon = QUrl(xml.readElementText());
                    }
                } else if (xml.isEndElement() && xml.name() == "provider") {
                    break;
                }
            }
            if (!baseUrl.isEmpty()) {
                qDebug() << "Adding provider" << baseUrl;
                d->m_providers.insert(baseUrl, Provider(d->m_internals, QUrl(baseUrl), name, icon));
                emit providerAdded(d->m_providers.value(baseUrl));
            }
        }
    }

    if (d->m_downloads.isEmpty()) {
        emit defaultProvidersLoaded();
    }
}

Provider ProviderManager::providerByUrl(const QUrl& url) const {
    return d->m_providers.value(url);
}

QList<Provider> ProviderManager::providers() const {
    return d->m_providers.values();
}


bool ProviderManager::contains(const QString& provider) const {
    return d->m_providers.contains(provider);
}


QList<QUrl> ProviderManager::providerFiles() const {
    return d->m_providerFiles.keys();
}


void ProviderManager::authenticate(QNetworkReply* reply, QAuthenticator* auth)
{
    QUrl baseUrl;
    foreach (const QUrl& url, d->m_providers.keys()) {
        if (url.isParentOf(reply->url())) {
            baseUrl = url;
            break;
        }
    }

    qDebug() << "ProviderManager::authenticate" << baseUrl;

    QString user;
    QString password;
    if (auth->user().isEmpty() && auth->password().isEmpty()) {
        if (d->m_internals->hasCredentials(baseUrl)) {
            if (d->m_internals->loadCredentials(baseUrl, user, password)) {
                qDebug() << "ProviderManager::authenticate: loading authentication";
                auth->setUser(user);
                auth->setPassword(password);
                return;
            }
        }
    }

    if (!d->m_authenticationSuppressed && d->m_internals->askForCredentials(baseUrl, user, password)) {
        qDebug() << "ProviderManager::authenticate: asking internals for new credentials";
        //auth->setUser(user);
        //auth->setPassword(password);
        return;
    }

    qDebug() << "ProviderManager::authenticate: No authentication credentials provided, aborting." << reply->url().toString();
    emit authenticationCredentialsMissing(d->m_providers.value(baseUrl));
    reply->abort();
}


void ProviderManager::proxyAuthenticationRequired(const QNetworkProxy& proxy, QAuthenticator* authenticator)
{
}


void ProviderManager::initNetworkAccesssManager()
{
    connect(d->m_internals->nam(), SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)), this, SLOT(authenticate(QNetworkReply*, QAuthenticator*)));
    connect(d->m_internals->nam(), SIGNAL(proxyAuthenticationRequired(QNetworkProxy, QAuthenticator*)), this, SLOT(proxyAuthenticationRequired(QNetworkProxy, QAuthenticator*)));
}


#include "providermanager.moc"
