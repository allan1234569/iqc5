#ifndef MANAGEREAGENT_H
#define MANAGEREAGENT_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QListWidget>
#include <QKeyEvent>
#include <QCloseEvent>
class Reagent;

namespace Ui {
class ManageReagent;
}


class ManageReagent : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ManageReagent(QWidget *parent = 0);
    ~ManageReagent();
    void InitTree();
    void ShowAllData();
    void ShowAllData(QString subjectId, QString categoryId, QString name, QString Manufacturer, QString Country,QString registerNo, QString batchNo);
    
private slots:
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_btnAdd_clicked();

    void OnBtnTableEditClicked();
    void OnBtnTableDeleteClicked();

    void on_btnSearch_clicked();

    void on_inputKeyword_textChanged(const QString &arg1);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_inputSubject_currentIndexChanged(int index);


    void on_btnClose_clicked();

    void on_inputCountry_textChanged(const QString &arg1);

    void on_inputManufacturer_textChanged(const QString &arg1);

    void on_inputName_textChanged(const QString &arg1);


    void keyPressEvent (QKeyEvent * keyevent);

    void closeEvent(QCloseEvent* event);

    void mousePressEvent(QMouseEvent *);

    void on_inputCountry_editingFinished();

    void on_inputManufacturer_editingFinished();

    void on_inputName_editingFinished();

    void on_inputCountry_selectionChanged();

    void on_inputManufacturer_selectionChanged();

    void on_inputName_selectionChanged();

    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::ManageReagent *ui;
    QVector<Reagent> model;
    QListWidget *listWidget;
    QLineEdit *lineEdit;

};

#endif // MANAGEREAGENT_H
