#include "AnalyzeDevice.h"
#include "ui_AnalyzeDevice.h"
#include "Service/ProjectService.h"
#include <QCheckBox>
#include <QListWidgetItem>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_canvas.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qwt_math.h>
#include <qwt_symbol.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <math.h>
#include <QDebug>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Rule/IRule.h"
#include "Rule/RuleManager.h"


double grand2(double average, double StandardDeviation)
{

    static double V1, V2, S;
    static int phase = 0;
    double X;

    if ( phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;

            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);

        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);

    phase = 1 - phase;


    return X*StandardDeviation + average;
}


AnalyzeDevice::AnalyzeDevice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalyzeDevice)
{
    ui->setupUi(this);

    ui->cb_se->addItem("50%");
    ui->cb_se->addItem("90%");
    ui->cb_se->setCurrentIndex(0);
    connect(ui->cb_se,SIGNAL(currentIndexChanged(int)),this,SLOT(DrawProjectChart()));

    ui->cb_re->addItem("50%");
    ui->cb_re->addItem("90%");
    ui->cb_re->setCurrentIndex(0);
    connect(ui->cb_re,SIGNAL(currentIndexChanged(int)),this,SLOT(DrawProjectChart()));

    QwtPlotCanvas *plotCanvas = qobject_cast<QwtPlotCanvas *>(ui->funcChart_SE->canvas());
    plotCanvas->setFrameStyle(QFrame::Box | QFrame::Plain);
    plotCanvas->setLineWidth(0);
    plotCanvas->setPalette(Qt::white);
    for (int i = 0; i < ui->funcChart_SE->axisCnt; i++)
    {
        QwtScaleWidget *scaleWidget = ui->funcChart_SE->axisWidget(i);
        if (scaleWidget)
        {
            scaleWidget->setMargin(1);
        }
        QwtScaleDraw *scaleDraw = ui->funcChart_SE->axisScaleDraw(i);
        if (scaleDraw)
        {
            scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, true);
        }

    }
    ui->funcChart_SE->plotLayout()->setAlignCanvasToScales(true);

    plotCanvas = qobject_cast<QwtPlotCanvas *>(ui->funcChart_RE->canvas());
    plotCanvas->setFrameStyle(QFrame::Box | QFrame::Plain);
    plotCanvas->setLineWidth(0);
    plotCanvas->setPalette(Qt::white);
    for (int i = 0; i < ui->funcChart_RE->axisCnt; i++)
    {
        QwtScaleWidget *scaleWidget = ui->funcChart_RE->axisWidget(i);
        if (scaleWidget)
        {
            scaleWidget->setMargin(1);
        }
        QwtScaleDraw *scaleDraw = ui->funcChart_RE->axisScaleDraw(i);
        if (scaleDraw)
        {
            scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, true);
        }

    }
    ui->funcChart_RE->plotLayout()->setAlignCanvasToScales(true);


    ui->tabWidget->removeTab(1);


    xCount = 9;
    testDataCount=20000;
    double means[] = {0,1,2,3,4,5,6,7,8};
    double variances[] = {0,1,2,3,4,5,6,7,8};

    //生成SE数据
    for(int i=0; i<xCount; i++)
    {
        QVector<Result> result1;
        QVector<Result> result2;
        QVector<Result> result3;
        QVector<Result> result4;
        QVector<Result> result5;
        QVector<Result> result6;

        for(int j=0; j<testDataCount; j++)
        {
            Result r1, r2, r3, r4, r5,r6;
            r1.value = 0.5*1 * grand2(means[i], 1) * grand2(means[i], 1) + 0.5*6 * grand2(0, 0) * grand2(0, 0);

            r2.value = 0.5*2 * grand2(means[i], 1) * grand2(means[i], 1) + 0.5*5 * grand2(0, 0) * grand2(0, 0);

            r3.value = 0.5*3 * grand2(means[i], 1) * grand2(means[i], 1) + 0.5*4 * grand2(0, 0) * grand2(0, 0);

            r4.value = 0.5*4 * grand2(means[i], 1) * grand2(means[i], 1) + 0.5*3 * grand2(0, 0) * grand2(0, 0);

            r5.value = 0.5*5 * grand2(means[i], 1) * grand2(means[i], 1) + 0.5*2 * grand2(0, 0) * grand2(0, 0);

            r6.value = 0.5*6 * grand2(means[i], 1) * grand2(means[i], 1) + 0.5*1 * grand2(0, 0) * grand2(0, 0);


            result1.append(r1);
            result2.append(r2);
            result3.append(r3);
            result4.append(r4);
            result5.append(r5);
            result6.append(r6);
        }
        results_se1.append(result1);
        results_se2.append(result2);
        results_se3.append(result3);
        results_se4.append(result4);
        results_se5.append(result5);
        results_se6.append(result6);

    }
     //生成RE数据
    for(int i=0; i<xCount; i++)
    {
        QVector<Result> result1;
        QVector<Result> result2;
        QVector<Result> result3;
        QVector<Result> result4;
        QVector<Result> result5;
        QVector<Result> result6;

        for(int j=0; j<testDataCount; j++)
        {
            Result r1, r2, r3, r4, r5,r6;

            r1.value = 0.5*1 * grand2(0, variances[i]) * grand2(0, variances[i]) + 0.5*6 * grand2(0, 0) * grand2(0, 0);

            r2.value = 0.5*2 * grand2(0, variances[i]) * grand2(0, variances[i]) + 0.5*5 * grand2(0, 0) * grand2(0, 0);

            r3.value = 0.5*3 * grand2(0, variances[i]) * grand2(0, variances[i]) + 0.5*4 * grand2(0, 0) * grand2(0, 0);

            r4.value = 0.5*4 * grand2(0, variances[i]) * grand2(0, variances[i]) + 0.5*3 * grand2(0, 0) * grand2(0, 0);

            r5.value = 0.5*5 * grand2(0, variances[i]) * grand2(0, variances[i]) + 0.5*2 * grand2(0, 0) * grand2(0, 0);

            r6.value = 0.5*6 * grand2(0, variances[i]) * grand2(0, variances[i]) + 0.5*1 * grand2(0, 0) * grand2(0, 0);


            result1.append(r1);
            result2.append(r2);
            result3.append(r3);
            result4.append(r4);
            result5.append(r5);
            result6.append(r6);
        }
        results_re1.append(result1);
        results_re2.append(result2);
        results_re3.append(result3);
        results_re4.append(result4);
        results_re5.append(result5);
        results_re6.append(result6);

    }


    ui->inputN->clear();
    for(int i=1;i<=6;i++)
    {
        ui->inputN->addItem(QString("n = %1").arg(i), i);
    }

    InitRules();
    InitProjects();

    ui->inputN->setHidden(true);

}

