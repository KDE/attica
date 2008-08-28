/*
 * atticaview.h
 *
 * Copyright (C) 2008 Cornelius Schumacher <schumacher@kde.org>
 */
#ifndef ATTICAVIEW_H
#define ATTICAVIEW_H

#include <QtGui>

class KUrl;
class KJob;
class PeopleView;

/**
  This is the main view class for Attica.  Most of the non-menu,
  non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
  here.

  @short Main view
  @author Cornelius Schumacher <schumacher@kde.org>
  @version 0.1
*/
class AtticaView : public QWidget
{
    Q_OBJECT
  public:
    AtticaView(QWidget *parent);
    virtual ~AtticaView();

  protected slots:
    void addPerson();
    void searchName();
    void searchLocation();

    void readLocalAddressbook();

    void slotJobSearchNameResult( KJob *j );

    void showActivities();

  private:

  signals:
    /**
     * Use this signal to change the content of the statusbar
     */
    void signalChangeStatusbar(const QString& text);

    /**
     * Use this signal to change the content of the caption
     */
    void signalChangeCaption(const QString& text);

  private slots:
    void switchColors();
    void settingsChanged();

  private:
    QLineEdit *m_addEdit;
    QLineEdit *m_searchEdit;
    QLineEdit *m_latitudeEdit;
    QLineEdit *m_longitudeEdit;

    PeopleView *m_peopleView;
};

#endif
