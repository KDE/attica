/*
    This file is part of KDE.

    Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>

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

#include "provider.h"

#include "accountbalance.h"
#include "activity.h"
#include "content.h"
#include "downloaditem.h"
#include "event.h"
#include "folder.h"
#include "knowledgebaseentry.h"
#include "message.h"
#include "person.h"
#include "platformdependent.h"
#include "postjob.h"
#include "postfiledata.h"
#include "itemjob.h"
#include "listjob.h"

#include <QtCore/QStringList>
#include <QNetworkAccessManager>
#include <QDebug>
#include <QUrl>
#include <QNetworkReply>
#include <QtCore/QFile>


using namespace Attica;

class Provider::Private : public QSharedData {
  public:
    QUrl m_baseUrl;
    QUrl m_icon;
    QString m_name;
    QSharedPointer<PlatformDependent> m_internals;
    QString m_credentialsUserName;
    QString m_credentialsPassword;

    Private(const Private& other)
      : QSharedData(other), m_baseUrl(other.m_baseUrl), m_name(other.m_name)
      , m_internals(other.m_internals), m_credentialsUserName(other.m_credentialsUserName)
      , m_credentialsPassword(other.m_credentialsPassword)
    {
    }

    Private(const QSharedPointer<PlatformDependent>& internals, const QUrl& baseUrl, const QString& name, const QUrl& icon)
      : m_baseUrl(baseUrl), m_icon(icon), m_name(name), m_internals(internals)
    {
        if (m_baseUrl.isEmpty()) {
            return;
        }
        QString user;
        QString pass;
        if (m_internals->loadCredentials(m_baseUrl, user, pass)) {
            m_credentialsUserName = user;
            m_credentialsPassword = pass;
        }
    }

    ~Private()
    {
    }
};


Provider::Provider()
  : d(new Private(QSharedPointer<PlatformDependent>(0), QUrl(), QString(), QUrl()))
{
}

Provider::Provider(const Provider& other)
  : QObject(), d(other.d)
{
}

Provider::Provider(const QSharedPointer<PlatformDependent>& internals, const QUrl& baseUrl, const QString& name, const QUrl& icon)
  : d(new Private(internals, baseUrl, name, icon))
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


QString Provider::name() const
{
    return d->m_name;
}


PostJob* Provider::checkLogin(const QString& user, const QString& password)
{
    QMap<QString, QString> postParameters;

    postParameters.insert("login", user);
    postParameters.insert("password", password);

    return new PostJob(d->m_internals, createRequest("person/check"), postParameters);
}

PostJob* Provider::registerAccount(const QString& id, const QString& password, const QString& mail, const QString& firstName, const QString& lastName)
{
    QMap<QString, QString> postParameters;

    postParameters.insert("login", id);
    postParameters.insert("password", password);
    postParameters.insert("firstname", firstName);
    postParameters.insert("lastname", lastName);
    postParameters.insert("email", mail);

    return new PostJob(d->m_internals, createRequest("person/add"), postParameters);
}


ItemJob<Person>* Provider::requestPerson(const QString& id)
{
  QUrl url = createUrl( "person/data/" + id );
  return doRequestPerson( url );
}

ItemJob<Person>* Provider::requestPersonSelf()
{
  QUrl url = createUrl( "person/self" );
  return doRequestPerson( url );
}

ItemJob<AccountBalance>* Provider::requestAccountBalance()
{
  QUrl url = createUrl( "person/balance" );
  return doRequestAccountBalance( url );
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
  if (distance > 0.0) {
    url.addQueryItem("distance", QString::number(distance));
  }
  url.addQueryItem("page", QString::number(page));
  url.addQueryItem("pagesize", QString::number(pageSize));
  
  return doRequestPersonList( url );
}

ListJob<Person>* Provider::requestFriends(const QString& id, int page, int pageSize)
{
  QUrl url = createUrl( "friend/data/" + id );
  url.addQueryItem("page", QString::number(page));
  url.addQueryItem("pagesize", QString::number(pageSize));

  return doRequestPersonList( url );
}

ListJob<Person>* Provider::requestSentInvitations(int page, int pageSize)
{
  QUrl url = createUrl("friend/sentinvitations");
  url.addQueryItem("page", QString::number(page));
  url.addQueryItem("pagesize", QString::number(pageSize));

  return doRequestPersonList(url);
}

ListJob<Person>* Provider::requestReceivedInvitations(int page, int pageSize)
{
  QUrl url = createUrl("friend/receivedinvitations");
  url.addQueryItem("page", QString::number(page));
  url.addQueryItem("pagesize", QString::number(pageSize));

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
    return new PostJob(d->m_internals, createRequest("activity"), postParameters);
}


PostJob* Provider::inviteFriend(const QString& to, const QString& message)
{
    StringMap postParameters;
    postParameters.insert("message", message);
    return new PostJob(d->m_internals, createRequest("friend/invite/" + to), postParameters);
}


PostJob* Provider::approveFriendship(const QString& to)
{
    return new PostJob(d->m_internals, createRequest("friend/approve/" + to));
}


PostJob* Provider::declineFriendship(const QString& to)
{
    return new PostJob(d->m_internals, createRequest("friend/decline/" + to));
}

PostJob* Provider::cancelFriendship(const QString& to)
{
    return new PostJob(d->m_internals, createRequest("friend/cancel/" + to));
}


PostJob* Provider::postLocation(qreal latitude, qreal longitude, const QString& city, const QString& country)
{
    StringMap postParameters;
    postParameters.insert("latitude", QString::number(latitude));
    postParameters.insert("longitude", QString::number(longitude));
    postParameters.insert("city", city);
    postParameters.insert("country", country);
    return new PostJob(d->m_internals, createRequest("person/self"), postParameters);
}


ListJob<Folder>* Provider::requestFolders()
{
  return doRequestFolderList( createUrl( "message" ) );
}

ListJob<Message>* Provider::requestMessages(const Folder& folder)
{
  return doRequestMessageList( createUrl( "message/" + folder.id() ) );
}


ListJob<Message>* Provider::requestMessages(const Folder& folder, Message::Status status)
{
    QUrl url = createUrl("message/" + folder.id());
    url.addQueryItem("status", QString::number(status));
    return doRequestMessageList(url);
}


ItemJob<Message>* Provider::requestMessage(const Folder& folder, const QString& id)
{
    return new ItemJob<Message>(d->m_internals, createRequest("message/" + folder.id() + '/' + id));
}


PostJob* Provider::postMessage( const Message &message )
{
    StringMap postParameters;
    postParameters.insert("message", message.body());
    postParameters.insert("subject", message.subject());
    postParameters.insert("to", message.to());
    return new PostJob(d->m_internals, createRequest("message/2"), postParameters);
}

ListJob<Category>* Provider::requestCategories()
{
  QUrl url = createUrl( "content/categories" );
  ListJob<Category> *job = new ListJob<Category>(d->m_internals, createRequest(url));
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
  
    ListJob<Content> *job = new ListJob<Content>(d->m_internals, createRequest(url));

  return job;
}

ItemJob<Content>* Provider::requestContent(const QString& id)
{
  QUrl url = createUrl( "content/data/" + id );
  ItemJob<Content> *job = new ItemJob<Content>(d->m_internals, createRequest(url));
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
    
    return new ItemPostJob<Content>(d->m_internals, createRequest(url), pars);
}


ItemPostJob<Content>* Provider::editContent(const Category& updatedCategory, const QString& contentId, const Content& updatedContent)
{
    // FIXME I get a server error message here, though the name of the item is changed
    QUrl url = createUrl("content/edit/" + contentId);
    StringMap pars(updatedContent.attributes());

    pars.insert("type", updatedCategory.id());
    pars.insert("name", updatedContent.name());

    qDebug() << "Parameter map: " << pars;

    return new ItemPostJob<Content>(d->m_internals, createRequest(url), pars);
}

/*
PostJob* Provider::setDownloadFile(const QString& contentId, QIODevice* payload)
{
    QUrl url = createUrl("content/uploaddownload/" + contentId);
    PostFileData postRequest(url);
    // FIXME mime type
    //postRequest.addFile("localfile", payload, "application/octet-stream");
    postRequest.addFile("localfile", payload, "image/jpeg");
    return new PostJob(d->m_internals, postRequest.request(), postRequest.data());
}
*/