AnalyzeDevice::~AnalyzeDevice()
{
    delete ui;
}

void AnalyzeDevice::InitProjects()
{
}

void AnalyzeDevice::InitRules()
{
    needDisplay = false;

    //指控规则复选框
    QCheckBox *Rule12S = new  QCheckBox;
    Rule12S->setObjectName("Rule12S");
    Rule12S->setText("12S");
    connect(Rule12S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule12S);
    list.append(Rule12S);

    QCheckBox *Rule13S = new  QCheckBox;
    Rule13S->setObjectName("Rule13S");
    Rule13S->setText("13S");
    connect(Rule13S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule13S);
    list.append(Rule13S);

    QCheckBox *Rule22S = new  QCheckBox;
    Rule22S->setObjectName("Rule22S");
    Rule22S->setText("22S");
    connect(Rule22S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule22S);
    list.append(Rule22S);

    QCheckBox *RuleR4S = new  QCheckBox;
    RuleR4S->setObjectName("RuleR4S");
    RuleR4S->setText("R4S");
    connect(RuleR4S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(RuleR4S);
    list.append(RuleR4S);

    QCheckBox *Rule41S = new  QCheckBox;
    Rule41S->setObjectName("Rule41S");
    Rule41S->setText("41S");
    connect(Rule41S, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule41S);
    list.append(Rule41S);

    QCheckBox *Rule6T = new  QCheckBox;
    Rule6T->setObjectName("Rule6T");
    Rule6T->setText("6T");
    connect(Rule6T, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule6T);
    list.append(Rule6T);

    QCheckBox *Rule9X = new  QCheckBox;
    Rule9X->setObjectName("Rule9X");
    Rule9X->setText("9X");
    connect(Rule9X, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule9X);
    list.append(Rule9X);

    QCheckBox *Rule10X = new  QCheckBox;
    Rule10X->setObjectName("Rule10X");
    Rule10X->setText("10X");
    connect(Rule10X, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(Rule10X);
    list.append(Rule10X);

    QCheckBox *RuleWestgard = new  QCheckBox;
    RuleWestgard->setObjectName("RuleWestgard");
    RuleWestgard->setText("Westgard");
    connect(RuleWestgard, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged()));
    ui->singleRuleContainer->addWidget(RuleWestgard);
    list.append(RuleWestgard);


    needDisplay = true;
}

void AnalyzeDevice::ShowProjectResult()
{
    needDisplay = false;

    ProjectService *service; service = new ProjectService();


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
    }

    DrawProjectChart();

    needDisplay = true;
}

