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

#include "atticabasejob.h"

#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtNetwork/QNetworkReply>

#include "platformdependent.h"


using namespace Attica;

class BaseJob::Private
{
public:
    Metadata m_metadata;
    QSharedPointer<PlatformDependent> m_internals;
    QNetworkReply* m_reply;

    Private(QSharedPointer<PlatformDependent> internals)
        : m_internals(internals), m_reply(0)
    {
    }
};

BaseJob::BaseJob(const QSharedPointer<PlatformDependent>& internals)
    : d(new Private(internals))
{
}


BaseJob::~BaseJob()
{
    delete d;
}

void BaseJob::dataFinished()
{
    if (d->m_reply->error() == QNetworkReply::NoError) {
        QByteArray data = d->m_reply->readAll();
        //qDebug() << data;
        parse(QString::fromUtf8(data.constData()));
        if (d->m_metadata.statusCode() == 100) {
            d->m_metadata.setError(Metadata::NoError);
        } else {
            d->m_metadata.setError(Metadata::OcsError);
        }
    } else {
        d->m_metadata.setError(Metadata::NetworkError);
        d->m_metadata.setStatusCode(d->m_reply->error());
        d->m_metadata.setStatusString("Network error");
    }
    emit finished(this);

    d->m_reply->deleteLater();
    deleteLater();
}


void BaseJob::start()
{
    QTimer::singleShot(0, this, SLOT(doWork()));
}

void BaseJob::doWork()
{
    d->m_reply = executeRequest();
    connect(d->m_reply, SIGNAL(finished()), SLOT(dataFinished()));
}

void BaseJob::abort()
{
    if (d->m_reply) {
        d->m_reply->abort();
        d->m_reply->deleteLater();
    }
    deleteLater();
}

PlatformDependent* BaseJob::internals()
{
    return d->m_internals.data();
}


Metadata BaseJob::metadata() const
{
    return d->m_metadata;
}

void BaseJob::setMetadata(const Attica::Metadata& data) const
{
    d->m_metadata = data;
}

#include "atticabasejob.moc"
