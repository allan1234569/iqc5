#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include "Model/MachineCode.h"

namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = 0);
    ~Registration();

    void loadInfo();

Q_SIGNALS:
    void sig_TurnBackToLogin();

private slots:
    void on_BtnTurnBack_clicked();

    void on_AccreditCode_LineEdit_textChanged(const QString &arg1);

    void on_Btn_Accredit_clicked();

private:
    Ui::Registration *ui;

    MachineCode *m_machineCode;
};

#endif // REGISTRATION_H
