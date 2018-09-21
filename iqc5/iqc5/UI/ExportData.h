#ifndef EXPORTDATA_H
#define EXPORTDATA_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QAxObject>
#include <QAxWidget>
#include <QThread>

class ExportData_Thread : public QThread
{
    Q_OBJECT
public:
    explicit ExportData_Thread(QObject *parent = 0);

    void setItems(QVector<QString> items);

    void setFilename(QString filename);

signals:

public slots:


    // QThread interface
protected:
    void run();

private:
    QVector<QString> m_Items;  //项目缓存区，格式：项目名,项目Id

    QString m_filename;
};
namespace Ui {
class ExportData;
}

class ExportData : public QWidget
{
    Q_OBJECT

public:
    explicit ExportData(QWidget *parent = 0);
    ~ExportData();

    void initProject();

private slots:
    void on_export_Btn_clicked();

    void on_cancel_Btn_clicked();

    void on_checkBox_clicked(bool checked);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    void updateItemList(QString ProjcetId, QString ProjectName, bool remove);

    void dealItems();

private:
    Ui::ExportData *ui;

    QVector<QString> m_ExportData;  //保存项目名,项目ID

    ExportData_Thread *thread;
};

#endif // EXPORTDATA_H
