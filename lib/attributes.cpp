/*
    This file is part of KDE.

    Copyright (c) Martin Sandsmark <martin.sandsmark@kde.org>

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

#include <QStringList>

#include "attributes.h"


using namespace Attica;

class Attributes::Private : public QSharedData {
    public:
        QMap<QString, QString> m_attributes;
        QMap<QString, QDateTime> m_attributesChanged;

        Provider *m_provider;

        bool m_autoSync;

        MergeType m_mergeType;

        Private()
            : m_provider(0), m_autoSync(false), m_mergeType(Attributes::Ask)
        {
        }
};


Attributes::Attributes()
  : d(new Private)
{
}

Attributes::Attributes(const Attributes& other)
    : d(other.d)
{
}

Attributes& Attributes::operator=(const Attica::Attributes & other)
{
    d = other.d;
    return *this;
}

Attributes::~Attributes()
{
}


void Attributes::setAttribute(const QString &key, const QString &value)
{
    d->m_attributes[key] = value;
    d->m_attributesChanged[key] = QDateTime::currentDateTime();

    if (d->m_autoSync) {
        d->m_provider->setAttributes(QStringList(key), QStringList(value));
    }
}

QString Attributes::attribute(const QString &key) const
{
    return d->m_attributes[key];
}

QDateTime Attributes::attributeChanged(const QString &key) const
{
    return d->m_attributesChanged[key];
}

void Attributes::setAttributeChanged(const QString &key, const QDateTime &when)
{
    d->m_attributesChanged[key] = when;
}

void Attributes::setAutoSync(bool val)
{
    d->m_autoSync = val;
}

bool Attributes::autoSync() const
{
    return d->m_autoSync;
}

void Attributes::setMergeType(MergeType type)
{
    d->m_mergeType = type;
}

Attributes::MergeType Attributes::mergeType()
{
    return d->m_mergeType;
}

