#ifndef MANAGEMATERIAL_H
#define MANAGEMATERIAL_H
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMainWindow>
#include <QListWidget>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QString>

namespace Ui {
class ManageMaterial;
}

class ManageMaterial : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManageMaterial(QWidget *parent = 0);
    ~ManageMaterial();
    void InitTree();
    void ShowAllData();
    void ShowAllData(QString subjectId, QString categoryId, QString name, QString Manufacturer, QString country, QString registerNo, QString batchNo);

private slots:
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
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
    void closeEvent(QCloseEvent *event);
    void on_btnAdd_clicked();

    void mousePressEvent(QMouseEvent *);

    void on_inputCountry_editingFinished();

    void on_inputManufacturer_editingFinished();

    void on_inputName_editingFinished();

    void on_inputCountry_selectionChanged();

    void on_inputManufacturer_selectionChanged();

    void on_inputName_selectionChanged();

    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::ManageMaterial *ui;
    QListWidget *listWidget;
    QLineEdit *lineEdit;
};

#endif // MANAGEMATERIAL_H
