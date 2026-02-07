/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2009 Eckhart Wörner <ewoerner@kde.org>
    SPDX-FileCopyrightText: 2011 Laszlo Papp <djszapi@archlinux.us>
    SPDX-FileCopyrightText: 2012 Jeff Mitchell <mitchell@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#include "qtplatformdependent_p.h"

#include <QDebug>
#include <QStringList>
#include <QUrl>

using namespace Attica;

QtPlatformDependent::QtPlatformDependent()
{
    QMetaObject::invokeMethod(this, &QtPlatformDependent::readyChanged, Qt::QueuedConnection);
}

QtPlatformDependent::~QtPlatformDependent()
{
}

QNetworkAccessManager *QtPlatformDependent::nam()
{
    static thread_local QNetworkAccessManager threadLocalManager;
    return &threadLocalManager;
}

// TODO actually save and restore providers!
QList<QUrl> Attica::QtPlatformDependent::getDefaultProviderFiles() const
{
    // Return the defaultiest default provider (since that's what our documentation says we'll do)
    return QList<QUrl>{QUrl(QStringLiteral("https://autoconfig.kde.org/ocs/providers.xml"))};
}

void QtPlatformDependent::addDefaultProviderFile(const QUrl &)
{
    qWarning() << "attica-qt does not support default providers yet";
}

void QtPlatformDependent::removeDefaultProviderFile(const QUrl &)
{
}

void QtPlatformDependent::enableProvider(const QUrl &baseUrl, bool enabled) const
{
    Q_UNUSED(baseUrl)
    Q_UNUSED(enabled)
    qWarning() << "attica-qt does not support disabling of providers yet";
}

bool QtPlatformDependent::isEnabled(const QUrl &baseUrl) const
{
    Q_UNUSED(baseUrl)
    return true;
}

QNetworkReply *QtPlatformDependent::post(const QNetworkRequest &request, const QByteArray &data)
{
    return nam()->post(request, data);
}

QNetworkReply *QtPlatformDependent::post(const QNetworkRequest &request, QIODevice *data)
{
    return nam()->post(request, data);
}

QNetworkReply *QtPlatformDependent::put(const QNetworkRequest &request, const QByteArray &data)
{
    return nam()->put(request, data);
}

QNetworkReply *QtPlatformDependent::put(const QNetworkRequest &request, QIODevice *data)
{
    return nam()->put(request, data);
}

QNetworkReply *QtPlatformDependent::get(const QNetworkRequest &request)
{
    return nam()->get(request);
}

QNetworkReply *QtPlatformDependent::deleteResource(const QNetworkRequest &request)
{
    return nam()->deleteResource(request);
}

bool QtPlatformDependent::hasCredentials(const QUrl &baseUrl) const
{
    return m_passwords.contains(baseUrl.toString());
}

bool QtPlatformDependent::saveCredentials(const QUrl &baseUrl, const QString &user, const QString &password)
{
    m_passwords[baseUrl.toString()] = QPair<QString, QString>(user, password);
    return true;
}

bool QtPlatformDependent::loadCredentials(const QUrl &baseUrl, QString &user, QString &password)
{
    if (!hasCredentials(baseUrl)) {
        return false;
    }
    QPair<QString, QString> userPass = m_passwords.value(baseUrl.toString());
    user = userPass.first;
    password = userPass.second;
    return true;
}

bool Attica::QtPlatformDependent::askForCredentials(const QUrl &baseUrl, QString &user, QString &password)
{
    Q_UNUSED(baseUrl)
    Q_UNUSED(user)
    Q_UNUSED(password)
    return false;
}

bool Attica::QtPlatformDependent::isReady()
{
    return true;
}
