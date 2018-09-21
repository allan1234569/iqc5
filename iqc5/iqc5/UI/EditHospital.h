#ifndef EDITHOSPITAL_H
#define EDITHOSPITAL_H

#include <QDialog>

namespace Ui {
class EditHospital;
}

class EditHospital : public QDialog
{
    Q_OBJECT

public:
    explicit EditHospital(QWidget *parent = 0);
    ~EditHospital();
    void SetModel(QString id);

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::EditHospital *ui;
    QString hospitalId;
};

#endif // EDITHOSPITAL_H
