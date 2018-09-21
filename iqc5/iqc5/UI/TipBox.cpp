#include "TipBox.h"
#include "ui_TipBox.h"

#include <QPainter>
#include <QPaintEvent>

TipBox::TipBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TipBox)
{
    ui->setupUi(this);
    setFixedSize(180, 70);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    tip_label = new QLabel(this);
    tip_label->move(1, 16);
    tip_label->setFixedSize(this->width()-2, this->height()-17);
}

TipBox::~TipBox()
{
    delete ui;
}


void TipBox::SetStr(QString text)
{
    tip_label->setText(text);
}

void TipBox::paintEvent(QPaintEvent *)
{
   QLinearGradient linear2(rect().topLeft(), rect().bottomLeft());
   linear2.setColorAt(0, QColor(247, 247, 250));
   linear2.setColorAt(0.5, QColor(240, 242, 247));
   linear2.setColorAt(1, QColor(233, 233, 242));

   QPainter painter2(this);
   painter2.setPen(Qt::black);
   painter2.setBrush(linear2);
   static const QPointF points[8] = {QPointF(15, 0), QPointF(15, 15), QPointF(0, 15), QPointF(0, this->height()-1), QPointF(this->width()-1, this->height()-1), QPointF(this->width()-1, 15),   QPointF(30, 15), QPointF(15, 0)};
   painter2.drawPolygon(points, 8);
}

