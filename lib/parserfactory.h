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

#ifndef ATTICA_PARSERFACTORY_H
#define ATTICA_PARSERFACTORY_H

#include "parser.h"
#include "statusparser.h"

// XML parsers
#include "accountbalancexmlparser.h"
#include "achievementxmlparser.h"
#include "activityxmlparser.h"
#include "buildservicejoboutputxmlparser.h"
#include "buildservicejobxmlparser.h"
#include "buildservicexmlparser.h"
#include "categoryxmlparser.h"
#include "commentxmlparser.h"
#include "contentxmlparser.h"
#include "distributionxmlparser.h"
#include "downloaditemxmlparser.h"
#include "eventxmlparser.h"
#include "folderxmlparser.h"
#include "forumxmlparser.h"
#include "homepagetypexmlparser.h"
#include "knowledgebaseentryxmlparser.h"
#include "licensexmlparser.h"
#include "messagexmlparser.h"
#include "personxmlparser.h"
#include "privatedataxmlparser.h"
#include "projectxmlparser.h"
#include "publisherfieldxmlparser.h"
#include "publisherxmlparser.h"
#include "remoteaccountxmlparser.h"
#include "topicxmlparser.h"

namespace Attica
{

class ParserFactory
{
public:
    enum ParserType { Xml, Json };
    static ParserFactory* self();

    template<class T>
    Parser<T>* getParser();
    StatusParser* getStatusParser();

    ParserType getParserType();
    void setParserType( ParserType type );

private:
    ParserFactory();

    static ParserFactory* instance;
    class Private;
    Private* d;
};

template<class T>
Parser<T>* ParserFactory::getParser()
{
    switch( getParserType() )
    {
        case Xml:
            return new typename T::XmlParser();
            break;
        case Json:
            return 0;
            break;
    }
}

}

#endif
