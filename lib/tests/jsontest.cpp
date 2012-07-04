/*
    This file is part of KDE.

    Copyright (c) 2012 Felix Rohrbach <fxrh@gmx>

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

#include "jsonparser.h"
#include "metadata.h"
#include "message.h"
#include "person.h"

#include <QtTest>
#include <QObject>
#include <QtCore/QDateTime>

using namespace Attica;

class JsonTest: public QObject
{
    Q_OBJECT
private slots:
    void testMetadata();
    void testMessage();
    void testPerson();

private:
    static const QString startString;
    static const QString endString;
};

const QString JsonTest::startString = QLatin1String("{"
            "\"status\": \"ok\","
            "\"statuscode\": 100,"
            "\"message\": null,"
            "\"data\": ");

const QString JsonTest::endString = QLatin1String("}");

void JsonTest::testMetadata()
{
    QString testData1 = QLatin1String("{"
            "\"status\":\"ok\","
            "\"statuscode\":100,"
            "\"message\":null"
            "}");
    JsonParser<NoneType> parser;
    parser.parse(testData1);
    Metadata metadata = parser.metadata();
    QCOMPARE( metadata.statusString(), QLatin1String("ok") );
    QCOMPARE( metadata.statusCode(), 100 );
    QCOMPARE( metadata.message(), QLatin1String("") );
}

void JsonTest::testMessage()
{
    QString testData1 =startString+QLatin1String("{"
                "\"id\":\"8490\","
                "\"messagefrom\":\"testy\","
                "\"firstname\":\"Test\","
                "\"lastname\":\"TTT\","
                "\"profilepage\":\"http://www.opendesktop.org/usermanager/search.php?username=testy\","
                "\"messageto\":\"Frank\","
                "\"senddate\":\"2008-08-10T16:03:59+02:00\","
                "\"status\":1,"
                "\"statustext\":null,"
                "\"subject\":\"test message\","
                "\"body\":\"Sorry for bothering but did you ...\""
                "}")+endString;
    JsonParser<Message> parser;
    parser.parse( testData1 );
    Message message = parser.item();

    QVERIFY( message.isValid() );
    QCOMPARE( message.id(), QLatin1String("8490") );
    QCOMPARE( message.from(), QLatin1String("testy") );
    QCOMPARE( message.to(), QLatin1String("Frank") );
    QCOMPARE( message.sent(), QDateTime::fromString(QLatin1String("2008-08-10T16:03:59+02:00"), Qt::ISODate) );
    QCOMPARE( message.status(), Message::Status(1) );
    QCOMPARE( message.subject(), QLatin1String("test message") );
    QCOMPARE( message.body(), QLatin1String("Sorry for bothering but did you ...") );
}


void JsonTest::testPerson()
{
    QString testData1 = startString+QLatin1String("{"
            "\"details\":\"full\","
            "\"personid\":\"Frank\","
            "\"privacy\":1,"
            "\"privacytext\":\"visible only for registered users\","
            "\"firstname\":\"Frank\","
            "\"lastname\":\"Test\","
            "\"gender\":\"male\","
            "\"communityrole\":\"developer\","
            "\"homepage\":\"openDesktop.org\","
            "\"homepagetype\":null,"
            "\"homepageicon\":null,"
            "\"homepage2\":null,"
            "\"homepagetype2\":null,"
            "\"homepage3\":null,"
            "\"homepagetype3\":null,"
            "\"homepage4\":null,"
            "\"homepagetype4\":null,"
            "\"homepageicon4\":null,"
            "\"homepage5\":null,"
            "\"homepagetype5\":null,"
            "\"homepage6\":\"www.facebook.com/foo\","
            "\"homepagetype6\":\"Facebook\","
            "\"homepageicon6\":\"http://openDesktop.org/img/socialicons/emblem-facebook.png\","
            "\"company\":\"opendesktop.org\","
            "\"avatarpic\":\"http://www.KDE-Look.org/CONTENT/user-pics/0/Frank.jpg\","
            "\"avatarpicfound\":1,"
            "\"bigavatarpic\":\"http://www.KDE-Look.org/CONTENT/user-bigpics/0/Frank.jpg\","
            "\"bigavatarpicfound\":1,"
            "\"birthday\":\"1973-07-25\","
            "\"jobstatus\":\"working\","
            "\"city\":\"Stuttgart\","
            "\"country\":\"Germany\","
            "\"latitude\":null,"
            "\"longitude\":null,"
            "\"ircnick\":\"karli\","
            "\"ircchannels\":\"kde-dev, plasma\","
            "\"irclink\":\"irc://irc.freenode.org/kde-dev\","
            "\"irclink\":\"irc://irc.freenode.org/plasma\","
            "\"likes\":\"lot of stuff\","
            "\"dontlikes\":\"nothing\","
            "\"interests\":\"travel\","
            "\"languages\":\"english\","
            "\"programminglanguages\":\"php, c++\","
            "\"favouritequote\":null,"
            "\"favouritemusic\":\"nin\","
            "\"favouritetvshows\":null,"
            "\"favouritemovies\":\"fightclub\","
            "\"favouritebooks\":null,"
            "\"favouritegames\":\"ut3\","
            "\"description\":null,"
            "\"profilepage\":\"http://www.KDE-Look.org/usermanager/search.php?username=Frank\""
        "}") + endString;
    JsonParser<Person> parser;
    parser.parse( testData1 );
    Person person = parser.item();
    QVERIFY( person.isValid() );
    QCOMPARE( person.id(), QLatin1String("Frank") );
    QCOMPARE( person.firstName(), QLatin1String("Frank") );
    QCOMPARE( person.lastName(), QLatin1String("Test") );
    QCOMPARE( person.birthday(), QDate(1973, 07, 25) );
    QCOMPARE( person.country(), QLatin1String("Germany") );
    QCOMPARE( person.latitude(), 0.0 );
    QCOMPARE( person.longitude(), 0.0 );
    QCOMPARE( person.avatarUrl(), QUrl( QLatin1String("http://www.KDE-Look.org/CONTENT/user-pics/0/Frank.jpg") ) );
    QCOMPARE( person.homepage(), QLatin1String("openDesktop.org") );
    QCOMPARE( person.city(), QLatin1String("Stuttgart") );
    QCOMPARE( person.extendedAttribute(QLatin1String("favouritemusic")), QLatin1String("nin"));
}

// void JsonTest::testConfig()
// {
//     QString testData1 = startString +
//             "{"
//             "\"version\": \"1.4\","
//             "\"website\": \"opendesktop.org\","
//             "\"host\": \"api.opendesktop.org\","
//             "\"contact\": \"frank@opendesktop.org\","
//             "\"ssl\": true"
//             "}" + endString;
//     JsonParser parser;
//     parser.parse(testData1);
//     Config
// }

QTEST_MAIN(JsonTest);

#include "jsontest.moc"
