#ifndef EDITOFFICE_H
#define EDITOFFICE_H

#include <QDialog>

namespace Ui {
class EditOffice;
}

class EditOffice : public QDialog
{
    Q_OBJECT

public:
    explicit EditOffice(QWidget *parent = 0);
    ~EditOffice();
    void SetModel(QString id);

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_inputHospital_currentIndexChanged(int index);

private:
    Ui::EditOffice *ui;
    QString officeId;
};

#endif // EDITOFFICE_H
