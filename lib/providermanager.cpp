#include "providermanager.h"

#include <QtCore/QDebug>
#include <QtCore/QSet>
#include <QtCore/QSharedPointer>
#include <QtCore/QTimer>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkReply>
#include <QtXml/QXmlStreamReader>


#define ATTICA_USE_KDE
#ifdef ATTICA_USE_KDE
#include <KIO/AccessManager>
#include <KWallet/Wallet>
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
    KWallet::Wallet* m_wallet;

    Private()
#ifndef ATTICA_USE_KDE
        : m_qnam(new KIO::AccessManager(0)),
          m_wallet(0)
#else
        : m_qnam(new QNetworkAccessManager),
          m_wallet(0)
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
    connect(d->m_qnam.data(), SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), SLOT(authenticate(QNetworkReply*,QAuthenticator*)));
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

void ProviderManager::addProviderFile(const QUrl& file)
{
    // TODO: use qnam::get to get the file and then parse it
    
    // For local files:
    /*
    QFile file(localFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "ProviderManager::addProviderFile: could not open provider file: " << url.toString();
        return;
    }
    addProviderFromXml(file.readAll());
    file.close();
    */
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
    qDebug() << "parseProviderFile" << xmlString;
    QXmlStreamReader xml(xmlString);
    while (!xml.atEnd() && xml.readNext()) {
        if (xml.isStartElement() && xml.name() == "provider") {
            QString baseUrl;
            QString name;
            QUrl icon;
            while (!xml.atEnd() && xml.readNext()) {
                if (xml.isStartElement())
                {
                    qDebug() << "parseProviderFile" << xml.name();
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
                emit providersChanged();
            }
        }
    }
}

Provider ProviderManager::providerByUrl(const QUrl& url) const {
    return d->m_providers.value(url);
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
    // FIXME: This is a KDE specific authentication only atm
    QUrl baseUrl;
    foreach (const QUrl& url, d->m_providers.keys()) {
        if (url.isParentOf(reply->url())) {
            baseUrl = url;
            break;
        }
    }
    
    if (auth->user().isEmpty() && auth->password().isEmpty()) {
        QString networkWallet = KWallet::Wallet::NetworkWallet();
        if (!KWallet::Wallet::keyDoesNotExist(networkWallet, "Attica", baseUrl.toString())) {
            if (!d->m_wallet) {
                d->m_wallet = KWallet::Wallet::openWallet(networkWallet, 0);
            }
            if (d->m_wallet) {
                d->m_wallet->setFolder("Attica");
                QMap<QString, QString> entries;
                d->m_wallet->readMap(baseUrl.toString(), entries);
                auth->setUser(entries.value("user"));
                auth->setPassword(entries.value("password"));
                return;
            }
        } else {
            qDebug() << "ProviderManager::authenticate: Wallet entry not found";
        }
    } else {
        qDebug() << "ProviderManager::authenticate: We already authenticated once, not trying forever...";
    }
    reply->abort();
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
