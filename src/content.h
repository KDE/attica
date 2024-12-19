/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2008 Cornelius Schumacher <schumacher@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef ATTICA_CONTENT_H
#define ATTICA_CONTENT_H

#include <QList>
#include <QMap>
#include <QSharedDataPointer>
#include <QString>
#include <QUrl>

#include "attica_export.h"
#include "downloaddescription.h"
#include "homepageentry.h"
#include "icon.h"

class QDateTime;

namespace Attica
{
/*!
 * \class Attica::Content
 * \inheaderfile Attica/Content
 * \inmodule Attica
 *
 * \brief Represents a single content.
 */
class ATTICA_EXPORT Content
{
public:
    /*!
     *
     */
    typedef QList<Content> List;
    class Parser;

    /*!
     * Creates an empty Content
     */
    Content();

    Content(const Content &other);

    Content &operator=(const Content &other);

    ~Content();

    /*!
     * Sets the id of the Content.
     *
     * The id uniquely identifies a Content with the OCS API.
     *
     * \a id the new id
     */
    void setId(const QString &id);

    /*!
     * Returns the id of the Content.
     *
     * The id uniquely identifies a Content with the OCS API.
     */
    QString id() const;

    /*!
     * Sets the name of the Content.
     *
     * \a name the new name
     */
    void setName(const QString &name);

    /*!
     * Returns the name of the Content.
     */
    QString name() const;

    /*!
     * Sets the rating of the Content.
     *
     * \a rating the new rating, has to be in the range 0-100
     */
    void setRating(int rating);

    /*!
     * Returns the rating of the Content, in the range 0-100
     */
    int rating() const;

    /*!
     * Sets the number of downloads for the Content.
     *
     * \a downloads the new number of downloads
     */
    void setDownloads(int downloads);

    /*!
     * Returns the number of downloads for the Content (how often this has been downloaded from the server).
     */
    int downloads() const;

    /*!
     * Sets the number of comments for the Content.
     *
     * \a numComments the new number of downloads
     */
    void setNumberOfComments(int numComments);

    /*!
     * Returns the number of comments for the Content.
     */
    int numberOfComments() const;

    /*!
     * Sets the date and time the Content has been created.
     *
     * \a created the new creation date and time
     */
    void setCreated(const QDateTime &created);

    /*!
     * Returns the date and time the Content has been created.
     */
    QDateTime created() const;

    /*!
     * Sets the time the Content has been last updated.
     *
     * \a updated the new date and time of the last update
     */
    void setUpdated(const QDateTime &updated);

    /*!
     * Returns the date and time the Content has been last updated.
     */
    QDateTime updated() const;

    /*!
     * A summary description of this content.
     */
    QString summary() const;

    /*!
     * A description of this content.
     */
    QString description() const;

    /*!
     * A webpage with the detailed description of this content.
     */
    QUrl detailpage() const;

    /*!
     *
     */
    QString changelog() const;

    /*!
     *
     */
    QString version() const;

    /*!
     *
     */
    QString depend() const;

    /*!
      Get the details about a download (a content can have multiple links, eg for different distros).
      This is not very helpful if we don't know the allowed numbers.
      */
    DownloadDescription downloadUrlDescription(int number) const;

    /*!
      Get all possible downloads.
      This is slow searching through lots of strings, so beware and don't call it too often.
      */
    QList<DownloadDescription> downloadUrlDescriptions() const;

    /*!
      Get the details about a home page (a content can have multiple home pages, blog, bugs, ...).
      This is not very helpful if we don't know the allowed numbers.
      */
    HomePageEntry homePageEntry(int number) const;

    /*!
      Get all home pages for this content.
      This is slow searching through lots of strings, so beware and don't call it too often.
      */
    QList<HomePageEntry> homePageEntries();

    /*!
     *
     */
    QString previewPicture(const QString &number = QStringLiteral("1")) const;

    /*!
     *
     */
    QString smallPreviewPicture(const QString &number = QStringLiteral("1")) const;

    /*!
     *
     */
    QString license() const;

    /*!
     *
     */
    QString licenseName() const;

    /*!
     *
     */
    QString author() const;

    /*!
      Get all icons for this content.
      */
    QList<Icon> icons();

    /*!
      Get all icons for this content.
      */
    QList<Icon> icons() const;

    /*!
     * Set list of icons.
     *
     * \a icons list of icons for this content
     */
    void setIcons(QList<Icon> icons);

    /*!
      Get all videos for this content.
      */
    QList<QUrl> videos();
    /*!
     * Set list of videos.
     *
     * \a videos list of videos for this content
     */
    void setVideos(QList<QUrl> videos);

    /*!
     * Get all the tags for this content
     * \since 5.50
     */
    QStringList tags() const;
    /*!
     * Set the list of tags
     *
     * \a tags list of tags for this content
     * \since 5.50
     */
    void setTags(const QStringList &tags);

    /*!
     * Add an attribute that is not included in the basis set of attributes exposed by the Content class.
     * If the attribute already exists it gets overwritten.
     *
     * \a key the key of the attribute
     *
     * \a value the value of the attribute
     */
    void addAttribute(const QString &key, const QString &value);

    /*!
     * Get an attribute that is not included in the basis set of attributes exposed by the Content class.
     *
     * \a key the key of the attribute
     *
     * Returns the value of the attribute with the specified key, or an empty string, if the key has not been found
     */
    QString attribute(const QString &key) const;

    /*!
     * Get all attributes that are not included in the basis set of attributes exposed by the Content class.
     */
    QMap<QString, QString> attributes() const;

    /*!
     * Checks whether this Content has an id
     * Returns \c true if an id has been set, \c false otherwise
     */
    bool isValid() const;

private:
    class Private;
    QSharedDataPointer<Private> d;
};

}

#endif
