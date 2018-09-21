#ifndef W_DXI800_H
#define W_DXI800_H

#include "basewindow.h"

class W_Dxi800 : public BaseWindow
{
    Q_OBJECT

public:
    W_Dxi800(QWidget *parent = 0);
    ~W_Dxi800();

    int checkEtx(QString as_data);

    void getSampleNo(QString as_sampleno, QString as_posno);

    // BaseWindow interface
public:
    void loadConfig();

    int decode(QString data);

public slots:
    void on_action_DecodeSetup_triggered();

private:
    qint32 m_nSampleNoMode;
};

#endif // W_DXI800_H
