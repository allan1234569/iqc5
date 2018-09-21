/********************************************************************************
** Form generated from reading UI file 'ManageReagent.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEREAGENT_H
#define UI_MANAGEREAGENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManageReagent
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *inputKeyword;
    QTreeWidget *treeWidget;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget_1;
    QComboBox *inputSubject;
    QLabel *label_3;
    QLineEdit *inputName;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_6;
    QLabel *label_5;
    QLineEdit *inputManufacturer;
    QLineEdit *inputCountry;
    QComboBox *inputCategory;
    QPushButton *btnSearch;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QTableWidget *table;
    QWidget *widget_4;
    QPushButton *btnAdd;
    QPushButton *btnClose;

    void setupUi(QMainWindow *ManageReagent)
    {
        if (ManageReagent->objectName().isEmpty())
            ManageReagent->setObjectName(QStringLiteral("ManageReagent"));
        ManageReagent->resize(800, 600);
        centralwidget = new QWidget(ManageReagent);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 0));
        widget->setMaximumSize(QSize(200, 16777215));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(200, 16777215));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        inputKeyword = new QLineEdit(groupBox_3);
        inputKeyword->setObjectName(QStringLiteral("inputKeyword"));

        verticalLayout_2->addWidget(inputKeyword);

        treeWidget = new QTreeWidget(groupBox_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMaximumSize(QSize(16777215, 16777215));
        treeWidget->header()->setVisible(false);

        verticalLayout_2->addWidget(treeWidget);


        verticalLayout_3->addWidget(groupBox_3);


        horizontalLayout_2->addWidget(widget);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_1 = new QWidget(widget_2);
        widget_1->setObjectName(QStringLiteral("widget_1"));
        widget_1->setMinimumSize(QSize(0, 80));
        inputSubject = new QComboBox(widget_1);
        inputSubject->setObjectName(QStringLiteral("inputSubject"));
        inputSubject->setGeometry(QRect(50, 50, 111, 22));
        label_3 = new QLabel(widget_1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(340, 50, 54, 12));
        inputName = new QLineEdit(widget_1);
        inputName->setObjectName(QStringLiteral("inputName"));
        inputName->setGeometry(QRect(50, 20, 271, 20));
        label_4 = new QLabel(widget_1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(170, 50, 54, 12));
        label = new QLabel(widget_1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(340, 20, 54, 12));
        label_6 = new QLabel(widget_1);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 50, 54, 12));
        label_5 = new QLabel(widget_1);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 20, 41, 16));
        inputManufacturer = new QLineEdit(widget_1);
        inputManufacturer->setObjectName(QStringLiteral("inputManufacturer"));
        inputManufacturer->setGeometry(QRect(370, 50, 113, 20));
        inputCountry = new QLineEdit(widget_1);
        inputCountry->setObjectName(QStringLiteral("inputCountry"));
        inputCountry->setGeometry(QRect(370, 20, 113, 20));
        inputCategory = new QComboBox(widget_1);
        inputCategory->setObjectName(QStringLiteral("inputCategory"));
        inputCategory->setGeometry(QRect(210, 50, 111, 22));
        btnSearch = new QPushButton(widget_1);
        btnSearch->setObjectName(QStringLiteral("btnSearch"));
        btnSearch->setGeometry(QRect(524, 19, 51, 23));

        verticalLayout->addWidget(widget_1);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        table = new QTableWidget(widget_3);
        table->setObjectName(QStringLiteral("table"));

        horizontalLayout->addWidget(table);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMinimumSize(QSize(120, 0));
        btnAdd = new QPushButton(widget_4);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setGeometry(QRect(20, 250, 75, 23));
        btnClose = new QPushButton(widget_4);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(20, 280, 75, 23));

        horizontalLayout->addWidget(widget_4);


        verticalLayout->addWidget(widget_3);


        horizontalLayout_2->addWidget(widget_2);

        ManageReagent->setCentralWidget(centralwidget);

        retranslateUi(ManageReagent);

        QMetaObject::connectSlotsByName(ManageReagent);
    } // setupUi

    void retranslateUi(QMainWindow *ManageReagent)
    {
        ManageReagent->setWindowTitle(QApplication::translate("ManageReagent", "MainWindow", 0));
        groupBox_3->setTitle(QString());
        label_3->setText(QApplication::translate("ManageReagent", "\345\216\202\345\256\266", 0));
        label_4->setText(QApplication::translate("ManageReagent", "\344\272\232\344\270\223\344\270\232", 0));
        label->setText(QApplication::translate("ManageReagent", "\344\272\247\345\234\260", 0));
        label_6->setText(QApplication::translate("ManageReagent", "\344\270\223\344\270\232", 0));
        label_5->setText(QApplication::translate("ManageReagent", "\345\220\215\347\247\260", 0));
        btnSearch->setText(QApplication::translate("ManageReagent", "\346\237\245\350\257\242", 0));
        btnAdd->setText(QApplication::translate("ManageReagent", "\346\267\273\345\212\240", 0));
        btnClose->setText(QApplication::translate("ManageReagent", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class ManageReagent: public Ui_ManageReagent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEREAGENT_H
