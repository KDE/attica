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

#include "personplate.h"

#include "personjob.h"

#include "kstandarddirs.h"

PersonPlate::PersonPlate()
{
  setFrameStyle( Panel | Raised );

  QBoxLayout *topLayout = new QHBoxLayout( this );
  
  m_picLabel = new QLabel;
  topLayout->addWidget( m_picLabel );
  QString picPath = KStandardDirs::locate( "appdata", "attica_person.png" );
  m_picLabel->setPixmap( QPixmap( picPath ) );
  
  m_label = new QLabel();
  m_label->setAlignment( Qt::AlignCenter );
  topLayout->addWidget( m_label, 1 );
}

void PersonPlate::setLabel( const QString &label )
{
  m_label->setText( label );
}

void PersonPlate::slotJobResult( KJob *j )
{
  Attica::PersonJob *job = static_cast<Attica::PersonJob *>( j );

  if ( job->error() ) {
    qDebug() << "Error";
  } else {
    setPerson( job->person() );
  }
}

void PersonPlate::setPerson( const Attica::Person &person )
{
  m_person = person;

  if ( !m_person.avatar().isNull() ) {
    m_picLabel->setPixmap( m_person.avatar() );
  }

  QString label = m_person.firstName() + " " + m_person.lastName();
  if ( !m_person.city().isEmpty() ) label += "\n" + m_person.city();
  if ( !m_person.homepage().isEmpty() ) label += "\n" + m_person.homepage();

  setLabel( label );
}

void PersonPlate::setAddressee( const KABC::Addressee &addressee )
{
  qDebug() << addressee.uid();

  QString label = addressee.realName();
  if ( !addressee.preferredEmail().isEmpty() ) {
    label += "\n" + addressee.preferredEmail();
  }
  
  setLabel( label );
}
