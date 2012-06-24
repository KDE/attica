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

#include <QtCore/QObject>

#include "metadata.h"
#include "atticaclient_export.h"

class QNetworkReply;

#ifndef ATTICA_BASICJOB_H
#define ATTICA_BASICJOB_H

namespace Attica
{
class PlatformDependent;

class ATTICA_EXPORT BasicJob: public QObject
{
    Q_OBJECT
public:
    enum JobType { Post, Put, Get, Delete };
    enum ParserType { Xml };

    BasicJob(JobType jobType, ParserType parserType);
    virtual ~BasicJob();

    Metadata metadata() const;
    JobType jobType() const;
    ParserType parserType() const;

public Q_SLOTS:
    void start();
    void abort();

Q_SIGNALS:
    void finished(Attica::BasicJob* job);

protected Q_SLOTS:
    void dataFinished();

protected:
    void setMetadata(const Metadata& data) const;
    virtual QNetworkReply* executeRequest()=0;
    virtual void parse(const QString& data)=0;
    virtual PlatformDependent* internals()=0;

private Q_SLOTS:
    void doWork();

private:
    class Private;
    Private *d;
};

}

#endif
