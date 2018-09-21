/********************************************************************************
** Form generated from reading UI file 'receivesetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEIVESETUPDIALOG_H
#define UI_RECEIVESETUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_ReceiveSetupDialog
{
public:
    QTableWidget *tableWidget;
    QToolButton *Add_ToolButton;
    QToolButton *Delete_ToolButton;
    QPushButton *Save_PushButton;
    QPushButton *Cancel_PushButton;
    QPushButton *Ensure_PushButton;

    void setupUi(QDialog *ReceiveSetupDialog)
    {
        if (ReceiveSetupDialog->objectName().isEmpty())
            ReceiveSetupDialog->setObjectName(QStringLiteral("ReceiveSetupDialog"));
        ReceiveSetupDialog->resize(471, 350);
        ReceiveSetupDialog->setMinimumSize(QSize(471, 350));
        ReceiveSetupDialog->setMaximumSize(QSize(471, 350));
        tableWidget = new QTableWidget(ReceiveSetupDialog);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 410, 300));
        tableWidget->setGridStyle(Qt::SolidLine);
        tableWidget->setColumnCount(3);
        tableWidget->verticalHeader()->setVisible(false);
        Add_ToolButton = new QToolButton(ReceiveSetupDialog);
        Add_ToolButton->setObjectName(QStringLiteral("Add_ToolButton"));
        Add_ToolButton->setGeometry(QRect(430, 30, 30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/pics/Add_213px.png"), QSize(), QIcon::Normal, QIcon::Off);
        Add_ToolButton->setIcon(icon);
        Add_ToolButton->setIconSize(QSize(20, 20));
        Delete_ToolButton = new QToolButton(ReceiveSetupDialog);
        Delete_ToolButton->setObjectName(QStringLiteral("Delete_ToolButton"));
        Delete_ToolButton->setGeometry(QRect(430, 70, 30, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/pics/Remove_213px.png"), QSize(), QIcon::Normal, QIcon::Off);
        Delete_ToolButton->setIcon(icon1);
        Delete_ToolButton->setIconSize(QSize(20, 20));
        Save_PushButton = new QPushButton(ReceiveSetupDialog);
        Save_PushButton->setObjectName(QStringLiteral("Save_PushButton"));
        Save_PushButton->setGeometry(QRect(170, 320, 60, 23));
        Cancel_PushButton = new QPushButton(ReceiveSetupDialog);
        Cancel_PushButton->setObjectName(QStringLiteral("Cancel_PushButton"));
        Cancel_PushButton->setGeometry(QRect(310, 320, 60, 23));
        Ensure_PushButton = new QPushButton(ReceiveSetupDialog);
        Ensure_PushButton->setObjectName(QStringLiteral("Ensure_PushButton"));
        Ensure_PushButton->setGeometry(QRect(40, 320, 70, 23));

        retranslateUi(ReceiveSetupDialog);

        QMetaObject::connectSlotsByName(ReceiveSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *ReceiveSetupDialog)
    {
        ReceiveSetupDialog->setWindowTitle(QApplication::translate("ReceiveSetupDialog", "\346\216\245\346\224\266\350\256\276\347\275\256", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ReceiveSetupDialog", "\346\240\267\346\234\254\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ReceiveSetupDialog", "\351\241\271\347\233\256\345\220\215\347\247\260", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ReceiveSetupDialog", "\346\265\223\345\272\246\346\260\264\345\271\263", 0));
        Add_ToolButton->setText(QString());
        Delete_ToolButton->setText(QString());
        Save_PushButton->setText(QApplication::translate("ReceiveSetupDialog", "\344\277\235 \345\255\230", 0));
        Cancel_PushButton->setText(QApplication::translate("ReceiveSetupDialog", "\345\217\226 \346\266\210", 0));
        Ensure_PushButton->setText(QApplication::translate("ReceiveSetupDialog", "\344\277\235\345\255\230\345\271\266\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class ReceiveSetupDialog: public Ui_ReceiveSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEIVESETUPDIALOG_H
