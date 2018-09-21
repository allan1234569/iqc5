/********************************************************************************
** Form generated from reading UI file 'AnalyzeRule.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYZERULE_H
#define UI_ANALYZERULE_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_AnalyzeRule
{
public:
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QLineEdit *inputKeyword;
    QTreeWidget *treeWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QLabel *label_6;
    QLineEdit *inputTea;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *inputBias;
    QLineEdit *inputCV;
    QGroupBox *ruleGroup1;
    QVBoxLayout *verticalLayout_3;
    QWidget *ruleGroup;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *singleRuleContainer;
    QComboBox *inputN;
    QPushButton *btnAddRule;
    QSpacerItem *horizontalSpacer;
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
    QWidget *tab_5;
    QHBoxLayout *horizontalLayout_2;
    QwtPlot *opChart_50;
    QwtPlot *opChart_90;

    void setupUi(QDialog *AnalyzeRule)
    {
        if (AnalyzeRule->objectName().isEmpty())
            AnalyzeRule->setObjectName(QStringLiteral("AnalyzeRule"));
        AnalyzeRule->resize(988, 772);
        horizontalLayout_3 = new QHBoxLayout(AnalyzeRule);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        groupBox_3 = new QGroupBox(AnalyzeRule);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        inputKeyword = new QLineEdit(groupBox_3);
        inputKeyword->setObjectName(QStringLiteral("inputKeyword"));

        verticalLayout->addWidget(inputKeyword);

        treeWidget = new QTreeWidget(groupBox_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget);


        horizontalLayout_3->addWidget(groupBox_3);

        widget = new QWidget(AnalyzeRule);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(0, 70));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 20, 111, 16));
        inputTea = new QLineEdit(groupBox);
        inputTea->setObjectName(QStringLiteral("inputTea"));
        inputTea->setGeometry(QRect(10, 40, 113, 20));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(140, 20, 111, 16));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(270, 20, 111, 16));
        inputBias = new QLineEdit(groupBox);
        inputBias->setObjectName(QStringLiteral("inputBias"));
        inputBias->setGeometry(QRect(140, 40, 113, 20));
        inputCV = new QLineEdit(groupBox);
        inputCV->setObjectName(QStringLiteral("inputCV"));
        inputCV->setGeometry(QRect(270, 40, 113, 20));

        verticalLayout_2->addWidget(groupBox);

        ruleGroup1 = new QGroupBox(widget);
        ruleGroup1->setObjectName(QStringLiteral("ruleGroup1"));
        sizePolicy1.setHeightForWidth(ruleGroup1->sizePolicy().hasHeightForWidth());
        ruleGroup1->setSizePolicy(sizePolicy1);
        ruleGroup1->setMinimumSize(QSize(0, 140));
        ruleGroup1->setMaximumSize(QSize(16777215, 140));
        verticalLayout_3 = new QVBoxLayout(ruleGroup1);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        ruleGroup = new QWidget(ruleGroup1);
        ruleGroup->setObjectName(QStringLiteral("ruleGroup"));
        ruleGroup->setMinimumSize(QSize(0, 26));
        ruleGroup->setMaximumSize(QSize(16777215, 26));
        horizontalLayout_4 = new QHBoxLayout(ruleGroup);
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        singleRuleContainer = new QHBoxLayout();
        singleRuleContainer->setObjectName(QStringLiteral("singleRuleContainer"));

        horizontalLayout_4->addLayout(singleRuleContainer);

        inputN = new QComboBox(ruleGroup);
        inputN->setObjectName(QStringLiteral("inputN"));
        inputN->setMinimumSize(QSize(40, 0));

        horizontalLayout_4->addWidget(inputN);

        btnAddRule = new QPushButton(ruleGroup);
        btnAddRule->setObjectName(QStringLiteral("btnAddRule"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnAddRule->sizePolicy().hasHeightForWidth());
        btnAddRule->setSizePolicy(sizePolicy2);
        btnAddRule->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_4->addWidget(btnAddRule);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_3->addWidget(ruleGroup);

        listWidget = new QListWidget(ruleGroup1);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMinimumSize(QSize(0, 80));
        listWidget->setMaximumSize(QSize(16777215, 80));

        verticalLayout_3->addWidget(listWidget);

        label_9 = new QLabel(ruleGroup1);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_3->addWidget(label_9);

        verticalLayout_3->setStretch(0, 2);

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
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        horizontalLayout_2 = new QHBoxLayout(tab_5);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        opChart_50 = new QwtPlot(tab_5);
        opChart_50->setObjectName(QStringLiteral("opChart_50"));
        opChart_50->setMinimumSize(QSize(320, 0));
        opChart_50->setLineWidth(0);

        horizontalLayout_2->addWidget(opChart_50);

        opChart_90 = new QwtPlot(tab_5);
        opChart_90->setObjectName(QStringLiteral("opChart_90"));
        opChart_90->setMinimumSize(QSize(320, 0));
        opChart_90->setLineWidth(0);

        horizontalLayout_2->addWidget(opChart_90);

        tabWidget->addTab(tab_5, QString());

        verticalLayout_2->addWidget(tabWidget);


        horizontalLayout_3->addWidget(widget);


        retranslateUi(AnalyzeRule);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(AnalyzeRule);
    } // setupUi

    void retranslateUi(QDialog *AnalyzeRule)
    {
        AnalyzeRule->setWindowTitle(QApplication::translate("AnalyzeRule", "\350\256\276\350\256\241\351\200\211\346\213\251", 0));
        groupBox_3->setTitle(QApplication::translate("AnalyzeRule", "\350\257\267\351\200\211\346\213\251\351\241\271\347\233\256", 0));
        groupBox->setTitle(QApplication::translate("AnalyzeRule", "\350\257\204\344\273\267\345\217\202\346\225\260", 0));
        label_6->setText(QApplication::translate("AnalyzeRule", "\345\205\201\350\256\270\346\200\273\350\257\257\345\267\256(TEa)", 0));
        inputTea->setText(QApplication::translate("AnalyzeRule", "30", 0));
        label_7->setText(QApplication::translate("AnalyzeRule", "\345\205\201\350\256\270\345\201\217\345\200\232(Bias)", 0));
        label_8->setText(QApplication::translate("AnalyzeRule", "\345\205\201\350\256\270\344\270\215\347\262\276\347\241\256\345\272\246(CV)", 0));
        inputBias->setText(QApplication::translate("AnalyzeRule", "6", 0));
        inputCV->setText(QApplication::translate("AnalyzeRule", "4", 0));
        ruleGroup1->setTitle(QApplication::translate("AnalyzeRule", "\350\257\267\351\200\211\346\213\251\346\226\271\346\241\210", 0));
        btnAddRule->setText(QApplication::translate("AnalyzeRule", "\345\212\240\345\205\245", 0));
        label_9->setText(QApplication::translate("AnalyzeRule", "(\345\217\214\345\207\273\345\217\257\347\247\273\351\231\244\350\257\245\350\247\204\345\210\231)", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("AnalyzeRule", "\345\212\237\346\225\210\345\207\275\346\225\260\345\233\276(SE)", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("AnalyzeRule", "\345\212\237\346\225\210\345\207\275\346\225\260\345\233\276(RE)", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("AnalyzeRule", "\346\223\215\344\275\234\350\277\207\347\250\213\350\247\204\350\214\203\345\233\276", 0));
    } // retranslateUi

};

namespace Ui {
    class AnalyzeRule: public Ui_AnalyzeRule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYZERULE_H
