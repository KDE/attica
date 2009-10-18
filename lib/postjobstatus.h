/*
    This file is part of KDE.

    Copyright (c) 2009 Frederik Gladhorn <gladhorn@kde.org>

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

#ifndef ATTICA_POSTJOBSTATUS_H
#define ATTICA_POSTJOBSTATUS_H

#include "atticaclient_export.h"

#include <QtCore/QDate>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QSharedDataPointer>
#include <QtCore/QUrl>


namespace Attica {
    
/**
 * Status after posting to server
 */
class ATTICA_EXPORT PostJobStatus
{
    public:
        class Parser;

        PostJobStatus();

        /**
         * Copy constructor.
         * @param other the Event to copy from
         */
        PostJobStatus(const PostJobStatus& other);

        /**
         * Assignment operator.
         * @param other the Event to assign from
         * @return pointer to this Event
         */
        PostJobStatus& operator=(const PostJobStatus& other);

        /**
         * Destructor.
         */
        ~PostJobStatus();

        QString status();
        int statusCode();
        QString statusMessage();
        QString data();

        void setStatus(const QString& status);
        void setStatusCode(int statusCode);
        void setStatusMessage(const QString& statusMessage);
        void setData(const QString& data);

    private:
        class Private;
        QSharedDataPointer<Private> d;
};

}


#endif
