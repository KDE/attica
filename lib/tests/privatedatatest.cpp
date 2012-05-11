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

#include <QtTest/QtTest>
#include "../privatedata.h"
#include "../privatedataparser.h"

using namespace Attica;

class PersonTest : public QObject
{
    Q_OBJECT

private slots:
    void testParsing();
    void testMergeType();
};

void PersonTest::testParsing()
{
    PrivateData::Parser parser;
    QString validData ("<?xml version=\"1.0\"?><ocs><attributes>"
          "<key>keyfoo</key>"
          "<value>valuebar</value>"
          "<changed>01.01.1998</changed>"
          "</attributes></ocs>");
    PrivateData attributes = parser.parse(validData);
    QVERIFY(attributes.attributeChanged("keyfoo").isValid());
    QVERIFY(!attributes.attribute("keyfoo").isNull());
}

void PersonTest::testMergeType()
{
    PrivateData a;
    a.setMergeType(PrivateData::OverwriteLocal);
    QVERIFY(a.mergeType() == PrivateData::OverwriteLocal);
}

QTEST_MAIN(PersonTest);

#include "moc_persontest.cxx"
