#ifndef EDITMATERIAL_H
#define EDITMATERIAL_H

#include <QDialog>
#include <QTableWidget>
#include "Model/MaterialBatch.h"

namespace Ui {
class EditMaterial;
}

class EditMaterial : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditMaterial(QWidget *parent = 0);
    ~EditMaterial();
    void SetModel(QString id);
    void SetName(QString name);
    void initRow(QTableWidget *table, int row, MaterialBatch *material);
    
private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void rowAdd();
    void rowDelete();

private:
    Ui::EditMaterial *ui;
    QString materialId;
};

#endif // EDITMATERIAL_H
