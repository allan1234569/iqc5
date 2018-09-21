#include "ChartView.h"
#include "ui_ChartView.h"
#include <QDebug>
#include <qevent.h>
#include <math.h>
#include <QFileDialog>
#include "Service/ProjectService.h"
#include "UI/TableView.h"
#include "UI/CustomQwtPlot.h"
#include "UI/Background.h"
#include "UI/daterangedialog.h"
#include <QEvent>
#include <QKeyEvent>


ChartView::ChartView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartView)
{
    ui->setupUi(this);

    pop = new PopBox();

    needRefresh = true;
}


void ChartView::initRules(QString testTypeId, QString currentRule)
{
    if(testTypeId != "")
    {
        ProjectService *service = new ProjectService();
        QVector <QString> rules = service->GetRules(testTypeId);

        needRefresh = false;
        ui->listWidget->clear();
        if(rules.count()>0)
        {
            foreach(QString string, rules)
            {
                if(string.endsWith("|"))
                {
                    string = string.mid(0, string.count()-1);
                }
                ui->listWidget->addItem(string);
            }
            ui->listWidget->setCurrentIndex(0);
        }
        needRefresh = true;
    }
}

//Levey-Jenning质控图
void ChartView::DrawLjChart(QVector<Project> projects, int index, QString currentRule, double avg[], double sd[], bool IfCaculate)
{
    this->projectList = projects;
    this->index = index;

    mode = 1;

    QVector< QVector<Result> > allData;
    Project &p = projects[index];

    allData.clear();
    for(int i=1;i<=p.level;i++)
    {
        ProjectService service;
        QVector<Result> result1 = service.GetResult(p.ProjectId, i, service.getStartTime(p.ProjectId,i), service.getEndTime(p.ProjectId, i), ui->cbkShowAll->isChecked());

        allData.append(result1);
    }

    CheckData(allData);
    this->ui->tabWidget->clear();


    //画曲线
    for(int h=0;h<allData.count();h++)
    {
        QVector<Result> data = allData[h];

        ProjectService *service = new ProjectService();

        QDate startDate = QDate::fromString(service->getStartTime(p.ProjectId,h+1), "yyyy-MM-dd");
        QDate endDate = QDate::fromString(service->getEndTime(p.ProjectId,h+1), "yyyy-MM-dd");

        double max, min, avg, sd, cv, n;

//        max = service->getMax(projects[index].ProjectId, index);
//        min = service->getMin(projects[index].ProjectId, index);
//        avg = service->getAvg(projects[index].ProjectId, index);
//        sd = service->getSd(projects[index].ProjectId, index);
//        n = service->getN(projects[index].ProjectId, index);

        max = p.GetMax(data);
        min = p.GetMin(data);
        avg = p.GetAverage(data,"","");
        sd = p.GetStandardDeviation(data,"","");

        if(avg!=0)
        {
            cv= sd / avg *100;
        }
        else
        {
            cv=0;
        }

        double sigma6;
        if(cv!=0)
        {
            sigma6 = 20/cv;
        }
        else
        {
            sigma6=0;
        }

        CustomQwtPlot* chart = new CustomQwtPlot(this);

        chart->IfCaculate->setChecked(true);
        chart->inputCustAvg->setText(QString::number(avg, 'f', 2));
        chart->txtAvg->setText(QString::number(avg, 'f', 2));
        chart->inputCustSD->setText(QString::number(sd, 'f', 2));
        chart->txtSd->setText(QString::number(sd, 'f', 2));
        chart->txtCV->setText(QString::number(cv, 'f', 2)+'%');
        chart->txtCustCV->setText(QString::number(cv, 'f', 2)+'%');
        chart->txt6sigma->setText(QString::number(sigma6, 'f', 2));
        chart->txtCust6sigma->setText(QString::number(sigma6, 'f', 2));
        chart->txtN->setText(QString::number(n));

        connect(chart->inputCustAvg, SIGNAL(textChanged(QString)), this, SLOT(on_inputCustAvg_textChanged(QString)));
        connect(chart->inputCustSD, SIGNAL(textChanged(QString)), this, SLOT(on_inputCustSD_textChanged(QString)));
        connect(chart->inputStartDate,SIGNAL(dateChanged(QDate)),this,SLOT(on_inputStartDate_Changed(QDate)));
        connect(chart->inputEndDate,SIGNAL(dateChanged(QDate)),this,SLOT(on_inputEndDate_Changed(QDate)));
        connect(chart->IfCustum, SIGNAL(toggled(bool)), this, SLOT(on_IfCaculate_toggled(bool)));
        connect(chart->btnInit,SIGNAL(clicked()),this,SLOT(on_btnInit_clicked()));
        connect(chart->btnCaculate, SIGNAL(clicked()), this, SLOT(on_btnCaculate_clicked()));

        chart->inputStartDate->setDate(startDate);
        chart->inputEndDate->setDate(endDate);
        chart->txtN->setText(QString("%1").arg(service->getN(p.ProjectId,h+1)));

        if(data.count()>0)
        {
            chart->SetTitle("          " + projects[index].CustomName + "    日期：" + QString("%1").arg(data[0].TestTime) + "至"+ QString("%1").arg(data[data.count()-1].TestTime
                + "    数据：" + QString("%1").arg(data.count())+ "个"));
        }
        else
        {
            chart->SetTitle("          " + projects[index].CustomName);
        }

        this->DrawLjChart(chart->getChart(), h, avg, sd, min, max, data);
        this->ui->tabWidget->addTab(chart, QString("L%1").arg(h+1));

        QwtPlotPanner *PQ= new QwtPlotPanner(chart->getChart()->canvas());
        PQ->setOrientations(Qt::Horizontal);
    }
}
void ChartView::DrawLjChart(QwtPlot*chart, int level, double avg, double s, double min, double max, QVector<Result> data)
{
    chart->detachItems(QwtPlotItem::Rtti_PlotItem, false);

    chart->canvas()->installEventFilter(this);

    QColor colors[] = {Qt::darkGreen,Qt::blue,QColor(11,68,54),Qt::darkBlue,Qt::darkCyan,Qt::darkMagenta,Qt::darkYellow};

    //图表标题

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
        QwtSymbol *symbolErr = new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush, QPen(Qt::red, 1), QSize(15, 15)) ;
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


