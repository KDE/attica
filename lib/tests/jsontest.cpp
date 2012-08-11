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
#include "achievement.h"
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

    void testAchievement();
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

void JsonTest::testAchievement()
{
    QString testData1 = startString+QLatin1String("["
        "{"
            "\"id\": 12,"
            "\"content_id\": 1234,"
            "\"name\": \"The Great Thing\","
            "\"description\": \"Great things are afoot\","
            "\"explanation\": \"A great thing which will help you with other things.\","
            "\"points\": 15,"
            "\"image\": \"https://opendesktop.org/content/achievements/images/12.png\","
            "\"dependencies\": null,"
            "\"visibility\": \"visible\","
            "\"type\": \"flowing\","
            "\"progress\": 1"
        "},"
        "{"
            "\"id\": 321,"
            "\"content_id\": 1234,"
            "\"name\": \"The Greater Thing\","
            "\"description\": \"Even greater things are afoot\","
            "\"explanation\": \"Incredible things have been achieved.\","
            "\"points\": 25,"
            "\"image\": \"https://opendesktop.org/content/achievements/images/12.png\","

            "\"dependencies\": ["
                "{"
                    "\"achievement_id\": 12"
                "}"
            "],"

            "\"visibility\": \"dependents\","
            "\"type\": \"set\","

            "\"options\": ["
                "{"
                    "\"option\": \"good\""
                "},"
                "{"
                    "\"option\": \"other good\""
                "},"
                "{"
                    "\"option\": \"also good\""
                "}"
            "],"

            "\"progress\": ["
                "{"
                    "\"reached\": \"good\""
                "},"
                "{"
                    "\"reached\": \"also good\""
                "}"
            "]"
        "}"
        "]") + endString;
    JsonParser<Achievement> parser;
    parser.parse( testData1 );
    Achievement achievement1 = parser.itemList().at(0);
    Achievement achievement2 = parser.itemList().at(1);

    QVERIFY( achievement1.isValid() );
    QVERIFY( achievement2.isValid() );

    QCOMPARE( achievement1.id(), QLatin1String("12") );
    QCOMPARE( achievement1.contentId(), QLatin1String("1234") );
    QCOMPARE( achievement1.name(), QLatin1String("The Great Thing") );
    QCOMPARE( achievement1.description(), QLatin1String("Great things are afoot") );
    QCOMPARE( achievement1.explanation(), QLatin1String("A great thing which will help you with other things.") );
    QCOMPARE( achievement1.points(), 15 );
    QCOMPARE( achievement1.image(), QUrl(QLatin1String("https://opendesktop.org/content/achievements/images/12.png")) );
    QVERIFY( achievement1.dependencies().isEmpty() );
    QCOMPARE( achievement1.visibility(), Achievement::VisibleAchievement );
    QCOMPARE( achievement1.type(), Achievement::FlowingAchievement );
    QCOMPARE( achievement1.progress(), QVariant::fromValue<int>(1) );

    QCOMPARE( achievement2.id(), QLatin1String("321") );
    QCOMPARE( achievement2.dependencies().size(), 1 );
    QCOMPARE( achievement2.dependencies().at(0), QLatin1String("12") );
    QCOMPARE( achievement2.options().size(), 3 );
    QCOMPARE( achievement2.options().at(2), QLatin1String("also good") );
    QVERIFY( achievement2.progress().toStringList().contains(QLatin1String("also good")) );
}

