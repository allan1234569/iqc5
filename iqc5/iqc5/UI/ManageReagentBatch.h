#ifndef MANAGEREAGENTBATCH_H
#define MANAGEREAGENTBATCH_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMainWindow>
#include <QMainWindow>
#include <QTableWidget>
#include "Model/ReagentBatch.h"
#include <QCloseEvent>

namespace Ui {
class ManageReagentBatch;
}

class ManageReagentBatch : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManageReagentBatch(QWidget *parent = 0);
    ~ManageReagentBatch();

    void InitTree();
    void ShowAllData();
    void InitTable();
    void initRow(QTableWidget *table, int row, ReagentBatch *batch);

private slots:
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void OnBtnTableEditClicked();
    void OnBtnTableDeleteClicked();
    void on_pushButton_clicked();

    void on_inputKeyword_textChanged(const QString &arg1);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnSave_clicked();

    void closeEvent(QCloseEvent* event);

private:
    Ui::ManageReagentBatch *ui;

    QString currentReagentId;
};
#endif // MANAGEREAGENTBATCH_H
