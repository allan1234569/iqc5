#include "Pv_TextBrowser.h"
#include "ui_Pv_TextBrowser.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>

Pv_TextBrowser::Pv_TextBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pv_TextBrowser)
{
    setWindowTitle(tr("实验要求"));
    ui->setupUi(this);
    setFixedSize(800,600);
    ui->textBrowser->installEventFilter(this);
}

void Pv_TextBrowser::setHtml(const QString &html)
{
    ui->textBrowser->setHtml(html);
}

Pv_TextBrowser::~Pv_TextBrowser()
{
    delete ui;
}

void Pv_TextBrowser::keyPressEvent(QKeyEvent *event)
{//什么都不做，屏弊键盘

}
