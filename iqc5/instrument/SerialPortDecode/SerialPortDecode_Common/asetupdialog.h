#ifndef ASETUPDIALOG_H
#define ASETUPDIALOG_H

#include <QDialog>
#include "ui_asetupdialog.h"
#include "common.h"

namespace Ui {
class ASetupDialog;
}

class ASetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ASetupDialog(QWidget *parent = 0);
    ~ASetupDialog();

    virtual void loadConfig();

    virtual void saveConfig();

protected slots:

    virtual void on_Ensure_PushButton_clicked();

    void on_AdvancePushButton_clicked();

    void on_Cancel_PushButton_clicked();

public:
    Ui::ASetupDialog *ui;

};

#endif // ASETUPDIALOG_H
