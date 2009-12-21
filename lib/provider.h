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

#ifndef ATTICA_PROVIDER_H
#define ATTICA_PROVIDER_H

#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>

#include <QUrl>

#include "atticaclient_export.h"
#include "category.h"
#include "itemjob.h"
#include "listjob.h"
#include "message.h"

class QDate;
class QUrl;

namespace Attica {

class PlatformDependent;

class PostJobStatus;

class Activity;
class Content;
class DownloadItem;
class Event;
class Folder;
class KnowledgeBaseEntry;
class Person;
class PostJob;
class Provider;
class AccountBalance;


/**
 * The Provider class represents one Open Collaboration Service provider.
 * Use the ProviderManager to instanciate a Provider.
 *
 * Accessing funtions of the Provider returns a Job class that
 * takes care of accessing the server and parsing the result.
 */
class ATTICA_EXPORT Provider
{
  public:
    Provider();
    Provider(const Provider& other);
    Provider& operator=(const Provider& other);
    ~Provider();

    bool isValid() const;
    QUrl baseUrl() const;
    QString name() const;

    enum SortMode {
        Newest,
        Alphabetical,
        Rating,
        Downloads
    };

    bool hasCredentials();
    bool hasCredentials() const;
    bool loadCredentials(QString& user, QString& password);
    bool saveCredentials(const QString& user, const QString& password);
    
    PostJob* checkLogin(const QString& user, const QString& password);

    // Person part of OCS

    PostJob* registerAccount(const QString& id, const QString& password, const QString& mail, const QString& firstName, const QString& lastName);
    ItemJob<Person>* requestPerson(const QString& id);
    ItemJob<Person>* requestPersonSelf();
    ItemJob<AccountBalance>* requestAccountBalance();
    ListJob<Person>* requestPersonSearchByName(const QString& name);
    ListJob<Person>* requestPersonSearchByLocation(qreal latitude, qreal longitude, qreal distance = 0.0, int page = 0, int pageSize = 20);
    PostJob* postLocation(qreal latitude, qreal longitude, const QString& city = QString(), const QString& country = QString());

    // Friend part of OCS

    ListJob<Person>* requestFriends(const QString& id, int page = 0, int pageSize = 20);
    PostJob* postFriendInvitation(const QString& to, const QString& message);
    ListJob<Person>* requestSentInvitations(int page = 0, int pageSize = 20);
    ListJob<Person>* requestReceivedInvitations(int page = 0, int pageSize = 20);
    PostJob* inviteFriend(const QString& to, const QString& message);
    PostJob* approveFriendship(const QString& to);
    PostJob* declineFriendship(const QString& to);
    PostJob* cancelFriendship(const QString& to);

    // Message part of OCS

    ListJob<Folder>* requestFolders();
    ListJob<Message>* requestMessages(const Folder& folder);
    ListJob<Message>* requestMessages(const Folder& folder, Message::Status status);
    ItemJob<Message>* requestMessage(const Folder& folder, const QString& id);
    PostJob* postMessage(const Message& message);

    // Activity part of OCS

    ListJob<Activity>* requestActivities();
    PostJob* postActivity(const QString& message);

    // Content part of OCS

    /** 
     * Get a list of categories (such as wallpaper)
     * @return the categories of the server
     */
    ListJob<Category>* requestCategories();
    ListJob<Content>* searchContents(const Category::List& categories, const QString& search = QString(), SortMode mode = Rating, uint page = 1, uint pageSize = 10);
    ItemJob<Content>* requestContent(const QString& contentId);

    ItemJob<DownloadItem>* downloadLink(const QString& contentId, const QString& itemId = QLatin1String("1"));

    PostJob* voteForContent(const QString& contentId, bool positiveVote);

    ItemPostJob<Content>* addNewContent(const Category& category, const Content& newContent);
    ItemPostJob<Content>* editContent(const Category& updatedCategory, const QString& contentId, const Content& updatedContent);
    PostJob* deleteContent(const QString& contentId);

    PostJob* setDownloadFile(const QString& contentId, const QString& fileName, QIODevice* payload);
    PostJob* setDownloadFile(const QString& contentId, const QString& fileName, const QByteArray& payload);
    PostJob* deleteDownloadFile(const QString& contentId);

    /**
     * Upload an image file as preview for the content
     * @param contentId
     * @param previewId each content can have previews with the id 1,2 or 3
     * @param payload the image file
     */
    PostJob* setPreviewImage(const QString& contentId, const QString& previewId, const QString& fileName, const QByteArray& image);
    PostJob* deletePreviewImage(const QString& contentId, const QString& previewId);

    // KnowledgeBase part of OCS

    ItemJob<KnowledgeBaseEntry>* requestKnowledgeBaseEntry(const QString& id);
    ListJob<KnowledgeBaseEntry>* searchKnowledgeBase(const Content& content, const QString& search, SortMode, int page, int pageSize);

    // Event part of OCS

    ItemJob<Event>* requestEvent(const QString& id);
    ListJob<Event>* requestEvent(const QString& country, const QString& search, const QDate& startAt, SortMode mode, int page, int pageSize);

    // Fan part of OCS

    PostJob* becomeFan(const QString& contentId);

  protected:
    QUrl createUrl(const QString& path);
    QNetworkRequest createRequest(const QUrl& url);
    // Convenience overload
    QNetworkRequest createRequest(const QString& path);

    ItemJob<Person>* doRequestPerson(const QUrl& url);
    ItemJob<AccountBalance>* doRequestAccountBalance(const QUrl& url);
    ListJob<Person>* doRequestPersonList(const QUrl& url);
    ListJob<Activity>* doRequestActivityList(const QUrl& url);
    ListJob<Folder>* doRequestFolderList(const QUrl& url);
    ListJob<Message>* doRequestMessageList(const QUrl& url);

  private:
    class Private;
    QExplicitlySharedDataPointer<Private> d;
    
    // FIXME use baseUrl as id
    Provider(const QSharedPointer<PlatformDependent>& internals, const QUrl& baseUrl, const QString& name, const QUrl& icon = QUrl());

    // TODO remove
    friend class ProviderManager;
};
}

#endif
