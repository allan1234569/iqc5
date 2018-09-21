#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QFileInfoList>
#include <QStackedLayout>
#include <QDir>
#include <QMap>
#include <QLibrary>

#include "lisinterface.h"
#include "lis.h"

#define PLUGIN_NAME "pluginName"
#define PLUGIN_DESCRIPTION "interfaceName"


// 定义插件中的两个导出函数的原型
typedef LisInterface *(*CreateInterfaceFunc)();
typedef void (*ReleaseInterfaceFunc)(LisInterface *interface);

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    enum TYPE
    {
        FILE,
        DIRECTORY
    };

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    void init();
    void RetrievePlugins();
    QDir directoryOf(const QString &subdir);

    bool checkFiles(QFileInfoList &fileList);
    QString GetDirectory();
    QString GetFile() const;
    bool extract(const QString& in_file_path, const QString &out_file_path);
    void setBtnEnable(bool flag);
signals:
    void canImport();
protected slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_selectDirectoryRadioBtn_clicked();
    void on_selectFileRadioBtn_clicked();
    void on_cancleBtn_clicked();
    void on_importBtn_clicked();

    void selectDirectoryBtn_clicked();
    void selectFileBtn_clicked();
    void LoadPlugin();
    void ReleaseInterface();

    bool check();
    void import();
    void completeImport();

private:
    Ui::Widget *ui;
    QStackedLayout *stackedLayout;
    QPushButton *selectDirectoryBtn;
    QPushButton *selectFileBtn;
    QFileInfoList fileInfoList;
    QMap<int,QMap<QString, QString> > comboxIndex;
    QLibrary lib;
    LisInterface * interface;
    Lis *lis;
    TYPE type;
    QString out_path;
    QString dir_path;

};

#endif // WIDGET_H
