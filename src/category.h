/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2008 Cornelius Schumacher <schumacher@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/
#ifndef ATTICA_CATEGORY_H
#define ATTICA_CATEGORY_H

#include <QList>
#include <QSharedDataPointer>

#include "attica_export.h"

namespace Attica
{
/*!
 * \class Attica::Category
 * \inheaderfile Attica/Category
 * \inmodule Attica
 *
 * \brief Represents a single content category.
 */
class ATTICA_EXPORT Category
{
public:
    /*!
     *
     */
    typedef QList<Category> List;
    class Parser;

    /*!
     * Creates an empty Category
     */
    Category();

    Category(const Category &other);

    Category &operator=(const Category &other);

    ~Category();

    /*!
     * Sets the id of the Category.
     *
     * The id uniquely identifies a Category with the OCS API.
     *
     * \a id the new id
     */
    void setId(const QString &);

    /*!
     * Returns the id of the Category.
     *
     * The id uniquely identifies a Category with the OCS API.
     */
    QString id() const;

    /*!
     * Sets the name of the Category.
     *
     * \a name the new name
     */
    void setName(const QString &name);

    /*!
     * Returns the name of the Category.
     */
    QString name() const;

    /*!
     * Returns whether this Category has an id
     */
    bool isValid() const;

    /*!
     * Sets the display name of the Category.
     *
     * This name is guaranteed to be user friendly, while name may be
     * internal for the server
     *
     * \a name the new name
     * \since 5.31
     */
    void setDisplayName(const QString &name);

    /*!
     * Returns the display name of the Category.
     *
     * This name is guaranteed to be user friendly, while name may be
     * internal for the server
     *
     * \since 5.31
     */
    QString displayName() const;

private:
    class Private;
    QSharedDataPointer<Private> d;
};

}

#endif
