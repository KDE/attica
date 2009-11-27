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

#ifndef ATTICA_PROVIDERMANAGER_H
#define ATTICA_PROVIDERMANAGER_H

#include <QtCore/QUrl>

#include "provider.h"
#include "atticaclient_export.h"

namespace Attica {


/**
 * Attica ProviderManager
 *
 * This class is the primary access to Attica's functions.
 * Use the ProviderManager to load Open Collaboration Service providers,
 * either the default system ones, or from XML or custom locations.
 *
 * \section providerfiles Provider Files
 * Provider files are defined here:
 * http://www.freedesktop.org/wiki/Specifications/open-collaboration-services
 *
 * <pre>
   provider file example
 * </pre>
 *
 * Once you have loaded a Provider, use its functions to access the service.
 */
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

    /**
     * Suppresses the authentication, so that the application can take care of authenticating itself
     */
    void setAuthenticationSuppressed(bool suppressed);

    /**
     * Remove all providers that have been loaded
     */
    void clear();

    /**
     * Parse a xml file containing a provider description
     */
    void addProviderFromXml(const QString& providerXml);
    void addProviderFile(const QUrl& file);
    QList<QUrl> providerFiles() const;

    QList<Provider> providers() const;
    bool contains(const QString& provider) const;
    Provider providerByUrl(const QUrl& url) const;

Q_SIGNALS:
    void providerAdded(const Attica::Provider& provider);
    void defaultProvidersLoaded();
    void authenticationCredentialsMissing(const Provider& provider);

private Q_SLOTS:
    void fileFinished(const QString& url);
    void authenticate(QNetworkReply*, QAuthenticator*);
    void proxyAuthenticationRequired(const QNetworkProxy& proxy, QAuthenticator* authenticator);
    void init();

private:
    ProviderManager(const ProviderManager& other);
    ProviderManager& operator=(const ProviderManager& other);

    void initNetworkAccesssManager();
    PlatformDependent* loadPlatformDependent();

    void parseProviderFile(const QString& xmlString, const QString& url);

    class Private;
    Private* const d;
};

}


#endif
