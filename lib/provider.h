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

#include <QtCore/QUrl>

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

class AccountBalance;
class Activity;
class PrivateData;
class Comment;
class Content;
class DownloadItem;
class Distribution;
class Event;
class Folder;
class HomePageType;
class KnowledgeBaseEntry;
class License;
class Person;
class PostJob;
class Provider;

/**
 * The Provider class represents one Open Collaboration Service provider.
 * Use the ProviderManager to instanciate a Provider.
 *
 * Accessing functions of the Provider returns a Job class that
 * takes care of accessing the server and parsing the result.
 *
 * Provider files are xml of the form:
 <pre>
 <provider>
 <id>opendesktop</id>
 <location>https://api.opendesktop.org/v1/</location>
 <name>openDesktop.org</name>
 <icon></icon>
 <termsofuse>https://opendesktop.org/terms/</termsofuse>
 <register>https://opendesktop.org/usermanager/new.php</register>
 <services>
   <person ocsversion="1.3" />
   <friend ocsversion="1.3" />
   <message ocsversion="1.3" />
   <activity ocsversion="1.3" />
   <content ocsversion="1.3" />
   <fan ocsversion="1.3" />
   <knowledgebase ocsversion="1.3" />
   <event ocsversion="1.3" />
   <comment ocsversion="1.2" />
 </services>
</provider>
 </pre>
 * The server provides the services specified in the services section, not necessarily all of them. 
 */
class ATTICA_EXPORT Provider
{
  public:
    Provider();
    Provider(const Provider& other);
    Provider& operator=(const Provider& other);
    ~Provider();

    /**
    Returns true if the provider has been set up and can be used.
    */
    bool isValid() const;
    
    /**
    Test if the provider is enabled by the settings.
    The application can choose to ignore this, but the user settings should be respected.
    */
    bool isEnabled() const;
    void setEnabled(bool enabled);
    
    /**
    A url that identifies this provider.
    This should be used as identifier when refering to this provider but you don't want to use the full provider object.
    */
    QUrl baseUrl() const;
    
    /**
    A name for the provider that can be displayed to the user
    */
    QString name() const;

    enum SortMode {
        Newest,
        Alphabetical,
        Rating,
        Downloads
    };

    /**
    Test if the server supports the person part of the API
    */
    bool hasPersonService() const;
    /**
    Version of the person part of the API
    */
    QString personServiceVersion() const;
    
    /**
    Test if the server supports the friend part of the API
    */
    bool hasFriendService() const;
    
    /**
    Version of the friend part of the API
    */
    QString friendServiceVersion() const;
    
    /**
    Test if the server supports the message part of the API
    */
    bool hasMessageService() const;
    /**
    Version of the message part of the API
    */
    QString messageServiceVersion() const;
    
    /**
    Test if the server supports the activity part of the API
    */
    bool hasActivityService() const;
    /**
    Version of the activity part of the API
    */
    QString activityServiceVersion() const;
    
    /**
    Test if the server supports the content part of the API
    */
    bool hasContentService() const;
    /**
    Version of the content part of the API
    */
    QString contentServiceVersion() const;
    
    /**
    Test if the server supports the fan part of the API
    */
    bool hasFanService() const;
    /**
    Version of the fan part of the API
    */
    QString fanServiceVersion() const;
    
    /**
    Test if the server supports the knowledgebase part of the API
    */
    bool hasKnowledgebaseService() const;
    /**
    Version of the knowledgebase part of the API
    */
    QString knowledgebaseServiceVersion() const;
    
    /**
    Test if the server supports the comments part of the API
    */
    bool hasCommentService() const;
    /**
    Version of the comments part of the API
    */
    QString commentServiceVersion() const;

    /**
      Test if the provider has user name/password available.
      This does not yet open kwallet in case the KDE plugin is used.
      @return true if the provider has login information
    */
    bool hasCredentials() const;
    bool hasCredentials();
    
    /**
      Load user name and password from the store.
      Attica will remember the loaded values and use them from this point on.
      @param user reference that returns the user name
      @param password reference that returns the password
      @return if credentials could be loaded
    */
    bool loadCredentials(QString& user, QString& password);
    
    /**
      Sets (and remembers) user name and password for this provider.
      To remove the data an empty username should be passed.
      @param user the user (login) name
      @param password the password
      @return if credentials could be saved
    */
    bool saveCredentials(const QString& user, const QString& password);
    
    /**
      Test if the server accepts the login/password.
      This function does not actually set the credentials. Use saveCredentials for that purpose.
      @param user the user (login) name
      @param password the password
      @return the job that will contain the success of the login as metadata
    */
    PostJob* checkLogin(const QString& user, const QString& password);

    // Person part of OCS

