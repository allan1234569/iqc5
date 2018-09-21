#ifndef W_LUMINO_H
#define W_LUMINO_H

#include "basewindow.h"

class W_Lumino : public BaseWindow
{
    Q_OBJECT

public:
    W_Lumino(QWidget *parent = 0);
    ~W_Lumino();

    int decode_NewMode(QString data);

    // BaseWindow interface
public:
    int decode(QString data);

    void loadConfig();

    // BaseWindow interface
public slots:
    void on_action_DecodeSetup_triggered();

private:
    qint32 m_nSampleNoStart;
    qint32 m_nSampleNoLen;
    qint32 m_nResultStart;
    qint32 m_nResultLen;
    qint32 m_nFlagStart;
    qint32 m_nFlagLen;

    bool m_bNewMode;

};

#endif // W_LUMINO_H
