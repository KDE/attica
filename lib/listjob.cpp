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

#include "listjob.h"

#include <QDebug>
#include <QXmlStreamReader>

using namespace Attica;


template <class T>
ListJob<T>::ListJob(QSharedPointer<QNetworkAccessManager> nam, const QNetworkRequest& request): GetJob(nam, request)
{
}

template <class T>
typename T::List ListJob<T>::itemList() const
{
    return m_itemList;
}

template <class T>
ListJobMetadata ListJob<T>::metadata() const
{
    return m_metadata;
}

template <class T>
void ListJob<T>::parse(const QString& xml)
{
    typename T::Parser parser;
    m_itemList = typename T::Parser().parseList(xml);
    m_metadata = parser.metadata();
    if (m_metadata.statusCode != 100) {
        setError(m_metadata.statusCode);
    }
}
