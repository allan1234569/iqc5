#ifndef W_STRATAGENE_H
#define W_STRATAGENE_H

#include "basewindow.h"

class W_Stratagene : public BaseWindow
{
    Q_OBJECT

public:
    W_Stratagene(QWidget *parent = 0);
    ~W_Stratagene();

    // BaseWindow interface
public:
    void loadConfig();
    int decode(const QString &data);

private:
    quint16 m_nWellIndex;
    quint16 m_nSampleNoIndex;
    quint16 m_nResultIndex;

};

#endif // W_STRATAGENE_H
