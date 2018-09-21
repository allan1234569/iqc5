#ifndef PV_EXCURSIONCHART_H
#define PV_EXCURSIONCHART_H

#include <QDialog>
#include <QToolTip>

#include "Common/Axis.h"
#include <QMouseEvent>
#include <qwt_plot_curve.h>


namespace Ui {
class Pv_ExcursionChart;
}

class Pv_ExcursionChart : public QDialog
{
    Q_OBJECT

public:
    static bool isOpen;
    explicit Pv_ExcursionChart(QWidget *parent = 0);
    void Set(double avg, QVector< Axis<double> >&Vec);
    void GetMaxMinX(QVector<Axis<double> > Vec, double &xMax, double &xMin);
    void GetMaxMinY(QVector<Axis<double> > Vec, double &yMax, double &yMin);

    ~Pv_ExcursionChart();

    void initExcursionChar();
public slots:
    void updateChart(QwtPlotCurve *curve, QPolygonF &points);
    void onSelected(const QPointF& point);

protected:
    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    Ui::Pv_ExcursionChart *ui;
    double average;
    QVector< Axis<double> >axisVec;

};

#endif // PV_EXCURSIONCHART_H
