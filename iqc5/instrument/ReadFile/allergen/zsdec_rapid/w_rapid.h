#ifndef W_RAPID_H
#define W_RAPID_H

#include "basewindow.h"

class W_Rapid : public BaseWindow
{
    Q_OBJECT

public:
    W_Rapid(QWidget *parent = 0);
    ~W_Rapid();

    // BaseWindow interface
public:
    void decode(QString data);

    void loadConfig();

public slots:

    void on_action_DecodeSetup_triggered();

    // BaseWindow interface
public slots:
    void slt_timeout();

private:
    QString m_sSampleNoSeg;

    QString m_sSampleNoKey;

    QString m_sResultFile;
};

#endif // W_RAPID_H
