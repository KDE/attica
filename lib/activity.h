/*
    This file is part of KDE.

    Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
    USA.
*/
#ifndef ATTICA_ACTIVITY_H
#define ATTICA_ACTIVITY_H

#include <kurl.h>

#include <QtCore>
#include <QPixmap>

namespace Attica {

class Transport;
class ActivityListJob;

class Activity
{
  public:
    typedef QList<Activity> List;
  
    Activity();

    static void setTransport( Transport * );

    static ActivityListJob *request();

    void setUser( const QString & );
    QString user() const;

    void setTimestamp( const QDateTime & );
    QDateTime timestamp() const;

    void setMessage( const QString & );
    QString message() const;

  private:
    static Transport *m_transport;

    QString m_user;  
    QDateTime m_timestamp;
    QString m_message;
};

}

#endif