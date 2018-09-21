#ifndef MANAGETYPE_H
#define MANAGETYPE_H
#include "Model/TestType.h"
#include "Model/TestParam.h"
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QCloseEvent>

namespace Ui {
class ManageType;
}

class ManageType : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ManageType(QWidget *parent = 0);
    ~ManageType();

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

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_inputKeyword_textChanged(const QString &arg1);

    void closeEvent(QCloseEvent* event);

private:
    Ui::ManageType *ui;
    QVector<TestType> model;
};

#endif // MANAGETYPE_H
