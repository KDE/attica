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

#include "xmlparser.h"
#include <QStringList>
#include <QDebug>

#include "atticautils.h"

using namespace Attica;


template <class T>
XmlParser<T>::~XmlParser()
{
}


template <class T>
void XmlParser<T>::parse(const QString &data)
{
/*
        QString testxml = QString("<?xml version=\"1.0\"?>\
<ocs>\
 <meta>\
  <status>ok</status>\
  <statuscode>100</statuscode>\
  <message></message>\
 </meta>\
 <data>\
  <buildservice>\
   <id>obs</id>\
   <name>openSUSE Build Service</name>\
   <registrationurl>foobar.com</registrationurl>\
   <supportedtargets>\
    <target>openSUSE 11.2 32bit Intel</target>\
    <target>openSUSE 11.3 64bit Intel</target>\
    <target>openSUSE 11.3 32bit Intel</target>\
    <target>openSUSE 11.3 64bit Intel</target>\
   </supportedtargets>\
  </buildservice>\
  <buildservice>\
   <id>mbs</id>\
   <name>MeeGo Build Service</name>\
   <registrationurl>foobar42.com</registrationurl>\
   <supportedtargets>\
    <target>MeeGo 1.0 Intel</target>\
    <target>MeeGo 1.0 ARM</target>\
    <target>MeeGo 1.1 Intel</target>\
    <target>MeeGo 1.1 ARM</target>\
   </supportedtargets>\
  </buildservice>\
  <buildservice>\
   <id>sbs</id>\
   <name>Sebas' Build Service</name>\
   <registrationurl>foobar42.com</registrationurl>\
   <supportedtargets>\
    <target>sebasix 1.3 33bit</target>\
    <target>sebasis 4.4 14bit</target>\
    <target>sebasix 1.3 65bit</target>\
    <target>sebasis 4.4 37bit</target>\
   </supportedtargets>\
  </buildservice>\
 </data>\
</ocs>\
 ");

    qDebug() << "parsing list:" << xmlString;
    */
    QStringList elements = xmlElement();
    m_result.clear();

    QXmlStreamReader xml( data );

    while (!xml.atEnd()) {
        xml.readNext();
        //qDebug() << "parseList():: Looking for:" << xml.name().toString();
        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("data")) {
                while (!xml.atEnd()) {
                    xml.readNext();

                    if (xml.isEndElement() && xml.name() == QLatin1String("data")) {
                        break;
                    }

                    if (xml.isStartElement() && elements.contains(xml.name().toString())) {
                        //qDebug() << "xxxxxxxxx New Item!" << xml.name().toString();
                        m_result.append(parseXml(xml));
                    }
                }
            } else if (xml.name() == QLatin1String("meta")) {
                parseMetadataXml(xml);
            }
        }
    }
    if (xml.hasError()) {
        // TODO: error handling in metadata?
        qWarning() << "parseList():: XML Error: " << xml.errorString() << "\nIn XML:\n" << data;
    }
}

template <class T>
T XmlParser<T>::item() const
{
    if (m_result.size() == 0) {
        return T();
    }
    return m_result.at(0);
}

template <class T>
typename T::List XmlParser<T>::itemList() const
{
    return m_result;
}

template <class T>
void XmlParser<T>::parseMetadataXml(QXmlStreamReader &xml)
{
    while ( !xml.atEnd() ) {
        xml.readNext();
        if (xml.isEndElement() && xml.name() == QLatin1String("meta")) {
            break;
        } else if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("status")) {
                m_metadata.setStatusString(xml.readElementText());
            } else if (xml.name() == QLatin1String("statuscode")) {
                m_metadata.setStatusCode(xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("message")) {
                m_metadata.setMessage(xml.readElementText());
            } else if (xml.name() == QLatin1String("totalitems")) {
                m_metadata.setTotalItems(xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("itemsperpage")) {
                m_metadata.setItemsPerPage(xml.readElementText().toInt());
            }
        }
    }
    if (xml.hasError()) {
        // TODO: error handling in metadata?
        qWarning() << "XML Error: " << xml.errorString();
    }

}

template <class T>
Metadata XmlParser<T>::metadata() const {
    return m_metadata;
}

template <class T>
QList<T> XmlParser<T>::parseXmlChildren(QXmlStreamReader& xml)
{
    QList<T> children;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xmlElement().contains(xml.name().toString())) {
                T child = parseXml(xml);
                children.append(child);
            }
        } else if (xml.isEndElement() && xml.name() == QLatin1String("children")) {
            break;
        }
    }

    return children;
}

template <class T>
QStringList XmlParser<T>::xmlElement()
{
    qWarning() << "Something went wrong here. It seems like you forgot to add a specialized"
                " function for XmlParser::xmlElement.";
    return QStringList();
}

template <>
QStringList XmlParser<NoneType>::xmlElement()
{
    return QStringList();
}

