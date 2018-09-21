#ifndef MANAGEGROUP_H
#define MANAGEGROUP_H

#include "Model/Group.h"
#include <QDialog>

namespace Ui {
class ManageGroup;
}

class ManageGroup : public QDialog
{
    Q_OBJECT

public:
    explicit ManageGroup(QWidget *parent = 0);
    ~ManageGroup();

    void ShowAllData();
    void ShowAllData(QString categoryId, QString name);

private slots:
    void on_btnCancel_clicked();

    void on_btnAdd_clicked();

    void OnBtnTableEditClicked();
    void OnBtnTableDeleteClicked();

    void on_btnSearch_clicked();

    void on_inputHospital_currentIndexChanged(int index);

private:
    Ui::ManageGroup *ui;
    QVector<Group> model;
};

#endif // MANAGEGROUP_H
