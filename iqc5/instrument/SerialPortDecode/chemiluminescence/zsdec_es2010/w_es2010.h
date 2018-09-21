#ifndef W_ES2010_H
#define W_ES2010_H

#include "basewindow.h"

class W_Es2010 : public BaseWindow
{
    Q_OBJECT

public:
    W_Es2010(QWidget *parent = 0);
    ~W_Es2010();

    int getSegPos(QString data, QString find, qint32 from = 0);

    void dealPatient(QString data);

    void dealOrder(QString data);

    void dealResult(QString data);

    void calcResult(QString &result);

    // BaseWindow interface
public:
    void loadConfig();

    int decode(QString data);

public slots:
    void on_action_DecodeSetup_triggered();

private:
    bool m_bIsQc;
    qint32 m_nSampleIdType;     //1 样本号，2 流水号


    bool m_bBarCodeMode;        //条码双工模式
    QString m_sBarCodeSampleNo; //条码双工时的样本号



};

#endif // W_ES2010_H
