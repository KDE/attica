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

#include "provider.h"

#include "activity.h"
#include "content.h"
#include "event.h"
#include "folder.h"
#include "knowledgebaseentrylistjob.h"
#include "message.h"
#include "personjob.h"
#include "postjob.h"
#include "itemjob.h"
#include "listjob.h"

#include <QNetworkAccessManager>
#include <QDebug>
#include <QUrl>
#include <QNetworkReply>
#include <QAuthenticator>
#include <KDebug>

using namespace Attica;


class Provider::Private : public QSharedData {
  public:
    QUrl m_baseUrl;
    QString m_id;
    QString m_name;
    QNetworkAccessManager* m_qnam;

    Private(const Private& other)
      : QSharedData(other), m_baseUrl(other.m_baseUrl), m_id(other.m_id), m_name(other.m_name), m_qnam(other.m_qnam)
    {
    }
    Private(const QString& id, const QUrl& baseUrl, const QString name)
      : m_baseUrl(baseUrl), m_id(id), m_name(name), m_qnam(new QNetworkAccessManager)
    {
    }
    ~Private()
    {
        delete m_qnam;
    }
};


Provider Provider::createProvider(const QString& id)
{
    if (id == "opendesktop") {
        return Provider(id, QUrl("https://api.opendesktop.org/v1/"), "OpenDesktop.org");
    }
    return Provider();
}


Provider::Provider(QObject* parent)
  : QObject(parent), d(new Private(QString(), QUrl(), QString()))
{
    connect(d->m_qnam, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(authenticate(QNetworkReply*,QAuthenticator*)));

}

Provider::Provider(const Provider& other, QObject* parent)
  : QObject(parent), d(other.d)
{
    connect(d->m_qnam, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(authenticate(QNetworkReply*,QAuthenticator*)));
    dumpObjectInfo();
}

Provider::Provider(const QString& id, const QUrl& baseUrl, const QString& name)
  : d(new Private(id, baseUrl, name))
{
    connect(d->m_qnam, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(authenticate(QNetworkReply*,QAuthenticator*)));
}

Provider& Provider::operator=(const Attica::Provider & other)
{
    d = other.d;
    connect(d->m_qnam, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(authenticate(QNetworkReply*,QAuthenticator*)));
    return *this;
}

Provider::~Provider()
{
}

QUrl Provider::baseUrl() const
{
    return d->m_baseUrl;
}


bool Provider::isValid() const
{
    return d->m_baseUrl.isValid();
}


void Provider::authenticate(QNetworkReply* , QAuthenticator* auth)
{
    qDebug() << "authentication requested - implement me :D";
    // TODO

    auth->setUser("API4752248551824585417547616258117595859336334565755742650330375402");
    //auth->setPassword("pass");
}

QString Provider::id() const
{
    return d->m_id;
}


QString Provider::name() const
{
    return d->m_name;
}


PersonJob* Provider::requestPerson(const QString& id)
{
  QUrl url = createUrl( "person/data/" + id );
  return doRequestPerson( url );
}

PersonJob* Provider::requestPersonSelf()
{
  QUrl url = createUrl( "person/self" );
  return doRequestPerson( url );
}

ListJob<Person>* Provider::requestPersonSearchByName(const QString& name)
{
  QUrl url = createUrl( "person/data");
  url.addQueryItem("name", name);
  return doRequestPersonList( url );
}

ListJob<Person>* Provider::requestPersonSearchByLocation(qreal latitude, qreal longitude, qreal distance, int page, int pageSize)
{
  QUrl url = createUrl( "person/data" );
  url.addQueryItem("latitude", QString::number(latitude));
  url.addQueryItem("longitude", QString::number(longitude));
  url.addQueryItem("distance", QString::number(distance));
  url.addQueryItem("page", QString::number(page));
  url.addQueryItem("pagesize", QString::number(pageSize));
  
  qDebug() << "Location-based search:" << latitude << longitude << distance;
  qDebug() << "URL:" << url;
  return doRequestPersonList( url );
}

