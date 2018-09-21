#ifndef W_ES1010_H
#define W_ES1010_H

#include "basewindow.h"

class W_Es1010 : public BaseWindow
{
    Q_OBJECT

public:
    W_Es1010(QWidget *parent = 0);
    ~W_Es1010();

    void dealPatient(QString data);

    void dealOrder(QString data);

    int dealResult(QString data);

    void calcResult(QString &result);

    int makeResult(QString &itemalais, QString result, QString &printResult);   //未使用，暂留



    // BaseWindow interface
public:
    void loadConfig();

    int decode(QString data);

private:
    qint32 m_nSampleIdType;

    bool m_bIsQc;

};

#endif // W_ES1010_H
