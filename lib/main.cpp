#include "attica.h"
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <KDE/KLocale>

static const char description[] =
    I18N_NOOP("Social Desktop Community Viewer");

static const char version[] = "0.1";

int main(int argc, char **argv)
{
    KAboutData about("attica", 0, ki18n("Attica"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2008 Cornelius Schumacher"), KLocalizedString(), 0, "schumacher@kde.org");
    about.addAuthor( ki18n("Cornelius Schumacher"), KLocalizedString(), "schumacher@kde.org" );
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    options.add("+[URL]", ki18n( "Document to open" ));
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    Attica *widget = new Attica;

    // see if we are starting with session management
    if (app.isSessionRestored())
    {
        RESTORE(Attica);
    }
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        if (args->count() == 0)
        {
            //attica *widget = new attica;
            widget->show();
        }
        else
        {
            int i = 0;
            for (; i < args->count(); i++)
            {
                //attica *widget = new attica;
                widget->show();
            }
        }
        args->clear();
    }

    return app.exec();
}
