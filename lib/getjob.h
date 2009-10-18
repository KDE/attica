/*
    This file is part of KDE.

    Copyright (c) 2009 Eckhart Wörner <ewoerner@kde.org>

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

#ifndef ATTICA_GETJOB_H
#define ATTICA_GETJOB_H

#include <QtNetwork/QNetworkRequest>

#include "atticaclient_export.h"
#include "atticabasejob.h"


namespace Attica {

class ATTICA_EXPORT GetJob : public Attica::BaseJob
{
    Q_OBJECT

public:
    GetJob(QNetworkAccessManager* nam, const QNetworkRequest& request);
    
private:
    virtual QNetworkReply* executeRequest();

    const QNetworkRequest m_request;
};

}


#endif
