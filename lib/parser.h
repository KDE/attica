/*
    This file is part of KDE.

    Copyright (c) 2009 Eckhart Wörner <ewoerner@kde.org>

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

#ifndef ATTICA_PARSER_H
#define ATTICA_PARSER_H

#include <QtCore/QStringList>
// WARNING: QXmlStreamReader cannot be forward declared (Qt 4.5)
#include <QtXml/QXmlStreamReader>

#include "listjob.h"


namespace Attica {

template <class T>
class Parser {
public:
    T parse(const QString& xml);
    typename T::List parseList(const QString& xml);
    ListJobMetadata metadata() const;
    virtual ~Parser();

protected:
    virtual QStringList xmlElement() const = 0;
    virtual T parseXml(QXmlStreamReader& xml) = 0;

private:
    void parseMetadataXml(QXmlStreamReader& xml);
    ListJobMetadata m_metadata;
};

}


#endif