ListJob<Person>* Provider::requestFriends(const QString& id, int page, int pageSize)
{
  QUrl url = createUrl( "friend/data/" + id );
  url.addQueryItem("page", QString::number(page));
  url.addQueryItem("pagesize", QString::number(pageSize));
  qDebug() << "URL:" << url;
  return doRequestPersonList( url );
}

ListJob<Activity>* Provider::requestActivities()
{
    qDebug() << "request activity";
  QUrl url = createUrl( "activity" );
  return doRequestActivityList( url );
}

PostJob* Provider::postActivity(const QString& message)
{
  PostJob *job = new PostJob();

  QUrl url = createUrl( "activity" );
  job->setUrl( url );
  job->setData( "message", message );
  
  job->start();
  return job;
}

PostJob* Provider::postFriendInvitation(const QString& to, const QString& message)
{
  PostJob *job = new PostJob();

  QUrl url = createUrl( "friend/outbox/" + to );
  job->setUrl( url );
  job->setData( "message", message );

  job->start();
  return job;  
}

PostJob* Provider::postLocation(qreal latitude, qreal longitude, const QString& city, const QString& country)
{
  PostJob *job = new PostJob();
  
  QUrl url = createUrl( "person/self" );
  
  job->setUrl( url ); 

  job->setData( "latitude", QString("%1").arg(latitude) );
  job->setData( "longitude", QString("%1").arg(longitude) );
  job->setData( "city", city );
  job->setData( "country", country );
  
  job->start();
  return job;
}


ListJob<Folder>* Provider::requestFolders()
{
  return doRequestFolderList( createUrl( "message" ) );
}

ListJob<Message>* Provider::requestMessages(const Folder& folder)
{
  return doRequestMessageList( createUrl( "message/" + folder.id() ) );
}

PostJob* Provider::postMessage( const Message &message )
{
  PostJob *job = new PostJob();
  
  QUrl url = createUrl( "message/2" );
  job->setUrl( url );
  job->setData( "message", message.body() );
  job->setData( "subject", message.subject() );
  job->setData( "to", message.to() );
  
  job->start();
  return job;
}

ListJob<Category>* Provider::requestCategories()
{
  QUrl url = createUrl( "content/categories" );
  ListJob<Category> *job = new ListJob<Category>(d->m_qnam->get(QNetworkRequest(url)));
  return job;
}

ListJob<Content>* Provider::searchContents(const Category::List& categories, const QString& search, SortMode sortMode)
{

  QUrl url = createUrl( "content/data" );

  QStringList categoryIds;
  foreach( const Category &category, categories ) {
    categoryIds.append( category.id() );
  }
  url.addQueryItem( "categories", categoryIds.join( "x" ) );
  
  url.addQueryItem( "search", search );
  QString sortModeString;
  switch ( sortMode ) {
    case Newest:
      sortModeString = "new";
      break;
    case Alphabetical:
      sortModeString = "alpha";
      break;
    case Rating:
      sortModeString = "high";
      break;
    case Downloads:
      sortModeString = "down";
      break;
  }
  if ( !sortModeString.isEmpty() ) {
    url.addQueryItem( "sortmode", sortModeString );
  }

    ListJob<Content> *job = new ListJob<Content>(d->m_qnam->get(QNetworkRequest(url)));

  return job;
}

ItemJob<Content>* Provider::requestContent(const QString& id)
{
  QUrl url = createUrl( "content/data/" + id );
  ItemJob<Content> *job = new ItemJob<Content>(d->m_qnam->get(QNetworkRequest(url)));
  return job;
}

PostJob* Provider::addNewContent(const Category& category, const Content& newContent)
{
  if (!category.isValid() || !newContent.isValid()) {
    return 0;
  }
  
  QString cat = category.id();
  
  
  // FIXME
  return 0;
}

