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

class BaseJob::Private
{
public:
    int m_error;
    QString m_errorString;
    QSharedPointer<Internals> m_internals;
    QNetworkReply* m_reply;

    Private(QSharedPointer<Internals> internals)
        : m_error(0), m_internals(internals), m_reply(0)
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


int BaseJob::error() const {
    return d->m_error;
}


QString BaseJob::errorString() const {
    return d->m_errorString;
}


void BaseJob::dataFinished()
{
    if (d->m_reply->error() == QNetworkReply::NoError) {
        QByteArray data = d->m_reply->readAll();
        qDebug() << data;
        parse(data);
    } else {
        // FIXME: Use more fine-grained error messages
        setError(1);
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


QNetworkAccessManager* BaseJob::nam()
{
    return d->m_internals->nam();
}


void BaseJob::setError(int errorCode) {
    d->m_error = errorCode;
}


void BaseJob::setErrorString(const QString& errorText) {
    d->m_errorString = errorText;
}


#include "atticabasejob.moc"
