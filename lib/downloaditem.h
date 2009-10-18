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

#ifndef ATTICA_DOWNLOADITEM_H
#define ATTICA_DOWNLOADITEM_H

#include <QtCore/QSharedDataPointer>
#include <QtCore/QUrl>

#include "atticaclient_export.h"

namespace Attica {

class ATTICA_EXPORT DownloadItem
{
public:
    class Parser;
    
    /**
    * Creates an empty DownloadItem
    */
    DownloadItem();
    
    /**
    * Copy constructor.
    * @param other the DownloadItem to copy from
    */
    DownloadItem(const DownloadItem& other);
    
    /**
    * Assignment operator.
    * @param other the DownloadItem to assign from
    * @return pointer to this DownloadItem
    */
    DownloadItem& operator=(const DownloadItem& other);
    
    /**
    * Destructor.
    */
    ~DownloadItem();
    
    void setUrl(const QUrl& url);
    QUrl url();

private:
    class Private;
    QExplicitlySharedDataPointer<Private> d;
};

}

#endif // DOWNLOADITEM_H
