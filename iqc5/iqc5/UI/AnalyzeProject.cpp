#include "AnalyzeProject.h"
#include "ui_AnalyzeProject.h"
#include "Service/ProjectService.h"
#include "Service/CategoryService.h"
#include "ChartView.h"
#include "UI/TableView.h"
#include <QCheckBox>
#include <QMessageBox>
#include <qwt_plot.h>
#include <qwt_plot_tradingcurve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_panner.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qwt_text_label.h>
#include <qwt_math.h>
#include <qwt_symbol.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <math.h>
#include <QDebug>
#include <qevent.h>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintEngine>
#include <QPainter>
#include <QPrintDialog>
#include <QPixmap>
#include "UI/CustomQwtPlot.h"
#include "UI/Background.h"
#include "UI/daterangedialog.h"
#include "IRule.h"
#include "RuleManager.h"
#include <QMenu>
#include <QAction>
#include <QWidgetAction>
#include <QApplication>
#include <QProcess>
#include <QSettings>


AProcess::AProcess(QObject *parent)
{

}

AProcess::~AProcess()
{

}

void AProcess::setProgram(const QString &path)
{
    m_sProgram = path;
}

void AProcess::run()
{
    QProcess::execute(m_sProgram);
}



AnalyzeProject::AnalyzeProject(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnalyzeProject)
{
    ui->setupUi(this);

    pop = new PopBox();

    lastListWidgetItem = NULL;

    ui->splitter->setCollapsible(0,true);

    ui->btnImport->setVisible(false);

    InitRules();
    InitProjects();
}

void AnalyzeProject::SetMode(int mode)
{
    this->mode = mode;
    if(mode == 1)
    {
        ui->groupBox_2->setVisible(true);
//        ui->groupBox->setVisible(false);
//    }
//    if(mode == 2)
//    {
//        ui->groupBox_2->setVisible(false);
        ui->groupBox->setVisible(true);
    }
    if(mode == 3)
    {
        ui->groupBox_2->setVisible(true);
        ui->groupBox->setVisible(false);
    }
    if(mode == 4)
    {
        ui->groupBox_2->setVisible(true);
        ui->groupBox->setVisible(false);
    }
}

CustomQwtPlot *AnalyzeProject::getChart()
{
    CustomQwtPlot *customQwtPlot= (CustomQwtPlot *)(ui->tabWidget->widget(ui->tabWidget->currentIndex()));

    return customQwtPlot;
}

AnalyzeProject::~AnalyzeProject()
{
    delete ui;
}

void AnalyzeProject::InitProjects()
{
    ProjectService *service;
    service = new ProjectService();
    QString keyword = ui->inputKeyword->text();

    ui->treeWidget->clear();

    QVector<Project> projects =  service->SearchProject("","",keyword,"");

    if(projects.count() > 0)
    {
        QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<projects[0].testType.SubjectName);
        ui->treeWidget->addTopLevelItem(ca);
        QTreeWidgetItem* ca2 = new QTreeWidgetItem(QStringList() << projects[0].testType.CategoryName);
        ca2->setToolTip(0, projects[0].testType.CategoryId);
        ca->addChild(ca2);
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList() << projects[0].CustomName);
        pItem->setToolTip(0, QString("%1").arg(projects[0].ProjectId));
        ca2->addChild(pItem);

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
                ca2->setToolTip(0, projects[i].testType.CategoryId);
                ca->addChild(ca2);
            }

            QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<projects[i].CustomName);
            pItem->setToolTip(0, QString("%1").arg(projects[i].ProjectId));
            ca2->addChild(pItem);
        }

    }
    ui->treeWidget->expandAll();

//    ShowProjectResult();
}

void AnalyzeProject::InitRules()
{
    needDisplay = false;

    //指控规则复选框
    QCheckBox *Rule12S = new  QCheckBox;
    Rule12S->setObjectName("Rule12S");
    Rule12S->setText("12S");
//    connect(Rule12S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule12S);
    list.append(Rule12S);

    QCheckBox *Rule12dot5S = new  QCheckBox;
    Rule12dot5S->setObjectName("Rule12.5S");
    Rule12dot5S->setText("12.5S");
//    connect(Rule12dot5S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule12dot5S);
    list.append(Rule12dot5S);


    QCheckBox *Rule13S = new  QCheckBox;
    Rule13S->setObjectName("Rule13S");
    Rule13S->setText("13S");
//    connect(Rule13S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule13S);
    list.append(Rule13S);

    QCheckBox *Rule13dot5S = new  QCheckBox;
    Rule13dot5S->setObjectName("Rule13.5S");
    Rule13dot5S->setText("13.5S");
//    connect(Rule13dot5S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule13dot5S);
    list.append(Rule13dot5S);

    QCheckBox *Rule14S = new  QCheckBox;
    Rule14S->setObjectName("Rule14S");
    Rule14S->setText("14S");
//    connect(Rule14S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule14S);
    list.append(Rule14S);

    QCheckBox *Rule15S = new  QCheckBox;
    Rule15S->setObjectName("Rule15S");
    Rule15S->setText("15S");
//    connect(Rule14S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule15S);
    list.append(Rule15S);

    QCheckBox *Rule22S = new  QCheckBox;
    Rule22S->setObjectName("Rule22S");
    Rule22S->setText("22S");
//    connect(Rule22S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule22S);
    list.append(Rule22S);

    QCheckBox *Rule2of32S = new  QCheckBox;
    Rule2of32S->setObjectName("Rule2of32S");
    Rule2of32S->setText("2/32S");
//    connect(Rule2of32S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule2of32S);
    list.append(Rule2of32S);

    QCheckBox *RuleR4S = new  QCheckBox;
    RuleR4S->setObjectName("RuleR4S");
    RuleR4S->setText("R4S");
//    connect(RuleR4S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(RuleR4S);
    list.append(RuleR4S);

    QCheckBox *Rule31S = new  QCheckBox;
    Rule31S->setObjectName("Rule31S");
    Rule31S->setText("31S");
//    connect(Rule31S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule31S);
    list.append(Rule31S);

    QCheckBox *Rule41S = new  QCheckBox;
    Rule41S->setObjectName("Rule41S");
    Rule41S->setText("41S");
//    connect(Rule41S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule41S);
    list.append(Rule41S);

    QCheckBox *Rule6T = new  QCheckBox;
    Rule6T->setObjectName("Rule6T");
    Rule6T->setText("6T");
//    connect(Rule6T, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule6T);
    list.append(Rule6T);

    QCheckBox *Rule9X = new  QCheckBox;
    Rule9X->setObjectName("Rule9X");
    Rule9X->setText("9X");
//    connect(Rule9X, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule9X);
    list.append(Rule9X);

    QCheckBox *Rule10X = new  QCheckBox;
    Rule10X->setObjectName("Rule10X");
    Rule10X->setText("10X");
//    connect(Rule10X, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule10X);
    list.append(Rule10X);

//    needDisplay = true;

}


