#include "Circle.h"
#include "ui_Circle.h"
#include "Service/ProjectService.h"
#include <QCheckBox>
#include <QMessageBox>
#include <qwt_plot.h>
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
#include <qpainter.h>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include "Service/CategoryService.h"
#include "Service/ProjectService.h"
#include "UI/CustomQwtPlot.h"
#include "UI/Background.h"
#include "UI/AnalyzeDevice.h"


Circle::Circle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Circle)
{
    ui->setupUi(this);

    ui->inputStartDate->setCalendarPopup(true);
    ui->inputEndDate->setCalendarPopup(true);

    InitTree();


    //得到规则
    ProjectService *service;service = new ProjectService();
    QVector <QString> rules = service->GetAllRules();
    {
        ui->listWidget->clear();
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

    InitRules();

    ui->inputStartDate->setDate(QDate::fromString(service->getStartTime("399005",1), "yyyy-MM-dd"));
    ui->inputEndDate->setDate(QDate::fromString(service->getEndTime("399005",1), "yyyy-MM-dd"));
    ui->txtN->setText(QString("n=%1").arg(service->getN("399005",1)));

}

Circle::~Circle()
{
    delete ui;
}

void Circle::InitTree()
{
    ui->treeWidget->clear();

    CategoryService categoryService;
    ProjectService projectService;
    QVector<Category> categories =  categoryService.GetCategories();

    if(categories.count() > 0)
    {
        for(int i=0;i<categories.count();i++)
        {
            QTreeWidgetItem* ca = new QTreeWidgetItem(QStringList()<<categories[i].CategoryName);
            ca->setToolTip(0, categories[i].CategoryId);
            ui->treeWidget->addTopLevelItem(ca);
            QVector<Category> subCategories =  categoryService.GetCategories(categories[i].CategoryId);
            for(int j=0;j<subCategories.count();j++)
            {
                QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList()<<subCategories[j].CategoryName);
                pItem->setToolTip(0, QString("%1").arg(subCategories[j].CategoryId));
                ca->addChild(pItem);

                QVector<QString> projects = projectService.GetProjectsDay(subCategories[j].CategoryId);
                for(int k=0;k<projects.count();k++)
                {
                    QTreeWidgetItem* pItem2 = new QTreeWidgetItem(QStringList()<<projects[k]);
                    pItem2->setToolTip(0, QString("%1").arg(projects[k]));
                    pItem->addChild(pItem2);
                }
            }
        }

    }
    ui->treeWidget->expandAll();
}

void Circle::GenerateData20()
{
    allData.clear();
    ProjectService service;
    QString categoryId = ui->treeWidget->currentItem()->parent()->toolTip(0);
    QVector<QString> dates= service.GetProjectsDay(categoryId);
    for(int i=0;i<dates.count();i++)
    {
        AddToAllDate(categoryId, dates[i]);
    }

    //计算面积
    int levelCount = service.GetLevelByCategoryId(categoryId);
    allAreaData.clear();

    for(int level=0;level<levelCount;level++)
    {
        QVector<Result> oneLevelAreaData;
        for(int i=0;i<allData.count();i++)
        {
            double area = 0;
            int NUM = allData[i][level][0].ResultNum;
            for(int j=0;j<NUM;j++)
            {
                double a = allData[i][level][j].value;
                double b = allData[i][level][(j+1)%NUM].value;

                //计算面积
                area +=  0.5 * sin(3.1415926*2 / NUM) * a * b;
            }
            Result result;
            result.TestTime = allData[i][level][0].TestTime;
            result.value = area;
            result.ResultNum = allData[i][level][0].ResultNum;
            oneLevelAreaData.append(result);
        }
        allAreaData.append(oneLevelAreaData);
    }
}


void Circle::AddToAllDate(QString categoryId, QString date)
{
    ProjectService service;

    QVector<Project> projects =service.GetProjectByCategoryId(categoryId);
    int levelCount = service.GetLevelByCategoryId(categoryId);

    QVector< QVector<Result> > dayData;
    for(int level=0;level<levelCount;level++)
    {
        QVector<Result> levelData;
        for(int i=0;i<projects.count();i++)
        {
            Result r;
            r.Memo = projects[i].CustomName;
            r.TestTime = date;
            r.value = projects[i].GetDayZ(level+1, date)+ 6;
            r.ResultNum = projects.count()>3 ? projects.count():3;
            levelData.append(r);
        }
        //少于3个项目没有的补0
        for(int i=0;i<3-projects.count();i++)
        {
            Result r;
            r.TestTime = date;
            r.value = 0 + 6;
            r.ResultNum = projects.count()>3 ? projects.count():3;
            levelData.append(r);
        }

        dayData.append(levelData);

    }
    allData.append(dayData);
}

