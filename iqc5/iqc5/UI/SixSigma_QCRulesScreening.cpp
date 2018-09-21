#include "SixSigma_QCRulesScreening.h"
#include "ui_SixSigma_QCRulesScreening.h"

#include "ProjectService.h"
#include "EvaluationParameter.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_scale_widget.h>
#include <qwt_legend.h>
#include <qwt_plot_marker.h>
#include <qwt_symbol.h>
#include <qwt_scale_draw.h>
#include <qwt_text.h>
#include <qwt_plot_grid.h>

#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFile>

static QColor colors[6] = { QColor(Qt::green), QColor(Qt::blue), QColor(Qt::yellow), QColor(Qt::cyan), QColor(Qt::darkMagenta),QColor(Qt::black) };

QColor symbolColors[255];

SixSigma_QCRulesScreening::SixSigma_QCRulesScreening(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SixSigma_QCRulesScreening)
{
    ui->setupUi(this);

    for(int i = 0; i< 255; i++)
    {
        symbolColors[i] = QColor(rand() % 255, rand() % 255,rand() % 255);
    }

    getparams();

    InitProjects();

    m_bParamChanged = false;
    m_bNeedShow = false;
    InitPlot();

    draw_100PercentMedicalDecisionChart();
}

SixSigma_QCRulesScreening::~SixSigma_QCRulesScreening()
{
    delete ui;
}

void SixSigma_QCRulesScreening::InitProjects()
{
    m_bNeedShow = false;
    ProjectService *service;service = new ProjectService();
    QString keyword = ui->input_keyword->text();


    ui->treeWidget->clear();
    pro2widget_Map.clear();
    projectList.clear();

    QVector<Project> projects =  service->SearchProject("","",keyword,"");

    int index = 0;
    if(projects.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<projects[0].testType.SubjectName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* ca2 = new QTreeWidgetItem(QStringList()<<projects[0].testType.CategoryName);
        ca->addChild(ca2);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<projects[0].CustomName);
        pItem->setToolTip(0, QString("%1").arg(projects[0].ProjectId));
//        pItem->setCheckState(0, Qt::Unchecked);
        ca2->addChild(pItem);

        EvaluationParameter *widget = new EvaluationParameter;
        QStringList paramslist = projectParamList[projects[0].ProjectId].split(",");
        if(paramslist.count() >= 3)
        {
            widget->setTea(paramslist[0].toDouble());
            widget->setBias(paramslist[1].toDouble());
            widget->setCv(paramslist[2].toDouble());
        }
        connect(widget,SIGNAL(textChanged()),this,SLOT(slt_hasParamChanged()));
        addWidgetToStackedWidget(widget,index);

        pro2widget_Map.insert(projects[0].ProjectId, index);
        projectList.insert(projects[0].CustomName, projects[0].ProjectId);
        index++;

        for(int i=1;i<projects.count();i++)
        {
            if(QString::compare(projects[i].testType.SubjectName, projects[i-1].testType.SubjectName) != 0)
            {
                ca = new QTreeWidgetItem(QStringList()<<projects[i].testType.SubjectName);
                ui->treeWidget->addTopLevelItem(ca);
            }

            if(QString::compare(projects[i].testType.CategoryName, projects[i-1].testType.CategoryName) != 0)
            {
                ca2 = new QTreeWidgetItem(QStringList()<<projects[i].testType.CategoryName);
                ca->addChild(ca2);
            }

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<projects[i].CustomName);
            pItem->setToolTip(0, QString("%1").arg(projects[i].ProjectId));
//            pItem->setCheckState(0, Qt::Unchecked);
            ca2->addChild(pItem);

            EvaluationParameter *widget = new EvaluationParameter;
            QStringList paramslist = projectParamList[projects[i].ProjectId].split(",");
            if(paramslist.count() >= 3)
            {
                widget->setTea(paramslist[0].toDouble());
                widget->setBias(paramslist[1].toDouble());
                widget->setCv(paramslist[2].toDouble());
            }
            connect(widget,SIGNAL(textChanged()),this,SLOT(slt_hasParamChanged()));
            addWidgetToStackedWidget(widget,index);

            pro2widget_Map.insert(projects[i].ProjectId, index);
            projectList.insert(projects[i].CustomName,projects[i].ProjectId);
            index++;
        }

    }
    ui->treeWidget->expandAll();

}