//Z分数质控图
void ChartView::DrawZChart(QVector<Project> projects, int index, QString currentRule, double avg[], double sd[], bool IfCaculate)
{
    this->projectList = projects;
    this->index = index;

    mode = 2;

    QVector< QVector<Result> > allData;
    Project &p = projects[index];

    allData.clear();
    for(int i=1;i<=p.level;i++)
    {
        ProjectService service;
        QVector<Result> result1 = service.GetResult(p.ProjectId,i,ui->cbkShowAll->isChecked());
        allData.append(result1);
    }

    CheckData(allData);

    //Project p;

    int allDataCount=0;
    for(int i=0;i<allData.count();i++)
    {
        if(IfCaculate)
        {
            p.CaculateZ(&allData[i],0,0);
        }
        else
        {
            p.CaculateZ(&allData[i],avg[i],sd[i]);
        }
        allDataCount +=allData[i].count();
    }

    QVector< QVector<Result> >allData_z = p.ReSort(allData);

    CustomQwtPlot* custChart = new CustomQwtPlot(this);
    ui->tabWidget->clear();
    ui->tabWidget->addTab(custChart,"Z分数质控图");

    custChart->widget_4->setHidden(true);
    QwtPlot* chart = custChart->getChart();

    chart->detachItems(QwtPlotItem::Rtti_PlotItem, false);

    chart->canvas()->installEventFilter(this);

    double min=0, max=0;
    for(int i=0;i<allData_z.count();i++)
    {
        double t1= p.GetMinZ(allData_z[i]);
        double t2= p.GetMaxZ(allData_z[i]);
        min = min < t1 ? min : t1;
        max = max > t2 ? max : t2;
    }


    if(allData.count()>0 && allData[0].count()>0)
    {
        //图表标题
        custChart->SetTitle("          " + projects[index].CustomName + "    日期：" + QString("%1").arg(allData[0][0].TestTime) + "至"+ QString("%1").arg(allData[0][allData[0].count()-1].TestTime
                + "    数据：" + QString("%1").arg(allDataCount)+ "个"));
    }
    else
    {
        custChart->SetTitle("          " + projects[index].CustomName);
    }

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
            scaleWidget->setMargin(0);
        }
        QwtScaleDraw *scaleDraw = chart->axisScaleDraw(i);
        if (scaleDraw)
        {
            scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
        }

    }
    chart->plotLayout()->setAlignCanvasToScales(true);

    //上下限
    min = min < - 3 ? -4 : - 3;
    max = max > 3 ? 4 : 3;

    int count_max = 0;
    for(int i=0;i<allData_z.count();i++)
    {
        if(allData_z[i].count() > count_max)
        {
            count_max = allData_z[i].count();
        }
    }

    if(count_max<30)
    {
        chart->setAxisScale(chart->xBottom, 0, count_max);
    }
    else
    {
        chart->setAxisScale(chart->xBottom, count_max-30, count_max);
    }
    chart->setAxisScale(chart->yLeft, min*1.1, max*1.2);

    QColor colors[] = {Qt::darkGreen,Qt::blue,QColor(11,68,54),Qt::darkBlue,Qt::darkCyan,Qt::darkMagenta,Qt::darkYellow};

    //画曲线
    for(int h=0;h<allData_z.count();h++)
    {
        QVector<Result> data = allData_z[h];

        int count = data.count();
        QwtPlotCurve *qcCurve = new QwtPlotCurve(tr(""));
        qcCurve->setPen(colors[h%7],2.0,Qt::SolidLine);
        qcCurve->attach(chart);

        //QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Diamond, QColor(colors[h%7]), QPen(colors[h%7]), QSize(10, 10));
        //qcCurve->setSymbol(symbol);
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
                y[i] = data[i].z_value;
                if(data[i].z_value > 4)
                {
                    y[i] = 4;
                }
                if(data[i].z_value < -4)
                {
                    y[i] = -4;
                }

                x_hasValue = i;
                y_hasValue = data[i].z_value;
            }
        }
        //第一个开始的点没有的话不显示
        int noValue = 0;
        for(int i=0; i<count-1;i++)
        {
            if(x[i]!=0 || y[i]!=0)
            {
                noValue = i;
                break;
            }
        }
        for(int i=0; i<noValue;i++)
        {
            x[i]=x[noValue+1];
            y[i]=y[noValue+1];
        }



        qcCurve->setSamples(x, y, count);
        //qcCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine, true);
        qcCurve->setTitle("L"+QString("%1").arg(h+1));

        QColor color = colors[h];
