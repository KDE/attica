#include "providermanager.h"

#include <QtCore/QDebug>
#include <QtCore/QSet>
#include <QtCore/QSharedPointer>
#include <QtCore/QTimer>
#include <QtNetwork/QAuthenticator>
#include <QtXml/QXmlStreamReader>


#define ATTICA_USE_KDE
#ifdef ATTICA_USE_KDE
#include <KIO/AccessManager>
#endif


using namespace Attica;

uint qHash(const QUrl& key) {
    return qHash(key.toString());
}

class ProviderManager::Private {
public:
    QHash<QUrl, Provider> m_providers;
    QHash<QUrl, QList<QString> > m_providerFiles;
    QSharedPointer<QNetworkAccessManager> m_qnam;

    Private()
#ifdef ATTICA_USE_KDE
        : m_qnam(new KIO::AccessManager(0))
#else
        : m_qnam(new QNetworkAccessManager)
#endif
    {
    }
    ~Private()
    {
    }
};


ProviderManager::ProviderManager()
    : d(new Private)
{
    
}

void ProviderManager::loadDefaultProviders()
{
    QTimer::singleShot(0, this, SLOT(init()));
}


void ProviderManager::clear() {
    d->m_providerFiles.clear();
    d->m_providers.clear();
}


void ProviderManager::init() {
    d->m_providers.insert(QUrl("https://api.opendesktop.org/v1/"), Provider(d->m_qnam, QUrl("https://api.opendesktop.org/v1/"), "OpenDesktop.org", QUrl()));
    emit providersChanged();
}

ProviderManager::~ProviderManager()
{
    delete d;
}

void ProviderManager::addProviderFile(const QUrl& file) {
    // FIXME: Implement
    
}

void ProviderManager::addProviderFromXml(const QString& providerXml)
{
    parseProviderFile(providerXml);
}

void ProviderManager::removeProviderFile(const QUrl& file) {
    // FIXME: Implement
}


void ProviderManager::parseProviderFile(const QString& xmlString)
{
    QXmlStreamReader xml(xmlString);
    while (xml.readNext()) {
        if (xml.isStartElement() && xml.name() == "provider") {
            QString baseUrl;
            QString name;
            QUrl icon;
            while (xml.readNext()) {
                if (xml.isStartElement())
                {
                    if (xml.name() == "location") {
                        baseUrl = xml.readElementText();
                        qDebug() << "reading provider with URL: " << baseUrl;
                    }
                    if (xml.name() == "name") {
                        name = xml.readElementText();
                    }
                    if (xml.name() == "icon") {
                        icon = QUrl(xml.readElementText());
                    }
                }         
            }
            if (!baseUrl.isEmpty()) {
                d->m_providers.insert(baseUrl, Provider(d->m_qnam, QUrl(baseUrl), name, icon));
            }
        }
    }
}

Provider ProviderManager::providerById(const QString& id) const {
    return d->m_providers.value(id);
}


QList<Provider> ProviderManager::providers() const {
    return d->m_providers.values();
}


bool ProviderManager::contains(const QString& provider) const {
    return d->m_providers.contains(provider);
}


QList<QUrl> ProviderManager::providerFiles() const {
    return d->m_providerFiles.keys();
}


void ProviderManager::authenticate(QNetworkReply* reply, QAuthenticator* auth)
{
    qDebug() << "authentication requested - implement me :D";
    // TODO
    
    // to stop the request use
    // reply->abort();
    
 
    auth->setUser("API4752248551824585417547616258117595859336334565755742650330375402");
    //auth->setPassword("pass");
    
    // we get the authentication details from storage (config/kwallet...)
    
    /* authentication needs to be implemented...
    if (d->m_authenticationStorage && d->m_authenticationStorage.contains(d->m_id)) {
        auth->setUser(d->m_authenticationStorage.user());
        auth->setPassword(d->m_authenticationStorage.password());
        return;
    }
    */

    
}

void ProviderManager::proxyAuthenticationRequired(const QNetworkProxy& proxy, QAuthenticator* authenticator)
{
#ifdef ATTICA_USE_KDE
    // FIXME
#endif

}


void ProviderManager::initNetworkAccesssManager()
{
    connect(d->m_qnam.data(), SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)), this, SLOT(authenticate(QNetworkReply*, QAuthenticator*)));
    connect(d->m_qnam.data(), SIGNAL(proxyAuthenticationRequired(QNetworkProxy, QAuthenticator*)), this, SLOT(proxyAuthenticationRequired(QNetworkProxy, QAuthenticator*)));
}


#include "providermanager.moc"
