#ifndef AWARNINGDIALOG_H
#define AWARNINGDIALOG_H

#include <QDialog>

namespace Ui {
class AWarningDialog;
}

class AWarningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AWarningDialog(QWidget *parent = 0);
    ~AWarningDialog();

    void showMessage(QString &message);
private:
    Ui::AWarningDialog *ui;
};

#endif // AWARNINGDIALOG_H