//        int iColor = h;
        QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse, QColor(color), QPen(color), QSize(10, 10));
        for(int i=0;i<count;i++)
        {
            QwtPlotMarker *mPos = new QwtPlotMarker("Marker");
            mPos->setRenderHint(QwtPlotItem::RenderAntialiased, true);
            mPos->setItemAttribute(QwtPlotItem::Legend, false);
//            if(i>0 && data[i].detail.Project_DetailId != data[i-1].detail.Project_DetailId)
//            {
//                color =  colors[(++iColor)%7];
//                symbol = new QwtSymbol(QwtSymbol::Ellipse, QColor(color), QPen(color), QSize(10, 10));
//            }
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
                result.Y = data[i].z_value;
                if(data[i].z_value > 4)
                {
                    result.Y = 4;
                }
                if(data[i].z_value < -4)
                {
                    result.Y = -4;
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
            QwtSymbol *symbolErr = new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush, QPen(Qt::red, 1), QSize(15, 15)) ;
            mPos->setSymbol(symbolErr);
            mPos->setValue(QPointF(errs[i].X, errs[i].Y));
            mPos->setLabel(errs[i].refuseReason.split(',')[0]);
            mPos->setLabelAlignment(Qt::AlignRight);
            mPos->attach(chart);
        }
    }

    //质控线
    QwtPlotMarker *mY;
    if(max>=4)
    {
        mY = new QwtPlotMarker();
        mY->setLabel(QString::fromLatin1("4"));
        mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
        mY->setLabelOrientation(Qt::Horizontal);
        mY->setLineStyle(QwtPlotMarker::HLine);
        mY->setLinePen(QPen(Qt::red, 0, Qt::SolidLine));
        mY->setYValue(4);
        mY->attach(chart);
    }
    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("3"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(Qt::red, 0, Qt::SolidLine));
    mY->setYValue(3);
    mY->attach(chart);

    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("2"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(QColor(255,128,64,255), 0, Qt::DashDotLine));
    mY->setYValue(2);
    mY->attach(chart);

    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("1"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(Qt::black, 0, Qt::DashDotLine));
    mY->setYValue(1);
    mY->attach(chart);

    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromStdString("0"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(Qt::black, 0, Qt::SolidLine));
    mY->setYValue(0);
    mY->attach(chart);

    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("-1"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(Qt::black, 0, Qt::DashDotLine));
    mY->setYValue(-1);
    mY->attach(chart);

    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("-2"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(QColor(255,128,64,255), 0, Qt::DashDotLine));
    mY->setYValue(-2);
    mY->attach(chart);

    mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("-3"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLabelOrientation(Qt::Horizontal);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setLinePen(QPen(Qt::red, 0, Qt::SolidLine));
    mY->setYValue(-3);
    mY->attach(chart);

    if(min<=-4)
    {
        mY = new QwtPlotMarker();
        mY->setLabel(QString::fromLatin1("-4"));
        mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
        mY->setLabelOrientation(Qt::Horizontal);
        mY->setLineStyle(QwtPlotMarker::HLine);
        mY->setLinePen(QPen(Qt::red, 0, Qt::SolidLine));
        mY->setYValue(-4);
        mY->attach(chart);
    }

    Background *bg = new Background(0, 1);
    bg->attach(chart);

    chart->replot();

    QwtPlotPanner *PQ= new QwtPlotPanner(chart->canvas());
    PQ->setOrientations(Qt::Horizontal);
}

