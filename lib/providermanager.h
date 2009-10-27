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

#ifndef ATTICA_PROVIDERMANAGER_H
#define ATTICA_PROVIDERMANAGER_H

#include <QtCore/QUrl>

#include "provider.h"
#include "atticaclient_export.h"

namespace Attica {

class ATTICA_EXPORT ProviderManager : public QObject
{
    Q_OBJECT

public:
    ProviderManager();
    ~ProviderManager();
    
    /** 
     * Load available providers from configuration
     */
    void loadDefaultProviders();

    void clear();
    void addProviderFromXml(const QString& providerXml);
    void addProviderFile(const QUrl& file);
    void removeProviderFile(const QUrl& file);
    QList<QUrl> providerFiles() const;

    QList<Provider> providers() const;
    bool contains(const QString& provider) const;
    Provider providerByUrl(const QUrl& url) const;

Q_SIGNALS:
    void providersChanged();

private Q_SLOTS:
    void fileFinished(const QString& url);
    void authenticate(QNetworkReply*, QAuthenticator*);
    void proxyAuthenticationRequired(const QNetworkProxy& proxy, QAuthenticator* authenticator);
    void init();

private:
    ProviderManager(const ProviderManager& other);
    ProviderManager& operator=(const ProviderManager& other);

    void initNetworkAccesssManager();
    Internals* loadInternals();

    void parseProviderFile(const QString& xmlString, const QString& url);

    class Private;
    Private* const d;
};

}


#endif
