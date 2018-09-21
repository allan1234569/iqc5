#ifndef W_AC980_H
#define W_AC980_H

#include "basewindow.h"

class W_AC980 : public BaseWindow
{
    Q_OBJECT

public:
    W_AC980(QWidget *parent = 0);
    ~W_AC980();

    // BaseWindow interface
public:
    void decode(QString data);

    // BaseWindow interface
public:
    void loadConfig();

private:
    quint32 m_nSampleNoStart;
    quint32 m_nSampleNoLen;
};

#endif // W_AC980_H
