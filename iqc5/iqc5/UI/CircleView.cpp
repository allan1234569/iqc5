#include "CircleView.h"
#include <math.h>
#include <QDebug>
#include "Service/ProjectService.h"

CircleView::CircleView()
{
}

void CircleView::paintEvent(QPaintEvent *event)
{
    int width = this->width();
    int height = this->height();
    int r = (width<height ? width : height) - 40;

    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));


    //画渐变圆
    double circleMum=11;

    for(double i=11;i>=1;i--)
    {
        if(i==6) //均值
        {
            painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        }
        else if(i==5 || i==7)  //1s
        {
            painter.setPen(QPen(Qt::black, 1, Qt::DotLine));
        }
        else if(i==6 || i==8)  //2s
        {
            painter.setPen(QPen(QColor(255,128,64,255), 1, Qt::SolidLine));
        }
        else  //3s
        {
            painter.setPen(QPen(Qt::red, 1, Qt::SolidLine));
        }
        painter.setBrush(QBrush(QColor(180+10*(fabs(i-6)),180+10*(fabs(i-6)),180+10*(fabs(i-6)),255),Qt::SolidPattern));
        painter.drawEllipse(QPointF(width/2, height/2), r/circleMum*i/2, r/circleMum*i/2);

    }


    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));

    //标标准差注释
    for(int i=1;i<=11;i++)
    {
        if(i-6>=0)
        {
            painter.drawText(QRectF(width/2-15,  height/2 - r/circleMum*i/2 - 5, 50,20), QString(" %1").arg(i-6));
            painter.drawText(QRectF(width/2-15,  height/2 + r/circleMum*i/2 - 5, 50,20), QString(" %1").arg(i-6));
            painter.drawText(QRectF(width/2 - r/circleMum*i/2 -8,  height/2 , 50,20), QString(" %1").arg(i-6));
            painter.drawText(QRectF(width/2 + r/circleMum*i/2 -8,  height/2, 50,20), QString(" %1").arg(i-6));

        }
        else
        {
            painter.drawText(QRectF(width/2-15,  height/2 - r/circleMum*i/2 - 5, 50,20), QString("%1").arg(i-6));
            painter.drawText(QRectF(width/2-15,  height/2 + r/circleMum*i/2 - 5, 50,20), QString("%1").arg(i-6));
            painter.drawText(QRectF(width/2 - r/circleMum*i/2 -8,  height/2, 50,20), QString("%1").arg(i-6));
            painter.drawText(QRectF(width/2 + r/circleMum*i/2 -8,  height/2, 50,20), QString("%1").arg(i-6));
        }
    }


    //画线

    int NUM = datas[0][0].count();
    double angle = 2*M_PI / NUM;
    for(int i=0;i<NUM; i++)
    {
        painter.drawLine(width/2, height/2, width/2 + r*cos(i*angle)/2, height/2 + r*sin(i*angle)/2);

        //标项目注释
        painter.drawText(QRectF(width/2 + (r+30)*cos(i*angle)/2, height/2 + (r+30)*sin(i*angle)/2 - 5, 50,20), QString("%1").arg(datas[0][0][i].Memo));
    }

    //画曲线
    painter.setPen(QPen(Qt::black, 1.5));

    double x[NUM + 1];
    double y[NUM + 1];

    QColor colors[] = {Qt::darkGreen,Qt::blue,QColor(11,68,54),Qt::darkBlue,Qt::darkCyan,Qt::darkMagenta,Qt::darkYellow};

    QVector< QVector<Result> > dayData = datas[0];
    for(int level=0;level<dayData.count();level++)
    {
        QVector<Result> oneLevelData = dayData[level];

        for(int j=0; j<oneLevelData.count();j++)
        {
            //画每天的圆(每个圆有oneLevelData.count个数据)
            for(int i=0;i<NUM; i++)
            {
                x[0] = oneLevelData[i].value * cos(i*angle);
                y[0] = oneLevelData[i].value * sin(i*angle);

                x[1] = oneLevelData[(i+1)%NUM].value * cos(((i+1)%NUM)*angle);
                y[1] = oneLevelData[(i+1)%NUM].value * sin(((i+1)%NUM)*angle);

                painter.setPen(QPen(colors[level], 2, Qt::SolidLine));
                painter.drawLine(width/2+ x[0]/circleMum*(r/2),height/2+ y[0]/circleMum*(r/2),  width/2+x[1]/circleMum*(r/2), height/2+y[1]/circleMum*(r/2));

            }
        }
    }


    painter.end();
}

void CircleView::paint(QVector <QVector< QVector<Result> > > data, double add)
{
    datas = data;
    this->add = add;
    this->repaint();
}

void CircleView::mouseDoubleClickEvent(QMouseEvent *event)
{

    CircleView *c = new CircleView();
    c->paint(datas, this->add);
    c->show();

}
