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

#include <QUrl>
#include <QNetworkReply>

#include "provider.h"
#include "attica_export.h"

namespace Attica
{

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
 * \section basicuse Basic Use
 *
 * See addProviderFileToDefaultProviders(const QUrl &url) for an example of
 * what the provider file sohuld look like. You can add providers to the
 * ProviderManager as either raw XML data using addProviderFromXml(const QString &providerXml),
 * or from a file somewhere on the system through addProviderFile(const QUrl &file),
 * or you can simply load the default providers provided by your system
 * (which generally means KDE's provider opendesktop.org).
 *
 * Importantly, to be able to detect when the ProviderManager is ready to
 * manage things, before initialising it you will want to connect to the
 * providerAdded(const Attica::Provider &provider) signal, which is fired
 * every time a new provider is added to the manager.
 *
 * If you manually add all providers from XML, you can expect this to happen
 * immediately. This means that once you have added your providers that way,
 * you can access them through the providers() function, which returns
 * a list of all loaded Providers.
 *
 * Once you have loaded a Provider, you can use its functions to access the
 * services offered by that provider.
 */
class ATTICA_EXPORT ProviderManager : public QObject
{
    Q_OBJECT

public:

    enum ProviderFlag {
        NoFlags = 0x0,
        DisablePlugins = 0x1
    };
    Q_DECLARE_FLAGS(ProviderFlags, ProviderFlag)

    ProviderManager(const ProviderFlags &flags = NoFlags);
    ~ProviderManager();

    /**
     * Load available providers from configuration
     */
    void loadDefaultProviders();

    /**
     * The list of provider files that get loaded by loadDefaultProviders.
     * Each of these files can contain multiple providers.
     * @return list of provider file urls
     */
    QList<QUrl> defaultProviderFiles();

    /**
    * Add a provider file to the default providers (xml that contains provider descriptions).
      Provider files contain information about each provider:
     <pre>
     <providers>
     <provider>
        <id>opendesktop</id>
        <location>https://api.opendesktop.org/v1/</location>
        <name>openDesktop.org</name>
        <icon></icon>
        <termsofuse>https://opendesktop.org/terms/</termsofuse>
        <register>https://opendesktop.org/usermanager/new.php</register>
        <services>
            <person ocsversion="1.3" />
            <friend ocsversion="1.3" />
            <message ocsversion="1.3" />
            <activity ocsversion="1.3" />
            <content ocsversion="1.3" />
            <fan ocsversion="1.3" />
            <knowledgebase ocsversion="1.3" />
            <event ocsversion="1.3" />
        </services>
     </provider>
     </providers>
     </pre>
    * @param url the url of the provider file
    */
    void addProviderFileToDefaultProviders(const QUrl &url);

    void removeProviderFileFromDefaultProviders(const QUrl &url);

    /**
     * Suppresses the authentication, so that the application can take care of authenticating itself
     */
    void setAuthenticationSuppressed(bool suppressed);

    /**
     * Remove all providers and provider files that have been loaded
     */
    void clear();

    /**
     * Parse a xml file containing a provider description
     */
    void addProviderFromXml(const QString &providerXml);
    void addProviderFile(const QUrl &file);
    QList<QUrl> providerFiles() const;

    /**
     * @returns all loaded providers
     */
    QList<Provider> providers() const;

#if ATTICA_ENABLE_DEPRECATED_SINCE(5, 23)
    /**
     * @deprecated Since 5.23, use contains(const QUrl&)
     */
    ATTICA_DEPRECATED_VERSION(5, 23, "Use ProviderManager::contains(const QUrl&)")
    bool contains(const QString &provider) const;
#endif

    /**
     * @returns whether there's a provider with base url @p provider
     */
    bool contains(const QUrl &provider) const;

    /**
     * @returns the provider with @p url base url.
     */
    Provider providerByUrl(const QUrl &url) const;

    /**
     * @returns the provider for a given provider @p url.
     */
    Provider providerFor(const QUrl &url) const;

Q_SIGNALS:
    void providerAdded(const Attica::Provider &provider);
    void defaultProvidersLoaded();
    void authenticationCredentialsMissing(const Provider &provider);
    void failedToLoad(const QUrl& provider, QNetworkReply::NetworkError error);

private Q_SLOTS:
    void fileFinished(const QString &url);
    void authenticate(QNetworkReply *, QAuthenticator *);
    void proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void slotLoadDefaultProvidersInternal();

private:
    ProviderManager(const ProviderManager &other);
    ProviderManager &operator=(const ProviderManager &other);

    void initNetworkAccesssManager();
    PlatformDependent *loadPlatformDependent(const ProviderFlags &flags);

    void parseProviderFile(const QString &xmlString, const QUrl &url);

    class Private;
    Private *const d;
};

}

Q_DECLARE_OPERATORS_FOR_FLAGS(Attica::ProviderManager::ProviderFlags)

#endif