ItemJob<KnowledgeBaseEntry>* Provider::requestKnowledgeBaseEntry(const QString& id)
{
    QUrl url = createUrl( "knowledgebase/data/" + id );
    ItemJob<KnowledgeBaseEntry> *job = new ItemJob<KnowledgeBaseEntry>(d->m_qnam->get(QNetworkRequest(url)));
    return job;
}

ListJob<KnowledgeBaseEntry>* Provider::searchKnowledgeBase(const Content& content, const QString& search, Provider::SortMode sortMode, int page, int pageSize)
{
  QUrl url = createUrl( "knowledgebase/data" );
  if (content.isValid()) {
      url.addQueryItem("content", content.id());
  }

  url.addQueryItem( "search", search );
  QString sortModeString;
  switch ( sortMode ) {
    case Newest:
      sortModeString = "new";
      break;
    case Alphabetical:
      sortModeString = "alpha";
      break;
    case Rating:
      sortModeString = "high";
      break;
    //FIXME: knowledge base doesn't have downloads
    case Downloads:
      sortModeString = "new";
      break;
  }
  if ( !sortModeString.isEmpty() ) {
    url.addQueryItem( "sortmode", sortModeString );
  }

  url.addQueryItem( "page", QString::number(page) );
  url.addQueryItem( "pagesize", QString::number(pageSize) );

  ListJob<KnowledgeBaseEntry> *job = new ListJob<KnowledgeBaseEntry>(d->m_qnam->get(QNetworkRequest(url)));
  return job;
}

ItemJob<Event>* Provider::requestEvent(const QString& id)
{
    ItemJob<Event>* job = new ItemJob<Event>(d->m_qnam->get(QNetworkRequest(createUrl("event/data/" + id))));
    return job;
}

ListJob<Event>* Provider::requestEvent(const QString& country, const QString& search, const QDate& startAt, Provider::SortMode mode, int page, int pageSize)
{
  QUrl url = createUrl("event/data");

  if (!search.isEmpty()) {
      url.addQueryItem("search", search);
  }

  QString sortModeString;
  switch (mode) {
    case Newest:
      sortModeString = "new";
      break;
    case Alphabetical:
      sortModeString = "alpha";
      break;
    default:
        break;
  }
  if (!sortModeString.isEmpty()) {
    url.addQueryItem("sortmode", sortModeString);
  }
  
  if (!country.isEmpty()) {
    url.addQueryItem("country", country);
  }
  
  url.addQueryItem("startat", startAt.toString(Qt::ISODate));

  url.addQueryItem("page", QString::number(page));
  url.addQueryItem("pagesize", QString::number(pageSize));

  ListJob<Event>* job = new ListJob<Event>(d->m_qnam->get(QNetworkRequest(url)));
  return job;
}

QUrl Provider::createUrl(const QString& path)
{

  QUrl url(d->m_baseUrl.toString() + path);

  //url.addPath( path );

  return url;
}

PersonJob* Provider::doRequestPerson(const QUrl& url)
{
  QNetworkReply* reply = d->m_qnam->get(QNetworkRequest(url));
  PersonJob *job = new PersonJob(reply);

  return job;
}

ListJob<Person>* Provider::doRequestPersonList(const QUrl& url)
{
    ListJob<Person> *job = new ListJob<Person>(d->m_qnam->get(QNetworkRequest(url)));
    return job;
}

ListJob<Activity>* Provider::doRequestActivityList(const QUrl& url)
{
    ListJob<Activity> *job = new ListJob<Activity>(d->m_qnam->get(QNetworkRequest(url)));
    return job;
}

ListJob<Folder>* Provider::doRequestFolderList(const QUrl& url)
{
    ListJob<Folder> *job = new ListJob<Folder>(d->m_qnam->get(QNetworkRequest(url)));
    return job;
}

ListJob<Message>* Provider::doRequestMessageList(const QUrl& url)
{
    ListJob<Message> *job = new ListJob<Message>(d->m_qnam->get(QNetworkRequest(url)));
    return job;
}

#include "provider.moc"

