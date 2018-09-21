#ifndef DXI800_SETUP_H
#define DXI800_SETUP_H

#include "asetupdialog.h"

class Dxi800_setup : public ASetupDialog
{
    Q_OBJECT
public:
    explicit Dxi800_setup(QWidget *parent = 0);

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
    QComboBox *combox;
};

#endif // DXI800_SETUP_H
