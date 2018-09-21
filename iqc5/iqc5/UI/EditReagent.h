#ifndef EDITREAGENT_H
#define EDITREAGENT_H

#include <QDialog>
#include <QTableWidget>
#include "Model/ReagentBatch.h"

namespace Ui {
class EditReagent;
}

class EditReagent : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditReagent(QWidget *parent = 0);
    ~EditReagent();
    void SetModel(QString id);
    void SetName(QString name);
    void initRow(QTableWidget *table, int row, ReagentBatch *material);
    
private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void rowAdd();
    void rowDelete();

private:
    Ui::EditReagent *ui;
    QString reagentId;
};

#endif // EDITREAGENT_H
