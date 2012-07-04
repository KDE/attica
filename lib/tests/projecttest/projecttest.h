/*
    This file is part of KDE.

    Copyright 2010 Sebastian Kügler <sebas@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef PROJECTTEST_H
#define PROJECTTEST_H

#include "ui_editproject.h"

#include <QtGui/QLabel>
#include <QtGui/QMainWindow>

#include <providermanager.h>
#include <project.h>
#include "nonetype.h"

namespace Attica {
    class Project;
    class Provider;
}

class ProjectTest : public QMainWindow
{
Q_OBJECT
public:
    ProjectTest();
    virtual ~ProjectTest();

private Q_SLOTS:
    void providerAdded(const Attica::Provider& provider);

    void projectListResult(Attica::BasicJob*);
    void projectResult(Attica::BasicJob*);
    void createProjectResult(Attica::BasicJob* j);
    void saveProjectResult(Attica::BasicJob* j);
    void deleteProjectResult(Attica::BasicJob* j);

    void buildServiceListResult(Attica::BasicJob*);
    void buildServiceJobListResult(Attica::BasicJob*);

    void save();
    void create();
    void deleteProject(); // don't clashs with keyword

    void selectedBuildServiceChanged(QListWidgetItem* current, QListWidgetItem* previous);
    void createBuildServiceJob();
    void buildServiceJobCreated(Attica::BasicJob* j);
    void cancelBuildServiceJob();
    void buildServiceJobCanceled(Attica::BasicJob* j);

    void updateCurrentProject();

private:
    void initOcs();
    void getProject(QString id);
    void deleteProject(QString id);
    void listProjects();
    void listBuildServices();
    void listBuildServiceJobs(const Attica::Project &p);

    void setStatus(QString status);
    Attica::Project uiToProject();
    void projectToUi(const Attica::Project& p);
    QString currentProject();

    Attica::ProviderManager m_pm;
    Attica::Provider m_provider;
    QHash<QString, QSharedPointer<Attica::Provider> > m_providers;

    QString m_currentProjectId;

    QWidget* m_mainWidget;

    Ui::EditProject* m_editor;

    QHash<QString, Attica::BuildService> m_buildServices;
    QHash<QString, Attica::BuildServiceJob> m_buildServiceJobs;
    QHash<QString, Attica::Project> m_projects;

};

#endif // PROJECTTEST_H
