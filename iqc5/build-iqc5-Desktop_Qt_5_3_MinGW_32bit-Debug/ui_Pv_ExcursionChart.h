/********************************************************************************
** Form generated from reading UI file 'Pv_ExcursionChart.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PV_EXCURSIONCHART_H
#define UI_PV_EXCURSIONCHART_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_Pv_ExcursionChart
{
public:
    QVBoxLayout *verticalLayout;
    QwtPlot *qwtPlot;

    void setupUi(QDialog *Pv_ExcursionChart)
    {
        if (Pv_ExcursionChart->objectName().isEmpty())
            Pv_ExcursionChart->setObjectName(QStringLiteral("Pv_ExcursionChart"));
        Pv_ExcursionChart->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        Pv_ExcursionChart->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(Pv_ExcursionChart);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        qwtPlot = new QwtPlot(Pv_ExcursionChart);
        qwtPlot->setObjectName(QStringLiteral("qwtPlot"));
        QBrush brush(QColor(240, 240, 240, 255));
        brush.setStyle(Qt::SolidPattern);
        qwtPlot->setProperty("canvasBackground", QVariant(brush));
        qwtPlot->setProperty("autoReplot", QVariant(false));

        verticalLayout->addWidget(qwtPlot);


        retranslateUi(Pv_ExcursionChart);

        QMetaObject::connectSlotsByName(Pv_ExcursionChart);
    } // setupUi

    void retranslateUi(QDialog *Pv_ExcursionChart)
    {
        Pv_ExcursionChart->setWindowTitle(QApplication::translate("Pv_ExcursionChart", "\346\255\243\347\241\256\345\272\246ep15\346\226\271\346\241\210-\345\201\217\347\247\273\345\233\276", 0));
    } // retranslateUi

};

namespace Ui {
    class Pv_ExcursionChart: public Ui_Pv_ExcursionChart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PV_EXCURSIONCHART_H
