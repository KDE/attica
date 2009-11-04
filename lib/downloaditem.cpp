/*
    This file is part of KDE.
    
    Copyright (c) 2009 Frederik Gladhorn <gladhorn@kde.org>
    
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License version 2 as published by the Free Software Foundation.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/


#include "downloaditem.h"

using namespace Attica;

class DownloadItem::Private :public QSharedData
{
public:
    QUrl m_url;
};


DownloadItem::DownloadItem()
    :d(new Private)
{
}

DownloadItem::DownloadItem(const Attica::DownloadItem& other)
    :d(other.d)
{
}

DownloadItem& DownloadItem::operator=(const Attica::DownloadItem& other)
{
    d = other.d;
    return *this;
}

DownloadItem::~DownloadItem()
{}

void DownloadItem::setUrl(const QUrl& url)
{
    d->m_url = url;
}

QUrl DownloadItem::url() const
{
    return d->m_url;
}
