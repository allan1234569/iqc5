#ifndef INPUTDATASINGLE_H
#define INPUTDATASINGLE_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QTableWidget>
#include <QListWidget>
#include "Model/Project.h"
#include <QKeyEvent>
#include <QCloseEvent>

namespace Ui {
class InputDataSingle;
}

class InputDataSingle : public QMainWindow
{
    Q_OBJECT

public:
    explicit InputDataSingle(QWidget *parent = 0);
    ~InputDataSingle();
    Project currentProject;
    QVector<QTableWidget *> tables;

private slots:
    void on_btnOK_clicked();

    void on_inputKeyword_textChanged(const QString &arg1);

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_inputSubject_currentIndexChanged(int index);

    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void rowAdd();
    void rowDelete();

    void material_changed(int index);
    void materialbatch_changed(QString arg1);
    void reagent_changed(int index);
    void reagentbatch_changed(QString arg1);

    void materialName_changed(QString arg1);
    void materialBatchName_changed(QString arg1);
    void reagentName_changed(QString arg1);
    void reagentBatchName_changed(QString arg1);
    void methodName_changed(QString arg1);

    void materialName_changed();
    void materialBatchName_changed();
    void reagentName_changed();
    void reagentBatchName_changed();
    void methodName_changed();

    void on_inputDeviceName_textChanged(const QString &arg1);

    void on_btnCancel_clicked();
    void on_listWidget_clicked(const QModelIndex &index);

    void on_inputDeviceName_selectionChanged();

    void closeEvent(QCloseEvent* event);
    void keyPressEvent (QKeyEvent * keyevent);
    void mousePressEvent(QMouseEvent *event);

    void on_inputDeviceName_editingFinished();

//    /**
//     * @brief slt_Editing   单元格被编辑时的处理函数
//     * @param txt
//     */
//    void slt_Editing(const QString &txt);

//    /**
//     * @brief slt_EditFinished  单元格完成编辑时的处理函数
//     */
//    void slt_EditFinished();

private:
    Ui::InputDataSingle *ui;
    void InitProjects();
    void InitTree();
    void ShowProjectResult();
    QListWidget *listWidget;
    QLineEdit *lineEdit;
    void initRow(QTableWidget *table, int row, Result *result);
    bool eventFilter(QObject*obj,QEvent*event);
    bool IsValid(QTableWidget *table,QString name,int col);


    QVector<QString> deleteList;

};

#endif // INPUTDATASINGLE_H
