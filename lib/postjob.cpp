/*
    This file is part of KDE.

    Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>

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

#include "postjob.h"
#include <QtNetwork/QNetworkAccessManager>

#include "platformdependent.h"
#include "parserfactory.h"


using namespace Attica;


PostJob::PostJob(PlatformDependent* internals, const QNetworkRequest& request, QIODevice* iodevice)
    : BaseJob(internals), m_ioDevice(iodevice), m_request(request)
{
}

Attica::PostJob::PostJob(PlatformDependent* internals, const QNetworkRequest& request, const QByteArray& byteArray)
    : BaseJob(internals), m_ioDevice(0) , m_byteArray(byteArray), m_request(request)
{
}

PostJob::PostJob(PlatformDependent* internals, const QNetworkRequest& request, const StringMap& parameters)
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


void PostJob::parse(const QString& data)
{
    StatusParser* parser = ParserFactory::self()->getStatusParser();
    parser->parse(data);
    setMetadata( parser->metadata() );
    delete parser;
}


#include "postjob.moc"
