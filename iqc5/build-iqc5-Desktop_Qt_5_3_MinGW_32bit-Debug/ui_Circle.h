/********************************************************************************
** Form generated from reading UI file 'Circle.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CIRCLE_H
#define UI_CIRCLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_Circle
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *ruleGroup;
    QComboBox *listWidget;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *tableWidget;
    QWidget *widget_2;
    QPushButton *btnAreaData;
    QLabel *label_10;
    QDateEdit *inputEndDate;
    QPushButton *btnImport;
    QLabel *label_11;
    QPushButton *btnCaculate;
    QDateEdit *inputStartDate;
    QLabel *txtN;
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QWidget *paintView;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QwtPlot *totalChart;

    void setupUi(QDialog *Circle)
    {
        if (Circle->objectName().isEmpty())
            Circle->setObjectName(QStringLiteral("Circle"));
        Circle->resize(1048, 592);
        horizontalLayout = new QHBoxLayout(Circle);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_3 = new QGroupBox(Circle);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeWidget = new QTreeWidget(groupBox_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget);


        horizontalLayout->addWidget(groupBox_3);

        widget = new QWidget(Circle);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        ruleGroup = new QGroupBox(widget);
        ruleGroup->setObjectName(QStringLiteral("ruleGroup"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ruleGroup->sizePolicy().hasHeightForWidth());
        ruleGroup->setSizePolicy(sizePolicy1);
        ruleGroup->setMinimumSize(QSize(0, 60));
        ruleGroup->setMaximumSize(QSize(16777215, 60));
        listWidget = new QComboBox(ruleGroup);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(20, 20, 251, 20));

        verticalLayout_2->addWidget(ruleGroup);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_5 = new QVBoxLayout(groupBox_2);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox = new QGroupBox(groupBox_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 120));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout_3->addWidget(tableWidget);

        widget_2 = new QWidget(groupBox);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(0, 50));
        btnAreaData = new QPushButton(widget_2);
        btnAreaData->setObjectName(QStringLiteral("btnAreaData"));
        btnAreaData->setGeometry(QRect(450, 10, 80, 26));
        label_10 = new QLabel(widget_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 15, 54, 12));
        inputEndDate = new QDateEdit(widget_2);
        inputEndDate->setObjectName(QStringLiteral("inputEndDate"));
        inputEndDate->setGeometry(QRect(180, 10, 91, 22));
        btnImport = new QPushButton(widget_2);
        btnImport->setObjectName(QStringLiteral("btnImport"));
        btnImport->setGeometry(QRect(381, 10, 60, 26));
        QFont font;
        font.setPointSize(9);
        btnImport->setFont(font);
        label_11 = new QLabel(widget_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(165, 10, 51, 12));
        btnCaculate = new QPushButton(widget_2);
        btnCaculate->setObjectName(QStringLiteral("btnCaculate"));
        btnCaculate->setGeometry(QRect(309, 10, 60, 26));
        btnCaculate->setFont(font);
        inputStartDate = new QDateEdit(widget_2);
        inputStartDate->setObjectName(QStringLiteral("inputStartDate"));
        inputStartDate->setGeometry(QRect(67, 10, 91, 22));
        txtN = new QLabel(widget_2);
        txtN->setObjectName(QStringLiteral("txtN"));
        txtN->setGeometry(QRect(280, 15, 31, 12));
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(550, 10, 121, 23));

        verticalLayout_3->addWidget(widget_2);


        verticalLayout_5->addWidget(groupBox);

        tabWidget = new QTabWidget(groupBox_2);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 180));
        tabWidget->setIconSize(QSize(16, 16));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        paintView = new QWidget(tab);
        paintView->setObjectName(QStringLiteral("paintView"));
        paintView->setMinimumSize(QSize(320, 250));
        paintView->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        horizontalLayout_3 = new QHBoxLayout(paintView);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));

        horizontalLayout_3->addLayout(verticalLayout_4);


        horizontalLayout_2->addWidget(paintView);

        totalChart = new QwtPlot(tab);
        totalChart->setObjectName(QStringLiteral("totalChart"));
        totalChart->setMinimumSize(QSize(0, 180));

        horizontalLayout_2->addWidget(totalChart);

        tabWidget->addTab(tab, QString());

        verticalLayout_5->addWidget(tabWidget);


        verticalLayout_2->addWidget(groupBox_2);


        horizontalLayout->addWidget(widget);


        retranslateUi(Circle);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Circle);
    } // setupUi

    void retranslateUi(QDialog *Circle)
    {
        Circle->setWindowTitle(QApplication::translate("Circle", "\346\227\245\346\225\260\346\215\256\346\250\241\346\213\237", 0));
        groupBox_3->setTitle(QApplication::translate("Circle", "\350\257\267\351\200\211\346\213\251\346\227\245\346\234\237", 0));
        ruleGroup->setTitle(QApplication::translate("Circle", "\350\257\267\351\200\211\346\213\251\350\247\204\345\210\231", 0));
        groupBox_2->setTitle(QString());
        groupBox->setTitle(QString());
        btnAreaData->setText(QApplication::translate("Circle", "\345\257\274\345\207\272\351\235\242\347\247\257\346\225\260\346\215\256", 0));
        label_10->setText(QApplication::translate("Circle", "\350\265\267\346\255\242\346\227\245\346\234\237:", 0));
        inputEndDate->setDisplayFormat(QApplication::translate("Circle", "yyyy-MM-dd", 0));
        btnImport->setText(QApplication::translate("Circle", "\345\257\274\345\205\245", 0));
        label_11->setText(QApplication::translate("Circle", "\350\207\263", 0));
        btnCaculate->setText(QApplication::translate("Circle", "\351\207\215\346\226\260\350\256\241\347\256\227", 0));
        inputStartDate->setDisplayFormat(QApplication::translate("Circle", "yyyy-MM-dd", 0));
        txtN->setText(QApplication::translate("Circle", "n=", 0));
        pushButton->setText(QApplication::translate("Circle", "\344\273\252\345\231\250\345\201\217\345\267\256\345\212\237\346\225\210\345\207\275\346\225\260\345\233\276", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Circle", "\345\233\276\350\241\250", 0));
    } // retranslateUi

};

namespace Ui {
    class Circle: public Ui_Circle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CIRCLE_H
