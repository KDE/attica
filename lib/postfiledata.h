/*
    This file is part of KDE.

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

#ifndef POSTFILEDATA_H
#define POSTFILEDATA_H

#include <QtCore/QByteArray>
#include <QtNetwork/QNetworkRequest>

namespace Attica {
    class PostFileDataPrivate;

class PostFileData
{
    public:
        /**
         * Prepare a QNetworkRequest and QByteArray for sending a HTTP POST.
         * Parameters and files can be added with addArgument() and addFile()
         * Do not add anything after calling request or data for the first time.
         */
        PostFileData(const QUrl& url);
        ~PostFileData();
        
        void addArgument(const QString& key, const QString& value);
        void addFile(const QString& fileName, QIODevice* file, const QString& mimeType);
        void addFile(const QString& fileName, const QByteArray& file, const QString& mimeType);
        
        QNetworkRequest request();
        QByteArray data();
        
    private:
        void finish();
        QString randomString(int length);
        PostFileDataPrivate* d;
        Q_DISABLE_COPY(PostFileData)
};

}

#endif // POSTFILEDATA_H
