/********************************************************************************
** Form generated from reading UI file 'SixSigma_QCRulesScreening.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIXSIGMA_QCRULESSCREENING_H
#define UI_SIXSIGMA_QCRULESSCREENING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_SixSigma_QCRulesScreening
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLineEdit *input_keyword;
    QTreeWidget *treeWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QwtPlot *qwtPlot_DecisionChart;
    QwtPlot *qwtPlot_StandardizedTo100;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SixSigma_QCRulesScreening)
    {
        if (SixSigma_QCRulesScreening->objectName().isEmpty())
            SixSigma_QCRulesScreening->setObjectName(QStringLiteral("SixSigma_QCRulesScreening"));
        SixSigma_QCRulesScreening->resize(846, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        SixSigma_QCRulesScreening->setWindowIcon(icon);
        centralwidget = new QWidget(SixSigma_QCRulesScreening);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        input_keyword = new QLineEdit(groupBox);
        input_keyword->setObjectName(QStringLiteral("input_keyword"));
        input_keyword->setMinimumSize(QSize(200, 0));
        input_keyword->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(input_keyword);

        treeWidget = new QTreeWidget(groupBox);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMinimumSize(QSize(200, 0));
        treeWidget->setMaximumSize(QSize(200, 16777215));
        treeWidget->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget);


        horizontalLayout_3->addWidget(groupBox);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        groupBox_2->setMinimumSize(QSize(0, 111));
        groupBox_2->setMaximumSize(QSize(16777215, 111));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(6, 6, 6, 6);
        stackedWidget = new QStackedWidget(groupBox_2);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);

        horizontalLayout_2->addWidget(stackedWidget);


        verticalLayout_2->addWidget(groupBox_2);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        qwtPlot_DecisionChart = new QwtPlot(widget_2);
        qwtPlot_DecisionChart->setObjectName(QStringLiteral("qwtPlot_DecisionChart"));
        sizePolicy1.setHeightForWidth(qwtPlot_DecisionChart->sizePolicy().hasHeightForWidth());
        qwtPlot_DecisionChart->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(qwtPlot_DecisionChart);

        qwtPlot_StandardizedTo100 = new QwtPlot(widget_2);
        qwtPlot_StandardizedTo100->setObjectName(QStringLiteral("qwtPlot_StandardizedTo100"));
        sizePolicy1.setHeightForWidth(qwtPlot_StandardizedTo100->sizePolicy().hasHeightForWidth());
        qwtPlot_StandardizedTo100->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(qwtPlot_StandardizedTo100);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        verticalLayout_2->addWidget(widget_2);


        horizontalLayout_3->addWidget(widget);

        SixSigma_QCRulesScreening->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SixSigma_QCRulesScreening);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 846, 23));
        SixSigma_QCRulesScreening->setMenuBar(menubar);
        statusbar = new QStatusBar(SixSigma_QCRulesScreening);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SixSigma_QCRulesScreening->setStatusBar(statusbar);

        retranslateUi(SixSigma_QCRulesScreening);

        QMetaObject::connectSlotsByName(SixSigma_QCRulesScreening);
    } // setupUi

    void retranslateUi(QMainWindow *SixSigma_QCRulesScreening)
    {
        SixSigma_QCRulesScreening->setWindowTitle(QApplication::translate("SixSigma_QCRulesScreening", "6\316\243\350\264\250\346\216\247\350\247\204\345\210\231\347\255\233\351\200\211", 0));
        groupBox->setTitle(QApplication::translate("SixSigma_QCRulesScreening", "\350\257\267\351\200\211\346\213\251\351\241\271\347\233\256", 0));
        groupBox_2->setTitle(QApplication::translate("SixSigma_QCRulesScreening", "\350\257\204\344\273\267\345\217\202\346\225\260", 0));
    } // retranslateUi

};

namespace Ui {
    class SixSigma_QCRulesScreening: public Ui_SixSigma_QCRulesScreening {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIXSIGMA_QCRULESSCREENING_H
