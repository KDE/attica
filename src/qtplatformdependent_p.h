/*
    This file is part of KDE.

    Copyright (c) 2009 Eckhart Wörner <ewoerner@kde.org>
    Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
    Copyright (c) 2012 Jeff Mitchell <mitchell@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef ATTICA_QTPLATFORMDEPENDENT_P_H
#define ATTICA_QTPLATFORMDEPENDENT_P_H

#include "platformdependent_v2.h"

#include <QHash>
#include <QMutex>
#include <QSet>
#include <QThread>
#include <QNetworkAccessManager>

namespace Attica
{

class QtPlatformDependent : public Attica::PlatformDependentV2
{
public:
    QtPlatformDependent();
    virtual ~QtPlatformDependent();

    void setNam(QNetworkAccessManager *nam) Q_DECL_OVERRIDE;
    QNetworkAccessManager *nam() Q_DECL_OVERRIDE;

    QList<QUrl> getDefaultProviderFiles() const Q_DECL_OVERRIDE;
    void addDefaultProviderFile(const QUrl &url) Q_DECL_OVERRIDE;
    void removeDefaultProviderFile(const QUrl &url) Q_DECL_OVERRIDE;
    void enableProvider(const QUrl &baseUrl, bool enabled) const Q_DECL_OVERRIDE;
    bool isEnabled(const QUrl &baseUrl) const Q_DECL_OVERRIDE;

    QNetworkReply *post(const QNetworkRequest &request, const QByteArray &data) Q_DECL_OVERRIDE;
    QNetworkReply *post(const QNetworkRequest &request, QIODevice *data) Q_DECL_OVERRIDE;
    QNetworkReply *get(const QNetworkRequest &request) Q_DECL_OVERRIDE;
    bool hasCredentials(const QUrl &baseUrl) const Q_DECL_OVERRIDE;
    bool saveCredentials(const QUrl &baseUrl, const QString &user, const QString &password) Q_DECL_OVERRIDE;
    bool loadCredentials(const QUrl &baseUrl, QString &user, QString &password) Q_DECL_OVERRIDE;
    bool askForCredentials(const QUrl &baseUrl, QString &user, QString &password) Q_DECL_OVERRIDE;
    QNetworkReply *deleteResource(const QNetworkRequest &request) Q_DECL_OVERRIDE;
    QNetworkReply *put(const QNetworkRequest &request, const QByteArray &data) Q_DECL_OVERRIDE;
    QNetworkReply *put(const QNetworkRequest &request, QIODevice *data) Q_DECL_OVERRIDE;

private:
    QMutex m_accessMutex;
    QHash<QThread *, QNetworkAccessManager *> m_threadNamHash;
    QSet<QThread *> m_ourNamSet;
    QHash<QString, QPair <QString, QString> > m_passwords;
};

}

#endif