void AnalyzeProject::ShowProjectResult()
{

    needDisplay = false;

    ProjectService *service;
    service = new ProjectService();
    QString projectId = ui->treeWidget->currentItem()->toolTip(0);
    currentProject = service->GetById(projectId);

    QVector <QString> rules = service->GetRules(currentProject.testType.TestTypeId);


    ui->listWidget->clear();

    foreach(QString string, rules)
    {
        if(string.endsWith("|"))
        {
            string = string.mid(0, string.count()-1);
        }

        ui->listWidget->addItem(new QListWidgetItem(string));
    }
    ui->listWidget->setCurrentRow(0);



    DrawProjectChart();


    needDisplay = true;

}

void AnalyzeProject::DrawProjectChart()
{
    Project &p = currentProject;

    //计算是否符合规则
    allData.clear();
    for(int i=1 ;i <= p.level; i++)
    {
        ProjectService service;
        QVector<Result> result1 = service.GetResult(p.ProjectId,i,ui->cbkShowAll->isChecked());
        allData.append(result1);
    }


    CheckData();

    ui->inputN->setCurrentIndex(allData.count() - 1);

    if(mode == 1)
    {
        //LJ图
        DrawLjChart();
//    }
//    else if(mode == 2)
//    {
        //Z图
        DrawZChart();
    }
    else if(mode == 3)
    {
        DrawBarChart();
    }
    else if(mode == 4)
    {
        DrawTargetChart();
    }
}

