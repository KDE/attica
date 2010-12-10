#include "buildservicejoboutputparser.h"

using namespace Attica;

BuildServiceJobOutput BuildServiceJobOutput::Parser::parseXml(QXmlStreamReader& xml)
{
    BuildServiceJobOutput buildservicejoboutput;

    // For specs about the XML provided, see here:
    // http://www.freedesktop.org/wiki/Specifications/open-collaboration-services-draft#BuildServiceJobs
    while (!xml.atEnd()) {
        //qDebug() << "XML returned:" << xml.text().toString();
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == "output") {
                buildservicejoboutput.setOutput(xml.readElementText());
            }
        } else if (xml.isEndElement() && (xml.name() == "output" || xml.name() == "user")) {
            break;
        }
    }
    return buildservicejoboutput;
}

QStringList BuildServiceJobOutput::Parser::xmlElement() const {
    return QStringList(QLatin1String("output")) << QLatin1String("user");
}
