#ifndef MANAGEREAGENTTESTTYPE_H
#define MANAGEREAGENTTESTTYPE_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QCloseEvent>

namespace Ui {
class ManageReagentTestType;
}

class ManageReagentTestType : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManageReagentTestType(QWidget *parent = 0);
    ~ManageReagentTestType();

    void InitTree();
    void InitTestTypeTree();
    void Save();

private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_btnSave_clicked();

    void closeEvent(QCloseEvent* event);

    void on_input2_textChanged(const QString &arg1);

private:
    Ui::ManageReagentTestType *ui;
};


#endif // MANAGEREAGENTTESTTYPE_H
