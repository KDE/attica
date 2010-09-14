#ifndef ATTICAUTILS_H
#define ATTICAUTILS_H

#include <QDateTime>
#include <QString>

namespace Attica {

class Utils {
public:
    /// parses the QtDateTime in ISO 8601 format correctly (recognizes TZ properly)
    static QDateTime parseQtDateTimeIso8601(const QString & str);
};

}

#endif // ATTICAUTILS_H
