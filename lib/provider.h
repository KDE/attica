/*
    This file is part of KDE.

    Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>
    Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>

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
#include <QtCore/QStringList>

#include <QtCore/QUrl>

#include "achievement.h"
#include "atticaclient_export.h"
#include "category.h"
#include "forum.h"
#include "job.h"
#include "message.h"
#include "comment.h"
#include "distribution.h"
#include "license.h"

class QDate;
class QUrl;

namespace Attica {

class PlatformDependent;

class JobStatus;

class AccountBalance;
class Activity;
class BuildServiceJobOutput;
class BuildServiceJob;
class BuildService;
class PrivateData;
class Content;
class DownloadItem;
class Distribution;
class Event;
class Folder;
class HomePageType;
class KnowledgeBaseEntry;
class License;
class Person;
class NoneType;
class Project;
class Provider;
class Publisher;
class PublisherField;
class RemoteAccount;


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
    This should be used as identifier when referring to this provider but you don't want to use the full provider object.
    */
    QUrl baseUrl() const;

    /**
    A name for the provider that can be displayed to the user
    */
    QString name() const;

    /**
    Choose which format should be used in the communication with the server. The default is XML.
    */
    FormatType format();
    void setFormat( FormatType format );

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
    Test if the server supports the achievement part of the API
    */
    bool hasAchievementService() const;
    /**
    Version of the achievement part of the API
    */
    QString achievementServiceVersion() const;

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
    Test if the server supports the forum part of the API
    */
    bool hasForumService() const;
    /**
    Version of the forum part of the API
    */
    QString forumServiceVersion() const;

    /**
     *
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
    Job<NoneType>* checkLogin(const QString& user, const QString& password);

    // Person part of OCS

    Job<NoneType>* registerAccount(const QString& id, const QString& password, const QString& mail, const QString& firstName, const QString& lastName);
    Job<Person>* requestPerson(const QString& id);
    Job<Person>* requestPersonSelf();
    Job<AccountBalance>* requestAccountBalance();
    Job<Person>* requestPersonSearchByName(const QString& name);
    Job<Person>* requestPersonSearchByLocation(qreal latitude, qreal longitude, qreal distance = 0.0, int page = 0, int pageSize = 20);
    Job<NoneType>* postLocation(qreal latitude, qreal longitude, const QString& city = QString(), const QString& country = QString());

    //////////////////////////
    // PrivateData part of OCS

    /**
     * Fetches the a given attribute from an OCS-compliant server.
     * @param app The application name
     * @param key The key of the attribute to fetch (optional)
     * @return The job that is responsible for fetching the data
     */
    Job<PrivateData>* requestPrivateData(const QString& app, const QString& key = QString());

    /**
     * Fetches all stored private data.
     * @return The job responsible for fetching data
     */
    Job<PrivateData>* requestPrivateData() { return requestPrivateData(QString(), QString()); }

    /**
     * Sets the value of an attribute.
     * @param app The application name
     * @param key The key of the attribute
     * @param value The new value of the attribute
     * @return The job responsible for setting data
     */
    Job<NoneType>* setPrivateData(const QString &app, const QString &key, const QString &value);

    // Friend part of OCS

    Job<Person>* requestFriends(const QString& id, int page = 0, int pageSize = 20);
    Job<NoneType>* postFriendInvitation(const QString& to, const QString& message);
    Job<Person>* requestSentInvitations(int page = 0, int pageSize = 20);
    Job<Person>* requestReceivedInvitations(int page = 0, int pageSize = 20);
    Job<NoneType>* inviteFriend(const QString& to, const QString& message);
    Job<NoneType>* approveFriendship(const QString& to);
    Job<NoneType>* declineFriendship(const QString& to);
    Job<NoneType>* cancelFriendship(const QString& to);

    // Message part of OCS

    Job<Folder>* requestFolders();
    Job<Message>* requestMessages(const Folder& folder);
    Job<Message>* requestMessages(const Folder& folder, Message::Status status);
    Job<Message>* requestMessage(const Folder& folder, const QString& id);
    Job<NoneType>* postMessage(const Message& message);

    // Achievement part of OCS
    /**
     * Get a list of achievements
     * @return Job listing Achievements
     */
    Job<Achievement>* requestAchievements(const QString& contentId, const QString& achievementId, const QString& userId);

    /** Add a new achievement.
     * @param id id of the achievement entry
     * @param achievement The new Achievement added
     * @return item post job for adding the new achievement
     */
    Job<Achievement>* addNewAchievement(const QString& id, const Achievement& newAchievement);

    /**
     * Post modifications to an Achievement on the server
     * @param achievement Achievement to update on the server
     */
    Job<Achievement>* editAchievement(const QString& contentId, const QString& achievementId, const Achievement& achievement);

    /**
     * Deletes an achievement on the server. The achievement passed as an argument doesn't need complete
     * information as just the id() is used.
     * @param achievement Achievement to delete on the server.
     */
    Job<Achievement>* deleteAchievement(const QString& contentId, const QString& achievementId);

    // Job<NoneType>* postAchievement(const Achievement& achievement);
    Job<Achievement>* setAchievementProgress(const QString& id, const QVariant& progress, const QDateTime& timestamp);
    Job<Achievement>* resetAchievementProgress(const QString& id);

    // Activity part of OCS

    Job<Activity>* requestActivities();
    Job<NoneType>* postActivity(const QString& message);

    // Project part of OCS
    /**
     * Get a list of build service projects
     * @return Job listing Projects
     */
    Job<Project>* requestProjects();

    /**
     * Get a Project's data
     * @return Job receiving data
     */
    Job<Project>* requestProject(const QString& id);

    /**
     * Post modifications to a Project on the server. The resulting project ID can be found in
     * the Attica::MetaData of the finished() Job<NoneType>. You can retrieve it using
     * Attica::MetaData::resultingProjectId().
     * @param project Project to create on the server
     */
    Job<NoneType>* createProject(const Project& project);

    /**
     * Deletes a project on the server. The project passed as an argument doesn't need complete
     * information as just the id() is used.
     * @param project Project to delete on the server.
     */
    Job<NoneType>* deleteProject(const Project& project);

    /**
     * Post modifications to a Project on the server
     * @param project Project to update on the server
     */
    Job<NoneType>* editProject(const Project& project);

    // Buildservice part of OCS

    /**
     * Get the information for a specific build service instance.
     * @return Job receiving data
     */
    Job<BuildService>* requestBuildService(const QString& id);

    /**
     * Get the information for a specific publisher.
     * @return Job receiving data
     */
    Job<Publisher>* requestPublisher(const QString& id);

    /**
     * Save the value of a single publishing field
     * @return Job*
     */
    Job<NoneType>* savePublisherField(const Project& project, const PublisherField& field);

    /**
     * Publish the result of a completed build job to a publisher.
     * @return Job receiving data
     */
    Job<NoneType>* publishBuildJob(const BuildServiceJob& buildjob, const Publisher& publisher);

    /**
     * Get the build output for a specific build service job
     * @return Job receiving and containing the output data
     */
    Job<BuildServiceJobOutput>* requestBuildServiceJobOutput(const QString& id);

    /**
     * Get the information for a specific build service job, such as status and progress.
     * @return Job receiving and containing the data
     */
    Job<BuildServiceJob>* requestBuildServiceJob(const QString& id);

    /**
     * Get a list of build service build services
     * @return Job listing BuildServices
     */
    Job<BuildService>* requestBuildServices();

    /**
     * Get a list of publishers
     * @return Job listing Publishers
     */
    Job<Publisher>* requestPublishers();

    /**
     * Get a list of build service projects
     * @return Job listing BuildServiceJobs
     */
    Job<BuildServiceJob>* requestBuildServiceJobs(const Project &project);


    /**
     * Create a new job for a given project on a given buildservice for a given target.
     * Those three items are mandatory for the job to succeed.
     * @param job Buildservicejob to create on the server
     */
    Job<NoneType>* createBuildServiceJob(const BuildServiceJob& job);

    /**
     * Cancel a job.
     * Setting the ID on the build service parameter is enough for it to work.
     * @param job Buildservicejob to cancel on the server, needs at least id set.
     */
    Job<NoneType>* cancelBuildServiceJob(const BuildServiceJob& job);

    /**
     * Get a list of remote accounts, account for a build service instance
     * which is stored in the OCS service in order to authenticate with the
     * build service instance.
     * @return Job listing RemoteAccounts
     */
    Job<RemoteAccount>* requestRemoteAccounts();

    /**
     * Deletes a remote account stored on the OCS server.
     * @param id The ID of the remote account on the OCS instance.
     */
    Job<NoneType>* deleteRemoteAccount(const QString& id);

    /**
     * Create a new remote account, an account for a build service instance
     * which is stored in the OCS service in order to authenticate with the
     * build service instance.
     * Type, Type ID, login and password are mandatory.
     * @param account RemoteAccount to create on the server
     */
    Job<NoneType>* createRemoteAccount(const RemoteAccount& account);

    /**
     * Edit an existing remote account.
     * @param account RemoteAccount to create on the server
     */
    Job<NoneType>* editRemoteAccount(const RemoteAccount& account);

    /** Get a remote account by its ID.
     * @param id The ID of the remote account
     */
    Job<RemoteAccount>* requestRemoteAccount(const QString &id);

    /** Upload a tarball to the buildservice.
     * @param projectId The ID of the project this source file belongs to
     * @param payload A reference tothe complete file data
     * @return A postjob to keep keep track of the upload
     */
    Attica::Job<NoneType>* uploadTarballToBuildService(const QString& projectId, const QString& fileName, const QByteArray& payload);

    // Content part of OCS

    /**
     * Get a list of categories (such as wallpaper)
     * @return the categories of the server
     */
    Job<Category>* requestCategories();

    /**
    * Get a list of licenses (such as GPL)
    * @return the licenses available from the server
    */
    Job<License>* requestLicenses();

    /**
    * Get a list of distributions (such as Ark, Debian)
    * @return the licenses available from the server
    */
    Job<Distribution>* requestDistributions();

    /**
    * Get a list of home page types (such as blog, Facebook)
    * @return the licenses available from the server
    */
    Job<HomePageType>* requestHomePageTypes();

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
    Job<Content>* searchContents(const Category::List& categories, const QString& search = QString(), SortMode mode = Rating, uint page = 0, uint pageSize = 10);

    /**
      Request a list of Contents.
      Like @see searchContents, but only contents created by one person.
      @param person the person-id that created the contents.
     */
    Job<Content>* searchContentsByPerson(const Category::List& categories, const QString& person, const QString& search = QString(), SortMode mode = Rating, uint page = 0, uint pageSize = 10);

    /**
      Request a list of Contents. More complete version.
      Note that @p categories is not optional. If left empty, no results will be returned.
      An empty search string @p search returns the top n items.
      @param categories categories to search in
      @param person the person-id that created the contents
      @param distributions list of distributions to filter by, if empty no filtering by distribution is done
      @param licenses list of licenses to filter by, if empty no filtering by license is done
      @param search optional search string (in name/description of the content)
      @param mode sorting mode
      @param page request nth page in the list of results
      @param pageSize requested size of pages when calculating the list of results
      @return list job for the search results
      */
    Job<Content>* searchContents(const Category::List& categories, const QString& person, const Distribution::List& distributions, const License::List& licenses, const QString& search = QString(), SortMode sortMode = Rating, uint page = 0, uint pageSize = 10);

    /**
      Retrieve a single content.
      @param contentId the id of the content
      @return job that retrieves the content object
     */
    Job<Content>* requestContent(const QString& contentId);

    Job<DownloadItem>* downloadLink(const QString& contentId, const QString& itemId = QLatin1String("1"));

    /** Vote for a content item
     * This version is for the old OCS API < 1.6
     * @param contentId the content which this voting is for
     * @param positiveVote whether the voting is positive or negative
     * @return the post job for this voting
     */
    Q_DECL_DEPRECATED Job<NoneType>* voteForContent(const QString& contentId, bool positiveVote);

    /** Vote for a content item
     * @param contentId the content which this voting is for
     * @param rating - the rating, must be between 0 (bad) and 100 (good)
     * @return the post job for this voting
     */
    Job<NoneType>* voteForContent(const QString& contentId, uint rating);

    Job<Content>* addNewContent(const Category& category, const Content& newContent);
    Job<Content>* editContent(const Category& updatedCategory, const QString& contentId, const Content& updatedContent);
    Job<NoneType>* deleteContent(const QString& contentId);

    Job<NoneType>* setDownloadFile(const QString& contentId, const QString& fileName, QIODevice* payload);
    Job<NoneType>* setDownloadFile(const QString& contentId, const QString& fileName, const QByteArray& payload);
    Job<NoneType>* deleteDownloadFile(const QString& contentId);

    /**
     * Upload an image file as preview for the content
     * @param contentId
     * @param previewId each content can have previews with the id 1,2 or 3
     * @param payload the image file
     */
    Job<NoneType>* setPreviewImage(const QString& contentId, const QString& previewId, const QString& fileName, const QByteArray& image);
    Job<NoneType>* deletePreviewImage(const QString& contentId, const QString& previewId);

    // KnowledgeBase part of OCS

    Job<KnowledgeBaseEntry>* requestKnowledgeBaseEntry(const QString& id);
    Job<KnowledgeBaseEntry>* searchKnowledgeBase(const Content& content, const QString& search, SortMode, int page, int pageSize);

    // Event part of OCS

    Job<Event>* requestEvent(const QString& id);
    Job<Event>* requestEvent(const QString& country, const QString& search, const QDate& startAt, SortMode mode, int page, int pageSize);

    // Comment part of OCS
    /** Request a list of comments for a content / forum / knowledgebase / event.
     * @param comment::Type type of the comment @see Comment::Type (content / forum / knowledgebase / event)
     * @param id id of the content entry where you want to get the comments is from
     * @param id2 id of the content entry where you want to get the comments is from
     * @param page request nth page in the list of results
     * @param pageSize requested size of pages when calculating the list of results
     * @return list job for the comments results
     */
    Job<Comment>* requestComments(const Comment::Type commentType, const QString& id, const QString& id2, int page, int pageSize);

    /** Add a new comment.
     * @param commentType type of the comment @see CommentType (content / forum / knowledgebase / event)
     * @param id id of the content entry where you want to get the comments is from
     * @param id2 id of the sub content entry where you want to get the comments is from
     * @param parentId the id of the parent comment if the new comment is a reply
     * @param subject title of the comment
     * @param message text of the comment
     * @return item post job for adding the new comment
     */
    Job<Comment>* addNewComment(const Comment::Type commentType, const QString& id, const QString& id2, const QString& parentId, const QString &subject, const QString& message);

    /** Vote a comment item
     * @param id the comment id which this voting is for
     * @param rating the rating, must be between 0 (bad) and 100 (good)
     * @return the post job for this voting
     */
    Job<NoneType>* voteForComment(const QString & id, uint rating);

    // Fan part of OCS

    Job<NoneType>* becomeFan(const QString& contentId);
    Job<Person>* requestFans(const QString& contentId, uint page = 0, uint pageSize = 10);

    // Forum part of OCS
    Job<Forum>* requestForums(uint page = 0, uint pageSize = 10);
    Job<Topic>* requestTopics(const QString& forum, const QString& search, const QString& description, SortMode mode, int page, int pageSize);
    Job<NoneType>* postTopic(const QString& forumId, const QString& subject, const QString& content);

  protected:
    QUrl createUrl(const QString& path);
    QNetworkRequest createRequest(const QUrl& url);
    // Convenience overload
    QNetworkRequest createRequest(const QString& path);

    Job<Person>* doRequestPerson(const QUrl& url);
    Job<AccountBalance>* doRequestAccountBalance(const QUrl& url);
    Job<Person>* doRequestPersonList(const QUrl& url);
    Job<Achievement>* doRequestAchievementList(const QUrl& url);
    Job<Activity>* doRequestActivityList(const QUrl& url);
    Job<Folder>* doRequestFolderList(const QUrl& url);
    Job<Forum>* doRequestForumList(const QUrl& url);
    Job<Topic>* doRequestTopicList(const QUrl& url);
    Job<Message>* doRequestMessageList(const QUrl& url);

  private:
    class Private;
    QExplicitlySharedDataPointer<Private> d;

    Provider(PlatformDependent* internals, const QUrl& baseUrl, const QString& name, const QUrl& icon = QUrl());
    Provider(PlatformDependent* internals, const QUrl& baseUrl, const QString& name, const QUrl& icon,
             const QString& person, const QString& friendV, const QString& message, const QString& achievements,
             const QString& activity, const QString& content, const QString& fan, const QString& forum,
             const QString& knowledgebase, const QString& event, const QString& comment);

friend class ProviderManager;
};
}

#endif
