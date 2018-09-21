#include "setupdialog.h"
#include "ui_setupdialog.h"
#include "global.h"
#include <QUuid>

extern QSettings *settings;

SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupDialog)
{
    ui->setupUi(this);
}

SetupDialog::~SetupDialog()
{
    delete ui;
}

void SetupDialog::saveConfig()
{
    QUuid quuid;
    QString guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");

    settings->setValue(QString("SERVER/ip"),QString(ui->ipLineEdit->text().toUtf8()));
    settings->setValue(QString("SERVER/port"),QString(ui->portLineEdit->text().toUtf8()));
    settings->setValue(QString("DEVICE/DeviceName"),QString(ui->deviceLineEdit->text().toUtf8()));
    settings->setValue(QString("DEVICE/ModelName"),QString(ui->modelLineEdit->text().toUtf8()));
    settings->setValue(QString("DEVICE/BrandName"),QString(ui->brandLineEdit->text().toUtf8()));
    settings->setValue(QString("DEVICE/DeviceId"),guid);
    guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
    settings->setValue(QString("DEVICE/ModelId"),guid);
    guid = quuid.createUuid().toString().replace(QRegularExpression("[{|}]"), "");
    settings->setValue(QString("DEVICE/BrandId"),guid);
}

void SetupDialog::on_okPushButton_clicked()
{
    saveConfig();
    emit on_exit();
    this->close();
}

void SetupDialog::on_cancelPushButton_clicked()
{
    emit on_exit();
    this->close();
}
