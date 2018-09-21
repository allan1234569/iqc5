#ifndef W_DSI905_H
#define W_DSI905_H

#include "basewindow.h"

class W_Dsi905 : public BaseWindow
{
    Q_OBJECT

public:
    W_Dsi905(QWidget *parent = 0);
    ~W_Dsi905();

    // BaseWindow interface
public:
    void decode(QString data);

    void loadConfig();

private:
    qint32 m_nSampleNoStart;
    qint32 m_nSampleNoLen;
};

#endif // W_DSI905_H
