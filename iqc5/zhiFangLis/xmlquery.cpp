#include "xmlquery.h"
#include <QFile>
#include <QDebug>
#include <QXmlResultItems>

XmlQuery::XmlQuery()
{
}

QDomNodeList XmlQuery::query(QString filename,QString path, QString namespaceStr)
{
    QString lastNode = path.right(path.length() - (path.lastIndexOf("/") + 1));
    path = path.left(path.lastIndexOf("/"));

    QFile file;
    file.setFileName(filename);

    file.open(QFile::ReadOnly);
    QXmlQuery query;
    query.setFocus(&file);


    query.setQuery(QString(namespaceStr + path));

    QString result;

    query.evaluateTo(&result);

    QDomDocument root;
    root.setContent(result);
    QDomNodeList list = root.elementsByTagName(lastNode);

    return list;
}
