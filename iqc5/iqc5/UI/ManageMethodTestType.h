#ifndef MANAGEMETHODTESTTYPE_H
#define MANAGEMETHODTESTTYPE_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QCloseEvent>

namespace Ui {
class ManageMethodTestType;
}

class ManageMethodTestType : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManageMethodTestType(QWidget *parent = 0);
    ~ManageMethodTestType();

    void InitTree();
    void InitTestTypeTree();
    void Save();

private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_btnSave_clicked();

    void closeEvent(QCloseEvent* event);

private:
    Ui::ManageMethodTestType *ui;
};

#endif // MANAGEMETHODTESTTYPE_H
