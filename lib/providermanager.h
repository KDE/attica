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
    QHash<QString, Provider> providers() const;
    Provider providerById(const QString& id) const;

Q_SIGNALS:
    void providersChanged();

private Q_SLOTS:

private:
    ProviderManager(const ProviderManager& other);
    ProviderManager& operator=(const ProviderManager& other);

    void parseProviderFile(const QString& xmlString);

    class Private;
    Private* const d;
};

}


#endif
