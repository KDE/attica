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
#include "downloaditem.h"
#include "event.h"
#include "folder.h"
#include "knowledgebaseentry.h"
#include "message.h"
#include "personjob.h"
#include "postjob.h"
#include "itemjob.h"
#include "listjob.h"
#include "postjobstatus.h"

#include <QNetworkAccessManager>
#include <QDebug>
#include <QUrl>
#include <QNetworkReply>
#include <KDebug>
#include <QtCore/QFile>


using namespace Attica;


class Provider::Private : public QSharedData {
  public:
    QUrl m_baseUrl;
    QString m_id;
    QUrl m_icon;
    QString m_name;
    QSharedPointer<QNetworkAccessManager> m_qnam;

    Private(const Private& other)
      : QSharedData(other), m_baseUrl(other.m_baseUrl), m_id(other.m_id), m_name(other.m_name), m_qnam(other.m_qnam)
    {
    }
    Private(QSharedPointer<QNetworkAccessManager> qnam, const QString& id, const QUrl& baseUrl, const QString& name, const QUrl& icon)
      : m_baseUrl(baseUrl), m_id(id), m_icon(icon), m_name(name), m_qnam(qnam)
    {
    }
    ~Private()
    {
    }
};


Provider::Provider()
  : d(new Private(QSharedPointer<QNetworkAccessManager>(), QString(), QUrl(), QString(), QUrl()))
{
}

Provider::Provider(const Provider& other)
  : QObject(), d(other.d)
{
}

Provider::Provider(QSharedPointer<QNetworkAccessManager> qnam, const QString& id, const QUrl& baseUrl, const QString& name, const QUrl& icon)
  : d(new Private(qnam, id, baseUrl, name, icon))
{
}

Provider& Provider::operator=(const Attica::Provider & other)
{
    d = other.d;
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

ListJob<Person>* Provider::requestSentInvitations(int page, int pageSize)
{
  QUrl url = createUrl("friend/sentinvitations");
  url.addQueryItem("page", QString::number(page));
  url.addQueryItem("pagesize", QString::number(pageSize));
  qDebug() << "URL:" << url;
  return doRequestPersonList(url);
}

ListJob<Person>* Provider::requestReceivedInvitations(int page, int pageSize)
{
  QUrl url = createUrl("friend/receivedinvitations");
  url.addQueryItem("page", QString::number(page));
  url.addQueryItem("pagesize", QString::number(pageSize));
  qDebug() << "URL:" << url;
  return doRequestPersonList(url);
}

ListJob<Activity>* Provider::requestActivities()
{
    qDebug() << "request activity";
    QUrl url = createUrl( "activity" );
    return doRequestActivityList( url );
}


PostJob* Provider::postActivity(const QString& message)
{
    StringMap postParameters;
    postParameters.insert("message", message);
    return new PostJob(d->m_qnam, createRequest("activity"), postParameters);
}


PostJob* Provider::inviteFriend(const QString& to, const QString& message)
{
    StringMap postParameters;
    postParameters.insert("message", message);
    return new PostJob(d->m_qnam, createRequest("friend/invite/" + to), postParameters);
}


PostJob* Provider::approveFriendship(const QString& to)
{
    return new PostJob(d->m_qnam, createRequest("friend/approve/" + to));
}


PostJob* Provider::declineFriendship(const QString& to)
{
    return new PostJob(d->m_qnam, createRequest("friend/decline/" + to));
}

PostJob* Provider::cancelFriendship(const QString& to)
{
    return new PostJob(d->m_qnam, createRequest("friend/cancel/" + to));
}


PostJob* Provider::postLocation(qreal latitude, qreal longitude, const QString& city, const QString& country)
{
    StringMap postParameters;
    postParameters.insert("latitude", QString::number(latitude));
    postParameters.insert("longitude", QString::number(longitude));
    postParameters.insert("city", city);
    postParameters.insert("country", country);
    return new PostJob(d->m_qnam, createRequest("person/self"), postParameters);
}


ListJob<Folder>* Provider::requestFolders()
{
  return doRequestFolderList( createUrl( "message" ) );
}

ListJob<Message>* Provider::requestMessages(const Folder& folder)
{
  return doRequestMessageList( createUrl( "message/" + folder.id() ) );
}


ItemJob<Message>* Provider::requestMessage(const Folder& folder, const QString& id)
{
    return new ItemJob<Message>(d->m_qnam, createRequest("message/" + folder.id() + '/' + id));
}


PostJob* Provider::postMessage( const Message &message )
{
    StringMap postParameters;
    postParameters.insert("message", message.body());
    postParameters.insert("subject", message.subject());
    postParameters.insert("to", message.to());
    return new PostJob(d->m_qnam, createRequest("message/2"), postParameters);
}


ListJob<Category>* Provider::requestCategories()
{
  QUrl url = createUrl( "content/categories" );
  ListJob<Category> *job = new ListJob<Category>(d->m_qnam, createRequest(url));
  return job;
}

ListJob<Content>* Provider::searchContents(const Category::List& categories, const QString& search, SortMode sortMode, uint page, uint pageSize)
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
  url.addQueryItem( "page", QString::number(page) );
  url.addQueryItem( "pagesize", QString::number(pageSize) );
  
    ListJob<Content> *job = new ListJob<Content>(d->m_qnam, createRequest(url));

  return job;
}

