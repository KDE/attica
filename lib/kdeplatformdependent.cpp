/*
    This file is part of KDE.

    Copyright (c) 2009 Eckhart Wörner <ewoerner@kde.org>

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

#include "kdeplatformdependent.h"

#include <QtCore/QDebug>

#include <KConfigGroup>
#include <KWallet/Wallet>


using namespace Attica;

KdePlatformDependent::KdePlatformDependent()
    : m_config(KSharedConfig::openConfig("atticarc")), m_qnam(0), m_wallet(0)
{
    QString networkWallet = KWallet::Wallet::NetworkWallet();
    m_wallet = KWallet::Wallet::openWallet(networkWallet, 0);
    m_wallet->createFolder("Attica");
    m_wallet->setFolder("Attica");
}


QNetworkReply* KdePlatformDependent::post(const QNetworkRequest& request, const QByteArray& data)
{
    return m_qnam.post(request, data);
}


QNetworkReply* KdePlatformDependent::post(const QNetworkRequest& request, QIODevice* data) {
    return m_qnam.post(request, data);
}


QNetworkReply* KdePlatformDependent::get(const QNetworkRequest& request) {
    return m_qnam.get(request);
}


bool KdePlatformDependent::saveCredentials(const QUrl& baseUrl, const QString& user, const QString& password) {
    if (!m_wallet) {
        return false;
    }
    QMap<QString, QString> entries;
    entries.insert("user", user);
    entries.insert("password", password);

    return !m_wallet->writeMap(baseUrl.toString(), entries);
}


bool KdePlatformDependent::loadCredentials(const QUrl& baseUrl, QString& user, QString& password) {
    if (!m_wallet) {
        return false;
    }
    QMap<QString, QString> entries;
    if (m_wallet->readMap(baseUrl.toString(), entries)) {
        return false;
    }
    user = entries.value("user");
    password = entries.value("password");

    return true;
}


QList<QUrl> KdePlatformDependent::getDefaultProviderFiles() const {
    KConfigGroup group(m_config, "General");
    QStringList pathStrings = group.readPathEntry("providerFiles", QStringList("http://download.kde.org/ocs/providers.xml"));
    QList<QUrl> paths;
    foreach (const QString& pathString, pathStrings) {
        paths.append(QUrl(pathString));
    }
    qDebug() << "Loaded paths from config:" << paths;
    return paths;
}


QNetworkAccessManager* Attica::KdePlatformDependent::nam() {
    return &m_qnam;
}


Q_EXPORT_PLUGIN2(attica_kde, Attica::KdePlatformDependent)


#include "kdeplatformdependent.moc"
