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
#include "accountbalanceparser.h"
#include "activity.h"
#include "activityparser.h"
#include "privatedata.h"
#include "privatedataparser.h"
#include "category.h"
#include "categoryparser.h"
#include "content.h"
#include "contentparser.h"
#include "downloaditem.h"
#include "downloaditemparser.h"
#include "event.h"
#include "eventparser.h"
#include "folder.h"
#include "folderparser.h"
#include "knowledgebaseentry.h"
#include "knowledgebaseentryparser.h"
#include "license.h"
#include "licenseparser.h"
#include "message.h"
#include "messageparser.h"
#include "person.h"
#include "personparser.h"
#include "platformdependent.h"
#include "postjob.h"
#include "postfiledata.h"
#include "itemjob.h"
#include "listjob.h"
#include "comment.h"

#include <QtCore/QStringList>
#include <QNetworkAccessManager>
#include <QDebug>
#include <QUrl>
#include <QNetworkReply>
#include <QtCore/QFile>


using namespace Attica;

class Provider::Private : public QSharedData
{
public:
    QUrl m_baseUrl;
    QUrl m_icon;
    QString m_name;
    QString m_credentialsUserName;
    QString m_credentialsPassword;
    QString m_personVersion;
    QString m_friendVersion;
    QString m_messageVersion;
    QString m_activityVersion;
    QString m_contentVersion;
    QString m_fanVersion;
    QString m_knowledgebaseVersion;
    QString m_eventVersion;
    QString m_commentVersion;
    PlatformDependent* m_internals;
    
    Private()
        :m_internals(0)
    {}
    
    Private(const Private& other)
        : QSharedData(other), m_baseUrl(other.m_baseUrl), m_name(other.m_name)
        , m_internals(other.m_internals), m_credentialsUserName(other.m_credentialsUserName)
        , m_credentialsPassword(other.m_credentialsPassword)
        , m_personVersion(other.m_personVersion)
        , m_friendVersion(other.m_friendVersion)
        , m_messageVersion(other.m_messageVersion)
        , m_activityVersion(other.m_activityVersion)
        , m_contentVersion(other.m_contentVersion)
        , m_fanVersion(other.m_fanVersion)
        , m_knowledgebaseVersion(other.m_knowledgebaseVersion)
        , m_eventVersion(other.m_eventVersion)
        , m_commentVersion(other.m_commentVersion)
    {
    }

Private(PlatformDependent* internals, const QUrl& baseUrl, const QString& name, const QUrl& icon,
        const QString& person, const QString& friendV, const QString& message,
        const QString& activity, const QString& content, const QString& fan,
        const QString& knowledgebase, const QString& event, const QString& comment)
        : m_baseUrl(baseUrl), m_icon(icon), m_name(name), m_internals(internals)
        , m_personVersion(person)
        , m_friendVersion(friendV)
        , m_messageVersion(message)
        , m_activityVersion(activity)
        , m_contentVersion(content)
        , m_fanVersion(fan)
        , m_knowledgebaseVersion(knowledgebase)
        , m_eventVersion(event)
        , m_commentVersion(comment)
    {
        if (m_baseUrl.isEmpty()) {
            return;
        }
        QString user;
        QString pass;
        if (m_internals->hasCredentials(m_baseUrl) && m_internals->loadCredentials(m_baseUrl, user, pass)) {
            m_credentialsUserName = user;
            m_credentialsPassword = pass;
        }
    }

    ~Private()
    {
    }
};


Provider::Provider()
    : d(new Private)
{
}

Provider::Provider(const Provider& other)
    : d(other.d)
{
}

Provider::Provider(PlatformDependent* internals, const QUrl& baseUrl, const QString& name, const QUrl& icon,
                   const QString& person, const QString& friendV, const QString& message,
                   const QString& activity, const QString& content, const QString& fan,
                   const QString& knowledgebase, const QString& event, const QString& comment)
    : d(new Private(internals, baseUrl, name, icon, person, friendV, message, activity, content, fan, knowledgebase, event, comment))
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

