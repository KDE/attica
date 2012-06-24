/*
    This file is part of KDE.

    Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>
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
#ifndef ATTICA_JOB_H
#define ATTICA_JOB_H

#include "basicjob.h"

#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtCore/QUrl>
#include <QtCore/QIODevice>
#include <QtNetwork/QNetworkAccessManager>

#include "atticaclient_export.h"
#include "metadata.h"

class QNetworkReply;

// workaround to get initialization working with gcc < 4.4
typedef QMap<QString, QString> StringMap;

namespace Attica {
    class PlatformDependent;

template <class T>
class ATTICA_EXPORT Job : public BasicJob
{
public:
    Job(PlatformDependent *internals, JobType type, ParserType parser, const QNetworkRequest &request, QIODevice *data);
    Job(PlatformDependent *internals, JobType type, ParserType parser, const QNetworkRequest &request, const StringMap &parameters = StringMap());
    Job(PlatformDependent *internals, JobType type, ParserType parser, const QNetworkRequest &request, const QByteArray &data);
    virtual ~Job();

    T item() const;
    typename T::List itemList() const;

protected:
    QNetworkReply* executeRequest();
    void parse(const QString& data);
    PlatformDependent* internals();

private:
    Job(const Job& other);
    Job& operator=(const Job& other);

    class Private;
    Private* d;
};

}

#endif
