/********************************************************************************
** Form generated from reading UI file 'ManageProject.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEPROJECT_H
#define UI_MANAGEPROJECT_H

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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManageProject
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *keyword;
    QTreeWidget *treeWidget;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *inputCountry;
    QComboBox *inputCategory;
    QComboBox *inputSubject;
    QLineEdit *inputManufacturer;
    QPushButton *pushButton;
    QComboBox *inputCategory_2;
    QTableWidget *table;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnNew;
    QPushButton *btnRefresh;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ManageProject)
    {
        if (ManageProject->objectName().isEmpty())
            ManageProject->setObjectName(QStringLiteral("ManageProject"));
        ManageProject->resize(800, 600);
        centralwidget = new QWidget(ManageProject);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
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
        keyword = new QLineEdit(groupBox_3);
        keyword->setObjectName(QStringLiteral("keyword"));

        verticalLayout_2->addWidget(keyword);

        treeWidget = new QTreeWidget(groupBox_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMaximumSize(QSize(16777215, 16777215));
        treeWidget->header()->setVisible(false);

        verticalLayout_2->addWidget(treeWidget);


        verticalLayout_3->addWidget(groupBox_3);


        horizontalLayout->addWidget(widget);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMinimumSize(QSize(0, 80));
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 10, 54, 12));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(170, 10, 54, 12));
        label_4 = new QLabel(widget_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(160, 40, 54, 12));
        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(330, 10, 51, 16));
        label_6 = new QLabel(widget_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 40, 54, 12));
        inputCountry = new QLineEdit(widget_3);
        inputCountry->setObjectName(QStringLiteral("inputCountry"));
        inputCountry->setGeometry(QRect(40, 10, 113, 20));
        inputCategory = new QComboBox(widget_3);
        inputCategory->setObjectName(QStringLiteral("inputCategory"));
        inputCategory->setGeometry(QRect(200, 40, 111, 22));
        inputSubject = new QComboBox(widget_3);
        inputSubject->setObjectName(QStringLiteral("inputSubject"));
        inputSubject->setGeometry(QRect(40, 40, 111, 22));
        inputManufacturer = new QLineEdit(widget_3);
        inputManufacturer->setObjectName(QStringLiteral("inputManufacturer"));
        inputManufacturer->setGeometry(QRect(200, 10, 113, 20));
        pushButton = new QPushButton(widget_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(490, 10, 51, 23));
        inputCategory_2 = new QComboBox(widget_3);
        inputCategory_2->setObjectName(QStringLiteral("inputCategory_2"));
        inputCategory_2->setGeometry(QRect(370, 10, 111, 22));

        verticalLayout->addWidget(widget_3);

        table = new QTableWidget(widget_2);
        table->setObjectName(QStringLiteral("table"));

        verticalLayout->addWidget(table);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnNew = new QPushButton(widget_2);
        btnNew->setObjectName(QStringLiteral("btnNew"));

        horizontalLayout_2->addWidget(btnNew);

        btnRefresh = new QPushButton(widget_2);
        btnRefresh->setObjectName(QStringLiteral("btnRefresh"));

        horizontalLayout_2->addWidget(btnRefresh);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addWidget(widget_2);

        ManageProject->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ManageProject);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        ManageProject->setMenuBar(menubar);
        statusbar = new QStatusBar(ManageProject);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ManageProject->setStatusBar(statusbar);

        retranslateUi(ManageProject);

        QMetaObject::connectSlotsByName(ManageProject);
    } // setupUi

    void retranslateUi(QMainWindow *ManageProject)
    {
        ManageProject->setWindowTitle(QApplication::translate("ManageProject", "MainWindow", 0));
        groupBox_3->setTitle(QString());
        label_2->setText(QApplication::translate("ManageProject", "\344\270\255\346\226\207\345\220\215", 0));
        label_3->setText(QApplication::translate("ManageProject", "\347\256\200\347\247\260", 0));
        label_4->setText(QApplication::translate("ManageProject", "\344\272\232\344\270\223\344\270\232", 0));
        label_5->setText(QApplication::translate("ManageProject", "\350\264\250\346\216\247\345\223\201", 0));
        label_6->setText(QApplication::translate("ManageProject", "\344\270\223\344\270\232", 0));
        pushButton->setText(QApplication::translate("ManageProject", "\346\237\245\350\257\242", 0));
        btnNew->setText(QApplication::translate("ManageProject", "\346\226\260\345\273\272", 0));
        btnRefresh->setText(QApplication::translate("ManageProject", "\345\210\267\346\226\260", 0));
    } // retranslateUi

};

namespace Ui {
    class ManageProject: public Ui_ManageProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEPROJECT_H
