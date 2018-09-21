#ifndef CENTAURSETUP_H
#define CENTAURSETUP_H

#include "asetupdialog.h"

#include <QLabel>
#include <QComboBox>

class CentaurSetup : public ASetupDialog
{
    Q_OBJECT
public:
    explicit CentaurSetup(QWidget *parent = 0);

signals:

public slots:

private:



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

#endif // CENTAURSETUP_H
