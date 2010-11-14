#include <QtGui/QApplication>
#include "projecttest.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    ProjectTest foo;
    foo.show();
    return app.exec();
}
