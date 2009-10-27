/*
    This file is part of KDE.

    Copyright (c) 2009 Eckhart Wörner <ewoerner@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
    USA.
*/

#include "kdeinternals.h"

#include <QtCore/QDebug>

#include <KConfigGroup>
#include <KWallet/Wallet>


using namespace Attica;

KDEInternals::KDEInternals()
    : m_config(KSharedConfig::openConfig("atticarc")), m_qnam(0), m_wallet(0)
{
}


QNetworkReply* KDEInternals::post(const QNetworkRequest& request, const QByteArray& data)
{
    return m_qnam.post(request, data);
}


QNetworkReply* KDEInternals::post(const QNetworkRequest& request, QIODevice* data) {
    return m_qnam.post(request, data);
}


QNetworkReply* KDEInternals::get(const QNetworkRequest& request) {
    return m_qnam.get(request);
}


bool KDEInternals::saveCredentials(const QUrl& baseUrl, const QString& user, const QString& password) {
    QString networkWallet = KWallet::Wallet::NetworkWallet();
    if (!m_wallet) {
        m_wallet = KWallet::Wallet::openWallet(networkWallet, 0);
    }
    if (!m_wallet) {
        return false;
    }
    m_wallet->createFolder("Attica");
    if (!m_wallet->setFolder("Attica")) {
        return false;
    }
    QMap<QString, QString> entries;
    entries.insert("user", user);
    entries.insert("password", password);

    return !m_wallet->writeMap(baseUrl.toString(), entries);
}


bool KDEInternals::loadCredentials(const QUrl& baseUrl, QString& user, QString& password) {
    QString networkWallet = KWallet::Wallet::NetworkWallet();
    if (KWallet::Wallet::keyDoesNotExist(networkWallet, "Attica", baseUrl.toString())) {
        return false;
    }
    if (!m_wallet) {
        m_wallet = KWallet::Wallet::openWallet(networkWallet, 0);
    }
    if (!m_wallet || !m_wallet->setFolder("Attica")) {
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


QList<QUrl> KDEInternals::getDefaultProviderFiles() const {
    KConfigGroup group(m_config, "General");
    QStringList pathStrings = group.readPathEntry("providerFiles", QStringList("http://download.kde.org/ocs/providers.xml"));
    QList<QUrl> paths;
    foreach (const QString& pathString, pathStrings) {
        paths.append(QUrl(pathString));
    }
    qDebug() << "Loaded paths from config:" << paths;
    return paths;
}


QNetworkAccessManager* Attica::KDEInternals::nam() {
    return &m_qnam;
}


Q_EXPORT_PLUGIN2(attica_kde, Attica::KDEInternals)


#include "kdeinternals.moc"