bool Provider::isEnabled() const
{
    return d->m_internals->isEnabled(d->m_baseUrl);
}

void Provider::setEnabled(bool enabled)
{
    d->m_internals->enableProvider(d->m_baseUrl, enabled);
}

QString Provider::name() const
{
    return d->m_name;
}

bool Provider::hasCredentials()
{
    return d->m_internals->hasCredentials(d->m_baseUrl);
}

bool Provider::hasCredentials() const
{
    return d->m_internals->hasCredentials(d->m_baseUrl);
}

bool Provider::loadCredentials(QString& user, QString& password)
{
    return d->m_internals->loadCredentials(d->m_baseUrl, user, password);
}

bool Provider::saveCredentials(const QString& user, const QString& password)
{
    return d->m_internals->saveCredentials(d->m_baseUrl, user, password);
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

ListJob< License >* Provider::requestLicenses()
{
    QUrl url = createUrl( "content/licenses" );
    ListJob<License> *job = new ListJob<License>(d->m_internals, createRequest(url));
    return job;
}

ListJob<Content>* Provider::searchContents(const Category::List& categories, const QString& search, SortMode sortMode, uint page, uint pageSize)
{
    return searchContentsByPerson(categories, QString(), search, sortMode, page, pageSize);
}

ListJob<Content>* Provider::searchContentsByPerson(const Category::List& categories, const QString& person, const QString& search, SortMode sortMode, uint page, uint pageSize)
{
    QUrl url = createUrl( "content/data" );

    QStringList categoryIds;
    foreach( const Category &category, categories ) {
        categoryIds.append( category.id() );
    }
    url.addQueryItem( "categories", categoryIds.join( "x" ) );

    if (!person.isEmpty()) {
        url.addQueryItem( "user", person );
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
    qDebug() << "vote: " << positiveVote;
    return new PostJob(d->m_internals, createRequest("content/vote/" + contentId), postParameters);
}

PostJob* Provider::voteForContent(const QString& contentId, uint rating)
{
    // according to OCS API, the rating is 0..100
    Q_ASSERT(rating <= 100);
    StringMap postParameters;
    postParameters.insert("vote", QString::number(rating));
    qDebug() << "vote: " << QString::number(rating);
    return new PostJob(d->m_internals, createRequest("content/vote/" + contentId), postParameters);
}

PostJob* Provider::becomeFan(const QString& contentId)
{
    QUrl url = createUrl("fan/add/" + contentId);
    PostFileData postRequest(url);
    postRequest.addArgument("contentid", contentId);
    return new PostJob(d->m_internals, postRequest.request(), postRequest.data());
}

ListJob<Person>* Provider::requestFans(const QString& contentId, uint page, uint pageSize)
{
    QUrl url = createUrl( "fan/data/" + contentId );
    url.addQueryItem( "contentid", contentId );
    url.addQueryItem( "page", QString::number(page) );
    url.addQueryItem( "pagesize", QString::number(pageSize) );
    ListJob<Person> *job = new ListJob<Person>(d->m_internals, createRequest(url));
    return job;
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

ListJob<Comment>* Provider::requestComments(const Provider::CommentType commentType, const QString& id, const QString& id2, int page, int pageSize)
{
    QString commentTypeString;
    commentTypeString = commentTypeToString(commentType);
    if (!commentTypeString.isEmpty()) {
        return 0;
    }
 
    QUrl url = createUrl("comments/data/" + commentTypeString + "/" + id + "/" + id2);

    url.addQueryItem("page", QString::number(page));
    url.addQueryItem("pagesize", QString::number(pageSize));

    ListJob<Comment>* job = new ListJob<Comment>(d->m_internals, createRequest(url));
    return job;
}

PostJob* Provider::addNewComment(const Provider::CommentType commentType, const QString& id, const QString& id2, const QString& parentId, const QString &subject, const QString& message)
{
    QString commentTypeString;
    commentTypeString = commentTypeToString(commentType);
    if (!commentTypeString.isEmpty()) {
        return 0;
    }

    QMap<QString, QString> postParameters;

    postParameters.insert("type", commentTypeString);
    postParameters.insert("content", id);
    postParameters.insert("content2", id2);
    postParameters.insert("parent", parentId);
    postParameters.insert("subject", subject);
    postParameters.insert("message", message);

    return new PostJob(d->m_internals, createRequest("comments/add"), postParameters);
}

PostJob* Provider::voteForComment(const QString & id, uint rating)
{
    if (rating > 100) {
        return 0;
    }

    QMap<QString, QString> postParameters;
    postParameters.insert("vote", QString::number(rating));

    QUrl url = createUrl("comments/vote/" + id);
    return new PostJob(d->m_internals, createRequest(url), postParameters);
}

QString Provider::commentTypeToString(const Provider::CommentType type) const
{
    switch(type) {
    case ContentComment:
        return QString("1");
        break;
    case ForumComment:
        return QString("4");
        break;
    case KnowledgeBaseComment:
        return QString("7");
        break;
    case EventComment:
        return QString("8");
        break;
    }

    Q_ASSERT(false);
    return QString();
}

PostJob* Provider::setPrivateData(const QStringList& keys, const QStringList& values)
{
    Q_ASSERT(keys.size() == values.size());
    
    QUrl url = createUrl("person/privatedata/set/");
    PostFileData postRequest(url);

    for (int i=0; i<keys.size(); i++) {
        postRequest.addArgument(keys[i], values[i]); //I'm not good with XML, what is this?
    }
    return new PostJob(d->m_internals, postRequest.request(), postRequest.data());
}

ItemJob<PrivateData>* Provider::requestPrivateData(const QString& key)
{
    ItemJob<PrivateData>* job = new ItemJob<PrivateData>(d->m_internals, createRequest("person/privatedata/search/" + key));
    return job;
}

QUrl Provider::createUrl(const QString& path)
{
    QUrl url(d->m_baseUrl.toString() + path);
    if (!d->m_credentialsUserName.isEmpty()) {
        url.setUserName(d->m_credentialsUserName);
        url.setPassword(d->m_credentialsPassword);
    }
    return url;
}

QNetworkRequest Provider::createRequest(const QUrl& url)
{
    QNetworkRequest request(url);

    if (!d->m_credentialsUserName.isEmpty()) {
        QString concatenated = d->m_credentialsUserName + ':' + d->m_credentialsPassword;
        QByteArray data = concatenated.toLocal8Bit().toBase64();
        QString headerData = "Basic " + data;
        request.setRawHeader("Authorization", headerData.toLocal8Bit());
    }

    return request;
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

QString Provider::activityServiceVersion() const
{
    return d->m_activityVersion;
}
QString Provider::commentServiceVersion() const
{
    return d->m_commentVersion;
}
QString Provider::contentServiceVersion() const
{
    return d->m_contentVersion;
}
QString Provider::fanServiceVersion() const
{
    return d->m_fanVersion;
}
QString Provider::friendServiceVersion() const
{
    return d->m_friendVersion;
}
QString Provider::knowledgebaseServiceVersion() const
{
    return d->m_knowledgebaseVersion;
}
QString Provider::messageServiceVersion() const
{
    return d->m_messageVersion;
}
QString Provider::personServiceVersion() const
{
    return d->m_personVersion;
}

bool Provider::hasActivityService() const
{
    return !d->m_activityVersion.isEmpty();
}
bool Provider::hasCommentService() const
{
    return !d->m_commentVersion.isEmpty();
}
bool Provider::hasContentService() const
{
    return !d->m_contentVersion.isEmpty();
}
bool Provider::hasFanService() const
{
    return !d->m_fanVersion.isEmpty();
}
bool Provider::hasFriendService() const
{
    return !d->m_friendVersion.isEmpty();
}
bool Provider::hasKnowledgebaseService() const
{
    return !d->m_knowledgebaseVersion.isEmpty();
}
bool Provider::hasMessageService() const
{
    return !d->m_messageVersion.isEmpty();
}
bool Provider::hasPersonService() const
{
    return !d->m_personVersion.isEmpty();
}