void Circle::AddToDayDate(QString categoryId, QString date)
{
    ProjectService service;

    QVector<Project> projects =service.GetProjectByCategoryId(categoryId);
    int levelCount = service.GetLevelByCategoryId(categoryId);

    QVector< QVector<Result> > dayData;
    for(int level=0;level<levelCount;level++)
    {
        QVector<Result> levelData;
        for(int i=0;i<projects.count();i++)
        {
            Result r;
            r.TestTime = date;
            r.Memo = projects[i].CustomName;
            r.value = projects[i].GetDayZ(level+1, date)+ 6;
            r.ResultNum = projects.count()>3 ? projects.count():3;
            levelData.append(r);
        }
        //少于3个项目没有的补0
        for(int i=0;i<3-projects.count();i++)
        {
            Result r;
            r.TestTime = date;
            r.value = 0 + 6;
            r.ResultNum = projects.count()>3 ? projects.count():3;
            levelData.append(r);
        }

        dayData.append(levelData);

    }
    oneDayData.append(dayData);
}

void Circle::InitProjects()
{

    ShowProjectResult();

}

void Circle::InitRules()
{
}


void Circle::ShowProjectResult()
{
    needDisplay = false;

    if(ui->treeWidget->currentItem()!=NULL && ui->treeWidget->currentItem()->childCount() == 0)
    {
        //画图
        DrawCircleChart();
        DrawZChart();

    }
    needDisplay = true;

}


void Circle::DrawCircleChart()
{
    QString categoryId = ui->treeWidget->currentItem()->parent()->toolTip(0);
    QString date = ui->treeWidget->currentItem()->text(0);
    oneDayData.clear();
    AddToDayDate(categoryId, date);


    if(ui->verticalLayout_4->count() == 0)
    {
        c = new CircleView();
        ui->verticalLayout_4->addWidget(c);
    }
    c->paint(oneDayData, 6);//ui->add->itemText(ui->add->currentIndex()).toDouble()

    DrawZChart();
}

void Circle::DrawZChart()
{

    Project p;

    double avg = p.GetAverage("399005",1);
    double sd = p.GetStandardDeviation("399005",1);
    for(int i=0;i<allAreaData.count();i++)
    {
        p.CaculateZ(&allAreaData[i],avg,sd);
    }

    QVector< QVector<Result> > allData_z = p.ReSort(allAreaData);


    QwtPlot* chart = ui->totalChart;

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


void Circle::CheckData()
{
    for(int h=0;h<allAreaData.count();h++)
    {
        for(int j=0;j<allAreaData[h].count();j++)
        {
            allAreaData[h][j].isValid = true;
            allAreaData[h][j].refuseReason = "";
        }
    }
    //是否符合规则
    Project p;
//    for(int h=0;h<allAreaData.count();h++)
//    {
//        for(int i=0; i<ui->listWidget->count(); i++)
//        {
//            if(ui->listWidget->currentIndex() == i) //只根据选中的规则检查
//            {
//                QString s = ui->listWidget->itemText(i);

//                p.CaculateByRule(&allAreaData[h], s, 0, 0);
//            }
//        }
//    }

    //modify by heyi

    //n>1各个浓度联合判断 有一个不符合就都算不符合
    if(ui->listWidget->currentIndex()>=0)
    {
        int n = 1;
        QString s = ui->listWidget->currentText();
        if(s.split(",n=").count() == 2)
        {
            n = s.split(",n=").at(1).toInt();
        }
        if(n == p.level)
        {
            for(int i=0;i<allAreaData[0].count();i++)
            {
                QString s = "";
                bool isValid=true;
                for(int j=0;j<n;j++)
                {
                    if(allAreaData[j][i].isValid == false)
                    {
                        isValid = false;
                        s.append(allAreaData[j][i].refuseReason);
                    }
                }
                for(int j=0;j<n;j++)
                {
                    if(isValid == false)
                    {
                        allAreaData[j][i].isValid = false;
                        allAreaData[j][i].refuseReason = s;
                    }
                }
            }
        }
    }
}

 bool Circle::eventFilter(QObject *object, QEvent *e)
 {


     switch(e->type())
     {
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

 void Circle::select(QwtPlot* chart, const QPoint &pos)
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
             if ( d < dist )
             {
                 curve = c;
                 index = idx;

                 QStringList list = curve->title().text().split("|");
                 if(list.count() > 0 && idx < list.count())
                 {
                     if(list[idx].count()>0)
                     {
                         QMessageBox::information(this, tr("信息") , list[idx]);
                     }
                     else
                     {
                         QMessageBox::information(this, tr("信息") , "在控");
                     }

                 }
                 break;
             }
         }
     }
 }

