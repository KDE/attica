/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2008 Cornelius Schumacher <schumacher@kde.org>
    SPDX-FileCopyrightText: 2011 Laszlo Papp <djszapi@archlinux.us>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef ATTICA_PROVIDER_H
#define ATTICA_PROVIDER_H

#include <QExplicitlySharedDataPointer>
#include <QSharedPointer>
#include <QString>
#include <QStringList>

#include <QUrl>

#include "achievement.h"
#include "attica_export.h"
#include "category.h"
#include "comment.h"
#include "distribution.h"
#include "forum.h"
#include "itemjob.h"
#include "license.h"
#include "listjob.h"
#include "message.h"

class QDate;
class QUrl;

namespace Attica
{
class PlatformDependent;

class PostJobStatus;

class AccountBalance;
class Activity;
class BuildServiceJobOutput;
class BuildServiceJob;
class BuildService;
class PrivateData;
class Config;
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
class Project;
class Provider;
class Publisher;
class PublisherField;
class RemoteAccount;

/*!
 * \class Attica::Provider
 * \inheaderfile Attica/Provider
 * \inmodule Attica
 *
 * \brief The Provider class represents one Open Collaboration Service provider.
 *
 * Use the ProviderManager to instantiate a Provider.
 *
 * Accessing functions of the Provider returns a Job class that
 * takes care of accessing the server and parsing the result.
 *
 * Provider files are xml of the form:
 * \badcode
 * <provider>
 * <id>opendesktop</id>
 * <location>https://api.opendesktop.org/v1/</location>
 * <name>openDesktop.org</name>
 * <icon></icon>
 * <termsofuse>https://opendesktop.org/terms/</termsofuse>
 * <register>https://opendesktop.org/usermanager/new.php</register>
 * <services>
 *   <person ocsversion="1.3" />
 *   <friend ocsversion="1.3" />
 *   <message ocsversion="1.3" />
 *   <activity ocsversion="1.3" />
 *   <content ocsversion="1.3" />
 *   <fan ocsversion="1.3" />
 *   <knowledgebase ocsversion="1.3" />
 *   <event ocsversion="1.3" />
 *   <comment ocsversion="1.2" />
 * </services>
 * </provider>
 * \endcode
 * The server provides the services specified in the services section, not necessarily all of them.
 */
class ATTICA_EXPORT Provider
{
public:
    /*!
     * Default construct a Provider. Please note that this provider is incomplete and never valid.
     */
    Provider();
    Provider(const Provider &other);
    Provider &operator=(const Provider &other);
    ~Provider();

    /*!
    Returns true if the provider has been set up and can be used.
    */
    bool isValid() const;

    /*!
    Test if the provider is enabled by the settings.
    The application can choose to ignore this, but the user settings should be respected.
    */
    bool isEnabled() const;

    /*!
     *
     */
    void setEnabled(bool enabled);

    /*!
     * Set a custom identifier for your application (sent along with the requests as
     * the http agent header in addition to the application name and version).
     *
     * For example, you might have an application named SomeApplication, version 23,
     * and wish to send along the data "lookandfeel.knsrc". Call this function, and
     * the resulting agent header would be:
     *
     * SomeApplication/23 (+lookandfeel.knsrc)
     *
     * If you do not set this (or set it to an empty string), the agent string becomes
     *
     * SomeApplication/23
     *
     * \a additionalAgentInformation The extra string
     * \since 5.66
     */
    void setAdditionalAgentInformation(const QString &additionalInformation);
    /*!
     * The custom identifier sent along with requests
     *
     * Returns the custom identifier
     * \sa setAdditionalAgentInformation(const QString&)
     * \since 5.66
     */
    QString additionalAgentInformation() const;

    /*!
    A url that identifies this provider.
    This should be used as identifier when referring to this provider but you don't want to use the full provider object.
    */
    QUrl baseUrl() const;

    /*!
    A name for the provider that can be displayed to the user
    */
    QString name() const;

    /*!
     * An icon used to visually identify this provider
     * Returns a URL for an icon image (or an invalid URL if one was not defined by the provider)
     * \since 5.85
     */
    QUrl icon() const;

    /*!
     * \value Newest
     * \value Alphabetical
     * \value Rating
     * \value Downloads
     */
    enum SortMode {
        Newest,
        Alphabetical,
        Rating,
        Downloads,
    };

