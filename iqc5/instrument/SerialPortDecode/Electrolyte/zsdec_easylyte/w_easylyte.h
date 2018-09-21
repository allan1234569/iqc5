#ifndef W_EASYLYTE_H
#define W_EASYLYTE_H

#include "basewindow.h"

class W_Easylyte : public BaseWindow
{
    Q_OBJECT

public:
    W_Easylyte(QWidget *parent = 0);
    ~W_Easylyte();

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);

    void decode_autoSample(QString data);

private:
    qint32 m_nAutoSample;   //自动样本
};

#endif // W_EASYLYTE_H