template <>
QStringList XmlParser<AccountBalance>::xmlElement()
{
    return QStringList(QLatin1String("person"));
}

template <>
QStringList XmlParser<Achievement>::xmlElement()
{
    return QStringList(QLatin1String( "achievement" ));
}

template <>
QStringList XmlParser<Activity>::xmlElement()
{
    return QStringList(QLatin1String("activity"));
}

template <>
QStringList XmlParser<BuildService>::xmlElement()
{
    return QStringList(QLatin1String("buildservice")) << QLatin1String("user");
}

template <>
QStringList XmlParser<BuildServiceJob>::xmlElement()
{
    return QStringList(QLatin1String("buildjob")) << QLatin1String("user");
}

template <>
QStringList XmlParser<BuildServiceJobOutput>::xmlElement()
{
    return QStringList(QLatin1String("output"));
}

template <>
QStringList XmlParser<Category>::xmlElement()
{
    return QStringList(QLatin1String( "category" ));
}

template <>
QStringList XmlParser<Comment>::xmlElement()
{
    return QStringList(QLatin1String( "comment" ));
}

template <>
QStringList XmlParser<Content>::xmlElement()
{
    return QStringList(QLatin1String( "content" ));
}

template <>
QStringList XmlParser<Distribution>::xmlElement()
{
    return QStringList(QLatin1String( "distribution" ));
}

template <>
QStringList XmlParser<DownloadItem>::xmlElement()
{
    return QStringList(QLatin1String( "content" ));
}

template <>
QStringList XmlParser<Event>::xmlElement()
{
    return QStringList(QLatin1String( "event" ));
}

template <>
QStringList XmlParser<Folder>::xmlElement()
{
    return QStringList(QLatin1String( "folder" ));
}

template <>
QStringList XmlParser<Forum>::xmlElement()
{
    return QStringList(QLatin1String( "forum" ));
}

template <>
QStringList XmlParser<HomePageType>::xmlElement()
{
    return QStringList(QLatin1String( "homepagetype" ));
}

template <>
QStringList XmlParser<KnowledgeBaseEntry>::xmlElement()
{
    return QStringList(QLatin1String( "content" ));
}

template <>
QStringList XmlParser<License>::xmlElement()
{
    return QStringList(QLatin1String( "license" ));
}

template <>
QStringList XmlParser<Message>::xmlElement()
{
    return QStringList(QLatin1String( "message" ));
}

template <>
QStringList XmlParser<Person>::xmlElement()
{
    return QStringList(QLatin1String( "person" )) << QLatin1String( "user" );
}

template <>
QStringList XmlParser<PrivateData>::xmlElement()
{
    return QStringList(QLatin1String( "privatedata" ));
}

template <>
QStringList XmlParser<Project>::xmlElement()
{
    return QStringList(QLatin1String("project")) << QLatin1String("user");
}

template <>
QStringList XmlParser<PublisherField>::xmlElement()
{
    return QStringList(QLatin1String("field"));
}

template <>
QStringList XmlParser<Publisher>::xmlElement()
{
    return QStringList(QLatin1String("publisher")) << QLatin1String("user");
}

template <>
QStringList XmlParser<RemoteAccount>::xmlElement()
{
    return QStringList(QLatin1String("remoteaccount")) << QLatin1String("user");
}

template <>
QStringList XmlParser<Topic>::xmlElement()
{
    return QStringList(QLatin1String( "topic" ));
}

template <class T>
T XmlParser<T>::parseXml(QXmlStreamReader &xml)
{
    qWarning() << "Something went wrong here. It seems like you forgot to add a specialized"
                " function for XmlParser::parseXml.";
    return T();
}

template <>
AccountBalance XmlParser<AccountBalance>::parseXml(QXmlStreamReader& xml)
{
    AccountBalance item;

    while ( !xml.atEnd() ) {
        xml.readNext();
        if ( xml.isStartElement() ) {
            if ( xml.name() == QLatin1String("balance") ) {
                item.setBalance( xml.readElementText() );
            }
            if ( xml.name() == QLatin1String("currency") ) {
                item.setCurrency( xml.readElementText() );
            }
        }
    }
    return item;
}

