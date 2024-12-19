/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2009 Eckhart Wörner <ewoerner@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef ATTICA_EVENT_H
#define ATTICA_EVENT_H

#include "attica_export.h"

#include <QDate>
#include <QList>
#include <QMap>
#include <QSharedDataPointer>
#include <QUrl>

namespace Attica
{
/*!
 * \class Attica::Event
 * \inheaderfile Attica/Event
 * \inmodule Attica
 *
 * \brief Represents a single event.
 */
class ATTICA_EXPORT Event
{
public:
    /*!
     *
     */
    typedef QList<Event> List;
    class Parser;

    /*!
     * Creates an empty Event
     */
    Event();

    Event(const Event &other);

    Event &operator=(const Event &other);

    ~Event();

    /*!
     * Sets the id of the Event.
     *
     * The id uniquely identifies a Event with the OCS API.
     *
     * \a id the new id
     */
    void setId(const QString &id);

    /*!
     * Returns the id of the Event.
     *
     * The id uniquely identifies a Event with the OCS API.
     */
    QString id() const;

    /*!
     * Sets the name of the Event.
     *
     * \a name the new name
     */
    void setName(const QString &name);

    /*!
     * Returns the name of the Event.
     */
    QString name() const;

    /*!
     * Sets the description of the Event.
     *
     * \a description the new description
     */
    void setDescription(const QString &description);

    /*!
     * Returns the description of the Event.
     */
    QString description() const;

    /*!
     * Sets the id of the user bound to the Event.
     *
     * \a user the new user id
     */
    void setUser(const QString &user);

    /*!
     * Returns the id of the user bound to the Event.
     */
    QString user() const;

    /*!
     * Sets the start date of the Event.
     *
     * \a startDate the start date
     */
    void setStartDate(const QDate &startDate);

    /*!
     * Returns the start date of the Event.
     */
    QDate startDate() const;

    /*!
     * Sets the end date of the Event.
     *
     * \a endDate the end date
     */
    void setEndDate(const QDate &endDate);

    /*!
     * Returns the start date of the Event.
     */
    QDate endDate() const;

    /*!
     * Sets the latitude of the position the Event takes place.
     */
    void setLatitude(qreal latitude);

    /*!
     * Returns the latitude of the position the Event takes place.
     */
    qreal latitude() const;

    /*!
     * Sets the longitude of the position the Event takes place.
     */
    void setLongitude(qreal longitude);

    /*!
     * Returns the longitude of the position the Event takes place.
     */
    qreal longitude() const;

    /*!
     * Sets the homepage of the Event.
     *
     * \a homepage the new homepage
     */
    void setHomepage(const QUrl &homepage);

    /*!
     * Returns the homepage of the Event.
     */
    QUrl homepage() const;

    /*!
     * Sets the country where the Event takes place.
     *
     * \a country the new country
     */
    void setCountry(const QString &country);

    /*!
     * Returns the country where the Event takes place.
     */
    QString country() const;

    /*!
     * Sets the city where the Event takes place.
     *
     * \a city the new city
     */
    void setCity(const QString &city);

    /*!
     * Returns the city where the Event takes place.
     */
    QString city() const;

    /*!
     * Add an attribute that is not included in the basis set of attributes exposed by the Event class.
     *
     * If the attribute already exists it gets overwritten.
     *
     * \a key the key of the attribute
     *
     * \a value the value of the attribute
     */
    void addExtendedAttribute(const QString &key, const QString &value);

    /*!
     * Get an attribute that is not included in the basis set of attributes exposed by the Event class.
     *
     * \a key the key of the attribute
     *
     * Returns the value of the attribute with the specified key, or an empty string, if the key has not been found
     */
    QString extendedAttribute(const QString &key) const;

    /*!
     * Get all attributes that are not included in the basis set of attributes exposed by the Event class.
     */
    QMap<QString, QString> extendedAttributes() const;

    /*!
     * Checks whether this Event has an id
     */
    bool isValid() const;

private:
    class Private;
    QSharedDataPointer<Private> d;
};

}

#endif