void AnalyzeProject::CheckData()
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

    QVector<double> lv_means;
    QVector<double> lv_sds;
    for(int level = 0; level < allData.count(); level++)
    {
        double avg;
        double sd;

        ProjectService ps;

        if(mode == 1)
        {
            if(level < ui->tabWidget->count())
            {
                CustomQwtPlot * cusQwtPlot = (CustomQwtPlot *)(ui->tabWidget->widget(level));

                if(cusQwtPlot != NULL)
                {
                    if(cusQwtPlot->IfCaculate->isChecked())
                    {
                        avg = cusQwtPlot->txtAvg->text().toDouble();
                        sd = cusQwtPlot->txtSd->text().toDouble();
                    }
                    else
                    {
                        avg = cusQwtPlot->inputCustAvg->text().toDouble();
                        sd = cusQwtPlot->inputCustSD->text().toDouble();
                    }
                }
                else
                {
                    avg = 0.0;
                    sd = 0.0;
                }
            }
            else
            {

                avg = ps.getAvg(currentProject.ProjectId, level + 1);
                sd = ps.getSd(currentProject.ProjectId, level + 1);
            }
        }
        else
        {
            avg = ps.getAvg(currentProject.ProjectId, level + 1);
            sd = ps.getSd(currentProject.ProjectId, level + 1);
        }


        lv_means.push_back(avg);
        lv_sds.push_back(sd);
    }

    if(ui->listWidget->currentItem() != NULL)
    {
        QString rule = ui->listWidget->currentItem()->text();
        QStringList filterResultIds;   //不参与规则计算的结果Id值
        ProjectService ps;

        filterResultIds = ps.GetResultIdFromComputatonResult(currentProject.ProjectId);
        p.CaculateByRule(allData,rule,lv_means,lv_sds,filterResultIds);  //计算规则
    }


    //n>1各个浓度联合判断 有一个不符合就都算不符合
    if(ui->listWidget->currentRow() >= 0)
    {
        int n = 1;
        QString s = ui->listWidget->currentItem()->text();
        if(s.split(",n=").count() == 2)
        {
            n = s.split(",n=").at(1).toInt();
        }
        if(n == p.level)
        {
            for(int i = 0;i < allData[0].count(); i++)
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
}


bool AnalyzeProject::InitCheckData(QVector<QVector<Result> > av_data, QString timeSplitString)
{

    QString startDate = timeSplitString.left(timeSplitString.indexOf(","));
    QString endDate = timeSplitString.mid(timeSplitString.indexOf(",") + 1);

    if( av_data[ui->tabWidget->currentIndex()].count() < 20)
    {
        if(timeSplitString == "")
        {
            QMessageBox::information(this,
                                     "提示",
                                     ("数据不足20个，不能进行初始化操作"));
        }
        else
        {
            QMessageBox::information(this,
                                     "提示",
                                     QString("日期从%1到%2之间共%3个数据，不足20个，不能进行初始化操作").arg(startDate).arg(endDate).arg(QString::number(av_data[ui->tabWidget->currentIndex()].count())));
        }

        return false;
    }

    int level = ui->tabWidget->currentIndex();

    for(int  i = 0; i < av_data[level].count(); i++)
    {
        av_data[level][i].isValid = true;
        av_data[level][i].refuseReason = "";
    }

    //是否符合规则
    Project p;
    QVector<double> avgs;
    QVector<double> sds;
    for(int i = 0; i < av_data.count(); i ++)
    {
        double sd = 0, avg = 0;
        avg = p.GetAverage(av_data[i],"","");
        sd = p.GetStandardDeviation(av_data[i],"","");
        avgs.push_back(avg);
        sds.push_back(sd);
    }



    QVector<QVector<double> > d;
    for(int i = 0;  i < av_data.count(); i++)
    {
        QVector<double> dd;
        for(int j = 0; j < av_data[i].count(); j++)
        {
            dd.append(av_data[level][i].value);
        }
        d.append(dd);
    }

    IRule *rule = RuleManager::GetRule("13S", avgs, sds, av_data);  //只选择13S规则
    for(int i = 0; i < av_data[level].count(); i++)
    {
        bool valid =  rule->IsValid(level,i);
        if(!valid)
        {
            av_data[level][i].isValid =false;
        }
    }

    //找出有问题的质控点
    QString errPointsStr;
    int err_count = 0;

    errPointsStr.append("以下质控点无效，请删除重做");

    for(int i = 0; i < av_data.count(); i++)
    {
        if(!av_data[level][i].isValid)
        {
            err_count++;
            errPointsStr += (QString("\n%1：日期：%2,水平：L%3，结果：%4 违反13S规则").arg(err_count).arg(av_data[level][i].TestTime).arg(av_data[level][i].level).arg(av_data[level][i].value));
        }
    }

    if(err_count > 0)
    {
        QMessageBox::information(this,
                                 "提示",
                                 errPointsStr);
        return false;

    }

    return true;
}

//Levey-Jenning质控图
void AnalyzeProject::DrawLjChart()
{

    this->ui->tabWidget->clear();

    //画曲线
    int allDataCount = 0;
    for(int h=0;h<allData.count();h++)
    {
        ProjectService *service; service = new ProjectService();
        //初始化前先从数据库获取之前的日期，否责数据会被修改
        QDate startDate = QDate::fromString(service->getStartTime(currentProject.ProjectId,h+1), "yyyy-MM-dd");
        if(startDate.isNull())
        {
            startDate.setDate(QDate::currentDate().year(),QDate::currentDate().month(),1);
        }
        QDate endDate   = QDate::fromString(service->getEndTime(currentProject.ProjectId,h+1), "yyyy-MM-dd");
        if(endDate.isNull())
        {
            endDate.setDate(QDate::currentDate().year(),QDate::currentDate().month(),QDate::currentDate().daysInMonth());
        }

        QVector<Result> data = allData[h];
        if(data.count()==0)
        {
            CustomQwtPlot* cchart = new CustomQwtPlot(this);
            QwtPlot* chart = cchart->getChart();
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
            this->ui->tabWidget->addTab(cchart, QString("L%1").arg(h+1));
            continue;
        }

        QString projectId = ui->treeWidget->currentItem()->toolTip(0);
        Project p = service->GetById(projectId);

        double max = p.GetMax(data);
        double min = p.GetMin(data);
        double avg = p.GetAverage(projectId,h+1);
        if(avg == 0)
        {
            avg = p.GetAverage(data,"","");
        }
        double sd = p.GetStandardDeviation(projectId,h+1);
        if(sd == 0)
        {
            sd = p.GetStandardDeviation(data,"","");
        }
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
        CustomQwtPlot* chart = new CustomQwtPlot(this);
        chart->current_projectId = ui->treeWidget->currentItem()->toolTip(0);
        chart->current_level = h + 1;
        chart->IfCaculate->setChecked(true);
        chart->inputCustAvg->setText(QString::number(avg, 'f', 2));
        chart->txtAvg->setText(QString::number(avg, 'f', 2));
        chart->inputCustSD->setText(QString::number(sd, 'f', 2));
        chart->txtSd->setText(QString::number(sd, 'f', 2));
        chart->txtCV->setText(QString::number(cv, 'f', 2)+'%');
        chart->txtCustCV->setText(QString::number(cv, 'f', 2)+'%');
        chart->txt6sigma->setText(QString::number(sigma6, 'f', 2));
        chart->txtCust6sigma->setText(QString::number(sigma6, 'f', 2));

        connect(chart->inputStartDate,SIGNAL(dateChanged(QDate)),this,SLOT(on_inputStartDate_Changed(QDate)));
        connect(chart->inputEndDate,SIGNAL(dateChanged(QDate)),this,SLOT(on_inputEndDate_Changed(QDate)));
        connect(chart->inputCustAvg, SIGNAL(textChanged(QString)), this, SLOT(on_inputCustAvg_textChanged(QString)));
        connect(chart->inputCustSD, SIGNAL(textChanged(QString)), this, SLOT(on_inputCustSD_textChanged(QString)));
        connect(chart->IfCustum, SIGNAL(toggled(bool)), this, SLOT(on_IfCaculate_toggled(bool)));
        connect(chart->btnCaculate, SIGNAL(clicked()), this, SLOT(on_btnCaculate_clicked()));
        connect(chart->btnInit, SIGNAL(clicked()), this, SLOT(on_btnInit_clicked()));

        chart->inputStartDate->setDate(startDate);
        chart->inputEndDate->setDate(endDate);
        allDataCount +=data.count();
        chart->txtN->setText(QString("%1").arg(service->getN(currentProject.ProjectId,h+1)));

        if(data.count()>0)
        {
            chart->SetTitle("          " + currentProject.CustomName + "    日期：" + QString("%1").arg(data[0].TestTime) + "至"+ QString("%1").arg(data[data.count()-1].TestTime
                + "    数据：" + QString("%1").arg(data.count())+ "个"));
        }
        else
        {
            chart->SetTitle("          " + currentProject.CustomName);
        }

        this->DrawLjChart(chart->getChart(), h, avg, sd, min, max, data);
        this->ui->tabWidget->addTab(chart, QString("L%1").arg(h+1));
    }

    ui->tabWidget->setCurrentIndex(currentIndex);
}

void AnalyzeProject::DrawLjChart(QwtPlot*chart, int level, double avg, double s, double min, double max, QVector<Result> data)
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
    for(int i=0;i<count;i++)
    {
        QwtPlotMarker *mPos = new QwtPlotMarker("Marker");
        mPos->setRenderHint(QwtPlotItem::RenderAntialiased, true);
        mPos->setItemAttribute(QwtPlotItem::Legend, false);
        QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse, QColor(color), QPen(color), QSize(7.5, 7.5));
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
        QwtSymbol *symbolErr = new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush, QPen(Qt::red, 2), QSize(9, 9)) ;
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