template <>
Achievement XmlParser<Achievement>::parseXml(QXmlStreamReader &xml)
{
    Achievement achievement;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("id")) {
                achievement.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("content_id")) {
                achievement.setContentId(xml.readElementText());
            } else if (xml.name() == QLatin1String("name")) {
                achievement.setName(xml.readElementText());
            } else if (xml.name() == QLatin1String("description")) {
                achievement.setDescription(xml.readElementText());
            } else if (xml.name() == QLatin1String("explanation")) {
                achievement.setExplanation(xml.readElementText());
            } else if (xml.name() == QLatin1String("points")) {
                achievement.setPoints(xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("image")) {
                achievement.setImage(QUrl(xml.readElementText()));
            } else if (xml.name() == QLatin1String("dependencies")) {
                QStringList dependencies;
                while (!xml.atEnd()) {
                    xml.readNext();

                    if (xml.isStartElement()) {
                        if (xml.name() == QLatin1String("achievement_id"))
                            dependencies.append(xml.readElementText());
                    } else if (xml.isEndElement() && xml.name() == QLatin1String("dependencies")) {
                        break;
                    }
                }
                achievement.setDependencies(dependencies);
            } else if (xml.name() == QLatin1String("visibility")) {
                achievement.setVisibility(Achievement::stringToAchievementVisibility(xml.readElementText()));
            } else if (xml.name() == QLatin1String("type")) {
                achievement.setType(Achievement::stringToAchievementType(xml.readElementText()));
            } else if (xml.name() == QLatin1String("options")) {
                QStringList options;
                while (!xml.atEnd()) {
                    xml.readNext();

                    if (xml.isStartElement()) {
                        if (xml.name() == QLatin1String("option"))
                            options.append(xml.readElementText());
                    } else if (xml.isEndElement() && xml.name() == QLatin1String("options")) {
                        break;
                    }
                }
                achievement.setOptions(options);
            } else if (xml.name() == QLatin1String("steps")) {
                achievement.setSteps(xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("progress")) {
                switch(achievement.type()) {
                case Achievement::FlowingAchievement:
                    achievement.setProgress(QVariant(xml.readElementText().toFloat()));
                    break;
                case Achievement::SteppedAchievement:
                    achievement.setProgress(QVariant(xml.readElementText().toInt()));
                    break;
                case Achievement::NamedstepsAchievement:
                    achievement.setProgress(QVariant(xml.readElementText()));
                    break;
                case Achievement::SetAchievement:
                    {
                    QStringList progress;
                    while (!xml.atEnd()) {
                        xml.readNext();

                        if (xml.isStartElement()) {
                            if (xml.name() == QLatin1String("reached"))
                                progress.append(xml.readElementText());
                        } else if (xml.isEndElement() && xml.name() == QLatin1String("progress")) {
                            break;
                        }
                    }
                    achievement.setProgress(progress);
                    }
                    break;
                default:
                    break;
                }
            }
        } else if (xml.isEndElement() && xml.name() == QLatin1String("achievement")) {
            break;
        }
    }

    return achievement;
}

template <>
Activity XmlParser<Activity>::parseXml(QXmlStreamReader &xml)
{
    Activity activity;
    Person person;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("id")) {
                activity.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("personid")) {
                person.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("avatarpic")) {
                person.setAvatarUrl(xml.readElementText());
            } else if (xml.name() == QLatin1String("firstname")) {
                person.setFirstName(xml.readElementText());
            } else if (xml.name() == QLatin1String("lastname")) {
                person.setLastName(xml.readElementText());
            } else if (xml.name() == QLatin1String("timestamp")) {
                QString timestampString = xml.readElementText();
                timestampString.remove(QRegExp(QLatin1String("\\+.*$")));
                QDateTime timestamp = QDateTime::fromString(timestampString, Qt::ISODate);
                activity.setTimestamp(timestamp);
            } else if (xml.name() == QLatin1String("message")) {
                activity.setMessage(xml.readElementText());
            } else if (xml.name() == QLatin1String("link")) {
                activity.setLink(xml.readElementText());
            }
        } else if (xml.isEndElement() && xml.name() == QLatin1String("activity")) {
            break;
        }
    }

    activity.setAssociatedPerson(person);
    return activity;
}

template <>
BuildService XmlParser<BuildService>::parseXml(QXmlStreamReader &xml)
{
    // For specs about the XML provided, see here:
    // http://www.freedesktop.org/wiki/Specifications/open-collaboration-services-draft

    BuildService buildservice;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {

            if (xml.name() == QLatin1String("id")) {
                buildservice.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("name")) {
                buildservice.setName(xml.readElementText());
            } else if (xml.name() == QLatin1String("registrationurl")) {
                buildservice.setUrl(xml.readElementText());
            } else if (xml.name() == QLatin1String("supportedtargets")) {
                while (!xml.atEnd()) {
                    xml.readNextStartElement();
                    if (xml.isStartElement()) {
                        if (xml.name() == QLatin1String("target")) {
                            Target t;
                            while (!xml.atEnd()) {
                                xml.readNextStartElement();
                                if (xml.isStartElement()) {
                                    if (xml.name() == QLatin1String("id")) {
                                        t.id = xml.readElementText();
                                    } else if (xml.name() == QLatin1String("name")) {
                                        t.name = xml.readElementText();
                                    }
                                } else if (xml.isEndElement() && (xml.name() == QLatin1String("target"))) {
                                    xml.readNext();
                                    break;
                                }
                            }
                            buildservice.addTarget(t);
                        }
                    } else if (xml.isEndElement() && (xml.name() == QLatin1String("supportedtargets"))) {
                        xml.readNext();
                        break;
                    }
                }
            }
        } else if (xml.isEndElement()
               && ((xml.name() == QLatin1String("buildservice"))
               || (xml.name() == QLatin1String("user")))) {
            break;
        }
    }
    return buildservice;
}

