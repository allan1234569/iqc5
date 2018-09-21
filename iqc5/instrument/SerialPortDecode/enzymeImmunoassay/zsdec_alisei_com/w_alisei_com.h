#ifndef W_ALISEI_COM_H
#define W_ALISEI_COM_H

#include "basewindow.h"

class W_Alisei_Com : public BaseWindow
{
    Q_OBJECT

public:
    W_Alisei_Com(QWidget *parent = 0);
    ~W_Alisei_Com();

    // BaseWindow interface
public:
    void decode(QString data);

    int wf_decode(QString data);

    int getLineVal(QString data, QString key, QString &ret);

};

#endif // W_ALISEI_COM_H
