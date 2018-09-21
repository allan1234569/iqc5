#ifndef W_SPIFE_H
#define W_SPIFE_H

#include "basewindow.h"

class W_Spife : public BaseWindow
{
    Q_OBJECT

public:
    W_Spife(QWidget *parent = 0);
    ~W_Spife();

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);


    void deal_result(QString as_str);

private:
    int m_nNoMode;
    QString m_sResultMode;
};

#endif // W_SPIFE_H
