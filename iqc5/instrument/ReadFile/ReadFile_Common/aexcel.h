#ifndef AEXCEL_H
#define AEXCEL_H

#include <QtGlobal>
#include <QAxObject>

class AExcel
{
public:
    /**
     * @brief AExcel    初始化并打开文件
     * @param filename
     */
    AExcel(const QString filename);

    /**
     * @brief openWorkSheet 打开一张表格，默认第一张
     * @param index
     * @return
     */
    bool openWorkSheet(int index = 1);

    /**
     * @brief close 关闭文件
     */
    void close();

    /**
     * @brief getRowStart   获取开始行
     * @return
     */
    quint32 getRowStart();

    /**
     * @brief getColumnStart    获取开始列
     * @return
     */
    quint32 getColumnStart();

    /**
     * @brief rowCount  获取行数
     * @return
     */
    quint32 rowCount();

    /**
     * @brief columnCount   获取列数
     * @return
     */
    quint32 columnCount();

    /**
     * @brief getItemValue  获取指定单元格内容
     * @param row
     * @param column
     * @return
     */
    QString getItemValue(int row,int column);



private:
    QString m_filename;

    QAxObject *excel;
    QAxObject *workbooks;
    QAxObject *workbook;
    QAxObject *workSheet;
    QAxObject *usedrange;
    QAxObject *rows;
    QAxObject *columns;
};

#endif // AEXCEL_H