void SixSigma_QCRulesScreening::InitPlot()
{
    /*
     *  方法评价决策图 初始化
     */
    {
        ui->qwtPlot_DecisionChart->setTitle("   方法评价决策图   ");
        ui->qwtPlot_DecisionChart->setAxisTitle(QwtPlot::yLeft,"不准确度(Bias)");
        ui->qwtPlot_DecisionChart->setAxisTitle(QwtPlot::xBottom,"不精密度(CV)");

        ui->qwtPlot_DecisionChart->setAxisScale(QwtPlot::yLeft, 0.0, 10.0);
        ui->qwtPlot_DecisionChart->setAxisScale(QwtPlot::xBottom, 0.0, 10.0/2);

        QwtPlotGrid *plotGrid = new QwtPlotGrid;
        plotGrid->setPen(QColor(Qt::gray));
        plotGrid->attach(ui->qwtPlot_DecisionChart);

        QwtPlotCanvas *plotCanvas = qobject_cast<QwtPlotCanvas*>(ui->qwtPlot_DecisionChart->canvas());
        plotCanvas->setFrameStyle(QFrame::Box | QFrame::Plain);
        plotCanvas->setLineWidth(1);
        plotCanvas->setPalette(Qt::white);
        ui->qwtPlot_DecisionChart->setCanvas(plotCanvas);

        //自绘坐标系
        for (int i = 0; i < ui->qwtPlot_DecisionChart->axisCnt; i++)
        {
            QwtScaleWidget *scaleWidget = ui->qwtPlot_DecisionChart->axisWidget(i);
            if (scaleWidget)
            {
                scaleWidget->setMargin(1);
            }
            QwtScaleDraw *scaleDraw = ui->qwtPlot_DecisionChart->axisScaleDraw(i);
            if (scaleDraw)
            {
                scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
            }
        }
        ui->qwtPlot_DecisionChart->plotLayout()->setAlignCanvasToScales(true);
        ui->qwtPlot_DecisionChart->replot();
    }

    /*
     *标化100%时的方法评价决策图 初始化
     */
    {
        ui->qwtPlot_StandardizedTo100->setTitle("标化100%时的方法评价决策图");
        ui->qwtPlot_StandardizedTo100->setAxisTitle(QwtPlot::yLeft,"不准确度(Bias,%)");
        ui->qwtPlot_StandardizedTo100->setAxisTitle(QwtPlot::xBottom,"不精密度(CV,%)");

        ui->qwtPlot_StandardizedTo100->setAxisScale(QwtPlot::yLeft, 0.0, 100.0, 10.0);
        ui->qwtPlot_StandardizedTo100->setAxisScale(QwtPlot::xBottom, 0.0, 100.0 / 2, 10.0 / 2);

        QwtPlotGrid *plotGrid = new QwtPlotGrid;
        plotGrid->setPen(QColor(Qt::gray));
        plotGrid->attach(ui->qwtPlot_StandardizedTo100);

        ui->qwtPlot_StandardizedTo100->insertLegend(new QwtLegend, QwtPlot::RightLegend);

        QwtPlotCanvas *plotCanvas = qobject_cast<QwtPlotCanvas*>(ui->qwtPlot_StandardizedTo100->canvas());
        plotCanvas->setFrameStyle(QFrame::Box | QFrame::Plain);
        plotCanvas->setLineWidth(1);
        plotCanvas->setPalette(Qt::white);
        ui->qwtPlot_StandardizedTo100->setCanvas(plotCanvas);

        //计算操作线坐标
        for(int i = 0; i < 5; i++)
        {

            double x[2] = {0.0, 100.0  / (6 - i)};
            double y[2] = {100.0, 0.0};

            QwtPlotCurve *plotCurve = new QwtPlotCurve(QString("%1 Sigma").arg(6 - i));
            plotCurve->attach(ui->qwtPlot_StandardizedTo100);

            plotCurve->setStyle(QwtPlotCurve::Lines);

            plotCurve->setPen(QPen(colors[i]));
            plotCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);    //抗锯齿
            plotCurve->setCurveAttribute(QwtPlotCurve::Fitted,false);
            plotCurve->setSamples(x, y, 2);
            plotCurve->setLegendAttribute(plotCurve->LegendShowLine);   //图例以线状显示
        }

        //自绘坐标系
        for (int i = 0; i < ui->qwtPlot_StandardizedTo100->axisCnt; i++)
        {
            QwtScaleWidget *scaleWidget = ui->qwtPlot_StandardizedTo100->axisWidget(i);
            if (scaleWidget)
            {
                scaleWidget->setMargin(1);
            }
            QwtScaleDraw *scaleDraw = ui->qwtPlot_StandardizedTo100->axisScaleDraw(i);
            if (scaleDraw)
            {
                scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
            }
        }
        ui->qwtPlot_StandardizedTo100->plotLayout()->setAlignCanvasToScales(true);
        ui->qwtPlot_StandardizedTo100->replot();
    }
}

