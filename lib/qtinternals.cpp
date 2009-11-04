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

#include "qtinternals.h"

#include <QtCore/QUrl>


using namespace Attica;

QNetworkReply* QtInternals::post(const QNetworkRequest& request, const QByteArray& data)
{
    return m_qnam.post(request, data);
}


QNetworkReply* QtInternals::post(const QNetworkRequest& request, QIODevice* data)
{
    return m_qnam.post(request, data);
}


QNetworkReply* QtInternals::get(const QNetworkRequest& request)
{
    return m_qnam.get(request);
}


bool QtInternals::saveCredentials(const QUrl& baseUrl, const QString& user, const QString& password)
{
    Q_UNUSED(baseUrl)
    Q_UNUSED(user)
    Q_UNUSED(password)
    return false;
}


bool QtInternals::loadCredentials(const QUrl& baseUrl, QString& user, QString& password)
{
    Q_UNUSED(baseUrl)
    Q_UNUSED(user)
    Q_UNUSED(password)
    return false;
}


QList<QUrl> Attica::QtInternals::getDefaultProviderFiles() const
{
    return QList<QUrl>();
}


QNetworkAccessManager* Attica::QtInternals::nam()
{
    return &m_qnam;
}
