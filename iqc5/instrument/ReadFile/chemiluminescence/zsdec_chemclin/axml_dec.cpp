#include "axml_dec.h"

#include <QDir>
#include <QFile>

#include <QDebug>

AXml_dec::AXml_dec(const QString filepath)
    :m_filepath(filepath)
{
    m_errorStr = "";

    m_count = 0;
}

void AXml_dec::parser()
{
    m_count = 0;
    QString ls_item;
    QString ls_date;
    QString ls_sampleno;
    QString ls_result;

    QDomNodeList methods = getMethods();
    qDebug() << __LINE__;
    for (int i = 0; i < methods.size(); i++)
    {
        qDebug() << __LINE__;
        if (methods.at(i).isElement() && (methods.at(i).nodeName() == "Method"))
        {
            qDebug() << __LINE__;
            QDomElement method = methods.at(i).toElement();
            QDomNodeList methodNodes = method.childNodes();

            for(int j = 0; j < methodNodes.size(); j++)
            {
                qDebug() << __LINE__;
                if(methodNodes.at(j).isElement() && methodNodes.at(j).nodeName() == "MethodName")
                {
                    qDebug() << __LINE__;
                    ls_item = methodNodes.at(j).toElement().text(); //项目名
                }
                else if (methodNodes.at(j).isElement() && methodNodes.at(j).nodeName() == "report")
                {
                    qDebug() << __LINE__;
                    QDomElement report = methodNodes.at(j).toElement();
                    ls_date = report.attribute("generatedAt");   //日期

                    QDomNodeList repotrNodes = report.childNodes();
                    for(int k = 0; k < repotrNodes.size(); k++)
                    {
                        qDebug() << __LINE__;
                        if (repotrNodes.at(k).isElement() && (repotrNodes.at(k).nodeName() == "sample"))
                        {
                            qDebug() << __LINE__;
                            qDebug() << repotrNodes.at(k).nodeName();
                            QDomElement sample =repotrNodes.at(k).toElement();
                            qDebug() << sample.attribute("type");
                            if(sample.attribute("type") == "3")
                            {
                                qDebug() << __LINE__;
                                ls_sampleno = sample.attribute("id");
                                ls_result = sample.attribute("result");
                                ls_result = ls_result.replace("&#60","<");
                                if ((ls_result != "+") && (ls_result != "-") && (ls_result != "+-"))
                                {
                                    qDebug() << __LINE__;
                                    m_vSampleNo.push_back(ls_sampleno);
                                    m_vItem.push_back(ls_item);
                                    m_vSampleDate.push_back(ls_date);
                                    m_vResult.push_back(ls_result);
                                    m_count++;
                                }
                            }

                        }
                    }
                }
            }
        }
    }


}

void AXml_dec::clear()
{
    m_count = 0;
    m_vItem.clear();
    m_vSampleNo.clear();
    m_vSampleDate.clear();
    m_vResult.clear();
}

QDomNodeList AXml_dec::getMethods()
{
    m_errorStr.clear();
    QDomNodeList nodeList;

    QFile file(m_filepath);
    if (!file.exists())
    {
        m_errorStr.append("文件不存在或文件路径不正确\n");
        return nodeList;
    }

    if (m_filepath.left(1) != "/")
    {
        m_filepath.prepend("/");

    }

    qDebug() << m_filepath;
    QXmlQuery query;
    query.setQuery(QString("doc('%1')//Method").arg(m_filepath));
    if (!query.isValid())
    {
        m_errorStr.append("查询参数错误");
        qDebug() << __LINE__;
        return nodeList;
    }

    QString xmlStr;
    query.evaluateTo(&xmlStr);
    xmlStr.prepend("<Methods>\n").append("</Methods>");

    QDomDocument resourceRoot;
    resourceRoot.setContent(xmlStr);
    xmlStr.replace("&gt",">");
    xmlStr.replace("&lt","<");

    nodeList = resourceRoot.elementsByTagName("Method");

    return nodeList;
}
