/*
    This file is part of KDE.
    
    Copyright (c) 2009 Eckhart Wörner <ewoerner@kde.org>
    Copyright (c) 2009 Frederik Gladhorn <gladhorn@kde.org>
    
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License version 2 as published by the Free Software Foundation.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "providermanager.h"

#include <QtCore/QDebug>
#include <QtCore/QPluginLoader>
#include <QtCore/QSet>
#include <QtCore/QSharedPointer>
#include <QtCore/QTimer>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkReply>
#include <QtXml/QXmlStreamReader>

#include "internals.h"
#include "qtinternals.h"


using namespace Attica;

uint qHash(const QUrl& key) {
    return qHash(key.toString());
}

class ProviderManager::Private {
public:
    QSharedPointer<Internals> m_internals;
    QHash<QUrl, Provider> m_providers;
    QHash<QUrl, QList<QString> > m_providerFiles;

    Private()
        : m_internals(0)
    {
    }
    ~Private()
    {
    }
};


Internals* ProviderManager::loadInternals() {
    QPluginLoader loader("attica_kde.so");
    QObject* plugin = loader.instance();
    if (plugin) {
        Internals* kdeInternals = qobject_cast<Internals*>(plugin);
        if (kdeInternals) {
            qDebug() << "Using Attica with KDE support";
            return kdeInternals;
        }
    }
    qDebug() << "Using Attica without KDE support";
    return new QtInternals;
}


ProviderManager::ProviderManager()
    : d(new Private)
{
    d->m_internals = QSharedPointer<Internals>(loadInternals());
    connect(d->m_internals->nam(), SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), SLOT(authenticate(QNetworkReply*,QAuthenticator*)));
}

void ProviderManager::loadDefaultProviders()
{
    QTimer::singleShot(0, this, SLOT(init()));
}


void ProviderManager::clear() {
    d->m_providerFiles.clear();
    d->m_providers.clear();
}


void ProviderManager::init() {
    QUrl url("http://api.opendesktop.dev.hive01.com/v1/");
    d->m_providers.insert(url, Provider(d->m_internals, url, "OpenDesktop.org", QUrl()));
    emit providersChanged();
}

ProviderManager::~ProviderManager()
{
    delete d;
}

void ProviderManager::addProviderFile(const QUrl& file)
{
    // TODO: use qnam::get to get the file and then parse it
    
    // For local files:
    /*
    QFile file(localFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "ProviderManager::addProviderFile: could not open provider file: " << url.toString();
        return;
    }
    addProviderFromXml(file.readAll());
    file.close();
    */
}

void ProviderManager::addProviderFromXml(const QString& providerXml)
{
    parseProviderFile(providerXml);
}

void ProviderManager::removeProviderFile(const QUrl& file) {
    // FIXME: Implement
}

void ProviderManager::parseProviderFile(const QString& xmlString)
{
    qDebug() << "parseProviderFile" << xmlString;
    QXmlStreamReader xml(xmlString);
    while (!xml.atEnd() && xml.readNext()) {
        if (xml.isStartElement() && xml.name() == "provider") {
            QString baseUrl;
            QString name;
            QUrl icon;
            while (!xml.atEnd() && xml.readNext()) {
                if (xml.isStartElement())
                {
                    qDebug() << "parseProviderFile" << xml.name();
                    if (xml.name() == "location") {
                        baseUrl = xml.readElementText();
                        qDebug() << "reading provider with URL: " << baseUrl;
                    }
                    if (xml.name() == "name") {
                        name = xml.readElementText();
                    }
                    if (xml.name() == "icon") {
                        icon = QUrl(xml.readElementText());
                    }
                }         
            }
            if (!baseUrl.isEmpty()) {
                d->m_providers.insert(baseUrl, Provider(d->m_internals, QUrl(baseUrl), name, icon));
                emit providersChanged();
            }
        }
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
    
    QString user;
    QString password;
    if (auth->user().isEmpty() && auth->password().isEmpty()) {
        if (d->m_internals->loadCredentials(baseUrl, user, password)) {
            auth->setUser(user);
            auth->setPassword(password);
            return;
        }
    } else {
        qDebug() << "ProviderManager::authenticate: We already authenticated once, not trying forever...";
    }
    
    reply->abort();
}


void ProviderManager::proxyAuthenticationRequired(const QNetworkProxy& proxy, QAuthenticator* authenticator)
{
#ifdef ATTICA_USE_KDE
    // FIXME
#endif

}


void ProviderManager::initNetworkAccesssManager()
{
    connect(d->m_internals->nam(), SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)), this, SLOT(authenticate(QNetworkReply*, QAuthenticator*)));
    connect(d->m_internals->nam(), SIGNAL(proxyAuthenticationRequired(QNetworkProxy, QAuthenticator*)), this, SLOT(proxyAuthenticationRequired(QNetworkProxy, QAuthenticator*)));
}


#include "providermanager.moc"