    PostJob* registerAccount(const QString& id, const QString& password, const QString& mail, const QString& firstName, const QString& lastName);
    ItemJob<Person>* requestPerson(const QString& id);
    ItemJob<Person>* requestPersonSelf();
    ItemJob<AccountBalance>* requestAccountBalance();
    ListJob<Person>* requestPersonSearchByName(const QString& name);
    ListJob<Person>* requestPersonSearchByLocation(qreal latitude, qreal longitude, qreal distance = 0.0, int page = 0, int pageSize = 20);
    PostJob* postLocation(qreal latitude, qreal longitude, const QString& city = QString(), const QString& country = QString());
    ItemJob<PrivateData>* requestPrivateData(const QString& key = QString());
    PostJob* setPrivateData(const QString &key, const QString &value);

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
    
    /** 
    * Get a list of licenses (such as GPL)
    * @return the licenses available from the server
    */
    ListJob<License>* requestLicenses();

    /**
    * Get a list of distributions (such as Ark, Debian)
    * @return the licenses available from the server
    */
    ListJob<Distribution>* requestDistributions();

    /**
    * Get a list of home page types (such as blog, Facebook)
    * @return the licenses available from the server
    */
    ListJob<HomePageType>* requestHomePageTypes();

    /**
      Request a list of Contents.
      Note that @p categories is not optional. If left empty, no results will be returned.
      An empty search string @p search returns the top n items.
      @param categories categories to search in
      @param search optional search string (in name/description of the content)
      @param mode sorting mode
      @param page request nth page in the list of results
      @param pageSize requested size of pages when calculating the list of results
      @return list job for the search results
      */
    ListJob<Content>* searchContents(const Category::List& categories, const QString& search = QString(), SortMode mode = Rating, uint page = 0, uint pageSize = 10);

    /**
      Request a list of Contents.
      Like @see searchContents, but only contents created by one person.
      @param person the person-id that created the contents.
     */
    ListJob<Content>* searchContentsByPerson(const Category::List& categories, const QString& person, const QString& search = QString(), SortMode mode = Rating, uint page = 0, uint pageSize = 10);

    /**
      Retrieve a single content.
      @param contentId the id of the content
      @return job that retrieves the content object
     */
    ItemJob<Content>* requestContent(const QString& contentId);

    ItemJob<DownloadItem>* downloadLink(const QString& contentId, const QString& itemId = QLatin1String("1"));

    /** Vote for a content item
     * This version is for the old OCS API < 1.6
     * @param contentId the content which this voting is for
     * @param positiveVote whether the voting is positive or negative
     * @return the post job for this voting
     */
    Q_DECL_DEPRECATED PostJob* voteForContent(const QString& contentId, bool positiveVote);

    /** Vote for a content item
     * @param contentId the content which this voting is for
     * @param rating - the rating, must be between 0 (bad) and 100 (good)
     * @return the post job for this voting
     */
    PostJob* voteForContent(const QString& contentId, uint rating);

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

    // Comment part of OCS
    enum CommentType {
        ContentComment,
        ForumComment,
        KnowledgeBaseComment,
        EventComment
    };

    /** Request a list of comments for a content / forum / knowledgebase / event.
     * @param commentType type of the comment @see CommentType (content / forum / knowledgebase / event)
     * @param id id of the content entry where you want to get the comments is from
     * @param id2 id of the content entry where you want to get the comments is from
     * @param page request nth page in the list of results
     * @param pageSize requested size of pages when calculating the list of results
     * @return list job for the comments results
     */
    ListJob<Comment>* requestComments(const CommentType commentType, const QString& id, const QString& id2, int page, int pageSize);

    /** Add a new comment.
     * @param commentType type of the comment @see CommentType (content / forum / knowledgebase / event)
     * @param id id of the content entry where you want to get the comments is from
     * @param id2 id of the sub content entry where you want to get the comments is from
     * @param parentId the id of the parent comment if the new comment is a reply
     * @param subject title of the comment
     * @param message text of the comment
     * @return post job for adding the new comment
     */
    PostJob* addNewComment(const CommentType commentType, const QString& id, const QString& id2, const QString& parentId, const QString &subject, const QString& message);

    /** Vote a comment item
     * @param id the comment id which this voting is for
     * @param rating the rating, must be between 0 (bad) and 100 (good)
     * @return the post job for this voting
     */
    PostJob* voteForComment(const QString & id, uint rating);

    // Fan part of OCS

    PostJob* becomeFan(const QString& contentId);
    ListJob<Person>* requestFans(const QString& contentId, uint page = 0, uint pageSize = 10);

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
    
    Provider(PlatformDependent* internals, const QUrl& baseUrl, const QString& name, const QUrl& icon = QUrl());
    Provider(PlatformDependent* internals, const QUrl& baseUrl, const QString& name, const QUrl& icon,
             const QString& person, const QString& friendV, const QString& message,
             const QString& activity, const QString& content, const QString& fan,
             const QString& knowledgebase, const QString& event, const QString& comment);
    
    QString commentTypeToString(const Provider::CommentType type) const;

friend class ProviderManager;
};
}

#endif