template <>
BuildServiceJob XmlParser<BuildServiceJob>::parseXml(QXmlStreamReader &xml)
{
    BuildServiceJob buildservicejob;

    // For specs about the XML provided, see here:
    // http://www.freedesktop.org/wiki/Specifications/open-collaboration-services-draft#BuildServiceJobs
    while (!xml.atEnd()) {
        //qDebug() << "XML returned:" << xml.text().toString();
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("id")) { // FIXME: server should give "id" here ...
                buildservicejob.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("project")) {
                buildservicejob.setProjectId(xml.readElementText());
            } else if (xml.name() == QLatin1String("buildservice")) {
                buildservicejob.setBuildServiceId(xml.readElementText());
            } else if (xml.name() == QLatin1String("target")) {
                buildservicejob.setTarget(xml.readElementText());
            } else if (xml.name() == QLatin1String("name")) {
                buildservicejob.setName(xml.readElementText());
            } else if (xml.name() == QLatin1String("status")) {
                int status = xml.readElementText().toInt();
                buildservicejob.setStatus(status);
            } else if (xml.name() == QLatin1String("progress")) {
                qreal progress = (qreal)(xml.readElementText().toFloat());
                buildservicejob.setProgress(progress);
            } else if (xml.name() == QLatin1String("message")) {
                buildservicejob.setMessage(xml.readElementText());
            } else if (xml.name() == QLatin1String("url")) {
                buildservicejob.setUrl(xml.readElementText());
            }
        } else if (xml.isEndElement() && (xml.name() == QLatin1String("buildjob") || xml.name() == QLatin1String("user"))) {
            break;
        }
    }
    return buildservicejob;
}

template <>
BuildServiceJobOutput XmlParser<BuildServiceJobOutput>::parseXml(QXmlStreamReader &xml)
{
    BuildServiceJobOutput buildservicejoboutput;

    // For specs about the XML provided, see here:
    // http://www.freedesktop.org/wiki/Specifications/open-collaboration-services-draft#BuildServiceJobs
    while (!xml.atEnd()) {
        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("output")) {
                buildservicejoboutput.setOutput(xml.readElementText());
            }
        } else if (xml.isEndElement() && xml.name() == QLatin1String("output")) {
            break;
        }
        xml.readNext();
    }
    return buildservicejoboutput;
}

template <> Category
XmlParser<Category>::parseXml(QXmlStreamReader &xml)
{
    Category category;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("id")) {
                category.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("name")) {
                category.setName(xml.readElementText());
            }
        } else if (xml.isEndElement() && xml.name() == QLatin1String("category")) {
            break;
        }
    }

    return category;
}

template <>
Comment XmlParser<Comment>::parseXml(QXmlStreamReader &xml)
{
    Comment comment;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("id")) {
                comment.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("subject")) {
                comment.setSubject(xml.readElementText());
            } else if (xml.name() == QLatin1String("text")) {
                comment.setText(xml.readElementText());
            } else if (xml.name() == QLatin1String("childcount")) {
                comment.setChildCount(xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("user")) {
                comment.setUser(xml.readElementText());
            } else if (xml.name() == QLatin1String("date")) {
                comment.setDate(Utils::parseQtDateTimeIso8601(xml.readElementText()));
            } else if (xml.name() == QLatin1String("score")) {
                comment.setScore(xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("children")) {
                QList<Comment> children = parseXmlChildren(xml);
                comment.setChildren(children);
            }
        } else if (xml.isEndElement() && xml.name() == QLatin1String("comment")) {
            break;
        }
    }

    return comment;
}

template <>
Content XmlParser<Content>::parseXml(QXmlStreamReader &xml)
{
    Content content;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("id")) {
                content.setId( xml.readElementText());
            } else if (xml.name() == QLatin1String("name")) {
                content.setName( xml.readElementText());
            } else if (xml.name() == QLatin1String("score")) {
                content.setRating( xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("downloads")) {
                content.setDownloads( xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("comments")) {
                content.setNumberOfComments(xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("created")) {
                // Qt doesn't accept +-Timezone modifiers, truncate if the string contains them
                QString dateString = xml.readElementText().left(19);
                content.setCreated( QDateTime::fromString( dateString, Qt::ISODate));
            } else if (xml.name() == QLatin1String("changed")) {
                // Qt doesn't accept +-Timezone modifiers, truncate if the string contains them
                QString dateString = xml.readElementText().left(19);
                content.setUpdated( QDateTime::fromString( dateString, Qt::ISODate));
            } else if (xml.name() == QLatin1String("icon")) {
                Icon icon;
                icon.setUrl(QUrl(xml.readElementText()));
                QXmlStreamAttributes attributes = xml.attributes();
                if (attributes.hasAttribute(QLatin1String( "width" ))) {
                    icon.setWidth(attributes.value(QLatin1String( "width" )).toString().toInt());
                }
                if (attributes.hasAttribute(QLatin1String( "height" ))) {
                    icon.setHeight(attributes.value(QLatin1String( "height" )).toString().toInt());
                }
                // append the icon to the current list of icons
                QList<Icon> icons;
                icons = content.icons();
                icons.append(icon);
                content.setIcons(icons);
            } else if (xml.name() == QLatin1String("video")) {
                QUrl video(xml.readElementText());
                // append the video to the current list of videos
                QList<QUrl> videos;
                videos = content.videos();
                videos.append(video);
                content.setVideos(videos);
            } else {
                content.addAttribute(xml.name().toString(), xml.readElementText());
            }
        }

        if (xml.isEndElement() && xml.name() == QLatin1String("content")) {
            break;
        }
    }

    // in case the server only sets creation date, use that as updated also
    if (content.updated().isNull()) {
        content.setUpdated(content.created());
    }

    return content;
}

