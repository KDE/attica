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

#include "job.cpp"

template class Job<NoneType>;
template class Job<AccountBalance>;
template class Job<Achievement>;
template class Job<Activity>;
template class Job<BuildService>;
template class Job<BuildServiceJob>;
template class Job<BuildServiceJobOutput>;
template class Job<Category>;
template class Job<Comment>;
template class Job<Content>;
template class Job<Distribution>;
template class Job<DownloadItem>;
template class Job<Event>;
template class Job<Folder>;
template class Job<Forum>;
template class Job<HomePageType>;
template class Job<KnowledgeBaseEntry>;
template class Job<License>;
template class Job<Message>;
template class Job<Person>;
template class Job<PrivateData>;
template class Job<Project>;
template class Job<PublisherField>;
template class Job<Publisher>;
template class Job<RemoteAccount>;
template class Job<Topic>;
