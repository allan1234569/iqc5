#ifndef INPUTDATAMULTI_H
#define INPUTDATAMULTI_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QEvent>
#include <QCloseEvent>

namespace Ui {
class InputDataMulti;
}

class InputDataMulti : public QMainWindow
{
    Q_OBJECT

public:
    explicit InputDataMulti(QWidget *parent = 0);
    ~InputDataMulti();

private slots:
    void on_btnClose_clicked();

    void on_btnSave_clicked();

    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_dateEdit_dateChanged(const QDate &date);

    void on_spinBox_valueChanged(int arg1);

    bool eventFilter(QObject*obj,QEvent*event);

    void on_inputKeyword_textChanged(const QString &arg1);

    void rowAdd();
    void rowDelete();

    void closeEvent(QCloseEvent* event);

private:
    Ui::InputDataMulti *ui;
    void Init();
    void InitTree();

};

#endif // INPUTDATAMULTI_H
