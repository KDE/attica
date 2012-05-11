/*
    This file is part of KDE.

    Copyright (c) 2009 Eckhart Wörner <ewoerner@kde.org>
    Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>

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

#include "listjob.cpp"
#include "itemjob.cpp"
#include "parser.cpp"

#include "accountbalance.h"
#include "achievement.h"
#include "activity.h"
#include "buildservice.h"
#include "buildservicejob.h"
#include "buildservicejoboutput.h"
#include "downloaditem.h"
#include "privatedata.h"
#include "category.h"
#include "comment.h"
#include "content.h"
#include "distribution.h"
#include "event.h"
#include "folder.h"
#include "forum.h"
#include "homepagetype.h"
#include "knowledgebaseentry.h"
#include "license.h"
#include "message.h"
#include "person.h"
#include "project.h"
#include "publisher.h"
#include "publisherfield.h"
#include "remoteaccount.h"
#include "topic.h"


using namespace Attica;

template class ListJob<Achievement>;
template class ListJob<Activity>;
template class ListJob<BuildServiceJob>;
template class ListJob<BuildService>;
template class ListJob<Category>;
template class ListJob<Comment>;
template class ListJob<Content>;
template class ListJob<Distribution>;
template class ListJob<DownloadItem>;
template class ListJob<Event>;
template class ListJob<Folder>;
template class ListJob<Forum>;
template class ListJob<HomePageType>;
template class ListJob<KnowledgeBaseEntry>;
template class ListJob<License>;
template class ListJob<Message>;
template class ListJob<Person>;
template class ListJob<Topic>;
template class ItemJob<Project>;
template class ItemJob<Publisher>;
template class ItemJob<RemoteAccount>;

template class ItemPostJob<BuildService>;
template class ItemPostJob<BuildServiceJob>;
template class ItemPostJob<Project>;
template class ItemPostJob<Publisher>;
template class ItemPostJob<RemoteAccount>;

template class ListJob<Project>;
template class ListJob<Publisher>;
template class ListJob<PublisherField>;
template class ListJob<RemoteAccount>;

template class ItemJob<AccountBalance>;
template class ItemJob<Achievement>;
template class ItemJob<BuildServiceJob>;
template class ItemJob<BuildServiceJobOutput>;
template class ItemJob<BuildService>;
template class ItemJob<Forum>;
template class ItemJob<PrivateData>;
template class ItemJob<Content>;
template class ItemJob<DownloadItem>;
template class ItemJob<Event>;
template class ItemJob<KnowledgeBaseEntry>;
template class ItemJob<Message>;
template class ItemJob<Person>;
template class ItemPostJob<Achievement>;
template class ItemPostJob<Content>;
template class ItemPostJob<Comment>;
template class ItemPostJob<Forum>;

template class ItemPutJob<Achievement>;

template class ItemDeleteJob<Achievement>;

template class Parser<AccountBalance>;
template class Parser<Achievement>;
template class Parser<Activity>;
template class Parser<BuildService>;
template class Parser<BuildServiceJob>;
template class Parser<BuildServiceJobOutput>;
template class Parser<PrivateData>;
template class Parser<Category>;
template class Parser<Comment>;
template class Parser<Content>;
template class Parser<Distribution>;
template class Parser<DownloadItem>;
template class Parser<Event>;
template class Parser<Folder>;
template class Parser<Forum>;
template class Parser<HomePageType>;
template class Parser<KnowledgeBaseEntry>;
template class Parser<License>;
template class Parser<Message>;
template class Parser<Person>;
template class Parser<Project>;
template class Parser<Publisher>;
template class Parser<PublisherField>;
template class Parser<RemoteAccount>;
template class Parser<Topic>;

