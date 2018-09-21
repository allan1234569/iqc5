#ifndef W_ACCESS2_H
#define W_ACCESS2_H

#include "basewindow.h"

class W_Access2 : public BaseWindow
{
    Q_OBJECT

public:
    W_Access2(QWidget *parent = 0);
    ~W_Access2();

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

#endif // W_ACCESS2_H
