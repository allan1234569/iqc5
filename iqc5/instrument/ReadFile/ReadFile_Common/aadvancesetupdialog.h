#ifndef AADVANCESETUPDIALOG_H
#define AADVANCESETUPDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class AAdvanceSetupDialog;
}

class AAdvanceSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AAdvanceSetupDialog(QWidget *parent = 0);
    ~AAdvanceSetupDialog();

    void loadConfig();

    void saveConfig();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Add_ToolButton_clicked();

    void on_Delete_ToolButton_clicked();

private:
    Ui::AAdvanceSetupDialog *ui;
};

#endif // AADVANCESETUPDIALOG_H
