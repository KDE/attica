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

#include "detailsview.h"

#include "personplate.h"

#include <klocale.h>

DetailsView::DetailsView()
{
  QBoxLayout *topLayout = new QVBoxLayout( this );
  
  QBoxLayout *controlLayout = new QHBoxLayout;
  topLayout->addLayout( controlLayout );
  
  m_plate = new PersonPlate;
  m_plate->enableDetails( false );
  controlLayout->addWidget( m_plate );
  
  controlLayout->addStretch( 1 );
  
  QPushButton *button = new QPushButton( i18n("Close") );
  controlLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( close() ) );

  m_view = new QLabel();
  m_view->setAlignment( Qt::AlignCenter );
  topLayout->addWidget( m_view );
}

void DetailsView::showPerson( const Attica::Person &person )
{
  m_plate->setPerson( person );
  
  QString text;
  
  text += i18n("User Id: %1").arg( person.user() );
  text += "\n" + person.firstName() + " " + person.lastName();

  if ( person.birthday().isValid() ) {
    text += "\nBirthday: " + person.birthday().toString();
  }
  
  if ( !person.country().isEmpty() ) {
    text += "\n" + person.country();
  }
  
  if ( !person.city().isEmpty() ) {
    text += "\n" + person.city();
  }
  
  if ( person.latitude() != 0 && person.longitude() != 0 ) {
    text += "\nLatitude: " + QString::number( person.latitude() ) +
      " Longitude: " + QString::number( person.longitude() );
  }
  
  if ( !person.homepage().isEmpty() ) {
    text += "\n" + person.homepage();
  }
  
  QMap<QString,QString> extendedAttributes = person.extendedAttributes();
  foreach( QString key, extendedAttributes.keys() ) {
    QString value = extendedAttributes.value( key );
    if ( !value.isEmpty() ) {
      text += "\n" + key + ": " + value;
    }
  }
  
  m_view->setText( text );
}
