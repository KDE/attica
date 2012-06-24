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

#include "metadata.h"
#include "person.h"

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

#ifndef ATTICA_IPARSER_H
#define ATTICA_IPARSER_H

namespace Attica {

template <class T>
class IParser
{
public:
    virtual ~IParser();

    virtual void parse(const QString& data)=0;
    virtual T item() const=0;
    virtual typename T::List itemList() const=0;
    virtual Metadata metadata() const=0;
};

template class IParser<NoneType>;
template class IParser<AccountBalance>;
template class IParser<Achievement>;
template class IParser<Activity>;
template class IParser<BuildService>;
template class IParser<BuildServiceJob>;
template class IParser<BuildServiceJobOutput>;
template class IParser<Category>;
template class IParser<Comment>;
template class IParser<Content>;
template class IParser<Distribution>;
template class IParser<DownloadItem>;
template class IParser<Event>;
template class IParser<Folder>;
template class IParser<Forum>;
template class IParser<HomePageType>;
template class IParser<KnowledgeBaseEntry>;
template class IParser<License>;
template class IParser<Message>;
template class IParser<Person>;
template class IParser<PrivateData>;
template class IParser<Project>;
template class IParser<PublisherField>;
template class IParser<Publisher>;
template class IParser<RemoteAccount>;
template class IParser<Topic>;

}

#endif //ATTICA_IPARSER_H
