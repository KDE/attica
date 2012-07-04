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

#include "jsonparser.h"

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonParseError>
#include <QtCore/QDate>

#include <QtCore/QDebug>

using namespace Attica;

template <class T>
void JsonParser<T>::parse(const QString &data)
{
    m_result.clear();
    QJsonValue dataField = getDataValue(data);
    if (dataField.isArray()) {
        QJsonArray array = dataField.toArray();
        for (QJsonArray::ConstIterator iter = array.constBegin(); iter != array.constEnd(); iter++) {
            m_result.append( parseElement( (*iter).toObject() ) );
        }
    }
    else if (dataField.isObject()) {
        m_result.append( parseElement( dataField.toObject() ) );
    }
}

template <class T>
T JsonParser<T>::item() const
{
    if( m_result.isEmpty() ) {
        return T();
    }
    else {
        return m_result.at(0);
    }
}

template <class T>
typename T::List JsonParser<T>::itemList() const
{
    return m_result;
}

template <class T>
Metadata JsonParser<T>::metadata() const
{
    return m_metadata;
}

template <class T>
T JsonParser<T>::parseElement(const QJsonObject &object)
{
    qWarning() << "It seems like you forgot to create one specialized parser function!";
    return T();
}

template <class T>
void JsonParser<T>::parseMetadata(const QJsonObject &object)
{
    m_metadata.setStatusString( object.value(QLatin1String("status")).toString() );
    m_metadata.setStatusCode( (int)object.value(QLatin1String("statuscode")).toDouble() );
    m_metadata.setTotalItems( (int)object.value(QLatin1String("totalitems")).toDouble() );
    m_metadata.setItemsPerPage( (int)object.value(QLatin1String("itemsperpage")).toDouble() );
}

template <class T>
QJsonValue JsonParser<T>::getDataValue(const QString &data)
{
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson( data.toUtf8(), &error );
    if (document.isNull()) {
        qWarning() << "parse:: JSON Error: " << error.errorString() << " in JSON data: " << data;
        return QJsonValue();
    }
    if (!document.isObject()) {
        qWarning() << "parse:: Expected single JSON object, but got array! JSON data: " << data;
        return QJsonValue();
    }

    QJsonObject object = document.object();
    parseMetadata( object );
    return object.value(QLatin1String("data"));
}

template <>
Message JsonParser<Message>::parseElement(const QJsonObject &object)
{
    Message message;
    for (QJsonObject::ConstIterator iter = object.constBegin(); iter != object.constEnd(); ++iter) {
        if (iter.key() == QLatin1String("id")) {
            message.setId( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("messagefrom")) {
            message.setFrom( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("messageto")) {
            message.setTo( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("senddate")) {
            message.setSent( QDateTime::fromString(iter.value().toString(), Qt::ISODate) );
        }
        else if (iter.key() == QLatin1String("status")) {
            message.setStatus( Message::Status( (int) iter.value().toDouble() ) );
        }
        else if (iter.key() == QLatin1String("subject")) {
            message.setSubject( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("body")) {
            message.setBody( iter.value().toString() );
        }
    }
    return message;
}

template <>
Person JsonParser<Person>::parseElement(const QJsonObject &object)
{
    Person person;
    for (QJsonObject::ConstIterator iter = object.constBegin(); iter != object.constEnd(); ++iter) {
        if (iter.key() == QLatin1String("personid") ) {
            person.setId( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("firstname") ) {
            person.setFirstName( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("lastname") ) {
            person.setLastName( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("birthday") ) {
            person.setBirthday( QDate::fromString(iter.value().toString(), Qt::ISODate) );
        }
        else if (iter.key() == QLatin1String("country") ) {
            person.setCountry( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("latitude") ) {
            person.setLatitude( iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("longitude") ) {
            person.setLongitude( iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("avatarpic") ) {
            person.setAvatarUrl( QUrl(iter.value().toString()) );
        }
        else if (iter.key() == QLatin1String("homepage") ) {
            person.setHomepage( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("city") ) {
            person.setCity( iter.value().toString() );
        }
        else {
            person.addExtendedAttribute( iter.key(), iter.value().toString() );
        }
    }
    return person;
}