template <>
Distribution XmlParser<Distribution>::parseXml(QXmlStreamReader &xml)
{
    Distribution item;

    while ( !xml.atEnd() ) {
        xml.readNext();
        if ( xml.isStartElement() ) {
            if ( xml.name() == QLatin1String("id") ) {
                item.setId( xml.readElementText().toInt() );
            } else if ( xml.name() == QLatin1String("name") ) {
                item.setName( xml.readElementText() );
            }
        }
        if (xml.isEndElement() && xml.name() == QLatin1String("distribution")) {
            break;
        }
    }
    return item;
}

template <>
DownloadItem XmlParser<DownloadItem>::parseXml(QXmlStreamReader &xml)
{
    DownloadItem item;

    while ( !xml.atEnd() ) {
        xml.readNext();
        if ( xml.isStartElement() ) {
            if ( xml.name() == QLatin1String("downloadlink") ) {
                item.setUrl( xml.readElementText() );
            } else if ( xml.name() == QLatin1String("mimetype") ) {
                item.setMimeType( xml.readElementText() );
            } else if ( xml.name() == QLatin1String("packagename") ) {
                item.setPackageName( xml.readElementText() );
            } else if ( xml.name() == QLatin1String("packagerepository") ) {
                item.setPackageRepository( xml.readElementText() );
            } else if ( xml.name() == QLatin1String("gpgfingerprint") ) {
                item.setGpgFingerprint( xml.readElementText() );
            } else if ( xml.name() == QLatin1String("gpgsignature") ) {
                item.setGpgSignature( xml.readElementText() );
            } else if ( xml.name() == QLatin1String("downloadway") ) {
                item.setType( DownloadDescription::Type(xml.readElementText().toInt()) );
            }
        }
    }
    return item;
}

template <>
Event XmlParser<Event>::parseXml(QXmlStreamReader &xml)
{
    Event event;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("id")) {
                event.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("name")) {
                event.setName(xml.readElementText());
            } else if (xml.name() == QLatin1String("description")) {
                event.setDescription(xml.readElementText());
            } else if (xml.name() == QLatin1String("user")) {
                event.setUser(xml.readElementText());
            } else if (xml.name() == QLatin1String("startdate")) {
                QString date = xml.readElementText().remove(QRegExp(QLatin1String( "\\+.*$" )));
                event.setStartDate(QDate::fromString(date, Qt::ISODate));
            } else if (xml.name() == QLatin1String("enddate")) {
                QString date = xml.readElementText().remove(QRegExp(QLatin1String( "\\+.*$" )));
                event.setEndDate(QDate::fromString(date, Qt::ISODate));
            } else if (xml.name() == QLatin1String("latitude")) {
                event.setLatitude(xml.readElementText().toFloat());
            } else if (xml.name() == QLatin1String("longitude")) {
                event.setLongitude(xml.readElementText().toFloat());
            } else if (xml.name() == QLatin1String("homepage")) {
                event.setHomepage(xml.readElementText());
            } else if (xml.name() == QLatin1String("country")) {
                event.setCountry(xml.readElementText());
            } else if (xml.name() == QLatin1String("city")) {
                event.setCity(xml.readElementText());
            } else {
                event.addExtendedAttribute(xml.name().toString(), xml.readElementText());
            }
        } else if (xml.isEndElement() && xml.name() == QLatin1String("event")) {
            break;
        }
    }

    return event;
}

template <>
Folder XmlParser<Folder>::parseXml(QXmlStreamReader &xml)
{
    Folder folder;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("id")) {
                folder.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("name")) {
                folder.setName(xml.readElementText());
            } else if (xml.name() == QLatin1String("messagecount")) {
                folder.setMessageCount(xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("type")) {
                folder.setType(xml.readElementText());
            }
        } else if (xml.isEndElement() && xml.name() == QLatin1String("folder")) {
            break;
        }
    }

    return folder;
}