    /*!
    Test if the server supports the person part of the API
    */
    bool hasPersonService() const;
    /*!
    Version of the person part of the API
    */
    QString personServiceVersion() const;

    /*!
    Test if the server supports the friend part of the API
    */
    bool hasFriendService() const;

    /*!
    Version of the friend part of the API
    */
    QString friendServiceVersion() const;

    /*!
    Test if the server supports the message part of the API
    */
    bool hasMessageService() const;
    /*!
    Version of the message part of the API
    */
    QString messageServiceVersion() const;

    /*!
    Test if the server supports the achievement part of the API
    */
    bool hasAchievementService() const;
    /*!
    Version of the achievement part of the API
    */
    QString achievementServiceVersion() const;

    /*!
    Test if the server supports the activity part of the API
    */
    bool hasActivityService() const;
    /*!
    Version of the activity part of the API
    */
    QString activityServiceVersion() const;

    /*!
    Test if the server supports the content part of the API
    */
    bool hasContentService() const;
    /*!
    Version of the content part of the API
    */
    QString contentServiceVersion() const;

    /*!
    Test if the server supports the fan part of the API
    */
    bool hasFanService() const;
    /*!
    Version of the fan part of the API
    */
    QString fanServiceVersion() const;

    /*!
    Test if the server supports the forum part of the API
    */
    bool hasForumService() const;
    /*!
    Version of the forum part of the API
    */
    QString forumServiceVersion() const;

    /*!
     *
    Test if the server supports the knowledgebase part of the API
    */
    bool hasKnowledgebaseService() const;
    /*!
    Version of the knowledgebase part of the API
    */
    QString knowledgebaseServiceVersion() const;

    /*!
    Test if the server supports the comments part of the API
    */
    bool hasCommentService() const;
    /*!
    Version of the comments part of the API
    */
    QString commentServiceVersion() const;

    /*!
      Test if the provider has user name/password available.
      This does not yet open kwallet in case the KDE plugin is used.
      Returns true if the provider has login information
    */
    bool hasCredentials() const;
    bool hasCredentials();

    /*!
      Load user name and password from the store.

      Attica will remember the loaded values and use them from this point on.

      \a user reference that returns the user name

      \a password reference that returns the password

      Returns if credentials could be loaded
    */
    bool loadCredentials(QString &user, QString &password);

    /*!
      Sets (and remembers) user name and password for this provider.

      To remove the data an empty username should be passed.

      \a user the user (login) name

      \a password the password

      Returns if credentials could be saved
    */
    bool saveCredentials(const QString &user, const QString &password);

    /*!
      Test if the server accepts the login/password.

      This function does not actually set the credentials. Use saveCredentials for that purpose.

      \a user the user (login) name

      \a password the password

      Returns the job that will contain the success of the login as metadata
    */
    PostJob *checkLogin(const QString &user, const QString &password);

    /*!
     * Fetches server config
     * Returns The job responsible for fetching data
     */
    ItemJob<Config> *requestConfig();

    // Person part of OCS

    /*!
     *
     */
    PostJob *registerAccount(const QString &id, const QString &password, const QString &mail, const QString &firstName, const QString &lastName);

    /*!
     *
     */
    ItemJob<Person> *requestPerson(const QString &id);

    /*!
     *
     */
    ItemJob<Person> *requestPersonSelf();

    /*!
     *
     */
    ItemJob<AccountBalance> *requestAccountBalance();

    /*!
     *
     */
    ListJob<Person> *requestPersonSearchByName(const QString &name);

    /*!
     *
     */
    ListJob<Person> *requestPersonSearchByLocation(qreal latitude, qreal longitude, qreal distance = 0.0, int page = 0, int pageSize = 20);

    /*!
     *
     */
    PostJob *postLocation(qreal latitude, qreal longitude, const QString &city = QString(), const QString &country = QString());

    //////////////////////////
    // PrivateData part of OCS

    /*!
     * Fetches the a given attribute from an OCS-compliant server.
     *
     * \a app The application name
     *
     * \a key The key of the attribute to fetch (optional)
     *
     * Returns The job that is responsible for fetching the data
     */
    ItemJob<PrivateData> *requestPrivateData(const QString &app, const QString &key = QString());

