/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2009 Frederik Gladhorn <gladhorn@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
 */

#ifndef ATTICA_METADATA_H
#define ATTICA_METADATA_H

#include <QString>

#include <QSharedDataPointer>

#include "attica_export.h"

namespace Attica
{
class BaseJob;

/**
    *Status messages from the server
    */
class ATTICA_EXPORT Metadata
{
public:
    Metadata();
    Metadata(const Metadata &other);
    ~Metadata();
    Metadata &operator=(const Metadata &other);

    enum Error {
        NoError = 0,
        NetworkError,
        OcsError
    };

    /**
     * Check if the job was successful.
     * @return the error state enum returns the type of error (network or ocs)
     */
    Error error() const;
    void setError(Error error);

    /**
     * The status as integer.
     * If the error is an OCS error, refer to http://www.freedesktop.org/wiki/Specifications/open-collaboration-services
     * in any other case it is the network return code.
     */
    int statusCode() const;
    void setStatusCode(int code);

    /**
     * The status of the job, for example "Ok"
     */
    QString statusString() const;
    void setStatusString(const QString &status);

    /// An optional additional message from the server
    QString message();
    void setMessage(const QString &message);

    /// The number of items returned by this job (only relevant for list jobs)
    int totalItems();
    void setTotalItems(int items);

    /// The number of items per page the server was asked for
    int itemsPerPage();
    void setItemsPerPage(int itemsPerPage);

    /// The resulting ID when a PostJob created a new item.
    QString resultingId();
    void setResultingId(const QString &id);

private:
    class Private;
    QSharedDataPointer<Private> d;

    friend class Attica::BaseJob;
};

}

#endif
