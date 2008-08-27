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

#include "person.h"

#include "personjob.h"
#include "personlistjob.h"

using namespace Attica;

Transport *Person::m_transport = 0;

Person::Person()
  : m_latitude( 0 ), m_longitude( 0 )
{
}

void Person::setTransport( Transport *t )
{
  m_transport = t;
}

PersonJob *Person::request( const QString &id )
{
  PersonJob *job = new PersonJob( id );
  job->start();
  return job;
}

PersonListJob *Person::requestSearchName( const QString &name )
{
  PersonListJob *job = new PersonListJob( name );
  job->start();
  return job;
}

void Person::setUser( const QString &u )
{
  m_user = u;
}

QString Person::user() const
{
  return m_user;
}

void Person::setFirstName( const QString &name )
{
  m_firstName = name;
}

QString Person::firstName() const
{
  return m_firstName;
}
  
void Person::setLastName( const QString &name )
{
  m_lastName = name;
}

QString Person::lastName() const
{
  return m_lastName;
}
    
void Person::setBirthday( const QDate &d )
{
  m_birthday = d;
}

QDate Person::birthday() const
{
  return m_birthday;
}

void Person::setCountry( const QString &c )
{
  m_country = c;
}

QString Person::country() const
{
  return m_country;
}

void Person::setLatitude( qreal l )
{
  m_latitude = l;
}

qreal Person::latitude() const
{
  return m_latitude;
}

void Person::setLongitude( qreal l )
{
  m_longitude = l;
}

qreal Person::longitude() const
{
  return m_longitude;
}

void Person::setAvatarUrl( const KUrl &url )
{
  m_avatarUrl = url;
}

KUrl Person::avatarUrl() const
{
  return m_avatarUrl;
}

void Person::setAvatar( const QPixmap &p )
{
  m_avatar = p;
}

QPixmap Person::avatar() const
{
  return m_avatar;
}

void Person::setHomepage( const QString &h )
{
  m_homepage = h;
}

QString Person::homepage() const
{
  return m_homepage;
}

void Person::setCity( const QString &h )
{
  m_city = h;
}

QString Person::city() const
{
  return m_city;
}
