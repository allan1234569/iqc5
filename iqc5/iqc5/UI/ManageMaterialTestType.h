#ifndef MANAGEMATERIALTESTTYPE_H
#define MANAGEMATERIALTESTTYPE_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QCloseEvent>

namespace Ui {
class ManageMaterialTestType;
}

class ManageMaterialTestType : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManageMaterialTestType(QWidget *parent = 0);
    ~ManageMaterialTestType();

    void InitTree();
    void InitTestTypeTree();
    void Save();

private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_btnSave_clicked();

    void closeEvent(QCloseEvent* event);

private:
    Ui::ManageMaterialTestType *ui;
};

#endif // MANAGEMATERIALTESTTYPE_H
