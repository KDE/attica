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

#ifndef ATTICA_QTPLATFORMDEPENDENT_H
#define ATTICA_QTPLATFORMDEPENDENT_H

#include "platformdependent.h"

#include <QtCore/QHash>
#include <QtCore/QMutex>
#include <QtCore/QSet>
#include <QtCore/QThread>
#include <QtNetwork/QNetworkAccessManager>


namespace Attica {

class QtPlatformDependent : public Attica::PlatformDependent
{
public:
    QtPlatformDependent();
    virtual ~QtPlatformDependent();

    virtual void setNetworkAccessManager(QNetworkAccessManager* nam);
    virtual QNetworkAccessManager* nam();

    virtual QList<QUrl> getDefaultProviderFiles() const;
    virtual void addDefaultProviderFile(const QUrl& url);
    virtual void removeDefaultProviderFile(const QUrl& url);
    virtual void enableProvider(const QUrl& baseUrl, bool enabled) const;
    virtual bool isEnabled(const QUrl& baseUrl) const;

    virtual QNetworkReply* post(const QNetworkRequest& request, const QByteArray& data);
    virtual QNetworkReply* post(const QNetworkRequest& request, QIODevice* data);
    virtual QNetworkReply* get(const QNetworkRequest& request);
    virtual bool hasCredentials(const QUrl& baseUrl) const;
    virtual bool saveCredentials(const QUrl& baseUrl, const QString& user, const QString& password);
    virtual bool loadCredentials(const QUrl& baseUrl, QString& user, QString& password);
    virtual bool askForCredentials(const QUrl& baseUrl, QString& user, QString& password);
    virtual QNetworkReply* deleteResource(const QNetworkRequest& request);
    virtual QNetworkReply* put(const QNetworkRequest& request, const QByteArray& data);
    virtual QNetworkReply* put(const QNetworkRequest& request, QIODevice* data);

private:
    QMutex m_accessMutex;
    QHash<QThread*, QNetworkAccessManager*> m_threadNamHash;
    QSet<QThread*> m_ourNamSet;
    QHash<QString, QPair <QString, QString> > m_passwords;
};

}


#endif
