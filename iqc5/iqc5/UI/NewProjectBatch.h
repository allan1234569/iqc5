#ifndef NEWPROJECTBATCH_H
#define NEWPROJECTBATCH_H

#include <QMainWindow>
#include <QTableWidget>
#include <QListWidget>
#include "Model/Project.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QCloseEvent>

namespace Ui {
class NewProjectBatch;
}

class NewProjectBatch : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewProjectBatch(QWidget *parent = 0);
    ~NewProjectBatch();



private slots:
    void subject_changed(int index);
    void category_changed(int index);
    void testtype_changed(int index);
    void level_changed(int index);
    void num_changed(int index);
    void material_changed(int index);
    void reagent_changed(int index);
    void method_changed(int index);

    void customName_changed(QString arg1);
    void englishName_changed(QString arg1);
    void chineseName_changed(QString arg1);
    void materialName_changed(QString arg1);
    void materialBatchName_changed(QString arg1);
    void reagentName_changed(QString arg1);
    void reagentBatchName_changed(QString arg1);
    void methodName_changed(QString arg1);
    void device_changed(QString arg1);
    void displayIndex_changed(QString arg1);

    void customName_changed();
    void englishName_changed();
    void chineseName_changed();
    void materialName_changed();
    void materialBatchName_changed();
    void reagentName_changed();
    void reagentBatchName_changed();
    void methodName_changed();
    void device_changed();
    void displayIndex_changed();


    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void rowAdd();
    void rowDelete();

    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_pushButton_clicked();

    void on_inputSubject_currentIndexChanged(int index);

    void slt_listWidget_clicked(const QModelIndex &index);

    bool eventFilter(QObject*obj,QEvent*event);
    void keyPressEvent (QKeyEvent * keyevent);

    void on_inputDeviceName_textChanged(const QString &arg1);

    void on_inputMethodName_textChanged(const QString &arg1);

    void on_inputMaterialName_textChanged(const QString &arg1);

    void on_inputReagentName_textChanged(const QString &arg1);

    void on_btnConfigColumn_clicked();

    void on_inputName_textChanged(const QString &arg1);

    void on_inputDeviceName_selectionChanged();

    void on_inputName_selectionChanged();

    void on_inputMethodName_selectionChanged();

    void on_inputMaterialName_selectionChanged();

    void on_inputReagentName_selectionChanged();

    void closeEvent(QCloseEvent* event);

    void closeList();

    void mousePressEvent(QMouseEvent *);

    void on_inputDeviceName_editingFinished();

    void on_inputName_editingFinished();

    void on_inputMethodName_editingFinished();

    void on_inputMaterialName_editingFinished();

    void on_inputReagentName_editingFinished();

public slots:

    void showCols();

private:
    Ui::NewProjectBatch *ui;
    QVector<Project> projects;
    QListWidget *listWidget;
    QLineEdit *lineEdit;
    void initRow(QTableWidget *table, int row, Project *project);
    int IsValid(QTableWidget *table,QString name,int col,int row);
    bool IsValid(QTableWidget *table,QString name,int col, QString projectName);
};

#endif // NEWPROJECTBATCH_H
