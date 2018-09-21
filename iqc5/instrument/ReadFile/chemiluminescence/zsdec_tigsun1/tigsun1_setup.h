#ifndef TIGSUN1_SETUP_H
#define TIGSUN1_SETUP_H

#include "asetupdialog.h"

class Tigsun1_Setup : public ASetupDialog
{
    Q_OBJECT
public:
    explicit Tigsun1_Setup(QWidget *parent = 0);

signals:

public slots:


    // ASetupDialog interface
public:
    void loadConfig();

    void saveConfig();

protected slots:
    void on_Ensure_PushButton_clicked();

private:
    QLabel *label;
    QLineEdit *filePath_LineEdit;
};

#endif // TIGSUN1_SETUP_H
