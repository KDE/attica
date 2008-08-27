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
#ifndef PERSONPLATE_H
#define PERSONPLATE_H

#include "person.h"

#include <kabc/addressee.h>

#include <QtGui>

class KJob;

class PersonPlate : public QFrame
{
    Q_OBJECT
  public:
    PersonPlate();

    void setLabel( const QString & );

    void setPerson( const Attica::Person & );
    void setAddressee( const KABC::Addressee & );

  protected slots:
    void slotJobResult( KJob *job );

  private:
    QLabel *m_picLabel;
    QLabel *m_label;

    Attica::Person m_person;
};

#endif