void Circle::on_btnCancel_clicked()
{
    this->close();
}

void Circle::DrawTable()
{
    if(ui->treeWidget->currentItem() != NULL && ui->treeWidget->currentItem()->parent() != NULL && ui->treeWidget->currentItem()->childCount() == 0)
    {
        ProjectService service;
        QString categoryId = ui->treeWidget->currentItem()->parent()->toolTip(0);
        QString date = ui->treeWidget->currentItem()->text(0);
        QVector<Project> projects= service.GetProjectByCategoryAndDay(categoryId,date);

        ui->tableWidget->setColumnCount(projects.count());
        ui->tableWidget->setRowCount(3);
        QStringList headers;
        for(int i=0;i<projects.count();i++)
        {
            headers << projects[i].CustomName;
        }
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        for(int i=0;i<projects.count();i++)
        {
            ui->tableWidget->setItem(0, i, new QTableWidgetItem(QString("%1").arg(projects[i].GetDayZ(1, date))));
            ui->tableWidget->setItem(1, i, new QTableWidgetItem(QString("%1").arg(projects[i].GetDayZ(2, date))));
            ui->tableWidget->setItem(2, i, new QTableWidgetItem(QString("%1").arg(projects[i].GetDayZ(3, date))));
        }
        ui->tableWidget->resizeRowsToContents();
    }

}


void Circle::on_inputKeyword_textChanged(const QString &arg1)
{
    InitProjects();
}

void Circle::on_checkBox_stateChanged()
{
    if(needDisplay)
        DrawZChart();

}

void Circle::on_btnAddRule_clicked()
{
    //加到右边
        QObjectList list = ui->ruleGroup->children();
        QCheckBox *chk;
        QString multiRule;
        foreach (QObject *obj, list)
        {
            chk = qobject_cast<QCheckBox*>(obj);
            if(chk && chk->checkState() == Qt::Checked)
            {
                multiRule.append(chk->text()).append("|");
                chk->setChecked(false);
            }
        }
        if(multiRule.endsWith("|"))
        {
            multiRule = multiRule.mid(0, multiRule.count()-1);
        }
        ui->listWidget->addItem(multiRule);

        if(needDisplay)
            DrawZChart();
}

void Circle::on_listWidget_clicked(const QModelIndex &index)
{

}

void Circle::on_listWidget_doubleClicked(const QModelIndex &index)
{
    DrawZChart();
}

void Circle::on_add_currentIndexChanged(const QString &arg1)
{

}

void Circle::on_btnImport_clicked()
{

}

void Circle::on_btnCaculate_clicked()
{
    ProjectService s;
    QVector<Result> a = allAreaData[0];
    s.InsertComputation(a, ui->inputStartDate->date().toString("yyyy-MM-dd"), ui->inputEndDate->date().toString("yyyy-MM-dd"));
    int n = s.getN("399005",1);
    ui->txtN->setText(QString("n=%1").arg(n));
    needDisplay = false;

    InitTree();
    needDisplay = true;
}

void Circle::on_listWidget_currentIndexChanged(int index)
{
    CheckData();
    DrawZChart();
}

void Circle::on_btnAreaData_clicked()
{
    QString strFilePath = QFileDialog::getSaveFileName(this,tr("保存为"),QString("面积数据.csv"));
    QFile file(strFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::information(NULL, tr("提示信息："), tr("未能打开文件"));
        return;
    }
    QTextStream out(&file);

    out<<tr("时间,浓度1面积,浓度2面积")<<endl;


    for(int i=0;i<allAreaData[0].count();i++)
    {
        out<<allAreaData[0][i].TestTime<<",";
        out<<allAreaData[0][i].value<<",";
        out<<allAreaData[1][i].value;
        out<<endl;


    }
    QMessageBox::information(NULL, tr("提示信息："), tr("导出成功"));
}

void Circle::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    needDisplay = false;


    //生成模拟数据
    GenerateData20();

    DrawTable();
    DrawCircleChart();

    needDisplay = true;
}

void Circle::on_pushButton_clicked()
{
    AnalyzeDevice *window = new AnalyzeDevice(this);
    window->setWindowTitle(tr("仪器功效函数图"));
    window->showMaximized();
}
