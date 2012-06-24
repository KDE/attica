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
class XmlParser: public IParser<T> {
public:
    void parse(const QString &data);
    T item() const;
    typename T::List itemList() const;
    Metadata metadata() const;
    virtual ~XmlParser();

private:
    static QStringList xmlElement();
    static T parseXml(QXmlStreamReader &xml);
    static QList<T> parseXmlChildren(QXmlStreamReader &xml);
    void parseMetadataXml(QXmlStreamReader &xml);
    Metadata m_metadata;
    typename T::List m_result;
};

template <> QStringList XmlParser<NoneType>::xmlElement();
template <> QStringList XmlParser<AccountBalance>::xmlElement();
template <> QStringList XmlParser<Achievement>::xmlElement();
template <> QStringList XmlParser<Activity>::xmlElement();
template <> QStringList XmlParser<BuildService>::xmlElement();
template <> QStringList XmlParser<BuildServiceJob>::xmlElement();
template <> QStringList XmlParser<BuildServiceJobOutput>::xmlElement();
template <> QStringList XmlParser<Category>::xmlElement();
template <> QStringList XmlParser<Comment>::xmlElement();
template <> QStringList XmlParser<Content>::xmlElement();
template <> QStringList XmlParser<Distribution>::xmlElement();
template <> QStringList XmlParser<DownloadItem>::xmlElement();
template <> QStringList XmlParser<Event>::xmlElement();
template <> QStringList XmlParser<Folder>::xmlElement();
template <> QStringList XmlParser<Forum>::xmlElement();
template <> QStringList XmlParser<HomePageType>::xmlElement();
template <> QStringList XmlParser<KnowledgeBaseEntry>::xmlElement();
template <> QStringList XmlParser<License>::xmlElement();
template <> QStringList XmlParser<Message>::xmlElement();
template <> QStringList XmlParser<Person>::xmlElement();
template <> QStringList XmlParser<PrivateData>::xmlElement();
template <> QStringList XmlParser<Project>::xmlElement();
template <> QStringList XmlParser<PublisherField>::xmlElement();
template <> QStringList XmlParser<Publisher>::xmlElement();
template <> QStringList XmlParser<RemoteAccount>::xmlElement();
template <> QStringList XmlParser<Topic>::xmlElement();

//template <> NoneType XmlParser<NoneType>::parseXml(QXmlStreamReader &xml);
template <> AccountBalance XmlParser<AccountBalance>::parseXml(QXmlStreamReader &xml);
template <> Achievement XmlParser<Achievement>::parseXml(QXmlStreamReader &xml);
template <> Activity XmlParser<Activity>::parseXml(QXmlStreamReader &xml);
template <> BuildService XmlParser<BuildService>::parseXml(QXmlStreamReader &xml);
template <> BuildServiceJob XmlParser<BuildServiceJob>::parseXml(QXmlStreamReader &xml);
template <> BuildServiceJobOutput XmlParser<BuildServiceJobOutput>::parseXml(QXmlStreamReader &xml);
template <> Category XmlParser<Category>::parseXml(QXmlStreamReader &xml);
template <> Comment XmlParser<Comment>::parseXml(QXmlStreamReader &xml);
template <> Content XmlParser<Content>::parseXml(QXmlStreamReader &xml);
template <> Distribution XmlParser<Distribution>::parseXml(QXmlStreamReader &xml);
template <> DownloadItem XmlParser<DownloadItem>::parseXml(QXmlStreamReader &xml);
template <> Event XmlParser<Event>::parseXml(QXmlStreamReader &xml);
template <> Folder XmlParser<Folder>::parseXml(QXmlStreamReader &xml);
template <> Forum XmlParser<Forum>::parseXml(QXmlStreamReader &xml);
template <> HomePageType XmlParser<HomePageType>::parseXml(QXmlStreamReader &xml);
template <> KnowledgeBaseEntry XmlParser<KnowledgeBaseEntry>::parseXml(QXmlStreamReader &xml);
template <> License XmlParser<License>::parseXml(QXmlStreamReader &xml);
template <> Message XmlParser<Message>::parseXml(QXmlStreamReader &xml);
template <> Person XmlParser<Person>::parseXml(QXmlStreamReader &xml);
template <> PrivateData XmlParser<PrivateData>::parseXml(QXmlStreamReader &xml);
template <> Project XmlParser<Project>::parseXml(QXmlStreamReader &xml);
template <> PublisherField XmlParser<PublisherField>::parseXml(QXmlStreamReader &xml);
template <> Publisher XmlParser<Publisher>::parseXml(QXmlStreamReader &xml);
template <> RemoteAccount XmlParser<RemoteAccount>::parseXml(QXmlStreamReader &xml);
template <> Topic XmlParser<Topic>::parseXml(QXmlStreamReader &xml);

template class XmlParser<NoneType>;
template class XmlParser<AccountBalance>;
template class XmlParser<Achievement>;
template class XmlParser<Activity>;
template class XmlParser<BuildService>;
template class XmlParser<BuildServiceJob>;
template class XmlParser<BuildServiceJobOutput>;
template class XmlParser<Category>;
template class XmlParser<Comment>;
template class XmlParser<Content>;
template class XmlParser<Distribution>;
template class XmlParser<DownloadItem>;
template class XmlParser<Event>;
template class XmlParser<Folder>;
template class XmlParser<Forum>;
template class XmlParser<HomePageType>;
template class XmlParser<KnowledgeBaseEntry>;
template class XmlParser<License>;
template class XmlParser<Message>;
template class XmlParser<Person>;
template class XmlParser<PrivateData>;
template class XmlParser<Project>;
template class XmlParser<PublisherField>;
template class XmlParser<Publisher>;
template class XmlParser<RemoteAccount>;
template class XmlParser<Topic>;

}


#endif