void SixSigma_QCRulesScreening::drawMedicalDecisionChart(double Tea, double Bias, double Cv)
{
    ui->qwtPlot_DecisionChart->detachItems(QwtPlotItem::Rtti_PlotItem, false);

    if((Tea > 0.0))
    {
        ui->qwtPlot_DecisionChart->setAxisScale(QwtPlot::yLeft, 0.0, Tea);
        ui->qwtPlot_DecisionChart->setAxisScale(QwtPlot::xBottom, 0.0, Tea/2);

        ui->qwtPlot_DecisionChart->insertLegend(new QwtLegend, QwtPlot::RightLegend);

        QwtPlotGrid *plotGrid = new QwtPlotGrid;
        plotGrid->setPen(QColor(Qt::gray));
        plotGrid->attach(ui->qwtPlot_DecisionChart);

        //计算操作线坐标
        for(int i = 0; i < 5; i++)
        {
            double x[2] = {0,Tea  / (6 - i)};
            double y[2] = {Tea, 0};

            QwtPlotCurve *plotCurve = new QwtPlotCurve(QString("%1 Sigma").arg(6 - i));
            plotCurve->attach(ui->qwtPlot_DecisionChart);

            plotCurve->setStyle(QwtPlotCurve::Lines);

            plotCurve->setPen(QPen(colors[i]));
            plotCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);    //抗锯齿
            plotCurve->setCurveAttribute(QwtPlotCurve::Fitted,false);
            plotCurve->setSamples(x, y, 2);
            plotCurve->setLegendAttribute(plotCurve->LegendShowLine);   //图例以线状显示
        }

        if((Bias > 0.0) && (Cv > 0.0))
        {
            //画操作点
            QwtPlotMarker *plotMarker = new QwtPlotMarker(ui->treeWidget->currentItem()->text(0));
            plotMarker->setRenderHint(QwtPlotItem::RenderAntialiased,true);
            plotMarker->setItemAttribute(QwtPlotItem::Legend,false);

            QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse,symbolColors[pro2widget_Map[ui->treeWidget->currentItem()->toolTip(0)]],QPen(symbolColors[pro2widget_Map[ui->treeWidget->currentItem()->toolTip(0)]]),QSize(7,7));
            plotMarker->setSymbol(symbol);
            plotMarker->setValue(QPointF(Cv,Bias));
            plotMarker->setLabelAlignment(Qt::AlignRight);
            plotMarker->attach(ui->qwtPlot_DecisionChart);

            //设置图例为圆点
            QwtPlotCurve *plotCurve = new QwtPlotCurve(ui->treeWidget->currentItem()->text(0));
            QwtSymbol *legendSymbol = new QwtSymbol(QwtSymbol::Ellipse,symbolColors[pro2widget_Map[ui->treeWidget->currentItem()->toolTip(0)]],QPen(symbolColors[pro2widget_Map[ui->treeWidget->currentItem()->toolTip(0)]]),QSize(6,6));
            plotCurve->setSymbol(legendSymbol);
            plotCurve->setLegendAttribute(plotCurve->LegendShowSymbol);
            plotCurve->attach(ui->qwtPlot_DecisionChart);
        }
    }
    else
    {
        ui->qwtPlot_DecisionChart->setAxisScale(QwtPlot::yLeft, 0.0, 10.0);
        ui->qwtPlot_DecisionChart->setAxisScale(QwtPlot::xBottom, 0.0, 10.0/2);

        QwtPlotCanvas *plotCanvas = qobject_cast<QwtPlotCanvas*>(ui->qwtPlot_DecisionChart->canvas());
        plotCanvas->setFrameStyle(QFrame::Box | QFrame::Plain);
        plotCanvas->setLineWidth(1);
        plotCanvas->setPalette(Qt::white);
        ui->qwtPlot_DecisionChart->setCanvas(plotCanvas);

        QwtPlotGrid *plotGrid = new QwtPlotGrid;
        plotGrid->setPen(QColor(Qt::gray));
        plotGrid->attach(ui->qwtPlot_DecisionChart);
    }

    ui->qwtPlot_DecisionChart->replot();
}

