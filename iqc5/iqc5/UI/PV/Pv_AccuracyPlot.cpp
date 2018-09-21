#include "Pv_AccuracyPlot.h"
#include "ui_Pv_AccuracyPlot.h"

#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_symbol.h>

#include <QDesktopWidget>

Pv_AccuracyPlot::Pv_AccuracyPlot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pv_AccuracyPlot)
{
    ui->setupUi(this);
    setWindowTitle(tr("EP9方案-数据作图"));
//    showChart();
//    showDValueChart();
    setFixedSize(QApplication::desktop()->width(),QApplication::desktop()->height());//设置屏幕大小
}

void Pv_AccuracyPlot::showChart()
{
//    QwtPlot *plot = new QwtPlot(this);
//    plot->setTitle(tr("图"));
//    plot->setCanvasBackground(Qt::white);
//    plot->insertLegend( new QwtLegend());

////    QwtPlotGrid *grid;grid = new QwtPlotGrid();
////    grid->attach(plot);
//    plot->resize(ui->AcPlot_Layout2->geometry().width(),ui->AcPlot_Layout2->geometry().height());

//    ui->AcPlot_Layout1->addWidget(plot);
}

void Pv_AccuracyPlot::showDValueChart()
{
//    QwtPlot *plot = new QwtPlot(this);
//    plot->setTitle(tr("方差比差值图"));
//    plot->setCanvasBackground(Qt::white);
//    plot->insertLegend( new QwtLegend());

////    QwtPlotGrid *grid;grid = new QwtPlotGrid();r
////    grid->attach(plot);
//    plot->resize(ui->AcPlot_Layout1->geometry().width(),ui->AcPlot_Layout1->geometry().height());

//    ui->AcPlot_Layout2->addWidget(plot);
}

Pv_AccuracyPlot::~Pv_AccuracyPlot()
{
    delete ui;
}
