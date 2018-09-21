#ifndef LUMINO_SETUP_H
#define LUMINO_SETUP_H

#include "asetupdialog.h"
#include <QCheckBox>

class Lumino_Setup : public ASetupDialog
{
    Q_OBJECT
public:
    explicit Lumino_Setup(QWidget *parent = 0);

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

#endif // LUMINO_SETUP_H
