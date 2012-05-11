#ifndef PUBLISHERFIELDPARSER_H
#define PUBLISHERFIELDPARSER_H

#include "publisherfield.h"
#include "xmlparser.h"

namespace Attica
{
class PublisherField::XmlParser : public Attica::XmlParser<PublisherField>
{
private:
    PublisherField parseXml(QXmlStreamReader& xml);
    QStringList xmlElement() const;
};

} // namespace Attica

#endif // PUBLISHERFIELDPARSER_H
