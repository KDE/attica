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

template <class T>
QStringList JsonParser<T>::arrayToStringList( const QJsonArray &array )
{
    QStringList stringList;
    for (QJsonArray::ConstIterator iter = array.constBegin(); iter != array.constEnd(); iter++) {
        stringList << (*iter).toString();
    }
    return stringList;
}

template <class T>
QStringList JsonParser<T>::intArrayToStringList( const QJsonArray &array )
{
    QStringList stringList;
    for (QJsonArray::ConstIterator iter = array.constBegin(); iter != array.constEnd(); iter++) {
        stringList << QString::number( (int) (*iter).toDouble() );
    }
    return stringList;
}

template <>
Achievement JsonParser<Achievement>::parseElement(const QJsonObject &object)
{
    Achievement achievement;
    for (QJsonObject::ConstIterator iter = object.constBegin(); iter != object.constEnd(); ++iter) {
        if (iter.key() == QLatin1String("id")) {
            achievement.setId( QString::number( (int) iter.value().toDouble() ) );
        }
        else if (iter.key() == QLatin1String("content_id")) {
            achievement.setContentId( QString::number( (int) iter.value().toDouble() ) );
        }
        else if (iter.key() == QLatin1String("name")) {
            achievement.setName( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("description")) {
            achievement.setDescription( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("explanation")) {
            achievement.setExplanation( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("points")) {
            achievement.setPoints( (int) iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("image")) {
            achievement.setImage( QUrl( iter.value().toString() ) );
        }
        else if (iter.key() == QLatin1String("dependencies")) {
            QStringList dependencies;
            const QJsonArray &array = iter.value().toArray();
            for (QJsonArray::ConstIterator iter = array.constBegin(); iter != array.constEnd(); ++iter) {
                const QJsonObject &object = (*iter).toObject();
                if (object.contains(QLatin1String("achievement_id"))) {
                    dependencies << QString::number( (int) object.value(QLatin1String("achievement_id")).toDouble() );
                }
            }
            achievement.setDependencies( dependencies );
        }
        else if (iter.key() == QLatin1String("visibility")) {
            if (iter.value() == QLatin1String("visible")) {
                achievement.setVisibility( Achievement::VisibleAchievement );
            }
            else if (iter.value() == QLatin1String("dependents")) {
                achievement.setVisibility( Achievement::DependentsAchievement );
            }
            else if (iter.value() == QLatin1String("secret")) {
                achievement.setVisibility( Achievement::SecretAchievement );
            }
        }
        else if (iter.key() == QLatin1String("type")) {
            if (iter.value() == QLatin1String("flowing")) {
                achievement.setType( Achievement::FlowingAchievement );
            }
            else if (iter.value() == QLatin1String("stepped")) {
                achievement.setType( Achievement::SteppedAchievement );
            }
            else if (iter.value() == QLatin1String("namedsteps")) {
                achievement.setType( Achievement::NamedstepsAchievement );
            }
            else if (iter.value() == QLatin1String("set")) {
                achievement.setType( Achievement::SetAchievement );
            }
        }
        else if (iter.key() == QLatin1String("options")) {
            QStringList options;
            const QJsonArray &array = iter.value().toArray();
            for (QJsonArray::ConstIterator iter = array.constBegin(); iter != array.constEnd(); ++iter) {
                const QJsonObject &object = (*iter).toObject();
                if (object.contains(QLatin1String("option"))) {
                    options << object.value(QLatin1String("option")).toString();
                }
            }
            achievement.setOptions( options );
        }
        else if (iter.key() == QLatin1String("steps")) {
            achievement.setSteps( (int) iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("progress")) {
            if (iter.value().isArray()) {
                QStringList progress;
                const QJsonArray &array = iter.value().toArray();
                for (QJsonArray::ConstIterator iter = array.constBegin(); iter != array.constEnd(); ++iter) {
                    const QJsonObject &object = (*iter).toObject();
                    if (object.contains(QLatin1String("reached"))) {
                        progress << object.value(QLatin1String("reached")).toString();
                    }
                }
                achievement.setProgress( progress );
            }
            else {
                achievement.setProgress( iter.value().toVariant() );
            }
        }
    }
    return achievement;
}

template <>
Activity JsonParser<Activity>::parseElement(const QJsonObject &object)
{
    Activity activity;
    Person person;
    for (QJsonObject::ConstIterator iter = object.constBegin(); iter != object.constEnd(); ++iter) {
        if (iter.key() == QLatin1String("id")) {
            activity.setId( QString::number( (int) iter.value().toDouble() ) );
        }
        else if (iter.key() == QLatin1String("timestamp")) {
            activity.setTimestamp( QDateTime::fromString(iter.value().toString(), Qt::ISODate) );
        }
        else if (iter.key() == QLatin1String("message")) {
            activity.setMessage( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("link")) {
            activity.setLink( QUrl( iter.value().toString() ) );
        }
        else if (iter.key() == QLatin1String("personid")) {
            person.setId( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("firstname")) {
            person.setFirstName( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("lastname")) {
            person.setLastName( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("avatarpic")) {
            person.setAvatarUrl( QUrl( iter.value().toString() ) );
        }
    }
    activity.setAssociatedPerson( person );
    return activity;
}

template <>
Category JsonParser<Category>::parseElement(const QJsonObject &object)
{
    Category category;
    for (QJsonObject::ConstIterator iter = object.constBegin(); iter != object.constEnd(); ++iter) {
        if (iter.key() == QLatin1String("id")) {
            category.setId( QString::number( (int) iter.value().toDouble() ) );
        }
        else if (iter.key() == QLatin1String("name")) {
            category.setName( iter.value().toString() );
        }
    }
    return category;
}

template <>
Comment JsonParser<Comment>::parseElement(const QJsonObject &object)
{
    Comment comment;
    QList<Comment> children;
    for (QJsonObject::ConstIterator iter = object.constBegin(); iter != object.constEnd(); ++iter) {
        if (iter.key() == QLatin1String("id")) {
            comment.setId( QString::number( (int) iter.value().toDouble() ) );
        }
        else if (iter.key() == QLatin1String("subject")) {
            comment.setSubject( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("text")) {
            comment.setText( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("childcount")) {
            comment.setChildCount( (int) iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("user")) {
            comment.setUser( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("date")) {
            comment.setDate( QDateTime::fromString(iter.value().toString(), Qt::ISODate) );
        }
        else if (iter.key() == QLatin1String("score")) {
            comment.setScore( (int) iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("children")) {
            const QJsonArray &array = iter.value().toArray();
            for (QJsonArray::ConstIterator childIter = array.constBegin(); childIter != array.constEnd(); ++childIter) {
                children.append( parseElement((*childIter).toObject()) );
            }
        }
    }
    comment.setChildren( children );
    return comment;
}

template <>
Content JsonParser<Content>::parseElement(const QJsonObject &object)
{
    Content content;
    QList<Icon> icons;
    QList<QUrl> videos;
    for (QJsonObject::ConstIterator iter = object.constBegin(); iter != object.constEnd(); ++iter) {
        if (iter.key() == QLatin1String("id")) {
            content.setId( QString::number( (int) iter.value().toDouble() ) );
        }
        else if (iter.key() == QLatin1String("name")) {
            content.setName( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("score")) {
            content.setRating( (int) iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("downloads")) {
            content.setDownloads( (int) iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("comments")) {
            content.setNumberOfComments( (int) iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("created")) {
            content.setCreated( QDateTime::fromString( iter.value().toString(), Qt::ISODate ) );
        }
        else if (iter.key() == QLatin1String("changed")) {
            content.setUpdated( QDateTime::fromString( iter.value().toString(), Qt::ISODate ) );
        }
        else if (iter.key() == QLatin1String("icon")) {
            const QJsonArray &array = iter.value().toArray();
            for (QJsonArray::ConstIterator arrayIter = array.constBegin(); arrayIter != array.constEnd(); ++arrayIter) {
                icons.append( JsonParser<Icon>::parseElement( (*arrayIter).toObject() ) );
            }
        }
        else if (iter.key() == QLatin1String("video")) {
            const QJsonArray &array = iter.value().toArray();
            for (QJsonArray::ConstIterator arrayIter = array.constBegin(); arrayIter != array.constEnd(); ++arrayIter) {
                const QJsonObject &video = (*arrayIter).toObject();
                if (video.contains( QLatin1String("link") )) {
                    videos.append( QUrl( video.value( QLatin1String("link") ).toString() ) );
                }
            }
        }
        else {
            content.addAttribute( iter.key(), iter.value().toString() );
        }
    }
    content.setIcons( icons );
    content.setVideos( videos );
    if (content.updated().isNull()) {
        content.setUpdated( content.created() );
    }
    return content;
}

template <>
Distribution JsonParser<Distribution>::parseElement(const QJsonObject &object)
{
    Distribution distribution;
    for (QJsonObject::ConstIterator iter = object.constBegin(); iter != object.constEnd(); ++iter) {
        if (iter.key() == QLatin1String("id")) {
            distribution.setId( (uint) iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("name")) {
            distribution.setName( iter.value().toString() );
        }
    }
    return distribution;
}

template <>
HomePageType JsonParser<HomePageType>::parseElement(const QJsonObject &object)
{
    HomePageType type;
    for (QJsonObject::ConstIterator iter = object.constBegin(); iter != object.constEnd(); ++iter) {
        if (iter.key() == QLatin1String("id")) {
            type.setId( (uint) iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("name")) {
            type.setName( iter.value().toString() );
        }
    }
    return type;
}

template <>
Icon JsonParser<Icon>::parseElement(const QJsonObject &object)
{
    Icon icon;
    for (QJsonObject::ConstIterator iter = object.constBegin(); iter != object.constEnd(); ++iter) {
        if (iter.key() == QLatin1String("width")) {
            icon.setWidth( (uint) iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("height")) {
            icon.setHeight( (uint) iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("link")) {
            icon.setUrl( QUrl( iter.value().toString() ) );
        }
    }
    return icon;
}

template <>
License JsonParser<License>::parseElement(const QJsonObject &object)
{
    License license;
    for (QJsonObject::ConstIterator iter = object.constBegin(); iter != object.constEnd(); ++iter) {
        if (iter.key() == QLatin1String("id")) {
            license.setId( (uint) iter.value().toDouble() );
        }
        else if (iter.key() == QLatin1String("name")) {
            license.setName( iter.value().toString() );
        }
        else if (iter.key() == QLatin1String("link")) {
            license.setUrl( QUrl( iter.value().toString() ) );
        }
    }
    return license;
}

template <>
Message JsonParser<Message>::parseElement(const QJsonObject &object)
{
    Message message;
    for (QJsonObject::ConstIterator iter = object.constBegin(); iter != object.constEnd(); ++iter) {
        if (iter.key() == QLatin1String("id")) {
            message.setId( QString::number( (int) iter.value().toDouble() ) );
        }
        else if (iter.key() == QLatin1String("message from")) {
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

