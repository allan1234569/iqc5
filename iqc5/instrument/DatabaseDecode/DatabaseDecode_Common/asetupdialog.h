#ifndef ASETUPDIALOG_H
#define ASETUPDIALOG_H

#include <QDialog>

namespace Ui {
class ASetupDialog;
}

class ASetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ASetupDialog(QWidget *parent = 0);
    ~ASetupDialog();

private slots:

    void on_Ensure_PushButton_clicked();

    void on_AdvancePushButton_clicked();

    void on_Cancel_PushButton_clicked();


private:
    Ui::ASetupDialog *ui;

private:
    void loadConfig();

    bool saveConfig();

};

#endif // ASETUPDIALOG_H
