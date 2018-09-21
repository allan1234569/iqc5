#include "Background.h"


Background::Background(double avg, double sd)
{
    setZ(0.0);
    this->avg = avg;
    this->sd = sd;
}

void Background::draw( QPainter *painter,
    const QwtScaleMap &, const QwtScaleMap &yMap,
    const QRectF &canvasRect ) const
{
    QColor c = QColor(220,220,220);
    QRectF r = canvasRect;

    for(int i = 0; i < 5; i++)
    {
        r.setBottom(yMap.transform(avg+i*sd));
        r.setTop(yMap.transform(avg+(i+1)*sd));
        painter->fillRect(r,c);

        r.setBottom(yMap.transform(avg-(i+1)*sd));
        r.setTop(yMap.transform(avg-i*sd));
        painter->fillRect(r,c);

        c = QColor(c.red()+5*i,c.green()+5*i,c.blue()+5*i);
    }


}