void ChartView::CheckData(QVector< QVector<Result> > &allData)
{
    for(int h=0;h<allData.count();h++)
    {
        for(int j=0;j<allData[h].count();j++)
        {
            allData[h][j].isValid = true;
            allData[h][j].refuseReason = "";
        }
    }
    //是否符合规则
    Project p;

//    for(int h=0;h<allData.count();h++)
//    {
//        CustomQwtPlot* chart = (CustomQwtPlot*)ui->tabWidget->widget(h);

//        if(chart != NULL)
//        {
//            if(chart->IfCaculate->isChecked())
//            {
//                p.CaculateByRule(&allData[h], ui->listWidget->currentText(), 0, 0);
//            }
//            else
//            {
//                p.CaculateByRule(&allData[h], ui->listWidget->currentText(), chart->inputCustAvg->text().toDouble(), chart->inputCustSD->text().toDouble());
//            }
//        }
//        else
//        {
//            p.CaculateByRule(&allData[h], ui->listWidget->currentText(), 0, 0);
//        }
//    }

    //modify by heyi
    QVector<double> means;
    QVector<double> variances;

    for(int level = 0; level < allData.count(); level++)
    {
        if(level < ui->tabWidget->count())
        {

            double avg = ((CustomQwtPlot *)(ui->tabWidget->widget(level)))->inputCustAvg->text().toDouble();
            double sd = ((CustomQwtPlot *)(ui->tabWidget->widget(level)))->inputCustSD->text().toDouble();
            means.push_back(avg);
            variances.push_back(sd);
        }
        else
        {
            means.push_back(0.0);
            variances.push_back(0.0);
        }
    }

    QString rule = ui->listWidget->itemText(ui->listWidget->currentIndex());
    QStringList filterResultIds;   //不参与规则计算的结果Id值
    ProjectService ps;

    filterResultIds = ps.GetResultIdFromComputatonResult(projectList[index].ProjectId);
    p.CaculateByRule(allData, rule, means, variances, filterResultIds);  //计算规则

    //n>1各个浓度联合判断 有一个不符合就都算不符合

    int n = 1;
//    QString rule = ui->listWidget->currentText();
    if(rule.split(",n=").count() == 2)
    {
        n = rule.split(",n=").at(1).toInt();
    }
    if(n == p.level)
    {
        for(int i=0;i<allData[0].count();i++)
        {
            QString s = "";
            bool isValid=true;
            for(int j=0;j<n;j++)
            {
                if(allData[j][i].isValid == false)
                {
                    isValid = false;
                    s.append(allData[j][i].refuseReason);
                }
            }
            for(int j=0;j<n;j++)
            {
                if(isValid == false)
                {
                    allData[j][i].isValid = false;
                    allData[j][i].refuseReason = s;
                }
            }
        }
    }
}


