/********************************************************************************
** Form generated from reading UI file 'ChartTitliBar.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTTITLIBAR_H
#define UI_CHARTTITLIBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChartTitliBar
{
public:
    QGroupBox *groupBox_4;
    QLabel *label;
    QLabel *txtAvg;
    QLabel *label_3;
    QLabel *txtSd;
    QLabel *label_5;
    QLabel *txtCV;
    QLabel *label_7;
    QLabel *txt6sigma;
    QPushButton *btnExport;
    QPushButton *btnExportByType;
    QPushButton *btnDataTable;
    QPushButton *btnPrint;

    void setupUi(QWidget *ChartTitliBar)
    {
        if (ChartTitliBar->objectName().isEmpty())
            ChartTitliBar->setObjectName(QStringLiteral("ChartTitliBar"));
        ChartTitliBar->resize(664, 57);
        groupBox_4 = new QGroupBox(ChartTitliBar);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 0, 645, 40));
        groupBox_4->setMinimumSize(QSize(0, 40));
        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 54, 12));
        txtAvg = new QLabel(groupBox_4);
        txtAvg->setObjectName(QStringLiteral("txtAvg"));
        txtAvg->setGeometry(QRect(50, 20, 54, 12));
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 20, 54, 12));
        txtSd = new QLabel(groupBox_4);
        txtSd->setObjectName(QStringLiteral("txtSd"));
        txtSd->setGeometry(QRect(150, 20, 54, 12));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(210, 20, 54, 12));
        txtCV = new QLabel(groupBox_4);
        txtCV->setObjectName(QStringLiteral("txtCV"));
        txtCV->setGeometry(QRect(230, 20, 54, 12));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(290, 20, 54, 12));
        txt6sigma = new QLabel(groupBox_4);
        txt6sigma->setObjectName(QStringLiteral("txt6sigma"));
        txt6sigma->setGeometry(QRect(310, 20, 54, 12));
        btnExport = new QPushButton(groupBox_4);
        btnExport->setObjectName(QStringLiteral("btnExport"));
        btnExport->setGeometry(QRect(370, 13, 60, 21));
        QFont font;
        font.setPointSize(8);
        btnExport->setFont(font);
        btnExportByType = new QPushButton(groupBox_4);
        btnExportByType->setObjectName(QStringLiteral("btnExportByType"));
        btnExportByType->setGeometry(QRect(440, 13, 60, 21));
        btnExportByType->setFont(font);
        btnDataTable = new QPushButton(groupBox_4);
        btnDataTable->setObjectName(QStringLiteral("btnDataTable"));
        btnDataTable->setGeometry(QRect(510, 13, 60, 21));
        btnDataTable->setFont(font);
        btnPrint = new QPushButton(groupBox_4);
        btnPrint->setObjectName(QStringLiteral("btnPrint"));
        btnPrint->setGeometry(QRect(580, 13, 60, 21));
        btnPrint->setFont(font);

        retranslateUi(ChartTitliBar);

        QMetaObject::connectSlotsByName(ChartTitliBar);
    } // setupUi

    void retranslateUi(QWidget *ChartTitliBar)
    {
        ChartTitliBar->setWindowTitle(QApplication::translate("ChartTitliBar", "Form", 0));
        groupBox_4->setTitle(QApplication::translate("ChartTitliBar", "\350\207\252\345\256\232\344\271\211", 0));
        label->setText(QApplication::translate("ChartTitliBar", "\345\271\263\345\235\207\345\200\274:", 0));
        txtAvg->setText(QApplication::translate("ChartTitliBar", "0", 0));
        label_3->setText(QApplication::translate("ChartTitliBar", "\346\240\207\345\207\206\345\267\256:", 0));
        txtSd->setText(QApplication::translate("ChartTitliBar", "0.0", 0));
        label_5->setText(QApplication::translate("ChartTitliBar", "CV:", 0));
        txtCV->setText(QApplication::translate("ChartTitliBar", "0.0", 0));
        label_7->setText(QApplication::translate("ChartTitliBar", "6\317\203:", 0));
        txt6sigma->setText(QApplication::translate("ChartTitliBar", "0.0", 0));
        btnExport->setText(QApplication::translate("ChartTitliBar", "\345\257\274\345\207\272", 0));
        btnExportByType->setText(QApplication::translate("ChartTitliBar", "\346\261\207\346\200\273", 0));
        btnDataTable->setText(QApplication::translate("ChartTitliBar", "\346\225\260\346\215\256\350\241\250", 0));
        btnPrint->setText(QApplication::translate("ChartTitliBar", "\346\211\223\345\215\260", 0));
    } // retranslateUi

};

namespace Ui {
    class ChartTitliBar: public Ui_ChartTitliBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTTITLIBAR_H