PostJob* Provider::deleteContent(const QString& contentId)
{
    QUrl url = createUrl("content/delete/" + contentId);
    PostFileData postRequest(url);
    postRequest.addArgument("contentid", contentId);
    return new PostJob(d->m_internals, postRequest.request(), postRequest.data());
}

PostJob* Provider::setDownloadFile(const QString& contentId, const QString& fileName, const QByteArray& payload)
{
    QUrl url = createUrl("content/uploaddownload/" + contentId);
    PostFileData postRequest(url);
    // FIXME mime type
    postRequest.addFile(fileName, payload, "application/octet-stream");
    return new PostJob(d->m_internals, postRequest.request(), postRequest.data());
}

PostJob* Provider::deleteDownloadFile(const QString& contentId)
{
    QUrl url = createUrl("content/deletedownload/" + contentId);
    PostFileData postRequest(url);
    postRequest.addArgument("contentid", contentId);
    return new PostJob(d->m_internals, postRequest.request(), postRequest.data());
}

PostJob* Provider::setPreviewImage(const QString& contentId, const QString& previewId, const QString& fileName, const QByteArray& image)
{
    QUrl url = createUrl("content/uploadpreview/" + contentId + '/' + previewId);

    PostFileData postRequest(url);
    postRequest.addArgument("contentid", contentId);
    postRequest.addArgument("previewid", previewId);
    // FIXME mime type
    postRequest.addFile(fileName, image, "application/octet-stream");

    return new PostJob(d->m_internals, postRequest.request(), postRequest.data());
}

