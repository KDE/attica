/*
    This file is part of KDE.

    Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>

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

#include "postjob.h"

#include <klocale.h>

#include <QXmlStreamReader>
#include <QDebug>

#include <QtNetwork/QNetworkAccessManager>

using namespace Attica;


PostJob::PostJob(QNetworkAccessManager* nam, const QNetworkRequest& request, QIODevice* iodevice)
    : BaseJob(nam), m_ioDevice(iodevice), m_request(request)
{
}


PostJob::PostJob(QNetworkAccessManager* nam, const QNetworkRequest& request, const StringMap& parameters)
    : BaseJob(nam), m_ioDevice(0), m_request(request)
{
    // Create post data
    int j = 0;
    for(StringMap::const_iterator i = parameters.begin(); i != parameters.end(); ++i) {
        if (j++ > 0) {
            m_byteArray.append('&');
        }
        m_byteArray.append(QUrl::toPercentEncoding(i.key()));
        m_byteArray.append('=');
        m_byteArray.append(QUrl::toPercentEncoding(i.value()));
    }
}

QNetworkReply* PostJob::executeRequest()
{
    if (m_ioDevice) {
        return nam()->post(m_request, m_ioDevice);
    } else {
        return nam()->post(m_request, m_byteArray);
    }
}


/*QString PostJob::status() const
{
  return m_status;
}

QString PostJob::statusMessage() const
{
  return m_statusMessage;
}*/

/*void PostJob::slotJobResult( KJob *job )
{
  m_job = 0;

  qDebug() << "RESPONSE" << m_responseData;

  if ( job->error() ) {
    setError( job->error() );
    setErrorText( job->errorText() );
  } else {
    qDebug() << "No error ";
    
    QXmlStreamReader xml( m_responseData );
    
    while ( !xml.atEnd() ) {
      xml.readNext();
      
      if ( xml.isStartElement() && xml.name() == "meta" ) {
        while ( !xml.atEnd() ) {
          xml.readNext();
         
          if ( xml.isStartElement() ) {
            if ( xml.name() == "status" ) {
              m_status = xml.readElementText();
            } else if ( xml.name() == "message" ) {
              m_statusMessage = xml.readElementText();
            }
          }
          
          if ( xml.isEndElement() && xml.name() == "meta" ) break;
        }
      }
    }
    
    qDebug() << "STATUS:" << m_status;
    
    if ( m_status != "ok" ) {
      setError( KJob::UserDefinedError );
      setErrorText( m_status + ": " + m_statusMessage );
    }
  }
  
  emitResult();
}

void PostJob::slotJobData( KIO::Job *, const QByteArray &data )
{
  m_responseData.append( QString::fromUtf8( data.data(), data.size() + 1 ) );
}*/


void PostJob::parse(const QString& )
{
}


#include "postjob.moc"