void JsonTest::testMessage()
{
    QString testData1 =startString+QLatin1String("["
        "{"
            "\"details\": \"full\","
            "\"id\": 8490,"
            "\"message from\": \"testy\","
            "\"firstname\": \"Laszlo\","
            "\"lastname\": \"Papp\","
            "\"profilepage\": \"https://www.opendesktop.org/usermanager/search.php?username=lpapp\","
            "\"messageto\": \"lpapp\","
            "\"senddate\": \"2008-08-10T16:03:59+02:00\","
            "\"status\": 1,"
            "\"statustext\": null,"
            "\"subject\": \"test message\","
            "\"body\": \"Sorry for bothering but did you ...\""
        "}"
        "]")+endString;
    JsonParser<Message> parser;
    parser.parse( testData1 );
    Message message = parser.item();

    QVERIFY( message.isValid() );
    QCOMPARE( message.id(), QLatin1String("8490") );
    QCOMPARE( message.from(), QLatin1String("testy") );
    QCOMPARE( message.to(), QLatin1String("lpapp") );
    QCOMPARE( message.sent(), QDateTime::fromString(QLatin1String("2008-08-10T16:03:59+02:00"), Qt::ISODate) );
    QCOMPARE( message.status(), Message::Status(1) );
    QCOMPARE( message.subject(), QLatin1String("test message") );
    QCOMPARE( message.body(), QLatin1String("Sorry for bothering but did you ...") );
}


void JsonTest::testPerson()
{
    QString testData1 = startString+QLatin1String("["
        "{"
            "\"details\": \"full\","
            "\"personid\": \"lpapp\","
            "\"privacy\": 1,"
            "\"privacytext\": \"visible only for registered users\","
            "\"firstname\": \"Laszlo\","
            "\"lastname\": \"Papp\","
            "\"gender\": \"male\","
            "\"communityrole\": \"developer\","
            "\"homepage\": null,"
            "\"company\": \"company\","
            "\"avatarpic\": \"https://www.opendesktop.org/usermanager/nopic.png\","
            "\"avatarpicfound\": 1,"
            "\"bigavatarpic\": \"https://www.opendesktop.org/usermanager/nopic.png\","
            "\"bigavatarpicfound\": 1,"
            "\"birthday\": \"1985-12-02\","
            "\"jobstatus\": \"working\","
            "\"city\": \"Helsinki\","
            "\"country\": \"Finland\","
            "\"longitude\": 24.9375,"
            "\"latitude\": 60.1708,"
            "\"ircnick\": \"djszapi\","
            "\"ircchannels\": \"ocs, qt-labs\","

            "\"irclink\": ["
                "{"
                    "\"link\": \"irc://irc.freenode.org/ocs\""
                "},"
                "{"
                    "\"link\": \"irc://irc.freenode.org/qt-labs\""
                "}"
            "],"

            "\"likes\": \"lot of stuff\","
            "\"dontlikes\": \"nothing\","
            "\"interests\": \"travel\","
            "\"languages\": \"english\","
            "\"programminglanguages\": \"c, c++\","
            "\"favouritequote\": null,"
            "\"favouritemusic\": \"Iron Maiden\","
            "\"favouritetvshows\": null,"
            "\"favouritemovies\": \"Back to the Future\","
            "\"favouritebooks\": null,"
            "\"favouritegames\": \"Star Craft\","
            "\"description\": null,"
            "\"profilpage\": \"https://www.KDE-Look.org/usermanager/search.php?username=lpapp\""
        "}"
        "]") + endString;
    JsonParser<Person> parser;
    parser.parse( testData1 );
    Person person = parser.item();
    QVERIFY( person.isValid() );
    QCOMPARE( person.id(), QLatin1String("lpapp") );
    QCOMPARE( person.firstName(), QLatin1String("Laszlo") );
    QCOMPARE( person.lastName(), QLatin1String("Papp") );
    QCOMPARE( person.birthday(), QDate(1985, 12, 02) );
    QCOMPARE( person.country(), QLatin1String("Finland") );
    QCOMPARE( person.latitude(), 60.1708 );
    QCOMPARE( person.longitude(), 24.9375 );
    QCOMPARE( person.avatarUrl(), QUrl( QLatin1String("https://www.opendesktop.org/usermanager/nopic.png") ) );
    QCOMPARE( person.homepage(), QLatin1String("") );
    QCOMPARE( person.city(), QLatin1String("Helsinki") );
    QCOMPARE( person.extendedAttribute(QLatin1String("favouritemusic")), QLatin1String("Iron Maiden"));
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