void ChartView::keyPressEvent (QKeyEvent * keyevent)
{
    int uKey = keyevent->key();
    Qt::Key key = static_cast<Qt::Key>(uKey);

    int currentTab = ui->tabWidget->currentIndex();
    if(key == Qt::Key_PageUp)
    {
        do
        {
            index++;
            if(index>=projectList.count())
            {
                index = 0;
            }
        }
        while(projectList[index].level < ui->tabWidget->currentIndex()+1);
    }
    if(key == Qt::Key_PageDown)
    {
        do
        {
            index--;
            if(index<0)
            {
                index = projectList.count()-1;
            }
        }
        while(projectList[index].level < ui->tabWidget->currentIndex()+1);
    }
    if(key == Qt::Key_PageUp || key == Qt::Key_PageDown)
    {
        Project p = projectList[index];
        initRules(p.testType.TestTypeId, "");

        if(mode == 1)
        {
            this->DrawLjChart(projectList,index,ui->listWidget->currentText(),0,0,true);
            ui->tabWidget->setCurrentIndex(currentTab);
        }
        else if(mode == 2)
        {
            this->DrawZChart(projectList,index,ui->listWidget->currentText(),0,0,true);
        }
    }

}
 bool ChartView::eventFilter(QObject *object, QEvent *e)
 {
     switch(e->type())
     {
         case QEvent::MouseButtonDblClick:
         {
         }
         case QEvent::MouseButtonPress:
         {
             QwtPlot* chart = (QwtPlot*)object->parent();
             select(chart, ((QMouseEvent *)e)->pos());
             return true;
         }
         default:
             break;
     }

     return QObject::eventFilter(object, e);
 }

 void ChartView::select(QwtPlot* chart, const QPoint &pos)
 {
     QwtPlotCurve *curve = NULL;
     double dist = 5;
     int dotIndex = -1;

     const QwtPlotItemList& itmList = chart->itemList();
     for ( QwtPlotItemIterator it = itmList.begin(); it != itmList.end(); ++it )
     {
         if ( (*it)->rtti() == QwtPlotItem::Rtti_PlotCurve)
         {
             QwtPlotCurve *c = (QwtPlotCurve*)(*it);

             double d;
             int idx = c->closestPoint(pos, &d);
             if (idx >=0 && d < dist)
             {
                 curve = c;
                 dotIndex = idx;

                 int l = curve->title().text().replace("L","").toInt();
                 if(pop->level != l || pop->no != idx) //换了个点
                 {
                     QVector<Result> result;

                     QVector< QVector<Result> > allData;
                     Project &p = projectList[index];

                     allData.clear();
                     for(int i=1;i<=p.level;i++)
                     {
                         ProjectService service;
                         QVector<Result> result1 = service.GetResult(p.ProjectId,i,ui->cbkShowAll->isChecked());

                         allData.append(result1);
                     }


                     if(mode == 2)
                     {
                         Project p;
                         result = p.ReSort(allData)[l-1];
                     }
                     else
                     {
                         result = allData[l-1];
                     }

                     if(!result[idx].isValid) //不在控
                     {
                         pop->no = idx;
                         pop->level = l;
                         pop->SetText(result[idx].TestTime + "\n" + curve->title().text() + ": " + QString("%1").arg(result[idx].value) + "\n" + result[idx].refuseReason);
                         pop->hide();
                         pop->showNormal();
                         showMsgBox = true;

                     }
                     else //在控
                     {
                         pop->no = idx;
                         pop->level = l;
                         pop->SetText(result[idx].TestTime + "\n" + curve->title().text() + ": " + QString("%1").arg(result[idx].value));
                         pop->hide();
                         pop->showNormal();
                         showMsgBox = true;
                     }
                 }
                 else //没换点
                 {
                     if(showMsgBox)
                     {
                         pop->hide();
                         showMsgBox = false;
                     }
                     else
                     {
                         pop->hide();
                         pop->showNormal();
                         showMsgBox = true;
                     }
                 }


                 break;
             }
         }
     }
 }


