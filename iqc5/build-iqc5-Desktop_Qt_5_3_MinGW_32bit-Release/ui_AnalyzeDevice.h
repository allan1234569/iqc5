/********************************************************************************
** Form generated from reading UI file 'AnalyzeDevice.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYZEDEVICE_H
#define UI_ANALYZEDEVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_AnalyzeDevice
{
public:
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *ruleGroup1;
    QVBoxLayout *verticalLayout_3;
    QWidget *ruleGroup;
    QPushButton *btnAddRule;
    QComboBox *inputN;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *singleRuleContainer;
    QListWidget *listWidget;
    QLabel *label_9;
    QTabWidget *tabWidget;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_3;
    QComboBox *cb_se;
    QHBoxLayout *horizontalLayout;
    QwtPlot *funcChart_SE;
    QWidget *tab;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_2;
    QComboBox *cb_re;
    QHBoxLayout *horizontalLayout_6;
    QwtPlot *funcChart_RE;

    void setupUi(QDialog *AnalyzeDevice)
    {
        if (AnalyzeDevice->objectName().isEmpty())
            AnalyzeDevice->setObjectName(QStringLiteral("AnalyzeDevice"));
        AnalyzeDevice->resize(988, 561);
        horizontalLayout_3 = new QHBoxLayout(AnalyzeDevice);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        widget = new QWidget(AnalyzeDevice);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        ruleGroup1 = new QGroupBox(widget);
        ruleGroup1->setObjectName(QStringLiteral("ruleGroup1"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ruleGroup1->sizePolicy().hasHeightForWidth());
        ruleGroup1->setSizePolicy(sizePolicy);
        ruleGroup1->setMinimumSize(QSize(0, 140));
        ruleGroup1->setMaximumSize(QSize(16777215, 140));
        verticalLayout_3 = new QVBoxLayout(ruleGroup1);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        ruleGroup = new QWidget(ruleGroup1);
        ruleGroup->setObjectName(QStringLiteral("ruleGroup"));
        ruleGroup->setMinimumSize(QSize(0, 26));
        ruleGroup->setMaximumSize(QSize(16777215, 26));
        btnAddRule = new QPushButton(ruleGroup);
        btnAddRule->setObjectName(QStringLiteral("btnAddRule"));
        btnAddRule->setGeometry(QRect(590, 2, 50, 23));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnAddRule->sizePolicy().hasHeightForWidth());
        btnAddRule->setSizePolicy(sizePolicy1);
        btnAddRule->setMaximumSize(QSize(16777215, 16777215));
        inputN = new QComboBox(ruleGroup);
        inputN->setObjectName(QStringLiteral("inputN"));
        inputN->setGeometry(QRect(510, 4, 71, 20));
        inputN->setMinimumSize(QSize(40, 0));
        horizontalLayoutWidget = new QWidget(ruleGroup);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 7, 461, 16));
        singleRuleContainer = new QHBoxLayout(horizontalLayoutWidget);
        singleRuleContainer->setObjectName(QStringLiteral("singleRuleContainer"));
        singleRuleContainer->setContentsMargins(0, 0, 0, 0);

        verticalLayout_3->addWidget(ruleGroup);

        listWidget = new QListWidget(ruleGroup1);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMinimumSize(QSize(0, 80));
        listWidget->setMaximumSize(QSize(16777215, 80));

        verticalLayout_3->addWidget(listWidget);

        label_9 = new QLabel(ruleGroup1);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_3->addWidget(label_9);


        verticalLayout_2->addWidget(ruleGroup1);

        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        verticalLayout_4 = new QVBoxLayout(tab_6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        widget_3 = new QWidget(tab_6);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMinimumSize(QSize(0, 30));
        widget_3->setMaximumSize(QSize(16777215, 30));
        cb_se = new QComboBox(widget_3);
        cb_se->setObjectName(QStringLiteral("cb_se"));
        cb_se->setGeometry(QRect(50, 10, 100, 20));

        verticalLayout_4->addWidget(widget_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        funcChart_SE = new QwtPlot(tab_6);
        funcChart_SE->setObjectName(QStringLiteral("funcChart_SE"));
        funcChart_SE->setLineWidth(0);

        horizontalLayout->addWidget(funcChart_SE);


        verticalLayout_4->addLayout(horizontalLayout);

        tabWidget->addTab(tab_6, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_5 = new QVBoxLayout(tab);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        widget_2 = new QWidget(tab);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(0, 30));
        widget_2->setMaximumSize(QSize(16777215, 30));
        cb_re = new QComboBox(widget_2);
        cb_re->setObjectName(QStringLiteral("cb_re"));
        cb_re->setGeometry(QRect(50, 10, 100, 20));

        verticalLayout_5->addWidget(widget_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        funcChart_RE = new QwtPlot(tab);
        funcChart_RE->setObjectName(QStringLiteral("funcChart_RE"));
        funcChart_RE->setLineWidth(0);

        horizontalLayout_6->addWidget(funcChart_RE);


        verticalLayout_5->addLayout(horizontalLayout_6);

        tabWidget->addTab(tab, QString());

        verticalLayout_2->addWidget(tabWidget);


        horizontalLayout_3->addWidget(widget);


        retranslateUi(AnalyzeDevice);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(AnalyzeDevice);
    } // setupUi

    void retranslateUi(QDialog *AnalyzeDevice)
    {
        AnalyzeDevice->setWindowTitle(QApplication::translate("AnalyzeDevice", "\350\256\276\350\256\241\351\200\211\346\213\251", 0));
        ruleGroup1->setTitle(QApplication::translate("AnalyzeDevice", "\350\257\267\351\200\211\346\213\251\346\226\271\346\241\210", 0));
        btnAddRule->setText(QApplication::translate("AnalyzeDevice", "\345\212\240\345\205\245", 0));
        label_9->setText(QApplication::translate("AnalyzeDevice", "(\345\217\214\345\207\273\345\217\257\347\247\273\351\231\244\350\257\245\350\247\204\345\210\231)", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("AnalyzeDevice", "\345\212\237\346\225\210\345\207\275\346\225\260\345\233\276(SE)", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("AnalyzeDevice", "\345\212\237\346\225\210\345\207\275\346\225\260\345\233\276(RE)", 0));
    } // retranslateUi

};

namespace Ui {
    class AnalyzeDevice: public Ui_AnalyzeDevice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYZEDEVICE_H
