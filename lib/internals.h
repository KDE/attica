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

#ifndef ATTICA_INTERNALS_H
#define ATTICA_INTERNALS_H

#include <QtCore/QList>
#include <QtCore/QtPlugin>


class QByteArray;
class QIODevice;
class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;
class QString;
class QUrl;

namespace Attica {

class Internals
{
public:
    virtual ~Internals();
    virtual QList<QUrl> getDefaultProviderFiles() const = 0;
    virtual bool loadCredentials(const QUrl& baseUrl, QString& user, QString& password) = 0;
    virtual bool saveCredentials(const QUrl& baseUrl, const QString& user, const QString& password) = 0;
    virtual QNetworkReply* get(const QNetworkRequest& request) = 0;
    virtual QNetworkReply* post(const QNetworkRequest& request, QIODevice* data) = 0;
    virtual QNetworkReply* post(const QNetworkRequest& request, const QByteArray& data) = 0;
    virtual QNetworkAccessManager* nam() = 0;
};

}

Q_DECLARE_INTERFACE(Attica::Internals, "org.kde.Attica.Internals/1.0")


#endif
