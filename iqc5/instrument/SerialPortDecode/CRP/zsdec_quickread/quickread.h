#ifndef QUICKREAD_H
#define QUICKREAD_H

#include "basewindow.h"
#include "asql.h"

class QuickRead : public BaseWindow
{
    Q_OBJECT
public:
    explicit QuickRead(QWidget *parent = 0);

    int getEndPos(QString as_data) const;

signals:

public slots:

    // BaseWindow interface
public:

    /**
     * @brief decode    解码函数
     * @param data      待解码的数据
     * @return          -1  数据库打开失败
     *                  0   解码成功
     *                  1   未做任何解码，原因：需要解码的数据不完整，没有文本起始符或结束符
     */
    int decode(const QString &data);

    void loadConfig();

private:
    bool m_bIsWorking;

    QString m_sWorkDay; //工作日

    int m_nUseSeqAsSampleNo;  //使用原始序列号作为样本号

};

#endif // QUICKREAD_H
