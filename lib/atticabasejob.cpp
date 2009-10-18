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


using namespace Attica;

class BaseJob::Private
{
public:
    QNetworkAccessManager* m_nam;
    QNetworkReply* m_reply;

    Private(QNetworkAccessManager* nam): m_nam(nam), m_reply(0)
    {
    }
};


BaseJob::BaseJob(QNetworkAccessManager* nam)
    : d(new Private(nam))
{
}


BaseJob::~BaseJob()
{
    delete d;
}


void BaseJob::dataFinished()
{
    qDebug() << "DataFinished";
    QByteArray data = d->m_reply->readAll();
    qDebug() << data;

    parse(data);
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
    return d->m_nam;
}


#include "atticabasejob.moc"
