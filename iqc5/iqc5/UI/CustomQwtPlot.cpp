#include "CustomQwtPlot.h"
#include "ui_CustomQwtPlot.h"
#include "ProjectService.h"
#include "CategoryService.h"
#include "ChartView.h"
#include "TableView.h"
#include <QCheckBox>
#include <QMessageBox>
#include <QFileDialog>
#include "ProjectDataSheet.h"
#include "Background.h"

CustomQwtPlot::CustomQwtPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomQwtPlot)
{
    ui->setupUi(this);

    IfCaculate = ui->IfCaculate;
    IfCustum = ui->IfCustum;
    txtAvg = ui->txtAvg;
    txtSd = ui->txtSd;
    txtCV = ui->txtCV;
    txt6sigma = ui->txt6sigma;
    inputCustAvg = ui->inputCustAvg;
    inputCustSD = ui->inputCustSD;
    txtCustCV = ui->txtCustCV;
    txtCust6sigma = ui->txtCust6sigma;
    inputStartDate = ui->inputStartDate;
    inputEndDate = ui->inputEndDate;
    txtN = ui->txtN;
    widget_4 = ui->widget_4;
    btnCaculate = ui->btnCaculate;
    btnInit = ui->btnInit;

    m_bAllShow = false;

    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255,255,255));
    setPalette(palette);

    SetTitle("");
    SetFooter("");
}

CustomQwtPlot::~CustomQwtPlot()
{
    delete ui;
}

QwtPlot* CustomQwtPlot::getChart()
{
    return ui->qwtPlot;
}

void CustomQwtPlot::SetTitle(QString str)
{

    ui->txtTitle->setText(str);
    if(str == "")
    {
        ui->widget_title->setHidden(true);
    }
    else
    {
        ui->widget_title->setHidden(false);
    }
}
void CustomQwtPlot::SetFooter(QString str)
{
    ui->txtFooter->setText(str);
    if(str == "")
    {
        ui->widget_footer->setHidden(true);
    }
    else
    {
        ui->widget_footer->setHidden(false);
    }
}


