/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2012 Laszlo Papp <lpapp@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef ATTICA_CLOUD_H
#define ATTICA_CLOUD_H

#include "attica_export.h"

#include <QList>
#include <QSharedDataPointer>
#include <QUrl>

namespace Attica
{

/*!
 * \class Attica::Cloud
 * \inheaderfile Attica/Cloud
 * \inmodule Attica
 *
 * \brief Represents a cloud service.
 */
class ATTICA_EXPORT Cloud
{
public:
    /*!
     *
     */
    typedef QList<Cloud> List;
    class Parser;

    /*!
     * Creates an empty Cloud
     */
    Cloud();

    Cloud(const Cloud &other);

    Cloud &operator=(const Cloud &other);

    ~Cloud();

    /*!
     * Sets the name of the Cloud service
     *
     * \a name the new name
     */
    void setName(const QString &name);

    /*!
     * Returns the name of the Cloud service.
     */
    QString name() const;

    /*!
     * Sets the url of the Cloud service
     *
     * \a url the new url
     */
    void setUrl(const QString &url);

    /*!
     * Returns the url of the Cloud service.
     */
    QString url() const;

    /*!
     * Sets the icon of the Cloud service
     *
     * \a icon the new icon
     */
    void setIcon(const QUrl &icon);

    /*!
     * Returns the icon of the Cloud service.
     */
    QUrl icon() const;

    /*!
     * Sets the quota of the Cloud service
     *
     * \a quota the new quota
     */
    void setQuota(qulonglong quota);

    /*!
     * Returns the quota of the Cloud service.
     */
    qulonglong quota() const;

    /*!
     * Sets the free amount of the Cloud service
     *
     * \a free the new free amount
     */
    void setFree(qulonglong free);

    /*!
     * Returns the free amount of the Cloud service.
     */
    qulonglong free() const;

    /*!
     * Sets the used amount of the Cloud service
     *
     * \a used the new used amount
     */
    void setUsed(qulonglong used);

    /*!
     * Returns the used amount of the Cloud service.
     */
    qulonglong used() const;

    /*!
     * Sets the relative of the Cloud service
     *
     * \a relative the new relative
     */
    void setRelative(float relative);

    /*!
     * Returns the relative of the Cloud service.
     */
    float relative() const;

    /*!
     * Sets the private key of the Cloud service
     *
     * \a privateKey the new privateKey
     */
    void setKey(const QString &privateKey);

    /*!
     * Returns the private key of the Cloud service.
     */
    QString key() const;

private:
    class Private;
    QSharedDataPointer<Private> d;
};

}

#endif