template <>
Forum XmlParser<Forum>::parseXml(QXmlStreamReader &xml)
{
    Forum forum;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("id")) {
                forum.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("name")) {
                forum.setName(xml.readElementText());
            } else if (xml.name() == QLatin1String("description")) {
                forum.setDescription(xml.readElementText());
            } else if (xml.name() == QLatin1String("date")) {
                forum.setDate(Utils::parseQtDateTimeIso8601(xml.readElementText()));
            } else if (xml.name() == QLatin1String("icon")) {
                forum.setIcon(QUrl(xml.readElementText()));
            } else if (xml.name() == QLatin1String("childcount")) {
                forum.setChildCount(xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("children")) {
                QList<Forum> children = parseXmlChildren(xml);
                forum.setChildren(children);
            } else if (xml.name() == QLatin1String("topics")) {
                forum.setTopics(xml.readElementText().toInt());
            }
        } else if (xml.isEndElement() && xml.name() == QLatin1String("forum")) {
            break;
        }
    }

    return forum;
}

template <>
HomePageType XmlParser<HomePageType>::parseXml(QXmlStreamReader &xml)
{
    HomePageType item;

    while ( !xml.atEnd() ) {
        xml.readNext();
        if ( xml.isStartElement() ) {
            if ( xml.name() == QLatin1String("id") ) {
                item.setId( xml.readElementText().toInt() );
            } else if ( xml.name() == QLatin1String("name") ) {
                item.setName( xml.readElementText() );
            }
        }
        if (xml.isEndElement() && xml.name() == QLatin1String("homepagetype")) {
            break;
        }
    }
    return item;
}

template <>
KnowledgeBaseEntry XmlParser<KnowledgeBaseEntry>::parseXml(QXmlStreamReader &xml)
{
    KnowledgeBaseEntry knowledgeBase;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("id")) {
                knowledgeBase.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("status")) {
                knowledgeBase.setStatus(xml.readElementText());
            } else if (xml.name() == QLatin1String("contentId")) {
                knowledgeBase.setContentId(xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("user")) {
                knowledgeBase.setUser(xml.readElementText());
            } else if (xml.name() == QLatin1String("changed")) {
                knowledgeBase.setChanged(QDateTime::fromString( xml.readElementText(), Qt::ISODate ));
            } else if (xml.name() == QLatin1String("description")) {
                knowledgeBase.setDescription(xml.readElementText());
            } else if (xml.name() == QLatin1String("answer")) {
                knowledgeBase.setAnswer(xml.readElementText());
            } else if (xml.name() == QLatin1String("comments")) {
                knowledgeBase.setComments(xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("detailpage")) {
                knowledgeBase.setDetailPage(QUrl(xml.readElementText()));
            } else if (xml.name() == QLatin1String("contentid")) {
                knowledgeBase.setContentId(xml.readElementText().toInt());
            } else if (xml.name() == QLatin1String("name")) {
                knowledgeBase.setName(xml.readElementText());
            } else {
                knowledgeBase.addExtendedAttribute(xml.name().toString(), xml.readElementText());
            }
        } else if (xml.isEndElement() && xml.name() == QLatin1String("content")) {
            break;
        }
    }

    return knowledgeBase;
}

template <>
License XmlParser<License>::parseXml(QXmlStreamReader &xml)
{
    License item;

    while ( !xml.atEnd() ) {
        xml.readNext();
        if ( xml.isStartElement() ) {
            if ( xml.name() == QLatin1String("id") ) {
                item.setId( xml.readElementText().toInt() );
            } else if ( xml.name() == QLatin1String("name") ) {
                item.setName( xml.readElementText() );
            } else if ( xml.name() == QLatin1String("link") ) {
                item.setUrl( xml.readElementText() );
            }
        }
        if (xml.isEndElement() && xml.name() == QLatin1String("license")) {
            break;
        }
    }
    return item;
}

template <>
Message XmlParser<Message>::parseXml(QXmlStreamReader &xml)
{
    Message message;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("id")) {
                message.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("messagefrom")) {
                message.setFrom(xml.readElementText());
            } else if (xml.name() == QLatin1String("messageto")) {
                message.setTo(xml.readElementText());
            } else if (xml.name() == QLatin1String("senddate")) {
                message.setSent(QDateTime::fromString(xml.readElementText(), Qt::ISODate));
            } else if (xml.name() == QLatin1String("status")) {
                message.setStatus(Message::Status(xml.readElementText().toInt()));
            } else if (xml.name() == QLatin1String("subject")) {
                message.setSubject(xml.readElementText());
            } else if (xml.name() == QLatin1String("body")) {
                message.setBody(xml.readElementText());
            }
        }

        if (xml.isEndElement() && xml.name() == QLatin1String("message")) {
            break;
        }
    }

    return message;
}

