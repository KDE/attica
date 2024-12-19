/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2008 Cornelius Schumacher <schumacher@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/
#ifndef ATTICA_ACTIVITY_H
#define ATTICA_ACTIVITY_H

#include <QList>
#include <QSharedDataPointer>
#include <QUrl>

#include "attica_export.h"
#include "person.h"

class QDateTime;

namespace Attica
{
/*!
 * \class Attica::Activity
 * \inheaderfile Attica/Activity
 * \inmodule Attica
 *
 * \brief Represents a single news item (also known as activity).
 */
class ATTICA_EXPORT Activity
{
public:
    /*!
     *
     */
    typedef QList<Activity> List;
    class Parser;

    /*!
     * Creates an empty Activity
     */
    Activity();

    Activity(const Activity &other);

    Activity &operator=(const Activity &other);

    ~Activity();

    /*!
     * Sets the id of the Activity.
     *
     * The id uniquely identifies an Activity with the OCS API.
     *
     * \a id the new id
     */
    void setId(const QString &id);

    /*!
     * Gets the id of the Activity.
     *
     * The id uniquely identifies an Activity with the OCS API.
     *
     * Returns the id
     */
    QString id() const;

    /*!
     * Sets the user bound to the Activity.
     *
     * \a id the new user
     */
    void setAssociatedPerson(const Person &associatedPerson);

    /*!
     * Returns the user bound to the Activity.
     */
    Person associatedPerson() const;

    /*!
     * Sets the timestamp the Activity has been published.
     *
     * \a timestamp the new timestamp
     */
    void setTimestamp(const QDateTime &timestamp);

    /*!
     * Returns the timestamp the Activity has been published.
     */
    QDateTime timestamp() const;

    /*!
     * Sets the message of the Activity.
     *
     * \a message the new message
     */
    void setMessage(const QString &message);

    /*!
     * Returns the message of the Activity.
     */
    QString message() const;

    /*!
     * Sets the link to further information about this Activity.
     *
     * \a link the new link
     */
    void setLink(const QUrl &link);

    /*!
     * Returns the link to further information about this Activity.
     */
    QUrl link() const;

    /*!
     * Checks whether this Activity has an id
     * Returns \c true if an id has been set, \c false otherwise
     */
    bool isValid() const;

private:
    class Private;
    QSharedDataPointer<Private> d;
};

}

#endif