    /*!
     * Fetches all stored private data.
     *
     * Returns The job responsible for fetching data
     */
    ItemJob<PrivateData> *requestPrivateData()
    {
        return requestPrivateData(QString(), QString());
    }

    /*!
     * Sets the value of an attribute.
     *
     * \a app The application name
     *
     * \a key The key of the attribute
     *
     * \a value The new value of the attribute
     *
     * Returns The job responsible for setting data
     */
    PostJob *setPrivateData(const QString &app, const QString &key, const QString &value);

    // Friend part of OCS

    /*!
     *
     */
    ListJob<Person> *requestFriends(const QString &id, int page = 0, int pageSize = 20);

    /*!
     *
     */
    ListJob<Person> *requestSentInvitations(int page = 0, int pageSize = 20);

    /*!
     *
     */
    ListJob<Person> *requestReceivedInvitations(int page = 0, int pageSize = 20);

    /*!
     *
     */
    PostJob *inviteFriend(const QString &to, const QString &message);

    /*!
     *
     */
    PostJob *approveFriendship(const QString &to);

    /*!
     *
     */
    PostJob *declineFriendship(const QString &to);

    /*!
     *
     */
    PostJob *cancelFriendship(const QString &to);

    // Message part of OCS

    /*!
     *
     */
    ListJob<Folder> *requestFolders();

    /*!
     *
     */
    ListJob<Message> *requestMessages(const Folder &folder);

    /*!
     *
     */
    ListJob<Message> *requestMessages(const Folder &folder, Message::Status status);

    /*!
     *
     */
    ItemJob<Message> *requestMessage(const Folder &folder, const QString &id);

    /*!
     *
     */
    PostJob *postMessage(const Message &message);

    // Achievement part of OCS
    /*!
     * Get a list of achievements
     * Returns ListJob listing Achievements
     */
    ListJob<Achievement> *requestAchievements(const QString &contentId, const QString &achievementId, const QString &userId);

    /*! Add a new achievement.
     *
     * \a id id of the achievement entry
     *
     * \a achievement The new Achievement added
     *
     * Returns item post job for adding the new achievement
     */
    ItemPostJob<Achievement> *addNewAchievement(const QString &id, const Achievement &newAchievement);

    /*!
     * Post modifications to an Achievement on the server
     *
     * \a achievement Achievement to update on the server
     */
    PutJob *editAchievement(const QString &contentId, const QString &achievementId, const Achievement &achievement);

    /*!
     * Deletes an achievement on the server. The achievement passed as an argument doesn't need complete
     * information as just the id() is used.
     *
     * \a achievementId Achievement to delete on the server.
     */
    DeleteJob *deleteAchievement(const QString &contentId, const QString &achievementId);

    // PostJob* postAchievement(const Achievement& achievement);

    /*!
     *
     */
    PostJob *setAchievementProgress(const QString &id, const QVariant &progress, const QDateTime &timestamp);

    /*!
     *
     */
    DeleteJob *resetAchievementProgress(const QString &id);

    // Activity part of OCS

    /*!
     *
     */
    ListJob<Activity> *requestActivities();

    /*!
     *
     */
    PostJob *postActivity(const QString &message);

    // Project part of OCS
    /*!
     * Get a list of build service projects
     * Returns ListJob listing Projects
     */
    ListJob<Project> *requestProjects();

    /*!
     * Get a Project's data
     * Returns ItemJob receiving data
     */
    ItemJob<Project> *requestProject(const QString &id);

    /*!
     * Post modifications to a Project on the server. The resulting project ID can be found in
     * the Attica::MetaData of the finished() PostJob. You can retrieve it using
     * Attica::MetaData::resultingProjectId().
     *
     * \a project Project to create on the server
     */
    PostJob *createProject(const Project &project);

    /*!
     * Deletes a project on the server. The project passed as an argument doesn't need complete
     * information as just the id() is used.
     *
     * \a project Project to delete on the server.
     */
    PostJob *deleteProject(const Project &project);

    /*!
     * Post modifications to a Project on the server
     *
     * \a project Project to update on the server
     */
    PostJob *editProject(const Project &project);

    // Buildservice part of OCS

    /*!
     * Get the information for a specific build service instance.
     * Returns ItemJob receiving data
     */
    ItemJob<BuildService> *requestBuildService(const QString &id);