ItemJob<Content>* Provider::requestContent(const QString& id)
{
  QUrl url = createUrl( "content/data/" + id );
  ItemJob<Content> *job = new ItemJob<Content>(d->m_qnam, createRequest(url));
  return job;
}

ItemPostJob<Content>* Provider::addNewContent(const Category& category, const Content& cont)
{
    if (!category.isValid()) {
        return 0;
    }

    QUrl url = createUrl("content/add");
    StringMap pars(cont.attributes());
    
    pars.insert("type", category.id());
    pars.insert("name", cont.name());
    
    qDebug() << "Parameter map: " << pars;
    
    return new ItemPostJob<Content>(d->m_qnam, createRequest(url), pars);
}

PostJob* Provider::setDownloadFile(const QString& contentId, QIODevice* payload)
{
    QUrl url = createUrl("content/uploaddownload/" + contentId);
    return new PostJob(d->m_qnam, createRequest(url), payload);
}

PostJob* Provider::voteForContent(const QString& contentId, bool positiveVote)
{
    StringMap postParameters;
    postParameters.insert("vote", positiveVote ? "good" : "bad");
    return new PostJob(d->m_qnam, createRequest("content/vote/" + contentId), postParameters);
}


ItemJob<DownloadItem>* Provider::downloadLink(const QString& contentId, const QString& itemId)
{
    QUrl url = createUrl( "content/download/" + contentId + '/' + itemId );
    ItemJob<DownloadItem> *job = new ItemJob<DownloadItem>(d->m_qnam, createRequest(url));
    return job;
}

ItemJob<KnowledgeBaseEntry>* Provider::requestKnowledgeBaseEntry(const QString& id)
{
    QUrl url = createUrl( "knowledgebase/data/" + id );
    ItemJob<KnowledgeBaseEntry> *job = new ItemJob<KnowledgeBaseEntry>(d->m_qnam, createRequest(url));
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

  ListJob<KnowledgeBaseEntry> *job = new ListJob<KnowledgeBaseEntry>(d->m_qnam, createRequest(url));
  return job;
}

ItemJob<Event>* Provider::requestEvent(const QString& id)
{
    ItemJob<Event>* job = new ItemJob<Event>(d->m_qnam, createRequest("event/data/" + id));
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

  ListJob<Event>* job = new ListJob<Event>(d->m_qnam, createRequest(url));
  return job;
}

QUrl Provider::createUrl(const QString& path)
{
    QUrl url(d->m_baseUrl.toString() + path);
    return url;
}

QNetworkRequest Provider::createRequest(const QUrl& url)
{
    return QNetworkRequest(url);
}


QNetworkRequest Provider::createRequest(const QString& path)
{
    return createRequest(createUrl(path));
}


PersonJob* Provider::doRequestPerson(const QUrl& url)
{
  return new PersonJob(d->m_qnam, createRequest(url));
}

ListJob<Person>* Provider::doRequestPersonList(const QUrl& url)
{
    return new ListJob<Person>(d->m_qnam, createRequest(url));
}

ListJob<Activity>* Provider::doRequestActivityList(const QUrl& url)
{
    return new ListJob<Activity>(d->m_qnam, createRequest(url));
}

ListJob<Folder>* Provider::doRequestFolderList(const QUrl& url)
{
    return new ListJob<Folder>(d->m_qnam, createRequest(url));
}

ListJob<Message>* Provider::doRequestMessageList(const QUrl& url)
{
    return new ListJob<Message>(d->m_qnam, createRequest(url));
}


#include "provider.moc"
