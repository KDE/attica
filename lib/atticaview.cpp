/*
 * atticaview.cpp
 *
 * Copyright (C) 2008 Cornelius Schumacher <schumacher@kde.org>
 */

#include "atticaview.h"

#include "settings.h"
#include "personplate.h"
#include "personjob.h"
#include "personlistjob.h"
#include "person.h"
#include "peopleview.h"
#include "activityview.h"

#include <klocale.h>
#include <kabc/stdaddressbook.h>

#include <QtGui/QLabel>
#include <QtGui>

AtticaView::AtticaView(QWidget *)
{
  settingsChanged();
  setAutoFillBackground(true);

  QBoxLayout *topLayout = new QVBoxLayout( this );

  QBoxLayout *navigationLayout = new QHBoxLayout;
  topLayout->addLayout( navigationLayout );

  navigationLayout->addStretch( 1 );

  QPushButton *button = new QPushButton( i18n("Show My Activities") );
  navigationLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( showActivities() ) );


  QTabWidget *tabWidget = new QTabWidget;
  topLayout->addWidget( tabWidget );
  

  QWidget *searchPage = new QWidget;
  tabWidget->addTab( searchPage, i18n("Search") );

  QBoxLayout *searchLayout = new QHBoxLayout( searchPage );
  
  m_searchEdit = new QLineEdit;
  searchLayout->addWidget( m_searchEdit );
  connect( m_searchEdit, SIGNAL( returnPressed() ), SLOT( searchName() ) );
  
  QPushButton *searchButton = new QPushButton( i18n("Search") );
  searchLayout->addWidget( searchButton );
  connect( searchButton, SIGNAL( clicked() ), SLOT( searchName() ) );
  

  QWidget *idPage = new QWidget;
  tabWidget->addTab( idPage, i18n("Id") );

  QBoxLayout *addLayout = new QHBoxLayout( idPage );

  m_addEdit = new QLineEdit;
  addLayout->addWidget( m_addEdit );
  connect( m_addEdit, SIGNAL( returnPressed() ), SLOT( addPerson() ) );
  
  QPushButton *addButton = new QPushButton( i18n("Add Person") );
  addLayout->addWidget( addButton );
  connect( addButton, SIGNAL( clicked() ), SLOT( addPerson() ) );


  QWidget *locationPage = new QWidget;
  tabWidget->addTab( locationPage, i18n("Location") );

  QBoxLayout *locationLayout = new QHBoxLayout( locationPage );

  QLabel *label = new QLabel( i18n("Latitude") );
  locationLayout->addWidget( label );
  
  m_latitudeEdit = new QLineEdit;
  locationLayout->addWidget( m_latitudeEdit );
  connect( m_latitudeEdit, SIGNAL( returnPressed() ),
    SLOT( searchLocation() ) );
  
  label = new QLabel( i18n("Longitude") );
  locationLayout->addWidget( label );
  
  m_longitudeEdit = new QLineEdit;
  locationLayout->addWidget( m_longitudeEdit );
  connect( m_longitudeEdit, SIGNAL( returnPressed() ),
    SLOT( searchLocation() ) );
  
  QPushButton *locationSearchButton = new QPushButton( i18n("Nearby people") );
  locationLayout->addWidget( locationSearchButton );
  connect( locationSearchButton, SIGNAL( clicked() ),
    SLOT( searchLocation() ) );


  QWidget *localPage = new QWidget;
  tabWidget->addTab( localPage, i18n("Local") );
  
  QBoxLayout *localLayout = new QHBoxLayout( localPage );
  
  QPushButton *localButton = new QPushButton( i18n("Read Local Addressbook") );
  localLayout->addWidget( localButton );
  connect( localButton, SIGNAL( clicked() ), SLOT( readLocalAddressbook() ) );

#if 0
  QScrollArea *scrollArea = new QScrollArea;
  topLayout->addWidget( scrollArea, 1 );

  m_peopleView = new PeopleView;
  scrollArea->setWidget( m_peopleView );
#else
  m_peopleView = new PeopleView;
  topLayout->addWidget( m_peopleView, 1 );
#endif
}

AtticaView::~AtticaView()
{
}

void AtticaView::addPerson()
{
  PersonPlate *plate = new PersonPlate();
  plate->setLabel( "Loading..." );
  m_peopleView->addWidget( plate );

  Attica::PersonJob *job = Attica::Person::request( m_addEdit->text() );
  connect( job, SIGNAL( result( KJob * ) ),
    plate, SLOT( slotJobResult( KJob * ) ) );

  m_addEdit->clear();
}

void AtticaView::switchColors()
{
  // switch the foreground/background colors of the label
  QColor color = Settings::col_background();
  Settings::setCol_background( Settings::col_foreground() );
  Settings::setCol_foreground( color );

  settingsChanged();
}

void AtticaView::settingsChanged()
{
  QPalette pal;
  pal.setColor( QPalette::Window, Settings::col_background());
  pal.setColor( QPalette::WindowText, Settings::col_foreground());

  // i18n : internationalization
  emit signalChangeStatusbar( i18n("Settings changed") );
}

void AtticaView::searchLocation()
{
}

void AtticaView::searchName()
{
  qDebug() << "Searching...";

  Attica::PersonListJob *job =
    Attica::Person::requestSearchName( m_searchEdit->text() );
  connect( job, SIGNAL( result( KJob * ) ),
    SLOT( slotJobSearchNameResult( KJob * ) ) );
}

void AtticaView::slotJobSearchNameResult( KJob *j )
{
  Attica::PersonListJob *job = static_cast<Attica::PersonListJob *>( j );
  foreach( Attica::Person person, job->personList() ) {
    PersonPlate *plate = new PersonPlate();
    plate->setPerson( person );
    m_peopleView->addWidget( plate );
  }
}

void AtticaView::readLocalAddressbook()
{
  KABC::AddressBook *ab = KABC::StdAddressBook::self();
  
  KABC::AddressBook::Iterator it;
  for( it = ab->begin(); it != ab->end(); ++it ) {
    KABC::Addressee addressee = *it;
    qDebug() << addressee.uid();
    
    PersonPlate *plate = new PersonPlate();
    plate->setAddressee( addressee );
    m_peopleView->addWidget( plate );
  }
}

void AtticaView::showActivities()
{
  ActivityView *activityView = new ActivityView;
  activityView->show();
}


#include "atticaview.moc"
