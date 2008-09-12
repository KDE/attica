/*
    This file is part of KDE.

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
#ifndef ATTICA_OCSAPI_H
#define ATTICA_OCSAPI_H

#include "atticaclient_export.h"

#include <kurl.h>

#include <QString>

namespace Attica {

class PersonJob;
class PersonListJob;
class ActivityListJob;

/**
  Open Collaboration Services API.
*/
class ATTICA_EXPORT OcsApi
{
  public:
    OcsApi();

    static PersonJob *requestPerson( const QString &id );
    static PersonJob *requestPersonSelf();
    static PersonListJob *requestPersonSearchByName( const QString &name );

    static PersonListJob *requestFriend( const QString &id );

    static ActivityListJob *requestActivity();

  protected:
    static PersonJob *doRequestPerson( const KUrl & );
    static PersonListJob *doRequestPersonList( const KUrl & );
    static ActivityListJob *doRequestActivityList( const KUrl & );
};

}

#endif
