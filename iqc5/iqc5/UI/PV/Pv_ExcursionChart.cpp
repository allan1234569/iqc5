#include "Pv_ExcursionChart.h"
#include "ui_Pv_ExcursionChart.h"

#include <qwt_plot_marker.h>
#include <qwt_plot_canvas.h>
#include <qwt_symbol.h>
#include <qwt_plot_picker.h>

#include <QDebug>

bool Pv_ExcursionChart::isOpen = false;

Pv_ExcursionChart::Pv_ExcursionChart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pv_ExcursionChart)
{
    ui->setupUi(this);

    isOpen = true;

    initExcursionChar();

}

void Pv_ExcursionChart::Set(double avg, QVector<Axis<double> > &Vec)
{
    average = avg;
    axisVec = Vec;
    initExcursionChar();
}

void Pv_ExcursionChart::GetMaxMinX(QVector<Axis<double> > Vec, double &xMax ,double &xMin)
{
    int max = 0,min = 0;
    double tempMax,tempMin;
    tempMax = Vec[0].x;
    tempMin = Vec[0].x;
    for(int i = 1; i < Vec.count(); i++)
    {
        if(tempMax < Vec[i].x)
        {
            max = i;
            tempMax = Vec[i].x;
        }
        if(tempMin > Vec[i].x)
        {
            tempMin = Vec[i].x;
            min = i;
        }
    }
    xMax = Vec[max].x;
    xMin = Vec[min].x;
}

void Pv_ExcursionChart::GetMaxMinY(QVector<Axis<double> > Vec, double &yMax, double &yMin)
{
    int max = 0,min = 0;
    double tempMax,tempMin;
    tempMax = Vec[0].y;
    tempMin = Vec[0].y;
    for(int i = 0; i < Vec.count(); i++)
    {
        if(tempMax < Vec[i].y)
        {
            tempMax = Vec[i].y;
            max = i;
        }
        if(tempMin > Vec[i].y)
        {
            tempMin = Vec[i].y;
            min = i;
        }
    }
    yMax = Vec[max].y;
    yMin = Vec[min].y;
}

Pv_ExcursionChart::~Pv_ExcursionChart()
{
    delete ui;
}

void Pv_ExcursionChart::initExcursionChar()
{
    setMouseTracking(true);//开启鼠标移动监视

    ui->qwtPlot->setTitle(tr("偏移图"));
    ui->qwtPlot->setAxisTitle(QwtPlot::xBottom,"比较方法");
    ui->qwtPlot->setAxisTitle(QwtPlot::yLeft,"偏倚（实验-比较）");
    ui->qwtPlot->setCanvasBackground(Qt::white);

//    plot->insertLegend( new QwtLegend());//插入图例
//    plot->setAxisScale(QwtPlot::yLeft,-5.0,10.0);
//    plot->setAxisScale(QwtPlot::xBottom,0,500);

    QwtPlotCanvas* canvas = qobject_cast<QwtPlotCanvas*>(ui->qwtPlot->canvas());
    canvas->setFrameStyle(QFrame::Box | QFrame::Plain);
    ui->qwtPlot->setCanvas(canvas);

//    QwtPlotPicker* plotPicker = new QwtPlotPicker(ui->qwtPlot->xBottom, ui->qwtPlot->yLeft, QwtPicker::CrossRubberBand, QwtPicker::AlwaysOn, canvas);
//    QwtPickerMachine* pickerMachine = new QwtPickerClickPointMachine();
//    plotPicker->setStateMachine(pickerMachine);
//    connect(plotPicker, SIGNAL(selected(const QPointF&)), this, SLOT(onSelected(const QPointF&)));

    QwtPlotMarker *idealLine; idealLine= new QwtPlotMarker();
    idealLine->setLabel(tr("理想值"));
    idealLine->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
    idealLine->setLinePen("black",0,Qt::DashLine);
    idealLine->setLineStyle(QwtPlotMarker::HLine);
    idealLine->setYValue(0);
    idealLine->attach(ui->qwtPlot);

    QwtPlotMarker *averageLine; averageLine= new QwtPlotMarker();
    averageLine->setLabel(tr("平均偏移值"));
    averageLine->setLabelAlignment(Qt::AlignRight | Qt::AlignBottom);
    averageLine->setLinePen("blue",0,Qt::SolidLine);
    averageLine->setLineStyle(QwtPlotMarker::HLine);
    averageLine->setYValue(average);
    averageLine->attach(ui->qwtPlot);

    QwtPlotCurve *curve; curve = new QwtPlotCurve();
    curve->setStyle(QwtPlotCurve::Dots);
    curve->setCurveAttribute(QwtPlotCurve::Fitted,true);
    curve->attach(ui->qwtPlot);
    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
                                       QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    curve->setSymbol( symbol );

//    QwtPlotPanner *panner = new QwtPlotPanner(plot->canvas());//坐标平移
//    panner->setOrientations(Qt::Horizontal);

    QPolygonF points;
    updateChart(curve, points);//绘制各个点及重新定义x,y轴的上下限




//    QwtPlotMagnifier *plotMagnifier = new QwtPlotMagnifier(plot->canvas());
//    ui->qwtPlot->resize(ui->chartLayout->geometry().width(),ui->chartLayout->geometry().height());
//    ui->qwtPlot->axisWidget(QwtPlot::xBottom)->setMinBorderDist(0,10);
//    ui->chartLayout->addWidget(plot);
}

void Pv_ExcursionChart::updateChart(QwtPlotCurve *curve, QPolygonF &points)
{

    double xMax,xMin,yMax,yMin;
    GetMaxMinX(axisVec,xMax,xMin);
    GetMaxMinY(axisVec,yMax,yMin);

    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,yMin-1,yMax+1);
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,xMin-10,xMax+10);

    foreach (Axis<double> axis, axisVec) {
        points << QPointF(axis.x,axis.y);
    }
    curve->setSamples(points);//添加点
}

void Pv_ExcursionChart::onSelected(const QPointF &point)
{
    QString info;
    info.append("x=%1,y=%2").arg(QString::number(point.x())).arg(QString::number(point.y()));
    this->setToolTip(info);
//    toolTip->showText(QCursor::pos(),info,0,1000);
}

void Pv_ExcursionChart::closeEvent(QCloseEvent *event)
{
    isOpen = false;
}

void Pv_ExcursionChart::mouseMoveEvent(QMouseEvent *event)
{
//    double fXOffset = 0.0;
//    double fYOffset = 0.0;
//    double fX = ui->qwtPlot->invTransform(QwtPlot::xBottom,event->pos().x()) - fXOffset;
//    double fY = ui->qwtPlot->invTransform(QwtPlot::yLeft,event->pos().y()) - fYOffset;
}
