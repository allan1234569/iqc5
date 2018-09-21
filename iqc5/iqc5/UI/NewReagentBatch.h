#ifndef NEWREAGENTBATCH_H
#define NEWREAGENTBATCH_H


#include <QMainWindow>
#include <QTableWidget>
#include <QListWidget>
#include "Model/Reagent.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QCloseEvent>

namespace Ui {
class NewReagentBatch;
}

class NewReagentBatch : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewReagentBatch(QWidget *parent = 0);
    ~NewReagentBatch();


private slots:
    void InitTree();
    void on_inputKeyword_textChanged(const QString &arg1);

    void reagentName_changed(QString arg1);
    void projectName_changed(QString arg1);
    void manufacturerName_changed(QString arg1);
    void countryName_changed(QString arg1);

    void reagentName_changed();
    void projectName_changed();
    void manufacturerName_changed();
    void countryName_changed();


    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void rowAdd();
    void rowDelete();

    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_pushButton_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    bool eventFilter(QObject*obj,QEvent*event);

    void on_inputReagentName_textChanged(const QString &arg1);

    void on_inputRegisterNo_textChanged(const QString &arg1);

    void on_inputBatchNo_textChanged(const QString &arg1);

    void on_inputCountry_textChanged(const QString &arg1);

    void on_inputMenufacturer_textChanged(const QString &arg1);



    void keyPressEvent (QKeyEvent * keyevent);

    void on_inputReagentName_selectionChanged();

    void on_inputRegisterNo_selectionChanged();

    void on_inputBatchNo_selectionChanged();

    void on_inputCountry_selectionChanged();

    void on_inputMenufacturer_selectionChanged();

    void closeEvent(QCloseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void closeList();


    void on_inputCountry_editingFinished();

    void on_inputMenufacturer_editingFinished();

    void on_inputReagentName_editingFinished();

    void on_inputBatchNo_editingFinished();

    void on_inputRegisterNo_editingFinished();

private:
    Ui::NewReagentBatch *ui;

    QVector<Reagent> reagents;
    QListWidget *listWidget;
    QLineEdit *lineEdit;
    void initRow(QTableWidget *table, int row, Reagent *reagent);
    int IsValid(QTableWidget *table,QString name,int col,int row);
    bool IsValid(QTableWidget *table,QString name,int col, QString ReagentName);
};

#endif // NEWMATERIALBATCH_H


