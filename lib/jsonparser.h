/*
    This file is part of KDE.

    Copyright (c) 2012 Felix Rohrbach <fxrh@gmx.de>

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

#ifndef ATTICA_JSONPARSER_H
#define ATTICA_JSONPARSER_H

#include "iparser.h"

#include "accountbalance.h"
#include "achievement.h"
#include "activity.h"
#include "category.h"
#include "comment.h"
#include "content.h"
#include "distribution.h"
#include "downloaditem.h"
#include "event.h"
#include "folder.h"
#include "forum.h"
#include "homepagetype.h"
#include "icon.h"
#include "knowledgebaseentry.h"
#include "license.h"
#include "message.h"
#include "person.h"
#include "project.h"
#include "remoteaccount.h"
#include "topic.h"

#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>

namespace Attica
{

template <class T>
class JsonParser: public IParser<T>
{
public:
    void parse( const QString &data );
    T item() const;
    typename T::List itemList() const;
    Metadata metadata() const;
    static T parseElement( const QJsonObject &object );

private:
    void parseMetadata( const QJsonObject &object );
    QJsonValue getDataValue( const QString &data );
    static QStringList arrayToStringList( const QJsonArray &array );
    static QStringList intArrayToStringList( const QJsonArray &array );
    Metadata m_metadata;
    typename T::List m_result;
};

template <> AccountBalance JsonParser<AccountBalance>::parseElement( const QJsonObject &object );
template <> Achievement JsonParser<Achievement>::parseElement( const QJsonObject &object );
template <> Activity JsonParser<Activity>::parseElement( const QJsonObject &object );
template <> Category JsonParser<Category>::parseElement( const QJsonObject &object );
template <> Comment JsonParser<Comment>::parseElement( const QJsonObject &object );
template <> Content JsonParser<Content>::parseElement( const QJsonObject &object );
template <> Distribution JsonParser<Distribution>::parseElement( const QJsonObject &object );
template <> DownloadItem JsonParser<DownloadItem>::parseElement( const QJsonObject &object );
template <> Event JsonParser<Event>::parseElement( const QJsonObject &object );
template <> Folder JsonParser<Folder>::parseElement( const QJsonObject &object );
template <> Forum JsonParser<Forum>::parseElement( const QJsonObject &object );
template <> HomePageType JsonParser<HomePageType>::parseElement( const QJsonObject &object );
template <> Icon JsonParser<Icon>::parseElement( const QJsonObject &object );
template <> KnowledgeBaseEntry JsonParser<KnowledgeBaseEntry>::parseElement( const QJsonObject &object );
template <> License JsonParser<License>::parseElement( const QJsonObject &object );
template <> Message JsonParser<Message>::parseElement( const QJsonObject &object );
template <> Person JsonParser<Person>::parseElement( const QJsonObject &object );
template <> Project JsonParser<Project>::parseElement( const QJsonObject &object );
template <> RemoteAccount JsonParser<RemoteAccount>::parseElement( const QJsonObject &object );
template <> Topic JsonParser<Topic>::parseElement( const QJsonObject &object );

template class JsonParser<NoneType>;
template class JsonParser<AccountBalance>;
template class JsonParser<Achievement>;
template class JsonParser<Activity>;
template class JsonParser<Category>;
template class JsonParser<Comment>;
template class JsonParser<Content>;
template class JsonParser<Distribution>;
template class JsonParser<DownloadItem>;
template class JsonParser<Event>;
template class JsonParser<Folder>;
template class JsonParser<Forum>;
template class JsonParser<HomePageType>;
template class JsonParser<Icon>;
template class JsonParser<KnowledgeBaseEntry>;
template class JsonParser<License>;
template class JsonParser<Message>;
template class JsonParser<Person>;
template class JsonParser<Project>;
template class JsonParser<RemoteAccount>;
template class JsonParser<Topic>;

}

#endif // ATTICA_JSONPARSER_H