template <>
Person XmlParser<Person>::parseXml(QXmlStreamReader &xml)
{
    Person person;
    bool hasAvatarPic = false;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("personid")) {
                person.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("firstname")) {
                person.setFirstName(xml.readElementText());
            } else if (xml.name() == QLatin1String("lastname")) {
                person.setLastName(xml.readElementText());
            } else if (xml.name() == QLatin1String("homepage")) {
                person.setHomepage(xml.readElementText());
            } else if (xml.name() == QLatin1String("avatarpic")) {
                person.setAvatarUrl(xml.readElementText());
            } else if (xml.name() == QLatin1String("avatarpicfound")) {
                QString value = xml.readElementText();
                if (value.toInt()) {
                    hasAvatarPic = true;
                }
            } else if (xml.name() == QLatin1String("birthday")) {
                person.setBirthday(QDate::fromString(xml.readElementText(), Qt::ISODate));
            } else if (xml.name() == QLatin1String("city")) {
                person.setCity(xml.readElementText());
            } else if (xml.name() == QLatin1String("country")) {
                person.setCountry(xml.readElementText());
            } else if (xml.name() == QLatin1String("latitude")) {
                person.setLatitude(xml.readElementText().toFloat());
            } else if (xml.name() == QLatin1String("longitude")) {
                person.setLongitude(xml.readElementText().toFloat());
            } else {
                person.addExtendedAttribute(xml.name().toString(), xml.readElementText());
            }
        } else if (xml.isEndElement() && (xml.name() == QLatin1String("person") || xml.name() == QLatin1String("user"))) {
            break;
        }
    }

    if (!hasAvatarPic) {
        person.setAvatarUrl(QString());
    }

    return person;
}

template <>
PrivateData XmlParser<PrivateData>::parseXml(QXmlStreamReader &xml)
{
    PrivateData data;
    bool hasAvatarPic = false;
    QString key;

    // TODO: when we get internet and some documentation
    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("key")) {
                key = xml.readElementText();
            } else if (xml.name() == QLatin1String("value")) {
                data.setAttribute(key, xml.readElementText());
            } else if (xml.name() == QLatin1String("timestamp")) {
                data.setTimestamp(key, QDateTime::fromString(xml.readElementText(), Qt::ISODate));
            }
        } else if (xml.isEndElement() && (xml.name() == QLatin1String("data") || xml.name() == QLatin1String("user"))) {
            break;
        }
    }

    return data;
}

template <>
Project XmlParser<Project>::parseXml(QXmlStreamReader &xml)
{
    Project project;

    // For specs about the XML provided, see here:
    // http://www.freedesktop.org/wiki/Specifications/open-collaboration-services-draft#Projects
    while (!xml.atEnd()) {
        //qDebug() << "XML returned:" << xml.text().toString();
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("projectid")) {
                project.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("name")) {
                project.setName(xml.readElementText());
            } else if (xml.name() == QLatin1String("version")) {
                project.setVersion(xml.readElementText());
            } else if (xml.name() == QLatin1String("license")) {
                project.setLicense(xml.readElementText());
            } else if (xml.name() == QLatin1String("url")) {
                project.setUrl(xml.readElementText());
            } else if (xml.name() == QLatin1String("summary")) {
                project.setSummary(xml.readElementText());
            } else if (xml.name() == QLatin1String("description")) {
                project.setDescription(xml.readElementText());
            } else if (xml.name() == QLatin1String("specfile")) {
                project.setSpecFile(xml.readElementText());
            } else if (xml.name() == QLatin1String("developers")) {
                project.setDevelopers(xml.readElementText().split(QLatin1String("\n")));
            } else if (xml.name() == QLatin1String("projectlist")) {
                QXmlStreamReader list_xml(xml.readElementText());
                while (!list_xml.atEnd()) {
                    list_xml.readNext();
                    if (xml.name() == QLatin1String("projectid")) {
                        project.setSpecFile(xml.readElementText());
                    }
                }

            }
        } else if (xml.isEndElement() && (xml.name() == QLatin1String("project") || xml.name() == QLatin1String("user"))) {
            break;
        }
    }
    return project;
}

template <>
PublisherField XmlParser<PublisherField>::parseXml(QXmlStreamReader &xml)
{
    PublisherField fld;
    while (!xml.atEnd()) {
        xml.readNextStartElement();
        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("fieldtype")) {
                fld.setType(xml.readElementText());
            } else if (xml.name() == QLatin1String("name")) {
                fld.setName(xml.readElementText());
            } else if (xml.name() == QLatin1String("data")) {
                fld.setData(xml.readElementText());
            }
        } else if (xml.isEndElement() && (xml.name() == QLatin1String("field"))) {
            xml.readNext();
            break;
        }
    }
    return fld;
}

