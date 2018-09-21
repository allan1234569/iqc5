#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>
#include <QSettings>

#include "mythread.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    setWindowTitle(QString(""));
    ui->setupUi(this);
    this->setFixedSize(400,300);
    this->setWindowTitle("");
    init();

    stackedLayout = new QStackedLayout;
    interface = NULL;
    lis = new Lis;
    type = DIRECTORY;


    selectDirectoryBtn = new QPushButton(tr("请选择目录"),this);
    connect(selectDirectoryBtn,SIGNAL(clicked()),
            this,SLOT(selectDirectoryBtn_clicked()));

    selectFileBtn = new QPushButton(tr("请选择文件"),this);
    connect(selectFileBtn,SIGNAL(clicked()),
            this,SLOT(selectFileBtn_clicked()));

    stackedLayout->addWidget(selectDirectoryBtn);
    stackedLayout->addWidget(selectFileBtn);
    ui->horizontalLayout->addLayout(stackedLayout);

    connect(this,SIGNAL(canImport()),this,SLOT(import()));
}

Widget::~Widget()
{
    delete ui;
    delete lis;
}


void Widget::init()
{
    RetrievePlugins();
    ui->comboBox->setCurrentIndex(0);
}

void Widget::RetrievePlugins()
{
    comboxIndex.clear();
    QDir pluginsDir = directoryOf(QDir::currentPath().append("/plugins/lis"));


    QMap<QString,QString> subMap;
    int count = 1;
    foreach (QString strPluginName, pluginsDir.entryList(QDir::Files)) {
        lib.setFileName(QDir::currentPath().append("/plugins/lis/")+strPluginName);

        if (lib.load())
        {
            // 解析导出函数
            CreateInterfaceFunc createinterface =
                    (CreateInterfaceFunc) lib.resolve("CreateInterface");
            ReleaseInterfaceFunc releaseinterface =
                    (ReleaseInterfaceFunc) lib.resolve("ReleaseInterface");

            if (createinterface && releaseinterface)
            {
                // 创建Interface对象
                LisInterface * lisInterface = createinterface();
                if (lisInterface)
                {
                    // 使用插件功能
                    if(!lisInterface->InterfaceName().isNull())
                    {
                        qDebug() << "strPluginName: " << strPluginName;
                        qDebug() << "interfaceName: " << lisInterface->InterfaceName();

                        subMap.insert(PLUGIN_NAME,strPluginName);
                        subMap.insert(PLUGIN_DESCRIPTION,lisInterface->InterfaceName());
                        comboxIndex.insert(count,subMap);
                        count++;
                    }

                    // 插件使用完毕，删除对象
                    releaseinterface(lisInterface);
                }
            }
            // 卸载插件
            lib.unload();
        }
        else
        {
            qDebug() << "Dll load failed!";
        }
    }

    for(int i = 0; i < comboxIndex.count(); i++)
    {
        ui->comboBox->insertItem(i,comboxIndex[i][PLUGIN_DESCRIPTION]);
    }
}

QDir Widget::directoryOf(const QString &subdir)
{
    QDir dir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug"
            || dir.dirName().toLower() == "release")
        dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS") {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    dir.cd(subdir);
    return dir;
}

bool Widget::checkFiles(QFileInfoList &fileList)
{
    QStringList testFilelist;

    testFilelist = interface->readSetting();

    foreach (QString f, testFilelist) {
        qDebug() << f;
    }

    QString loseFile = "";
    foreach (QString filename, testFilelist) {
        bool fExist = false;
        foreach (QFileInfo f, fileList) {
           if(f.fileName().contains(filename))
           {
               fExist = true;
               continue;
           }
        }
        if(!fExist)
        {
            loseFile.append(filename + ",");
        }
    }

    if( !loseFile.isEmpty() )
    {
        loseFile = loseFile.left(loseFile.lastIndexOf(","));
        QMessageBox::critical(this, QString("错误"),
                         QString("找不到文件 %1,导入失败！！！").arg(loseFile),
                         QMessageBox::Ok
                         | QMessageBox::Cancel,
                         QMessageBox::Ok);
        return false;
    }

    return true;
}

