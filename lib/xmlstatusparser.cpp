/*
    This file is part of KDE.

    Copyright (c) 2012 Felix Rohrbach <fxrh@gmx.de>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.

 */

#include "xmlstatusparser.h"

#include <QXmlStreamReader>
#include <QDebug>

using namespace Attica;

void XmlStatusParser::parse(const QString& data)
{
    qDebug() << "XmlStatusParser::parse" << data;
    QXmlStreamReader xml( data );
    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == "meta") {
                while ( !xml.atEnd() ) {
                    xml.readNext();
                    if (xml.isEndElement() && xml.name() == "meta") {
                        break;
                    } else if (xml.isStartElement()) {
                        if (xml.name() == "status") {
                            m_metadata.setStatusString(xml.readElementText());
                        } else if (xml.name() == "statuscode") {
                            m_metadata.setStatusCode(xml.readElementText().toInt());
                        } else if (xml.name() == "message") {
                            m_metadata.setMessage(xml.readElementText());
                        } else if (xml.name() == "totalitems") {
                            m_metadata.setTotalItems(xml.readElementText().toInt());
                        } else if (xml.name() == "itemsperpage") {
                            m_metadata.setItemsPerPage(xml.readElementText().toInt());
                        }
                    }
                }
            } else if (xml.name() == "data") {
                while ( !xml.atEnd() ) {
                    xml.readNext();
                    if (xml.isEndElement() && xml.name() == "data") {
                        break;
                    } else if (xml.isStartElement()) {
                        if (xml.name() == "projectid") {
                            m_metadata.setResultingId(xml.readElementText());
                        } if (xml.name() == "buildjobid") {
                            m_metadata.setResultingId(xml.readElementText());
                        }
                    }
                }
            }
        }
    }
}

Metadata XmlStatusParser::metadata() const
{
    return m_metadata;
}
