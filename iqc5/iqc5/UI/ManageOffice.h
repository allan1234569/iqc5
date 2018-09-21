#ifndef MANAGEOFFICE_H
#define MANAGEOFFICE_H

#include "Model/Office.h"
#include <QDialog>

namespace Ui {
class ManageOffice;
}

class ManageOffice : public QDialog
{
    Q_OBJECT

public:
    explicit ManageOffice(QWidget *parent = 0);
    ~ManageOffice();

    void ShowAllData();
    void ShowAllData(int categoryId, QString name);

private slots:
    void on_btnCancel_clicked();

    void on_btnAdd_clicked();

    void OnBtnTableEditClicked();
    void OnBtnTableDeleteClicked();

    void on_btnSearch_clicked();

    void on_inputHospital_currentIndexChanged(int index);

private:
    Ui::ManageOffice *ui;
    QVector<Office> model;
};


#endif // MANAGEOFFICE_H
