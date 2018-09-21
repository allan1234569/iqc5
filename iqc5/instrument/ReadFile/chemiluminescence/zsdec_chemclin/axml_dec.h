/*
 *
 *  针对文件的专用解析,只需要提供相应参数即可
 *
 */


#ifndef AXML_DEC_H
#define AXML_DEC_H

#include <QXmlQuery>
#include <QDomDocument>
#include <QVector>

class AXml_dec
{
public:
    AXml_dec(const QString filepath = "");

    void parser();

    void clear();

    inline const QString errorString(){ return m_errorStr; }

    inline QVector<QString> getItems(){ return m_vItem; }

    inline QVector<QString> getSampleNos(){ return m_vSampleNo; }

    inline QVector<QString> getSampleDates(){ return m_vSampleDate; }

    inline QVector<QString> getResults(){ return m_vResult; }

    inline int count(){ return m_count; }


private:
    /**
     * @brief getNodes      获取指定结点内容
     * @param filepath      文件路径
     * @param xpath         XPath字符串
     * @param splitByNode   分割结点
     * @return
     */
    QDomNodeList getMethods();

private:
    QString m_errorStr;

    QString m_filepath;

    int m_count;

    QVector<QString> m_vItem;
    QVector<QString> m_vSampleNo;
    QVector<QString> m_vSampleDate;
    QVector<QString> m_vResult;


};

#endif // AXML_DEC_H
