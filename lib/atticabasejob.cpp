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

#include "atticabasejob.h"

#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtNetwork/QNetworkReply>

#include "internals.h"




using namespace Attica;


BaseJob::Metadata::Metadata()
{
    // values that make sense for single item jobs where these are not set usually
    totalItems = 1;
    itemsPerPage = 1;
    statusCode = 0;
}

class BaseJob::Private
{
public:
    Metadata m_metadata;
    QSharedPointer<Internals> m_internals;
    QNetworkReply* m_reply;

    Private(QSharedPointer<Internals> internals)
        : m_internals(internals), m_reply(0)
    {
    }
};

BaseJob::BaseJob(const QSharedPointer<Internals>& internals)
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
    } else {
        // FIXME: Use more fine-grained error messages
        qWarning() << "Attica::BaseJob::dataFinished" << d->m_reply->readAll();
        d->m_metadata.statusString = QLatin1String("Network reply error");
        d->m_metadata.statusCode = -1;
    }
    emit finished(this);

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


Internals* BaseJob::internals()
{
    return d->m_internals.data();
}


BaseJob::Metadata BaseJob::metadata() const
{
    return d->m_metadata;
}

void BaseJob::setMetadata(const Attica::BaseJob::Metadata& data) const
{
    d->m_metadata = data;
}


int BaseJob::statusCode() const
{
    return d->m_metadata.statusCode;
}

/*
void BaseJob::setError(int errorCode) {
    d->m_metadata.statusCode = errorCode;
}
*/

QString BaseJob::statusString() const
{
    return d->m_metadata.message;
}
/*
void BaseJob::setErrorString(const QString& errorText) {
    d->m_metadata.message = errorText;
}
*/

#include "atticabasejob.moc"
