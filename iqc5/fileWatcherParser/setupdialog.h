#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>

namespace Ui {
class SetupDialog;
}

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupDialog(QWidget *parent = 0);
    ~SetupDialog();

private:
    Ui::SetupDialog *ui;
    void saveConfig();

signals:
    void on_exit();
protected slots:
    void on_okPushButton_clicked();
    void on_cancelPushButton_clicked();
};

#endif // SETUPDIALOG_H
