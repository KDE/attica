/*
    This file is part of KDE.

    Copyright (c) 2009 Eckhart Wörner <ewoerner@kde.org>
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

#ifndef ATTICA_XMLPARSERV2_H
#define ATTICA_XMLPARSERV2_H

#include <QtCore/QStringList>
#if QT_VERSION >= 0x050000
#include <QtCore/QXmlStreamReader>
#else
// WARNING: QXmlStreamReader cannot be forward declared (Qt 4.5)
#include <QtXml/QXmlStreamReader>
#endif // QT_VERSION

#include "iparser.h"

#include "nonetype.h"
#include "accountbalance.h"
#include "achievement.h"
#include "activity.h"
#include "buildservice.h"
#include "buildservicejob.h"
#include "buildservicejoboutput.h"
#include "category.h"
#include "comment.h"
#include "content.h"
#include "distribution.h"
#include "downloaditem.h"
#include "event.h"
#include "folder.h"
#include "forum.h"
#include "homepagetype.h"
#include "knowledgebaseentry.h"
#include "license.h"
#include "message.h"
#include "person.h"
#include "privatedata.h"
#include "project.h"
#include "publisherfield.h"
#include "publisher.h"
#include "remoteaccount.h"
#include "topic.h"


namespace Attica {

template <class T>
class XmlParserV2: public IParser<T> {
public:
    void parse(const QString &data);
    T item() const;
    typename T::List itemList() const;
    Metadata metadata() const;
    virtual ~XmlParserV2();

private:
    static QStringList xmlElement();
    static T parseXml(QXmlStreamReader &xml);
    static QList<T> parseXmlChildren(QXmlStreamReader &xml);
    void parseMetadataXml(QXmlStreamReader &xml);
    Metadata m_metadata;
    typename T::List m_result;
};

template <> QStringList XmlParserV2<NoneType>::xmlElement();
template <> QStringList XmlParserV2<AccountBalance>::xmlElement();
template <> QStringList XmlParserV2<Achievement>::xmlElement();
template <> QStringList XmlParserV2<Activity>::xmlElement();
template <> QStringList XmlParserV2<BuildService>::xmlElement();
template <> QStringList XmlParserV2<BuildServiceJob>::xmlElement();
template <> QStringList XmlParserV2<BuildServiceJobOutput>::xmlElement();
template <> QStringList XmlParserV2<Category>::xmlElement();
template <> QStringList XmlParserV2<Comment>::xmlElement();
template <> QStringList XmlParserV2<Content>::xmlElement();
template <> QStringList XmlParserV2<Distribution>::xmlElement();
template <> QStringList XmlParserV2<DownloadItem>::xmlElement();
template <> QStringList XmlParserV2<Event>::xmlElement();
template <> QStringList XmlParserV2<Folder>::xmlElement();
template <> QStringList XmlParserV2<Forum>::xmlElement();
template <> QStringList XmlParserV2<HomePageType>::xmlElement();
template <> QStringList XmlParserV2<KnowledgeBaseEntry>::xmlElement();
template <> QStringList XmlParserV2<License>::xmlElement();
template <> QStringList XmlParserV2<Message>::xmlElement();
template <> QStringList XmlParserV2<Person>::xmlElement();
template <> QStringList XmlParserV2<PrivateData>::xmlElement();
template <> QStringList XmlParserV2<Project>::xmlElement();
template <> QStringList XmlParserV2<PublisherField>::xmlElement();
template <> QStringList XmlParserV2<Publisher>::xmlElement();
template <> QStringList XmlParserV2<RemoteAccount>::xmlElement();
template <> QStringList XmlParserV2<Topic>::xmlElement();

//template <> NoneType XmlParserV2<NoneType>::parseXml(QXmlStreamReader &xml);
template <> AccountBalance XmlParserV2<AccountBalance>::parseXml(QXmlStreamReader &xml);
template <> Achievement XmlParserV2<Achievement>::parseXml(QXmlStreamReader &xml);
template <> Activity XmlParserV2<Activity>::parseXml(QXmlStreamReader &xml);
template <> BuildService XmlParserV2<BuildService>::parseXml(QXmlStreamReader &xml);
template <> BuildServiceJob XmlParserV2<BuildServiceJob>::parseXml(QXmlStreamReader &xml);
template <> BuildServiceJobOutput XmlParserV2<BuildServiceJobOutput>::parseXml(QXmlStreamReader &xml);
template <> Category XmlParserV2<Category>::parseXml(QXmlStreamReader &xml);
template <> Comment XmlParserV2<Comment>::parseXml(QXmlStreamReader &xml);
template <> Content XmlParserV2<Content>::parseXml(QXmlStreamReader &xml);
template <> Distribution XmlParserV2<Distribution>::parseXml(QXmlStreamReader &xml);
template <> DownloadItem XmlParserV2<DownloadItem>::parseXml(QXmlStreamReader &xml);
template <> Event XmlParserV2<Event>::parseXml(QXmlStreamReader &xml);
template <> Folder XmlParserV2<Folder>::parseXml(QXmlStreamReader &xml);
template <> Forum XmlParserV2<Forum>::parseXml(QXmlStreamReader &xml);
template <> HomePageType XmlParserV2<HomePageType>::parseXml(QXmlStreamReader &xml);
template <> KnowledgeBaseEntry XmlParserV2<KnowledgeBaseEntry>::parseXml(QXmlStreamReader &xml);
template <> License XmlParserV2<License>::parseXml(QXmlStreamReader &xml);
template <> Message XmlParserV2<Message>::parseXml(QXmlStreamReader &xml);
template <> Person XmlParserV2<Person>::parseXml(QXmlStreamReader &xml);
template <> PrivateData XmlParserV2<PrivateData>::parseXml(QXmlStreamReader &xml);
template <> Project XmlParserV2<Project>::parseXml(QXmlStreamReader &xml);
template <> PublisherField XmlParserV2<PublisherField>::parseXml(QXmlStreamReader &xml);
template <> Publisher XmlParserV2<Publisher>::parseXml(QXmlStreamReader &xml);
template <> RemoteAccount XmlParserV2<RemoteAccount>::parseXml(QXmlStreamReader &xml);
template <> Topic XmlParserV2<Topic>::parseXml(QXmlStreamReader &xml);

template class XmlParserV2<NoneType>;
template class XmlParserV2<AccountBalance>;
template class XmlParserV2<Achievement>;
template class XmlParserV2<Activity>;
template class XmlParserV2<BuildService>;
template class XmlParserV2<BuildServiceJob>;
template class XmlParserV2<BuildServiceJobOutput>;
template class XmlParserV2<Category>;
template class XmlParserV2<Comment>;
template class XmlParserV2<Content>;
template class XmlParserV2<Distribution>;
template class XmlParserV2<DownloadItem>;
template class XmlParserV2<Event>;
template class XmlParserV2<Folder>;
template class XmlParserV2<Forum>;
template class XmlParserV2<HomePageType>;
template class XmlParserV2<KnowledgeBaseEntry>;
template class XmlParserV2<License>;
template class XmlParserV2<Message>;
template class XmlParserV2<Person>;
template class XmlParserV2<PrivateData>;
template class XmlParserV2<Project>;
template class XmlParserV2<PublisherField>;
template class XmlParserV2<Publisher>;
template class XmlParserV2<RemoteAccount>;
template class XmlParserV2<Topic>;

}


#endif