template <>
Publisher XmlParser<Publisher>::parseXml(QXmlStreamReader &xml)
{
    // For specs about the XML provided, see here:
    // http://www.freedesktop.org/wiki/Specifications/open-collaboration-services-draft

    Publisher publisher;
    QStringList fields;

    while (!xml.atEnd()) {
        //qDebug() << "XML returned:" << xml.text().toString();
        xml.readNext();

        if (xml.isStartElement()) {

            if (xml.name() == QLatin1String("id")) {
                publisher.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("name")) {
                publisher.setName(xml.readElementText());
            } else if (xml.name() == QLatin1String("registrationurl")) {
                publisher.setUrl(xml.readElementText());
            } else if (xml.name() == QLatin1String("fields")) {
                while (!xml.atEnd()) {
                    xml.readNextStartElement();
                    if (xml.isStartElement()) {
                        if (xml.name() == QLatin1String("field")) {
                            Field t;
                            while (!xml.atEnd()) {
                                xml.readNextStartElement();
                                if (xml.isStartElement()) {
                                    if (xml.name() == QLatin1String("fieldtype")) {
                                        t.type = xml.readElementText();
                                    } else if (xml.name() == QLatin1String("name")) {
                                        t.name = xml.readElementText();
                                    } else if (xml.name() == QLatin1String("fieldsize")) {
                                        t.fieldsize = xml.readElementText().toInt();
                                    } else if (xml.name() == QLatin1String("required")) {
                                        t.required = xml.readElementText() == QLatin1String("true");
                                    } else if (xml.name() == QLatin1String("options")) {
                                        while (!xml.atEnd())
                                        {
                                            xml.readNextStartElement();
                                            if(xml.isStartElement())
                                            {
                                                if(xml.name() == QLatin1String("option"))
                                                {
                                                    t.options << xml.readElementText();
                                                }
                                            } else if (xml.isEndElement() && xml.name() == QLatin1String("options")) {
                                                xml.readNext();
                                                break;
                                            }
                                        }
                                    }
                                } else if (xml.isEndElement() && (xml.name() == QLatin1String("field"))) {
                                    xml.readNext();
                                    break;
                                }
                            }
                            publisher.addField(t);
                        }
                    } else if (xml.isEndElement() && (xml.name() == QLatin1String("fields"))) {
                        xml.readNext();
                        break;
                    }
                }
            } else if (xml.name() == QLatin1String("supportedtargets")) {
                while (!xml.atEnd()) {
                    xml.readNextStartElement();
                    if (xml.isStartElement()) {
                        if (xml.name() == QLatin1String("target")) {
                            Target t;
                            t.name = xml.readElementText();
                            publisher.addTarget(t);
                        }
                    } else if (xml.isEndElement() && (xml.name() == QLatin1String("supportedtargets"))) {
                        xml.readNext();
                        break;
                    }
                }
            }
        } else if (xml.isEndElement()
               && ((xml.name() == QLatin1String("publisher"))
               || (xml.name() == QLatin1String("user")))) {
            break;
        }
    }
    return publisher;
}

template <>
RemoteAccount XmlParser<RemoteAccount>::parseXml(QXmlStreamReader &xml)
{
    RemoteAccount remoteaccount;

    // For specs about the XML provided, see here:
    // http://www.freedesktop.org/wiki/Specifications/open-collaboration-services-draft#RemoteAccounts
    while (!xml.atEnd()) {
        //qDebug() << "XML returned:" << xml.text().toString();
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("id")) {
                remoteaccount.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("type")) {
                remoteaccount.setType(xml.readElementText());
            } else if (xml.name() == QLatin1String("typeid")) {  // FIXME: change to remoteserviceid sometime soon (OCS API change pending
                remoteaccount.setRemoteServiceId(xml.readElementText());
            } else if (xml.name() == QLatin1String("data")) {
                remoteaccount.setData(xml.readElementText());
            } else if (xml.name() == QLatin1String("login")) {
                remoteaccount.setLogin(xml.readElementText());
            } else if (xml.name() == QLatin1String("password")) {
                remoteaccount.setPassword(xml.readElementText());
            }
        } else if (xml.isEndElement() && (xml.name() == QLatin1String("remoteaccount") || xml.name() == QLatin1String("user"))) {
            break;
        }
    }
    return remoteaccount;
}

template <>
Topic XmlParser<Topic>::parseXml(QXmlStreamReader &xml)
{
    Topic topic;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("id")) {
                topic.setId(xml.readElementText());
            } else if (xml.name() == QLatin1String("forumId")) {
                topic.setForumId(xml.readElementText());
            } else if (xml.name() == QLatin1String("user")) {
                topic.setUser(xml.readElementText());
            } else if (xml.name() == QLatin1String("date")) {
                topic.setDate(Utils::parseQtDateTimeIso8601(xml.readElementText()));
            } else if (xml.name() == QLatin1String("subject")) {
                topic.setSubject(xml.readElementText());
            } else if (xml.name() == QLatin1String("content")) {
                topic.setContent(xml.readElementText());
            } else if (xml.name() == QLatin1String("comments")) {
                topic.setComments(xml.readElementText().toInt());
            }
        } else if (xml.isEndElement() && xml.name() == QLatin1String("topic")) {
            break;
        }
    }

    return topic;
}
