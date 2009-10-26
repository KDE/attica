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

#include "itemjob.h"


using namespace Attica;

template <class T>
ItemJob<T>::ItemJob(QSharedPointer<QNetworkAccessManager> nam, const QNetworkRequest& request)
    : GetJob(nam, request)
{
}


template <class T>
void ItemJob<T>::parse(const QString& xml)
{
    typename T::Parser p;
    m_item = p.parse(xml);
}


template <class T>
T ItemJob<T>::result() const
{
    return m_item;
}



template <class T>
ItemPostJob<T>::ItemPostJob(QSharedPointer<QNetworkAccessManager> nam, const QNetworkRequest& request, QIODevice* data)
    : PostJob(nam, request, data)
{
}

template <class T>
ItemPostJob<T>::ItemPostJob(QSharedPointer<QNetworkAccessManager> nam, const QNetworkRequest& request, const StringMap& parameters)
    : PostJob(nam, request, parameters)
{
}

template <class T>
void ItemPostJob<T>::parse(const QString& xml)
{
    typename T::Parser p;
    m_item = p.parse(xml);
    if (p.metadata().statusCode != 100) {
        setError(p.metadata().statusCode);
    }
}

template <class T>
T ItemPostJob<T>::result() const
{
    return m_item;
}
