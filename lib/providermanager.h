#ifndef ATTICA_PROVIDERMANAGER_H
#define ATTICA_PROVIDERMANAGER_H

#include <QtCore/QUrl>

#include "provider.h"
#include "atticaclient_export.h"

namespace Attica {

class ATTICA_EXPORT ProviderManager : public QObject
{
    Q_OBJECT

public:
    ProviderManager();
    ~ProviderManager();

    void addProviderFile(const QUrl& file);
    void removeProviderFile(const QUrl& file);
    QList<QUrl> providerFiles() const;

    QList<Provider> providers() const;
    bool contains(const QString& provider) const;
    Provider providerById(const QString& id) const;

Q_SIGNALS:
    void providersChanged();

private Q_SLOTS:
    void authenticate(QNetworkReply*, QAuthenticator*);
    void proxyAuthenticationRequired(const QNetworkProxy& proxy, QAuthenticator* authenticator);
    void init();

private:
    ProviderManager(const ProviderManager& other);
    ProviderManager& operator=(const ProviderManager& other);

    void initNetworkAccesssManager();

    QHash<QString, Provider> parseProviderFile(const QString& xmlString);

    class Private;
    Private* const d;
};

}


#endif
