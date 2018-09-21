#ifndef CIRCLEVIEW_H
#define CIRCLEVIEW_H

#include <qwidget.h>
#include <qpainter.h>
#include "Model/Result.h"

class CircleView : public QWidget
{
public:
    QVector <QVector< QVector<Result> > > datas;

public:
    CircleView();
    void paint(QVector <QVector< QVector<Result> > > data, double add);

    double add;

protected:
        void paintEvent(QPaintEvent *event);
        void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // CIRCLEVIEW_H
