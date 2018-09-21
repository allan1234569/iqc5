#ifndef NEWMATERIALBATCH_H
#define NEWMATERIALBATCH_H

#include <QMainWindow>
#include <QTableWidget>
#include <QListWidget>
#include "Model/Material.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QCloseEvent>

namespace Ui {
class NewMaterialBatch;
}

class NewMaterialBatch : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewMaterialBatch(QWidget *parent = 0);
    ~NewMaterialBatch();


private slots:
    void InitTree();
    void on_inputKeyword_textChanged(const QString &arg1);

    void materialName_changed(QString arg1);
    void manufacturerName_changed(QString arg1);
    void countryName_changed(QString arg1);

    void materialName_changed();
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

    void on_inputMaterialName_textChanged(const QString &arg1);

    void on_inputRegisterNo_textChanged(const QString &arg1);

    void on_inputBatchNo_textChanged(const QString &arg1);

    void on_inputCountry_textChanged(const QString &arg1);

    void on_inputMenufacturer_textChanged(const QString &arg1);



    void keyPressEvent (QKeyEvent * keyevent);

    void on_inputMaterialName_selectionChanged();

    void on_inputRegisterNo_selectionChanged();

    void on_inputBatchNo_selectionChanged();

    void on_inputCountry_selectionChanged();

    void on_inputMenufacturer_selectionChanged();

    void closeEvent(QCloseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void closeList();


    void on_inputCountry_editingFinished();

    void on_inputMenufacturer_editingFinished();

    void on_inputMaterialName_editingFinished();

    void on_inputBatchNo_editingFinished();

    void on_inputRegisterNo_editingFinished();

private:
    Ui::NewMaterialBatch *ui;

    QVector<Material> materials;
    QListWidget *listWidget;
    QLineEdit *lineEdit;
    void initRow(QTableWidget *table, int row, Material *material);
    int IsValid(QTableWidget *table,QString name,int col,int row);
    bool IsValid(QTableWidget *table,QString name,int col, QString MaterialName);
};

#endif // NEWMATERIALBATCH_H
