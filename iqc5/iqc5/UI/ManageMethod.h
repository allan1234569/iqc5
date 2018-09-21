#ifndef MANAGEMETHOD_H
#define MANAGEMETHOD_H
#include "Model/Method.h"
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QCloseEvent>

namespace Ui {
class ManageMethod;
}

class ManageMethod : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManageMethod(QWidget *parent = 0);
    ~ManageMethod();
    void SearchTree(QString name);
    void ShowAllData();
    void ShowAllData(QString subjectId,QString categoryId, QString name);

private slots:
    void on_btnCancel_clicked();

    void on_btnAdd_clicked();

    void OnBtnTableEditClicked();
    void OnBtnTableDeleteClicked();

    void on_btnSearch_clicked();

    void on_inputSubject_currentIndexChanged(int index);

    void on_inputKeyword_textChanged(const QString &arg1);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void closeEvent(QCloseEvent* event);

private:
    Ui::ManageMethod *ui;
    QVector<Method> model;
};
#endif // MANAGEMETHOD_H
