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

#include "achievement.h"
#include "message.h"
#include "person.h"

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

private:
    static T parseElement( const QJsonObject &object );
    void parseMetadata( const QJsonObject &object );
    QJsonValue getDataValue( const QString &data );
    static QStringList arrayToStringList( const QJsonArray &array );
    static QStringList intArrayToStringList( const QJsonArray &array );
    Metadata m_metadata;
    typename T::List m_result;
};

template <> Achievement JsonParser<Achievement>::parseElement( const QJsonObject &object );
template <> Message JsonParser<Message>::parseElement( const QJsonObject &object );
template <> Person JsonParser<Person>::parseElement( const QJsonObject &object );

template class JsonParser<NoneType>;
template class JsonParser<Achievement>;
template class JsonParser<Message>;
template class JsonParser<Person>;

}

#endif // ATTICA_JSONPARSER_H

