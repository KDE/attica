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


void ListJobMetadata::parseMetadata(const QString& xmlString)
{
    QXmlStreamReader xml( xmlString );

    status.clear();
    message.clear();
    totalItems = 0;
    itemsPerPage = 0;

    while ( !xml.atEnd() ) {
        xml.readNext();
        if (xml.isStartElement() && xml.name() == "meta") {
            while ( !xml.atEnd() ) {
                xml.readNext();
                if (xml.isEndElement() && xml.name() == "meta") {
                    break;
                } else if (xml.isStartElement()) {
                    if (xml.name() == "status") {
                        status = xml.readElementText();
                    } else if (xml.name() == "message") {
                        message = xml.readElementText();
                    } else if (xml.name() == "totalitems") {
                        totalItems = xml.readElementText().toInt();
                    } else if (xml.name() == "itemsperpage") {
                        itemsPerPage = xml.readElementText().toInt();
                    }
                }
            }
            break;
        }
    }
}


template <class T>
ListJob<T>::ListJob(QNetworkAccessManager* nam, const QNetworkRequest& request): GetJob(nam, request)
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
    qDebug() << "Parsing metadata";
    m_metadata.parseMetadata(xml);
    qDebug() << "Parsing List";
    m_itemList = typename T::Parser().parseList(xml);
}
