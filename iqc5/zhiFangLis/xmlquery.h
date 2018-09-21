#ifndef XMLQUERY_H
#define XMLQUERY_H

#include <QXmlQuery>
#include <QDomNodeList>

class XmlQuery
{
public:
    explicit XmlQuery();
    QDomNodeList query(QString filename, QString path, QString namespaceStr);

signals:

public slots:

};

#endif // XMLQUERY_H
