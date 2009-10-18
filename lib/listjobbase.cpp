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

#include "listjobbase.h"

#include <QNetworkReply>

#include <KIO/Job>


using namespace Attica;


ListJobBase::ListJobBase(QNetworkReply* data, QObject* parent)
    :QObject(parent), m_data(data)
{
    connect(m_data, SIGNAL(finished()), this, SLOT(dataFinished()));
}


void ListJobBase::dataFinished()
{
    parse(QString::fromUtf8(m_data->readAll()));

    // TODO: check if data should be deleted here
    delete m_data;
    emit finished();
}


/*
void ListJobBase::slotJobResult(KJob* job)
{
    if (job->error()) {
        setError(job->error());
        setErrorText(job->errorText());
    
        emitResult();
    } else {
        parse(QString::fromUtf8(m_data.data()));

        emitResult();
    }
}
*/

#include "listjobbase.moc"