    /*!
     * Get the information for a specific publisher.
     * Returns ItemJob receiving data
     */
    ItemJob<Publisher> *requestPublisher(const QString &id);

    /*!
     * Save the value of a single publishing field
     * Returns PostJob*
     */
    PostJob *savePublisherField(const Project &project, const PublisherField &field);

    /*!
     * Publish the result of a completed build job to a publisher.
     * Returns ItemJob receiving data
     */
    PostJob *publishBuildJob(const BuildServiceJob &buildjob, const Publisher &publisher);

    /*!
     * Get the build output for a specific build service job
     * Returns ItemJob receiving and containing the output data
     */
    ItemJob<BuildServiceJobOutput> *requestBuildServiceJobOutput(const QString &id);

    /*!
     * Get the information for a specific build service job, such as status and progress.
     * Returns ItemJob receiving and containing the data
     */
    ItemJob<BuildServiceJob> *requestBuildServiceJob(const QString &id);

    /*!
     * Get a list of build service build services
     * Returns ListJob listing BuildServices
     */
    ListJob<BuildService> *requestBuildServices();

    /*!
     * Get a list of publishers
     * Returns ListJob listing Publishers
     */
    ListJob<Publisher> *requestPublishers();

    /*!
     * Get a list of build service projects
     * Returns ListJob listing BuildServiceJobs
     */
    ListJob<BuildServiceJob> *requestBuildServiceJobs(const Project &project);

    /*!
     * Create a new job for a given project on a given buildservice for a given target.
     * Those three items are mandatory for the job to succeed.
     *
     * \a job Buildservicejob to create on the server
     */
    PostJob *createBuildServiceJob(const BuildServiceJob &job);

    /*!
     * Cancel a job.
     * Setting the ID on the build service parameter is enough for it to work.
     *
     * \a job Buildservicejob to cancel on the server, needs at least id set.
     */
    PostJob *cancelBuildServiceJob(const BuildServiceJob &job);

    /*!
     * Get a list of remote accounts, account for a build service instance
     * which is stored in the OCS service in order to authenticate with the
     * build service instance.
     * Returns ListJob listing RemoteAccounts
     */
    ListJob<RemoteAccount> *requestRemoteAccounts();

    /*!
     * Deletes a remote account stored on the OCS server.
     *
     * \a id The ID of the remote account on the OCS instance.
     */
    PostJob *deleteRemoteAccount(const QString &id);

    /*!
     * Create a new remote account, an account for a build service instance
     * which is stored in the OCS service in order to authenticate with the
     * build service instance.
     * Type, Type ID, login and password are mandatory.
     *
     * \a account RemoteAccount to create on the server
     */
    PostJob *createRemoteAccount(const RemoteAccount &account);

    /*!
     * Edit an existing remote account.
     *
     * \a account RemoteAccount to create on the server
     */
    PostJob *editRemoteAccount(const RemoteAccount &account);

    /*! Get a remote account by its ID.
     *
     * \a id The ID of the remote account
     */
    ItemJob<RemoteAccount> *requestRemoteAccount(const QString &id);

    /*! Upload a tarball to the buildservice.
     *
     * \a projectId The ID of the project this source file belongs to
     *
     * \a payload A reference to the complete file data
     *
     * Returns A postjob to keep keep track of the upload
     */
    Attica::PostJob *uploadTarballToBuildService(const QString &projectId, const QString &fileName, const QByteArray &payload);

    // Content part of OCS

    /*!
     * Get a list of categories (such as wallpaper)
     * Returns the categories of the server
     */
    ListJob<Category> *requestCategories();

    /*!
     * Get a list of licenses (such as GPL)
     * Returns the licenses available from the server
     */
    ListJob<License> *requestLicenses();

    /*!
     * Get a list of distributions (such as Ark, Debian)
     * Returns the licenses available from the server
     */
    ListJob<Distribution> *requestDistributions();

    /*!
     * Get a list of home page types (such as blog, Facebook)
     * Returns the licenses available from the server
     */
    ListJob<HomePageType> *requestHomePageTypes();

    /*!
      Request a list of Contents.

      Note that \a categories is not optional. If left empty, no results will be returned.

      An empty search string \a search returns the top n items.

      \a categories categories to search in

      \a search optional search string (in name/description of the content)

      \a mode sorting mode

      \a page request nth page in the list of results

      \a pageSize requested size of pages when calculating the list of results

      Returns list job for the search results
      */
    ListJob<Content> *
    searchContents(const Category::List &categories, const QString &search = QString(), SortMode mode = Rating, uint page = 0, uint pageSize = 10);

