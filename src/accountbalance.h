/*
    SPDX-FileCopyrightText: 2009 Frederik Gladhorn <gladhorn@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef ATTICA_ACCOUNTBALANCE_H
#define ATTICA_ACCOUNTBALANCE_H

#include <QSharedDataPointer>
#include <QString>

#include "attica_export.h"

namespace Attica
{
/*!
 * \class Attica::AccountBalance
 * \inheaderfile Attica/AccountBalance
 * \inmodule Attica
 *
 * \brief Represents the money in the account of the user.
 */
class ATTICA_EXPORT AccountBalance
{
public:
    /*!
     *
     */
    typedef QList<AccountBalance> List;
    class Parser;

    /*!
     * Creates an empty AccountBalance
     */
    AccountBalance();

    AccountBalance(const AccountBalance &other);

    AccountBalance &operator=(const AccountBalance &other);

    ~AccountBalance();

    /*!
     * Sets the currency in use.
     *
     * \a currency the new currency (Euro, US Dollar)
     */
    void setCurrency(const QString &currency);

    /*!
     * Returns the currency.
     */
    QString currency() const;

    /*!
     * Sets the balance.
     *
     * \a balance
     */
    void setBalance(const QString &name);

    /*!
     * Returns the amount of money in the account
     */
    QString balance() const;

private:
    class Private;
    QSharedDataPointer<Private> d;
};

}

#endif // ACCOUNTBALANCE_H
