#include "PopBox.h"
#include "ui_popbox.h"

PopBox::PopBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PopBox)
{
    ui->setupUi(this);
}

PopBox::~PopBox()
{
    delete ui;
}

void PopBox::SetText(QString text)
{
    ui->txtMsg->setText(text);
}
