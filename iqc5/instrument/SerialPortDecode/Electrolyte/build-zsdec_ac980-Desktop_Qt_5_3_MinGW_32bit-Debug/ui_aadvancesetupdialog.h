/********************************************************************************
** Form generated from reading UI file 'aadvancesetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AADVANCESETUPDIALOG_H
#define UI_AADVANCESETUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AAdvanceSetupDialog
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QWidget *widget;
    QToolButton *Add_ToolButton;
    QToolButton *Delete_ToolButton;

    void setupUi(QDialog *AAdvanceSetupDialog)
    {
        if (AAdvanceSetupDialog->objectName().isEmpty())
            AAdvanceSetupDialog->setObjectName(QStringLiteral("AAdvanceSetupDialog"));
        AAdvanceSetupDialog->resize(420, 350);
        pushButton = new QPushButton(AAdvanceSetupDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 320, 70, 23));
        pushButton_2 = new QPushButton(AAdvanceSetupDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 320, 70, 23));
        tabWidget = new QTabWidget(AAdvanceSetupDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 9, 341, 301));
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
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(325, 0));
        tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        tableWidget->setColumnCount(2);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->verticalHeader()->setVisible(false);

        horizontalLayout->addWidget(tableWidget);

        tabWidget->addTab(tab, QString());
        widget = new QWidget();
        widget->setObjectName(QStringLiteral("widget"));
        tabWidget->addTab(widget, QString());
        Add_ToolButton = new QToolButton(AAdvanceSetupDialog);
        Add_ToolButton->setObjectName(QStringLiteral("Add_ToolButton"));
        Add_ToolButton->setGeometry(QRect(370, 30, 30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/pics/Add_213px.png"), QSize(), QIcon::Normal, QIcon::Off);
        Add_ToolButton->setIcon(icon);
        Add_ToolButton->setIconSize(QSize(32, 32));
        Delete_ToolButton = new QToolButton(AAdvanceSetupDialog);
        Delete_ToolButton->setObjectName(QStringLiteral("Delete_ToolButton"));
        Delete_ToolButton->setGeometry(QRect(370, 80, 30, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/pics/Remove_213px.png"), QSize(), QIcon::Normal, QIcon::Off);
        Delete_ToolButton->setIcon(icon1);
        Delete_ToolButton->setIconSize(QSize(32, 32));

        retranslateUi(AAdvanceSetupDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AAdvanceSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *AAdvanceSetupDialog)
    {
        AAdvanceSetupDialog->setWindowTitle(QApplication::translate("AAdvanceSetupDialog", "\351\253\230\347\272\247\350\256\276\347\275\256", 0));
        pushButton->setText(QApplication::translate("AAdvanceSetupDialog", "\347\241\256 \345\256\232", 0));
        pushButton_2->setText(QApplication::translate("AAdvanceSetupDialog", "\345\217\226 \346\266\210", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("AAdvanceSetupDialog", "\351\200\232\351\201\223\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("AAdvanceSetupDialog", "\351\241\271\347\233\256\344\273\243\345\217\267", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("AAdvanceSetupDialog", "\351\200\232\351\201\223\345\217\267", 0));
        tabWidget->setTabText(tabWidget->indexOf(widget), QApplication::translate("AAdvanceSetupDialog", "\350\277\207\346\273\244\350\256\276\347\275\256", 0));
        Add_ToolButton->setText(QString());
        Delete_ToolButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AAdvanceSetupDialog: public Ui_AAdvanceSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AADVANCESETUPDIALOG_H
