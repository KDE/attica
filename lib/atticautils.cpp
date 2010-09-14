#include "atticautils.h"
#include <QStringList>
#include <QDebug>

using namespace Attica;

QDateTime Utils::parseQtDateTimeIso8601(const QString & str)
{
    QDateTime result;
    QStringList list;
    QString datetime;

    int tzsign = 0;
    if (str.indexOf("+") != -1) {
        list = str.split("+");
        datetime = list[0];
        tzsign = 1;
    } else if (str.indexOf("-") != -1) {
        list = str.split("-");
        datetime = list[0];
        tzsign = -1;
    } else {
        datetime = str;
    }

    // parse date time
    result = QDateTime::fromString( datetime, Qt::ISODate );
    result.setTimeSpec(Qt::UTC);

    // parse timezone
    if (list.count() == 2) {
        QString tz = list[1];
        int hh = 0;
        int mm = 0;
        int tzsecs = 0;
        if (tz.indexOf(":") != -1) {
            QStringList tzlist = tz.split(":");
            if (tzlist.count() == 2) {
                hh = tzlist[0].toInt();
                mm = tzlist[1].toInt();
            }
        } else {
            hh = tz.left(2).toInt();
            mm = tz.mid(2).toInt();
        }

        tzsecs = 60 * 60 * hh + 60 * mm;
        qDebug() << "before addSecs: " << result;
        result = result.addSecs( - tzsecs * tzsign );
        qDebug() << "after addSecs" << result;
        qDebug() << "to local time" << result.toLocalTime();
    }

    qDebug() << str << result;

    return result;
}
