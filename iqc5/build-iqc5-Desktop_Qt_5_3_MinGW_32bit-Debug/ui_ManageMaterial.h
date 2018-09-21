/********************************************************************************
** Form generated from reading UI file 'ManageMaterial.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEMATERIAL_H
#define UI_MANAGEMATERIAL_H

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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManageMaterial
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QLineEdit *inputKeyword;
    QTreeWidget *treeWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_1;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *inputCountry;
    QComboBox *inputCategory;
    QComboBox *inputSubject;
    QLineEdit *inputManufacturer;
    QLineEdit *inputName;
    QPushButton *btnSearch;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *table;
    QWidget *widget_4;
    QPushButton *btnAdd;
    QPushButton *btnClose;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ManageMaterial)
    {
        if (ManageMaterial->objectName().isEmpty())
            ManageMaterial->setObjectName(QStringLiteral("ManageMaterial"));
        ManageMaterial->resize(884, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        ManageMaterial->setWindowIcon(icon);
        centralwidget = new QWidget(ManageMaterial);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        inputKeyword = new QLineEdit(groupBox_3);
        inputKeyword->setObjectName(QStringLiteral("inputKeyword"));

        verticalLayout->addWidget(inputKeyword);

        treeWidget = new QTreeWidget(groupBox_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget);


        horizontalLayout->addWidget(groupBox_3);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        widget_1 = new QWidget(widget);
        widget_1->setObjectName(QStringLiteral("widget_1"));
        verticalLayout_2 = new QVBoxLayout(widget_1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget_2 = new QWidget(widget_1);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(0, 80));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(330, 40, 54, 12));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(330, 10, 54, 12));
        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(162, 44, 54, 12));
        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 10, 71, 16));
        label_6 = new QLabel(widget_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(11, 45, 54, 12));
        inputCountry = new QLineEdit(widget_2);
        inputCountry->setObjectName(QStringLiteral("inputCountry"));
        inputCountry->setGeometry(QRect(360, 40, 113, 20));
        inputCategory = new QComboBox(widget_2);
        inputCategory->setObjectName(QStringLiteral("inputCategory"));
        inputCategory->setGeometry(QRect(200, 40, 111, 22));
        inputSubject = new QComboBox(widget_2);
        inputSubject->setObjectName(QStringLiteral("inputSubject"));
        inputSubject->setGeometry(QRect(40, 40, 111, 22));
        inputManufacturer = new QLineEdit(widget_2);
        inputManufacturer->setObjectName(QStringLiteral("inputManufacturer"));
        inputManufacturer->setGeometry(QRect(360, 10, 113, 20));
        inputName = new QLineEdit(widget_2);
        inputName->setObjectName(QStringLiteral("inputName"));
        inputName->setGeometry(QRect(40, 10, 271, 20));
        btnSearch = new QPushButton(widget_2);
        btnSearch->setObjectName(QStringLiteral("btnSearch"));
        btnSearch->setGeometry(QRect(520, 10, 51, 23));

        verticalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(widget_1);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        table = new QTableWidget(widget_3);
        table->setObjectName(QStringLiteral("table"));

        horizontalLayout_2->addWidget(table);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMinimumSize(QSize(120, 0));
        btnAdd = new QPushButton(widget_4);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setGeometry(QRect(20, 360, 75, 23));
        btnClose = new QPushButton(widget_4);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(20, 390, 75, 23));

        horizontalLayout_2->addWidget(widget_4);


        verticalLayout_2->addWidget(widget_3);


        verticalLayout_3->addWidget(widget_1);


        horizontalLayout->addWidget(widget);

        ManageMaterial->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ManageMaterial);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ManageMaterial->setStatusBar(statusbar);
        QWidget::setTabOrder(inputKeyword, treeWidget);
        QWidget::setTabOrder(treeWidget, inputCountry);
        QWidget::setTabOrder(inputCountry, inputManufacturer);
        QWidget::setTabOrder(inputManufacturer, inputName);
        QWidget::setTabOrder(inputName, inputSubject);
        QWidget::setTabOrder(inputSubject, inputCategory);
        QWidget::setTabOrder(inputCategory, btnSearch);
        QWidget::setTabOrder(btnSearch, table);

        retranslateUi(ManageMaterial);

        QMetaObject::connectSlotsByName(ManageMaterial);
    } // setupUi

    void retranslateUi(QMainWindow *ManageMaterial)
    {
        ManageMaterial->setWindowTitle(QApplication::translate("ManageMaterial", "\350\264\250\346\216\247\345\223\201\347\273\264\346\212\244", 0));
        groupBox_3->setTitle(QString());
        label->setText(QApplication::translate("ManageMaterial", "\344\272\247\345\234\260", 0));
        label_3->setText(QApplication::translate("ManageMaterial", "\345\216\202\345\256\266", 0));
        label_4->setText(QApplication::translate("ManageMaterial", "\344\272\232\344\270\223\344\270\232", 0));
        label_5->setText(QApplication::translate("ManageMaterial", "\345\220\215\347\247\260", 0));
        label_6->setText(QApplication::translate("ManageMaterial", "\344\270\223\344\270\232", 0));
        btnSearch->setText(QApplication::translate("ManageMaterial", "\346\237\245\350\257\242", 0));
        btnAdd->setText(QApplication::translate("ManageMaterial", "\346\267\273\345\212\240", 0));
        btnClose->setText(QApplication::translate("ManageMaterial", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class ManageMaterial: public Ui_ManageMaterial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEMATERIAL_H
