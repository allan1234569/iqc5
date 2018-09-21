/********************************************************************************
** Form generated from reading UI file 'ConfigColumn.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGCOLUMN_H
#define UI_CONFIGCOLUMN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigColumn
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QPushButton *btnSave;
    QPushButton *pushButton_2;

    void setupUi(QMainWindow *ConfigColumn)
    {
        if (ConfigColumn->objectName().isEmpty())
            ConfigColumn->setObjectName(QStringLiteral("ConfigColumn"));
        ConfigColumn->resize(310, 380);
        centralwidget = new QWidget(ConfigColumn);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setStyleSheet(QStringLiteral("background-color:;"));
        verticalLayout_3 = new QVBoxLayout(widget_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        verticalLayout_3->addLayout(verticalLayout);


        verticalLayout_2->addWidget(widget_2);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMaximumSize(QSize(16777215, 60));
        btnSave = new QPushButton(widget);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(8, 22, 75, 23));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(91, 22, 75, 23));

        verticalLayout_2->addWidget(widget);

        ConfigColumn->setCentralWidget(centralwidget);

        retranslateUi(ConfigColumn);

        QMetaObject::connectSlotsByName(ConfigColumn);
    } // setupUi

    void retranslateUi(QMainWindow *ConfigColumn)
    {
        ConfigColumn->setWindowTitle(QApplication::translate("ConfigColumn", "\346\230\276\347\244\272\345\210\227", 0));
        btnSave->setText(QApplication::translate("ConfigColumn", "\347\241\256\345\256\232", 0));
        pushButton_2->setText(QApplication::translate("ConfigColumn", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class ConfigColumn: public Ui_ConfigColumn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGCOLUMN_H
