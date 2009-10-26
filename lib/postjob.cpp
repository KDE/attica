/*
    This file is part of KDE.

    Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>

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

#include "postjob.h"

#include <QXmlStreamReader>
#include <QDebug>

#include <QtNetwork/QNetworkAccessManager>

#include "internals.h"


using namespace Attica;


PostJob::PostJob(const QSharedPointer<Internals>& internals, const QNetworkRequest& request, QIODevice* iodevice)
    : BaseJob(internals), m_ioDevice(iodevice), m_request(request)
{
}

Attica::PostJob::PostJob(const QSharedPointer<Internals>& internals, const QNetworkRequest& request, const QByteArray& byteArray)
    : BaseJob(internals), m_ioDevice(0) , m_byteArray(byteArray), m_request(request)
{
}

PostJob::PostJob(const QSharedPointer<Internals>& internals, const QNetworkRequest& request, const StringMap& parameters)
    : BaseJob(internals), m_ioDevice(0), m_request(request)
{
    // Create post data
    int j = 0;
    for(StringMap::const_iterator i = parameters.begin(); i != parameters.end(); ++i) {
        if (j++ > 0) {
            m_byteArray.append('&');
        }
        m_byteArray.append(QUrl::toPercentEncoding(i.key()));
        m_byteArray.append('=');
        m_byteArray.append(QUrl::toPercentEncoding(i.value()));
    }
}

QNetworkReply* PostJob::executeRequest()
{
    if (m_ioDevice) {
        return internals()->post(m_request, m_ioDevice);
    } else {
        return internals()->post(m_request, m_byteArray);
    }
}


void PostJob::parse(const QString& )
{
}


#include "postjob.moc"