PostJob* Provider::deletePreviewImage(const QString& contentId, const QString& previewId)
{
    QUrl url = createUrl("content/deletepreview/" + contentId + '/' + previewId);
    PostFileData postRequest(url);
    postRequest.addArgument("contentid", contentId);
    postRequest.addArgument("previewid", previewId);
    return new PostJob(d->m_internals, postRequest.request(), postRequest.data());
}

PostJob* Provider::voteForContent(const QString& contentId, bool positiveVote)
{
    StringMap postParameters;
    postParameters.insert("vote", positiveVote ? "good" : "bad");
    return new PostJob(d->m_internals, createRequest("content/vote/" + contentId), postParameters);
}

PostJob* Provider::becomeFan(const QString& contentId)
{
    QUrl url = createUrl("fan/add/" + contentId);
    PostFileData postRequest(url);
    postRequest.addArgument("contentid", contentId);
    return new PostJob(d->m_internals, postRequest.request(), postRequest.data());
}

ItemJob<DownloadItem>* Provider::downloadLink(const QString& contentId, const QString& itemId)
{
    QUrl url = createUrl( "content/download/" + contentId + '/' + itemId );
    ItemJob<DownloadItem> *job = new ItemJob<DownloadItem>(d->m_internals, createRequest(url));
    return job;
}

ItemJob<KnowledgeBaseEntry>* Provider::requestKnowledgeBaseEntry(const QString& id)
{
    QUrl url = createUrl( "knowledgebase/data/" + id );
    ItemJob<KnowledgeBaseEntry> *job = new ItemJob<KnowledgeBaseEntry>(d->m_internals, createRequest(url));
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

  ListJob<KnowledgeBaseEntry> *job = new ListJob<KnowledgeBaseEntry>(d->m_internals, createRequest(url));
  return job;
}

ItemJob<Event>* Provider::requestEvent(const QString& id)
{
    ItemJob<Event>* job = new ItemJob<Event>(d->m_internals, createRequest("event/data/" + id));
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

  ListJob<Event>* job = new ListJob<Event>(d->m_internals, createRequest(url));
  return job;
}

QUrl Provider::createUrl(const QString& path)
{
    qDebug() << "create url" << path << " user: " << d->m_credentialsUserName;
    QUrl url(d->m_baseUrl.toString() + path);
    if (!d->m_credentialsUserName.isEmpty()) {
        url.setUserName(d->m_credentialsUserName);
        url.setPassword(d->m_credentialsPassword);
    }
    return url;
}

QNetworkRequest Provider::createRequest(const QUrl& url)
{
    qDebug() << "request with url: " << url.toString() << url.userName();
    return QNetworkRequest(url);
}


QNetworkRequest Provider::createRequest(const QString& path)
{
    return createRequest(createUrl(path));
}


ItemJob<Person>* Provider::doRequestPerson(const QUrl& url)
{
  return new ItemJob<Person>(d->m_internals, createRequest(url));
}

ItemJob<AccountBalance>* Provider::doRequestAccountBalance(const QUrl& url)
{
  return new ItemJob<AccountBalance>(d->m_internals, createRequest(url));
}

ListJob<Person>* Provider::doRequestPersonList(const QUrl& url)
{
    return new ListJob<Person>(d->m_internals, createRequest(url));
}

ListJob<Activity>* Provider::doRequestActivityList(const QUrl& url)
{
    return new ListJob<Activity>(d->m_internals, createRequest(url));
}

ListJob<Folder>* Provider::doRequestFolderList(const QUrl& url)
{
    return new ListJob<Folder>(d->m_internals, createRequest(url));
}

ListJob<Message>* Provider::doRequestMessageList(const QUrl& url)
{
    return new ListJob<Message>(d->m_internals, createRequest(url));
}


#include "provider.moc"