void AnalyzeDevice::DrawProjectChart()
{
    //Project &p = currentProject;
    //ProjectService service;


    //算功效函数图
    double means[] = {0,1,2,3,4,5,6,7,8};
    double variances[] = {0,1,2,3,4,5,6,7,8};
    QVector< QVector<Result> > allData_se;
    QVector< QVector<Result> > allData_re;

    QVector<double> lv_means;
    QVector<double> lv_variances;
    for(int i = 0; i < xCount; i++)
    {
        lv_means.append(0.0);
        lv_variances.append(1.0);
    }

    //计算该规则检出能力
    for  (int i=0; i<ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        QString s = item->text();


        int n = 1;
        QStringList rulenames2 = s.split(",n=");
        if(rulenames2.count() ==2)
        {
            s = rulenames2.at(0);
            n = rulenames2.at(1).toInt();
        }

        if(!s.contains("|") && s.length()>0)
        {

            //计算SE数据
            IRule *rule_se1 = RuleManager::GetRule(s, lv_means, lv_variances, results_se1);
            IRule *rule_se2 = RuleManager::GetRule(s, lv_means, lv_variances, results_se2);
            IRule *rule_se3 = RuleManager::GetRule(s, lv_means, lv_variances, results_se3);
            IRule *rule_se4 = RuleManager::GetRule(s, lv_means, lv_variances, results_se4);
            IRule *rule_se5 = RuleManager::GetRule(s, lv_means, lv_variances, results_se5);
            IRule *rule_se6 = RuleManager::GetRule(s, lv_means, lv_variances, results_se6);

            QVector<Result> data_se;
            for(int i=0;i<xCount;i++)
            {

                int count = 0;

                bool valid;
                for(int j=0;j<results_se1[i].count();j++)
                {
                    valid= true;
                    valid = valid && rule_se1->IsValid(i,j);
                    if(n>=2)
                    {
                        valid = valid && rule_se2->IsValid(i,j);
                    }
                    if(n>=3)
                    {
                        valid = valid && rule_se3->IsValid(i,j);
                    }
                    if(n>=4)
                    {
                        valid = valid && rule_se4->IsValid(i,j);
                    }
                    if(n>=5)
                    {
                        valid = valid && rule_se5->IsValid(i,j);
                    }
                    if(n>=6)
                    {
                        valid = valid && rule_se6->IsValid(i,j);
                    }
                    if(valid)
                    {
                        count++;
                    }
                }

                Result result;
                result.X = means[i];
                result.Y= (double)(testDataCount-count) / (double)testDataCount;
                result.Memo = s;
                result.Memo.append(QString(", n=%1 ").arg(n));
                if(i==0)
                {
                    result.Memo.append(QString(" Ped=%1").arg(result.Y));
                }
                data_se.append(result);
            }
            allData_se.append(data_se);

            //计算RE数据
            IRule *rule_re1 = RuleManager::GetRule(s, lv_means, lv_variances, results_re1);
            IRule *rule_re2 = RuleManager::GetRule(s, lv_means, lv_variances, results_re2);
            IRule *rule_re3 = RuleManager::GetRule(s, lv_means, lv_variances, results_re3);
            IRule *rule_re4 = RuleManager::GetRule(s, lv_means, lv_variances, results_re4);
            IRule *rule_re5 = RuleManager::GetRule(s, lv_means, lv_variances, results_re5);
            IRule *rule_re6 = RuleManager::GetRule(s, lv_means, lv_variances, results_re6);

            QVector<Result> data_re;
            for(int i=0;i<xCount;i++)
            {

                int count = 0;

                bool valid;
                for(int j=0;j<results_re1[i].count();j++)
                {
                    valid= true;
                    valid = valid && rule_re1->IsValid(i,j);
                    if(n>=2)
                    {
                        valid = valid && rule_re2->IsValid(i,j);
                    }
                    if(n>=3)
                    {
                        valid = valid && rule_re3->IsValid(i,j);
                    }
                    if(n>=4)
                    {
                        valid = valid && rule_re4->IsValid(i,j);
                    }
                    if(n>=5)
                    {
                        valid = valid && rule_re5->IsValid(i,j);
                    }
                    if(n>=6)
                    {
                        valid = valid && rule_re6->IsValid(i,j);
                    }
                    if(valid)
                    {
                        count++;
                    }
                }

                Result result;
                result.X = variances[i];
                result.Y= (double)(testDataCount-count) / (double)testDataCount;
                result.Memo = s;
                result.Memo.append(QString(", n=%1 ").arg(n));
                if(i==0)
                {
                    result.Memo.append(QString(" Ped=%1").arg(result.Y));
                }
                data_re.append(result);
            }
            allData_re.append(data_re);

        }
        if(s.contains("|"))
        {
            QStringList rulenames = s.split("|");

            //计算SE数据
            QVector<Result> data_se;
            for(int i=0;i<xCount;i++)
            {
                int count = 0;
                QVector<IRule*> rules_se;
                for(int h=0;h<rulenames.count();h++)
                {
                    IRule *rule = RuleManager::GetRule(rulenames.at(h), lv_means, lv_variances, results_se1);
                    rules_se.append(rule);

                    if(n>=2)
                    {
                        IRule *rule2 = RuleManager::GetRule(rulenames.at(h), lv_means, lv_variances, results_se2);
                        rules_se.append(rule2);
                    }
                    if(n>=3)
                    {
                        IRule *rule3 = RuleManager::GetRule(rulenames.at(h), lv_means, lv_variances, results_se3);
                        rules_se.append(rule3);
                    }
                    if(n>=4)
                    {
                        IRule *rule4 = RuleManager::GetRule(rulenames.at(h), lv_means, lv_variances, results_se4);
                        rules_se.append(rule4);
                    }
                    if(n>=5)
                    {
                        IRule *rule5 = RuleManager::GetRule(rulenames.at(h), lv_means, lv_variances, results_se5);
                        rules_se.append(rule5);
                    }
                    if(n>=6)
                    {
                        IRule *rule6 = RuleManager::GetRule(rulenames.at(h), lv_means, lv_variances, results_se6);
                        rules_se.append(rule6);
                    }
                }

                bool valid;
                for(int j=0;j<results_se1[i].count();j++)
                {
                    valid = true;
                    foreach(IRule *rule, rules_se)
                    {
                        valid = valid && rule->IsValid(i,j);
                    }
                    if(valid)
                    {
                        count++;
                    }
                }

                Result result;
                result.X = means[i];
                result.Y= (double)(testDataCount-count) / (double)testDataCount;
                result.Memo = s.replace("|","+");
                result.Memo.append(QString(", n=%1 ").arg(n));
                if(i==0)
                {
                    result.Memo.append(QString("\nPed=%1").arg(result.Y));
                }
                data_se.append(result);
            }
            allData_se.append(data_se);

            //计算RE数据
            QVector<Result> data_re;
            for(int i=0;i<xCount;i++)
            {
                int count = 0;
                QVector<IRule*> rules_re;
                for(int h=0;h<rulenames.count();h++)
                {
                    IRule *rule = RuleManager::GetRule(rulenames.at(h), lv_means, lv_variances, results_re1);
                    rules_re.append(rule);

                    if(n>=2)
                    {
                        IRule *rule2 = RuleManager::GetRule(rulenames.at(h), lv_means, lv_variances, results_re2);
                        rules_re.append(rule2);
                    }
                    if(n>=3)
                    {
                        IRule *rule3 = RuleManager::GetRule(rulenames.at(h), lv_means, lv_variances, results_re3);
                        rules_re.append(rule3);
                    }
                    if(n>=4)
                    {
                        IRule *rule4 = RuleManager::GetRule(rulenames.at(h), lv_means, lv_variances, results_re4);
                        rules_re.append(rule4);
                    }
                    if(n>=5)
                    {
                        IRule *rule5 = RuleManager::GetRule(rulenames.at(h), lv_means, lv_variances, results_re5);
                        rules_re.append(rule5);
                    }
                    if(n>=6)
                    {
                        IRule *rule6 = RuleManager::GetRule(rulenames.at(h), lv_means, lv_variances, results_re6);
                        rules_re.append(rule6);
                    }
                }

                bool valid;
                for(int j=0;j<results_re1[i].count();j++)
                {
                    valid = true;
                    foreach(IRule *rule, rules_re)
                    {
                        valid = valid && rule->IsValid(i,j);
                    }
                    if(valid)
                    {
                        count++;
                    }
                }

                Result result;
                result.X = variances[i];
                result.Y= (double)(testDataCount-count) / (double)testDataCount;
                result.Memo = s.replace("|","+");
                result.Memo.append(QString(", n=%1 ").arg(n));
                if(i==0)
                {
                    result.Memo.append(QString("\nPed=%1").arg(result.Y));
                }
                data_re.append(result);
            }
            allData_re.append(data_re);
        }
    }



    //画功效函数图的50%和90%点
    QVector< QVector<Result> > allFunc5090Data_se;
    QVector< QVector<Result> > allFunc5090Data_re;


    //算OPSpec图
    QVector< QVector<Result> > allOpsec50Data;

    //算OPSpec图
    QVector< QVector<Result> > allOpsec90Data;


    //对每条功效曲线图进行计算
    double Tea = 0;

    for(int h=0;h<allData_se.count();h++)
    {
        QVector<Result> data = allData_se[h];

        //画50%和90%检出概率的点

        QVector<Result> opsec50Data;
        QVector<Result> opsec90Data;

        //x=0的点
        Result r0;
        r0.X = 0;
        r0.Y =Tea;
        opsec50Data.append(r0);
        opsec90Data.append(r0);


        QVector<Result> func5090Data;
        Result r5090;

        //y=50的点
        Result r50;
        r50.X=100;
        r50.Y=Tea;
        for(int i=0;i<xCount;i++)
        {
            if(data[i].Y>=0.5 && i>=1)
            {
                Result r1 = data[i-1];
                Result r2 = data[i];

                double cv_op = 0;
                if((r2.Y - r1.Y) != 0)
                {
                    cv_op = r1.X + (r2.X - r1.X) / (r2.Y - r1.Y) * (0.5 - r1.Y);
                }
                else
                {
                    cv_op = r1.X + (r2.X - r1.X)*0.5;
                }

                func5090Data.clear();
                r5090.X = 0;
                r5090.Y = 0.5;
                r5090.refuseReason= QString("检出概率50%时系统误差:%1").arg(cv_op);
                func5090Data.append(r5090);
                r5090.X = cv_op;
                r5090.Y = 0.5;
                func5090Data.append(r5090);
                r5090.X = cv_op;
                r5090.Y = 0;
                func5090Data.append(r5090);


                r50.X =Tea/(cv_op+1.65);
                r50.Y = 0;

                break;
            }
        }
        opsec50Data.append(r50);
        allOpsec50Data.append(opsec50Data);

        if(ui->cb_se->currentIndex() == 0)
        {
            allFunc5090Data_se.append(func5090Data);
        }
        //y=90的点
        Result r90;
        r90.X=100;
        r90.Y=Tea;
        for(int i=0;i<xCount;i++)
        {
            if(data[i].Y>=0.9 && i>=1)
            {
                Result r1 = data[i-1];
                Result r2 = data[i];

                double cv_op = 0;
                if((r2.Y - r1.Y) != 0)
                {
                    cv_op = r1.X + (r2.X - r1.X) / (r2.Y - r1.Y) * (0.9 - r1.Y);
                }
                else
                {
                    cv_op = r1.X + (r2.X - r1.X)*0.5;
                }

                func5090Data.clear();
                r5090.X = 0;
                r5090.Y = 0.9;
                r5090.refuseReason= QString("检出概率90%时系统误差:%1").arg(cv_op);
                func5090Data.append(r5090);
                r5090.X = cv_op;
                r5090.Y = 0.9;
                func5090Data.append(r5090);
                r5090.X = cv_op;
                r5090.Y = 0;
                func5090Data.append(r5090);

                r90.X =Tea/(cv_op+1.65);
                r90.Y = 0;

                break;
            }
        }
        opsec90Data.append(r90);
        allOpsec90Data.append(opsec90Data);
        if(ui->cb_se->currentIndex() == 1)
        {
            allFunc5090Data_se.append(func5090Data);
        }
    }

    for(int h=0;h<allData_re.count();h++)
    {
        QVector<Result> data = allData_re[h];

        //画50%和90%检出概率的点
        QVector<Result> func5090Data;
        Result r5090;

        for(int i=0;i<xCount;i++)
        {
            if(data[i].Y>=0.5 && i>=1)
            {
                Result r1 = data[i-1];
                Result r2 = data[i];

                double cv_op = 0;
                if((r2.Y - r1.Y) != 0)
                {
                    cv_op = r1.X + (r2.X - r1.X) / (r2.Y - r1.Y) * (0.5 - r1.Y);
                }
                else
                {
                    cv_op = r1.X + (r2.X - r1.X)*0.5;
                }

                func5090Data.clear();
                r5090.X = 0;
                r5090.Y = 0.5;
                r5090.refuseReason= QString("检出概率50%时随机误差:%1").arg(cv_op);
                func5090Data.append(r5090);
                r5090.X = cv_op;
                r5090.Y = 0.5;
                func5090Data.append(r5090);
                r5090.X = cv_op;
                r5090.Y = 0;
                func5090Data.append(r5090);



                break;
            }
        }

        if(ui->cb_re->currentIndex() == 0)
        {
            allFunc5090Data_re.append(func5090Data);
        }

        //y=90的点

        for(int i=0;i<xCount;i++)
        {
            if(data[i].Y>=0.9 && i>=1)
            {
                Result r1 = data[i-1];
                Result r2 = data[i];

                double cv_op = 0;
                if((r2.Y - r1.Y) != 0)
                {
                    cv_op = r1.X + (r2.X - r1.X) / (r2.Y - r1.Y) * (0.9 - r1.Y);
                }
                else
                {
                    cv_op = r1.X + (r2.X - r1.X)*0.5;
                }

                func5090Data.clear();
                r5090.X = 0;
                r5090.Y = 0.9;
                r5090.refuseReason= QString("检出概率90%时随机误差:%1").arg(cv_op);
                func5090Data.append(r5090);
                r5090.X = cv_op;
                r5090.Y = 0.9;
                func5090Data.append(r5090);
                r5090.X = cv_op;
                r5090.Y = 0;
                func5090Data.append(r5090);

                break;
            }
        }
        if(ui->cb_re->currentIndex() == 1)
        {
            allFunc5090Data_re.append(func5090Data);
        }

    }



    //画功效函数图
    DrawFuncChart(ui->funcChart_SE, 1, allData_se, allFunc5090Data_se);
    DrawFuncChart(ui->funcChart_RE, 2, allData_re, allFunc5090Data_re);

}

