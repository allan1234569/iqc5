#include "configureform.h"
#include "ui_configureform.h"
#include "global.h"
#include <QFileDialog>

//QSettings *setting;

configureForm::configureForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::configureForm)
{
    ui->setupUi(this);
    setFixedSize(320,240);
    setWindowTitle(tr("设置"));
    QString port = setting->value(QString("SETTINGS/port")).toString();
    QString dir = setting->value(QString("SETTINGS/logDir")).toString();

    ui->listenPortLineEdit->setText(port);
    ui->listenDirectoryLineEdit->setText(dir);
}

configureForm::~configureForm()
{
    delete ui;
}

void configureForm::on_confirmButton_clicked()
{
    apply_settings();
    this->close();
}

void configureForm::on_cancelButton_clicked()
{
    this->close();
}

void configureForm::apply_settings()
{
    setting->setValue(QString("SETTINGS/port"),ui->listenPortLineEdit->text());
    setting->setValue(QString("SETTINGS/logDir"),ui->listenDirectoryLineEdit->text());
}

void configureForm::on_selectButton_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this,tr("选择目录"),tr("./"));
    ui->listenDirectoryLineEdit->setText(dirPath);
}
