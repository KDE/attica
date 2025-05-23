/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2009 Frederik Gladhorn <gladhorn@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef ATTICA_DOWNLOADITEM_H
#define ATTICA_DOWNLOADITEM_H

#include <QSharedDataPointer>
#include <QUrl>

#include "attica_export.h"
#include "downloaddescription.h"

namespace Attica
{

/*!
 * \class Attica::DownloadItem
 * \inheaderfile Attica/DownloadItem
 * \inmodule Attica
 *
 * \brief Represents a download item.
 */
class ATTICA_EXPORT DownloadItem
{
public:
    /*!
     *
     */
    typedef QList<DownloadItem> List;
    class Parser;

    /*!
     * Creates an empty DownloadItem
     */
    DownloadItem();

    DownloadItem(const DownloadItem &other);

    DownloadItem &operator=(const DownloadItem &other);

    ~DownloadItem();

    /*!
     *
     */
    void setUrl(const QUrl &url);

    /*!
     *
     */
    QUrl url() const;

    /*!
     *
     */
    void setMimeType(const QString &mimeType);

    /*!
     *
     */
    QString mimeType() const;

    /*!
     *
     */
    void setPackageName(const QString &packageName);

    /*!
     *
     */
    QString packageName() const;

    /*!
     *
     */
    void setPackageRepository(const QString &packageRepository);

    /*!
     *
     */
    QString packageRepository() const;

    /*!
     *
     */
    void setGpgFingerprint(const QString &gpgFingerprint);

    /*!
     *
     */
    QString gpgFingerprint() const;

    /*!
     *
     */
    void setGpgSignature(const QString &gpgSignature);

    /*!
     *
     */
    QString gpgSignature() const;

    /*!
     *
     */
    void setType(Attica::DownloadDescription::Type type);

    /*!
     *
     */
    Attica::DownloadDescription::Type type();

private:
    class Private;
    QSharedDataPointer<Private> d;
};

}

#endif // DOWNLOADITEM_H