ChartView::~ChartView()
{
    delete ui;
}


void ChartView::on_inputCustAvg_textChanged(const QString &arg1)
{
    ChangeChart();
}

void ChartView::on_inputCustSD_textChanged(const QString &arg1)
{
    ChangeChart();
}

void ChartView::on_inputStartDate_Changed(const QDate &date)
{
    ProjectService s;

    Project &p = projectList[index];
    if (getChart()!= NULL)
    {
        s.UpdateComputationDate(p.ProjectId,ui->tabWidget->currentIndex() + 1, date.toString("yyyy-MM-dd"), getChart()->inputEndDate->text());
        ChangeChart();
    }
}

void ChartView::on_inputEndDate_Changed(const QDate &date)
{
    ProjectService s;

    Project &p = projectList[index];
    if (getChart()!= NULL)
    {
        s.UpdateComputationDate(p.ProjectId,ui->tabWidget->currentIndex() + 1, getChart()->inputStartDate->text(), date.toString("yyyy-MM-dd"));
        ChangeChart();
    }
}

void ChartView::on_IfCaculate_toggled(bool checked)
{
    ChangeChart();
}


void ChartView::ChangeChart()
{
    QVector< QVector<Result> > allData;
    Project &p = projectList[index];



    allData.clear();
    for(int i=1;i<=p.level;i++)
    {
        CustomQwtPlot* c = (CustomQwtPlot*)ui->tabWidget->widget(ui->tabWidget->currentIndex());
        ProjectService service;
//        QVector<Result> result1 = service.GetResult(p.ProjectId,i,ui->cbkShowAll->isChecked());
        QVector<Result> result1 = service.GetResult(p.ProjectId, i, c->inputStartDate->text(), c->inputEndDate->text(), ui->cbkShowAll->isChecked());

        allData.append(result1);
    }

    CheckData(allData);



    //画曲线
    int h = ui->tabWidget->currentIndex();
    QVector<Result> data = allData[h];

    double max = p.GetMax(data);
    double min = p.GetMin(data);
    double avg = p.GetAverage(data,"","");
    double sd = p.GetStandardDeviation(data,"","");


    CustomQwtPlot* chart = (CustomQwtPlot*)ui->tabWidget->widget(h);
    if(chart->IfCustum->isChecked())
    {
        avg = chart->inputCustAvg->text().toDouble();
        sd = chart->inputCustSD->text().toDouble();

        double cv;
        if(avg!=0)
        {
            cv= sd / avg *100;
        }
        else
        {
            cv=0;
        }

        double sigma6;
        if(cv!=0)
        {
            sigma6 = 20/cv;
        }
        else
        {
            sigma6=0;
        }
        chart->txtCustCV->setText(QString::number(cv, 'f', 2)+'%');
        chart->txtCust6sigma->setText(QString::number(sigma6, 'f', 2));
    }
    if(data.count()>0)
    {
        chart->SetTitle("          " + projectList[index].CustomName + "    日期：" + QString("%1").arg(data[0].TestTime) + "至"+ QString("%1").arg(data[data.count()-1].TestTime
                + "    数据：" + QString("%1").arg(data.count())+ "个"));
    }
    else
    {
        chart->SetTitle("          " + projectList[index].CustomName);
    }

    this->DrawLjChart(chart->getChart(), h, avg, sd, min, max, data);

    QwtPlotPanner *PQ= new QwtPlotPanner(chart->getChart()->canvas());
    PQ->setOrientations(Qt::Horizontal);

}

