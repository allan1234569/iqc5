/********************************************************************************
** Form generated from reading UI file 'CustomQwtPlot.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMQWTPLOT_H
#define UI_CUSTOMQWTPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_CustomQwtPlot
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_4;
    QLabel *label;
    QLabel *txtAvg;
    QLabel *label_3;
    QLabel *txtSd;
    QLabel *label_5;
    QLabel *txtCV;
    QLabel *label_7;
    QLabel *txt6sigma;
    QPushButton *btnDataTable;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *inputCustAvg;
    QLineEdit *inputCustSD;
    QLabel *label_9;
    QLabel *txtCustCV;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QRadioButton *IfCaculate;
    QRadioButton *IfCustum;
    QLabel *txtCust6sigma;
    QLabel *label_8;
    QPushButton *btnCaculate;
    QDateEdit *inputStartDate;
    QDateEdit *inputEndDate;
    QPushButton *btnInit;
    QLineEdit *txtN;
    QWidget *widget_title;
    QLabel *txtTitle;
    QwtPlot *qwtPlot;
    QWidget *widget_footer;
    QLabel *txtFooter;

    void setupUi(QWidget *CustomQwtPlot)
    {
        if (CustomQwtPlot->objectName().isEmpty())
            CustomQwtPlot->setObjectName(QStringLiteral("CustomQwtPlot"));
        CustomQwtPlot->resize(937, 568);
        CustomQwtPlot->setAutoFillBackground(false);
        verticalLayout = new QVBoxLayout(CustomQwtPlot);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_4 = new QWidget(CustomQwtPlot);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMinimumSize(QSize(0, 60));
        widget_4->setMaximumSize(QSize(16777215, 60));
        widget_4->setStyleSheet(QStringLiteral(""));
        label = new QLabel(widget_4);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 10, 21, 12));
        txtAvg = new QLabel(widget_4);
        txtAvg->setObjectName(QStringLiteral("txtAvg"));
        txtAvg->setGeometry(QRect(105, 10, 54, 12));
        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(160, 10, 54, 12));
        txtSd = new QLabel(widget_4);
        txtSd->setObjectName(QStringLiteral("txtSd"));
        txtSd->setGeometry(QRect(180, 10, 54, 12));
        label_5 = new QLabel(widget_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(240, 10, 31, 12));
        txtCV = new QLabel(widget_4);
        txtCV->setObjectName(QStringLiteral("txtCV"));
        txtCV->setGeometry(QRect(268, 10, 50, 12));
        label_7 = new QLabel(widget_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(320, 10, 31, 12));
        txt6sigma = new QLabel(widget_4);
        txt6sigma->setObjectName(QStringLiteral("txt6sigma"));
        txt6sigma->setGeometry(QRect(343, 11, 54, 12));
        btnDataTable = new QPushButton(widget_4);
        btnDataTable->setObjectName(QStringLiteral("btnDataTable"));
        btnDataTable->setGeometry(QRect(840, 7, 60, 26));
        QFont font;
        font.setPointSize(9);
        btnDataTable->setFont(font);
        label_4 = new QLabel(widget_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(90, 35, 54, 12));
        label_6 = new QLabel(widget_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(160, 35, 51, 12));
        inputCustAvg = new QLineEdit(widget_4);
        inputCustAvg->setObjectName(QStringLiteral("inputCustAvg"));
        inputCustAvg->setGeometry(QRect(100, 30, 51, 20));
        inputCustSD = new QLineEdit(widget_4);
        inputCustSD->setObjectName(QStringLiteral("inputCustSD"));
        inputCustSD->setGeometry(QRect(180, 30, 51, 20));
        label_9 = new QLabel(widget_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(240, 30, 31, 20));
        txtCustCV = new QLabel(widget_4);
        txtCustCV->setObjectName(QStringLiteral("txtCustCV"));
        txtCustCV->setGeometry(QRect(268, 34, 50, 12));
        label_10 = new QLabel(widget_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(390, 10, 54, 12));
        label_11 = new QLabel(widget_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(537, 10, 51, 12));
        label_12 = new QLabel(widget_4);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(640, 10, 31, 12));
        IfCaculate = new QRadioButton(widget_4);
        IfCaculate->setObjectName(QStringLiteral("IfCaculate"));
        IfCaculate->setGeometry(QRect(20, 10, 61, 16));
        IfCaculate->setChecked(true);
        IfCustum = new QRadioButton(widget_4);
        IfCustum->setObjectName(QStringLiteral("IfCustum"));
        IfCustum->setGeometry(QRect(20, 32, 61, 16));
        IfCustum->setChecked(false);
        txtCust6sigma = new QLabel(widget_4);
        txtCust6sigma->setObjectName(QStringLiteral("txtCust6sigma"));
        txtCust6sigma->setGeometry(QRect(343, 34, 54, 12));
        label_8 = new QLabel(widget_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(320, 33, 31, 12));
        btnCaculate = new QPushButton(widget_4);
        btnCaculate->setObjectName(QStringLiteral("btnCaculate"));
        btnCaculate->setGeometry(QRect(770, 7, 60, 26));
        btnCaculate->setFont(font);
        inputStartDate = new QDateEdit(widget_4);
        inputStartDate->setObjectName(QStringLiteral("inputStartDate"));
        inputStartDate->setGeometry(QRect(450, 5, 85, 22));
        inputStartDate->setCurrentSection(QDateTimeEdit::YearSection);
        inputStartDate->setCalendarPopup(true);
        inputEndDate = new QDateEdit(widget_4);
        inputEndDate->setObjectName(QStringLiteral("inputEndDate"));
        inputEndDate->setGeometry(QRect(550, 5, 85, 22));
        inputEndDate->setCurrentSection(QDateTimeEdit::YearSection);
        inputEndDate->setCalendarPopup(true);
        btnInit = new QPushButton(widget_4);
        btnInit->setObjectName(QStringLiteral("btnInit"));
        btnInit->setGeometry(QRect(700, 7, 60, 26));
        btnInit->setFont(font);
        txtN = new QLineEdit(widget_4);
        txtN->setObjectName(QStringLiteral("txtN"));
        txtN->setGeometry(QRect(660, 7, 31, 20));

        verticalLayout->addWidget(widget_4);

        widget_title = new QWidget(CustomQwtPlot);
        widget_title->setObjectName(QStringLiteral("widget_title"));
        widget_title->setMinimumSize(QSize(0, 20));
        widget_title->setMaximumSize(QSize(16777215, 20));
        txtTitle = new QLabel(widget_title);
        txtTitle->setObjectName(QStringLiteral("txtTitle"));
        txtTitle->setGeometry(QRect(20, 0, 421, 16));

        verticalLayout->addWidget(widget_title);

        qwtPlot = new QwtPlot(CustomQwtPlot);
        qwtPlot->setObjectName(QStringLiteral("qwtPlot"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qwtPlot->sizePolicy().hasHeightForWidth());
        qwtPlot->setSizePolicy(sizePolicy);
        qwtPlot->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(qwtPlot);

        widget_footer = new QWidget(CustomQwtPlot);
        widget_footer->setObjectName(QStringLiteral("widget_footer"));
        widget_footer->setMinimumSize(QSize(0, 20));
        widget_footer->setMaximumSize(QSize(16777215, 20));
        txtFooter = new QLabel(widget_footer);
        txtFooter->setObjectName(QStringLiteral("txtFooter"));
        txtFooter->setGeometry(QRect(10, 5, 54, 12));

        verticalLayout->addWidget(widget_footer);


        retranslateUi(CustomQwtPlot);

        QMetaObject::connectSlotsByName(CustomQwtPlot);
    } // setupUi

    void retranslateUi(QWidget *CustomQwtPlot)
    {
        CustomQwtPlot->setWindowTitle(QString());
        label->setText(QApplication::translate("CustomQwtPlot", "X=", 0));
        txtAvg->setText(QApplication::translate("CustomQwtPlot", "0.0", 0));
        label_3->setText(QApplication::translate("CustomQwtPlot", "SD=", 0));
        txtSd->setText(QApplication::translate("CustomQwtPlot", "0.0", 0));
        label_5->setText(QApplication::translate("CustomQwtPlot", "CV%=", 0));
        txtCV->setText(QApplication::translate("CustomQwtPlot", "0.0", 0));
        label_7->setText(QApplication::translate("CustomQwtPlot", "6\317\203=", 0));
        txt6sigma->setText(QApplication::translate("CustomQwtPlot", "0.0", 0));
        btnDataTable->setText(QApplication::translate("CustomQwtPlot", "\346\225\260\346\215\256\350\241\250", 0));
        label_4->setText(QApplication::translate("CustomQwtPlot", "X=", 0));
        label_6->setText(QApplication::translate("CustomQwtPlot", "SD=", 0));
        label_9->setText(QApplication::translate("CustomQwtPlot", "CV%=", 0));
        txtCustCV->setText(QApplication::translate("CustomQwtPlot", "0.0", 0));
        label_10->setText(QApplication::translate("CustomQwtPlot", "\350\265\267\346\255\242\346\227\245\346\234\237:", 0));
        label_11->setText(QApplication::translate("CustomQwtPlot", "\350\207\263", 0));
        label_12->setText(QApplication::translate("CustomQwtPlot", "n=", 0));
        IfCaculate->setText(QApplication::translate("CustomQwtPlot", "\350\256\241\347\256\227\345\200\274", 0));
        IfCustum->setText(QApplication::translate("CustomQwtPlot", "\350\207\252\345\256\232\344\271\211", 0));
        txtCust6sigma->setText(QApplication::translate("CustomQwtPlot", "0.0", 0));
        label_8->setText(QApplication::translate("CustomQwtPlot", "6\317\203=", 0));
        btnCaculate->setText(QApplication::translate("CustomQwtPlot", "\347\264\257\347\247\257\350\256\241\347\256\227", 0));
        inputStartDate->setDisplayFormat(QApplication::translate("CustomQwtPlot", "yyyy-MM-dd", 0));
        inputEndDate->setDisplayFormat(QApplication::translate("CustomQwtPlot", "yyyy-MM-dd", 0));
        btnInit->setText(QApplication::translate("CustomQwtPlot", "\345\210\235\345\247\213\345\214\226", 0));
        txtTitle->setText(QApplication::translate("CustomQwtPlot", "[title]", 0));
        txtFooter->setText(QApplication::translate("CustomQwtPlot", "[footer]", 0));
    } // retranslateUi

};

namespace Ui {
    class CustomQwtPlot: public Ui_CustomQwtPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMQWTPLOT_H
