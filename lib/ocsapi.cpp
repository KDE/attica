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

#include "ocsapi.h"

using namespace Attica;

OcsApi::OcsApi()
{
}

PersonJob *OcsApi::requestPerson( const QString &id )
{
  KUrl url( "http://api.opendesktop.org/v1/person/data/" + id );
  return doRequestPerson( url );
}

PersonJob *OcsApi::requestPersonSelf()
{
  KUrl url( "http://api.opendesktop.org/v1/person/self" );
  return doRequestPerson( url );
}

PersonListJob *OcsApi::requestPersonSearchByName( const QString &name )
{
  KUrl url( "http://api.opendesktop.org/v1/person/data?name=" + name );
  return doRequestPersonList( url );
}

PersonListJob *OcsApi::requestFriend( const QString &id )
{
  KUrl url( "http://api.opendesktop.org/v1/friend/data/" + id );
  return doRequestPersonList( url );
}

ActivityListJob *OcsApi::requestActivity()
{
  KUrl url( "http://api.opendesktop.org/v1/activity" );
  return doRequestActivityList( url );
}

PostJob *OcsApi::postInvitation( const QString &to, const QString &message )
{
  PostJob *job = new PostJob();

  KUrl url( "http://api.opendesktop.org/v1/friend/outbox/" + to );
  job->setUrl( url );
  job->setData( "message", message );

  job->start();
  return job;  
}

FolderListJob *OcsApi::requestFolders()
{
  return doRequestFolderList( createUrl( "message" ) );
}

MessageListJob *OcsApi::requestMessages( const QString &folderId )
{
  return doRequestMessageList( createUrl( "message/" + folderId ) );
}

KUrl OcsApi::createUrl( const QString &path )
{
  KUrl url( "http://api.opendesktop.org/v1/" );
  url.addPath( path );
  return url;
}

PersonJob *OcsApi::doRequestPerson( const KUrl &url )
{
  PersonJob *job = new PersonJob();

  job->setUrl( url );

  job->start();
  return job;
}

PersonListJob *OcsApi::doRequestPersonList( const KUrl &url )
{
  PersonListJob *job = new PersonListJob();

  job->setUrl( url );

  job->start();
  return job;
}

ActivityListJob *OcsApi::doRequestActivityList( const KUrl &url )
{
  ActivityListJob *job = new ActivityListJob();

  job->setUrl( url );

  job->start();
  return job;
}

FolderListJob *OcsApi::doRequestFolderList( const KUrl &url )
{
  FolderListJob *job = new FolderListJob();
  
  job->setUrl( url );
  job->start();
  return job;
}

MessageListJob *OcsApi::doRequestMessageList( const KUrl &url )
{
  MessageListJob *job = new MessageListJob();
  
  job->setUrl( url );
  job->start();
  return job;
}