void AnalyzeProject::DrawBarChart()
{
    this->ui->tabWidget->clear();

    //画曲线
    int allDataCount = 0;
    for(int h=0;h<allData.count();h++)
    {
        QVector<Result> data = allData[h];
        if(data.count()==0)
        {
            CustomQwtPlot* cchart = new CustomQwtPlot(this);
            QwtPlot* chart = cchart->getChart();
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
            this->ui->tabWidget->addTab(cchart, QString("L%1").arg(h+1));
            continue;
        }

        ProjectService *service; service = new ProjectService();
        QString projectId = ui->treeWidget->currentItem()->toolTip(0);
        Project p = service->GetById(projectId);

        double max = p.GetMax(data);
        double min = p.GetMin(data);
        double avg = p.GetAverage(projectId,h+1);
        if(avg == 0)
        {
            avg = p.GetAverage(data,"","");
        }
        double sd = p.GetStandardDeviation(projectId,h+1);
        if(sd == 0)
        {
            sd = p.GetStandardDeviation(data,"","");
        }
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

        connect(chart->inputCustAvg, SIGNAL(textChanged(QString)), this, SLOT(on_inputCustAvg_textChanged(QString)));
        connect(chart->inputCustSD, SIGNAL(textChanged(QString)), this, SLOT(on_inputCustSD_textChanged(QString)));
        connect(chart->IfCustum, SIGNAL(toggled(bool)), this, SLOT(on_IfCaculate_toggled(bool)));
        connect(chart->btnCaculate, SIGNAL(clicked()), this, SLOT(on_btnCaculate_clicked()));
        connect(chart->btnInit, SIGNAL(clicked()), this, SLOT(on_btnInit_clicked()));

        chart->inputStartDate->setDate(QDate::fromString(service->getStartTime(currentProject.ProjectId,h+1), "yyyy-MM-dd"));
        chart->inputEndDate->setDate(QDate::fromString(service->getEndTime(currentProject.ProjectId,h+1), "yyyy-MM-dd"));
        allDataCount +=data.count();
        chart->txtN->setText(QString("%1").arg(service->getN(currentProject.ProjectId,h+1)));

        if(data.count()>0)
        {
            chart->SetTitle("          " + currentProject.CustomName + "    日期：" + QString("%1").arg(data[0].TestTime) + "至"+ QString("%1").arg(data[data.count()-1].TestTime
                + "    数据：" + QString("%1").arg(data.count())+ "个"));
        }
        else
        {
            chart->SetTitle("          " + currentProject.CustomName);
        }


        QVector<QwtOHLCSample> sampleList;
        for(int i=0;i<data.count();i++)
        {
            QwtOHLCSample sample;
            sample.open = avg;
            sample.close = data[i].value;
            if(sample.close>avg)
            {
                sample.low = avg;
                sample.high =sample.close + sd;
            }
            else if(sample.close<avg)
            {
                sample.high =avg;
                sample.low = data[i].value - sd;
            }
            sample.time = i;
            sampleList.append(sample);

        }

        this->DrawBarChart(chart->getChart(), h, avg, sd, min, max, sampleList);
        this->ui->tabWidget->addTab(chart, QString("L%1").arg(h+1));
    }

    ui->tabWidget->setCurrentIndex(currentIndex);
}

void AnalyzeProject::DrawBarChart(QwtPlot*chart, int level, double avg, double s, double min, double max, QVector<QwtOHLCSample> data)
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
    QwtPlotTradingCurve *qcCurve;qcCurve = new QwtPlotTradingCurve();
    qcCurve->setTitle("test");
    qcCurve->setOrientation( Qt::Vertical );
    qcCurve->setSymbolPen(colors[level]);
    qcCurve->setSymbolBrush( QwtPlotTradingCurve::Decreasing, Qt::white );
    qcCurve->setSymbolBrush( QwtPlotTradingCurve::Increasing, Qt::white );

    qcCurve->setSymbolExtent( 12 * 3600 * 1000.0 );
    qcCurve->setMinSymbolWidth( 3 );
    qcCurve->setMaxSymbolWidth( 15 );
    qcCurve->attach(chart);

    qcCurve->setSamples(data);

    qcCurve->setTitle("L"+QString("%1").arg(level+1));

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

void AnalyzeProject::DrawTargetChart()
{
    this->ui->tabWidget->clear();

    //画曲线
    int allDataCount = 0;
    for(int h=0;h<allData.count();h++)
    {
        QVector<Result> data = allData[h];
        if(data.count()==0)
        {
            CustomQwtPlot* cchart = new CustomQwtPlot(this);
            QwtPlot* chart = cchart->getChart();
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
            this->ui->tabWidget->addTab(cchart, QString("L%1").arg(h+1));
            continue;
        }

        ProjectService *service; service = new ProjectService();
        QString projectId = ui->treeWidget->currentItem()->toolTip(0);
        Project p = service->GetById(projectId);

        double max = p.GetMax(data);
        double min = p.GetMin(data);
        double avg = p.GetAverage(projectId,h+1);
        if(avg == 0)
        {
            avg = p.GetAverage(data,"","");
        }
        double sd = p.GetStandardDeviation(projectId,h+1);
        if(sd == 0)
        {
            sd = p.GetStandardDeviation(data,"","");
        }
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

        connect(chart->inputCustAvg, SIGNAL(textChanged(QString)), this, SLOT(on_inputCustAvg_textChanged(QString)));
        connect(chart->inputCustSD, SIGNAL(textChanged(QString)), this, SLOT(on_inputCustSD_textChanged(QString)));
        connect(chart->IfCustum, SIGNAL(toggled(bool)), this, SLOT(on_IfCaculate_toggled(bool)));
        connect(chart->btnCaculate, SIGNAL(clicked()), this, SLOT(on_btnCaculate_clicked()));
        connect(chart->btnInit, SIGNAL(clicked()), this, SLOT(on_btnInit_clicked()));

        chart->inputStartDate->setDate(QDate::fromString(service->getStartTime(currentProject.ProjectId,h+1), "yyyy-MM-dd"));
        chart->inputEndDate->setDate(QDate::fromString(service->getEndTime(currentProject.ProjectId,h+1), "yyyy-MM-dd"));
        allDataCount +=data.count();
        chart->txtN->setText(QString("%1").arg(service->getN(currentProject.ProjectId,h+1)));

        if(data.count()>0)
        {
            chart->SetTitle("          " + currentProject.CustomName + "    日期：" + QString("%1").arg(data[0].TestTime) + "至"+ QString("%1").arg(data[data.count()-1].TestTime
                + "    数据：" + QString("%1").arg(data.count())+ "个"));
        }
        else
        {
            chart->SetTitle("          " + currentProject.CustomName);
        }

        this->DrawTargetChart(chart->getChart(), h, avg, sd, min, max, data);
        this->ui->tabWidget->addTab(chart, QString("L%1").arg(h+1));
    }
    ui->tabWidget->setCurrentIndex(currentIndex);

}

