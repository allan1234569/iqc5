#ifndef MANAGEDEVICE_H
#define MANAGEDEVICE_H
#include "Model/Device.h"
#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QCloseEvent>

namespace Ui {
class ManageDevice;
}

class ManageDevice : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ManageDevice(QWidget *parent = 0);
    ~ManageDevice();

    void ShowAllData();
    void SearchTree(QString name);
    void ShowAllData(QString modelId, QString name);

private slots:

    void on_btnAdd_clicked();

    void OnBtnTableEditClicked();
    void OnBtnTableDeleteClicked();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_inputKeyword_textChanged(const QString &arg1);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void showEvent(QShowEvent *);

    void closeEvent(QCloseEvent* event);

private:
    Ui::ManageDevice *ui;
    QVector<Device> model;
};

#endif // MANAGEDEVICE_H
