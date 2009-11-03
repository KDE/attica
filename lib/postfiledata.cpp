/*
    This file is part of KDE.
    
    Copyright (c) 1999 Matthias Kalle Dalheimer <kalle@kde.org>
    Copyright (c) 2000 Charles Samuels <charles@kde.org>
    Copyright (c) 2005 Joseph Wenninger <kde@jowenn.at>
    Copyright (c) 2009 Frederik Gladhorn <gladhorn@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
    USA.
*/


#include "postfiledata.h"

#include <QDebug>
#include <QDateTime>

namespace Attica {
class PostFileDataPrivate {
    public:
        QByteArray buffer;
        QByteArray boundary;
        QUrl url;
        bool finished;
        
        PostFileDataPrivate()
            :finished(false)
        {
        }
};

PostFileData::PostFileData(const QUrl& url)
    :d(new PostFileDataPrivate)
{
    d->url = url;
    qsrand(QTime::currentTime().secsTo(QTime(0,0,0)));
    d->boundary = "----------" + randomString(42 + 13).toAscii();
}

PostFileData::~PostFileData()
{
    delete d;
}

QString PostFileData::randomString(int length)
{
   if (length <=0 ) return QString();

   QString str; str.resize( length );
   int i = 0;
   while (length--)
   {
      int r=qrand() % 62;
      r+=48;
      if (r>57) r+=7;
      if (r>90) r+=6;
      str[i++] =  char(r);
   }
   return str;
}
   
void PostFileData::addArgument(const QString& key, const QString& value)
{
    if (d->finished) {
        qDebug() << "PostFileData::addFile: should not add data after calling request() or data()";
    }
    QByteArray data(
        "--" + d->boundary + "\r\n"
        "Content-Disposition: form-data; name=\"" + key.toAscii() +
        "\"\r\n\r\n" + value.toUtf8() + "\r\n");
    
    d->buffer.append(data);
}

/*
void PostFileData::addFile(const QString& fileName, QIODevice* file, const QString& mimeType)
{
    if (d->finished) {
        qDebug() << "PostFileData::addFile: should not add data after calling request() or data()";
    }
    QByteArray data = file->readAll();
    addFile(fileName, data, mimeType);
}
*/

void PostFileData::addFile(const QString& fileName, const QByteArray& file, const QString& mimeType)
{
    if (d->finished) {
        qDebug() << "PostFileData::addFile: should not add data after calling request() or data()";
    }
    
    QByteArray data(
        "--" + d->boundary + "\r\n"
        "Content-Disposition: form-data; name=\"localfile\"; filename=\"" + fileName.toUtf8()
        + "\"\r\nContent-Type: " + mimeType.toAscii() + "\r\n\r\n");

    d->buffer.append(data);
    d->buffer.append(file + QByteArray("\r\n"));
}

QNetworkRequest PostFileData::request()
{
    if (!d->finished) {
        finish();
    }
    QNetworkRequest request;
    request.setUrl(d->url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=" + d->boundary);
    request.setHeader(QNetworkRequest::ContentLengthHeader, d->buffer.length());
    return request;
}

QByteArray PostFileData::data()
{
    if (!d->finished) {
        finish();
    }
    return d->buffer;
}

void PostFileData::finish()
{
    Q_ASSERT(!d->finished);
    d->finished = true;
    d->buffer.append("--" + d->boundary + "--");
}

}
