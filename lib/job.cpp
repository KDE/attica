/*
    This file is part of KDE.

    Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>
    Copyright (c) 2012 Felix Rohrbach <fxrh@gmx.de>

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

#include "job.h"

#include <QtCore/QDebug>
#include <QtCore/QIODevice>
#include <QtNetwork/QNetworkRequest>

#include "platformdependent.h"
#include "iparser.h"
#include "xmlparser.h"


using namespace Attica;

template <class T>
class Job<T>::Private
{
public:
    PlatformDependent *m_internals;
    const QNetworkRequest m_request;
    QIODevice *m_ioDevice;
    QByteArray m_byteArray;
    IParser<T> *m_parser;

    Private(PlatformDependent *internals, JobType jobType, ParserType parserType, const QNetworkRequest &request)
        : m_internals(internals), m_request(request), m_ioDevice(0), m_parser(0)
    {
    }
};

template <class T>
Job<T>::Job(PlatformDependent *internals, JobType jobType, ParserType parserType, const QNetworkRequest &request, QIODevice *data)
    : BasicJob(jobType, parserType)
    , d(new Private(internals, jobType, parserType, request))
{
    d->m_ioDevice = data;
}

template <class T>
Job<T>::Job(PlatformDependent *internals, JobType jobType, ParserType parserType, const QNetworkRequest &request, const StringMap &parameters)
    : BasicJob(jobType, parserType)
    , d(new Private(internals, jobType, parserType, request))
{
    // Create post data
    int j = 0;
    for(StringMap::const_iterator i = parameters.begin(); i != parameters.end(); ++i) {
        if (j++ > 0) {
            d->m_byteArray.append('&');
        }
        d->m_byteArray.append(QUrl::toPercentEncoding(i.key()));
        d->m_byteArray.append('=');
        d->m_byteArray.append(QUrl::toPercentEncoding(i.value()));
    }
}

template <class T>
Job<T>::Job(PlatformDependent *internals, JobType jobType, ParserType parserType, const QNetworkRequest &request, const QByteArray &data)
    : BasicJob(jobType, parserType)
    , d(new Private(internals, jobType, parserType, request))
{
    d->m_byteArray = data;
}

template <class T>
Job<T>::~Job()
{
    delete d;
}

template <class T>
T Job<T>::item() const
{
    return d->m_parser->item();
}

template <class T>
typename T::List Job<T>::itemList() const
{
    return d->m_parser->itemList();
}

template <class T>
QNetworkReply* Job<T>::executeRequest()
{
    switch (jobType()) {
    case Post:
        if (d->m_ioDevice) {
            return internals()->post(d->m_request, d->m_ioDevice);
        } else {
            return internals()->post(d->m_request, d->m_byteArray);
        }
        break;
    case Put:
        if (d->m_ioDevice) {
            return internals()->put(d->m_request, d->m_ioDevice);
        } else {
            return internals()->put(d->m_request, d->m_byteArray);
        }
        break;
    case Get:
        return internals()->get(d->m_request);
        break;
    case Delete:
        return internals()->deleteResource(d->m_request);
        break;
    }
}

template <class T>
void Job<T>::parse(const QString &data)
{
    switch (parserType()) {
    case Xml:
        d->m_parser = new XmlParser<T>();
        break;
    }
    d->m_parser->parse(data);
    setMetadata( d->m_parser->metadata() );
}

template <class T>
PlatformDependent* Job<T>::internals()
{
    return d->m_internals;
}

