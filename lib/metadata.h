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
#ifndef ATTICA_METADATA_H
#define ATTICA_METADATA_H

#include <QtCore/QString>

#include <QSharedDataPointer>

#include "atticaclient_export.h"


namespace Attica {
    class BaseJob;
    
/**
    *Status messages from the server
    */
class ATTICA_EXPORT Metadata
{
public:
    Metadata();
    Metadata(const Metadata& other);
    ~Metadata();
    Metadata& operator=(const Metadata& other);
    
    /**
     * The status as int, for easier interpretation.
     * 100 means "Ok", for other codes refer to http://www.freedesktop.org/wiki/Specifications/open-collaboration-services
     */
    int statusCode() const;
    void setStatusCode(int code);

    /**
     * The status of the job, for example "Ok"
     */
    QString statusString() const;
    void setStatusString(const QString& status);

    /// An optional additional message from the server
    QString message();
    void setMessage(const QString& message);
    
    /// The number of items returned by this job (only relevant for list jobs)
    int totalItems();
    void setTotalItems(int items);
        
    /// The number of items per page the server was asked for
    int itemsPerPage();
    void setItemsPerPage(int itemsPerPage);

    private:
        class Private;
        QSharedDataPointer<Private> d;

        friend class Attica::BaseJob;
    };

}

#endif
