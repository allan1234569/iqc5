#ifndef MANAGEHOSPITAL_H
#define MANAGEHOSPITAL_H

#include "Model/Hospital.h"
#include <QDialog>

namespace Ui {
class ManageHospital;
}

class ManageHospital : public QDialog
{
    Q_OBJECT

public:
    explicit ManageHospital(QWidget *parent = 0);
    ~ManageHospital();

    void ShowAllData();
    void ShowAllData(QString name);

private slots:
    void on_btnCancel_clicked();

    void on_btnAdd_clicked();

    void OnBtnTableEditClicked();
    void OnBtnTableDeleteClicked();

    void on_btnSearch_clicked();

private:
    Ui::ManageHospital *ui;
    QVector<Hospital> model;
};

#endif // MANAGEHOSPITAL_H