//功效函数图
void AnalyzeDevice::DrawFuncChart(QwtPlot*chart, int type, QVector< QVector<Result> > allData, QVector< QVector<Result> > allData5090)
{
        //int markerPositionY = 1;
        chart->detachItems(QwtPlotItem::Rtti_PlotItem, false);

        //图表标题
        chart->setTitle(tr(""));//Levey-Jenning质控图
        if(type==1)
        {
            chart->setTitle(tr("功效函数图(系统误差)"));
        }
        else if(type==2)
        {
            chart->setTitle(tr("功效函数图(随机误差)"));
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
        if(type==1)
        {
            chart->setAxisScale(chart->xBottom, 0, 5);
        }
        else if(type==2)
        {
            chart->setAxisScale(chart->xBottom, 1, 6);
        }
        chart->setAxisScale(chart->yLeft, 0, 1);
        if(type==1)
        {
            chart->setAxisTitle(2, "SE");
        }
        else if(type==2)
        {
            chart->setAxisTitle(2, "RE");
        }
        chart->setAxisTitle(0, "Ped");
        chart->setAxisMaxMajor(2, 10);
        chart->setAxisMaxMajor(0, 10);


        //画曲线
        QColor colors[] = {Qt::darkGreen,Qt::blue,QColor(11,68,54),Qt::darkBlue,Qt::darkCyan,Qt::darkMagenta,Qt::darkYellow};
        for(int h=0;h<allData.count();h++)
        {
            QVector<Result> data = allData[h];
            QVector<Result> data5090 = allData5090[h];

            QwtPlotCurve *qcCurve;
            if(data.count()>0 && data5090.count()>0)
            {
                qcCurve = new QwtPlotCurve(data[0].Memo + "\n" + data5090[0].refuseReason);
            }
            else
            {
                qcCurve = new QwtPlotCurve("无数据\n");
            }
            qcCurve->setPen(QPen(colors[h%7]));
            qcCurve->attach(chart);

            QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse, Qt::black, QPen(Qt::black), QSize(10, 10)) ;
            qcCurve->setSymbol(symbol);
            qcCurve->setStyle(QwtPlotCurve::Lines);
            qcCurve->setCurveAttribute(QwtPlotCurve::Fitted, false);

            int count = data.count();
            double x[count];
            double y[count];

            for(int i=0; i<count;i++)
            {
                x[i] = data[i].X;
                y[i] = data[i].Y;
            }

            qcCurve->setSamples(x, y, count);
        }

//        for(int h=0;h<allData5090.count();h++)
//        {
//            QVector<Result> data = allData5090[h];

//            if(data.count()>=1)
//            {
//                int count = data.count();
//                double x[count];
//                double y[count];

//                for(int i=0; i<count;i++)
//                {
//                    x[i] = data[i].X;
//                    y[i] = data[i].Y;
//                }

//                QwtPlotMarker *mPos = new QwtPlotMarker("Marker");
//                mPos->setRenderHint(QwtPlotItem::RenderAntialiased, true);
//                mPos->setItemAttribute(QwtPlotItem::Legend, false);
//                QColor colors[] = {Qt::darkGreen,Qt::blue,QColor(11,68,54),Qt::darkBlue,Qt::darkCyan,Qt::darkMagenta,Qt::darkYellow};

//                QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Diamond, QColor(colors[h]), QPen(colors[h]), QSize(8, 8)) ;
//                mPos->setSymbol(symbol);

//                mPos->setValue(QPointF(1, data[1].Y+h*0.05));
//                markerPositionY++;
//                mPos->setLabel(data[0].refuseReason);
//                mPos->setLabelAlignment(Qt::AlignRight);
//                mPos->attach(chart);


//            }

//        }


        chart->replot();
}

