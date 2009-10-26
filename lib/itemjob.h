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
#ifndef ATTICA_ITEMJOB_H
#define ATTICA_ITEMJOB_H

#include "atticaclient_export.h"
#include "getjob.h"
#include "postjob.h"

namespace Attica {

template <class T>
class ATTICA_EXPORT ItemJob : public GetJob
{
public:
    ItemJob(const QSharedPointer<Internals>& internals, const QNetworkRequest& request);
    T result() const;

private:
    virtual void parse(const QString& xml);
    T m_item;
};


template <class T>
class ATTICA_EXPORT ItemPostJob : public PostJob
{
public:
    ItemPostJob(const QSharedPointer<Internals>& internals, const QNetworkRequest& request, QIODevice * data);
    ItemPostJob(const QSharedPointer<Internals>& internals, const QNetworkRequest& request, const StringMap& parameters = StringMap());

    T result() const;

private:
    virtual void parse(const QString& xml);
    T m_item;
};

}


#endif
