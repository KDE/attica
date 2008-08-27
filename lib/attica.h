/*
 * attica.h
 *
 * Copyright (C) 2008 Cornelius Schumacher <schumacher@kde.org>
 */
#ifndef ATTICA_H
#define ATTICA_H


#include <kxmlguiwindow.h>

#include "ui_prefs_base.h"

class AtticaView;
class QPrinter;
class KToggleAction;
class KUrl;

/**
 * This class serves as the main window for Attica.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author Cornelius Schumacher <schumacher@kde.org>
 * @version 0.1
 */
class Attica : public KXmlGuiWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    Attica();

    /**
     * Default Destructor
     */
    virtual ~Attica();

private slots:
    void fileNew();
    void optionsPreferences();

private:
    void setupActions();

private:
    Ui::prefs_base ui_prefs_base ;
    AtticaView *m_view;

    QPrinter   *m_printer;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
};

#endif // _ATTICA_H_
