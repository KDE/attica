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

#include "postjobstatus.h"


using namespace Attica;

class PostJobStatus::Private : public QSharedData {
    public:
        QString m_status;
        QString m_statusMessage;
        int m_statusCode;
        QString m_data;
};


PostJobStatus::PostJobStatus()
    : d(new Private)
{
}

PostJobStatus::PostJobStatus(const PostJobStatus& other)
    : d(other.d)
{
}

PostJobStatus& PostJobStatus::operator=(const PostJobStatus& other)
{
    d = other.d;
    return *this;
}

PostJobStatus::~PostJobStatus()
{
}


QString Attica::PostJobStatus::status()
{
    return d->m_status;
}

void PostJobStatus::setStatus(const QString& status)
{
    d->m_status = status;
}

int PostJobStatus::statusCode()
{
    return d->m_statusCode;
}

void PostJobStatus::setStatusCode(int statusCode)
{
    d->m_statusCode = statusCode;
}

QString PostJobStatus::statusMessage()
{
    return d->m_statusMessage;
}

void PostJobStatus::setStatusMessage(const QString& statusMessage)
{
    d->m_statusMessage = statusMessage;
}

QString PostJobStatus::data()
{
    return d->m_data;
}

void PostJobStatus::setData(const QString& data)
{
    d->m_data = data;
}

