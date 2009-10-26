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
    return false;
}


bool QtInternals::loadCredentials(const QUrl& baseUrl, QString& user, QString& password)
{
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
