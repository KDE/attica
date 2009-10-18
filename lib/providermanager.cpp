#include "providermanager.h"


using namespace Attica;

class ProviderManager::Private {
public:
    QHash<QString, Provider> m_providers;
    QHash<QUrl, QList<QString> > m_providersInFile; 
};


ProviderManager::ProviderManager()
    : d(new Private)
{
    d->m_providers.insert("opendesktop", Provider("opendesktop", QUrl("https://api.opendesktop.org/"), "OpenDesktop.org"));
    emit providersChanged();
}


ProviderManager::~ProviderManager()
{
    delete d;
}


void ProviderManager::addProviderFile(const QUrl& file) {
    // FIXME: Implement
}


void ProviderManager::removeProviderFile(const QUrl& file) {
    // FIXME: Implement
}


void ProviderManager::parseProviderFile(const QString& xmlString) {
    // FIXME: Implement
}


Provider ProviderManager::providerById(const QString& id) const {
    return d->m_providers.value(id);
}


QHash< QString, Provider > ProviderManager::providers() const {
    return d->m_providers;
}


#include "providermanager.moc"
