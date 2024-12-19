/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2010 Intel Corporation
    SPDX-FileContributor: Mateu Batle Sastre <mbatle@collabora.co.uk>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef ATTICA_ICON_H
#define ATTICA_ICON_H

#include <QSharedDataPointer>
#include <QUrl>

#include "attica_export.h"

namespace Attica
{
/*!
    \class Attica::Icon
    \inheaderfile Attica/Icon
    \inmodule Attica

    \brief The Icon class contains information about an icon.

    It consists of a Url and icon size information.
 */
class ATTICA_EXPORT Icon
{
public:
    /*!
     *
     */
    typedef QList<Icon> List;

    /*!
     * Creates an empty Icon
     */
    Icon();

    Icon(const Icon &other);

    Icon &operator=(const Icon &other);

    ~Icon();

    /*!
     *
     */
    QUrl url() const;

    /*!
     *
     */
    void setUrl(const QUrl &url);

    /*!
     *
     */
    uint width() const;

    /*!
     *
     */
    void setWidth(uint width);

    /*!
     *
     */
    uint height() const;

    /*!
     *
     */
    void setHeight(uint height);

private:
    class Private;
    QSharedDataPointer<Private> d;
};

}

#endif
