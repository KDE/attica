/*
    This file is part of KDE.

    Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>

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

#include "attributesparser.h"


using namespace Attica;

Attributes Attributes::Parser::parseXml(QXmlStreamReader& xml)
{
    Attributes person;
    bool hasAvatarPic = false;
    QString key;
    
    // TODO: when we get internet and some documentation
    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == "key") {
                key = xml.readElementText();
            } else if (xml.name() == "value") {
                person.setAttribute(key, xml.readElementText());
            } else if (xml.name() == "attributeChanged") {
                person.setAttributeChanged(key, QDateTime::fromString(xml.readElementText()));
            }
        } else if (xml.isEndElement() && (xml.name() == "person" || xml.name() == "user")) {
            break;
        }
    }

    return person;
}


QStringList Attributes::Parser::xmlElement() const {
    return QStringList("attributes");
}
