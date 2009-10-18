/*
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

#include "postjobstatusparser.h"

#include <QtXml/QXmlStreamReader>

using namespace Attica;

PostJobStatus::Parser::Parser()
{

}


PostJobStatus PostJobStatus::Parser::parse(const QString& xmlString)
{
    QXmlStreamReader xml( xmlString );
    PostJobStatus item;
    item.setData(xmlString);

    while ( !xml.atEnd() ) {
        xml.readNext();
        
        if ( xml.isStartElement() && xml.name() == "meta" ) {
            while ( !xml.atEnd() ) {
                xml.readNext();
                
                if ( xml.isStartElement() ) {
                    if ( xml.name() == "status" ) {
                        item.setStatus(xml.readElementText());
                    } else if ( xml.name() == "message" ) {
                        item.setStatusMessage(xml.readElementText());
                    } else if ( xml.name() == "statuscode" ) {
                        item.setStatusCode(xml.readElementText().toInt());
                    }
                }
                if ( xml.isEndElement() && xml.name() == "meta" ) break;
            }
        }
    }
    return item;
}


