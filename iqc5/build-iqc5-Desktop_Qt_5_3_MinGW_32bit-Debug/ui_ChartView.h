/********************************************************************************
** Form generated from reading UI file 'ChartView.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTVIEW_H
#define UI_CHARTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChartView
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QCheckBox *cbkShowAll;
    QComboBox *listWidget;
    QLabel *label;
    QTabWidget *tabWidget;

    void setupUi(QWidget *ChartView)
    {
        if (ChartView->objectName().isEmpty())
            ChartView->setObjectName(QStringLiteral("ChartView"));
        ChartView->resize(748, 491);
        verticalLayout = new QVBoxLayout(ChartView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(ChartView);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 30));
        cbkShowAll = new QCheckBox(widget);
        cbkShowAll->setObjectName(QStringLiteral("cbkShowAll"));
        cbkShowAll->setGeometry(QRect(610, 10, 111, 16));
        listWidget = new QComboBox(widget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(90, 5, 251, 20));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 54, 12));

        verticalLayout->addWidget(widget);

        tabWidget = new QTabWidget(ChartView);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 180));
        tabWidget->setIconSize(QSize(16, 16));

        verticalLayout->addWidget(tabWidget);


        retranslateUi(ChartView);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(ChartView);
    } // setupUi

    void retranslateUi(QWidget *ChartView)
    {
        ChartView->setWindowTitle(QApplication::translate("ChartView", "\350\264\250\346\216\247\345\233\276", 0));
        cbkShowAll->setText(QApplication::translate("ChartView", "\346\230\276\347\244\272\346\211\200\346\234\211\350\264\250\346\216\247\345\223\201", 0));
        label->setText(QApplication::translate("ChartView", "\350\264\250\346\216\247\350\247\204\345\210\231", 0));
    } // retranslateUi

};

namespace Ui {
    class ChartView: public Ui_ChartView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTVIEW_H
