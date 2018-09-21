#ifndef ECI_SETUP_H
#define ECI_SETUP_H

#include "asetupdialog.h"

#include <QCheckBox>

class Eci_Setup : public ASetupDialog
{
    Q_OBJECT
public:
    explicit Eci_Setup(QWidget *parent = 0);

signals:

public slots:


    // ASetupDialog interface
public:
    void loadConfig();

    void saveConfig();

protected slots:
    void on_Ensure_PushButton_clicked();

private:
    QCheckBox *checkbox;
};

#endif // ECI_SETUP_H