void AnalyzeProject::DrawTargetChart(QwtPlot*chart, int level, double avg, double s, double min, double max, QVector<Result> data)
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

    qcCurve->setStyle(QwtPlotCurve::Dots);
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

bool AnalyzeProject::eventFilter(QObject *object, QEvent *e)
{


    switch(e->type())
    {
    case QEvent::MouseButtonDblClick:
    {
//        if(mode != 2)
//        {
//            //放大
//            ChartView *c; c = new ChartView();
//            ProjectService *service; service = new ProjectService();
//            QVector<Project> projects =  service->SearchProject("","",ui->inputKeyword->text(),"");
//            int index = 0;
//            for(int i=0;i<projects.count();i++)
//            {
//                if(projects[i].ProjectId == currentProject.ProjectId)
//                {
//                    index = i;
//                    break;
//                }
//            }

//            QwtPlot* chart = (QwtPlot*)object->parent();
//            double avg[10];
//            double sd[10];
//            for(int i=0;i<ui->tabWidget->count();i++)
//            {
//                CustomQwtPlot *cqp = (CustomQwtPlot*)(ui->tabWidget->widget(i));
//                if(cqp->IfCustum)
//                {
//                    avg[i] = cqp->inputCustAvg->text().toDouble();
//                    sd[i] = cqp->inputCustSD->text().toDouble();
//                }
//                else
//                {
//                    avg[i]=cqp->txtAvg->text().toDouble();
//                    sd[i]=cqp->txtSd->text().toDouble();
//                }
//            }
//            int currentIndex = ui->tabWidget->currentIndex();
//            c->initRules(projects[index].testType.TestTypeId, ui->listWidget->currentText());
//            if(chart->parent()->parent() == ui->widget_Z)
//            {
//                c->DrawZChart(projects, index, ui->listWidget->currentText(), avg, sd, ((CustomQwtPlot*)(ui->tabWidget->widget(currentIndex)))->IfCustum->isChecked());
//            }
//            else
//            {
//                c->DrawLjChart(projects, index, ui->listWidget->currentText(), avg, sd, ((CustomQwtPlot*)(ui->tabWidget->widget(currentIndex)))->IfCustum->isChecked());
//            }
//            c->showMaximized();
//            return true;
//        }
    }
    case QEvent::MouseButtonPress:
    {
        QwtPlot* chart = (QwtPlot*)object->parent();
        select(chart, ((QMouseEvent *)e)->pos());
        return true;
    }
    case QEvent::MouseMove:
    {
        //const QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        //QPoint p = mouseEvent->pos();

    }
    default:
        break;
    }

    return QObject::eventFilter(object, e);
}