//OpSpec图
void AnalyzeDevice::DrawOpChart(QwtPlot*chart, int type, QVector< QVector<Result> > allData, QVector<double> cvList, QVector<double> biasList, QVector<QString> nameList)
{

}


void AnalyzeDevice::on_btnCancel_clicked()
{
    this->close();
}

void AnalyzeDevice::on_projectList_itemDoubleClicked(QListWidgetItem *item)
{
    ShowProjectResult();
}

void AnalyzeDevice::on_btnSetRule_clicked()
{


}

void AnalyzeDevice::on_inputKeyword_textChanged(const QString &arg1)
{
    InitProjects();

}

void AnalyzeDevice::on_checkBox_stateChanged()
{
    if(needDisplay)
        DrawProjectChart();

}

void AnalyzeDevice::on_inputTea_textChanged(const QString &arg1)
{
    if(needDisplay)
        DrawProjectChart();
}

void AnalyzeDevice::on_inputBias_textChanged(const QString &arg1)
{
    if(needDisplay)
        DrawProjectChart();
}

void AnalyzeDevice::on_inputCV_textChanged(const QString &arg1)
{
    if(needDisplay)
        DrawProjectChart();
}

void AnalyzeDevice::on_btnAddRule_clicked()
{
    //加到右边
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
    //multiRule.append(QString(",n=%1").arg(ui->inputN->currentIndex()+1));
    //ui->listWidget->addItem(multiRule);
    for(int i=0;i<6;i++)
    {
        ui->listWidget->addItem(multiRule + QString(",n=%1").arg(i));
    }

    //保存
    ProjectService *s = new ProjectService();
    QVector<QString> rules;
    for  (int i=0; i<ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        rules.append(item->text());
    }
    s->SetDefaultRule(currentTypeId, rules);

    if(needDisplay)
        DrawProjectChart();
}

void AnalyzeDevice::on_listWidget_doubleClicked(const QModelIndex &index)
{
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
    s->SetDefaultRule(currentTypeId, rules);

    if(needDisplay)
        DrawProjectChart();
}

void AnalyzeDevice::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if( item->childCount() == 0)
    {
        ShowProjectResult();
    }
}

void AnalyzeDevice::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if( current->childCount() == 0)
    {
        ShowProjectResult();
    }
}
