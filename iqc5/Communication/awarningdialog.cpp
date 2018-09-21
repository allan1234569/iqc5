#include "awarningdialog.h"
#include "ui_awarningdialog.h"
#include <QMessageBox>

AWarningDialog::AWarningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AWarningDialog)
{
    ui->setupUi(this);
}

AWarningDialog::~AWarningDialog()
{
    delete ui;
}

void AWarningDialog::showMessage(QString &message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
//    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Yes);
    int ret = msgBox.exec();
}
