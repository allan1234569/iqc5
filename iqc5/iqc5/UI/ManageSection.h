#ifndef MANAGESECTION_H
#define MANAGESECTION_H

#include "Model/Section.h"
#include <QDialog>

namespace Ui {
class ManageSection;
}

class ManageSection : public QDialog
{
    Q_OBJECT

public:
    explicit ManageSection(QWidget *parent = 0);
    ~ManageSection();

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
    Ui::ManageSection *ui;
    QVector<Section> model;
};

#endif // MANAGESECTION_H