    /*!
      Request a list of Contents.

      Like searchContents, but only contents created by one person.

      \a person the person-id that created the contents.
     */
    ListJob<Content> *searchContentsByPerson(const Category::List &categories,
                                             const QString &person,
                                             const QString &search = QString(),
                                             SortMode mode = Rating,
                                             uint page = 0,
                                             uint pageSize = 10);

    /*!
      Request a list of Contents. More complete version.

      Note that \a categories is not optional. If left empty, no results will be returned.

      An empty search string \a search returns the top n items.

      \a categories categories to search in

      \a person the person-id that created the contents

      \a distributions list of distributions to filter by, if empty no filtering by distribution is done

      \a licenses list of licenses to filter by, if empty no filtering by license is done

      \a search optional search string (in name/description of the content)

      \a mode sorting mode

      \a page request nth page in the list of results

      \a pageSize requested size of pages when calculating the list of results

      Returns list job for the search results
      */
    ListJob<Content> *searchContents(const Category::List &categories,
                                     const QString &person,
                                     const Distribution::List &distributions,
                                     const License::List &licenses,
                                     const QString &search = QString(),
                                     SortMode sortMode = Rating,
                                     uint page = 0,
                                     uint pageSize = 10);

    /*!
      Retrieve a single content.

      \a contentId the id of the content

      Returns job that retrieves the content object
     */
    ItemJob<Content> *requestContent(const QString &contentId);

    /*!
     *
     */
    ItemJob<DownloadItem> *downloadLink(const QString &contentId, const QString &itemId = QStringLiteral("1"));

    /*! Vote for a content item
     *
     * \a contentId the content which this voting is for
     *
     * \a rating - the rating, must be between 0 (bad) and 100 (good)
     *
     * Returns the post job for this voting
     */
    PostJob *voteForContent(const QString &contentId, uint rating);

    /*!
     *
     */
    ItemPostJob<Content> *addNewContent(const Category &category, const Content &newContent);

    /*!
     *
     */
    ItemPostJob<Content> *editContent(const Category &updatedCategory, const QString &contentId, const Content &updatedContent);

    /*!
     *
     */
    PostJob *deleteContent(const QString &contentId);

    /*!
     *
     */
    PostJob *setDownloadFile(const QString &contentId, const QString &fileName, QIODevice *payload);

    /*!
     *
     */
    PostJob *setDownloadFile(const QString &contentId, const QString &fileName, const QByteArray &payload);

    /*!
     *
     */
    PostJob *deleteDownloadFile(const QString &contentId);

    /*!
     * Upload an image file as preview for the content
     *
     * \a contentId
     *
     * \a previewId each content can have previews with the id 1,2 or 3
     *
     * \a payload the image file
     */
    PostJob *setPreviewImage(const QString &contentId, const QString &previewId, const QString &fileName, const QByteArray &image);

    /*!
     *
     */
    PostJob *deletePreviewImage(const QString &contentId, const QString &previewId);

    // KnowledgeBase part of OCS

    /*!
     *
     */
    ItemJob<KnowledgeBaseEntry> *requestKnowledgeBaseEntry(const QString &id);

    /*!
     *
     */
    ListJob<KnowledgeBaseEntry> *searchKnowledgeBase(const Content &content, const QString &search, SortMode, int page, int pageSize);

    // Event part of OCS

    /*!
     *
     */
    ItemJob<Event> *requestEvent(const QString &id);

    /*!
     *
     */
    ListJob<Event> *requestEvent(const QString &country, const QString &search, const QDate &startAt, SortMode mode, int page, int pageSize);

    // Comment part of OCS
    /*! Request a list of comments for a content / forum / knowledgebase / event.
     *
     * \a type of the comment Comment::Type (content / forum / knowledgebase / event)
     *
     * \a id id of the content entry where you want to get the comments is from
     *
     * \a id2 id of the content entry where you want to get the comments is from
     *
     * \a page request nth page in the list of results
     *
     * \a pageSize requested size of pages when calculating the list of results
     *
     * Returns list job for the comments results
     */
    ListJob<Comment> *requestComments(const Comment::Type commentType, const QString &id, const QString &id2, int page, int pageSize);