void CustomQwtPlot::DrawLjChart(QwtPlot *chart, int level, double avg, double s, double min, double max, QVector<Result> data)
{
    chart->detachItems(QwtPlotItem::Rtti_PlotItem, false);

    chart->canvas()->installEventFilter(this);

    QColor colors[] = {Qt::darkGreen,Qt::blue,QColor(11,68,54),Qt::darkBlue,Qt::darkCyan,Qt::darkMagenta,Qt::darkYellow};
    //设置坐标轴标题
    chart->setAxisTitle(chart->xBottom, tr(""));//测试值
    chart->setAxisTitle(chart->yLeft, tr(""));//质控限

    chart->insertLegend(new QwtLegend(), QwtPlot::RightLegend);

    QwtPlotCanvas *plotCanvas = qobject_cast<QwtPlotCanvas *>(chart->canvas());
    plotCanvas->setFrameStyle(QFrame::Box | QFrame::Plain);
    plotCanvas->setLineWidth(1);
    plotCanvas->setPalette(Qt::white);
    chart->setCanvas(plotCanvas);

    for (int i = 0; i < chart->axisCnt; i++)
    {
        QwtScaleWidget *scaleWidget = chart->axisWidget(i);
        if (scaleWidget)
        {
            scaleWidget->setMargin(1);
        }
        QwtScaleDraw *scaleDraw = chart->axisScaleDraw(i);
        if (scaleDraw)
        {
            scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
        }

    }
    chart->plotLayout()->setAlignCanvasToScales(true);

    //上下限
    int count = data.count();
    min = min < avg - 3*s ? avg - 4*s : avg - 3*s;
    max = max > avg + 3*s ? avg + 4*s : avg + 3*s;


    if(count<30)
    {
        chart->setAxisScale(chart->xBottom, 0, count);
    }
    else
    {
        chart->setAxisScale(chart->xBottom, count-30, count);
    }
    chart->setAxisScale(chart->yLeft, min*0.95, max*1.05);

    //画曲线
    QwtPlotCurve *qcCurve = new QwtPlotCurve(tr(""));
    qcCurve->setPen(colors[level],2.0,Qt::SolidLine);
    qcCurve->attach(chart);

    //QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse, QColor(colors[level]), QPen(colors[level]), QSize(10, 10)) ;
    //qcCurve->setSymbol(symbol); 不同批号要不同颜色区分 故注释
    qcCurve->setStyle(QwtPlotCurve::Lines);
    qcCurve->setCurveAttribute(QwtPlotCurve::Fitted, false);

    double x[count];
    double y[count];
    double x_hasValue=0;
    double y_hasValue=0;
    for(int i=0; i<count;i++)
    {
        if(data[i].value ==0)
        {
            x[i] = x_hasValue;
            y[i] = y_hasValue;
        }
        else
        {
            x[i] = i;
            y[i] = data[i].value;
            if(data[i].value > avg + 4*s)
            {
                y[i] = avg + 4*s;
            }
            if(data[i].value < avg - 4*s)
            {
                y[i] = avg - 4*s;
            }

            x_hasValue = i;
            y_hasValue = data[i].value;
        }
    }
    qcCurve->setSamples(x, y, count);
    //qcCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine, true);
    qcCurve->setTitle("L"+QString("%1").arg(level+1));

    QColor color = colors[level];
    int iColor = level;
    QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse, QColor(color), QPen(color), QSize(10, 10));
    for(int i=0;i<count;i++)
    {
        QwtPlotMarker *mPos = new QwtPlotMarker("Marker");
        mPos->setRenderHint(QwtPlotItem::RenderAntialiased, true);
        mPos->setItemAttribute(QwtPlotItem::Legend, false);
        if(i>0 && data[i].detail.Project_DetailId != data[i-1].detail.Project_DetailId)
        {
            color =  colors[(++iColor)%7];
            symbol = new QwtSymbol(QwtSymbol::Ellipse, QColor(color), QPen(color), QSize(10, 10));
        }
        mPos->setSymbol(symbol);

        mPos->setValue(QPointF(x[i], y[i]));
        mPos->attach(chart);
    }

    //画有问题的质控点
    QVector<Result> errs;
    for(int i=0; i<count;i++)
    {
        if(!data[i].isValid)
        {
            Result result;
            result.X = i;
            result.Y = data[i].value;
            if(data[i].value > avg + 4*s)
            {
                result.Y = avg + 4*s;
            }
            if(data[i].value < avg - 4*s)
            {
                result.Y = avg - 4*s;
            }
            result.refuseReason = data[i].refuseReason;
            errs.append(result);
        }
    }
    for(int i=0; i<errs.count();i++)
    {
        QwtPlotMarker *mPos = new QwtPlotMarker("Marker");
        mPos->setRenderHint(QwtPlotItem::RenderAntialiased, true);
        mPos->setItemAttribute(QwtPlotItem::Legend, false);
        QwtSymbol *symbolErr = new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush, QPen(Qt::red, 2), QSize(15, 15)) ;
        mPos->setSymbol(symbolErr);
        mPos->setValue(QPointF(errs[i].X, errs[i].Y));
        mPos->setLabel(errs[i].refuseReason.split(',')[0]);
        mPos->setLabelAlignment(Qt::AlignRight);
        mPos->attach(chart);
    }



    //质控线
    QwtPlotMarker *mY;
    if(max >= avg + 4*s)
    {
        mY = new QwtPlotMarker();
        mY->setLabel(QString::fromLatin1("4S"));
        mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
        mY->setLabelOrientation(Qt::Horizontal);
        mY->setLineStyle(QwtPlotMarker::HLine);
        mY->setLinePen(QPen(Qt::red, 0, Qt::SolidLine));
        mY->setYValue(avg + 4*s);
        mY->attach(chart);
    }
    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("3S"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(Qt::red, 0, Qt::SolidLine));
    mY->setYValue(avg + 3*s);
    mY->attach(chart);

    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("2S"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(QColor(255,128,64,255), 0, Qt::DashDotLine));
    mY->setYValue(avg + 2*s);
    mY->attach(chart);

    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("1S"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(Qt::black, 0, Qt::DashDotLine));
    mY->setYValue(avg + s);
    mY->attach(chart);

    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromStdString("均值"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(Qt::black, 0, Qt::SolidLine));
    mY->setYValue(avg);
    mY->attach(chart);

    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("-S"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(Qt::black, 0, Qt::DashDotLine));
    mY->setYValue(avg - s);
    mY->attach(chart);

    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("-2S"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(QColor(255,128,64,255), 0, Qt::DashDotLine));
    mY->setYValue(avg - 2*s);
    mY->attach(chart);

    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("-3S"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(Qt::red, 0, Qt::SolidLine));
    mY->setYValue(avg - 3*s);
    mY->attach(chart);

    if(min <= avg - 4*s)
    {
        mY = new QwtPlotMarker();
        mY->setLabel(QString::fromLatin1("-4S"));
        mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
        mY->setLabelOrientation(Qt::Horizontal);
        mY->setLineStyle(QwtPlotMarker::HLine);
        mY->setLinePen(QPen(Qt::red, 0, Qt::SolidLine));
        mY->setYValue(avg - 4*s);
        mY->attach(chart);
    }

    Background *bg = new Background(avg, s);
    bg->attach(chart);

    chart->replot();

    QwtPlotPanner *PQ= new QwtPlotPanner(chart->canvas());
    PQ->setOrientations(Qt::Horizontal);
}

//void CustomQwtPlot::CheckData()
//{

//    for(int i = 0; i < m_data.count(); i++)
//    {
//        m_data[i].isValid = true;
//        m_data[i].refuseReason = "";
//    }

//    //是否符合规则
//    Project p;


//    if(ui->IfCustum->isChecked())
//    {
//        double avg = ui->inputCustAvg->text().toDouble();
//        double sd = ui->inputCustSD->text().toDouble();
//        p.CaculateByRule(&m_data, m_currentRule, avg, sd);
//    }
//    else
//    {
////        double avg = ui->txtAvg->text().toDouble();
////        double sd = ui->txtSd->text().toDouble();
//        p.CaculateByRule(&m_data, m_currentRule, 0, 0);
//    }



//    //n>1各个浓度联合判断 有一个不符合就都算不符合
//    if(!m_currentRule.isEmpty())
//    {
//        int n = 1;

//        if(m_currentRule.split(",n=").count() == 2)
//        {
//            n = m_currentRule.split(",n=").at(1).toInt();
//        }
//        if(n == current_level)
//        {
//            for(int i = 0; i < m_data.count(); i++)
//            {
//                QString s = "";
//                bool isValid=true;

//                if(m_data[i].isValid == false)
//                {
//                    isValid = false;
//                    s.append(m_data[i].refuseReason);
//                }


//                if(isValid == false)
//                {
//                    m_data[i].isValid = false;
//                    m_data[i].refuseReason = s;
//                }
//            }
//        }
//    }
//}

void CustomQwtPlot::on_btnDataTable_clicked()
{
    ProjectDataSheet *dateSheet = new ProjectDataSheet;
    dateSheet->setWindowModality(Qt::ApplicationModal);
    dateSheet->showMaximized();
}

