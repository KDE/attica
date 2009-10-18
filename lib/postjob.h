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

#ifndef ATTICA_POSTJOB_H
#define ATTICA_POSTJOB_H

#include <QtNetwork/QNetworkRequest>

#include "atticaclient_export.h"
#include "atticabasejob.h"

// workaround to get initialization working with gcc < 4.4
typedef QMap<QString, QString> StringMap;

namespace Attica {

class ATTICA_EXPORT PostJob : public Attica::BaseJob
{
    Q_OBJECT

public:
    PostJob(QNetworkAccessManager* nam, const QNetworkRequest& request, const QMap<QString, QString>& data = StringMap());
    
/*    QString status() const;
    QString statusMessage() const;

protected Q_SLOTS:
    void slotJobResult( KJob *job );
    void slotJobData( KIO::Job *, const QByteArray & );
*/
private:
    virtual QNetworkReply* executeRequest();
    virtual void parse(const QString&);

    QMap<QString,QString> m_data;
    QString m_responseData;
    const QNetworkRequest m_request;
  
    QString m_status;
    QString m_statusMessage;
};

}


#endif
