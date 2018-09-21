/********************************************************************************
** Form generated from reading UI file 'asetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASETUPDIALOG_H
#define UI_ASETUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ASetupDialog
{
public:
    QPushButton *Ensure_PushButton;
    QPushButton *Cancel_PushButton;
    QPushButton *AdvancePushButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_3;
    QLineEdit *Lab_LineEdit;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *DeviceName_LineEdit;
    QComboBox *Timer_ComboBox;
    QWidget *tab_2;

    void setupUi(QDialog *ASetupDialog)
    {
        if (ASetupDialog->objectName().isEmpty())
            ASetupDialog->setObjectName(QStringLiteral("ASetupDialog"));
        ASetupDialog->resize(450, 350);
        Ensure_PushButton = new QPushButton(ASetupDialog);
        Ensure_PushButton->setObjectName(QStringLiteral("Ensure_PushButton"));
        Ensure_PushButton->setGeometry(QRect(10, 320, 70, 23));
        Cancel_PushButton = new QPushButton(ASetupDialog);
        Cancel_PushButton->setObjectName(QStringLiteral("Cancel_PushButton"));
        Cancel_PushButton->setGeometry(QRect(370, 320, 70, 23));
        AdvancePushButton = new QPushButton(ASetupDialog);
        AdvancePushButton->setObjectName(QStringLiteral("AdvancePushButton"));
        AdvancePushButton->setGeometry(QRect(180, 320, 70, 23));
        tabWidget = new QTabWidget(ASetupDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 430, 300));
        tabWidget->setStyleSheet(QLatin1String("QTabWidget::pane{\n"
"	border:none;\n"
"}\n"
"QTabWidget::tab-bar{\n"
"        alignment:left;\n"
"}\n"
"QTabBar::tab{\n"
"	background:transparent;\n"
"	color:white;\n"
"	min-width:30ex;\n"
"	min-height:10ex;\n"
"}\n"
"QTabBar::tab:hover{\n"
"	background:rgb(255, 255, 255, 50);\n"
"}\n"
"QTabBar::tab:selected{\n"
"	border-color: white;\n"
"	background:white;\n"
"	color:green;\n"
"}\n"
"QTabBar::tab:!selected{\n"
"	\n"
"	color:blue;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 10, 80, 20));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Lab_LineEdit = new QLineEdit(tab);
        Lab_LineEdit->setObjectName(QStringLiteral("Lab_LineEdit"));
        Lab_LineEdit->setGeometry(QRect(100, 70, 140, 20));
        Lab_LineEdit->setReadOnly(true);
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 80, 20));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 80, 20));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        DeviceName_LineEdit = new QLineEdit(tab);
        DeviceName_LineEdit->setObjectName(QStringLiteral("DeviceName_LineEdit"));
        DeviceName_LineEdit->setGeometry(QRect(100, 40, 140, 20));
        Timer_ComboBox = new QComboBox(tab);
        Timer_ComboBox->setObjectName(QStringLiteral("Timer_ComboBox"));
        Timer_ComboBox->setGeometry(QRect(100, 10, 69, 22));
        Timer_ComboBox->setEditable(true);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(ASetupDialog);

        tabWidget->setCurrentIndex(0);
        Timer_ComboBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ASetupDialog);
    } // setupUi

    void retranslateUi(QDialog *ASetupDialog)
    {
        ASetupDialog->setWindowTitle(QApplication::translate("ASetupDialog", "\350\256\276\347\275\256", 0));
        Ensure_PushButton->setText(QApplication::translate("ASetupDialog", "\347\241\256 \345\256\232", 0));
        Cancel_PushButton->setText(QApplication::translate("ASetupDialog", "\345\217\226\346\266\210", 0));
        AdvancePushButton->setText(QApplication::translate("ASetupDialog", "\351\253\230\347\272\247\351\200\211\351\241\271", 0));
        label_3->setText(QApplication::translate("ASetupDialog", "\346\227\266\351\227\264\351\227\264\351\232\224\357\274\232", 0));
        label_2->setText(QApplication::translate("ASetupDialog", "\345\256\236\351\252\214\345\256\244\347\274\226\345\217\267\357\274\232", 0));
        label->setText(QApplication::translate("ASetupDialog", "\344\273\252\345\231\250\345\220\215\347\247\260\357\274\232", 0));
        Timer_ComboBox->clear();
        Timer_ComboBox->insertItems(0, QStringList()
         << QApplication::translate("ASetupDialog", "0.1", 0)
         << QApplication::translate("ASetupDialog", "0.2", 0)
         << QApplication::translate("ASetupDialog", "0.5", 0)
         << QApplication::translate("ASetupDialog", "1", 0)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ASetupDialog", "\351\200\232\347\224\250\345\217\202\346\225\260", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ASetupDialog", "\347\211\271\346\256\212\345\217\202\346\225\260", 0));
    } // retranslateUi

};

namespace Ui {
    class ASetupDialog: public Ui_ASetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASETUPDIALOG_H
