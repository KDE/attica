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

#ifndef ATTICA_QTINTERNALS_H
#define ATTICA_QTINTERNALS_H

#include "internals.h"

#include <QtNetwork/QNetworkAccessManager>


namespace Attica {

class QtInternals : public Attica::Internals
{
public:
    virtual QList<QUrl> getDefaultProviderFiles() const;
    virtual QNetworkReply* post(const QNetworkRequest& request, const QByteArray& data);
    virtual QNetworkReply* post(const QNetworkRequest& request, QIODevice* data);
    virtual QNetworkReply* get(const QNetworkRequest& request);
    virtual bool saveCredentials(const QUrl& baseUrl, const QString& user, const QString& password);
    virtual bool loadCredentials(const QUrl& baseUrl, QString& user, QString& password);
    virtual QNetworkAccessManager* nam();

private:
    QNetworkAccessManager m_qnam;
};

}


#endif
