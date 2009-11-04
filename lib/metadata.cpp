/*
    This file is part of KDE.

    Copyright (c) 2009 Frederik Gladhorn <gladhorn@kde.org>

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

#include "metadata.h"

#include <QtCore/QSharedData>

using namespace Attica;

class Metadata::Private :public QSharedData
{
public:
    /// The status of the job, for example "Ok"
    QString statusString;
    /// The status as int, for easier interpretation.
    /// 100 means "Ok", for other codes refer to http://www.freedesktop.org/wiki/Specifications/open-collaboration-services
    int statusCode;

    /// An optional additional message from the server
    QString message;

    /// The number of items returned by this job (only relevant for list jobs)
    int totalItems;
    /// The number of items per page the server was asked for
    int itemsPerPage;

    Private() {
        // values that make sense for single item jobs where these are not set usually
        totalItems = 1;
        itemsPerPage = 1;
        statusCode = 0;
    }
};

Metadata::Metadata()
    :d(new Private)
{
}

Metadata::~Metadata()
{
}

Metadata::Metadata(const Attica::Metadata& other)
    :d(other.d)
{
}

Metadata& Metadata::operator=(const Attica::Metadata& other)
{
    d = other.d;
    return *this;
}


QString Metadata::message()
{
    return d->message;
}

void Metadata::setMessage(const QString& message)
{
    d->message = message;
}

int Metadata::statusCode() const
{
    return d->statusCode;
}

void Metadata::setStatusCode(int code)
{
    d->statusCode = code;
}

QString Metadata::statusString() const
{
    return d->statusString;
}

void Metadata::setStatusString(const QString& status)
{
    d->statusString = status;
}

int Metadata::totalItems()
{
    return d->totalItems;
}

void Metadata::setTotalItems(int items)
{
    d->totalItems = items;
}

int Metadata::itemsPerPage()
{
    return d->itemsPerPage;
}

void Metadata::setItemsPerPage(int itemsPerPage)
{
    d->itemsPerPage = itemsPerPage;
}