void AnalyzeProject::select(QwtPlot* chart, const QPoint &pos)
{
    QwtPlotCurve *curve = NULL;
    double dist = 5;
    int index = -1;

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
                index = idx;

                int l = curve->title().text().replace("L","").toInt();
                if(pop->level != l || pop->no != idx) //换了个点
                {
                    QVector<Result> result;

                    if(chart->parent()->parent() == ui->widget_Z)
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

//wchar_t *AnalyzeProject::char2wchar(char *src)
//{
//    size_t len = strlen(src) + 1;
//    size_t converted = 0;
//    wchar_t *WStr;
//    WStr=(wchar_t*)malloc(len*sizeof(wchar_t));
//    mbstowcs_s(&converted, WStr, len, src, _TRUNCATE);

//    return WStr;
//}

#ifdef Q_OS_WIN

void AnalyzeProject::SendCommand(const char *uft8_handle)
{
    char str[] = "COMMAND_IMPORT";

    QString m_hw = QString::fromUtf8(uft8_handle);
    qDebug() << m_hw;

    COPYDATASTRUCT cpd;
    cpd.dwData = 0;
    cpd.cbData = 15;
    cpd.lpData = str;
    HWND hWndRcv=::FindWindow(NULL,m_hw.toStdWString().c_str());
    if(hWndRcv == NULL)
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("提示");
        msgbox.setText("数据导入程序未启动");
        msgbox.setStandardButtons(QMessageBox::Yes);
        msgbox.setButtonText(QMessageBox::Yes,"确定");
        msgbox.exec();
    }
    else
    {
        ::SendMessageW(hWndRcv, WM_COPYDATA, NULL, (LPARAM)&cpd);
    }
}
#endif

//Z分数质控图
void AnalyzeProject::DrawZChart()
{
    double avg[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double sd[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

//    ProjectService ps;
//    Project pp;
//    for(int i = 0; i < allData.count(); i++)
//    {
//        avg[i] = ps.getAvg(currentProject.ProjectId, i + 1);
//        sd[i] = ps.getSd(currentProject.ProjectId, i + 1);

//        if(avg[i] ==  0.0)
//        {
//            avg[i] = pp.GetAverage(allData[i],"",i + 1);
//        }

//        if(sd[i] == 0.0)
//        {
//            sd[i] = pp.GetStandardDeviation(allData[i],"",i + 1);
//        }
//    }

    for(int i=0;i<ui->tabWidget->count();i++)
    {
        CustomQwtPlot *cqp = (CustomQwtPlot*)(ui->tabWidget->widget(i));
        if(cqp->IfCustum)
        {
            avg[i] = cqp->inputCustAvg->text().toDouble();
            sd[i] =  cqp->inputCustSD->text().toDouble();
        }
        else
        {
            avg[i ]= cqp->txtAvg->text().toDouble();
            sd[i] = cqp->txtSd->text().toDouble();
        }
    }


    Project p;

    int allDataCount=0;
    for(int i=0;i<allData.count();i++)
    {
        if(i < allData.count())
        {
            p.CaculateZ(&allData[i],avg[i],sd[i]);
        }
        else
        {
            p.CaculateZ(&allData[i],0,0);
        }
        allDataCount +=allData[i].count();
    }

    QVector< QVector<Result> > allData_z = p.ReSort(allData);

    CustomQwtPlot* custChart = new CustomQwtPlot(this);
    if(ui->layout_z->count()>0)
    {
        ui->layout_z->removeWidget(chart_z);
    }
    ui->layout_z->addWidget(custChart);
    chart_z = custChart;
    chart_z->widget_4->setHidden(true);
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
        custChart->SetTitle("          " + currentProject.CustomName + "    日期：" + QString("%1").arg(allData[0][0].TestTime) + "至"+ QString("%1").arg(allData[0][allData[0].count()-1].TestTime
                + "    数据：" + QString("%1").arg(allDataCount)+ "个"));
    }
    else
    {
        custChart->SetTitle("          " + currentProject.CustomName);
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

        //QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse, QColor(colors[h%7]), QPen(colors[h%7]), QSize(10, 10));
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

        for(int i=0;i<count;i++)
        {
            QwtPlotMarker *mPos = new QwtPlotMarker("Marker");
            mPos->setRenderHint(QwtPlotItem::RenderAntialiased, true);
            mPos->setItemAttribute(QwtPlotItem::Legend, false);
            QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse, QColor(color), QPen(color), QSize(7.5, 7.5));

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
            QwtSymbol *symbolErr = new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush, QPen(Qt::red, 1), QSize(9, 9)) ;
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

void AnalyzeProject::ShowTable(QString title, int rowCount, QVector< QVector<Result> > allData)
{

    TableView *table;table = new TableView();
    table->setWindowTitle(title);
    table->ShowTable(rowCount, allData);
    table->show();
}

void AnalyzeProject::on_btnCancel_clicked()
{
    this->close();
}


void AnalyzeProject::on_inputKeyword_textChanged(const QString &arg1)
{
    InitProjects();
}

void AnalyzeProject::on_checkBox_stateChanged()
{
    if(needDisplay)
        DrawProjectChart();

}

void AnalyzeProject::on_btnAddRule_clicked()
{
    //加到右边
    QObjectList list = ui->ruleGroup->children();
    QCheckBox *chk;
    QString multiRule;
    foreach (QObject *obj, list)
    {
        qDebug() << obj->objectName();
        chk = qobject_cast<QCheckBox*>(obj);
        if(chk && chk->checkState() == Qt::Checked)
        {
            multiRule.append(chk->text()).append("|");
            chk->setChecked(false);


            if(multiRule.endsWith("|"))
            {
                multiRule = multiRule.mid(0, multiRule.count()-1);
            }
            multiRule.append(QString(",n=%1").arg(ui->inputN->currentIndex() + 1));
            ui->listWidget->addItem(new QListWidgetItem(multiRule));

            //保存
            ProjectService *s = new ProjectService();
            QVector<QString> rules;
            for  (int i=0; i<ui->listWidget->count(); i++)
            {
                rules.append(ui->listWidget->item(i)->text());
            }
            s->SetDefaultRule(currentProject.testType.TestTypeId, rules);

            if(ui->listWidget->count() == 1)
            {
                ui->listWidget->setCurrentRow(0);
            }
        }
    }

}

void AnalyzeProject::on_listWidget_doubleClicked(const QModelIndex &index)
{
    /*

      双击删除该规则代码(已作废)

    if(ui->listWidget->currentRow()>=0)
    {
        QListWidgetItem *item = ui->listWidget->takeItem(ui->listWidget->currentRow());
        delete item;
    }

    //保存
    ProjectService *s = new ProjectService();
    QVector<QString> rules;
    for  (int i=0; i<ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        rules.append(item->text());
    }
    s->SetDefaultRule(currentProject.testType.Id, rules);

    if(needDisplay)
        DrawProjectChart();

    */

    //双击在下面的框中按照选中的规则进行计算
//    DrawProjectChart();

}

void AnalyzeProject::on_btnExport_clicked()
{
    /*
    QString strFilePath = QFileDialog::getSaveFileName(this,tr("保存为"),QString("%1.csv").arg(currentProject.CustomName));
    QFile file(strFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::information(NULL, tr("提示信息："), tr("未能打开文件"));
        return;
    }
    QTextStream out(&file);

    int currentLevel = ui->tabWidget->currentIndex() + 1;

    out<<tr("项目名称:,")<<currentProject.ProjectName<<endl;
    out<<tr("日期:,")<<currentProject.GetMinDate(currentProject.GetResultByLevel(currentLevel,false))<<"  --  "<<currentProject.GetMaxDate(currentProject.GetResultByLevel(1,false))<<endl;
    out<<tr("平均值:,")<<currentProject.GetAverage(currentProject.GetResultByLevel(currentLevel,false))<<endl;
    out<<tr("标准差:,")<<currentProject.GetStandardDeviation(currentProject.GetResultByLevel(currentLevel,false))<<endl;
    out<<tr("CV:,")<<currentProject.GetRealCV(currentProject.GetResultByLevel(currentLevel,false))<<endl;
    out<<tr("6sigma:,")<<currentProject.Get6sigma(currentProject.GetResultByLevel(currentLevel,false))<<endl;
    out<<endl;
    out<<tr("日期")<<",";
    out<<tr("分析批")<<",";
    out<<tr("浓度")<<",";
    out<<tr("结果")<<",";
    out<<tr("是否在控")<<",";
    out<<tr("失控原因")<<endl;

    for(int h=0;h<allData.count();h++)
    {
        QVector<Result> result1 = allData[h];
        int num = result1.count();
        for(int i=0;i<num;i++)
        {
            out<<result1[i].CreateTime<<",";
            out<<result1[i].batch<<",";
            out<<result1[i].level<<",";
            out<<result1[i].value<<",";
            if(result1[i].isValid)
            {
                out<<tr("在控")<<",";

            }
            else
            {
                out<<tr("失控")<<",";

            }
            out<<"\""<<result1[i].refuseReason<<"\""<<endl;
        }
    }

    file.close();
    */

}

void AnalyzeProject::on_btnExportByType_clicked()
{
    ProjectService projectService;
    QVector<Project> project_total = projectService.GetSumProjectByType(currentProject.testType.TestTypeId);

    int currentLevel = ui->tabWidget->currentIndex() + 1;

    QString strFilePath = QFileDialog::getSaveFileName(this,tr("保存为"),QString("%1.csv").arg("汇总"));
    QFile file(strFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::information(NULL, tr("提示信息："), tr("未能打开文件"));
        return;
    }
    QTextStream out(&file);

    out<<tr("项目名称")<<",";
    out<<tr("开始时间")<<",";
    out<<tr("结束时间")<<",";
    out<<tr("平均值")<<",";
    out<<tr("标准差")<<",";
    out<<tr("CV")<<",";
    out<<tr("6sigma")<<endl;


    for(int i=0;i<project_total.count();i++)
    {
        Project p = project_total[i];
        out<<p.ProjectName<<",";
        QVector<Result> results = projectService.GetResult(currentProject.ProjectId,currentLevel,ui->cbkShowAll->isChecked());
        out<<p.GetMinDate(results)<<",";
        out<<p.GetMaxDate(results)<<",";
        out<<p.GetAverage(results,"","")<<",";
        out<<p.GetStandardDeviation(results,"","")<<",";
        out<<p.GetRealCV(results,"","")<<",";
        out<<p.Get6sigma(results,"","")<<endl;
    }

    file.close();
}

//void AnalyzeProject::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
//{
//    if( item->childCount() == 0)
//    {
//        ShowProjectResult();
//    }
//}

void AnalyzeProject::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(current != NULL && current->childCount() == 0)
    {
        ShowProjectResult();
    }
}

void AnalyzeProject::on_tabWidget_currentChanged(int index)
{

}


void AnalyzeProject::on_btnDataTable_clicked()
{
    ShowTable(currentProject.CustomName, currentProject.results.count(), allData);
}


void AnalyzeProject::on_btnPrint_clicked()
{

    //    QPrinter printer(QPrinter::HighResolution);
    //    QPrintDialog printDialog(&printer, this);
    //    if (printDialog.exec())
    //    {
    //        //准备
    //        QPixmap image;
    //        QRect r = ui->zChart->rect();
    //        image=image.grabWidget(ui->zChart,0, 0, r.width()+10, r.height()+10);


    //        //打印
    //        QPainter painter(&printer);
    //        QRect rect = painter.viewport();
    //        QSize size = image.size();
    //        size.scale(rect.size(), Qt::KeepAspectRatio);//此处保证图片显示完整
    //        painter.setViewport(rect.x(), rect.y(),
    //                            size.width(), size.height());
    //        painter.setWindow(image.rect());
    //        //painter.drawImage(0, 0, image);
    //        painter.drawPixmap(0,0,image);
    //    }
}

void AnalyzeProject::on_inputCustAvg_textChanged(const QString &arg1)
{
    CustomQwtPlot* chart = (CustomQwtPlot*)(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
    if(chart != NULL)
    {
        if(!chart->IfCaculate->isChecked())
        {
            int currentIndex = ui->tabWidget->currentIndex();
            ChangeChart(currentIndex);
        }
    }
}

void AnalyzeProject::on_inputCustSD_textChanged(const QString &arg1)
{
    CustomQwtPlot* chart = (CustomQwtPlot*)(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
    if(chart != NULL)
    {
        if(!chart->IfCaculate->isChecked())
        {
            int currentIndex = ui->tabWidget->currentIndex();
            ChangeChart(currentIndex);
        }
    }
}

void AnalyzeProject::on_inputStartDate_Changed(const QDate &date)
{
    ProjectService s;
    if (getChart()!= NULL)
    {
        s.UpdateComputationDate(currentProject.ProjectId,ui->tabWidget->currentIndex() + 1, date.toString("yyyy-MM-dd"), getChart()->inputEndDate->text());
        ChangeChart(ui->tabWidget->currentIndex());
    }
}

void AnalyzeProject::on_inputEndDate_Changed(const QDate &date)
{
    ProjectService s;
    getChart();
    if (getChart() != NULL)
    {
        s.UpdateComputationDate(currentProject.ProjectId,ui->tabWidget->currentIndex() + 1, getChart()->inputStartDate->text(), date.toString("yyyy-MM-dd"));
        ChangeChart(ui->tabWidget->currentIndex());
    }
}

void AnalyzeProject::on_IfCaculate_toggled(bool checked)
{
    CustomQwtPlot* chart = (CustomQwtPlot*)(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
    if(chart != NULL)
    {
        int currentIndex = ui->tabWidget->currentIndex();
        ChangeChart(currentIndex);
    }
}


void AnalyzeProject::ChangeChart(int currentIndex)
{
    if(currentIndex == -1)
    {
        return;
    }
    CustomQwtPlot* chart = (CustomQwtPlot*)(ui->tabWidget->widget(currentIndex));

    //计算是否符合规则
    allData.clear();
    for(int i=1;i <= currentProject.level;i++)
    {
        ProjectService service;
//        QVector<Result> result1 = service.GetResult(currentProject.ProjectId,i,ui->cbkShowAll->isChecked());
        QVector<Result> result1 = service.GetResult(currentProject.ProjectId, i, ((CustomQwtPlot*)ui->tabWidget->widget(currentIndex))->inputStartDate->text(), ((CustomQwtPlot*)ui->tabWidget->widget(currentIndex))->inputEndDate->text(), ui->cbkShowAll->isChecked());
        allData.append(result1);
    }


    CheckData();

    chart->SetTitle("          " + currentProject.CustomName + "    日期：" + QString("%1").arg(chart->inputStartDate->text()) + "至"+ QString("%1").arg(chart->inputEndDate->text())
                    + "    数据：" + QString("%1").arg(allData[currentIndex].count()) + "个");

    QVector<Result> data = allData[currentIndex];
    Project p;
    double max = p.GetMax(data);
    double min = p.GetMin(data);
    double avg, sd;
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
    else
    {
        avg = chart->txtAvg->text().toDouble();
        sd = chart->txtSd->text().toDouble();
    }

    this->DrawLjChart(chart->getChart(), currentIndex, avg, sd, min, max, data);

    this->DrawZChart();

}

void AnalyzeProject::on_btnImport_clicked()
{
    QString strFilePath = QFileDialog::getOpenFileName(this,tr("打开"));
    if (strFilePath.isNull())
    {
        return;
    }

    ProjectService s;
    bool needCaculate = false;
    bool needDelete = false;

    QMessageBox message1(QMessageBox::NoIcon, "信息", QString("需要保留原有数据吗?"), QMessageBox::Yes | QMessageBox::No, NULL);
    if(message1.exec() == QMessageBox::No)
    {
        needDelete = true;
    }

    QMessageBox message2(QMessageBox::NoIcon, "信息", QString("需要重新计算平均值和方差吗?"), QMessageBox::Yes | QMessageBox::No, NULL);
    if(message2.exec() == QMessageBox::Yes)
    {
        needCaculate = true;
    }
    s.Import(strFilePath,needDelete,needCaculate);

    DrawProjectChart();
    QMessageBox::information(NULL, tr("提示信息："), tr("导入成功"));
}

void AnalyzeProject::on_btnCaculate_clicked()
{
    DateRangeDialog *dialog = new DateRangeDialog;
    dialog->exec();

    if(dialog->m_state == DateRangeDialog::Cancel)
    {
        return;
    }

    QVector< QVector<Result> > lv_allData;

    ProjectService s;
    for(int i = 0; i < ui->tabWidget->count(); i++)
    {
        QVector<Result> lv_data;

        lv_data = s.GetResult(currentProject.ProjectId,dialog->m_startDate,dialog->m_endDate,ui->tabWidget->currentIndex() + 1);
        lv_allData.push_back(lv_data);
    }

    if (!InitCheckData(lv_allData, dialog->m_startDate + "," + dialog->m_endDate))  //初始化时的数据有效性检查
    {
        return;
    }

    currentIndex = ui->tabWidget->currentIndex();

    s.InsertComputation(currentProject.ProjectId,"",ui->tabWidget->currentIndex()+1,dialog->m_startDate, dialog->m_endDate);
//    s.UpdateComputationDate(currentProject.ProjectId, ui->tabWidget->currentIndex()+1, dialog->m_startDate, customQwtPlot->inputEndDate->date().toString("yyyy-MM-dd"));

    DrawProjectChart();
}

void AnalyzeProject::on_btnInit_clicked()
{
    QVector<QVector<Result> > lv_allData;

    ProjectService s;
    CustomQwtPlot *customQwtPlot= (CustomQwtPlot *)(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
    for(int i = 0; i < ui->tabWidget->count(); i++)
    {
        QVector<Result> lv_data;
        lv_data = s.GetResult(currentProject.ProjectId,customQwtPlot->inputStartDate->date().toString("yyyy-MM-dd"),customQwtPlot->inputEndDate->date().toString("yyyy-MM-dd"),ui->tabWidget->currentIndex() + 1,customQwtPlot->txtN->text().toInt());
        lv_allData.push_back(lv_data);
    }

    if (!InitCheckData(lv_allData))  //初始化时的数据有效性检查
    {
        return;
    }

    currentIndex = ui->tabWidget->currentIndex();

    int resultCount = s.GetResult(currentProject.ProjectId, ui->tabWidget->currentIndex() + 1,  customQwtPlot->inputStartDate->date().toString("yyyy-MM-dd"), customQwtPlot->inputEndDate->date().toString("yyyy-MM-dd"), ui->cbkShowAll->isChecked()).size();

    if ( resultCount < customQwtPlot->txtN->text().toInt() )
    {
        customQwtPlot->txtN->setText(QString::number(resultCount));
    }

    s.InsertComputation(currentProject.ProjectId,"",ui->tabWidget->currentIndex()+1,customQwtPlot->inputStartDate->date().toString("yyyy-MM-dd"), customQwtPlot->txtN->text().toInt());
    s.UpdateComputationDate(currentProject.ProjectId, ui->tabWidget->currentIndex()+1, customQwtPlot->inputStartDate->date().toString("yyyy-MM-dd"), customQwtPlot->inputEndDate->date().toString("yyyy-MM-dd"));

    DrawProjectChart();
}

void AnalyzeProject::on_cbkShowAll_toggled(bool checked)
{
    DrawProjectChart();
}

void AnalyzeProject::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(item != NULL)
    {
        ui->listWidget->removeItemWidget(item);
        delete item;

        ProjectService ps;
        QVector<QString> rules;
        for  (int i=0; i<ui->listWidget->count(); i++)
        {
            QListWidgetItem *item = ui->listWidget->item(i);
            rules.append(item->text());
        }
        ps.SetDefaultRule(currentProject.testType.TestTypeId, rules);
    }
}

void AnalyzeProject::on_listWidget_itemSelectionChanged()
{
    DrawProjectChart();
}

void AnalyzeProject::on_dataImport_clicked()
{
    QSettings setting("iqc.ini",QSettings::IniFormat);
    setting.setIniCodec("UTF-8");
    const char *handle = setting.value("IMPORT_PROGRAM/handle","").toString().toStdString().c_str();
    SendCommand(handle);
}

