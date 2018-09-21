#ifndef W_UF100_H
#define W_UF100_H

#include "basewindow.h"

class W_UF100 : public BaseWindow
{
    Q_OBJECT

public:
    W_UF100(QWidget *parent = 0);
    ~W_UF100();

    void transResult();

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);

private:
    bool m_bNoGraph;        //不处理图形数据
    bool m_bResultFirst;
    bool m_bIsQc;
    bool m_bIsEnd;
    bool m_bResultTok;

    QString m_sTotal;
    QString m_sEndBlock;
    QString m_sDcdMode;

    qint32 m_nTotalItem;

    QVector<QString> m_vItemCode;
    QVector<QString> m_vItemValue;
};

#endif // W_UF100_H
