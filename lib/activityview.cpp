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

#include "activityview.h"

#include "activitylistjob.h"

ActivityView::ActivityView()
{
  QBoxLayout *topLayout = new QVBoxLayout( this );

  m_view = new QLabel;
  topLayout->addWidget( m_view );

  Attica::ActivityListJob *job = Attica::Activity::request();
  connect( job, SIGNAL( result( KJob * ) ), SLOT( slotResult( KJob * ) ) );

  m_view->setText( "Loading..." );
}

void ActivityView::slotResult( KJob *j )
{
  QString text;

  if ( j->error() ) {
    text += "Error:" + j->errorText();
  } else {
    text = "<qt>";

    Attica::ActivityListJob *job = static_cast<Attica::ActivityListJob *>( j );
    foreach( Attica::Activity activity, job->ActivityList() ) {
      text += "<b>" + activity.user() + "</b>";
      text += " (" + activity.timestamp().toString() + "):";
      text += "<br/>";
      text += activity.message();
      text += "<br/><br/>";
    }

    text += "</qt>";

  }

  m_view->setText( text );  
}
