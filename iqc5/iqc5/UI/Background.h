#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_picker.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qwt_text_label.h>
#include <qwt_math.h>
#include <qwt_symbol.h>

class Background: public QwtPlotItem
{
private:
    double avg;
    double sd;
public:
    Background(double avg, double sd);

    virtual int rtti() const
    {
        return QwtPlotItem::Rtti_PlotUserItem;
    }

    virtual void draw( QPainter *painter, const QwtScaleMap &, const QwtScaleMap &yMap,
        const QRectF &canvasRect) const;

};
#endif // BACKGROUND_H