    /*! Add a new comment.
     *
     * \a commentType type of the comment CommentType (content / forum / knowledgebase / event)
     *
     * \a id id of the content entry where you want to get the comments is from
     *
     * \a id2 id of the sub content entry where you want to get the comments is from
     *
     * \a parentId the id of the parent comment if the new comment is a reply
     *
     * \a subject title of the comment
     *
     * \a message text of the comment
     *
     * Returns item post job for adding the new comment
     */
    ItemPostJob<Comment> *addNewComment(const Comment::Type commentType,
                                        const QString &id,
                                        const QString &id2,
                                        const QString &parentId,
                                        const QString &subject,
                                        const QString &message);

    /*! Vote a comment item
     *
     * \a id the comment id which this voting is for
     *
     * \a rating the rating, must be between 0 (bad) and 100 (good)
     *
     * Returns the post job for this voting
     */
    PostJob *voteForComment(const QString &id, uint rating);

    // Fan part of OCS

    /*!
     *
     */
    PostJob *becomeFan(const QString &contentId);

    /*!
     *
     */
    ListJob<Person> *requestFans(const QString &contentId, uint page = 0, uint pageSize = 10);

    // Forum part of OCS
    /*!
     *
     */
    ListJob<Forum> *requestForums(uint page = 0, uint pageSize = 10);

    /*!
     *
     */
    ListJob<Topic> *requestTopics(const QString &forum, const QString &search, const QString &description, SortMode mode, int page, int pageSize);

    /*!
     *
     */
    PostJob *postTopic(const QString &forumId, const QString &subject, const QString &content);

    /*!
     *
     */
    const QString &getRegisterAccountUrl() const;

protected:
    QUrl createUrl(const QString &path);
    QNetworkRequest createRequest(const QUrl &url);
    // Convenience overload
    QNetworkRequest createRequest(const QString &path);

    ItemJob<Config> *doRequestConfig(const QUrl &url);
    ItemJob<Person> *doRequestPerson(const QUrl &url);
    ItemJob<AccountBalance> *doRequestAccountBalance(const QUrl &url);
    ListJob<Person> *doRequestPersonList(const QUrl &url);
    ListJob<Achievement> *doRequestAchievementList(const QUrl &url);
    ListJob<Activity> *doRequestActivityList(const QUrl &url);
    ListJob<Folder> *doRequestFolderList(const QUrl &url);
    ListJob<Forum> *doRequestForumList(const QUrl &url);
    ListJob<Topic> *doRequestTopicList(const QUrl &url);
    ListJob<Message> *doRequestMessageList(const QUrl &url);

private:
    class Private;
    QExplicitlySharedDataPointer<Private> d;

    Provider(PlatformDependent *internals, const QUrl &baseUrl, const QString &name, const QUrl &icon = QUrl());
    Provider(PlatformDependent *internals,
             const QUrl &baseUrl,
             const QString &name,
             const QUrl &icon,
             const QString &person,
             const QString &friendV,
             const QString &message,
             const QString &achievements,
             const QString &activity,
             const QString &content,
             const QString &fan,
             const QString &forum,
             const QString &knowledgebase,
             const QString &event,
             const QString &comment);
    // kde-SC5: merge with the constructor above (i.e. remove the above one)
    Provider(PlatformDependent *internals,
             const QUrl &baseUrl,
             const QString &name,
             const QUrl &icon,
             const QString &person,
             const QString &friendV,
             const QString &message,
             const QString &achievements,
             const QString &activity,
             const QString &content,
             const QString &fan,
             const QString &forum,
             const QString &knowledgebase,
             const QString &event,
             const QString &comment,
             const QString &registerUrl);
    // TODO KF6: merge with the constructor above (i.e. remove the above one - and actually do it this time :P )
    Provider(PlatformDependent *internals,
             const QUrl &baseUrl,
             const QString &name,
             const QUrl &icon,
             const QString &person,
             const QString &friendV,
             const QString &message,
             const QString &achievements,
             const QString &activity,
             const QString &content,
             const QString &fan,
             const QString &forum,
             const QString &knowledgebase,
             const QString &event,
             const QString &comment,
             const QString &registerUrl,
             const QString &additionalAgentInformation);

    friend class ProviderManager;
};
}

#endif
