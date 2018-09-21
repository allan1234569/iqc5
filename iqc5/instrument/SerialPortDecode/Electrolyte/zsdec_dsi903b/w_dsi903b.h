#ifndef W_DSI903B_H
#define W_DSI903B_H

#include "basewindow.h"

class W_Dsi903b : public BaseWindow
{
    Q_OBJECT

public:
    W_Dsi903b(QWidget *parent = 0);
    ~W_Dsi903b();

    // BaseWindow interface
public:
    void decode(QString data);

private:
    qint32 m_nSegLen;
    qint32 m_nSampleNoStart;
    qint32 m_nSampleNoLen;

    // BaseWindow interface
public:
    void loadConfig();
};

#endif // W_DSI903B_H
