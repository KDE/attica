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

namespace Attica
{

class ParserFactory
{
public:
    enum ParserType { Xml, Json };
    static ParserFactory* self();

    template<class T>
    typename T::Parser* getParser();

    ParserType getParserType();
    void setParserType( ParserType type );

private:
    ParserFactory();

    static ParserFactory* instance;
    class Private;
    Private* d;
};

template<class T>
typename T::Parser* ParserFactory::getParser()
{
    switch( getParserType() )
    {
        case Xml:
            return new typename T::/*Xml*/Parser();
            break;
        case Json:
            return 0;
            break;
    }
}

}

#endif
