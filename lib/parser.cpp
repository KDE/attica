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

#include "parser.h"
#include <QStringList>


using namespace Attica;


template <class T>
Parser<T>::~Parser()
{
}


template <class T>
T Parser<T>::parse(const QString& xmlString)
{
    QStringList elements = xmlElement();
    T item;

    QXmlStreamReader xml(xmlString);

    while (!xml.atEnd()) {
        xml.readNext();
        
        if (xml.isStartElement()) {
            if (xml.name() == "meta") {
                parseMetadataXml(xml);
            } else if (elements.contains(xml.name().toString())) {
                item = parseXml(xml);
            }
        }
    }

    return item;
}


template <class T>
typename T::List Parser<T>::parseList(const QString& xmlString)
{
    QStringList elements = xmlElement();
    typename T::List items;

    QXmlStreamReader xml( xmlString );

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == "data") {
                while (!xml.atEnd()) {
                    xml.readNext();

                    if (xml.isEndElement() && xml.name() == "data") {
                        break;
                    }

                    if (xml.isStartElement() && elements.contains(xml.name().toString())) {
                        items.append(parseXml(xml));
                    }
                }
            } else if (xml.name() == "meta") {
                parseMetadataXml(xml);
            }
        }
    }

    return items;
}


template <class T>
void Parser<T>::parseMetadataXml(QXmlStreamReader& xml)
{
    while ( !xml.atEnd() ) {
        xml.readNext();
        if (xml.isEndElement() && xml.name() == "meta") {
            break;
        } else if (xml.isStartElement()) {
            if (xml.name() == "status") {
                m_metadata.statusString = xml.readElementText();
            } else if (xml.name() == "statuscode") {
                m_metadata.statusCode = xml.readElementText().toInt();
            } else if (xml.name() == "message") {
                m_metadata.message = xml.readElementText();
            } else if (xml.name() == "totalitems") {
                m_metadata.totalItems = xml.readElementText().toInt();
            } else if (xml.name() == "itemsperpage") {
                m_metadata.itemsPerPage = xml.readElementText().toInt();
            }
        }
    }
}


template <class T>
JobMetadata Parser<T>::metadata() const {
    return m_metadata;
}
