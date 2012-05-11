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

#include "parserfactory.h"
#include "xmlparser.cpp"

using namespace Attica;

template class XmlParser<AccountBalance>;
template class XmlParser<Achievement>;
template class XmlParser<Activity>;
template class XmlParser<BuildService>;
template class XmlParser<BuildServiceJob>;
template class XmlParser<BuildServiceJobOutput>;
template class XmlParser<PrivateData>;
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
template class XmlParser<Project>;
template class XmlParser<Publisher>;
template class XmlParser<PublisherField>;
template class XmlParser<RemoteAccount>;
template class XmlParser<Topic>;