CustomQwtPlot *ChartView::getChart()
{
    return (CustomQwtPlot*)(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
}

void ChartView::on_btnCaculate_clicked()
{
    DateRangeDialog *dialog = new DateRangeDialog;
    dialog->exec();
    if(dialog->m_state == DateRangeDialog::Cancel)
    {
        return;
    }

    ProjectService s;
//    CustomQwtPlot *customQwtPlot= (CustomQwtPlot *)(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
    s.InsertComputation(projectList[index].ProjectId,"",ui->tabWidget->currentIndex()+1,dialog->m_startDate, dialog->m_endDate);

    int currentTab = ui->tabWidget->currentIndex();
    if(mode == 1)
    {
        this->DrawLjChart(projectList,index,ui->listWidget->currentText(),0,0,true);
        ui->tabWidget->setCurrentIndex(currentTab);
    }
    else if(mode == 2)
    {
        this->DrawZChart(projectList,index,ui->listWidget->currentText(),0,0,true);
    }
}

void ChartView::on_btnInit_clicked()
{
    ProjectService s;

    Project &p = projectList[index];

    CustomQwtPlot *customQwtPlot= (CustomQwtPlot *)(ui->tabWidget->widget(ui->tabWidget->currentIndex()));

    int resultCount = s.GetResult(p.ProjectId, ui->tabWidget->currentIndex() + 1,  customQwtPlot->inputStartDate->date().toString("yyyy-MM-dd"), customQwtPlot->inputEndDate->date().toString("yyyy-MM-dd"), ui->cbkShowAll->isChecked()).size();

    if ( resultCount < customQwtPlot->txtN->text().toInt() )
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("n值大于当前结果数量,当前结果数为%1\n是否设置n为该值").arg(resultCount));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setButtonText(QMessageBox::Ok,"好");
        msgBox.setButtonText(QMessageBox::Cancel,"取消");
        int ret = msgBox.exec();

        if(ret == QMessageBox::Ok)
        {
            customQwtPlot->txtN->setText(QString::number(resultCount));
        }
        else
        {
            return;
        }
    }

    s.InsertComputation(p.ProjectId,"",ui->tabWidget->currentIndex()+1,customQwtPlot->inputStartDate->date().toString("yyyy-MM-dd"), customQwtPlot->txtN->text().toInt());
    s.UpdateComputationDate(p.ProjectId, ui->tabWidget->currentIndex()+1, customQwtPlot->inputStartDate->date().toString("yyyy-MM-dd"), customQwtPlot->inputEndDate->date().toString("yyyy-MM-dd"));

    ChangeChart();
}

void ChartView::on_cbkShowAll_toggled(bool checked)
{
    int currentTab = ui->tabWidget->currentIndex();
    if(mode == 1)
    {
        this->DrawLjChart(projectList,index,ui->listWidget->currentText(),0,0,true);
        ui->tabWidget->setCurrentIndex(currentTab);
    }
    else if(mode == 2)
    {
        this->DrawZChart(projectList,index,ui->listWidget->currentText(),0,0,true);
    }
}


void ChartView::on_listWidget_currentIndexChanged(int i)
{
    if(needRefresh)
    {
        int currentTab = ui->tabWidget->currentIndex();
        if(mode == 1)
        {
            this->DrawLjChart(projectList,index,ui->listWidget->currentText(),0,0,true);
            ui->tabWidget->setCurrentIndex(currentTab);
        }
        else if(mode == 2)
        {
            this->DrawZChart(projectList,index,ui->listWidget->currentText(),0,0,true);
        }
    }
}

void ChartView::on_btnAreaData_clicked()
{

}
