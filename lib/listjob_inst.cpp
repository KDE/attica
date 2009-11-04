/*
    This file is part of KDE.

    Copyright (c) 2009 Eckhart Wörner <ewoerner@kde.org>

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

#include "activity.h"
#include "activityparser.h"
#include "category.h"
#include "categoryparser.h"
#include "content.h"
#include "contentparser.h"
#include "downloaditemparser.h"
#include "event.h"
#include "eventparser.h"
#include "folder.h"
#include "folderparser.h"
#include "message.h"
#include "messageparser.h"
#include "person.h"
#include "personparser.h"
#include "knowledgebaseentry.h"
#include "knowledgebaseentryparser.h"

using namespace Attica;

template class ListJob<Activity>;
template class ListJob<Category>;
template class ListJob<Content>;
template class ListJob<Event>;
template class ListJob<Folder>;
template class ListJob<Message>;
template class ListJob<Person>;
template class ListJob<KnowledgeBaseEntry>;
template class ListJob<DownloadItem>;

template class ItemJob<Content>;
template class ItemJob<Event>;
template class ItemJob<Message>;
template class ItemJob<KnowledgeBaseEntry>;
template class ItemJob<DownloadItem>;
template class ItemJob<Person>;
template class ItemPostJob<Content>;

template class Parser<Activity>;
template class Parser<Category>;
template class Parser<Content>;
template class Parser<Event>;
template class Parser<Folder>;
template class Parser<KnowledgeBaseEntry>;
template class Parser<Message>;
template class Parser<Person>;
template class Parser<DownloadItem>;