bool Widget::check()
{
    setWindowTitle(QString("解压完成！"));
    qDebug() << "out_path: " << out_path;
    QDir *dir=new QDir(out_path);
    QStringList filter;
    filter<<"*";
    fileInfoList = dir->entryInfoList(filter);

    if(checkFiles(fileInfoList))
    {
        dir_path = out_path;
        emit canImport();
        qDebug() << "check emit canImport";
    }
    else
    {
        setBtnEnable(true);
    }

    sender()->deleteLater();
}

void Widget::import()
{
    qDebug() << "import";
    lis->data->clear();
    if(interface)
    {
        interface->readSetting();
        lis->data = interface->getData(dir_path);
        qDebug() << "lis->data->materialBatchVec.count(): " << lis->data->materialBatchVec.count();
        qDebug() << "lis->data->materialVec.count(): " << lis->data->materialVec.count();
        qDebug() << "lis->data->projectVec.count(): " << lis->data->projectVec.count();
        qDebug() << "lis->data->projectDetailVec.count(): " << lis->data->projectDetailVec.count();
        qDebug() << "lis->data->resultVec.count(): " << lis->data->resultVec.count();
        qDebug() << "lis->data->testTypeVec: " << lis->data->testTypeVec.count();
        if(lis->data->isNull())
        {
            qDebug() << "Lis->data is null!";
        }
        else
        {
            myThread *thread = new myThread;
            connect(thread,SIGNAL(importCompleted()),this,SLOT(completeImport()));
            thread->lis = lis;
            thread->start();
            setWindowTitle(QString("正在导入数据库，请稍后。。。"));
        }
    }
}

void Widget::completeImport()
{
    setWindowTitle(QString("成功导入数据库！"));
    setBtnEnable(true);
}

//bool Widget::checkFiles()
//{
//    QStringList fileList;
//    extract(ui->lineEdit->text(),fileList);

//    QStringList testFilelist;

//    testFilelist = interface->readSetting();
//    foreach (QString f, testFilelist) {
//        qDebug() << f;
//    }

//    QString loseFile = "";
//    foreach (QString filename, testFilelist) {
//        bool fExist = false;
//        foreach (QString f, fileList) {
//           if(f.contains(filename))
//           {
//               fExist = true;
//               continue;
//           }
//        }
//        if(!fExist)
//        {
//            loseFile.append(filename + ",");
//        }
//    }

//    if( !loseFile.isEmpty() )
//    {
//        QMessageBox::critical(this, QString("错误"),
//                         QString("文件 %1丢失,导入失败！！！").arg(loseFile),
//                         QMessageBox::Ok
//                         | QMessageBox::Cancel,
//                         QMessageBox::Ok);
//        return false;
//    }

//    return true;
//}

QString Widget::GetDirectory()
{
    QString path=QFileDialog::getExistingDirectory(NULL, QString("选择文件夹"),"..\\bin\\",QFileDialog::ShowDirsOnly);
    QDir *dir=new QDir(path);
    QStringList filter;
    filter<<"*";

    fileInfoList = dir->entryInfoList(filter);
//    QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
//    foreach (QFileInfo f, fileInfoList) {
//        qDebug() << f.fileName();
//    }

    return path;
}

QString Widget::GetFile() const
{
    return  QFileDialog::getOpenFileName(NULL,QString("选择文件"),"..\\bin\\","*.zip");
}

void Widget::on_selectDirectoryRadioBtn_clicked()
{
    stackedLayout->setCurrentIndex(0);
    type = DIRECTORY;
}

void Widget::on_selectFileRadioBtn_clicked()
{
    stackedLayout->setCurrentIndex(1);
    type = FILE;
}

void Widget::on_cancleBtn_clicked()
{
    this->close();
}

