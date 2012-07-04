/*
    This file is part of KDE.

    Copyright (c) 2010 Martin Sandsmark <martin.sandsmark@kde.org>

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

#include <QtTest>
#include "xmlparser.h"

using namespace Attica;

class PersonTest : public QObject
{
    Q_OBJECT

private slots:
    void testParsing();
};

void PersonTest::testParsing()
{
    XmlParser<Person> parser;
    QString validData (QLatin1String("<?xml version=\"1.0\"?>"
               "<ocs><data><person>"
               "<personid>10</personid>"
               "<firstname>Ola</firstname>"
               "<lastname>Nordmann</lastname>"
               "<homepage>http://kde.org/</homepage>"
               "<avatarpic>http://techbase.kde.org/skins/oxygen/top-kde.png</avatarpic>"
               "<avatarpicfound>1</avatarpicfound>"
               "<birthday>2010-06-21</birthday>"
               "<city>Oslo</city>"
               "<country>Norway</country>"
               "<latitude>59.56</latitude>"
               "<longitude>10.41</longitude>"
          "</person></data></ocs>"));
    parser.parse(validData);
    Person person = parser.item();
    QVERIFY(person.isValid());

    QString invalidData = QLatin1String("<ocs><braaaaaaaaaaawrlawrf></braaaaaaaaaaawrlawrf></ocs>");
    parser.parse(invalidData);
    person = parser.item();
    QVERIFY(!person.isValid());
}

QTEST_MAIN(PersonTest);

#include "persontest.moc"
