#ifndef EDITPROJECTDATA_H
#define EDITPROJECTDATA_H

#include "Model/Project.h"
#include "Service/MaterialService.h"
#include "Service/ReagentService.h"
#include <QDialog>
#include <QTableWidget>

namespace Ui {
class EditProjectData;
}

class EditProjectData : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditProjectData(QWidget *parent = 0);
    ~EditProjectData();

    void Init();

    void SetModel(Project project);

private slots:
    void on_btnOK_clicked();
    void on_btnCancel_clicked();
    void batchNo_changed(int index);
    void reagent_changed(int index);
    void material_changed(int index);

    void on_inputNum_valueChanged(int arg1);

    void on_btnAddRow_clicked();

    void on_btnDeleteRow_clicked();

private:
    Ui::EditProjectData *ui;
    QString projectId;
    Project proj;
    QVector<Material> materials;
    QVector<Reagent> reagents;
    void InitResultTable(Project p, int level);
    void initRow(QTableWidget *table, int row);
    QVector<QTableWidget *> tables;

    bool eventFilter(QObject *object, QEvent *e);

    QString Format(QString s, int len);

};

#endif // EDITPROJECTDATA_H