void Widget::on_importBtn_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("警告");
        msgBox.setInformativeText("请选择文件或目录!!!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    if(!interface)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("警告");
        msgBox.setInformativeText("请选系统!!!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    out_path = QString("./temp/");
    if(type == DIRECTORY)
    {
        setBtnEnable(false);
        if( !checkFiles(fileInfoList) )
        {
            setBtnEnable(true);
            setWindowTitle(QString("导入失败！！！"));
            return;
        }
        else
        {
            dir_path = ui->lineEdit->text();
        }
        emit canImport();
        qDebug() << "canImport";
    }
    else if(type == FILE)
    {
        setBtnEnable(false);
        myThread *thread = new myThread;
        connect(thread,SIGNAL(unCompressCompleted()),this,SLOT(check()));

        thread->in_path = ui->lineEdit->text();
        thread->out_path = out_path;
        thread->start();
        setWindowTitle(QString("正在解压文件，请等待。。。"));
    }


}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0)
        return;
    if(!lib.isLoaded())
    {
        qDebug() << "Not Loaded!!!";
        lib.setFileName(QDir::currentPath().append("/plugins/lis/")+comboxIndex[index][PLUGIN_NAME]);
        LoadPlugin();
    }
    else
    {
        qDebug() << "Is loaded!!!";
        if(interface)
        {
            ReleaseInterface();
        }
        lib.unload();
        lib.fileName().clear();
        lib.setFileName(QDir::currentPath().append("/plugins/lis/")+comboxIndex[index][PLUGIN_NAME]);
        LoadPlugin();
    }
}

void Widget::selectDirectoryBtn_clicked()
{
    QString path = GetDirectory();
    ui->lineEdit->setText(path);
}

void Widget::selectFileBtn_clicked()
{
    QString filepath = GetFile();
    ui->lineEdit->setText(filepath);
}

void Widget::LoadPlugin()
{
    if (lib.load())
    {
        // 解析导出函数
        CreateInterfaceFunc createinterface =
                (CreateInterfaceFunc) lib.resolve("CreateInterface");
//        ReleaseInterfaceFunc releaseinterface =
//                (ReleaseInterfaceFunc) lib.resolve("ReleaseInterface");

        if (createinterface) /* && releaseinterface)*/
        {
            interface = createinterface();  // 创建LisInterface对象
            if(interface)
            {

            }
        }
    }
    else
    {
        QMessageBox msg;
        msg.setText(QString("Dll load Faild!!!"));
        msg.exec();
    }
}

void Widget::ReleaseInterface()
{
    if(lib.isLoaded())
    {
        ReleaseInterfaceFunc releaseinterface =
                (ReleaseInterfaceFunc) lib.resolve("ReleaseInterface");

        releaseinterface(interface);
    }
}

bool Widget::extract(const QString& in_file_path, const QString &out_file_path)
{
//    QuaZip archive(in_file_path);
//    if (!archive.open(QuaZip::mdUnzip))
//        return false;

////    QString out_file_path = QString("./temp/");
////    if (!path.endsWith("/") && !out_file_path.endsWith("\\"))
////        path += "/";

//    QDir dir(out_file_path);
//    if (!dir.exists())
//        dir.mkpath(out_file_path);


//    for( bool f = archive.goToFirstFile(); f; f = archive.goToNextFile() )
//    {
//        QString filePath = archive.getCurrentFileName();
//        qDebug() << filePath;
//    }

//    for( bool f = archive.goToFirstFile(); f; f = archive.goToNextFile() )
//    {
//        QString filePath = archive.getCurrentFileName();
//        QuaZipFile zFile(archive.getZipName(), filePath);
//        zFile.open(QIODevice::ReadOnly );
//        QByteArray ba;
//        if(zFile.size() > MAX_SIZE)
//        {

//            if (filePath.endsWith("/"))
//            {
//                dir.mkpath(filePath);
//            }
//            else
//            {
//                QFile dstFile(out_file_path + filePath);
//                if (!dstFile.open(QIODevice::WriteOnly))
//                    return false;

//                while( !zFile.atEnd() )
//                {
//                    ba = zFile.read(MAX_SIZE);
//                    dstFile.write(ba);
//                }

//                dstFile.close();
//            }
//        }
//        else
//        {
//            ba.append(zFile.readAll());
//            QFile dstFile(out_file_path + filePath);
//            if (!dstFile.open(QIODevice::WriteOnly) )
//                return false;
//            dstFile.write(ba);
//            dstFile.close();
//        }

//        zFile.close();
//    }
    return true;
}

void Widget::setBtnEnable(bool flag)
{
    ui->selectDirectoryRadioBtn->setEnabled(flag);
    ui->selectFileRadioBtn->setEnabled(flag);
    ui->importBtn->setEnabled(flag);
    ui->comboBox->setEnabled(flag);
    ui->lineEdit->setEnabled(flag);
    this->selectDirectoryBtn->setEnabled(flag);
    this->selectFileBtn->setEnabled(flag);
}
