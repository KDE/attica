/*
    This file is part of KDE.

    SPDX-FileCopyrightText: 2009 Frederik Gladhorn <gladhorn@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#include "downloaddescription.h"

#include <QStringList>

namespace Attica
{
class DownloadDescription::Private : public QSharedData
{
public:
    int id = 0;
    Attica::DownloadDescription::Type type = Attica::DownloadDescription::FileDownload;
    bool hasPrice = false;
    QString category;
    QString name;
    QString link;
    QString distributionType;
    QString priceReason;
    QString priceAmount;
    QString gpgFingerprint;
    QString gpgSignature;
    QString packageName;
    QString repository;
    uint size = 0;
    QStringList tags;
};
}

using namespace Attica;

DownloadDescription::DownloadDescription()
    : d(new Private)
{
}

DownloadDescription::DownloadDescription(const Attica::DownloadDescription &other)
    : d(other.d)
{
}

DownloadDescription &DownloadDescription::operator=(const Attica::DownloadDescription &other)
{
    d = other.d;
    return *this;
}

DownloadDescription::~DownloadDescription()
{
}

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
QString Attica::DownloadDescription::category()
{
    return d->category;
}
#endif

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
int DownloadDescription::id()
{
    return d->id;
}
#endif

QString Attica::DownloadDescription::category() const
{
    return d->category;
}

int DownloadDescription::id() const
{
    return d->id;
}

void DownloadDescription::setId(int id)
{
    d->id = id;
}

void DownloadDescription::setCategory(const QString &category)
{
    d->category = category;
}

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
QString Attica::DownloadDescription::distributionType()
{
    return d->distributionType;
}
#endif

QString Attica::DownloadDescription::distributionType() const
{
    return d->distributionType;
}

void DownloadDescription::setDistributionType(const QString &distributionType)
{
    d->distributionType = distributionType;
}

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
bool Attica::DownloadDescription::hasPrice()
{
    return d->hasPrice;
}
#endif

bool Attica::DownloadDescription::hasPrice() const
{
    return d->hasPrice;
}

void DownloadDescription::setHasPrice(bool hasPrice)
{
    d->hasPrice = hasPrice;
}

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
Attica::DownloadDescription::Type DownloadDescription::type()
{
    return d->type;
}
#endif

Attica::DownloadDescription::Type DownloadDescription::type() const
{
    return d->type;
}

void DownloadDescription::setType(Attica::DownloadDescription::Type type)
{
    d->type = type;
}

#if ATTICA_BUILD_DEPRECATED_SINCE(0, 2)
bool Attica::DownloadDescription::isDownloadtypLink()
{
    return d->type == Attica::DownloadDescription::LinkDownload;
}
#endif

#if ATTICA_BUILD_DEPRECATED_SINCE(0, 2)
void DownloadDescription::setDownloadtypLink(bool isLink)
{
    if (isLink) {
        d->type = Attica::DownloadDescription::LinkDownload;
    } else {
        d->type = Attica::DownloadDescription::FileDownload;
    }
}
#endif

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
QString Attica::DownloadDescription::link()
{
    return d->link;
}
#endif

QString Attica::DownloadDescription::link() const
{
    return d->link;
}

void DownloadDescription::setLink(const QString &link)
{
    d->link = link;
}

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
QString Attica::DownloadDescription::name()
{
    return d->name;
}
#endif

QString Attica::DownloadDescription::name() const
{
    return d->name;
}

void DownloadDescription::setName(const QString &name)
{
    d->name = name;
}

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
QString Attica::DownloadDescription::priceAmount()
{
    return d->priceAmount;
}
#endif

QString Attica::DownloadDescription::priceAmount() const
{
    return d->priceAmount;
}

void DownloadDescription::setPriceAmount(const QString &priceAmount)
{
    d->priceAmount = priceAmount;
}

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
QString Attica::DownloadDescription::priceReason()
{
    return d->priceReason;
}
#endif

QString Attica::DownloadDescription::priceReason() const
{
    return d->priceReason;
}

void Attica::DownloadDescription::setPriceReason(const QString &priceReason)
{
    d->priceReason = priceReason;
}

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
uint Attica::DownloadDescription::size()
{
    return d->size;
}
#endif

uint Attica::DownloadDescription::size() const
{
    return d->size;
}

void Attica::DownloadDescription::setSize(uint size)
{
    d->size = size;
}

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
QString Attica::DownloadDescription::gpgFingerprint()
{
    return d->gpgFingerprint;
}
#endif

QString Attica::DownloadDescription::gpgFingerprint() const
{
    return d->gpgFingerprint;
}

void Attica::DownloadDescription::setGpgFingerprint(const QString &fingerprint)
{
    d->gpgFingerprint = fingerprint;
}

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
QString Attica::DownloadDescription::gpgSignature()
{
    return d->gpgSignature;
}
#endif

QString Attica::DownloadDescription::gpgSignature() const
{
    return d->gpgSignature;
}

void Attica::DownloadDescription::setGpgSignature(const QString &signature)
{
    d->gpgSignature = signature;
}

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
QString Attica::DownloadDescription::packageName()
{
    return d->packageName;
}
#endif

QString Attica::DownloadDescription::packageName() const
{
    return d->packageName;
}

void Attica::DownloadDescription::setPackageName(const QString &packageName)
{
    d->packageName = packageName;
}

#if ATTICA_BUILD_DEPRECATED_SINCE(5, 4)
QString Attica::DownloadDescription::repository()
{
    return d->repository;
}
#endif

QString Attica::DownloadDescription::repository() const
{
    return d->repository;
}

void Attica::DownloadDescription::setRepository(const QString &repository)
{
    d->repository = repository;
}

QStringList Attica::DownloadDescription::tags() const
{
    return d->tags;
}

void Attica::DownloadDescription::setTags(const QStringList &tags)
{
    d->tags = tags;
}
