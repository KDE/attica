/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2010 Sebastian Kügler <sebas@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef ATTICA_PUBLISHER_H
#define ATTICA_PUBLISHER_H

#include <QDate>
#include <QList>
#include <QMap>
#include <QSharedDataPointer>
#include <QStringList>
#include <QUrl>

#include "attica_export.h"
#include "buildservice.h"

namespace Attica
{

/*!
 * \class Attica::Field
 * \inheaderfile Attica/Publisher
 * \inmodule Attica
 *
 * \brief Field as set for the class Publisher.
 */
struct Field {
    /*!
     * \variable Attica::Field::type
     */
    QString type;

    /*!
     * \variable Attica::Field::name
     */
    QString name;

    /*!
     * \variable Attica::Field::fieldsize
     */
    int fieldsize;

    /*!
     * \variable Attica::Field::required
     */
    bool required;

    /*!
     * \variable Attica::Field::options
     */
    QStringList options;
};

/*!
 * \class Attica::Publisher
 * \inheaderfile Attica/Publisher
 * \inmodule Attica
 *
 * \brief Represents a publisher.
 */
class ATTICA_EXPORT Publisher
{
public:
    /*!
     *
     */
    typedef QList<Publisher> List;
    class Parser;

    /*!
     *
     */
    Publisher();
    Publisher(const Publisher &other);
    Publisher &operator=(const Publisher &other);
    ~Publisher();

    /*!
     *
     */
    void setId(const QString &);

    /*!
     *
     */
    QString id() const;

    /*!
     *
     */
    void setName(const QString &);

    /*!
     *
     */
    QString name() const;

    /*!
     *
     */
    void setUrl(const QString &);

    /*!
     *
     */
    QString url() const;

    /*!
     *
     */
    void addField(const Field &);

    /*!
     *
     */
    QList<Field> fields() const;

    /*!
     *
     */
    void addTarget(const Target &);

    /*!
     *
     */
    QList<Target> targets() const;

    /*!
     *
     */
    bool isValid() const;

private:
    class Private;
    QSharedDataPointer<Private> d;
};

}

#endif