void SixSigma_QCRulesScreening::draw_100PercentMedicalDecisionChart()
{
    ui->qwtPlot_StandardizedTo100->detachItems(QwtPlotItem::Rtti_PlotItem, false);

    double tea = 0;
    double bias = 0;
    double cv = 0;

    //计算操作线坐标
    for(int i = 0; i < 5; i++)
    {

        double x[2] = {0,100  / (6 - i)};
        double y[2] = {100, 0};

        QwtPlotCurve *plotCurve = new QwtPlotCurve(QString("%1 Sigma").arg(6 - i));
        plotCurve->attach(ui->qwtPlot_StandardizedTo100);

        plotCurve->setStyle(QwtPlotCurve::Lines);

        plotCurve->setPen(QPen(colors[i]));
        plotCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);    //抗锯齿
        plotCurve->setCurveAttribute(QwtPlotCurve::Fitted,false);
        plotCurve->setSamples(x, y, 2);
        plotCurve->setLegendAttribute(plotCurve->LegendShowLine);   //图例以线状显示
    }

    for(int i = 0; i < projectList.count(); i++)
    {
        int index =  pro2widget_Map[projectList[projectList.keys().at(i)]];
        EvaluationParameter *widget = (EvaluationParameter*)(ui->stackedWidget->widget(index));
        if(widget != NULL)
        {
            tea = widget->Tea();
            bias = widget->Bias();
            cv = widget->Cv();
            if((bias > 0.0) && (cv > 0.0))
            {
                //画操作点
                QwtPlotMarker *plotMarker = new QwtPlotMarker(projectList.keys().at(i));
                plotMarker->setLabel(QwtText(projectList.keys().at(i)));
                plotMarker->setRenderHint(QwtPlotItem::RenderAntialiased,true);
                plotMarker->setItemAttribute(QwtPlotItem::Legend,false);

                QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse,symbolColors[pro2widget_Map[projectList[projectList.keys().at(i)]]],QPen(symbolColors[pro2widget_Map[projectList[projectList.keys().at(i)]]]),QSize(7,7));
                plotMarker->setSymbol(symbol);
                plotMarker->setValue(QPointF(100 * cv / tea ,100 * bias / tea));
                plotMarker->setLabelAlignment(Qt::AlignRight);
                plotMarker->attach(ui->qwtPlot_StandardizedTo100);

                //设置图例为圆点
                QwtPlotCurve *plotCurve = new QwtPlotCurve(projectList.keys().at(i));
                QwtSymbol *legendSymbol = new QwtSymbol(QwtSymbol::Ellipse,symbolColors[pro2widget_Map[projectList[projectList.keys().at(i)]]],QPen(symbolColors[pro2widget_Map[projectList[projectList.keys().at(i)]]]),QSize(6,6));
                plotCurve->setSymbol(legendSymbol);
                plotCurve->setLegendAttribute(plotCurve->LegendShowSymbol);
                plotCurve->attach(ui->qwtPlot_StandardizedTo100);

                QwtPlotGrid *plotGrid = new QwtPlotGrid;
                plotGrid->setPen(QColor(Qt::gray));
                plotGrid->attach(ui->qwtPlot_StandardizedTo100);
            }
            else
            {
                ui->qwtPlot_StandardizedTo100->setAxisScale(QwtPlot::yLeft, 0.0, 100.0, 10.0);
                ui->qwtPlot_StandardizedTo100->setAxisScale(QwtPlot::xBottom, 0.0, 100.0/2, 10.0 / 2);

                QwtPlotCanvas *plotCanvas = qobject_cast<QwtPlotCanvas*>(ui->qwtPlot_StandardizedTo100->canvas());
                plotCanvas->setFrameStyle(QFrame::Box | QFrame::Plain);
                plotCanvas->setLineWidth(1);
                plotCanvas->setPalette(Qt::white);
                ui->qwtPlot_StandardizedTo100->setCanvas(plotCanvas);

                QwtPlotGrid *plotGrid = new QwtPlotGrid;
                plotGrid->setPen(QColor(Qt::gray));
                plotGrid->attach(ui->qwtPlot_StandardizedTo100);
            }
        }
        else
        {
            continue;
        }
    }

    ui->qwtPlot_StandardizedTo100->replot();
}

