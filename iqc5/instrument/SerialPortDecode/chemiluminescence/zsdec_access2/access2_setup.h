#ifndef ACCESS2_SETUP_H
#define ACCESS2_SETUP_H

#include "asetupdialog.h"
#include <QComboBox>
#include <QLabel>


class Access2_Setup : public ASetupDialog
{
    Q_OBJECT
public:
    explicit Access2_Setup(QWidget *parent = 0);

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

#endif // ACCESS2_SETUP_H
