/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2008 Cornelius Schumacher <schumacher@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef ATTICA_FOLDER_H
#define ATTICA_FOLDER_H

#include "attica_export.h"
#include <QList>
#include <QSharedDataPointer>
#include <QString>

namespace Attica
{
/*!
 * \class Attica::Folder
 * \inheaderfile Attica/Folder
 * \inmodule Attica
 *
 * \brief Represents a single mail folder.
 */
class ATTICA_EXPORT Folder
{
public:
    /*!
     *
     */
    typedef QList<Folder> List;
    class Parser;

    /*!
     * Creates an empty Folder
     */
    Folder();

    Folder(const Folder &other);

    Folder &operator=(const Folder &other);

    ~Folder();

    /*!
     * Sets the id of the Folder.
     *
     * The id uniquely identifies a Folder with the OCS API.
     *
     * \a id the new id
     */
    void setId(const QString &id);

    /*!
     * Returns the id of the Folder.
     *
     * The id uniquely identifies a Folder with the OCS API.
     */
    QString id() const;

    /*!
     * Sets the name of the Folder.
     *
     * \a name the new name
     */
    void setName(const QString &name);

    /*!
     * Returns the name of the Folder.
     */
    QString name() const;

    /*!
     * Sets the number of messages in the Folder.
     *
     * \a messageCount the new number of messages
     */
    void setMessageCount(int messageCount);

    /*!
     * Returns the number of messages in the Folder.
     */
    int messageCount() const;

    /*!
     * Sets the type of the folder
     *
     * \a type the new type
     */
    void setType(const QString &type);

    /*!
     * Returns the type of the Folder.
     */
    QString type() const;

    /*!
     * Checks whether this Folder has an id
     */
    bool isValid() const;

private:
    class Private;
    QSharedDataPointer<Private> d;
};

}

#endif
