#ifndef UF1000_SETUP_H
#define UF1000_SETUP_H

#include <QWidget>
#include "asetupdialog.h"
#include <QCheckBox>

class Uf1000_Setup : public ASetupDialog
{
    Q_OBJECT
public:
    explicit Uf1000_Setup(QWidget *parent = 0);

    void init();

signals:

public slots:


    // ASetupDialog interface
public:
    void loadConfig();

    void saveConfig();

protected slots:
    void on_Ensure_PushButton_clicked();

    void slt_on_oldmodeCheckBox_toggled(bool checked);

private:
    QCheckBox *oldmodeCheckBox;
    QCheckBox *usedfCheckBox;
    QCheckBox *useddCheckBox;
    QCheckBox *usedcCheckBox;
};

#endif // UF1000_SETUP_H
