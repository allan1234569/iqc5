#ifndef CENTAURCP_SETUP_H
#define CENTAURCP_SETUP_H

#include "asetupdialog.h"
#include <QLabel>
#include <QComboBox>

class CentaurCp_Setup : public ASetupDialog
{
    Q_OBJECT
public:
    explicit CentaurCp_Setup(QWidget *parent = 0);

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

#endif // CENTAURCP_SETUP_H