void SixSigma_QCRulesScreening::addWidgetToStackedWidget(QWidget *widget, int index)
{
    if(ui->stackedWidget->widget(index) != NULL)
    {
        QWidget *deleteWidget = ui->stackedWidget->widget(index);
        delete deleteWidget;
        deleteWidget = NULL;
    }

    ui->stackedWidget->insertWidget(index,widget);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->count() - 1);
}

void SixSigma_QCRulesScreening::saveParams()
{
    QFile file("evaluationParameter.csv");
    if(file.open(QFile::WriteOnly))
    {
        for(int i = 0; i < projectList.count(); i++)
        {
            int index =  pro2widget_Map[projectList[projectList.keys().at(i)]];
            EvaluationParameter *widget = (EvaluationParameter*)(ui->stackedWidget->widget(index));
            if(widget != NULL)
            {
                QString content;
                content.append(projectList[projectList.keys().at(i)]);
                content.append("," + QString::number(widget->Tea()));
                content.append("," + QString::number(widget->Bias()));
                content.append("," + QString::number(widget->Cv()));
                content.append("\r\n");
                file.write(content.toStdString().c_str());
            }
        }
        file.close();
    }
}

void SixSigma_QCRulesScreening::getparams()
{
    QFile file("evaluationParameter.csv");
    if(file.open(QFile::ReadOnly))
    {
        while(!file.atEnd())
        {
            QString str = QString(file.readLine(1024));
            projectParamList.insert(str.left(str.indexOf(",")),str.mid(str.indexOf(",") + 1));
        }
        file.close();
    }
}

void SixSigma_QCRulesScreening::on_input_keyword_textChanged(const QString &arg1)
{
    InitProjects();
}

void SixSigma_QCRulesScreening::on_treeWidget_itemSelectionChanged()
{
    if(ui->treeWidget->currentItem()->child(0) != NULL)
    {
        return;
    }

    m_bNeedShow = true;
    ui->stackedWidget->setCurrentIndex(pro2widget_Map[ui->treeWidget->currentItem()->toolTip(0)]);
}

void SixSigma_QCRulesScreening::on_stackedWidget_currentChanged(int arg1)
{
    if(m_bNeedShow)
    {
        EvaluationParameter *widget = (EvaluationParameter*)ui->stackedWidget->widget(arg1);

        double Tea, Bias, Cv, Sigma;

        Tea = widget->Tea();
        Bias = widget->Bias();
        Cv = widget->Cv();
        Sigma = widget->Sigma();

        drawMedicalDecisionChart(Tea, Bias, Cv);
    }
}

void SixSigma_QCRulesScreening::slt_hasParamChanged()
{
    m_bParamChanged = true;

    if(m_bNeedShow)
    {
        EvaluationParameter *widget = (EvaluationParameter*)ui->stackedWidget->currentWidget();
        if(widget == NULL)
        {
            return;
        }
        double Tea, Bias, Cv;

        Tea = widget->Tea();
        Bias = widget->Bias();
        Cv = widget->Cv();

        drawMedicalDecisionChart(Tea, Bias, Cv);

        draw_100PercentMedicalDecisionChart();
    }
}

void SixSigma_QCRulesScreening::closeEvent(QCloseEvent *e)
{
    if(m_bParamChanged)
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle("参数修改提示");
        msgBox.setText("有参数被修改,是否保存?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes,"保存");
        msgBox.setButtonText(QMessageBox::No,"不保存");
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes)
        {
            saveParams();
        }
    }

    e->accept();
}

void SixSigma_QCRulesScreening::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if(item->child(column) != NULL)
    {
        return;
    }

    m_bNeedShow = true;
    ui->stackedWidget->setCurrentIndex(pro2widget_Map[item->toolTip(column)]);

    EvaluationParameter *widget = (EvaluationParameter*)ui->stackedWidget->currentWidget();
    if(widget != NULL)
    {
        drawMedicalDecisionChart(widget->Tea(),widget->Bias(),widget->Cv());
    }
}
