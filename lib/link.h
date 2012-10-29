/*
    This file is part of KDE.

    Copyright (c) 2012 Dominik Schmidt <dev@dominik-schmidt.de>

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

#ifndef ATTICA_LINK_H
#define ATTICA_LINK_H

#include "atticaclient_export.h"

#include <QSharedData>
#include <QList>

class QUrl;

namespace Attica
{

class ATTICA_EXPORT Link
{
  public:
    typedef QList<Link> List;
    class Parser;

    Link();
    Link(const Link& other);
    Link& operator=(const Link& other);
    ~Link();

    void setUrl(const QUrl &id);
    QUrl url() const;

    bool isValid() const;

  private:
    class Private;
    QSharedDataPointer<Private> d;
};

}

#endif
